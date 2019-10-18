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

	//�C���]�w�ܼ�
	bool START=false;
	int Mode;
	Color3B Cnormal, Cattacked;

	//�Ѽ�
	bool hasEnemy = false, hasBoss = false, hasPlayer = false;
	int bossNum = 0;

	//Enemy�ͦ�����
	bool renderFlag=true;
	float TotalTime, dtTime, randomdt;

	//���Ƭ���
	Text *_Score,*_Level;
	int  score,level;
	char scoreNo[4],lvNo[5];
	bool complete = false;

	//�קK���ƥͦ�
	bool EnemyFlag = false, BossFlag = false;
	
	void doStep(float);	
	void setMode(int, Color3B, Color3B,CScore*);  //���a��ܬ���
	void restart();   //�C���}�l->��l��
	void start();     //�C���}�l->�ʵe����
	void RenderESet();   //enemy�ͦ��ɶ��t�]�w
	void RenderEnemy();  //�ͦ�enemy
	void RenderBoss();   //�ͦ�boss
	void killEnemy();    //�P�_�ñ���enemy
	void killBoss();     //�P�_�ñ���boss
	void addScore(int);  //�[ x ��
	void levelUp();
	void jumpcCollide(CEnemy *);  //enemy�I���P�_
	void jumpcCollide(CBoss *);   //boss�I���P�_
	void bulletCollide();         //bullet�I���P�_
	void menuControl(bool);        //�u�X������ܻP����
	void actionControl(bool);  //�Ȱ��P�}�l
	void theEnd();

public:
	~GamePlay();
	bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene(int m, Color3B c1, Color3B c2,CScore *);

	cocos2d::EventListenerTouchOneByOne *_listener1;
	bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //Ĳ�I�}�l�ƥ�
	void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //Ĳ�I���ʨƥ�
	void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //Ĳ�I�����ƥ� 

	// implement the "static create()" method manually
	// �ק�
	CREATE_FUNC(GamePlay);
};

