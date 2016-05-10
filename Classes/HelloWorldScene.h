#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "Block.h"
#include "music.h"
#include <iostream>
using namespace CocosDenshion;
class HelloWorld : public cocos2d::Layer
{
public:
	static bool ispausereplace;
public:
	bool checkPauseReplace();
	static void setPauseReplace(bool Click_Menu_buttom);
    static cocos2d::Scene* createScene(std::string chooseMusic);
    virtual bool init();
	virtual void update(float dt);

    void gamePause(Ref *p);
	void add_StarLine();
	void TheEnd();
	void add_NormalLine(int index);
	void movedown();
	void start_game();
	void start_timer();
	void stop_timer();
	bool touch_event(Touch*t, Event*e);
    CREATE_FUNC(HelloWorld);
private:
	MusicFather* music1=NULL;
	bool is_pause;
	bool ismusicplay;
	bool isstart;
	int sec;
	int deviation;
	int pause_buffer;
	int oldrhythm;
	int perfect_count;
	int miss_count;
	long start_time;
	long pause_start;
	long pause_end;
	Node *gamelayer;
	SimpleAudioEngine *music;
	Label *timer;
	Label* perfectlabel;
	Label* misslabel;
	Size visible_size;
	Size origin_size;
	Sprite* map1;
	Sprite* map2;
private:
	virtual void onExit();
	virtual void cleanup();
	void addtouchParticle(Touch*t, Event*e);
	void addBackGroundParticle();
	void mallocTheMemoryToMusic1();
	void map_update();
	void judge_resetmap(Sprite *map);
	void initAllVariableToZero();
	void countPauseDivationTime();
	void add_NewBlock();
};

#endif // __HELLOWORLD_SCENE_H__
