#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ylogger.h"

#include <QTimer>

#include <QModbusTcpClient>
#include <QModbusDataUnit>
#include <QModbusReply>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_serial_read(new QSerialPort(this))
    , m_serial_write(new QSerialPort(this))
    , m_num(0)
{
    ui->setupUi(this);
    int mun = 100;

    ylog.info("MainWindow is an info log");
    ylog.warn("MainWindow is a warning log");
    ylog.error("MainWindow is an error log");

    ylog.info("num: {}", mun);
    ylog.info("num: {}", "mun");
    qDebug() << "MainWindow ylog addr: " << &ylog;

    //获取端口，调用 QSerialPortInfo 类的静态方法 availablePorts()，获取当前系统中所有可用的串口信息，并将其存储在 portInfo 列表中。
    QList<QSerialPortInfo>  portInfo = QSerialPortInfo::availablePorts();
    //遍历串口信息
    foreach(QSerialPortInfo info,portInfo)
    {
        // ui->comboBox->addItem(info.portName());//添加到下拉框中
        ylog.info("ports list : {}", info.portName().toStdString());
        // spdlog::info("port info {}", info.portName().toStdString());

        // qDebug() << "port :" << info.portName();
    }

    connect(m_serial_read, &QSerialPort::readyRead, this, &MainWindow::readData);
    connect(ui->bt_write, &QPushButton::clicked, this, &MainWindow::handleBytesWritten);
    connect(ui->bt_write_modbus, &QPushButton::clicked, this, &MainWindow::writeData);

     // 设置一个定时器，每隔一段时间发送数据
     // QTimer::singleShot(2000, this, &MainWindow::handleBytesWritten);


    modbusDevice = new QModbusRtuSerialClient();
 }

MainWindow::~MainWindow()
{
    if(m_serial_read->isOpen()){
        m_serial_read->close();
    }
    if(m_serial_write->isOpen()){
        m_serial_write->close();
    }
    delete ui;
}

void MainWindow::on_bt_connect_clicked()
{

        // const SettingsDialog::Settings p = m_settings->settings();
        m_serial_read->setPortName("ttyV0");
        m_serial_read->setBaudRate(QSerialPort::Baud9600);
        m_serial_read->setDataBits(QSerialPort::Data8);
        m_serial_read->setParity(QSerialPort::NoParity);
        m_serial_read->setStopBits(QSerialPort::OneStop);
        m_serial_read->setFlowControl(QSerialPort::NoFlowControl);
        if (m_serial_read->open(QIODevice::ReadWrite)) {
            ylog.info("Connected to {}", "ttyV0");
        } else {

            ylog.error("Open error");
        }

        // m_serial_write->setPortName("ttyV1");
        // m_serial_write->setBaudRate(QSerialPort::Baud9600);
        // m_serial_write->setDataBits(QSerialPort::Data8);
        // m_serial_write->setParity(QSerialPort::NoParity);
        // m_serial_write->setStopBits(QSerialPort::OneStop);
        // m_serial_write->setFlowControl(QSerialPort::NoFlowControl);
        // if (m_serial_write->open(QIODevice::ReadWrite)) {
        //     ylog.info("Connected to {}", "ttyV1");
        // } else {

        //     ylog.error("Open error");
        // }

        // 创建 Modbus RTU 客户端并将其与串口连接
        // 设置串口参数
        modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter, "/dev/ttyV1");
        modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud9600);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::NoParity);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
        modbusDevice->setTimeout(100);
        modbusDevice->setNumberOfRetries(0);

        // 打开连接
        if (!modbusDevice->connectDevice()) {
            qInfo() << "Connect device failed:" << modbusDevice->errorString();
        }
}

void MainWindow::writeData(qint64 bytes)
{
    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, 0x01, 1);
    writeUnit.setValue(0, 0xABCD);
    if (!modbusDevice->sendWriteRequest(writeUnit, 1)) // 假设从站地址为1
    {
        qDebug() << "Write failed:" << modbusDevice->errorString();
        return;
    }

    // 创建要写入的数据单元
    // QModbusDataUnit writeRequest(QModbusDataUnit::HoldingRegisters, 0x00, 1); // 地址0x5C，1个寄存器

    // 设置要写入的值（例如 0x0002）
    // writeRequest.setValue(0, 0x0001);  // 写入寄存器0的值 0x0002

    // if (!modbusDevice->sendReadRequest(writeRequest, 1)) // 假设从站地址为1
    // {
    //     qDebug() << "Write failed:" << modbusDevice->errorString();
    //     return;
    // }
    ylog.info("write data");

}

void MainWindow::handleBytesWritten(qint64 bytes)
{
    QByteArray data = "Hello, Serial Port ";
    data.append(QByteArray::number(m_num++));
    qint64 bytesWritten = m_serial_write->write(data);
    if (bytesWritten == -1) {
        qDebug() << "Failed to write data to port" << m_serial_write->portName();
    } else {
        qDebug() << "Sent" << bytesWritten << "bytes to port" << m_serial_write->portName();
    }
}

void MainWindow::readData()
{
    if(!m_serial_read->isOpen()){
        ylog.info("m_serial_read is closed;");
        return;
    }
    const QByteArray data = m_serial_read->readAll();
    // const QByteArray data = m_serial_read->readLine();
    ylog.info("read text: {}", data.toStdString());

    // 将data转换为16进制字符串，不带空格
    QByteArray hexData = data.toHex();

    // 为了更好的可读性，在每个字节间添加空格
    QString hexString;
    for (int i = 0; i < hexData.length(); i += 2) {
        if (i > 0) {
            hexString.append(' ');
        }
        hexString.append(hexData.mid(i, 2));
    }

    qDebug() << "Hex Data:" << hexString;
    ui->label_read->setText(hexString);
}


