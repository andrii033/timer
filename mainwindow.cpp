// mainwindow.cpp

#include "mainwindow.h"
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent), isTimerRunning(false) {
    qDebug() << "constructor";
    vbox = new QVBoxLayout();
    btn = new QPushButton("Start");
    lbl = new QLabel("timer");

    // Create the timer and set its interval before starting it
    timer = new QTimer(this);
    timer->setInterval(1000);
    timer->start();

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
        timer->setInterval(1000);
        timer->start();
        btn->setText("Stop");
    }
    isTimerRunning = !isTimerRunning;
}

void MainWindow::timerSlot() {
    qDebug() << "time out";
    timer->stop();
}
