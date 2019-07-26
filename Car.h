//Created by
//Marcin Chrostowski
//Paweł Ostaszewski

#ifndef CAR_H
#define CAR_H

#include "RoadUser.h"

class Car : public RoadUser
{
public:
    Car(const QPointF& scenePosition, const Direction& direction, const QPixmap& pixmap, CarType carType_);

    int getSize();
    std::string getCarTypeName();
    virtual std::string getData();
    void moveStraight();
    void turnLeft();
    void turnRight();

protected:
    virtual void advance(int phase);

private:
    CarType carType;
    int size;
    float animationLength;
    QPixmap chosenPixmap;
    float currentAnimationProgress;
    float startAnimationAngle;
    bool rotateRight;
    bool rotateLeft;

    virtual void choseNextDirection();
    virtual void move(Direction direction);
};

#endif // CAR_H
