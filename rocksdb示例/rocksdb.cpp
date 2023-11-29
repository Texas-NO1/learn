// g++ rocksdb.cpp -lrocksdb
#include <iostream>
#include <rocksdb/db.h>
#include <rocksdb/utilities/db_ttl.h>

rocksdb::DBWithTTL *init_rdb(std::string db_path, int ttl = 0, bool read_only = false) {
    rocksdb::DBWithTTL *db = nullptr;
    rocksdb::Options options;
    options.IncreaseParallelism();
    options.OptimizeLevelStyleCompaction();
    options.create_if_missing = true;
    // options.max_compaction_bytes = 1;
    options.periodic_compaction_seconds = 1800;
    options.level_compaction_dynamic_level_bytes = true;
    options.min_write_buffer_number_to_merge = 4;
    options.write_buffer_size = 256 << 20;
    options.max_bytes_for_level_base = 1024 << 20;
    options.num_levels = 3;
    options.compression_opts.enabled = true;
    options.compression = rocksdb::CompressionType::kLZ4Compression;
    options.bottommost_compression = rocksdb::CompressionType::kZSTD;
    // ttl<=0时表示默认ttl无限大
    rocksdb::Status status = rocksdb::DBWithTTL::Open(options, db_path, &db, ttl, read_only);
    if (!status.ok()) {
        std::runtime_error("rdb open failed " + std::to_string(status.code()));
    }
    return db;
}

int main() {
    auto db = init_rdb("/app/test_db", 3600);
    std::string key = "test";
    std::string value;
    rocksdb::Status res = db->Get(rocksdb::ReadOptions(), key, &value);
    if (res.ok()) {
        std::cout << "key " << key << " value is" << value << std::endl;
    } else {
        std::cout << "key " << key << " is not in db" << std::endl;
    }
    rocksdb::WriteBatch batch;
    batch.Put()
    res = db->Write(rocksdb::WriteOptions(), );
    delete db;
    return 0;
}