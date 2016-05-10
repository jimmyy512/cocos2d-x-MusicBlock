#ifndef _StartMenu_H_
#define _StartMenu_H_
#include "cocos2d.h"
USING_NS_CC;
class StartMenu:public Layer
{
public:
	static Scene* create_scene();
	virtual bool init();
	CREATE_FUNC(StartMenu);
private:
	Size visible;
	Size origin;
};




#endif