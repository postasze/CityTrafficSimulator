//Created by
//Marcin Chrostowski
//Paweł Ostaszewski

#ifndef CROSSINGSTREET_H
#define CROSSINGSTREET_H

#include "StreetElement.h"

class CrossingStreet : public StreetElement
{
public:
    CrossingStreet(const QPointF& scenePosition = QPointF(0, 0), const Direction& direction = Direction::UP,
                   const QPixmap& pixmap = QPixmap());
    CrossingStreet(const CrossingStreet& crossingStreet);

    StreetElement* clone();
};

#endif // CROSSINGSTREET_H
