//Created by
//Marcin Chrostowski
//Paweł Ostaszewski

#ifndef DIVISIONSTREET_H
#define DIVISIONSTREET_H

#include "StreetElement.h"

class DivisionStreet : public StreetElement
{
public:
    DivisionStreet(const QPointF& scenePosition = QPointF(0, 0), const Direction& direction = Direction::UP,
                   const QPixmap& pixmap = QPixmap());
    DivisionStreet(const DivisionStreet& divisionStreet);

    StreetElement* clone();
};

#endif // DIVISIONSTREET_H
