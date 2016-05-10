#ifndef _Block_H_
#define _Block_H_
#include "cocos2d.h"
#include <iostream>
USING_NS_CC;
class Block:public Sprite
{
private:
	virtual void cleanup();
	static Vector <Block*>*Blocks;
	int Lineindex;
	Size visible_size;
	Size origin_size;
	bool isclick;
public:
	static Vector<Block*>* get_Blocks();
	static Block* createwithargs(Color3B color3b, Size size);
	bool initwithargs(Color3B color3b, Size size);
	int getLineindex();
	void move_down(float move_speed);
	void remove_Block();
	void setLineindex(int Lineindex);
	bool get_isclick();
	void set_isclick(bool n);
};


#endif