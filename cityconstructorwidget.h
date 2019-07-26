//Created by
//Marcin Chrostowski
//Paweł Ostaszewski

#ifndef CITYCONSTRUCTORWIDGET_H
#define CITYCONSTRUCTORWIDGET_H

#include <QWidget>
#include "ExtendedGraphicsView.h"
#include "Constants.h"
#include "Pavement.h"
#include "StraightStreet.h"
#include "TurnStreet.h"
#include "DivisionStreet.h"
#include "CrossingStreet.h"
#include "PedestrianCrossing.h"
#include "TrafficLight.h"
#include "Camera.h"

class CityConstructorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CityConstructorWidget(QWidget *parent = nullptr);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

signals:
    void streetElementSelected(StreetElement*);

public slots:

private:
    void loadImages();
    void setStreetElements();
    void addStreetElementsToScene();

    ExtendedGraphicsView cityConstructorView;
    QGraphicsScene cityConstructorScene;

    QPixmap cameraPixmap;
    QPixmap greenLightPixmap;
    QPixmap orangeLightPixmap;
    QPixmap redLightPixmap;
    QPixmap CrossingPixmap;
    QPixmap DivisionStreetPixmap;
    QPixmap StraightStreetPixmap;
    QPixmap TurnStreetPixmap;
    QPixmap PedestrianCrossingPixmap;
    QPixmap PavementPixmap;

    Pavement pavement;
    StraightStreet straightStreet;
    TurnStreet turnStreet;
    DivisionStreet divisionStreet;
    CrossingStreet crossingStreet;
    PedestrianCrossing pedestrianCrossing;
    TrafficLight trafficLight;
    Camera camera;
};

#endif // CITYCONSTRUCTORWIDGET_H
