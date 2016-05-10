#include "Block.h"
#include "music.h"
Vector < Block* >* Block::Blocks = new Vector < Block* >();
Vector<Block*>* Block::get_Blocks()
{
	return Block::Blocks;
}
Block * Block::createwithargs(Color3B color3b, Size size)
{
	static int i= 0;
	auto b = new Block();
	b->autorelease();
	b->initwithargs(color3b, size);
	Blocks->pushBack(b);
	return b;
}
bool Block::initwithargs(Color3B color3b, Size size)
{	
	this->getReferenceCount();
	Sprite::init();
	isclick = true;
	setTextureRect(Rect(0, 0,size.width,size.height));
	setAnchorPoint(Point::ZERO);
	setColor(color3b);
	return true;
}
void Block::set_isclick(bool n)//1=ture 0=false
{
	n  ? isclick = true : isclick = false;
}
bool Block::get_isclick()//true 쩑헕을 false 쮁┳헕을
{
	return isclick;
}
void Block::setLineindex(int Lineindex)
{
	this->Lineindex = Lineindex;
}
int Block::getLineindex()
{
	return Lineindex;
}
void Block::remove_Block()
{
	removeFromParent();
	Blocks->eraseObject(this);
}
void Block::cleanup()
{
	Sprite::cleanup();

}
void Block::move_down(float move_speed)//�^또0쩘ろㅸ락헕툹짦  �^또1쩘ろ┳ㅸ락쮁헕⑥
{
	this->Lineindex--;
	runAction(Sequence::create(MoveTo::create(move_speed, Point(getPositionX(), getPositionY() - getContentSize().height)),
		CallFunc::create([this]()
	{
		if (Lineindex <= -2)//0
		{
			remove_Block();
		}
	}
	),NULL));
}