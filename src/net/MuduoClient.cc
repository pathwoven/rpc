#include "MuduoClient.h"

#include "RpcHeader.pb.h"
#include "Logger.h"

//muduo::net::EventLoopThread loopThread_;
std::unique_ptr<muduo::Thread> MuduoClient::eventLoopThread_; 
muduo::net::EventLoop* MuduoClient::eventLoop_ = nullptr;

void MuduoClient::init(){
    if(eventLoop_){
        Logger::Error("MuduoClient::init() 只能调用一次");
        return;
    }
    eventLoopThread_ = std::make_unique<muduo::Thread>([](){
        muduo::net::EventLoop loop;
        eventLoop_ = &loop;
        MuduoClient::eventLoop_->loop();
    });
    eventLoopThread_->start();
    //eventLoop_->loop();
}

MuduoClient::~MuduoClient(){
    // todo
    // if(eventLoop_){
    //     eventLoop_->quit();
    //     eventLoopThread_->join();
    // }
}

MuduoClient::MuduoClient(const std::string& ip, const std::string& port):
client_ (eventLoop_, 
        muduo::net::InetAddress(ip, std::atoi(port.c_str())),
        ip+":"+port)
{
    ip_ = ip;
    port_ = port;

    client_.setConnectionCallback(std::bind(&MuduoClient::onConnection, this,std::placeholders::_1));
    client_.setMessageCallback(std::bind(&MuduoClient::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    client_.connect();
}

void MuduoClient::disconnect(){
    client_.disconnect();    
}

void MuduoClient::sendMessage(const std::string& header,const std::string& body){
    muduo::net::Buffer buffer;
    if(header!=""){
        uint32_t headerSize = header.size();
        buffer.append(&headerSize, 4);

        buffer.append(header);
    }
    uint32_t bodySize = body.size();
    buffer.append(&bodySize, 4);
    buffer.append(body);

    if(conn_->connected()){
        conn_->send(&buffer);
    }else{
        // todo
    }
}


void MuduoClient::sendMessage(const std::string& header,const std::string& body, uint32_t reqId, const std::function<void()>& cb){
     // 设置回调
    {
        std::lock_guard<std::mutex> lock(idMutex_);
        responseCbMap_[reqId] = cb;
    }
    muduo::net::Buffer buffer;
    if(header!=""){
        uint32_t headerSize = header.size();
        buffer.append(&headerSize, 4);

        buffer.append(header);
    }
    uint32_t bodySize = body.size();
    buffer.append(&bodySize, 4);
    buffer.append(body);

    if(conn_->connected()){
        conn_->send(&buffer);
    }else{
        // todo
    }
}

// void MuduoClient::setMessageCb(std::function<void(std::string&, std::string&)>& cb){
//     msgCb_ = std::move(cb);
// }

void MuduoClient::onMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buffer, muduo::Timestamp timestamp){
    while(buffer->readableBytes()>4){
        const char* data = buffer->peek();
        // 读取头部长度
        uint32_t headerSize = ntohl(*reinterpret_cast<const u_int32_t*>(data));
        if(buffer->readableBytes() < headerSize + 4) break;   // 不完整
        // 读取体的长度
        data += 4 + headerSize;
        uint32_t bodySize = ntohl(*reinterpret_cast<const u_int32_t*>(data));
        if(buffer->readableBytes() < headerSize + bodySize + 8) break;  // 不完整，等待下次调用

        // 读取头部
        buffer->retrieve(4);   // 跳过头部长度
        std::string header(buffer->peek(), headerSize);
        buffer->retrieve(headerSize);
        RpcHeader::ResponseHeader resHeader;
        uint32_t id;
        if(resHeader.ParseFromString(header)){
            id = resHeader.id();
        }else{
            Logger::Error("反序列化响应头部失败");
            // 设置错误  todo
            return;
        }

        // 读取rpc体
        buffer->retrieve(4);
        std::string message(buffer->peek(), bodySize);
        buffer->retrieve(bodySize);

        // msgCb_(header, message);
        {
            std::lock_guard<std::mutex> lock(idMutex_);
            auto it = responseCbMap_.find(id);
            if(it != responseCbMap_.end()){
                // 调用回调
                (it->second)();
            }
        }
    }
}
void MuduoClient::onConnection(const muduo::net::TcpConnectionPtr& conn){
    if(conn->connected()){
        conn_ = conn;
    }else{
        // todo
    }
}