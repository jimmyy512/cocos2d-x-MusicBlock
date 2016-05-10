#ifndef _Gameover_H_
#define _Gameover_H_
#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "StartMenu.h"
USING_NS_CC;
static int total_score;
class Gameover :public LayerColor
{
public:
	std::string NowStageMusic;
public:
	static Gameover* create(std::string StageMusic)
	{ 
		Gameover *pRet = new(std::nothrow) Gameover(); 
		if (pRet && pRet->init(StageMusic))
		{ 
			pRet->autorelease(); 
			return pRet; 
		} 
		else 
		{ 
			delete pRet; 
			pRet = nullptr; 
			return nullptr; 
		} 
	}
	static Scene* create_scene(int score,std::string StageMusic)
	{
		total_score = score;
		auto s = Scene::create();
		auto l = Gameover::create(StageMusic);
		l->NowStageMusic = StageMusic;
		s->addChild(l);
		return s;
	}
	virtual bool init(std::string StageMusic)
	{
		LayerColor::init();
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		auto visible_size = Director::getInstance()->getVisibleSize();
		auto origin_size = Director::getInstance()->getVisibleOrigin();
		auto EndGameBackGround = Sprite::create("EndGameBackGround.png");
		EndGameBackGround->setPosition(visible_size.width / 2 + origin_size.x, visible_size.height / 2 + origin_size.y);
		EndGameBackGround->setOpacity(180);
		addChild(EndGameBackGround,0);

		int highscore = UserDefault::getInstance()->getIntegerForKey(StageMusic.c_str());//count high score
		if (total_score > highscore)
		{
			UserDefault::getInstance()->setIntegerForKey(StageMusic.c_str(), total_score);
			highscore = total_score;
		}
		auto HighScoreLabel = Label::createWithTTF(StringUtils::format("High Score:%d", highscore), "fonts/Marker Felt.ttf", 30);
		HighScoreLabel->setPosition(Size((visible_size.width + origin_size.x) / 2, (visible_size.height + origin_size.y) * 8 / 10));
		addChild(HighScoreLabel, 1);

		auto scoreLabel = Label::createWithTTF(StringUtils::format("Your Score:%d", total_score), "fonts/Marker Felt.ttf", 30);
		scoreLabel->setPosition(Size((visible_size.width + origin_size.x) / 2, (visible_size.height + origin_size.y) * 6 / 10));
		//scoreLabel->setColor(Color3B(255,153,153));
		addChild(scoreLabel, 1);

		auto restart = Label::createWithTTF("Restart", "fonts/ARDESTINE.ttf", 30);
		restart->setPosition(Size((visible_size.width + origin_size.x) / 2, (visible_size.height + origin_size.y) * 4 / 10));
		restart->setColor(Color3B(222, 234, 244));
		addChild(restart,1);

		auto ReturnMenu = Label::createWithTTF("Return Menu", "fonts/ARDESTINE.ttf",30);
		ReturnMenu->setPosition(Size((visible_size.width + origin_size.x) / 2, (visible_size.height + origin_size.y) * 2 / 10));
		ReturnMenu->setColor(Color3B(222, 234, 244));
		addChild(ReturnMenu,1);

		auto restart_listener = EventListenerTouchOneByOne::create();
		restart_listener->onTouchBegan = [this](Touch* t, Event*e)
		{
			if (e->getCurrentTarget()->getBoundingBox().containsPoint(t->getLocation()))
				Director::getInstance()->replaceScene(HelloWorld::createScene(NowStageMusic));
			return false;
		};
		auto ReturnMenu_listener = EventListenerTouchOneByOne::create();
		ReturnMenu_listener->onTouchBegan = [](Touch* t, Event*e)
		{
			if (e->getCurrentTarget()->getBoundingBox().containsPoint(t->getLocation()))
			{
				Director::getInstance()->replaceScene(StartMenu::create_scene());
			}
			return false;
		};
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(restart_listener, restart);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(ReturnMenu_listener, ReturnMenu);
		return true;
	}
	//CREATE_FUNC(Gameover);
private:
};




#endif