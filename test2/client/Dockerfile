FROM ubuntu:22.04

# 安装必要的运行时依赖
RUN apt-get update && \
    apt-get install -y g++ libprotobuf-dev libboost-all-dev && \
    rm -rf /var/lib/apt/lists/*

# 创建目录
WORKDIR /app

# 拷贝静态库和头文件
COPY ../build/librpc.a ./lib/
COPY ../src/include ./include/


# 拷贝源码并构建
COPY ./client ./client
RUN mkdir build && cd build && cmake ../client && make

# 设置启动命令
CMD ["./client/bin/client"]
