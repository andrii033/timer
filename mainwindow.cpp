// mainwindow.cpp

#include "mainwindow.h"
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent), isTimerRunning(false), remainingTime(65) {
    vbox = new QVBoxLayout();
    btn = new QPushButton("Start");
    lbl = new QLabel(QString::number(0));
    timeEdit=new QTimeEdit();
    timeEdit->setDisplayFormat("hh:mm:ss");
    dialog = new QDialog(nullptr,
                         Qt::Dialog | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);

    // Create the timer and set its interval before starting it
    timer = new QTimer(this);
    timer->setInterval(1000);
    //timer->start();

    vbox->addWidget(timeEdit);
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
    delete vbox;
    delete btn;
    delete lbl;
    delete dialog;
    delete timer;
    delete timeEdit;
}

void MainWindow::toggleTimer() {
    if (isTimerRunning) {
        qDebug() << "timer stop";
        timer->stop();
        btn->setText("Start");
    } else {
        qDebug() << "timer start";
        QTime selectedTime = timeEdit->time();
        remainingTime = QTime(0, 0).secsTo(selectedTime);
        qDebug()<<remainingTime;
        timer->start();
        btn->setText("Stop");
    }
    isTimerRunning = !isTimerRunning;
}

void MainWindow::timerSlot() {
    remainingTime--;
    if (remainingTime<0)
        remainingTime=0;
    if (remainingTime < 60) {
        lbl->setText(QString::number(remainingTime) + " sec");
    } else if (remainingTime < 3600) {
        lbl->setText(QString::number(remainingTime / 60) + " min " + QString::number(remainingTime % 60) + " sec");
    } else {
        lbl->setText(QString::number(remainingTime / 3600) + " hour " +
                     QString::number((remainingTime % 3600) / 60) + " min " +
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
