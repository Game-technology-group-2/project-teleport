#ifndef PROJECT_TELEPORT_HELPERS_H
#define PROJECT_TELEPORT_HELPERS_H

namespace Helpers {
    enum class Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    enum class Rotation {
        YAW,
        PITCH,
        ROLL
    };
}

#endif //PROJECT_TELEPORT_HELPERS_H
