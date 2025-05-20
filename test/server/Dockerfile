FROM ubuntu:22.04

# 安装依赖
RUN apt-get update && \
    apt-get install -y cmake g++ libprotobuf-dev protobuf-compiler

# 创建目录
WORKDIR /app

# 拷贝源码并构建
COPY . .
RUN mkdir build && cd build && cmake .. && make

# 设置启动命令（假设生成的可执行文件叫 server）
CMD ["./build/server"]
