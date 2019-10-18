#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;
using namespace CocosDenshion;

class CBullet : public cocos2d::Node
{
private:
	void GoDie();
public:
	~CBullet();
	CBullet();
	CBullet(Point);

	Rect colliArea();
	Point getPosition();
	Sprite *_bullet;
	CBullet *next = NULL;
	bool dieFlag = false;
	void actionControl(bool);

	// implement the "static create()" method manually
	CREATE_FUNC(CBullet);
};

