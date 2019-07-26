//Created by
//Marcin Chrostowski
//Paweł Ostaszewski

#include "Pedestrian.h"
#include <sstream>
#include <QTime>
#include <cmath>

Pedestrian::Pedestrian(const QPointF& scenePosition, const Direction& direction, const QPixmap& pixmap) :
    RoadUser(scenePosition, direction, pixmap, SPEED_PEDESTRIAN)
{
    id = roadUserId;
    roadUserId++;
}

std::string Pedestrian::getData()
{
    std::ostringstream oss;
    oss << "pedestrian;id=" << id << ";x" << x() << ";y=" << y();
    return oss.str();
}


void Pedestrian::choseNextDirection()
{
    QTime timeSeed = QTime::currentTime();
    qsrand((uint)timeSeed.msec());

    switch(qrand() % 4)
    {
    case 0:
        direction = Direction::DOWN;
        break;
    case 1:
        direction = Direction::UP;
        break;
    case 2:
        direction = Direction::RIGHT;
        break;
    case 3:
        direction = Direction::LEFT;
        break;
    }
}

void Pedestrian::move(Direction direction)
{
    this->moving = true;
    this->currentDistance = QPointF(0, 0);
    this->setPixmapDirection(direction);
    this->direction = direction;

    switch(direction)
    {
    case Direction::DOWN:
        distance = QPoint(0, FIELD_HEIGHT);
        break;
    case Direction::UP:
        distance = QPoint(0, -FIELD_HEIGHT);
        break;
    case Direction::RIGHT:
        distance = QPoint(FIELD_WIDTH, 0);
        break;
    case Direction::LEFT:
        distance = QPoint(-FIELD_WIDTH, 0);
        break;
    case Direction::NONE:
        return;
    }
}

void Pedestrian::advance(int phase)
{
    if(!moving)
        return;

    if(direction == Direction::NONE)
        return;

    QPointF difference = distance - currentDistance;   
    if(difference.x() > 0)
    {
        moveBy(speed, 0);
        currentDistance.setX(currentDistance.x() + speed);
    }
    if(difference.x() < 0)
    {
        moveBy(-speed, 0);
        currentDistance.setX(currentDistance.x() - speed);
    }
    if(difference.y() > 0)
    {
        moveBy(0, speed);
        currentDistance.setY(currentDistance.y() + speed);
    }
    if(difference.y() < 0)
    {
        moveBy(0, -speed);
        currentDistance.setY(currentDistance.y() - speed);
    }

    if(currentDistance == distance)
        moving = false;
}
