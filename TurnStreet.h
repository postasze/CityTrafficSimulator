//Created by
//Marcin Chrostowski
//Paweł Ostaszewski

#ifndef TURNSTREET_H
#define TURNSTREET_H

#include "StreetElement.h"

class TurnStreet : public StreetElement
{
public:
    TurnStreet(const QPointF& scenePosition = QPointF(0, 0), const Direction& direction = Direction::UP,
               const QPixmap& pixmap = QPixmap());
    TurnStreet(const TurnStreet& turnStreet);

    StreetElement* clone();
};

#endif // TURNSTREET_H
