#include "ChooseStage.h"
using namespace ui;
Scene* ChooseStage::create_scene()
{
	auto s = Scene::create();
	auto l = ChooseStage::create();
	s->addChild(l);
	return s;
}
bool ChooseStage::init()
{
	Layer::init();
	visible = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	auto ChooseStageBackground = Sprite::create("ChooseStage.png");
	ChooseStageBackground->setPosition(visible.width / 2 + origin.width, visible.height / 2 + origin.height);
	ChooseStageBackground->setOpacity(150);
	addChild(ChooseStageBackground,0);

	auto in_the_end = Sprite::create("in_the_end_photo.png");
	in_the_end->setPosition(visible.width *2/10 + origin.width, visible.height * 6 / 10);
	in_the_end->setScale(0.5);
	addChild(in_the_end);
	auto in_the_end_Label = Label::createWithTTF("In the end", "fonts/ARDESTINE.ttf", 28);
	in_the_end_Label->setPosition(in_the_end->getPositionX() + visible.width * 5 / 10 + origin.width, in_the_end->getPositionY());
	addChild(in_the_end_Label);

	/*auto Man_enough = Sprite::create("Man_enough_photo.png");
	Man_enough->setPosition(visible.width * 2/10 + origin.width, visible.height * 5 / 10);
	Man_enough->setScale(0.5);
	addChild(Man_enough);
	auto Man_enough_Label = Label::createWithTTF("Man enough", "fonts/ARDESTINE.ttf", 28);
	Man_enough_Label->setPosition(Man_enough->getPositionX() + visible.width * 5 / 10 + origin.width, Man_enough->getPositionY());
	addChild(Man_enough_Label);*/

	auto frankmusik = Sprite::create("frankmusik_photo.png");
	frankmusik->setPosition(visible.width * 2/10 + origin.width, visible.height * 4 / 10);
	frankmusik->setScale(0.5);
	addChild(frankmusik);
	auto frankmusik_Label = Label::createWithTTF("Frankmusik", "fonts/ARDESTINE.ttf", 28);
	frankmusik_Label->setPosition(frankmusik->getPositionX() + visible.width * 5 / 10 + origin.width, frankmusik->getPositionY());
	addChild(frankmusik_Label);

	auto in_the_endListener = EventListenerTouchOneByOne::create();
	in_the_endListener->onTouchBegan = [in_the_end_Label](Touch* t, Event*e)
	{
		if (e->getCurrentTarget()->getBoundingBox().containsPoint(t->getLocation())||
			in_the_end_Label->getBoundingBox().containsPoint(t->getLocation()))
		{
			Director::getInstance()->replaceScene(HelloWorld::createScene("in_the_end"));
		}
		return false;
	};
	/*auto ManEnoughListener = EventListenerTouchOneByOne::create();
	ManEnoughListener->onTouchBegan = [Man_enough_Label](Touch* t, Event* e)
	{
		if (e->getCurrentTarget()->getBoundingBox().containsPoint(t->getLocation())||
			Man_enough_Label->getBoundingBox().containsPoint(t->getLocation()))
		{
			Director::getInstance()->replaceScene(HelloWorld::createScene("Man_Enough"));
		}
		return false;
	};*/
	auto Frank_MusikListener = EventListenerTouchOneByOne::create();
	Frank_MusikListener->onTouchBegan = [frankmusik_Label](Touch* t, Event* e)
	{
		if (e->getCurrentTarget()->getBoundingBox().containsPoint(t->getLocation()) ||
			frankmusik_Label->getBoundingBox().containsPoint(t->getLocation()))
		{
			Director::getInstance()->replaceScene(HelloWorld::createScene("Frank_Musik"));
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(in_the_endListener, in_the_end);
	/*Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(ManEnoughListener, Man_enough);*/
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(Frank_MusikListener, frankmusik);
	return true;
}