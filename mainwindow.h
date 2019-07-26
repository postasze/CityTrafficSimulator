//Created by
//Marcin Chrostowski
//Paweł Ostaszewski

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "Constants.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow *ui;

    void updateLCDClock(QTime clockTime);
    void clearCameraObservationTextEdit();
    void setCameraObservationTextEdit(QString observation);

signals:
    void currentPointTypeChanged(PointType);

public slots:
    void vehiclesStartPointPushButtonClicked();
    void vehiclesEndPointPushButtonClicked();
    void pedestrianStartPointPushButtonClicked();
    void pedestrianEndPointPushButtonClicked();

private:

};

#endif // MAINWINDOW_H
