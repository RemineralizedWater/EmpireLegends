#include "MapController.h"

MapController::MapController(MapObserver *newView, Map *newModel) {
    mapView = newView;
    mapModel = newModel;
}

void MapController::ControlMap() {
    mapModel->Display();
}
