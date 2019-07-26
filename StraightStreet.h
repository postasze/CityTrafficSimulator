//Created by
//Marcin Chrostowski
//Paweł Ostaszewski

#ifndef STRAIGHTSTREET_H
#define STRAIGHTSTREET_H

#include "StreetElement.h"

class StraightStreet : public StreetElement
{
public:
    StraightStreet(const QPointF& scenePosition = QPointF(0, 0), const Direction& direction = Direction::UP,
                   const QPixmap& pixmap = QPixmap());
    StraightStreet(const StraightStreet& straightStreet);

    StreetElement* clone();
};

#endif // STRAIGHTSTREET_H
