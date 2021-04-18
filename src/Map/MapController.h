#pragma once

#include "../GameObservers.h"
#include "Map.h"

class MapController {
private:
    MapObserver *mapView;
    Map *mapModel;

public:
    MapController(MapObserver *newView, Map *newModel);

    void ControlMap();
};
