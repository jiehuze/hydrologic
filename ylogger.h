#ifndef YLOGGER_H
#define YLOGGER_H

#include <string>
#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>


class YLogger {
public:
    // 构造函数，接受日志目录、日志格式和日志级别
    YLogger(const std::string &log_dir = "logs/",
            const std::string &log_pattern = "[%Y-%m-%d %H:%M:%S.%e] [%l] %v",
            spdlog::level::level_enum log_level = spdlog::level::info);

    // 设置日志级别和目录
    void set_log_config(spdlog::level::level_enum log_level, const std::string &log_dir);

    // 提供日志记录接口
    template <typename T>
    inline void info(const T &msg){
        spdlog::info(msg);
    }
    template <typename T>
    inline void warn(const T &msg){
        spdlog::warn(msg);
    }
    template <typename T>
    inline void error(const T &msg){
        spdlog::error(msg);
    }
    template <typename T>
    inline void debug(const T &msg){
        spdlog::debug(msg);
    }

    template <typename... Args>
    inline void info(spdlog::format_string_t<Args...> fmt, Args &&...args){
        spdlog::info(fmt, std::forward<Args>(args)...);
    }
    template <typename... Args>
    inline void warn(spdlog::format_string_t<Args...> fmt, Args &&...args){
        spdlog::warn(fmt, std::forward<Args>(args)...);
    }
    template <typename... Args>
    inline void error(spdlog::format_string_t<Args...> fmt, Args &&...args){
        spdlog::error(fmt, std::forward<Args>(args)...);
    }
    template <typename... Args>
    inline void debug(spdlog::format_string_t<Args...> fmt, Args &&...args){
        spdlog::debug(fmt, std::forward<Args>(args)...);
    }


private:
    // 获取当前日期并生成文件名
    std::string get_current_date_filename(const std::string &log_dir);

    void update_log_file_sink();  // 用于更新文件输出的 Sink

    std::string log_directory;
    std::string log_pattern;
    spdlog::level::level_enum log_level;
    std::shared_ptr<spdlog::logger> logger;
};

// 全局日志实例声明
extern YLogger ylog;

#endif // YLOGGER_H
