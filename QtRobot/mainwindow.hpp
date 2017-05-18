#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QDebug>
#include <QString>
#include <QPushButton>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSerialPort _serialConnection;

    void write(const char *str);
    void killFocus(QWidget *w);
    void setArrows(QPushButton *button, const QString &direction);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void forward();
    void back();
    void left();
    void right();
    void horn();
    void alarm();
    void lights();
    void buttonReleased();


};

#endif // MAINWINDOW_H
