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

class CEnemy : public cocos2d::Node
{
private:
	
	Node *_action = NULL;
	ActionTimeline *_actionAni;

	Point pt;

	void lifeEnd();
	void moveAni();
	
public:
	~CEnemy();
	CEnemy();
	CEnemy *next = NULL;
	bool GoDie = false, hasColliEnd = false;

	int collider(Point);
	void actionControl(bool);

	// implement the "static create()" method manually
	CREATE_FUNC(CEnemy);
};

