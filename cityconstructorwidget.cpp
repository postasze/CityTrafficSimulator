//Created by
//Marcin Chrostowski
//Paweł Ostaszewski

#include "cityconstructorwidget.h"
#include <QtWidgets>
#include <iostream>

CityConstructorWidget::CityConstructorWidget(QWidget *parent) : QWidget(parent)
{
    setAcceptDrops(true);

    cityConstructorView.setParent(this);
    cityConstructorScene.setParent(&cityConstructorView);
    cityConstructorView.setScene(&cityConstructorScene);
    cityConstructorView.setFixedSize(180, 1000);
    cityConstructorScene.setSceneRect(0, 0, 180, 1000);
    cityConstructorView.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    cityConstructorView.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    cityConstructorView.setStyleSheet("background: transparent");

    loadImages();
    setStreetElements();
    addStreetElementsToScene();
}

void CityConstructorWidget::loadImages()
{
    cameraPixmap.load(":/images/cameras/camera.png");
    greenLightPixmap.load(":/images/traffic_lights/green_light.png");
    orangeLightPixmap.load(":/images/traffic_lights/orange_light.png");
    redLightPixmap.load(":/images/traffic_lights/red_light.png");
    CrossingPixmap.load(":/images/streets/gray_crossing_street.png");
    DivisionStreetPixmap.load(":/images/streets/gray_division_street.png");
    StraightStreetPixmap.load(":/images/streets/gray_straight_street.png");
    TurnStreetPixmap.load(":/images/streets/gray_turn_street.png");
    PedestrianCrossingPixmap.load(":/images/streets/pedestrian_crossing.png");
    PavementPixmap.load(":/images/streets/pavement.png");
}

void CityConstructorWidget::setStreetElements()
{
    pavement.setPixmap(PavementPixmap);
    straightStreet.setPixmap(StraightStreetPixmap);
    turnStreet.setPixmap(TurnStreetPixmap);
    divisionStreet.setPixmap(DivisionStreetPixmap);
    crossingStreet.setPixmap(CrossingPixmap);
    pedestrianCrossing.setPixmap(PedestrianCrossingPixmap);
    trafficLight.setPixmap(greenLightPixmap);
    camera.setPixmap(cameraPixmap);

    pavement.setScale(1.25);
    straightStreet.setScale(0.7);
    turnStreet.setScale(0.7);
    divisionStreet.setScale(0.7);
    crossingStreet.setScale(0.7);
    camera.setScale(0.25);

    pavement.setPos(50, 20);
    straightStreet.setPos(50, 120);
    turnStreet.setPos(50, 220);
    divisionStreet.setPos(50, 320);
    crossingStreet.setPos(50, 420);
    pedestrianCrossing.setPos(75, 520);
    trafficLight.setPos(75, 650);
    camera.setPos(40, 750);
}

void CityConstructorWidget::addStreetElementsToScene()
{
    cityConstructorScene.addItem(&pavement);
    cityConstructorScene.addItem(&straightStreet);
    cityConstructorScene.addItem(&turnStreet);
    cityConstructorScene.addItem(&divisionStreet);
    cityConstructorScene.addItem(&crossingStreet);
    cityConstructorScene.addItem(&pedestrianCrossing);
    cityConstructorScene.addItem(&trafficLight);
    cityConstructorScene.addItem(&camera);
}

void CityConstructorWidget::dragEnterEvent(QDragEnterEvent *event)
{
    //std::cout << "dragEnter" << std::endl;
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void CityConstructorWidget::dragMoveEvent(QDragMoveEvent *event)
{
    //std::cout << "dragMove" << std::endl;
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void CityConstructorWidget::dropEvent(QDropEvent *event)
{
    //std::cout << "drop" << std::endl;
    event->ignore();
}

void CityConstructorWidget::mousePressEvent(QMouseEvent *event)
{
    //std::cout << "mousePress" << std::endl;

    StreetElement *streetElement = dynamic_cast<StreetElement*>(cityConstructorScene.itemAt(event->pos(), QTransform()));
    if (!streetElement)
        return;

    if (event->button() == Qt::LeftButton)
    {
        QPixmap pixmap;

        emit streetElementSelected(streetElement);

        if (streetElement == &pavement || streetElement == &straightStreet ||
            streetElement == &turnStreet || streetElement == &divisionStreet ||
            streetElement == &crossingStreet || streetElement == &pedestrianCrossing)
            pixmap = streetElement->pixmap().scaledToHeight(SCALE_OF_BASIC_ELEMENT * streetElement->pixmap().height());
        else if(streetElement == &trafficLight)
            pixmap = streetElement->pixmap().scaledToHeight(SCALE_OF_TRAFFIC_LIGHT * streetElement->pixmap().height());
        else if(streetElement == &camera)
            pixmap = streetElement->pixmap().scaledToHeight(SCALE_OF_CAMERA * streetElement->pixmap().height());

        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);

        dataStream << pixmap;

        QMimeData *mimeData = new QMimeData;
        mimeData->setData("application/x-dnditemdata", itemData);

        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->setPixmap(pixmap);
        drag->setHotSpot(QPoint(0.5 * pixmap.width(), 0.5 * pixmap.height()));

        drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction);
    }
    else if(event->button() == Qt::RightButton)
    {
        QTransform transform;
        transform = transform.rotate(90);
        streetElement->setPixmap(QPixmap(streetElement->pixmap().transformed(transform)));
        streetElement->setDirection((Direction)((streetElement->getDirection() + 1) % 4));
    }
}

void CityConstructorWidget::mouseReleaseEvent(QMouseEvent *event)
{
    //std::cout << "mouseReleaseEvent" << std::endl;
    event->ignore();
}

void CityConstructorWidget::mouseMoveEvent(QMouseEvent *event)
{
    //std::cout << "mouseMoveEvent" << std::endl;
    event->ignore();
}
