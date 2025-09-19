# ------------
# 编译构建阶段
# ------------
FROM ubuntu:22.04 AS builder

# 安装构建依赖
RUN apt-get update && apt-get install -y\
    build-essential g++ cmake make git\
    libzookeeper-mt-dev zookeeperd \
    libprotobuf-dev protobuf-compiler \
    libboost-dev \
    libspdlog-dev \
    libyaml-cpp-dev \
    && rm -rf /var/lib/apt/lists/*

# 构建 Muduo
RUN git clone https://github.com/chenshuo/muduo.git /tmp/muduo && \
    cd /tmp/muduo && \
    ./build.sh && ./build.sh install && cd build/release-install-cpp11 && \
    cd include && mv muduo/ /usr/local/include/ && \
    cd ../lib && mv * /usr/local/lib/


# 拷贝项目源码
WORKDIR /app
COPY . .

# 构建
RUN mkdir build && cd build && cmake .. && make
RUN cd test2/client && mkdir build && cd build && cmake .. && make

# ------------
# 运行时阶段
# ------------
FROM ubuntu:22.04 AS runtime

# 安装运行时依赖
RUN apt update && apt install -y \
    libprotobuf-dev libzookeeper-mt-dev \
    libyaml-cpp-dev \
    && rm -rf /var/lib/apt/lists/*

# 从构建阶段拷贝库文件和可执行文件
COPY --from=builder /usr/local/lib /usr/local/lib
COPY --from=builder /usr/local/include /usr/local/include
COPY --from=builder /app/lib/ /app/lib/
COPY --from=builder /app/test2/bin/ /app/test2/bin/
COPY --from=builder /app/src/include/ /app/src/include/

# 设置启动命令
CMD ["./test2/bin/client"]
