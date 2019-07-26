//Created by
//Marcin Chrostowski
//Paweł Ostaszewski

#include <QTime>
#include <QMessageBox>
#include "Controller.h"
#include "RoadUser.h"
#include "CrossingStreet.h"
#include "DivisionStreet.h"
#include "Pavement.h"
#include "PedestrianCrossing.h"
#include "StraightStreet.h"
#include "TurnStreet.h"
#include <iostream>
#include "ui_mainwindow.h"

Controller::Controller(QObject *parent) : QObject(parent), simulationPaused(true)
{
    connect(mainWindow.ui->cleanButton, SIGNAL(clicked()), this, SLOT(clearBoard()));
    connect(mainWindow.ui->startButton, SIGNAL(clicked()), this, SLOT(startSimulation()));
    connect(mainWindow.ui->stopButton, SIGNAL(clicked()), this, SLOT(stopSimulation()));
    connect(mainWindow.ui->vehiclesStartPointPushButton, &QPushButton::clicked, &mainWindow, &MainWindow::vehiclesStartPointPushButtonClicked);
    connect(mainWindow.ui->vehiclesEndPointPushButton, &QPushButton::clicked, &mainWindow, &MainWindow::vehiclesEndPointPushButtonClicked);
    connect(mainWindow.ui->pedestrianStartPointPushButton, &QPushButton::clicked, &mainWindow, &MainWindow::pedestrianStartPointPushButtonClicked);
    connect(mainWindow.ui->pedestrianEndPointPushButton, &QPushButton::clicked, &mainWindow, &MainWindow::pedestrianEndPointPushButtonClicked);
    connect(&mainWindow, SIGNAL(currentPointTypeChanged(PointType)), this, SLOT(currentPointTypeChanged(PointType)));
    connect(mainWindow.ui->cityConstructorWidget, SIGNAL(streetElementSelected(StreetElement*)), this, SLOT(selectStreetElement(StreetElement*)));
    connect(mainWindow.ui->defaultCityCreationPushButton, SIGNAL(clicked()), this, SLOT(createDefaultCity()));
    connect(mainWindow.ui->simulationSpeedComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeSimulationSpeed(int)));
    connect(mainWindow.ui->pedestrianNumberOkButton, SIGNAL(clicked()), this, SLOT(setMaxNumberOfPedestrians()));
    connect(mainWindow.ui->carNumberOkButton, SIGNAL(clicked()), this, SLOT(setMaxNumberOfCars()));
    connect(mainWindow.ui->cityTrafficSimulatorWidget, SIGNAL(streetElementDropped(QPixmap, QPoint)), this, SLOT(streetElementDroppedOnScene(QPixmap, QPoint)));
    connect(mainWindow.ui->cityTrafficSimulatorWidget, SIGNAL(leftMouseButtonPressed(QPoint)), this, SLOT(leftMouseButtonPressedOnScene(QPoint)));
    connect(mainWindow.ui->cityTrafficSimulatorWidget, SIGNAL(rightMouseButtonPressed(QPoint)), this, SLOT(rightMouseButtonPressedOnScene(QPoint)));

    maxNumberOfCars = MAXIMAL_NUMBER_OF_CARS;
    maxNumberOfPedestrians = MAXIMAL_NUMBER_OF_PEDESTRIANS;

    QTime timeSeed = QTime::currentTime();
    qsrand((uint)timeSeed.msec());

    animationTimer.start(ANIMATION_TIMER_INTERVAL);
    realTimer.start(REAL_TIMER_INTERVAL);
    
    setCurrentTimeForClock();
    loadImages();
    clearArrays();

    currentPointType = PointType::NONE;
    cameraForTextField = nullptr;
}

Controller::~Controller()
{
    //clearBoard();
}

void Controller::run()
{
    mainWindow.showMaximized();
    this->scene = &mainWindow.ui->cityTrafficSimulatorWidget->cityTrafficSimulatorScene;
    drawGrid();
}

void Controller::loadImages()
{
    pedestrian1Pixmap.load(":/images/pedestrians/pedestrian1.png");
    pedestrian2Pixmap.load(":/images/pedestrians/pedestrian2.png");
    pedestrian3Pixmap.load(":/images/pedestrians/pedestrian3.png");
    smallCar1Pixmap.load(":/images/small_cars/gray_car.png");
    smallCar2Pixmap.load(":/images/small_cars/gray_car1.png");
    smallCar3Pixmap.load(":/images/small_cars/police_car.png");
    smallCar4Pixmap.load(":/images/small_cars/red_car.png");
    smallCar5Pixmap.load(":/images/small_cars/yellow_car.png");
    smallCar6Pixmap.load(":/images/small_cars/yellow_car1.png");
    bigCar1Pixmap.load(":/images/big_cars/big_car.png");
    bigCar2Pixmap.load(":/images/big_cars/big_car1.png");
    bigCar3Pixmap.load(":/images/big_cars/big_car2.png");
    bigCar4Pixmap.load(":/images/big_cars/big_car3.png");

    cameraPixmap.load(":/images/cameras/camera.png");
    greenLightPixmap.load(":/images/traffic_lights/green_light.png");
    orangeLightPixmap.load(":/images/traffic_lights/orange_light.png");
    redLightPixmap.load(":/images/traffic_lights/red_light.png");
    CrossingPixmap.load(":/images/streets/gray_crossing_street.png");
    DivisionStreetPixmap.load(":/images/streets/gray_division_street.png");
    StraightStreetPixmap.load(":/images/streets/gray_straight_street.png");
    TurnStreetPixmap.load(":/images/streets/gray_turn_street.png");
    PedestrianCrossingPixmap.load(":/images/streets/pedestrian_crossing.png");
    PavementPixmap.load(":/images/streets/pavement.png");

    cameraPixmap = cameraPixmap.scaledToHeight(SCALE_OF_CAMERA * cameraPixmap.height());
    greenLightPixmap = greenLightPixmap.scaledToHeight(SCALE_OF_TRAFFIC_LIGHT * greenLightPixmap.height());
    orangeLightPixmap = orangeLightPixmap.scaledToHeight(SCALE_OF_TRAFFIC_LIGHT * orangeLightPixmap.height());
    redLightPixmap = redLightPixmap.scaledToHeight(SCALE_OF_TRAFFIC_LIGHT * redLightPixmap.height());
    CrossingPixmap = CrossingPixmap.scaledToHeight(SCALE_OF_BASIC_ELEMENT * CrossingPixmap.height());
    DivisionStreetPixmap = DivisionStreetPixmap.scaledToHeight(SCALE_OF_BASIC_ELEMENT * DivisionStreetPixmap.height());
    StraightStreetPixmap = StraightStreetPixmap.scaledToHeight(SCALE_OF_BASIC_ELEMENT * StraightStreetPixmap.height());
    TurnStreetPixmap = TurnStreetPixmap.scaledToHeight(SCALE_OF_BASIC_ELEMENT * TurnStreetPixmap.height());
    PedestrianCrossingPixmap = PedestrianCrossingPixmap.scaledToHeight(SCALE_OF_BASIC_ELEMENT * PedestrianCrossingPixmap.height());
    PavementPixmap = PavementPixmap.scaledToHeight(SCALE_OF_BASIC_ELEMENT * PavementPixmap.height());
}

void Controller::clearArrays()
{
    for(unsigned int i = 0; i < NUMBER_OF_HORIZONTAL_FIELDS; i++)
        for(unsigned int j = 0; j < NUMBER_OF_VERTICAL_FIELDS; j++)
        {
            streetArray[i][j] = nullptr;
            trafficLightsArray[i][j] = nullptr;
            camerasArray[i][j] = nullptr;
            pointsArray[i][j] = nullptr;
        }
}

void Controller::deleteAllCityObjects()
{
    streetElements.clear();
    trafficLights.clear();
    cameras.clear();
    cars.clear();
    pedestrians.clear();
    points.clear();
}

void Controller::startSimulation()
{
    if(!simulationPaused)
        return;

    connect(&animationTimer, SIGNAL(timeout()), scene, SLOT(advance()));
    connect(&animationTimer, SIGNAL(timeout()), scene, SLOT(update()));
    connect(&animationTimer, SIGNAL(timeout()), this, SLOT(addNewRoadUser()));
    connect(&animationTimer, SIGNAL(timeout()), this, SLOT(choseNextDirectionForRoadUsers()));
    connect(&realTimer, SIGNAL(timeout()), this, SLOT(addOneSecondToClock()));
    connect(&realTimer, SIGNAL(timeout()), this, SLOT(cameraObservationForTextField()));
    foreach(Camera* camera, cameras){
        connect(&realTimer, SIGNAL(timeout()), this, SLOT(camerasObserve()));
    }
    simulationPaused = false;
}

void Controller::stopSimulation()
{
    if(simulationPaused)
        return;

    disconnect(&animationTimer, SIGNAL(timeout()), scene, SLOT(advance()));
    disconnect(&animationTimer, SIGNAL(timeout()), scene, SLOT(update()));
    disconnect(&animationTimer, SIGNAL(timeout()), this, SLOT(addNewRoadUser()));
    disconnect(&animationTimer, SIGNAL(timeout()), this, SLOT(choseNextDirectionForRoadUsers()));
    disconnect(&realTimer, SIGNAL(timeout()), this, SLOT(addOneSecondToClock()));
    disconnect(&realTimer, SIGNAL(timeout()), this, SLOT(cameraObservationForTextField()));
    foreach(Camera* camera, cameras){
        disconnect(&realTimer, SIGNAL(timeout()), this, SLOT(camerasObserve()));
    }
    simulationPaused = true;
}

void Controller::addNewRoadUser()
{
    switch(qrand() % 2)
    {
    case 0: // new car
        if(cars.size() >= maxNumberOfCars)
            return;
        if((qrand() % 100) < 5) // probability for adding a new car
            addNewCar();
        break;
    case 1: // new pedestrian
        if(pedestrians.size() >= maxNumberOfPedestrians)
            return;
        if((qrand() % 100) < 5) // probability for adding a new pedestrian
            addNewPedestrian();
        break;
    }
}

void Controller::addNewPedestrian()
{
    Pedestrian *newPedestrian;
    QPixmap *chosenPixmap;
    QGraphicsEllipseItem *chosenPoint;
    std::vector<QGraphicsEllipseItem*> pedestrianStartPoints;
    int chosenIndex;

    std::copy_if(points.begin(), points.end(), std::back_inserter(pedestrianStartPoints),
                  [](QGraphicsEllipseItem* point) {return point->brush().color() == Qt::yellow;} );

    if(pedestrianStartPoints.empty())
        return;

    chosenIndex = qrand() % pedestrianStartPoints.size();
    chosenPoint = pedestrianStartPoints[chosenIndex];

    switch(qrand() % 3) // choice of one of the pedestrian images
    {
    case 0:
        chosenPixmap = &pedestrian1Pixmap;
        break;
    case 1:
        chosenPixmap = &pedestrian2Pixmap;
        break;
    case 2:
        chosenPixmap = &pedestrian3Pixmap;
        break;
    }

    newPedestrian = new Pedestrian(chosenPoint->pos(), Direction::UP, *chosenPixmap);
    newPedestrian->setScale(SCALE_OF_PEDESTRIAN);
    newPedestrian->setZValue(2);
    pedestrians.push_back(newPedestrian);
    scene->addItem(newPedestrian);
}

void Controller::addNewCar()
{
    Car *newCar;
    QPixmap *chosenPixmap;
    QGraphicsEllipseItem *chosenPoint;
    std::vector<QGraphicsEllipseItem*> carStartPoints;
    int chosenIndex;
    CarType chosenCarType;
    Direction carStartingDirection;

    std::copy_if(points.begin(), points.end(), std::back_inserter(carStartPoints),
                  [](QGraphicsEllipseItem* point) {return point->brush().color() == Qt::green;} );

    if(carStartPoints.empty())
        return;

    chosenIndex = qrand() % carStartPoints.size();
    chosenPoint = carStartPoints[chosenIndex];

    switch(qrand() % 2) // choice of one of the car types
    {
    case 0:
        chosenCarType = CarType::AUTOMOBILE;
        switch(qrand() % 6) // choice of one of the small car images
        {
        case 0:
            chosenPixmap = &smallCar1Pixmap;
            break;
        case 1:
            chosenPixmap = &smallCar2Pixmap;
            break;
        case 2:
            chosenPixmap = &smallCar3Pixmap;
            break;
        case 3:
            chosenPixmap = &smallCar4Pixmap;
            break;
        case 4:
            chosenPixmap = &smallCar5Pixmap;
            break;
        case 5:
            chosenPixmap = &smallCar6Pixmap;
            break;
        }
        break;
    case 1:
        chosenCarType = CarType::TRUCK;
        switch(qrand() % 4) // choice of one of the big car images
        {
        case 0:
            chosenPixmap = &bigCar1Pixmap;
            break;
        case 1:
            chosenPixmap = &bigCar2Pixmap;
            break;
        case 2:
            chosenPixmap = &bigCar3Pixmap;
            break;
        case 3:
            chosenPixmap = &bigCar4Pixmap;
            break;
        }
        break;
    }

    QPoint carPosition = QPoint(chosenPoint->pos().x() / FIELD_WIDTH, chosenPoint->pos().y() / FIELD_HEIGHT);
    StraightStreet *straightStreet = dynamic_cast<StraightStreet*>(streetArray[carPosition.x()][carPosition.y()]);
    QPoint streetPosition = straightStreet->getFieldPosition();
    QPoint difference = carPosition - streetPosition;

    if(difference == QPoint(0, 0)){
        if(straightStreet->getDirection() == Direction::UP || straightStreet->getDirection() == Direction::DOWN)
            carStartingDirection = Direction::DOWN;
        else if(straightStreet->getDirection() == Direction::LEFT || straightStreet->getDirection() == Direction::RIGHT)
            carStartingDirection = Direction::LEFT;
    }
    else if(difference == QPoint(0, 1)){
        if(straightStreet->getDirection() == Direction::LEFT || straightStreet->getDirection() == Direction::RIGHT)
            carStartingDirection = Direction::RIGHT;
        else if(straightStreet->getDirection() == Direction::UP || straightStreet->getDirection() == Direction::DOWN)
            carStartingDirection = Direction::DOWN;
    }
    else if(difference == QPoint(1, 0)){
        if(straightStreet->getDirection() == Direction::LEFT || straightStreet->getDirection() == Direction::RIGHT)
            carStartingDirection = Direction::LEFT;
        else if(straightStreet->getDirection() == Direction::UP || straightStreet->getDirection() == Direction::DOWN)
            carStartingDirection = Direction::UP;
    }
    else if(difference == QPoint(1, 1)){
        if(straightStreet->getDirection() == Direction::UP || straightStreet->getDirection() == Direction::DOWN)
            carStartingDirection = Direction::UP;
        else if(straightStreet->getDirection() == Direction::LEFT || straightStreet->getDirection() == Direction::RIGHT)
            carStartingDirection = Direction::RIGHT;
    }

    newCar = new Car(chosenPoint->pos(), carStartingDirection, *chosenPixmap, chosenCarType);
    newCar->setZValue(2);
    cars.push_back(newCar);
    scene->addItem(newCar);
}

void Controller::choseNextDirectionForRoadUsers()
{
    choseNextDirectionForPedestrians();
    choseNextDirectionForCars();
}

void Controller::choseNextDirectionForPedestrians()
{
    QPoint pedestrianPosition;

    foreach (Pedestrian *pedestrian, pedestrians) {

        if(pedestrian->isMoving())
            continue;

        pedestrianPosition = pedestrian->getFieldPosition();

        if(pointsArray[pedestrianPosition.x()][pedestrianPosition.y()] != nullptr)
            if(pointsArray[pedestrianPosition.x()][pedestrianPosition.y()]->brush().color() == Qt::blue)
            {
                scene->removeItem(pedestrian);
                pedestrians.erase(std::find(pedestrians.begin(), pedestrians.end(), pedestrian));
                delete pedestrian;
                continue;
            }

        switch(qrand() % 4)
        {
        case 0: // down
            if(pedestrianPosition.y() == NUMBER_OF_VERTICAL_FIELDS-1) // border of the 2D board
                continue;
            if (!dynamic_cast<Pavement*>(streetArray[pedestrianPosition.x()][pedestrianPosition.y()+1]) &&
                !dynamic_cast<PedestrianCrossing*>(streetArray[pedestrianPosition.x()][pedestrianPosition.y()+1]))
                continue;
            pedestrian->move(Direction::DOWN);
            break;
        case 1: // up
            if(pedestrianPosition.y() == 0) // border of the 2D board
                continue;
            if (!dynamic_cast<Pavement*>(streetArray[pedestrianPosition.x()][pedestrianPosition.y()-1]) &&
                !dynamic_cast<PedestrianCrossing*>(streetArray[pedestrianPosition.x()][pedestrianPosition.y()-1]))
                continue;
            pedestrian->move(Direction::UP);
            break;
        case 2: // right
            if(pedestrianPosition.x() == NUMBER_OF_HORIZONTAL_FIELDS-1) // border of the 2D board
                continue;
            if (!dynamic_cast<Pavement*>(streetArray[pedestrianPosition.x()+1][pedestrianPosition.y()]) &&
                !dynamic_cast<PedestrianCrossing*>(streetArray[pedestrianPosition.x()+1][pedestrianPosition.y()]))
                continue;
            pedestrian->move(Direction::RIGHT);
            break;
        case 3: // left
            if(pedestrianPosition.x() == 0) // border of the 2D board
                continue;
            if (!dynamic_cast<Pavement*>(streetArray[pedestrianPosition.x()-1][pedestrianPosition.y()]) &&
                !dynamic_cast<PedestrianCrossing*>(streetArray[pedestrianPosition.x()-1][pedestrianPosition.y()]))
                continue;
            pedestrian->move(Direction::LEFT);
            break;
        }
    }
}

void Controller::choseNextDirectionForCars()
{
    QPoint carPosition;

    foreach (Car *car, cars) {

        if(car->isMoving())
            continue;

        carPosition = car->getFieldPosition();

        if(pointsArray[carPosition.x()][carPosition.y()] != nullptr)
            if(pointsArray[carPosition.x()][carPosition.y()]->brush().color() == Qt::red)
            {
                scene->removeItem(car);
                cars.erase(std::find(cars.begin(), cars.end(), car));
                delete car;
                continue;
            }

        if (dynamic_cast<StraightStreet*>(streetArray[carPosition.x()][carPosition.y()]) ||
            dynamic_cast<PedestrianCrossing*>(streetArray[carPosition.x()][carPosition.y()]))
            car->moveStraight();
        else if(TurnStreet *turnStreet = dynamic_cast<TurnStreet*>(streetArray[carPosition.x()][carPosition.y()]))
        {
            switch(turnStreet->getDirection())
            {
            case Direction::UP:
                if(car->getDirection() == Direction::UP)
                    car->turnRight();
                else if(car->getDirection() == Direction::LEFT)
                    car->turnLeft();
                break;
            case Direction::RIGHT:
                if(car->getDirection() == Direction::RIGHT)
                    car->turnRight();
                else if(car->getDirection() == Direction::UP)
                    car->turnLeft();
                break;
            case Direction::DOWN:
                if(car->getDirection() == Direction::DOWN)
                    car->turnRight();
                else if(car->getDirection() == Direction::RIGHT)
                    car->turnLeft();
                break;
            case Direction::LEFT:
                if(car->getDirection() == Direction::LEFT)
                    car->turnRight();
                else if(car->getDirection() == Direction::DOWN)
                    car->turnLeft();
                break;
            case Direction::NONE:
                continue;
            }
        }
        else if(DivisionStreet *divisionStreet = dynamic_cast<DivisionStreet*>(streetArray[carPosition.x()][carPosition.y()]))
        {
            switch(divisionStreet->getDirection())
            {
            case Direction::UP:
                if(car->getDirection() == Direction::UP)
                    switch(qrand() % 2)
                    {
                    case 0:
                        car->turnLeft();
                        break;
                    case 1:
                        car->turnRight();
                        break;
                    }
                else if(car->getDirection() == Direction::LEFT)
                    car->turnLeft();
                else if(car->getDirection() == Direction::RIGHT)
                    car->turnRight();
                break;
            case Direction::RIGHT:
                if(car->getDirection() == Direction::RIGHT)
                    switch(qrand() % 2)
                    {
                    case 0:
                        car->turnLeft();
                        break;
                    case 1:
                        car->turnRight();
                        break;
                    }
                else if(car->getDirection() == Direction::UP)
                    car->turnLeft();
                else if(car->getDirection() == Direction::DOWN)
                    car->turnRight();
                break;
            case Direction::DOWN:
                if(car->getDirection() == Direction::DOWN)
                    switch(qrand() % 2)
                    {
                    case 0:
                        car->turnLeft();
                        break;
                    case 1:
                        car->turnRight();
                        break;
                    }
                else if(car->getDirection() == Direction::LEFT)
                    car->turnRight();
                else if(car->getDirection() == Direction::RIGHT)
                    car->turnLeft();
                break;
            case Direction::LEFT:
                if(car->getDirection() == Direction::LEFT)
                    switch(qrand() % 2)
                    {
                    case 0:
                        car->turnLeft();
                        break;
                    case 1:
                        car->turnRight();
                        break;
                    }
                else if(car->getDirection() == Direction::UP)
                    car->turnRight();
                else if(car->getDirection() == Direction::DOWN)
                    car->turnLeft();
                break;
            case Direction::NONE:
                continue;
            }
        }
        else if(dynamic_cast<CrossingStreet*>(streetArray[carPosition.x()][carPosition.y()]))
        {
            switch(qrand() % 4)
            {
            case 0: // down
                if(carPosition.y() >= NUMBER_OF_VERTICAL_FIELDS-2) // border of the 2D board
                    continue;
                if (!dynamic_cast<StraightStreet*>(streetArray[carPosition.x()][carPosition.y()+2]) &&
                    !dynamic_cast<TurnStreet*>(streetArray[carPosition.x()][carPosition.y()+2]) &&
                    !dynamic_cast<CrossingStreet*>(streetArray[carPosition.x()][carPosition.y()+2]) &&
                    !dynamic_cast<DivisionStreet*>(streetArray[carPosition.x()][carPosition.y()+2]) &&
                    !dynamic_cast<PedestrianCrossing*>(streetArray[carPosition.x()][carPosition.y()+2]))
                    continue;
                switch(car->getDirection())
                {
                case Direction::UP: case Direction::NONE:
                    continue;
                case Direction::RIGHT:
                    car->turnRight();
                    break;
                case Direction::DOWN:
                    car->moveStraight();
                    break;
                case Direction::LEFT:
                    car->turnLeft();
                    break;
                }
                break;
            case 1: // up
                if(carPosition.y() <= 1) // border of the 2D board
                    continue;
                if (!dynamic_cast<StraightStreet*>(streetArray[carPosition.x()][carPosition.y()-2]) &&
                    !dynamic_cast<TurnStreet*>(streetArray[carPosition.x()][carPosition.y()-2]) &&
                    !dynamic_cast<CrossingStreet*>(streetArray[carPosition.x()][carPosition.y()-2]) &&
                    !dynamic_cast<DivisionStreet*>(streetArray[carPosition.x()][carPosition.y()-2]) &&
                    !dynamic_cast<PedestrianCrossing*>(streetArray[carPosition.x()][carPosition.y()-2]))
                    continue;
                switch(car->getDirection())
                {
                case Direction::UP:
                    car->moveStraight();
                    break;
                case Direction::RIGHT:
                    car->turnLeft();
                    break;
                case Direction::DOWN: case Direction::NONE:
                    continue;
                case Direction::LEFT:
                    car->turnRight();
                    break;
                }
                break;
            case 2: // right
                if(carPosition.x() >= NUMBER_OF_HORIZONTAL_FIELDS-2) // border of the 2D board
                    continue;
                if (!dynamic_cast<StraightStreet*>(streetArray[carPosition.x()+2][carPosition.y()]) &&
                    !dynamic_cast<TurnStreet*>(streetArray[carPosition.x()+2][carPosition.y()]) &&
                    !dynamic_cast<CrossingStreet*>(streetArray[carPosition.x()+2][carPosition.y()]) &&
                    !dynamic_cast<DivisionStreet*>(streetArray[carPosition.x()+2][carPosition.y()]) &&
                    !dynamic_cast<PedestrianCrossing*>(streetArray[carPosition.x()+2][carPosition.y()]))
                    continue;
                switch(car->getDirection())
                {
                case Direction::UP:
                    car->turnRight();
                    break;
                case Direction::RIGHT:
                    car->moveStraight();
                    break;
                case Direction::DOWN:
                    car->turnLeft();
                    break;
                case Direction::LEFT: case Direction::NONE:
                    continue;
                }
                break;
            case 3: // left
                if(carPosition.x() <= 1) // border of the 2D board
                    continue;
                if (!dynamic_cast<StraightStreet*>(streetArray[carPosition.x()-2][carPosition.y()]) &&
                    !dynamic_cast<TurnStreet*>(streetArray[carPosition.x()-2][carPosition.y()]) &&
                    !dynamic_cast<CrossingStreet*>(streetArray[carPosition.x()-2][carPosition.y()]) &&
                    !dynamic_cast<DivisionStreet*>(streetArray[carPosition.x()-2][carPosition.y()]) &&
                    !dynamic_cast<PedestrianCrossing*>(streetArray[carPosition.x()-2][carPosition.y()]))
                    continue;
                switch(car->getDirection())
                {
                case Direction::UP:
                    car->turnLeft();
                    break;
                case Direction::RIGHT: case Direction::NONE:
                    continue;
                case Direction::DOWN:
                    car->turnRight();
                    break;
                case Direction::LEFT:
                    car->moveStraight();
                    break;
                }
                break;
            }
        }
    }
}

void Controller::camerasObserve()
{
    foreach(Camera *camera, cameras){
        camera->observe(pedestrians, cars, clock);
    }
}

void Controller::addRoadUser(RoadUser *roadUser)
{
    //listRoadUser.append(roadUser);
    scene->addItem(roadUser);
}

void Controller::removeRoadUser(RoadUser *roadUser)
{
    //listRoadUser.removeOne(roadUser);
    scene->removeItem(roadUser);
}

/*
void Controller::addCamera(Camera *camera)
{
    listCamera.append(camera);
}

void Controller::removeCamera(Camera *camera)
{
    listCamera.removeOne(camera);
}
*/

void Controller::drawGrid()
{
    for(unsigned int i = 0; i < NUMBER_OF_HORIZONTAL_FIELDS-1; i++)
    {
        horizontalLinesArray[i] = new QGraphicsLineItem(0, FIELD_WIDTH + i*FIELD_WIDTH,
            FIELD_WIDTH*NUMBER_OF_HORIZONTAL_FIELDS, FIELD_WIDTH + i*FIELD_WIDTH);
        horizontalLinesArray[i]->setPen(QPen(QBrush(LINE_COLOR), LINE_THICKNESS));
        scene->addItem(horizontalLinesArray[i]);
    }

    for(unsigned int i = 0; i < NUMBER_OF_VERTICAL_FIELDS-1; i++)
    {
        verticalLinesArray[i] = new QGraphicsLineItem(FIELD_WIDTH + i*FIELD_WIDTH, 0,
            FIELD_WIDTH + i*FIELD_WIDTH, FIELD_WIDTH*NUMBER_OF_VERTICAL_FIELDS);
        verticalLinesArray[i]->setPen(QPen(QBrush(LINE_COLOR), LINE_THICKNESS));
        scene->addItem(verticalLinesArray[i]);
    }
}

void Controller::clearBoard()
{
    scene->clear();
    clearArrays();
    deleteAllCityObjects();
    drawGrid();
}

void Controller::streetElementDroppedOnScene(QPixmap pixmap, QPoint eventPosition)
{
    if (dynamic_cast<Pavement*>(selectedStreetElement) ||
        dynamic_cast<TrafficLight*>(selectedStreetElement) ||
        dynamic_cast<Camera*>(selectedStreetElement))
        add_1x1_element(selectedStreetElement, pixmap, eventPosition);
    else if(dynamic_cast<PedestrianCrossing*>(selectedStreetElement))
        add_1x2_element(selectedStreetElement, pixmap, eventPosition);
    else if(dynamic_cast<StraightStreet*>(selectedStreetElement) ||
            dynamic_cast<TurnStreet*>(selectedStreetElement) ||
            dynamic_cast<DivisionStreet*>(selectedStreetElement) ||
            dynamic_cast<CrossingStreet*>(selectedStreetElement))
        add_2x2_element(selectedStreetElement, pixmap, eventPosition);
}

void Controller::leftMouseButtonPressedOnScene(QPoint eventPosition)
{
    // displaying pressed cameras observations
    if(Camera* camera = dynamic_cast<Camera*>(scene->itemAt(eventPosition, QTransform())))
        setCameraToDisplay(camera);

    // adding points for vehicles or pedestrians
    if(((currentPointType == PointType::VEHICLE_START_POINT || currentPointType == PointType::VEHICLE_END_POINT) &&
        dynamic_cast<StraightStreet*>(scene->itemAt(eventPosition, QTransform()))) ||
        ((currentPointType == PointType::PEDESTRIAN_START_POINT || currentPointType == PointType::PEDESTRIAN_END_POINT) &&
        dynamic_cast<Pavement*>(scene->itemAt(eventPosition, QTransform()))))
        addNewPoint(currentPointType, eventPosition);
}

void Controller::rightMouseButtonPressedOnScene(QPoint eventPosition)
{   // erasing elements that have been clicked with right mouse button
    if(StreetElement* child = dynamic_cast<StreetElement*>(scene->itemAt(eventPosition, QTransform())))
    {
        QPoint fieldPosition(child->pos().x()/FIELD_WIDTH, child->pos().y()/FIELD_HEIGHT);
        scene->removeItem(child);
        unsigned int fieldWidth, fieldHeight;
        StraightStreet *straightStreet;

        switch(static_cast<int>(child->zValue()))
        {
        case 0: // basic city element
            // warning, fragile part of code, dependent on the size of element's pixmap
            fieldWidth = round((double)(child->pixmap().width())/((double)FIELD_WIDTH));
            fieldHeight = round((double)(child->pixmap().height())/((double)FIELD_HEIGHT));

            for(unsigned int i = 0; i < fieldWidth; i++)
                for(unsigned int j = 0; j < fieldHeight; j++)
                    streetArray[fieldPosition.x()+i][fieldPosition.y()+j] = nullptr;
            streetElements.erase(std::find(streetElements.begin(), streetElements.end(), child));
            break;
        case 1: // pedestrian crossing
            // warning, fragile part of code, dependent on the size of element's pixmap
            fieldWidth = round((double)(child->pixmap().width())/((double)FIELD_WIDTH));
            fieldHeight = round((double)(child->pixmap().height())/((double)FIELD_HEIGHT));

            straightStreet = dynamic_cast<StraightStreet*>(scene->itemAt(eventPosition, QTransform()));

            for(unsigned int i = 0; i < fieldWidth; i++)
                for(unsigned int j = 0; j < fieldHeight; j++)
                    streetArray[fieldPosition.x()+i][fieldPosition.y()+j] = straightStreet;
            streetElements.erase(std::find(streetElements.begin(), streetElements.end(), child));
            break;
        case 3: // traffic light
            trafficLightsArray[fieldPosition.x()][fieldPosition.y()] = nullptr;
            trafficLights.erase(std::find(trafficLights.begin(), trafficLights.end(), child));
            break;
        case 4: // camera
            camerasArray[fieldPosition.x()][fieldPosition.y()] = nullptr;
            cameras.erase(std::find(cameras.begin(), cameras.end(), child));
            break;
        }
        delete child;
    }
    else if(QGraphicsEllipseItem* child = dynamic_cast<QGraphicsEllipseItem*>(scene->itemAt(eventPosition, QTransform())))
    {
        QPoint fieldPosition(eventPosition.x()/FIELD_WIDTH, eventPosition.y()/FIELD_HEIGHT);
        scene->removeItem(child);
        pointsArray[fieldPosition.x()][fieldPosition.y()] = nullptr;
        points.erase(std::find(points.begin(), points.end(), child));
        delete child;
    }
}

void Controller::add_1x1_element(StreetElement *streetElement, const QPixmap& pixmap, const QPoint& eventPosition)
{   // coordinates of city elements are in the numbers of 2D board squares, instead of in pixels
    QPoint fieldPosition(eventPosition.x()/FIELD_WIDTH, eventPosition.y()/FIELD_HEIGHT);
    StreetElement *newStreetElement;

    if (dynamic_cast<Pavement*>(streetElement))
    {
        if(streetArray[fieldPosition.x()][fieldPosition.y()] != nullptr)
            return ;
        newStreetElement = streetElement->clone();
        newStreetElement->setZValue(0);
        streetElements.push_back(newStreetElement);
        streetArray[fieldPosition.x()][fieldPosition.y()] = newStreetElement;
        newStreetElement->setPixmap(pixmap);
        newStreetElement->setPos(QPoint(fieldPosition.x()*FIELD_WIDTH, fieldPosition.y()*FIELD_HEIGHT));
        scene->addItem(newStreetElement);
    }
    else if(dynamic_cast<TrafficLight*>(streetElement))
    {
        if ((!dynamic_cast<CrossingStreet*>(streetArray[fieldPosition.x()][fieldPosition.y()])) ||
            trafficLightsArray[fieldPosition.x()][fieldPosition.y()] != nullptr)
            return ;
        newStreetElement = streetElement->clone();
        newStreetElement->setZValue(3);
        trafficLights.push_back((TrafficLight*) newStreetElement);
        trafficLightsArray[fieldPosition.x()][fieldPosition.y()] = (TrafficLight*) newStreetElement;
        newStreetElement->setPixmap(pixmap);
        newStreetElement->setPos(QPoint(fieldPosition.x()*FIELD_WIDTH, fieldPosition.y()*FIELD_HEIGHT));
        scene->addItem(newStreetElement);
    }
    else if(dynamic_cast<Camera*>(streetElement))
    {
        if(camerasArray[fieldPosition.x()][fieldPosition.y()] != nullptr)
            return ;
        newStreetElement = streetElement->clone();
        newStreetElement->setZValue(4);
        Camera* newCamera = (Camera*) newStreetElement;
        cameras.push_back(newCamera);
        camerasArray[fieldPosition.x()][fieldPosition.y()] = newCamera;
        newCamera->setPixmap(pixmap);
        newCamera->setPos(QPoint(fieldPosition.x()*FIELD_WIDTH, fieldPosition.y()*FIELD_HEIGHT));
        newCamera->setObservationField();
        scene->addItem(newCamera);
    }
}

void Controller::add_1x2_element(StreetElement *streetElement, const QPixmap& pixmap, const QPoint& eventPosition)
{   // coordinates of city elements are in the numbers of 2D board squares, instead of in pixels
    QPoint fieldPosition;
    StreetElement *newStreetElement;

    switch(streetElement->getDirection())
    {
    case Direction::UP: case Direction::DOWN:
        fieldPosition.setX(eventPosition.x()/FIELD_WIDTH);
        fieldPosition.setY(fmin((eventPosition.y()/(FIELD_HEIGHT/2)-1)/2, NUMBER_OF_VERTICAL_FIELDS-2));

        if ((!dynamic_cast<StraightStreet*>(streetArray[fieldPosition.x()][fieldPosition.y()])) ||
            (!dynamic_cast<StraightStreet*>(streetArray[fieldPosition.x()][fieldPosition.y()+1])) ||
            (dynamic_cast<PedestrianCrossing*>(streetArray[fieldPosition.x()][fieldPosition.y()])) ||
            (dynamic_cast<PedestrianCrossing*>(streetArray[fieldPosition.x()][fieldPosition.y()+1])))
            return;
        else if ((dynamic_cast<StraightStreet*>(streetArray[fieldPosition.x()][fieldPosition.y()]))->getDirection() == UP ||
            (dynamic_cast<StraightStreet*>(streetArray[fieldPosition.x()][fieldPosition.y()]))->getDirection() == DOWN ||
            (dynamic_cast<StraightStreet*>(streetArray[fieldPosition.x()][fieldPosition.y()+1]))->getDirection() == UP ||
            (dynamic_cast<StraightStreet*>(streetArray[fieldPosition.x()][fieldPosition.y()+1]))->getDirection() == DOWN)
            return;

        newStreetElement = streetElement->clone();
        streetArray[fieldPosition.x()][fieldPosition.y()] = newStreetElement;
        streetArray[fieldPosition.x()][fieldPosition.y()+1] = newStreetElement;
        break;
    case Direction::LEFT: case Direction::RIGHT:
        fieldPosition.setX(fmin((eventPosition.x()/(FIELD_WIDTH/2)-1)/2, NUMBER_OF_HORIZONTAL_FIELDS-2));
        fieldPosition.setY(eventPosition.y()/FIELD_HEIGHT);

        if ((!dynamic_cast<StraightStreet*>(streetArray[fieldPosition.x()][fieldPosition.y()])) ||
            (!dynamic_cast<StraightStreet*>(streetArray[fieldPosition.x()+1][fieldPosition.y()])) ||
            (dynamic_cast<PedestrianCrossing*>(streetArray[fieldPosition.x()][fieldPosition.y()])) ||
            (dynamic_cast<PedestrianCrossing*>(streetArray[fieldPosition.x()+1][fieldPosition.y()])))
            return;
        else if ((dynamic_cast<StraightStreet*>(streetArray[fieldPosition.x()][fieldPosition.y()]))->getDirection() == LEFT ||
            (dynamic_cast<StraightStreet*>(streetArray[fieldPosition.x()][fieldPosition.y()]))->getDirection() == RIGHT ||
            (dynamic_cast<StraightStreet*>(streetArray[fieldPosition.x()+1][fieldPosition.y()]))->getDirection() == LEFT ||
            (dynamic_cast<StraightStreet*>(streetArray[fieldPosition.x()+1][fieldPosition.y()]))->getDirection() == RIGHT)
            return ;

        newStreetElement = streetElement->clone();
        streetArray[fieldPosition.x()][fieldPosition.y()] = newStreetElement;
        streetArray[fieldPosition.x()+1][fieldPosition.y()] = newStreetElement;
        break;
    case Direction::NONE:
        return;
    }

    newStreetElement->setZValue(1);
    newStreetElement->setPixmap(pixmap);
    newStreetElement->setPos(QPoint(FIELD_WIDTH*fieldPosition.x(), FIELD_HEIGHT*fieldPosition.y()));
    streetElements.push_back(newStreetElement);
    scene->addItem(newStreetElement);
}

void Controller::add_2x2_element(StreetElement *streetElement, const QPixmap& pixmap, const QPoint& eventPosition)
{   // coordinates of city elements are in the numbers of 2D board squares, instead of in pixels
    QPoint fieldPosition;
    StreetElement *newStreetElement;

    fieldPosition.setX(fmin((eventPosition.x()/(FIELD_WIDTH/2)-1)/2, NUMBER_OF_HORIZONTAL_FIELDS-2));
    fieldPosition.setY(fmin((eventPosition.y()/(FIELD_HEIGHT/2)-1)/2, NUMBER_OF_VERTICAL_FIELDS-2));

    if (streetArray[fieldPosition.x()][fieldPosition.y()] != nullptr ||
        streetArray[fieldPosition.x()][fieldPosition.y()+1] != nullptr ||
        streetArray[fieldPosition.x()+1][fieldPosition.y()] != nullptr ||
        streetArray[fieldPosition.x()+1][fieldPosition.y()+1] != nullptr)
        return ;

    if(fieldPosition.x() % 2 == 1 || fieldPosition.y() % 2 == 1)
        return;

    newStreetElement = streetElement->clone();
    newStreetElement->setPixmap(pixmap);
    newStreetElement->setZValue(0);
    newStreetElement->setPos(QPoint(FIELD_WIDTH*fieldPosition.x(), FIELD_HEIGHT*fieldPosition.y()));
    streetElements.push_back(newStreetElement);
    scene->addItem(newStreetElement);

    streetArray[fieldPosition.x()][fieldPosition.y()] = newStreetElement;
    streetArray[fieldPosition.x()][fieldPosition.y()+1] = newStreetElement;
    streetArray[fieldPosition.x()+1][fieldPosition.y()] = newStreetElement;
    streetArray[fieldPosition.x()+1][fieldPosition.y()+1] = newStreetElement;
}

void Controller::addNewPoint(const PointType& pointType, const QPoint& eventPosition)
{   // coordinates of points in the numbers of 2D board squares, instead of in pixels
    QPoint fieldPosition(eventPosition.x()/FIELD_WIDTH, eventPosition.y()/FIELD_HEIGHT);
    QGraphicsEllipseItem *newPoint;
    QColor pointColor;

    if(pointType == PointType::NONE)
        return;

    StreetElement *tmpStreetElement = streetArray[fieldPosition.x()][fieldPosition.y()];
    if((pointType == PointType::VEHICLE_END_POINT || pointType == PointType::VEHICLE_START_POINT) && (tmpStreetElement->getDirection() == Direction::LEFT || tmpStreetElement->getDirection() == Direction::RIGHT)){
        if((fieldPosition.x() % 2 == 0 && fieldPosition.y() % 2 == 0) ||
                (fieldPosition.x() % 2 == 1 && fieldPosition.y() % 2 == 1))
            return;
    }

    if((pointType == PointType::VEHICLE_END_POINT || pointType == PointType::VEHICLE_START_POINT) && (tmpStreetElement->getDirection() == Direction::UP || tmpStreetElement->getDirection() == Direction::DOWN)){
        if((fieldPosition.x() % 2 == 0 && fieldPosition.y() % 2 == 1) ||
                (fieldPosition.x() % 2 == 1 && fieldPosition.y() % 2 == 0))
            return;
    }

    switch(pointType)
    {
    case PointType::VEHICLE_START_POINT:
        pointColor = Qt::green;
        break;
    case PointType::VEHICLE_END_POINT:
        pointColor = Qt::red;
        break;
    case PointType::PEDESTRIAN_START_POINT:
        pointColor = Qt::yellow;
        break;
    case PointType::PEDESTRIAN_END_POINT:
        pointColor = Qt::blue;
        break;
    case PointType::NONE:
        break;
    }

    if(pointsArray[fieldPosition.x()][fieldPosition.y()] != nullptr)
    {
        QGraphicsItem *point = pointsArray[fieldPosition.x()][fieldPosition.y()];
        points.erase(std::find(points.begin(), points.end(), (QGraphicsEllipseItem*) point));
        scene->removeItem(point);
        delete point;
    }

    newPoint = new QGraphicsEllipseItem(0, 0, FIELD_WIDTH-1, FIELD_HEIGHT-1);
    newPoint->setBrush(QBrush(pointColor));
    newPoint->setZValue(5);
    newPoint->setPos(FIELD_WIDTH*fieldPosition.x(), FIELD_HEIGHT*fieldPosition.y());
    points.push_back(newPoint);
    scene->addItem(newPoint);
    pointsArray[fieldPosition.x()][fieldPosition.y()] = newPoint;
}

void Controller::createDefaultCity()
{
    QTransform transform;
    transform = transform.rotate(90);
    StreetElement *streetElement;

    clearBoard();

    streetElement = new StraightStreet(QPointF(0, 0), Direction::UP, StraightStreetPixmap);

    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(11*FIELD_WIDTH, 11*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(11*FIELD_WIDTH, 19*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(17*FIELD_WIDTH, 11*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(17*FIELD_WIDTH, 19*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(23*FIELD_WIDTH, 11*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(23*FIELD_WIDTH, 19*FIELD_HEIGHT));

    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(15*FIELD_WIDTH, 1*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(15*FIELD_WIDTH, 3*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(15*FIELD_WIDTH, 5*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(15*FIELD_WIDTH, 7*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(15*FIELD_WIDTH, 23*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(15*FIELD_WIDTH, 25*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(15*FIELD_WIDTH, 27*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(15*FIELD_WIDTH, 29*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(15*FIELD_WIDTH, 31*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(19*FIELD_WIDTH, 1*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(19*FIELD_WIDTH, 3*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(19*FIELD_WIDTH, 5*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(19*FIELD_WIDTH, 7*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(19*FIELD_WIDTH, 23*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(19*FIELD_WIDTH, 25*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(19*FIELD_WIDTH, 27*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(19*FIELD_WIDTH, 29*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(19*FIELD_WIDTH, 31*FIELD_HEIGHT));

    streetElement->setDirection(Direction::RIGHT);
    streetElement->setPixmap(QPixmap(streetElement->pixmap().transformed(transform)));

    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(13*FIELD_WIDTH, 9*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(21*FIELD_WIDTH, 9*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(13*FIELD_WIDTH, 15*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(21*FIELD_WIDTH, 15*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(13*FIELD_WIDTH, 21*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(21*FIELD_WIDTH, 21*FIELD_HEIGHT));

    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(1*FIELD_WIDTH, 13*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(3*FIELD_WIDTH, 13*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(5*FIELD_WIDTH, 13*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(7*FIELD_WIDTH, 13*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(9*FIELD_WIDTH, 13*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(25*FIELD_WIDTH, 13*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(27*FIELD_WIDTH, 13*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(29*FIELD_WIDTH, 13*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(31*FIELD_WIDTH, 13*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(1*FIELD_WIDTH, 17*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(3*FIELD_WIDTH, 17*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(5*FIELD_WIDTH, 17*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(7*FIELD_WIDTH, 17*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(9*FIELD_WIDTH, 17*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(25*FIELD_WIDTH, 17*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(27*FIELD_WIDTH, 17*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(29*FIELD_WIDTH, 17*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(31*FIELD_WIDTH, 17*FIELD_HEIGHT));

    delete streetElement;

    streetElement = new DivisionStreet(QPointF(0, 0), Direction::UP, DivisionStreetPixmap);

    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(17*FIELD_WIDTH, 9*FIELD_HEIGHT));

    streetElement->setDirection(Direction::RIGHT);
    streetElement->setPixmap(QPixmap(streetElement->pixmap().transformed(transform)));

    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(23*FIELD_WIDTH, 15*FIELD_HEIGHT));

    streetElement->setDirection(Direction::DOWN);
    streetElement->setPixmap(QPixmap(streetElement->pixmap().transformed(transform)));

    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(17*FIELD_WIDTH, 21*FIELD_HEIGHT));

    streetElement->setDirection(Direction::LEFT);
    streetElement->setPixmap(QPixmap(streetElement->pixmap().transformed(transform)));

    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(11*FIELD_WIDTH, 15*FIELD_HEIGHT));

    delete streetElement;

    streetElement = new CrossingStreet(QPointF(0, 0), Direction::UP, CrossingPixmap);

    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(15*FIELD_WIDTH, 15*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(19*FIELD_WIDTH, 15*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(17*FIELD_WIDTH, 13*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(17*FIELD_WIDTH, 17*FIELD_HEIGHT));

    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(11*FIELD_WIDTH, 13*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(11*FIELD_WIDTH, 17*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(23*FIELD_WIDTH, 13*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(23*FIELD_WIDTH, 17*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(15*FIELD_WIDTH, 9*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(19*FIELD_WIDTH, 9*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(15*FIELD_WIDTH, 21*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(19*FIELD_WIDTH, 21*FIELD_HEIGHT));

    delete streetElement;

    streetElement = new TurnStreet(QPointF(0, 0), Direction::UP, TurnStreetPixmap);

    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(11*FIELD_WIDTH, 9*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(15*FIELD_WIDTH, 13*FIELD_HEIGHT));

    streetElement->setDirection(Direction::RIGHT);
    streetElement->setPixmap(QPixmap(streetElement->pixmap().transformed(transform)));

    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(23*FIELD_WIDTH, 9*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(19*FIELD_WIDTH, 13*FIELD_HEIGHT));

    streetElement->setDirection(Direction::DOWN);
    streetElement->setPixmap(QPixmap(streetElement->pixmap().transformed(transform)));

    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(23*FIELD_WIDTH, 21*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(19*FIELD_WIDTH, 17*FIELD_HEIGHT));

    streetElement->setDirection(Direction::LEFT);
    streetElement->setPixmap(QPixmap(streetElement->pixmap().transformed(transform)));

    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(11*FIELD_WIDTH, 21*FIELD_HEIGHT));
    add_2x2_element(streetElement, streetElement->pixmap(), QPoint(15*FIELD_WIDTH, 17*FIELD_HEIGHT));

    delete streetElement;

    streetElement = new Pavement(QPointF(0, 0), Direction::UP, PavementPixmap);

    for(unsigned int i = 0; i < 18; i++)
        for(unsigned int j = 0; j < 18; j++)
            add_1x1_element(streetElement, streetElement->pixmap(), QPoint((8+i)*FIELD_WIDTH, (6+j)*FIELD_HEIGHT));

    delete streetElement;

    streetElement = new PedestrianCrossing(QPointF(0, 0), Direction::UP, PedestrianCrossingPixmap);

    add_1x2_element(streetElement, streetElement->pixmap(), QPoint(12*FIELD_WIDTH, 15*FIELD_HEIGHT));
    add_1x2_element(streetElement, streetElement->pixmap(), QPoint(13*FIELD_WIDTH, 15*FIELD_HEIGHT));
    add_1x2_element(streetElement, streetElement->pixmap(), QPoint(20*FIELD_WIDTH, 15*FIELD_HEIGHT));
    add_1x2_element(streetElement, streetElement->pixmap(), QPoint(21*FIELD_WIDTH, 15*FIELD_HEIGHT));
    add_1x2_element(streetElement, streetElement->pixmap(), QPoint(12*FIELD_WIDTH, 9*FIELD_HEIGHT));
    add_1x2_element(streetElement, streetElement->pixmap(), QPoint(21*FIELD_WIDTH, 9*FIELD_HEIGHT));
    add_1x2_element(streetElement, streetElement->pixmap(), QPoint(12*FIELD_WIDTH, 21*FIELD_HEIGHT));
    add_1x2_element(streetElement, streetElement->pixmap(), QPoint(21*FIELD_WIDTH, 21*FIELD_HEIGHT));

    add_1x2_element(streetElement, streetElement->pixmap(), QPoint(8*FIELD_WIDTH, 13*FIELD_HEIGHT));
    add_1x2_element(streetElement, streetElement->pixmap(), QPoint(9*FIELD_WIDTH, 13*FIELD_HEIGHT));
    add_1x2_element(streetElement, streetElement->pixmap(), QPoint(24*FIELD_WIDTH, 13*FIELD_HEIGHT));
    add_1x2_element(streetElement, streetElement->pixmap(), QPoint(25*FIELD_WIDTH, 13*FIELD_HEIGHT));
    add_1x2_element(streetElement, streetElement->pixmap(), QPoint(8*FIELD_WIDTH, 17*FIELD_HEIGHT));
    add_1x2_element(streetElement, streetElement->pixmap(), QPoint(9*FIELD_WIDTH, 17*FIELD_HEIGHT));
    add_1x2_element(streetElement, streetElement->pixmap(), QPoint(24*FIELD_WIDTH, 17*FIELD_HEIGHT));
    add_1x2_element(streetElement, streetElement->pixmap(), QPoint(25*FIELD_WIDTH, 17*FIELD_HEIGHT));

    streetElement->setDirection(Direction::RIGHT);
    streetElement->setPixmap(QPixmap(streetElement->pixmap().transformed(transform)));

    add_1x2_element(streetElement, streetElement->pixmap(), QPoint(11*FIELD_WIDTH, 10*FIELD_HEIGHT));
    add_1x2_element(streetElement, streetElement->pixmap(), QPoint(11*FIELD_WIDTH, 19*FIELD_HEIGHT));
    add_1x2_element(streetElement, streetElement->pixmap(), QPoint(23*FIELD_WIDTH, 10*FIELD_HEIGHT));
    add_1x2_element(streetElement, streetElement->pixmap(), QPoint(23*FIELD_WIDTH, 19*FIELD_HEIGHT));
    add_1x2_element(streetElement, streetElement->pixmap(), QPoint(17*FIELD_WIDTH, 10*FIELD_HEIGHT));
    add_1x2_element(streetElement, streetElement->pixmap(), QPoint(17*FIELD_WIDTH, 11*FIELD_HEIGHT));
    add_1x2_element(streetElement, streetElement->pixmap(), QPoint(17*FIELD_WIDTH, 18*FIELD_HEIGHT));
    add_1x2_element(streetElement, streetElement->pixmap(), QPoint(17*FIELD_WIDTH, 19*FIELD_HEIGHT));

    add_1x2_element(streetElement, streetElement->pixmap(), QPoint(15*FIELD_WIDTH, 6*FIELD_HEIGHT));
    add_1x2_element(streetElement, streetElement->pixmap(), QPoint(15*FIELD_WIDTH, 7*FIELD_HEIGHT));
    add_1x2_element(streetElement, streetElement->pixmap(), QPoint(15*FIELD_WIDTH, 22*FIELD_HEIGHT));
    add_1x2_element(streetElement, streetElement->pixmap(), QPoint(15*FIELD_WIDTH, 23*FIELD_HEIGHT));
    add_1x2_element(streetElement, streetElement->pixmap(), QPoint(19*FIELD_WIDTH, 7*FIELD_HEIGHT));
    add_1x2_element(streetElement, streetElement->pixmap(), QPoint(19*FIELD_WIDTH, 23*FIELD_HEIGHT));
    add_1x2_element(streetElement, streetElement->pixmap(), QPoint(19*FIELD_WIDTH, 6*FIELD_HEIGHT));
    add_1x2_element(streetElement, streetElement->pixmap(), QPoint(19*FIELD_WIDTH, 22*FIELD_HEIGHT));

    delete streetElement;

    streetElement = new Camera(QPointF(0, 0), Direction::UP, cameraPixmap);

    add_1x1_element(streetElement, streetElement->pixmap(), QPoint(20*FIELD_WIDTH, 24*FIELD_HEIGHT));
    add_1x1_element(streetElement, streetElement->pixmap(), QPoint(12*FIELD_WIDTH, 24*FIELD_HEIGHT));

    streetElement->setDirection(Direction::RIGHT);
    streetElement->setPixmap(QPixmap(streetElement->pixmap().transformed(transform)));

    add_1x1_element(streetElement, streetElement->pixmap(), QPoint(8*FIELD_WIDTH, 10*FIELD_HEIGHT));
    add_1x1_element(streetElement, streetElement->pixmap(), QPoint(8*FIELD_WIDTH, 20*FIELD_HEIGHT));

    streetElement->setDirection(Direction::DOWN);
    streetElement->setPixmap(QPixmap(streetElement->pixmap().transformed(transform)));

    add_1x1_element(streetElement, streetElement->pixmap(), QPoint(20*FIELD_WIDTH, 6*FIELD_HEIGHT));
    add_1x1_element(streetElement, streetElement->pixmap(), QPoint(12*FIELD_WIDTH, 6*FIELD_HEIGHT));

    streetElement->setDirection(Direction::LEFT);
    streetElement->setPixmap(QPixmap(streetElement->pixmap().transformed(transform)));

    add_1x1_element(streetElement, streetElement->pixmap(), QPoint(26*FIELD_WIDTH, 10*FIELD_HEIGHT));
    add_1x1_element(streetElement, streetElement->pixmap(), QPoint(26*FIELD_WIDTH, 20*FIELD_HEIGHT));

    add_1x1_element(streetElement, streetElement->pixmap(), QPoint(17*FIELD_WIDTH, 14*FIELD_HEIGHT));

    delete streetElement;

    addNewPoint(PointType::VEHICLE_START_POINT, QPoint(14*FIELD_WIDTH, 0*FIELD_HEIGHT));
    addNewPoint(PointType::VEHICLE_START_POINT, QPoint(15*FIELD_WIDTH, 31*FIELD_HEIGHT));
    addNewPoint(PointType::VEHICLE_START_POINT, QPoint(18*FIELD_WIDTH, 0*FIELD_HEIGHT));
    addNewPoint(PointType::VEHICLE_START_POINT, QPoint(19*FIELD_WIDTH, 31*FIELD_HEIGHT));
    addNewPoint(PointType::VEHICLE_START_POINT, QPoint(0*FIELD_WIDTH, 13*FIELD_HEIGHT));
    addNewPoint(PointType::VEHICLE_START_POINT, QPoint(31*FIELD_WIDTH, 12*FIELD_HEIGHT));
    addNewPoint(PointType::VEHICLE_START_POINT, QPoint(0*FIELD_WIDTH, 17*FIELD_HEIGHT));
    addNewPoint(PointType::VEHICLE_START_POINT, QPoint(31*FIELD_WIDTH, 16*FIELD_HEIGHT));

    addNewPoint(PointType::VEHICLE_END_POINT, QPoint(15*FIELD_WIDTH, 1*FIELD_HEIGHT));
    addNewPoint(PointType::VEHICLE_END_POINT, QPoint(14*FIELD_WIDTH, 30*FIELD_HEIGHT));
    addNewPoint(PointType::VEHICLE_END_POINT, QPoint(19*FIELD_WIDTH, 1*FIELD_HEIGHT));
    addNewPoint(PointType::VEHICLE_END_POINT, QPoint(18*FIELD_WIDTH, 30*FIELD_HEIGHT));
    addNewPoint(PointType::VEHICLE_END_POINT, QPoint(1*FIELD_WIDTH, 12*FIELD_HEIGHT));
    addNewPoint(PointType::VEHICLE_END_POINT, QPoint(30*FIELD_WIDTH, 13*FIELD_HEIGHT));
    addNewPoint(PointType::VEHICLE_END_POINT, QPoint(1*FIELD_WIDTH, 16*FIELD_HEIGHT));
    addNewPoint(PointType::VEHICLE_END_POINT, QPoint(30*FIELD_WIDTH, 17*FIELD_HEIGHT));

    addNewPoint(PointType::PEDESTRIAN_START_POINT, QPoint(8*FIELD_WIDTH, 6*FIELD_HEIGHT));
    addNewPoint(PointType::PEDESTRIAN_START_POINT, QPoint(25*FIELD_WIDTH, 23*FIELD_HEIGHT));
    addNewPoint(PointType::PEDESTRIAN_END_POINT, QPoint(25*FIELD_WIDTH, 6*FIELD_HEIGHT));
    addNewPoint(PointType::PEDESTRIAN_END_POINT, QPoint(8*FIELD_WIDTH, 23*FIELD_HEIGHT));
}

void Controller::changeSimulationSpeed(int index)
{
    switch(index)
    {
    case 0:
        simulationSpeed = 0.5;
        break;
    case 1:
        simulationSpeed = 1.0;
        break;
    case 2:
        simulationSpeed = 2.0;
        break;
    case 3:
        simulationSpeed = 4.0;
        break;
    case 4:
        simulationSpeed = 5.0;
        break;
    }

    animationTimer.start(((float) ANIMATION_TIMER_INTERVAL) / simulationSpeed);
    realTimer.start((float) REAL_TIMER_INTERVAL / simulationSpeed);
}

void Controller::setMaxNumberOfCars()
{
    maxNumberOfCars = mainWindow.ui->carNumberLineEdit->text().toInt();
}

void Controller::setMaxNumberOfPedestrians()
{
    maxNumberOfPedestrians = mainWindow.ui->pedestrianNumberLineEdit->text().toInt();
}

void Controller::setCurrentTimeForClock()
{
    clock = QTime::currentTime();
    mainWindow.updateLCDClock(clock);
}

void Controller::addOneSecondToClock()
{
    clock = clock.addSecs(1);
    mainWindow.updateLCDClock(clock);
}

void Controller::setCameraToDisplay(Camera *camera)
{
    cameraForTextField = camera;
    mainWindow.clearCameraObservationTextEdit();
}

void Controller::cameraObservationForTextField()
{
    if(cameraForTextField != nullptr)
        mainWindow.setCameraObservationTextEdit(cameraForTextField->observeToTextField(pedestrians, cars, clock));
}

void Controller::selectStreetElement(StreetElement* streetElement)
{
    selectedStreetElement = streetElement;
}

void Controller::currentPointTypeChanged(PointType pointType)
{
    currentPointType = pointType;
}
