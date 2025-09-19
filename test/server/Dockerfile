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
    libyaml-cpp-dev \
    && rm -rf /var/lib/apt/lists/*

# 构建 Muduo
RUN git clone https://github.com/chenshuo/muduo.git /tmp/muduo && \
    cd /tmp/muduo && \
    ./build.sh && ./build.sh install && \
    cd /tmp/build/release-install-cpp11/include && mv muduo/ /usr/include/ && \
    cd ../lib && mv * /usr/local/lib/

# # 构建 yaml-cpp
# RUN git clone https://github.com/jbeder/yaml-cpp.git && \
#     cd yaml-cpp && \
#     mkdir build && cd build && \
#     cmake -D BUILD_SHARED_LIBS=ON .. && \
#     make -j16 && \
#     make install

# 构建spdlog
RUN git clone https://github.com/gabime/spdlog.git /tmp/spdlog && \
    mkdir -p /tmp/spdlog/build && cd /tmp/spdlog/build && \
    cmake .. && make -j$(nproc) && make install



# 拷贝项目源码
WORKDIR /app
COPY . .

# 构建
RUN rm -rf build && mkdir build && cd build && cmake .. && make VERBOSE=1
RUN mkdir test/lib && mv lib/* test/lib/
RUN cd test/server && rm -rf build && mkdir build && cd build && cmake .. && make VERBOSE=1

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
COPY --from=builder /app/test/lib/ /app/lib/
COPY --from=builder /app/test/server/bin/ /app/server/bin/
COPY --from=builder /app/src/include/ /app/src/include/

# 设置启动命令
CMD ["./server/bin/server"]
