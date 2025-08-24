FROM ubuntu:22.04  AS deps

# 安装必要的运行时依赖
RUN apt-get update && \
    apt-get install -y g++ libprotobuf-dev libboost-all-dev && \
    rm -rf /var/lib/apt/lists/*

# 创建目录
WORKDIR /app

# 编译原项目
FROM deps AS builder

# 拷贝静态库和头文件
COPY ../build/librpc.a ./lib/
COPY ../src/include ./include/


# 拷贝源码并构建
COPY ./server ./server
RUN mkdir build && cd build && cmake ../server && make

# 设置启动命令
CMD ["./server/bin/server"]
