//Created by
//Marcin Chrostowski
//Paweł Ostaszewski

#include "Camera.h"
#include "RoadUser.h"
#include "Pedestrian.h"
#include "Car.h"
#include "Constants.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <QDateTime>

unsigned int Camera::currentCamerasId = 0;

Camera::Camera(const QPointF& scenePosition, const Direction& direction, const QPixmap& pixmap, double angle_) :
    StreetElement(scenePosition, direction, pixmap), time(QDateTime::currentDateTime()), id(++currentCamerasId), angle(angle_)
{
    setObservationField();
}

Camera::Camera(const Camera& camera) :
    StreetElement(camera.pos(), camera.getDirection(), camera.pixmap()), time(QDateTime::currentDateTime()), id(++currentCamerasId), angle(camera.getAngle()),
    rightCorner(camera.rightCorner), leftCorner(camera.leftCorner), aRight(camera.aRight), aLeft(camera.aLeft), bRight(camera.bRight), bLeft(camera.bLeft)
{

}

void Camera::setObservationField()
{
    double side = tan(PI * CAMERA_ANGLE / 180) * VIEW_DISTANCE;

    //Observation field is a triangle. Setting parameters for points which aren't camera position.
    //Left and right point are assigned according to camera direction.
    if(direction == Direction::UP)
    {
        leftCorner.setY(static_cast<qreal>(static_cast<double>(y()) - VIEW_DISTANCE));
        rightCorner.setY(static_cast<qreal>(static_cast<double>(y()) - VIEW_DISTANCE));
        leftCorner.setX(static_cast<qreal>(static_cast<double>(x()) - side));
        rightCorner.setX(static_cast<qreal>(static_cast<double>(x()) + side));
    }
    else if(direction == Direction::DOWN){
        leftCorner.setY(static_cast<qreal>(static_cast<double>(y()) + VIEW_DISTANCE));
        rightCorner.setY(static_cast<qreal>(static_cast<double>(y()) + VIEW_DISTANCE));
        leftCorner.setX(static_cast<qreal>(static_cast<double>(x()) + side));
        rightCorner.setX(static_cast<qreal>(static_cast<double>(x()) - side));
    }
    else if(direction == Direction::LEFT)
    {
        leftCorner.setX(static_cast<qreal>(static_cast<double>(x()) - VIEW_DISTANCE));
        rightCorner.setX(static_cast<qreal>(static_cast<double>(x()) - VIEW_DISTANCE));
        leftCorner.setY(static_cast<qreal>(static_cast<double>(y()) + side));
        rightCorner.setY(static_cast<qreal>(static_cast<double>(y()) - side));
    }
    else if(direction == Direction::RIGHT)
    {
        leftCorner.setX(static_cast<qreal>(static_cast<double>(x()) + VIEW_DISTANCE));
        rightCorner.setX(static_cast<qreal>(static_cast<double>(x()) + VIEW_DISTANCE));
        leftCorner.setY(static_cast<qreal>(static_cast<double>(y()) - side));
        rightCorner.setY(static_cast<qreal>(static_cast<double>(y()) + side));
    }

    //Calculating a and b for two straight lines. Each cross camera position and left or right point
    aLeft = (y() - leftCorner.y()) / (x() - leftCorner.x());
    aRight = (y() - rightCorner.y()) / (x() - rightCorner.x());
    bLeft = y() - aLeft * x();
    bRight = y() - aRight * x();
}

void Camera::observe(std::vector<Pedestrian *> pedestrians, std::vector<Car *> cars, QTime& observaionTime)
{
    std::ofstream file;
    file.open("kamery.txt", std::ios_base::app);
    foreach (Pedestrian* pedestrian, pedestrians) {
        if(isRoadUserInRange(pedestrian))
        {
            file << this->getData() << ";" << pedestrian->getData() << ";time=" << observaionTime.toString(QString::fromStdString("hh:mm:ss")).toStdString() << "\n";
            //file << "TEST\n";
        }
    }
    foreach (Car* car, cars) {
        if(isRoadUserInRange(car))
        {
            file << this->getData() << ";" << car->getData() << ";time=" << observaionTime.toString(QString::fromStdString("hh:mm:ss")).toStdString() << "\n";
        }
    }
    file.close();
}

QString Camera::observeToTextField(std::vector<Pedestrian *> pedestrians, std::vector<Car *> cars, QTime& observaionTime)
{
    QString observation;
    foreach (Pedestrian* pedestrian, pedestrians) {
        if(isRoadUserInRange(pedestrian))
        {
            observation = observation + QString::fromStdString(this->getData()) + ";" + QString::fromStdString(pedestrian->getData()) + +  ";time=" + observaionTime.toString(QString::fromStdString("hh:mm:ss")) + "\n";
            //file << "TEST\n";
        }
    }
    foreach (Car* car, cars) {
        if(isRoadUserInRange(car))
        {
            observation = observation + QString::fromStdString(this->getData()) + ";" + QString::fromStdString(car->getData()) + ";time=" + observaionTime.toString(QString::fromStdString("hh:mm:ss")) + "\n";
        }
    }
    return observation;
}

bool Camera::isRoadUserInRange(RoadUser* roadUser)
{
    if(direction == Direction::UP)
    {
        if(roadUser->y() <= y() && roadUser->y() >= leftCorner.y() &&
                roadUser->x() >= (roadUser->y() - bLeft) / aLeft &&
                roadUser->x() <= (roadUser->y() - bRight) / aRight){
            return true;
        }
        else return false;
    }
    else if(direction == Direction::DOWN){
        if(roadUser->y() >= y() && roadUser->y() <= leftCorner.y() &&
                roadUser->x() <= (roadUser->y() - bLeft) / aLeft &&
                roadUser->x() >= (roadUser->y() - bRight) / aRight)
        {
            return true;
        }
        else return false;
    }
    else if(direction == Direction::LEFT)
    {
        if(roadUser->x() <= x() && roadUser->x() >= leftCorner.x() &&
                roadUser->y() <= (aLeft * roadUser->x() + bLeft) &&
                roadUser->y() >= (aRight * roadUser->x() + bRight))
        {
            return true;
        }
        else return false;
    }
    else if(direction == Direction::RIGHT)
    {
        if(roadUser->y() >=x() && roadUser->x() <= leftCorner.y() &&
                roadUser->y() >= (aLeft * roadUser->x() + bLeft) &&
                roadUser->y() <= (aRight * roadUser->x() + bRight))
        {
            return true;
        }
        else return false;
    }
    return false;
}

int Camera::getID() const
{
    return this->id;
}

std::string Camera::getData()
{
    std::ostringstream oss;
    oss << "camera" << ";id=" << id;
    return oss.str();
}

double Camera::getAngle() const
{
    return this->angle;
}

void Camera::advance(int phase)
{

}

StreetElement* Camera::clone()
{
    return new Camera(*this);
}
