//Created by
//Marcin Chrostowski
//Paweł Ostaszewski

#ifndef CITYOBJECT_H
#define CITYOBJECT_H

#include <QGraphicsPixmapItem>
#include "Constants.h"

class CityObject : public QGraphicsPixmapItem
{
public:
    CityObject(const QPointF& scenePosition, const Direction& direction, const QPixmap& pixmap);
    Direction getDirection() const;
    void setDirection(Direction direction);
    QPoint getFieldPosition();

protected:
    Direction direction;

private:
};

#endif // CITYOBJECT_H
