#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "element/C3Button.h"
#include "element/CScore.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocostudio;
using namespace ui;
using namespace CocosDenshion;

class GameSet : public cocos2d::Layer
{
private:
	Sprite *_PR, *_PY, *_PG,*_PB;
	Rect rPR, rPY, rPG, rPB;
	Text *_Easy, *_Normal , *_Hard;
	Rect rEasy, rNormal, rHard;
	Sprite *_body, *_mouth;
	ComAudio *bkmusic;
	//Sprite *_Go;
	//Rect rGo;

	Node *_Running;
	ActionTimeline *_RunAction;

	Color3B PColor,PColor2;
	C3Button *_btnPlay,*_btnClose,*_btnTable;
	CScore *_STable;
	Sprite *_wbg,*_tablebg;
	Node *_tableNode;
	int Mode = 1;

	//bool btnGo = false;

	void SetRect(Sprite *, Rect *);
	void SetRect(Text*, Rect *);
	void ChageAni(Sprite *, Sprite *, Sprite *, Sprite *, Color3B);
	void ChageMode(Text *, Text *, Text *);
	void SetTable(CScore *);

public:
	~GameSet();
	//bool changeScene = false;
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene(CScore *);
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	bool init();

	cocos2d::EventListenerTouchOneByOne *_listener1;
	bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰開始事件
	void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰移動事件
	void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰結束事件 

	// implement the "static create()" method manually
	CREATE_FUNC(GameSet);
};

