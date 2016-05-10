#ifndef _PauseMenu_H_
#define _PauseMenu_H_
#include "cocos2d.h"
#include "StartMenu.h"
#include "HelloWorldScene.h"
USING_NS_CC;
class MyMenu:public Layer
{
public:
	static Scene* create_scene(RenderTexture *capture);
	virtual bool init();
	void set_pauseMenu_position(float width,float height);
	Size get_pauseMenu_position();
	void Menu_resume(Ref *p);
	void Menu_menu(Ref *p);
	void goMenu(Ref *p);
	CREATE_FUNC(MyMenu);
private:
	Size pauseMenu_position;
};

#endif