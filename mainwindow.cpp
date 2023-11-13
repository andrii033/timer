// mainwindow.cpp

#include "mainwindow.h"
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent), isTimerRunning(false), remainingTime(5) {
    vbox = new QVBoxLayout();
    btn = new QPushButton("Start");
    lbl = new QLabel(QString::number(remainingTime));
    dialog = new QDialog(nullptr,
                         Qt::Dialog | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);

    // Create the timer and set its interval before starting it
    timer = new QTimer(this);
    timer->setInterval(1000);
    //timer->start();

    vbox->addWidget(lbl);
    vbox->addWidget(btn);
    setLayout(vbox);

    // Dialog setup
    QLabel *dialogLabel = new QLabel("Time's up! ", dialog);
    QVBoxLayout *dialogLayout = new QVBoxLayout(dialog);
    dialogLayout->addWidget(dialogLabel);

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
    if (remainingTime < 60) {
        lbl->setText(QString::number(remainingTime) + " sec");
    } else if (remainingTime < 3600) {
        lbl->setText(QString::number(remainingTime / 60) + " min " + QString::number(remainingTime % 60) + " sec");
    } else {
        lbl->setText(QString::number(remainingTime / 3600) + " hour " + QString::number(remainingTime / 60) + " min " +
                     QString::number(remainingTime % 60) + " sec");
    }


    if (remainingTime <= 0) {
        // Timer has reached 0, stop the timer
        timer->stop();
        isTimerRunning = false;
        btn->setText("Start");
        dialog->show();
    }
}
