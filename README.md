# 1. 功能介绍
本文档是一个水文项目，其中封装了log模块


# 模块
 
## 1. log模块
该模块主要使用spdlog进行封装，可以直接引入同文件即可使用；当需要更改日志级别和日志写入目录时，在代码入口进行配置，及时生效；
该日志模块的实例为全局实例，命名为：ylog，目前支持四个级别 info， debug error 和 warn
该日志可以在控制台和文件中打印日志内容；