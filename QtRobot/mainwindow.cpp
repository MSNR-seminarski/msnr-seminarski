#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#define PORT_NAME "/dev/pts/4"
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

    if (!_serialConnection.open(QIODevice::ReadWrite))
    {
        qDebug() << _serialConnection.errorString();
    }

    connect(ui->forwardButton, SIGNAL(pressed()), this, SLOT(forward()));
    connect(ui->forwardButton, SIGNAL(released()), this, SLOT(buttonReleased()));
    connect(ui->backButton, SIGNAL(pressed()), this, SLOT(back()));
    connect(ui->backButton, SIGNAL(released()), this, SLOT(buttonReleased()));
    connect(ui->leftButton, SIGNAL(pressed()), this, SLOT(left()));
    connect(ui->leftButton, SIGNAL(released()), this, SLOT(buttonReleased()));
    connect(ui->rightButton, SIGNAL(pressed()), this, SLOT(right()));
    connect(ui->rightButton, SIGNAL(released()), this, SLOT(buttonReleased()));
}

void MainWindow::write(const char *str)
{
    if (_serialConnection.isOpen())
    {
        if (_serialConnection.isWritable())
        {
            _serialConnection.write(str);
        }
    }
}
void MainWindow::buttonReleased()
{
    this->write("stop");
}

void MainWindow::forward()
{
    this->write("forward");
}
void MainWindow::back()
{
    this->write("back");
}
void MainWindow::left()
{
    this->write("left");
}
void MainWindow::right()
{
    this->write("right");
}

MainWindow::~MainWindow()
{
    _serialConnection.close();
    delete ui;
}
