#include "mainwindow.h"

#include <QApplication>
#include "ylogger.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //设置日志级别和目录
    ylog.set_log_config(spdlog::level::debug, "/Users/jiehu/works/test/logs/");
    MainWindow w;
    w.show();

    ylog.info("This is an info log");
    ylog.warn("This is a warning log");
    ylog.error("This is an error log");
    ylog.debug("This is an debug log");
    ylog.info("set_log_config is an info log");
    ylog.warn("set_log_config is a warning log");
    ylog.error("set_log_config is an error log");
    ylog.debug("set_log_config is an debug log");

    return a.exec();
}
