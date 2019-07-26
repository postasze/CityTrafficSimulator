//Created by
//Marcin Chrostowski
//Paweł Ostaszewski

#ifndef PEDESTRIAN_H
#define PEDESTRIAN_H

#include "RoadUser.h"

class Pedestrian : public RoadUser
{
public:
    Pedestrian(const QPointF& scenePosition, const Direction& direction, const QPixmap& pixmap);

    virtual std::string getData();
    virtual void choseNextDirection();
    virtual void move(Direction direction);

protected:
    virtual void advance(int phase);

private:
};

#endif // PEDESTRIAN_H
