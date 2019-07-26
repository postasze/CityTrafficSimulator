//Created by
//Marcin Chrostowski
//Paweł Ostaszewski

#include "MainWindow.h"
#include "ui_mainwindow.h"
#include <QPen>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Symulator ruchu miejskiego");

    ui->vehiclesStartPointPushButton->setCheckable(true);
    ui->vehiclesEndPointPushButton->setCheckable(true);
    ui->pedestrianStartPointPushButton->setCheckable(true);
    ui->pedestrianEndPointPushButton->setCheckable(true);

    ui->simulationSpeedComboBox->addItem(QString("0.5x"));
    ui->simulationSpeedComboBox->addItem(QString("1x"));
    ui->simulationSpeedComboBox->addItem(QString("2x"));
    ui->simulationSpeedComboBox->addItem(QString("4x"));
    ui->simulationSpeedComboBox->addItem(QString("5x"));

    ui->simulationSpeedComboBox->setCurrentIndex(1);

    ui->carNumberLineEdit->setValidator(new QIntValidator(0, 100, this));
    ui->pedestrianNumberLineEdit->setValidator(new QIntValidator(0, 100, this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::vehiclesStartPointPushButtonClicked()
{
    if(ui->vehiclesStartPointPushButton->isChecked())
    {
        ui->vehiclesStartPointPushButton->setChecked(true);
        ui->vehiclesEndPointPushButton->setChecked(false);
        ui->pedestrianStartPointPushButton->setChecked(false);
        ui->pedestrianEndPointPushButton->setChecked(false);
        emit currentPointTypeChanged(PointType::VEHICLE_START_POINT);
    }
    else
        emit currentPointTypeChanged(PointType::NONE);
}

void MainWindow::vehiclesEndPointPushButtonClicked()
{
    if(ui->vehiclesEndPointPushButton->isChecked())
    {
        ui->vehiclesStartPointPushButton->setChecked(false);
        ui->vehiclesEndPointPushButton->setChecked(true);
        ui->pedestrianStartPointPushButton->setChecked(false);
        ui->pedestrianEndPointPushButton->setChecked(false);
        emit currentPointTypeChanged(PointType::VEHICLE_END_POINT);
    }
    else
        emit currentPointTypeChanged(PointType::NONE);
}

void MainWindow::pedestrianStartPointPushButtonClicked()
{
    if(ui->pedestrianStartPointPushButton->isChecked())
    {
        ui->vehiclesStartPointPushButton->setChecked(false);
        ui->vehiclesEndPointPushButton->setChecked(false);
        ui->pedestrianStartPointPushButton->setChecked(true);
        ui->pedestrianEndPointPushButton->setChecked(false);
        emit currentPointTypeChanged(PointType::PEDESTRIAN_START_POINT);
    }
    else
        emit currentPointTypeChanged(PointType::NONE);
}

void MainWindow::pedestrianEndPointPushButtonClicked()
{
    if(ui->pedestrianEndPointPushButton->isChecked())
    {
        ui->vehiclesStartPointPushButton->setChecked(false);
        ui->vehiclesEndPointPushButton->setChecked(false);
        ui->pedestrianStartPointPushButton->setChecked(false);
        ui->pedestrianEndPointPushButton->setChecked(true);
        emit currentPointTypeChanged(PointType::PEDESTRIAN_END_POINT);
    }
    else
        emit currentPointTypeChanged(PointType::NONE);
}

void MainWindow::updateLCDClock(QTime clockTime)
{
    ui->hoursLCDDisplay->display(clockTime.hour());
    ui->minutesLCDDisplay->display(clockTime.minute());
    ui->secondsLCDDisplay->display(clockTime.second());
}

void MainWindow::setCameraObservationTextEdit(QString observation)
{
    ui->cameraObservationTextEdit->setText(ui->cameraObservationTextEdit->toPlainText() + observation);
}

void MainWindow::clearCameraObservationTextEdit()
{
    ui->cameraObservationTextEdit->setText("");
}

