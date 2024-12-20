#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QSerialPort"
#include "QSerialPortInfo"
#include <QtSerialBus/qmodbusrtuserialclient.h>
#include <QModbusDataUnit>
#include <QSerialPort>
#include <QSerialPortInfo>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_bt_connect_clicked();
    void writeData(qint64 bytes);
    void handleBytesWritten(qint64 bytes);
    void readData();

private:
    Ui::MainWindow *ui;
    QSerialPort *m_serial_read;
    QSerialPort *m_serial_write;
    QModbusRtuSerialClient *modbusDevice;
    int m_num;
};
#endif // MAINWINDOW_H
