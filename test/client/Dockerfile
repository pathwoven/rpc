FROM ubuntu:22.04

# 设置非交互模式
ENV DEBIAN_FRONTEND=noninteractive

# 安装基础依赖
RUN apt-get update && \
    apt-get install -y \
        cmake \
        g++ \
        protobuf-compiler \
        libprotobuf-dev \
        wget \
        build-essential \
        unzip \
        sudo \
        libzookeeper-mt-dev \
        libboost-all-dev \
        git \
        curl \
    && rm -rf /var/lib/apt/lists/*

# 安装 zookeeper 服务
RUN apt-get update && \
    apt-get install -y zookeeperd && \
    rm -rf /var/lib/apt/lists/*

# 安装 spdlog（从 GitHub 编译头文件库）
RUN git clone https://github.com/gabime/spdlog.git /tmp/spdlog && \
    mkdir -p /tmp/spdlog/build && cd /tmp/spdlog/build && \
    cmake .. && make -j$(nproc) && make install && \
    rm -rf /tmp/spdlog

# 安装 Muduo（从 GitHub 编译）
RUN git clone https://github.com/chenshuo/muduo.git /tmp/muduo && \
    mkdir -p /tmp/muduo/build && cd /tmp/muduo/build && \
    cmake .. && make -j$(nproc) && make install && \
    rm -rf /tmp/muduo

# 创建目录
WORKDIR /app

# 拷贝源码并构建
COPY . .
RUN mkdir build && cd build && cmake .. && make

# 设置启动命令
CMD ["./bin/client"]
