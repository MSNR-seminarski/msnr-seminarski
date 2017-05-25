#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QEvent>
#include <QDebug>
#include <QPixmap>
#include <QIcon>

#define PORT_NAME "/dev/ttyACM0"
#define BAUD_RATE 9600

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->showMessage("Arduino Status | Connecting...");

    _serialConnection.setPortName(PORT_NAME);
    _serialConnection.setBaudRate(BAUD_RATE);
    _serialConnection.setDataBits(QSerialPort::Data8);
    _serialConnection.setParity(QSerialPort::NoParity);
    _serialConnection.setStopBits(QSerialPort::OneStop);
    _serialConnection.setFlowControl(QSerialPort::NoFlowControl);

    if (!_serialConnection.open(QIODevice::ReadWrite))
    {
        ui->statusBar->showMessage("Arduino Status | Connection Error");
        qDebug() << _serialConnection.errorString();
    }
    else
    {
        ui->statusBar->showMessage("Arduino Status | Connection Established");
    }

    connect(ui->forwardButton, SIGNAL(pressed()), this, SLOT(forward()));
    connect(ui->forwardButton, SIGNAL(released()), this, SLOT(actionButtonReleased()));
    connect(ui->backButton, SIGNAL(pressed()), this, SLOT(back()));
    connect(ui->backButton, SIGNAL(released()), this, SLOT(actionButtonReleased()));
    connect(ui->leftButton, SIGNAL(pressed()), this, SLOT(left()));
    connect(ui->leftButton, SIGNAL(released()), this, SLOT(actionButtonReleased()));
    connect(ui->rightButton, SIGNAL(pressed()), this, SLOT(right()));
    connect(ui->rightButton, SIGNAL(released()), this, SLOT(actionButtonReleased()));
    connect(ui->hornButton, SIGNAL(pressed()), this, SLOT(horn()));
    connect(ui->hornButton, SIGNAL(released()), this, SLOT(hornButtonReleased()));
    connect(ui->alarmButton, SIGNAL(pressed()), this, SLOT(alarm()));
    connect(ui->alarmButton, SIGNAL(released()), this, SLOT(alarmButtonReleased()));
    connect(ui->lightButton, SIGNAL(pressed()), this, SLOT(lights()));
    connect(ui->lightButton, SIGNAL(released()), this, SLOT(lightsButtonReleased()));

    //ui->centralWidget->installEventFilter(this);
    setFocus();
    killFocus(this);

    setArrows(ui->forwardButton, "forward");
    setArrows(ui->leftButton, "left");
    setArrows(ui->rightButton, "right");
    setArrows(ui->backButton, "back");

    QPixmap pix(":/resources/images/horn.png");
    QIcon icon(pix);
    ui->hornButton->setIcon(icon);
    ui->hornButton->setIconSize(QSize(50, 50));

    pix = QPixmap(":/resources/images/light.png");
    icon = QIcon(pix);
    ui->lightButton->setIcon(icon);
    ui->lightButton->setIconSize(QSize(50, 50));

    pix = QPixmap(":/resources/images/padlock.png");
    icon = QIcon(pix);
    ui->alarmButton->setIcon(icon);
    ui->alarmButton->setIconSize(QSize(40, 40));

    QPalette palette = ui->backButton->palette();
    palette.setColor(QPalette::Button, QColor(Qt::white));
    ui->backButton->setPalette(palette);
    ui->backButton->update();
}

void MainWindow::setArrows(QPushButton *button, const QString &direction)
{
    const QString img_path = ":/resources/images/arrow_";
    QPixmap pix(img_path + direction + ".png");
    QIcon icon(pix);
    button->setIcon(icon);
    button->setIconSize(QSize(60, 60));
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

void MainWindow::actionButtonReleased()
{
    char cValue = 5;
    this->write(&cValue);
}

void MainWindow::hornButtonReleased()
{
    char cValue = 11;
    this->write(&cValue);
}

void MainWindow::alarmButtonReleased()
{
    char cValue = 12;
    this->write(&cValue);
}

void MainWindow::lightsButtonReleased()
{
    char cValue = 13;
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
    case Qt::Key_L:
        lights();
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
        actionButtonReleased();
        return;
    case Qt::Key_H:
        hornButtonReleased();
        return;
    case Qt::Key_Q:
        alarmButtonReleased();
        return;
    case Qt::Key_L:
        lightsButtonReleased();
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
