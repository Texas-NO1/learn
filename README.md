# learn
学习用库，包含各种代码
1. C/C++特性学习：stl容器内存优化、自定义new方法、template模版、library生成、socket网络编程、POD类型
2. 自造轮子：线程池实现、C++中不同矩阵计算库与比较、时间格式转换
3. 第三方库或工具学习：kafka、redis、rocksdb、httplib、json、nginx、mysql、
4. 算法：如《算法导论》、《编程珠玑》的章节代码，如快排序；
5. 工具：如jemalloc和jeprof的使用，进行内存泄露定位；cmake学习测试
## 构建运行镜像
`docker build . -t learn:0.0.1`
## 启动环境
`docker-compose up -d`