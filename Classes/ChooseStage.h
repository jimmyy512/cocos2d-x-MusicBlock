#ifndef _ChooseStage_H_
#define _ChooseStage_H_
#include "cocos2d.h"
#include "ui\UIScrollView.h"
#include "ui\UIButton.h"
#include "HelloWorldScene.h"
USING_NS_CC;
class ChooseStage :public Layer
{
public:
	static Scene * create_scene();
	virtual bool init();
	CREATE_FUNC(ChooseStage);
private:
	Size visible;
	Size origin;
};
#endif