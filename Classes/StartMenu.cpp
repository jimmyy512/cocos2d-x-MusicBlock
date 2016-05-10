#include "StartMenu.h"
#include "HelloWorldScene.h"
#include "ChooseStage.h"
Scene* StartMenu::create_scene()
{
	auto s = Scene::create();
	auto l = StartMenu::create();
	s->addChild(l);
	return s;
}
bool StartMenu::init()
{
	Layer::init();
	visible = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	Sprite *startGameBackground = Sprite::create("main_scene.png");
	startGameBackground->setPosition(visible.width / 2 + origin.width, visible.height / 2 + origin.height);
	startGameBackground->setOpacity(200);
	addChild(startGameBackground,0);

	Sprite *audioItem = Sprite::create("item_audio.png");
	audioItem->setOpacity(100);
	audioItem->setScale(1.1f);
	audioItem->setPosition(visible.width / 2 + origin.width, audioItem->getContentSize().height / 2); 
	addChild(audioItem);

	auto Title = Sprite::create("Title.png");
	Title->setPosition(visible.width / 2 + origin.width, visible.height * 8 / 10+origin.height);
	addChild(Title);

	auto StartGame = Sprite::create("StartGame.png");
	StartGame->setPosition(Title->getPositionX(), visible.height * 6 / 10 + origin.height);
	addChild(StartGame);

	auto ExitGame = Sprite::create("ExitGame.png");
	ExitGame->setPosition(Title->getPositionX(), visible.height * 4 / 10 + origin.height);
	addChild(ExitGame);

	auto Created = Label::create();
	Created->setTextColor(Color4B(99,87,255,255));
	Created->setString("Created By Majioo"); 
	Created->setSystemFontSize(25);
	Created->setPosition(visible.width-Created->getContentSize().width/2+origin.width,
						visible.height-Created->getContentSize().height/2+origin.height);
	addChild(Created);

	auto StartGameListener = EventListenerTouchOneByOne::create();
	StartGameListener->onTouchBegan = [](Touch*t, Event*e)
	{
		if (e->getCurrentTarget()->getBoundingBox().containsPoint(t->getLocation()))
		{
			Director::getInstance()->replaceScene(ChooseStage::create_scene());
		}
		return false;
	};

	auto ExitGameListener = EventListenerTouchOneByOne::create();
	ExitGameListener->onTouchBegan = [](Touch*t, Event*e)
	{
		if (e->getCurrentTarget()->getBoundingBox().containsPoint(t->getLocation()))
		{
			Director::getInstance()->end();
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(ExitGameListener, ExitGame);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(StartGameListener, StartGame);
	return true;
}