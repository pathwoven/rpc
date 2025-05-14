#ifndef LOGGER_H
#define LOGGER_H
#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

class Logger{
public:
    static void Trace(const std::string& msg);
    static void Debug(const std::string& msg);
    static void Info(const std::string& msg);
    static void Warning(const std::string& msg);
    static void Error(const std::string& msg);
    static void Critical(const std::string& msg);

    static void init(const std::string& fileName = "logs/rpc.log", size_t maxSize = 1048576 * 5, size_t maxFile = 3);

private:
    static std::shared_ptr<spdlog::logger> logger_;
};
 
#endif   // LOGGER_H