# rpc

## 运行example
- 生成protobuf 的文件
```
protoc -I=../example/proto --cpp_out=../example/proto ../example/proto/Calculator.proto && protoc -I=../src/proto --cpp_out=../src/proto ../src/proto/RpcHeader.proto
```

- 在项目根目录下创建build文件夹，配置并构建项目
``` 
mkdir build && cd build && cmake .. && make
```

- 运行（在项目根目录下）
```
cd bin && ./server
./client
```