#include "YLogger.h"
#include <ctime>
#include <sstream>
#include <iomanip>
#include <vector>

// 获取当前日期并生成文件名
std::string YLogger::get_current_date_filename(const std::string &log_dir) {
    std::time_t now = std::time(nullptr);
    std::tm* time_tm = std::localtime(&now);

    std::ostringstream oss;
    oss << log_dir << "log_"
        << std::put_time(time_tm, "%Y-%m-%d") << ".log"; // 使用日期作为文件名
    return oss.str();
}

// 构造函数，初始化日志系统
YLogger::YLogger(const std::string &log_dir,
                 const std::string &log_pattern,
                 spdlog::level::level_enum log_level)
    : log_directory(log_dir), log_pattern(log_pattern), log_level(log_level) {

    // 创建控制台日志输出
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

    // 获取当前日期并生成日志文件名
    std::string log_filename = get_current_date_filename(log_directory);

    // 文件日志输出，使用 rotating_file_sink 进行日志轮转
    // 每个文件最大10MB，最多保留3个文件
    auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
        log_filename, 10 * 1024 * 1024, 3);

    // 合并日志输出目标
    std::vector<spdlog::sink_ptr> sinks{console_sink, file_sink};

    // 创建日志器，并关联到输出目标
    logger = std::make_shared<spdlog::logger>("multi_sink", sinks.begin(), sinks.end());

    // 设置日志格式和级别
    spdlog::set_default_logger(logger);
    spdlog::set_pattern(log_pattern);
    spdlog::set_level(log_level);
    spdlog::flush_on(log_level);  // 设置自动刷新级别
}

// 设置日志级别和日志目录
void YLogger::set_log_config(spdlog::level::level_enum new_log_level, const std::string &new_log_dir) {

    // 更新日志目录
    log_directory = new_log_dir;
    update_log_file_sink();  // 更新日志文件 sink

    // 更新日志级别
    log_level = new_log_level;
    spdlog::set_level(log_level);
    spdlog::flush_on(log_level);  // 设置自动刷新级别
}

// 更新日志文件输出 sink
void YLogger::update_log_file_sink() {
    std::string new_log_filename = get_current_date_filename(log_directory);

    // 创建新的 rotating_file_sink
    auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
        new_log_filename, 10 * 1024 * 1024, 3);

    // 获取当前的控制台输出 sink
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

    // 重新设置 logger
    std::vector<spdlog::sink_ptr> sinks{console_sink, file_sink};
    logger = std::make_shared<spdlog::logger>("multi_sink", sinks.begin(), sinks.end());
    spdlog::set_default_logger(logger);
    spdlog::set_pattern(log_pattern);
}


// 提供日志记录接口
void YLogger::info(const std::string &message) {
    spdlog::info(message);
}

void YLogger::warn(const std::string &message) {
    spdlog::warn(message);
}

void YLogger::error(const std::string &message) {
    spdlog::error(message);
}

void YLogger::debug(const std::string &message) {
    spdlog::debug(message);
}

// 全局日志实例定义
YLogger ylog("logs/", "[%Y-%m-%d %H:%M:%S.%e] [%l] %v", spdlog::level::info);
