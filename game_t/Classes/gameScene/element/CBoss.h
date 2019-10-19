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

class CBoss :public cocos2d::Node
{
private:
	Node *_action = NULL;
	ActionTimeline *_actionAni;
	Rect colliderArea;
	Point pt;
	MoveTo *moveAct;
	Color3B color, color2;
	int Mode, Num;

	void lifeEnd();
	void moveAni();

	int derseHP, reHP;
	float speed;
	char *runner;
	bool startAttacked=false;

	void decreaseHP();
	void running();
	void changeFace(bool);
	void changeFaceEnd();
	void reback();
	void reset();
public:
	~CBoss();
	CBoss();
	CBoss(int,int);
	bool GoDie = false, hasColliEnd = false;

	int collider(Point);
	bool isMoving = false;
	LoadingBar *_hp;
	bool isAttacked(Point);
	void actionControl(bool);
	
	// implement the "static create()" method manually
	CREATE_FUNC(CBoss);
};

