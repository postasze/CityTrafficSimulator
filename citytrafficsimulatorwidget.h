//Created by
//Marcin Chrostowski
//Paweł Ostaszewski

#ifndef CITYTRAFFICSIMULATORWIDGET_H
#define CITYTRAFFICSIMULATORWIDGET_H

#include <QWidget>
#include "Constants.h"
#include <QGraphicsLineItem>
#include "ExtendedGraphicsView.h"
//#include "Controller.h"
#include "StreetElement.h"
#include "TrafficLight.h"
#include "Camera.h"
#include "Car.h"
#include "Pedestrian.h"

class CityTrafficSimulatorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CityTrafficSimulatorWidget(QWidget *parent = nullptr);
    ~CityTrafficSimulatorWidget();

    QGraphicsScene cityTrafficSimulatorScene;

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void streetElementDropped(QPixmap pixmap, QPoint eventPosition);
    void leftMouseButtonPressed(QPoint eventPosition);
    void rightMouseButtonPressed(QPoint eventPosition);

public slots:

private:

    //Controller *controller;
    ExtendedGraphicsView cityTrafficSimulatorView;
};

#endif // CITYTRAFFICSIMULATORWIDGET_H
