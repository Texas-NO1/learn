#include <iostream>
#include <set>
#include <librdkafka/rdkafkacpp.h>
#include <thread>

int main () {

    RdKafka::Conf *conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
    std::string brokers = "172.16.244.13:9094";
    std::string group_id = "qxai-test";
    std::string errstr;
    conf->set("debug", "broker", errstr);
    std::cout << errstr << std::endl;
    conf->set("security.protocol", "SASL_SSL", errstr);
    std::cout << errstr << std::endl;
    conf->set("sasl.mechanism", "PLAIN", errstr);
    std::cout << errstr << std::endl;
    conf->set("sasl.username", "admin", errstr);
    std::cout << errstr << std::endl;
    conf->set("sasl.password", "tvPZd5PvGnMPT1DfUMhy", errstr);
    std::cout << errstr << std::endl;
    conf->set("ssl.ca.location", "/app/resources/kafka/ca-cert", errstr);
    std::cout << errstr << std::endl;
    conf->set("enable.ssl.certificate.verification", "false", errstr);
    std::cout << errstr << std::endl;
    conf->set("ssl.endpoint.identification.algorithm", "none", errstr);
    std::cout << errstr << std::endl;

    conf->set("enable.partition.eof", "false", errstr);
    std::cout << errstr << std::endl;
    conf->set("message.max.bytes", "1000000000", errstr);
    std::cout << errstr << std::endl;
    conf->set("auto.offset.reset", "earliest", errstr);
    std::cout << errstr << std::endl;
    conf->set("metadata.broker.list", brokers, errstr);
    std::cout << errstr << std::endl;
    conf->set("group.id", group_id, errstr);
    std::cout << errstr << std::endl;
    conf->set("max.poll.interval.ms", "300000", errstr);
    std::cout << errstr << std::endl;
    conf->set("session.timeout.ms", "30000", errstr);
    std::cout << errstr << std::endl;
    conf->set("heartbeat.interval.ms", "3000", errstr);
    std::cout << errstr << std::endl;
    conf->set("allow.auto.create.topics", "true", errstr);
    std::cout << errstr << std::endl;
    RdKafka::KafkaConsumer *consumer = RdKafka::KafkaConsumer::create(conf, errstr);
    std::cout << errstr << std::endl;
    
    consumer->subscribe({"test-topic"});
    while (true) {
        consumer->consume(0);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}