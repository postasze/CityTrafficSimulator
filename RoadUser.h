//Created by
//Marcin Chrostowski
//Paweł Ostaszewski

#ifndef ROADUSER_H
#define ROADUSER_H

#include "CityObject.h"
#include <QPointF>

class RoadUser : public CityObject
{
public:
    RoadUser(const QPointF& scenePosition, const Direction& direction, const QPixmap& pixmap, qreal speed_ = 0, bool moving = false, QPointF distance = QPointF(0, 0));
    virtual ~RoadUser();
    qreal getSpeed();
    virtual std::string getData() = 0;
    void setPixmapDirection(Direction direction);
    bool isMoving();
    void setMoving(bool moving);

protected:
    int id;
    qreal speed;
    bool moving;
    QPointF distance;
    QPointF currentDistance;
    static unsigned int roadUserId;

    virtual void choseNextDirection() = 0;
    virtual void move(Direction direction) = 0;

private:
};

#endif // ROADUSER_H
