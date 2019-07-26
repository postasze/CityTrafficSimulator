//Created by
//Marcin Chrostowski
//Paweł Ostaszewski

#include "citytrafficsimulatorwidget.h"
#include <QtWidgets>
#include <iostream>
#include <cmath>
#include "MainWindow.h"
#include "CrossingStreet.h"
#include "DivisionStreet.h"
#include "Pavement.h"
#include "PedestrianCrossing.h"
#include "StraightStreet.h"
#include "TurnStreet.h"

CityTrafficSimulatorWidget::CityTrafficSimulatorWidget(QWidget *parent) : QWidget(parent)
{
    setAcceptDrops(true);

    //this->controller = &((MainWindow*)this->parent()->parent())->controller;
    //this->controller->scene = &this->cityTrafficSimulatorScene;

    cityTrafficSimulatorView.setParent(this);
    cityTrafficSimulatorScene.setParent(&cityTrafficSimulatorView);
    cityTrafficSimulatorView.setScene(&cityTrafficSimulatorScene);
    cityTrafficSimulatorView.setFixedSize(FIELD_WIDTH*NUMBER_OF_HORIZONTAL_FIELDS, FIELD_WIDTH*NUMBER_OF_VERTICAL_FIELDS);
    cityTrafficSimulatorScene.setSceneRect(0, 0, FIELD_WIDTH*NUMBER_OF_HORIZONTAL_FIELDS, FIELD_WIDTH*NUMBER_OF_VERTICAL_FIELDS);
    cityTrafficSimulatorView.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    cityTrafficSimulatorView.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    cityTrafficSimulatorScene.setBackgroundBrush(QBrush(FIELD_COLOR));

    //controller->drawGrid();
}

CityTrafficSimulatorWidget::~CityTrafficSimulatorWidget()
{
    //controller->clearBoard();
    cityTrafficSimulatorScene.clear();
}

void CityTrafficSimulatorWidget::dragEnterEvent(QDragEnterEvent *event)
{
    //std::cout << "dragEnter" << std::endl;
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void CityTrafficSimulatorWidget::dragMoveEvent(QDragMoveEvent *event)
{
    //std::cout << "dragMove" << std::endl;
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void CityTrafficSimulatorWidget::dropEvent(QDropEvent *event)
{
    //std::cout << "drop" << std::endl;

    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);
        QPixmap pixmap;

        dataStream >> pixmap;

        emit streetElementDropped(pixmap, event->pos());

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void CityTrafficSimulatorWidget::mousePressEvent(QMouseEvent *event)
{
    //std::cout << "mousePress" << std::endl;

    if(event->button() == Qt::LeftButton)
        emit leftMouseButtonPressed(event->pos());

    if(event->button() == Qt::RightButton)
        emit rightMouseButtonPressed(event->pos());
}
