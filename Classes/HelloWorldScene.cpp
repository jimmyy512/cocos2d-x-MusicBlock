#include "HelloWorldScene.h"
#include "Gameover.h"
#include "PauseMenu.h"

USING_NS_CC;
using namespace CocosDenshion;
bool HelloWorld::ispausereplace;
std::string ChooseTheNowStageMusic;
Scene* HelloWorld::createScene(std::string chooseMusic)
{
	ChooseTheNowStageMusic = chooseMusic;
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
	
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
// on "init" you need to initialize your instance
bool HelloWorld::init()//package="com.music_block.test"
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	srand(time(NULL));
	visible_size = Director::getInstance()->getVisibleSize();
	origin_size = Director::getInstance()->getVisibleOrigin();
	//init 


	gamelayer = Node::create();
	mallocTheMemoryToMusic1();
	initAllVariableToZero();
	auto perfect = Sprite::create("PERFECT.png");
	perfect->setPosition(visible_size.width*1/5+origin_size.width,visible_size.height-perfect->getContentSize().height/2+origin_size.height );
	addChild(perfect,4);
	auto miss = Sprite::create("miss.png");
	miss->setPosition(visible_size.width * 5 / 9 + origin_size.width, visible_size.height - miss->getContentSize().height / 2 + origin_size.height);
	addChild(miss, 4);

	perfectlabel = Label::create();
	perfectlabel->setColor(Color3B::WHITE);
	perfectlabel->setPosition(perfect->getPositionX()+perfect->getContentSize().width/2,perfect->getPositionY());
	perfectlabel->setString(StringUtils::format("%d",perfect_count));
	perfectlabel->setSystemFontSize(30);
	perfect->setScale(0.7);
	perfectlabel->setScale(0.5);
	addChild(perfectlabel, 4);
	
	misslabel = Label::create();
	misslabel->setColor(Color3B::RED);
	misslabel->setPosition(miss->getPositionX() + miss->getContentSize().width / 2, miss->getPositionY()-2);
	misslabel->setString(StringUtils::format("%d", miss_count));
	misslabel->setSystemFontSize(30);
	miss->setScale(0.7);
	misslabel->setScale(0.5);
	addChild(misslabel, 4);

	addChild(gamelayer, 3);//遊戲層
	start_game();
	//child 1, 2 between map layer and game layer
	//背景
	Director::getInstance()->getTextureCache()->addImage("background2.png");
	map1 = Sprite::create("background2.png");
	map2 = Sprite::create("background2.png");
	map1->setPosition(visible_size.width / 2 + origin_size.width, visible_size.height / 2 + origin_size.height);
	map1->setAnchorPoint(Vec2(0.5, 0.5));
	map2->setPosition(map1->getPositionX(), map1->getPositionY()+map2->getContentSize().height);
	map2->setAnchorPoint(Vec2(0.5, 0.5));
	
	addChild(map1, 0);
	addChild(map2, 0);
	//pause munu
	auto menuItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(HelloWorld::gamePause,this));
	menuItem->setPosition(Vec2((visible_size.width-menuItem->getContentSize().width/2)+origin_size.width,
								(visible_size.height-menuItem->getContentSize().height/2)+origin_size.height));
	
	auto menu = Menu::create(menuItem,NULL);
	menu->setAnchorPoint(Vec2(0,0));
	menu->setPosition(0, 0);
	addChild(menu,5);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch*t, Event*e)
	{
		if (touch_event(t, e))
		{
			addtouchParticle(t, e);
			addBackGroundParticle();
			perfect_count++;
		}
		return true;
	};
	listener->onTouchMoved = [this](Touch*t, Event*e)
	{
		if (touch_event(t, e))
		{
			addtouchParticle(t, e);
			addBackGroundParticle();
			perfect_count++;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}
void HelloWorld::update(float dt)
{
	map_update();
	perfectlabel->setString(StringUtils::format("%d", perfect_count));
	misslabel->setString(StringUtils::format("%d", miss_count));
	log("%d", sec);
	countPauseDivationTime();
	sec = (time(NULL) - start_time) - deviation;//deviation 時間暫停誤差値
	int rhythm = music1->get_speed(sec);//傳入目前歌曲秒速 回傳節奏速度
	static int count = rhythm;
	if (oldrhythm != rhythm)//如果節奏變換時
	{
		count = rhythm;
		oldrhythm = rhythm;
	}
	if (count == rhythm)
	{
		movedown();
		count = 0;
	}
	count++;
	if (checkPauseReplace())
	{
		this->TheEnd();
	}
}
void HelloWorld::addBackGroundParticle()
{
	auto particle = ParticleFire::create();
	particle->initWithFile("hit_particle.plist");
	particle->setPosition(visible_size.width / 2 + origin_size.width, visible_size.height / 2 + origin_size.height);
	particle->setAutoRemoveOnFinish(true);
	addChild(particle, 1);
}
void HelloWorld::addtouchParticle(Touch*t, Event*e)
{
	auto particle = ParticleFire::create();
	particle->initWithFile("particle.plist");
	particle->setPosition(t->getLocation().x, t->getLocation().y + 10);
	particle->setScale(0.5);
	particle->setAutoRemoveOnFinish(true);
	addChild(particle, 4);
}
void HelloWorld::map_update()
{
	map1->setPositionY(map1->getPositionY()-1);
	map2->setPositionY(map2->getPositionY()-1);
	judge_resetmap(map1);
	judge_resetmap(map2);
}
void HelloWorld::judge_resetmap(Sprite *map)
{
	if (map->getPositionY() == 0 - map->getContentSize().height / 2)
	{
		map->setPositionY(map->getPositionY() + 2 * (map->getContentSize().height));
	}
}
bool HelloWorld::touch_event(Touch*t, Event*e)
{
	Block* b;
	int check = 0;
	auto bs = Block::get_Blocks();
	
	for (auto it = bs->begin(); it != bs->end(); it++)
	{
		b = (*it);
		if (b->getBoundingBox().containsPoint(t->getLocation()))
		{
			if (music1->check_swing(sec))
			{
				this->runAction(Sequence::create(MoveBy::create(0.15, Vec2(5, 0)), MoveBy::create(0.3, Vec2(-10, 0)),
					MoveBy::create(0.15,Vec2(5,0)),NULL));
			}
			if (b->getColor() == Color3B::CustomPurple)
			{
				if (!isstart)
				{
					start_timer();
					isstart = true;
				}
				if (ismusicplay)
				{
					SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
				}
				if (!ismusicplay)
				{
					if (strcmp(ChooseTheNowStageMusic.c_str(), "in_the_end")==0)
					{
						SimpleAudioEngine::getInstance()->playBackgroundMusic("zero.mp3", true);
						SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
					}
					if (strcmp(ChooseTheNowStageMusic.c_str(), "Man_Enough") == 0)
					{
						SimpleAudioEngine::getInstance()->playBackgroundMusic("Man_Enough.mp3", true);
						SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
					}
					if (strcmp(ChooseTheNowStageMusic.c_str(), "Frank_Musik") == 0)
					{
						SimpleAudioEngine::getInstance()->playBackgroundMusic("Frank_Musik.mp3", true);
						SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0);
					}
					ismusicplay = true;
				}
				if (!b->get_isclick())
				{
					b->set_isclick(1);
				}
				b->setColor(Color3B::GRAY);
				b->setOpacity(120);
				check = 1;
			}
			break;//處理完 所點擊得方塊 就不用繼續掃下去
		}
	}
	if (check)
		return true;
	else
		return false;
}
void HelloWorld::start_timer()
{
	scheduleUpdate();
	start_time =time(NULL);
}
void HelloWorld::stop_timer()
{
	unscheduleUpdate();
}
void HelloWorld::movedown()
{
	if (sec <= music1->get_second())//多少秒後結束
		add_NewBlock();
	else
		TheEnd();
	auto bs = Block::get_Blocks();
	for (auto it = bs->begin(); it != bs->end(); it++)
	{
		(*it)->move_down(music1->get_float_speed(sec));
		if ((*it)->getLineindex() == -1)
		{
			if (!(*it)->get_isclick())//沒點到得方塊
			{
				miss_count++;
			}
		}
	}
}
void HelloWorld::add_NormalLine(int index)
{
	Block* b;
	int color = rand() % 4;//4
	for (int i = 0; i < 4; i++)
	{
		b = Block::createwithargs(color == i ? Color3B::CustomPurple : Color3B::WHITE, Size(visible_size.width/ 4 - 1+origin_size.width,
			visible_size.height/4+origin_size.height));
		if (b->getColor() == Color3B::CustomPurple)
		{
			b->setOpacity(150);
			b->set_isclick(false);
		}
		if (b->getColor() == Color3B::WHITE)
		{
			b->setOpacity(5);
		}
		b->setPosition(i*visible_size.width / 4 + origin_size.width, index*visible_size.height/ 4+origin_size.height);
		b->setLineindex(index);
		gamelayer->addChild(b);
	}
}
void HelloWorld::start_game()
{
	isstart = false;
	ismusicplay = false;
	add_StarLine();
	int randNum = rand() % 3 + 1;
	add_NormalLine(randNum);
}
void HelloWorld::mallocTheMemoryToMusic1()
{
	if (strcmp(ChooseTheNowStageMusic.c_str(), "in_the_end") == 0)
		music1 = (MusicFather*) new in_the_end();
	//if (strcmp(ChooseTheNowStageMusic.c_str(), "Man_Enough") == 0)
	//	music1 = (MusicFather*) new Man_Enough();
	if (strcmp(ChooseTheNowStageMusic.c_str(), "Frank_Musik") == 0)
		music1 = (MusicFather*)new Frank_Musik();
}
void HelloWorld::TheEnd()
{
	//SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	stop_timer();
	auto bs = Block::get_Blocks();
	bs->clear();
	int score = perfect_count - (miss_count * 2);
	Director::getInstance()->replaceScene(TransitionJumpZoom::create(0.3f, Gameover::create_scene(score,ChooseTheNowStageMusic)));
}
void HelloWorld::add_StarLine()
{
	auto b = Block::createwithargs(Color3B::YELLOW, Size(visible_size.width + origin_size.width, visible_size.height / 4 + origin_size.height));
	b->setOpacity(100);
	b->setLineindex(0);
	gamelayer->addChild(b);
}
void HelloWorld::gamePause(Ref *p)
{
	if (sec != 0)   //再遊戲尚未開始之前暫停得話 不要計算暫停時間
	{
		pause_start = time(NULL);
		is_pause = true;
	}
	pause_buffer = 0;
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	auto capture= RenderTexture::create(visible_size.width+origin_size.width, visible_size.height+origin_size.height);
	capture->begin();
	getParent()->visit();
	capture->end();
	Director::getInstance()->pushScene(MyMenu::create_scene(capture));
}
void HelloWorld::setPauseReplace(bool Click_Menu_buttom)
{
	if (Click_Menu_buttom)
		ispausereplace = true;
	else
		ispausereplace = false;
}
bool HelloWorld::checkPauseReplace()
{
	if (ispausereplace)
		return true;
	else
		return false;
}
void HelloWorld::countPauseDivationTime()
{
	if (is_pause)
	{
		if (pause_buffer++ == 1)
		{
			pause_end = time(NULL);
			deviation += pause_end - pause_start;
			is_pause = false;
			SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		}
		else
		{
			pause_end = pause_start;
		}
	}
}
void HelloWorld::add_NewBlock()
{
	if (music1->check_delay_black(sec))
	{
		static int delayBlockCount = 0;
		if (delayBlockCount == 1)//方塊不出現三次 就強制出現一次
		{
			add_NormalLine(4);
			delayBlockCount = 0;
		}
		else
		{
			int randNum = rand() % 2;
			if (randNum)
			{
				add_NormalLine(4);
				delayBlockCount = 0;
			}
			else
				delayBlockCount++;
		}
	}
	else
	{
		add_NormalLine(4);
	}
}
void HelloWorld::initAllVariableToZero()
{
	is_pause = false;
	deviation = 0;
	pause_start = 0;
	pause_end = 0;
	ispausereplace = false;
	perfect_count = 0;
	miss_count = 0;
	sec = 0;//start second
	oldrhythm = 0;
}
void HelloWorld::onExit()
{
	Layer::onExit();
	TextureCache::getInstance()->removeAllTextures();
}
void HelloWorld::cleanup()
{
	Layer::cleanup();
	delete music1;
}