#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QEvent>
#include <QDebug>

#define PORT_NAME "/dev/ttyACM0"
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
    connect(ui->hornButton, SIGNAL(pressed()), this, SLOT(horn()));
    connect(ui->hornButton, SIGNAL(released()), this, SLOT(buttonReleased()));
    connect(ui->alarmButton, SIGNAL(pressed()), this, SLOT(alarm()));
    connect(ui->alarmButton, SIGNAL(released()), this, SLOT(buttonReleased()));
    connect(ui->lightButton, SIGNAL(pressed()), this, SLOT(lights()));
    connect(ui->lightButton, SIGNAL(released()), this, SLOT(buttonReleased()));

    //ui->centralWidget->installEventFilter(this);
    setFocus();
    killFocus(this);
}

void MainWindow::killFocus(QWidget *w)
{
    for (auto child : w->children()) {
        auto tmp = dynamic_cast<QWidget*>(child);
        if (tmp != NULL) {
            tmp->setFocusPolicy(Qt::NoFocus);
            if (child->children().length() != 0)
                killFocus(tmp);
        }
    }
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
    char cValue = 5;
    this->write(&cValue);
}

void MainWindow::forward()
{
    char cValue = 3;
    this->write(&cValue);
}
void MainWindow::back()
{
    char cValue = 4;
    this->write(&cValue);
}
void MainWindow::left()
{
    char cValue = 1;
    this->write(&cValue);
}
void MainWindow::right()
{
    char cValue = 2;
    this->write(&cValue);
}
void MainWindow::horn()
{
    char cValue = 6;
    this->write(&cValue);
}
void MainWindow::alarm()
{
    char cValue = 7;
    this->write(&cValue);
}
void MainWindow::lights()
{
    char cValue = 8;
    this->write(&cValue);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
        return;
    switch (event->key()) {
    case Qt::Key_Up:
    case Qt::Key_W:
        forward();
        return;
    case Qt::Key_Down:
    case Qt::Key_S:
        back();
        return;
    case Qt::Key_Left:
    case Qt::Key_A:
        left();
        return;
    case Qt::Key_Right:
    case Qt::Key_D:
        right();
        return;
    case Qt::Key_H:
        horn();
        return;
    case Qt::Key_Q:
        alarm();
        return;
    default:
        QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
        return;
    switch (event->key()) {
    case Qt::Key_Up:
    case Qt::Key_W:
    case Qt::Key_Down:
    case Qt::Key_S:
    case Qt::Key_Left:
    case Qt::Key_A:
    case Qt::Key_Right:
    case Qt::Key_D:
    case Qt::Key_H:
    case Qt::Key_Q:
        buttonReleased();
        return;
    default:
        QMainWindow::keyReleaseEvent(event);
    }
}

MainWindow::~MainWindow()
{
    _serialConnection.close();
    delete ui;
}
