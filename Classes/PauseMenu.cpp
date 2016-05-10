#include "PauseMenu.h"
Scene* MyMenu::create_scene(RenderTexture *capture)
{
	Size visible = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto scene = Scene::create();
	auto layer = MyMenu::create(); 
	scene->addChild(layer,1);
	//­I´º
	auto pause_background = Sprite::createWithTexture(capture->getSprite()->getTexture());
	pause_background->setColor(Color3B::GRAY);
	pause_background->setFlipY(true);
	pause_background->setPosition(Vec2(visible.width/2+origin.x, visible.height/2+origin.y));
	scene->addChild(pause_background);

	auto pause_menu = Sprite::create("pause_main.png");
	pause_menu->setPosition(visible.width / 2 + origin.x, visible.height / 2 + origin.y);
	pause_menu->setScale(0.5);
	scene->addChild(pause_menu);
	return scene;
}
bool MyMenu::init()
{
	Layer::init();
	//¼È°±µæ³æ
	Size visible = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto resume = MenuItemImage::create("pause_resume.png","pause_resume.png",CC_CALLBACK_1(MyMenu::Menu_resume,this));
	resume->setPosition(visible.width / 2 + origin.x, visible.height*5 /10  + origin.y);
	resume->setScale(0.5);

	auto gomenu = MenuItemImage::create("pause_menu.png", "pause_menu.png", CC_CALLBACK_1(MyMenu::Menu_menu, this));
	gomenu->setPosition(visible.width / 2 + origin.x, visible.height *4 / 10 + origin.y);
	gomenu->setScale(0.5);

	auto pause_menu = Menu::create(resume,gomenu,NULL);
	pause_menu->setAnchorPoint(Vec2(0, 0));
	pause_menu->setPosition(0,0);
	addChild(pause_menu);
	return true;
}
void MyMenu::Menu_menu(Ref* p)
{
	HelloWorld::setPauseReplace(true);
	Director::getInstance()->popScene();
}
void MyMenu::Menu_resume(Ref *p)
{
	Director::getInstance()->popScene();
}
void MyMenu::set_pauseMenu_position(float width, float height)
{
	pauseMenu_position.width = width;
	pauseMenu_position.height = height;
}
Size MyMenu::get_pauseMenu_position()
{
	return pauseMenu_position;
}