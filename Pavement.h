//Created by
//Marcin Chrostowski
//Paweł Ostaszewski

#ifndef PAVEMENT_H
#define PAVEMENT_H

#include "StreetElement.h"

class Pavement : public StreetElement
{
public:
    Pavement(const QPointF& scenePosition = QPointF(0, 0), const Direction& direction = Direction::UP,
             const QPixmap& pixmap = QPixmap());
    Pavement(const Pavement& pavement);

    StreetElement* clone();
};

#endif // PAVEMENT_H
