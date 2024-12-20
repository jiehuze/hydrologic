# 1. 功能介绍
本文档是一个水文项目，其中封装了log模块


# 2. 模块

## 1. log模块
> 该模块主要使用spdlog进行封装，可以直接引入同文件即可使用；当需要更改日志级别和日志写入目录时，在代码入口进行配置，及时生效；
> 该日志模块的实例为全局实例，命名为：ylog，目前支持四个级别 info， debug error 和 warn
> 该日志可以在控制台和文件中打印日志内容；
``` 
移植文件和目录：
日志文件包括：ylogger.cpp  ylogger.h   
spd头文件目录：spdlog
都需要移植到新的项目中；
```

## 2. serialport 串口协议

### 2.1 重要方法

```
setPortName(const QString &name)：设置串行端口的名称，如 "COM1"、"ttyUSB0" 等。
portName() const：返回当前串行端口的名称。
setBaudRate(BaudRate baudRate, Directions directions = AllDirections)：设置串行通信的波特率。
baudRate() const：返回当前波特率。
setDataBits(DataBits dataBits)：设置数据位数量。
dataBits() const：返回当前数据位数量。
setParity(Parity parity)：设置校验位类型。
parity() const：返回当前校验位类型。
setStopBits(StopBits stopBits)：设置停止位数量。
stopBits() const：返回当前停止位数量。
setFlowControl(FlowControl flowControl)：设置流控制类型。
flowControl() const：返回当前流控制类型。
open(OpenMode mode = ReadWrite)：打开串行端口。
close()：关闭串行端口。
isOpen() const：检查串行端口是否已打开。
read(qint64 maxSize)：从串行端口读取数据。
write(const QByteArray &data)：向串行端口写入数据。
waitForReadyRead(int msecs = -1)：等待数据到达，可设置超时时间。
waitForBytesWritten(int msecs = -1)：等待数据写入完成，可设置超时时间。
clear(SerialPortError error)：清除指定的错误标志。
error() const：返回当前错误状态。

```

### 2.2 重要信号

```
readyRead()：当串行端口有数据可读时发出。
bytesWritten(qint64 bytes)：当数据写入串行端口完成时发出，参数为写入的字节数。
errorOccurred(QSerialPort::SerialPortError error)：当发生串行通信错误时发出，参数为错误类型。
```

### 2.3 常用枚举类型

```
BaudRate：表示波特率的枚举类型，如 Baud9600、Baud115200 等。
DataBits：表示数据位数量的枚举类型，如 Data5、Data6、Data7、Data8 等。
Parity：表示校验位类型的枚举类型，如 NoParity、EvenParity、OddParity 等。
StopBits：表示停止位数量的枚举类型，如 OneStop、TwoStop 等。
FlowControl：表示流控制类型的枚举类型，如 NoFlowControl、HardwareControl 等。
OpenMode：表示打开串行端口时的模式，如 ReadOnly、WriteOnly、ReadWrite 等。
SerialPortError：表示串行通信错误类型的枚举类型，如 ResourceError、PermissionError 等。
```

# 3 serialbus（modlu bus）

![image-20241218153443636](/Users/jiehu/Library/Application Support/typora-user-images/image-20241218153443636.png)