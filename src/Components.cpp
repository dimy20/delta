#include <raymath.h>

typedef unsigned int EntityId;

struct Transform{
    Vector3 position;
    Vector3 scale;
    Vector3 rotationAxis;
    float rotationAngle;
    EntityId entityId;
};

#define MAX_COMPONENTS 1024

namespace Components{
    Transform transforms[MAX_COMPONENTS];
};
