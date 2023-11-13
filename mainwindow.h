//
// Created by andrii on 11/1/23.
//

#ifndef TIMER_MAINWINDOW_H
#define TIMER_MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QTimer>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:
    QPushButton *btn;
    QLabel *lbl;
    QVBoxLayout *vbox;
    QTimer *timer;
    bool isTimerRunning;
    int remainingTime;

private slots:
    void toggleTimer();
    void timerSlot();
};


#endif //TIMER_MAINWINDOW_H
