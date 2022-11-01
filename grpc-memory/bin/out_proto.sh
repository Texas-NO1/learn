#!/bin/bash

protoDirs="./proto"
generatedDir="./src/generated"

for protoDir in $protoDirs;
do
    echo ${protoDir}
    protoc -I${protoDir} --cpp_out=${generatedDir} --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ${protoDir}/*.proto
    protoc -I${protoDir} --grpc_out=${generatedDir} --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ${protoDir}/*.proto
done