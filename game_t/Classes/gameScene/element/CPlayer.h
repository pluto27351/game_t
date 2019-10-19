#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "CBullet.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;
using namespace CocosDenshion;

class CPlayer : public cocos2d::Node
{
private:
	Point pt;
	Node *_Player;
	ActionTimeline *_PlayerAni;
	Color3B color,color2;

	void JumpFlagChange();
public:
	CPlayer();
	CPlayer(Color3B, Color3B);
	~CPlayer();

	CBullet *_LastBullet, *_HeadBullet = NULL;
	LoadingBar *_hp, *_mp;

	float changeTime = 0, BulletTime = 0;
	int JumpTime = 0;
	bool BulletFlag = false, ChangeFlag = false, JumpFlag =false;
	bool hasBullet = false;

	//觸碰動作
	void RenderBullet();
	void JumpAct();

	//bool bulletAttack(Rect);
	void start();
	void killbullet();
	void changeFace(int);
	void decreaseHP();
	int jumpCollider(Point);
	bool bulletCollider(Point);
	void actionControl(bool);

	Point getPosition();

	// implement the "static create()" method manually
	CREATE_FUNC(CPlayer);
};

