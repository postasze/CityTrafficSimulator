//Created by
//Marcin Chrostowski
//Paweł Ostaszewski

#ifndef PEDESTRIANCROSSING_H
#define PEDESTRIANCROSSING_H

#include "StreetElement.h"

class PedestrianCrossing : public StreetElement
{
public:
    PedestrianCrossing(const QPointF& scenePosition = QPointF(0, 0), const Direction& direction = Direction::UP,
                       const QPixmap& pixmap = QPixmap());
    PedestrianCrossing(const PedestrianCrossing& pedestrianCrossing);

    StreetElement* clone();
};

#endif // PEDESTRIANCROSSING_H
