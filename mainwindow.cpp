// mainwindow.cpp

#include "mainwindow.h"
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent), isTimerRunning(false),remainingTime(5) {
    vbox = new QVBoxLayout();
    btn = new QPushButton("Start");
    lbl = new QLabel(QString::number(remainingTime));

    // Create the timer and set its interval before starting it
    timer = new QTimer(this);
    timer->setInterval(1000);
    //timer->start();

    vbox->addWidget(lbl);
    vbox->addWidget(btn);
    setLayout(vbox);

    connect(timer, &QTimer::timeout, this, &MainWindow::timerSlot);
    connect(btn, &QPushButton::clicked, this, &MainWindow::toggleTimer);
}

MainWindow::~MainWindow() {
}

void MainWindow::toggleTimer() {
    if (isTimerRunning) {
        qDebug() << "timer stop";
        timer->stop();
        btn->setText("Start");
    } else {
        qDebug() << "timer start";
        timer->start();
        btn->setText("Stop");
    }
    isTimerRunning = !isTimerRunning;
}

void MainWindow::timerSlot() {
    remainingTime--;
    lbl->setText(QString::number(remainingTime));

    if (remainingTime <= 0) {
        // Timer has reached 0, stop the timer
        timer->stop();
        isTimerRunning = false;
        btn->setText("Start");
        qDebug()<<"time out";
    }
}
