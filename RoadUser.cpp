//Created by
//Marcin Chrostowski
//Paweł Ostaszewski

#include "RoadUser.h"
#include <iostream>

RoadUser::RoadUser(const QPointF& scenePosition, const Direction& direction, const QPixmap& pixmap, qreal speed_, bool moving, QPointF distance) :
    CityObject(scenePosition, direction, pixmap), speed(speed_), moving(moving), distance(distance)
{

}

RoadUser::~RoadUser()
{

}

qreal RoadUser::getSpeed()
{
    return speed;
}

bool RoadUser::isMoving()
{
    return moving;
}

void RoadUser::setMoving(bool moving)
{
    this->moving = moving;
}

void RoadUser::setPixmapDirection(Direction direction)
{
    QTransform transform;

    if(this->direction == Direction::NONE)
        this->direction = Direction::UP;

    if(direction == Direction::NONE)
        direction = Direction::UP;

    int difference = direction - this->direction;

    transform = transform.rotate(difference * 90);
    this->setPixmap(QPixmap(this->pixmap().transformed(transform)));
}

unsigned int RoadUser::roadUserId = 0;
