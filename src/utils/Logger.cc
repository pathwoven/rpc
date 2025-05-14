#include "Logger.h"

std::shared_ptr<spdlog::logger> Logger::logger_ = nullptr;

void Logger::init(const std::string& fileName, size_t maxSize, size_t maxFile){
#if DEBUG
    auto sink_console = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    sink_console->set_pattern("[%Y-%m-%d %H:%M:%S.%e][%n][%^%l%$][thread %t] %v");
    auto sink_file = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(fileName, maxSize, maxFile);
    sink_file->set_pattern("[%Y-%m-%d %H:%M:%S.%e][%n][%l][thread %t] %v");
    spdlog::init_thread_pool(8192, 1); // 队列长度 + 后台线程数
    logger_ = std::make_shared<spdlog::async_logger>(
        "rpcLogger", spdlog::sinks_init_list{sink_console, sink_file},
        spdlog::thread_pool(), spdlog::async_overflow_policy::block);
    logger_->set_level(spdlog::level::debug);
#else
    auto sink_file = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(fileName, maxSize, maxFile);
    sink_file->set_pattern("[%Y-%m-%d %H:%M:%S.%e][%n][%l][thread %t] %v");
    spdlog::init_thread_pool(8192, 1); // 队列长度 + 后台线程数    todo 配置修改异步/同步， 线程数量、队列长度
    logger_ = std::make_shared<spdlog::async_logger>(
        "rpcLogger", sink_file,
        spdlog::thread_pool(), spdlog::async_overflow_policy::block);
    logger_->set_level(spdlog::level::info);
#endif
    spdlog::register_logger(logger_);
}

void Logger::Trace(const std::string& msg){
    logger_->trace(msg);
}
void Logger::Debug(const std::string& msg){
    logger_->debug(msg);
}
void Logger::Info(const std::string& msg){
    logger_->info(msg);
}
void Logger::Warning(const std::string& msg){
    logger_->warn(msg);
}
void Logger::Error(const std::string& msg){
    logger_->error(msg);
}
void Logger::Critical(const std::string& msg){
    logger_->critical(msg);
}
