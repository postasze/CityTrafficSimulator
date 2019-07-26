//Created by
//Marcin Chrostowski
//Paweł Ostaszewski

#include "Car.h"
#include <QTime>
#include <cmath>
#include <iostream>
#include <sstream>

Car::Car(const QPointF& scenePosition, const Direction& direction, const QPixmap& pixmap, CarType carType_) :
    RoadUser(scenePosition, Direction::NONE, pixmap), carType(carType_), chosenPixmap(pixmap)
{
    id = roadUserId;
    roadUserId++;

    switch(carType)
    {
    case CarType::AUTOMOBILE:
        speed = SPEED_AUTOMOBILE;
        size = SIZE_AUTOMOBILE;
        break;
    case CarType::TRUCK:
        speed = SPEED_TRUCK;
        size = SIZE_TRUCK;
        break;
    }

    this->setPixmapDirection(direction);
    this->setDirection(direction);
}

int Car::getSize()
{
    return size;
}

std::string Car::getCarTypeName()
{
    if(carType == CarType::AUTOMOBILE)
    {
        return "automobile";
    }
    else if(carType == CarType::TRUCK)
    {
        return "truck";
    }
    else
    {
        return "UNKNOWN";
    }
}

std::string Car::getData()
{
    std::ostringstream oss;
    oss << "vehicle;type=" << getCarTypeName() << ";id=" << id << ";x=" << x() << ";y=" << y();
    return oss.str();
}


void Car::choseNextDirection()
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

void Car::move(Direction direction)
{

}

void Car::moveStraight()
{
    moving = true;
    currentDistance = QPointF(0, 0);

    switch(direction)
    {
    case Direction::DOWN:
        distance = QPointF(0, 2*FIELD_HEIGHT);
        break;
    case Direction::UP:
        distance = QPointF(0, -2*FIELD_HEIGHT);
        break;
    case Direction::RIGHT:
        distance = QPointF(2*FIELD_WIDTH, 0);
        break;
    case Direction::LEFT:
        distance = QPointF(-2*FIELD_WIDTH, 0);
        break;
    case Direction::NONE:
        return;
    }

    rotateLeft = false;
    rotateRight = false;
}

void Car::turnLeft()
{
    moving = true;
    currentDistance = QPointF(0, 0);

    switch(direction)
    {
    case Direction::UP:
        distance = QPointF(-2*FIELD_WIDTH, -FIELD_HEIGHT);
        direction = Direction::LEFT;
        startAnimationAngle = 0;
        break;
    case Direction::RIGHT:
        distance = QPointF(FIELD_WIDTH, -2*FIELD_HEIGHT);
        direction = Direction::UP;
        startAnimationAngle = 90;
        break;
    case Direction::DOWN:
        distance = QPointF(2*FIELD_WIDTH, FIELD_HEIGHT);
        direction = Direction::RIGHT;
        startAnimationAngle = 180;
        break;
    case Direction::LEFT:
        distance = QPointF(-FIELD_WIDTH, 2*FIELD_HEIGHT);
        direction = Direction::DOWN;
        startAnimationAngle = 270;
        break;
    case Direction::NONE:
        return;
    }

    QPointF difference = distance - currentDistance;
    animationLength = fmax(fabs(difference.x()), fabs(difference.y()));
    currentAnimationProgress = 0;
    rotateLeft = true;
    rotateRight = false;
}

void Car::turnRight()
{
    moving = true;
    currentDistance = QPointF(0, 0);

    switch(direction)
    {
    case Direction::UP:
        distance = QPointF(FIELD_WIDTH, 0);
        direction = Direction::RIGHT;
        startAnimationAngle = 0;
        break;
    case Direction::RIGHT:
        distance = QPointF(0, FIELD_HEIGHT);
        direction = Direction::DOWN;
        startAnimationAngle = 90;
        break;
    case Direction::DOWN:
        distance = QPointF(-FIELD_WIDTH, 0);
        direction = Direction::LEFT;
        startAnimationAngle = 180;
        break;
    case Direction::LEFT:
        distance = QPointF(0, -FIELD_HEIGHT);
        direction = Direction::UP;
        startAnimationAngle = 270;
        break;
    case Direction::NONE:
        return;
    }

    QPointF difference = distance - currentDistance;
    animationLength = fmax(fabs(difference.x()), fabs(difference.y()));
    currentAnimationProgress = 0;
    rotateLeft = false;
    rotateRight = true;
}

void Car::advance(int phase)
{
    QTransform transform;

    if(!moving)
        return;

    if(direction == Direction::NONE)
        return;

    if((x() <= 0 && direction == Direction::LEFT) ||
            (x() >= FIELD_WIDTH * (NUMBER_OF_VERTICAL_FIELDS - 1) && direction == Direction::RIGHT) ||
            (y() <= 0 && direction == Direction::UP) ||
            (y() >= FIELD_HEIGHT * (NUMBER_OF_HORIZONTAL_FIELDS - 1) && direction == Direction::LEFT))
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

    if(rotateLeft)
    {
        currentAnimationProgress += speed;
        transform = transform.rotate(startAnimationAngle - ((float)currentAnimationProgress / (float)animationLength) * 90.0);
        this->setPixmap(QPixmap(this->chosenPixmap.transformed(transform)));
    }
    else if(rotateRight)
    {
        currentAnimationProgress += speed;
        transform = transform.rotate(startAnimationAngle + ((float)currentAnimationProgress / (float)animationLength) * 90.0);
        this->setPixmap(QPixmap(this->chosenPixmap.transformed(transform)));
    }

    if(currentDistance == distance)
        moving = false;
}
