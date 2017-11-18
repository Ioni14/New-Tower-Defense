#pragma once

#include "Component.h"
#include <vector>

struct Waypoint;

class WaypointComponent :
    public Component
{
public:
    WaypointComponent();
    ~WaypointComponent();

    inline Type getType() const {
        return Type::WAYPOINT;
    }

public:
    std::vector<Waypoint>::size_type mCurrentIndex;
    std::vector<Waypoint>::size_type mPreviousIndex;
};
