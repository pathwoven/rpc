#include "MuduoServer.h"
#include<iostream>

void MuduoServer::bindListen(std::string ip, int port, std::string name=""){
    // 创建地址对象
    muduo::net::InetAddress addr(ip, port);
    // 创建server
    server = std::make_shared<muduo::net::TcpServer>(&eventLoop, addr, name);

    
}

void MuduoServer::setConnCallback(void (*OnConn())){
    
}
void OnConnection(const muduo::net::TcpConnectionPtr& conn){
    if(!conn->connected()){
        conn->shutdown();   // 断开连接
    }
}
void OnMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buffer, muduo::Timestamp receiveTime){
    std::cout << "receive message" << std::endl;  // todo
}

void MuduoServer::setThreadNum(int num){
    server->setThreadNum(num);
}

void MuduoServer::run(){
    server->setConnectionCallback(std::bind(&OnConnection, this, std::placeholders::_1));
    server->setMessageCallback(std::bind(&OnMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    server->start();
    eventLoop.loop();
}