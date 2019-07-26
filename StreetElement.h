//Created by
//Marcin Chrostowski
//Paweł Ostaszewski

#ifndef STREETELEMENT_H
#define STREETELEMENT_H

#include "CityObject.h"

class StreetElement : public CityObject
{
public:
    StreetElement(const QPointF& scenePosition = QPointF(0, 0), const Direction& direction = Direction::UP,
                  const QPixmap& pixmap = QPixmap());

    virtual StreetElement* clone() = 0;
};

#endif // STREETELEMENT_H
