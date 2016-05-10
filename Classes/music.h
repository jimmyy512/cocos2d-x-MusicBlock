#ifndef _music_H_
#define _music_H_
#include <iostream>
#include "cocos2d.h"
using namespace std;

class MusicFather
{
public:
	virtual int get_second() = 0;
	virtual int get_speed(int sec) = 0;
	virtual float get_float_speed(int sec) = 0;//1.0
	virtual bool check_swing(int sec)=0;
	virtual bool check_delay_black(int sec) = 0;
public:
	int BlockDownSpeed;
	float animationSpeed;//animation speed
};
class Frank_Musik :public MusicFather
{
public:
	int get_second()
	{
		return 203;//203
	}
	int get_speed(int sec)//60  
	{
		if (sec <= 7)
			BlockDownSpeed = 60;
		else if (sec <= 24)
			BlockDownSpeed= 30;
		else if (sec <= 39)
			BlockDownSpeed = 15;
		else if (sec <= 56)
			BlockDownSpeed = 10;
		else if (sec <= 71)
			BlockDownSpeed = 30;
		else if (sec <= 88)
			BlockDownSpeed = 15;
		else if (sec <= 104)
			BlockDownSpeed = 10;
		else if (sec <= 136)
			BlockDownSpeed = 30;
		else if (sec <= 152)
			BlockDownSpeed = 15;
		else if (sec <= 167)
			BlockDownSpeed = 10;
		else if (sec <= 184)
			BlockDownSpeed =15;
		else
			BlockDownSpeed = 10;
		animationSpeed = ((float)BlockDownSpeed) / 60;
		return BlockDownSpeed;
	}
	float get_float_speed(int sec)//1.0
	{
		return animationSpeed;
	}
	bool check_swing(int sec)
	{
			return false;
	}
	bool check_delay_black(int sec)
	{
		if (sec <= 7)
			return true;
		else
			return false;
	}
};
class in_the_end :public MusicFather
{
public:
	int get_second()
	{
		return 200;
	}
	int get_speed(int sec)//60  
	{
		if (sec <= 19)
			BlockDownSpeed = 40;
		else if (sec <= 55)
			BlockDownSpeed = 15;
		else if (sec <= 74)
			BlockDownSpeed = 10;
		else if (sec <= 111)
			BlockDownSpeed = 15;
		else if (sec <= 130)
			BlockDownSpeed = 10;
		else if (sec <= 150)
			BlockDownSpeed = 40;
		else if (sec <= 168)
			BlockDownSpeed = 15;
		else if (sec <= 187)
			BlockDownSpeed = 10;
		else
			BlockDownSpeed = 40;
		animationSpeed = ((float)BlockDownSpeed) / 60;
		return BlockDownSpeed;
	}
	float get_float_speed(int sec)//1.0
	{
		return animationSpeed;
	}
	bool check_swing(int sec)
	{
		if (sec == 18)
			return true;
		else if (sec == 54)
			return true;
		else if (sec == 109)
			return true;
		else if (sec == 148)
			return true;
		else if (sec == 166)
			return true;
		else 
			return false;
	}
	bool check_delay_black(int sec)
	{
		//if (sec >= 20)
		//	return true;
		//else
			return false;
	}
};


#endif