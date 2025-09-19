# rpc

## 运行example
- 生成protobuf 的文件
```
protoc -I=../example/proto --cpp_out=../example/proto ../example/proto/Calculator.proto && protoc -I=../src/proto --cpp_out=../src/proto ../src/proto/RpcHeader.proto
```

- 在项目根目录下创建build文件夹，配置并构建项目
``` 
rm -rf build && mkdir build && cd build && cmake .. && make
```

- 进入example并构建
```
cd ../example && rm -rf build && mkdir build && cd build && cmake .. && make
```

- 运行
```
cd ../bin && ./server
./client
```

## 使用docker部署测试
- 进入test目录
```
cd test
```
- 构建基础镜像
```
docker compose build server_builder client_builder
```
- 运行docker-compose
```
docker compose up -d
```
### 配置docker代理（可选）
> 该方法需要重启docker服务，如果有不想关闭的容器的话，可以去查找其他不需要重启的方法
- 创建配置文件
```shell
sudo mkdir -p /etc/systemd/system/docker.service.d
sudo nano /etc/systemd/system/docker.service.d/proxy.conf
```
- 写入（我的代理ip不能够用127.0.0.1，而是用网络设置里配置的ip）
```
[Service]
Environment="HTTP_PROXY=http://<代理IP>:<代理端口>/"
Environment="HTTPS_PROXY=http://<代理IP>:<代理端口>/"
```
- 重启
```shell
sudo systemctl daemon-reexec
sudo systemctl restart docker
```