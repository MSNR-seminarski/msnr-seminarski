#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QEvent>
#include <QDebug>

#define PORT_NAME "/dev/pts/5"
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
    connect(ui->lightButton, SIGNAL(pressed()), this, SLOT(light()));
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
void MainWindow::horn()
{
    this->write("horn");
}
void MainWindow::light()
{
    this->write("light");
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
    case Qt::Key_L:
        light();
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
    case Qt::Key_L:
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
