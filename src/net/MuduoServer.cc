#include "MuduoServer.h"
#include<iostream>

void MuduoServer::bindListen(std::string ip, int port, std::string name){
    // 创建地址对象
    muduo::net::InetAddress addr(ip, port);
    // 创建server
    server_ = std::make_shared<muduo::net::TcpServer>(&eventLoop_, addr, name);
}

void MuduoServer::setConnCallback(void (*OnConn())){
    
}
void MuduoServer::onConnection(const muduo::net::TcpConnectionPtr& conn){
    if(!conn->connected()){
        conn->shutdown();   // 断开连接
    }
}

// 消息回调
void MuduoServer::setMessCallback(std::function<void(std::string&, std::string&, void*)> cb){
    messCb_ = std::move(cb);
}
void MuduoServer::onMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buffer, muduo::Timestamp receiveTime){
    
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

        // 读取rpc体
        buffer->retrieve(4);
        std::string message(buffer->peek(), bodySize);
        buffer->retrieve(bodySize);

        messCb_(header, message, static_cast<void*>(conn.get()));
    }
}

void MuduoServer::setSendCallback(std::function<void(std::string&,std::string&,void*)>& sendCb){
    sendCb = [this](std::string& header, std::string& msg, void* cxt){
        muduo::net::TcpConnection* conn = static_cast<muduo::net::TcpConnection*>(cxt);
        this->SendMessage(header, msg, muduo::net::TcpConnectionPtr(conn));
    };
}
void MuduoServer::SendMessage(std::string& header, std::string& body, const muduo::net::TcpConnectionPtr& conn){
    muduo::net::Buffer buffer;
    if(header!=""){
        uint32_t headerSize = header.size();
        buffer.append(&headerSize, 4);

        buffer.append(header);
    }
    uint32_t bodySize = body.size();
    buffer.append(&bodySize, 4);
    buffer.append(body);

    conn->send(&buffer);
}

void MuduoServer::setThreadNum(int num){
    server_->setThreadNum(num);
}

void MuduoServer::run(){
    // note: 注意绑定非静态成员时，前面要显示类名
    server_->setConnectionCallback(std::bind(&MuduoServer::onConnection, this, std::placeholders::_1));
    server_->setMessageCallback(std::bind(&MuduoServer::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    server_->start();
    eventLoop_.loop();
}