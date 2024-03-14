//#include <bullet/BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>
#include <bullet/btBulletCollisionCommon.h>

btDefaultCollisionConfiguration * collisionConfig;
btCollisionDispatcher * dispatcher;

void init(){
    collisionConfig = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfig);
};

void quit(){
    delete collisionConfig;
    delete dispatcher;
};

