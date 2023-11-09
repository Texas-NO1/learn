#include <librdkafka/rdkafkacpp.h>
#include <librdkafka/rdkafka.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <cassert>

std::string topic_str = "test-topic-1";

void show_config(RdKafka::Conf* conf) {
        std::list<std::string> *dump;
        dump = conf->dump();
        std::cout << "# config" << std::endl;

        for (std::list<std::string>::iterator it = dump->begin();
            it != dump->end();) {
            std::cout << *it << " = ";
            it++;
            std::cout << *it << std::endl;
            it++;
        }
        std::cout << std::endl;
}

void consume_test() {
std::string errstr;
    RdKafka::Conf* conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
    RdKafka::Conf* tconf = RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC);

    conf->set("group.id", "test-group", errstr);
    conf->set("allow.auto.create.topics", "true", errstr);
    conf->set("metadata.broker.list", "kafka:9092", errstr);
    conf->set("default_topic_conf", tconf, errstr);
    conf->set("debug", "all", errstr);

    RdKafka::KafkaConsumer *consumer = RdKafka::KafkaConsumer::create(conf, errstr);
    std::cout << errstr << std::endl;
    assert(consumer);

    RdKafka::Conf* new_tconf = RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC);
    RdKafka::Topic *topic = RdKafka::Topic::create(consumer, topic_str, new_tconf, errstr);
    // delete topic;
    // assert(topic);
    // {
        // RdKafka::TopicPartition *topic_partition = RdKafka::TopicPartition::create(topic_str, RdKafka::Topic::PARTITION_UA);
        // std::vector<RdKafka::TopicPartition*> topic_partitions = {topic_partition};
        // RdKafka::ErrorCode err = consumer->assign(topic_partitions);
        // delete topic_partition;
    // }
    // {
        std::vector<std::string> topics = {topic_str};
        RdKafka::ErrorCode err = consumer->subscribe(topics);
        if (err) std::cout << "errcode " << err << std::endl;
    // }

    // delete conf;
    // delete tconf;

    // RdKafka::Message *message = consumer->consume(30000);
    // if (message->err()) std::cout << message->errstr() << std::endl;
    // else {
    //     std::cout << "consume message: " << message << std::endl;
    // }
    while (1) std::this_thread::sleep_for(std::chrono::seconds(10));
}

class DeliveryReportCb : public RdKafka::DeliveryReportCb {
 public:
  void dr_cb(RdKafka::Message &message) {
    /* If message.err() is non-zero the message delivery failed permanently
     * for the message. */
    if (message.err())
       std::cout << "[PRODUCER] Message delivery failed: " << message.errstr() << " len {}";
  }
};

void produce_test() {
    std::string errstr;
    RdKafka::Conf* conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
    RdKafka::Conf* tconf = RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC);

    conf->set("metadata.broker.list", "sh-cpu001.aibee.cn:9092", errstr);
    conf->set("message.timeout.ms", "1000", errstr);
    conf->set("default_topic_conf", tconf, errstr);
    conf->set("debug", "all", errstr);
    // conf->set("allow.auto.create.topics", "true", errstr);
    DeliveryReportCb ex_dr_cb;
    conf->set("dr_cb", &ex_dr_cb, errstr);
    show_config(conf);
    RdKafka::Producer *producer = RdKafka::Producer::create(conf, errstr);
    // show_config(conf);
    if (!producer) {
       std::cout << errstr << std::endl;
    }
    std::string message = "12243536t4564";
    RdKafka::ErrorCode err = producer->produce(
        topic_str, RdKafka::Topic::PARTITION_UA,
        RdKafka::Producer::RK_MSG_COPY,                       // Copy payload
        const_cast<char *>(message.c_str()), message.size(),  // value
        NULL, 0,                                              // key
        0,    // Timestamp (defaults to now)
        NULL  // Message headers, if any
    );
    if (err != RdKafka::ERR_NO_ERROR) std::cout << err << std::endl;
    producer->poll(0);
    while (1) std::this_thread::sleep_for(std::chrono::seconds(10));
}

int main () {
    // produce_test();
    consume_test();
    // std::thread t_consume(consume_test);
    // std::thread t_produce(produce_test);
    // std::this_thread::sleep_for(std::chrono::seconds(60));
    return 0;
}