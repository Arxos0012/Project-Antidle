#ifndef OBJECT_H
#define OBJECT_H

#include "entity.h"

class Object : public Entity{
public:
	Object(int x, int y, int w, int h, int screenWidth, int screenHeight, std::string name = "generic object") : Entity(x,y,w,h,screenWidth,screenHeight,name){}
private:
};

#endif