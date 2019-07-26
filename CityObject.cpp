//Created by
//Marcin Chrostowski
//Paweł Ostaszewski

#include "CityObject.h"

CityObject::CityObject(const QPointF& scenePosition, const Direction& direction, const QPixmap& pixmap) :
    QGraphicsPixmapItem(pixmap), direction(direction)
{
    this->setPos(scenePosition);
}

Direction CityObject::getDirection() const
{
    return this->direction;
}

void CityObject::setDirection(Direction direction)
{
    this->direction = direction;
}

QPoint CityObject::getFieldPosition()
{
    return QPoint(pos().x() / FIELD_WIDTH, pos().y() / FIELD_HEIGHT);
}
