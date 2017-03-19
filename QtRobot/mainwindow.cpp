#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#define PORT_NAME "/dev/pts/17"
#define BAUD_RATE 9600

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _serialConnection.setPortName(PORT_NAME);
    _serialConnection.setBaudRate(BAUD_RATE);
    _serialConnection.setDataBits(QSerialPort::Data8);
    _serialConnection.setParity(QSerialPort::NoParity);
    _serialConnection.setStopBits(QSerialPort::OneStop);
    _serialConnection.setFlowControl(QSerialPort::NoFlowControl);

    if (_serialConnection.open(QIODevice::ReadWrite))
    {
        if (_serialConnection.isOpen())
        {
            if (_serialConnection.isWritable())
            {
                _serialConnection.write("blabla");
            }
        }
    }
    else
    {
        qDebug() << _serialConnection.errorString();
    }
}

MainWindow::~MainWindow()
{
    _serialConnection.close();
    delete ui;
}
