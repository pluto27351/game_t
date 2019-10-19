#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "element/CPlayer.h"
#include "element/CEnemy.h"
#include "element/CBoss.h"
#include "element/C3Button.h"
#include "element/CScore.h"


USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocostudio;
using namespace ui;
using namespace CocosDenshion;

class GamePlay : public cocos2d::Layer
{
private:
	Node *rootNode,*_Line;
	ActionTimeline *_LineAni;
	LoadingBar *_timeline;
	Sprite *_menu,*_help,*_wbg,*_table;
	Label *_fin, *_finScore;
	ComAudio *bkmusic;

	CPlayer *_Player;
	CEnemy *_HeadEnemy = NULL, *_LastEnemy;
	CBoss *_Boss;
	C3Button *_btnGo,*_btnHome, *_btnRestart,*_btnMenu,*_btnHelp,*_btnClose1, *_btnClose2;
	CScore *_STable;

	//遊戲設定變數
	bool START=false;
	int Mode;
	Color3B Cnormal, Cattacked;

	//參數
	bool hasEnemy = false, hasBoss = false, hasPlayer = false;
	int bossNum = 0;

	//Enemy生成相關
	bool renderFlag=true;
	float TotalTime, dtTime, randomdt;

	//分數相關
	Text *_Score,*_Level;
	int  score,level;
	char scoreNo[4],lvNo[5];
	bool complete = false;

	//避免重複生成
	bool EnemyFlag = false, BossFlag = false;
	
	void doStep(float);	
	void setMode(int, Color3B, Color3B,CScore*);  //玩家選擇紀錄
	void restart();   //遊戲開始->初始化
	void start();     //遊戲開始->動畫撥放
	void RenderESet();   //enemy生成時間差設定
	void RenderEnemy();  //生成enemy
	void RenderBoss();   //生成boss
	void killEnemy();    //判斷並殺死enemy
	void killBoss();     //判斷並殺死boss
	void addScore(int);  //加 x 分
	void levelUp();
	void jumpcCollide(CEnemy *);  //enemy碰撞判斷
	void jumpcCollide(CBoss *);   //boss碰撞判斷
	void bulletCollide();         //bullet碰撞判斷
	void menuControl(bool);        //彈出視窗顯示與隱藏
	void actionControl(bool);  //暫停與開始
	void theEnd();

public:
	~GamePlay();
	bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene(int m, Color3B c1, Color3B c2,CScore *);

	cocos2d::EventListenerTouchOneByOne *_listener1;
	bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰開始事件
	void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰移動事件
	void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰結束事件 

	// implement the "static create()" method manually
	// 修改
	CREATE_FUNC(GamePlay);
};

