#include "GamePlay.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameSet.h"
#include "SimpleAudioEngine.h"

#define NORMAL_FACE 0
#define HAPPY_FACE 1
#define SAD_FACE 2

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;
using namespace CocosDenshion;

GamePlay::~GamePlay() {
	while (hasEnemy) {
		CEnemy *e = _HeadEnemy;
		e->GoDie = true;		killEnemy();
	}

	if (hasBoss) {
		_Boss->GoDie = true;		killBoss();
	}

	this->removeChild(_btnGo);	delete _btnGo;
	this->removeChild(_btnMenu);	delete _btnMenu;
	this->removeChild(_btnHome);	delete _btnHome;
	this->removeChild(_btnRestart);	delete _btnRestart;
	this->removeChild(_btnHelp);	delete _btnHelp;
	this->removeChild(_btnClose1);	delete _btnClose1;
	this->removeChild(_btnClose2);	delete _btnClose2;

	this->removeChild(_Player);	delete _Player;
	// 釋放音效檔
	SimpleAudioEngine::getInstance()->unloadEffect("./Audio/jump.WAV"); 
	SimpleAudioEngine::getInstance()->unloadEffect("./Audio/attacked.WAV");
	SimpleAudioEngine::getInstance()->unloadEffect("./Audio/gain point.mp3");
	SimpleAudioEngine::getInstance()->unloadEffect("./Audio/bullet.WAV");
}

Scene* GamePlay::createScene(int m,Color3B c1,Color3B c2,CScore *table)
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GamePlay::create();
	layer->setMode(m,c1,c2,table);

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GamePlay::init()
{
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	rootNode = CSLoader::createNode("PlayScene.csb");

	addChild(rootNode);

	// 預先載入音效檔	
	SimpleAudioEngine::getInstance()->preloadEffect("./Audio/jump.WAV");
	SimpleAudioEngine::getInstance()->preloadEffect("./Audio/attacked.WAV");
	SimpleAudioEngine::getInstance()->preloadEffect("./Audio/gain point.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("./Audio/bullet.WAV");


	//按鈕相關
	_btnGo = new C3Button(Vec2(1120,125), "b_playOn.png", "b_playDown.png", "b_playDown.png");
	this->addChild(_btnGo, 11);
	_btnMenu = new C3Button(Vec2(1220,670), "s_menuOn.png", "s_menuDown.png", "s_menuDown.png");
	this->addChild(_btnMenu, 1);
	_btnHome = new C3Button(Vec2(510,390), "s_homeOn.png", "s_homeDown.png", "s_homeDown.png");
	this->addChild(_btnHome, 6);
	_btnRestart = new C3Button(Vec2(640,390), "s_restartOn.png", "s_restartDown.png", "s_restartDown.png");
	this->addChild(_btnRestart, 6);
	_btnHelp = new C3Button(Vec2(770,390), "s_helpOn.png", "s_helpDown.png", "s_helpDown.png");
	this->addChild(_btnHelp, 6);
	_btnClose1 = new C3Button(Vec2(840,465), "s_closeOn.png", "s_closeDown.png", "s_closeDown.png");
	this->addChild(_btnClose1, 6);
	_btnClose2 = new C3Button(Vec2(1110,595), "s_closeOn.png", "s_closeDown.png", "s_closeDown.png");
	this->addChild(_btnClose2, 11);

	//彈出視窗
	_wbg = Sprite::createWithSpriteFrameName("w_bg.png");
	_wbg->setPosition(640, 360);
	_wbg->setScale(10, 10);
	this->addChild(_wbg, 4);
	_table = Sprite::createWithSpriteFrameName("btn_menu.png");
	_table->setPosition(640, 390);
	this->addChild(_table, 5);
	/*_menu = Sprite::createWithSpriteFrameName("menu.png");
	_menu->setPosition(640, 360);
	this->addChild(_menu,5);
*/
	//遊戲說明
	_help = Sprite::createWithSpriteFrameName("help.png");
	_help->setPosition(640, 360);
	this->addChild(_help,10);

	_btnClose1->setDisable(true);    _btnClose1->setVisible(false);
	_btnClose2->setDisable(true);    _btnClose2->setVisible(false);
	_btnHome->setDisable(true);     _btnHome->setVisible(false);
	_btnRestart->setDisable(true);  _btnRestart->setVisible(false);
	_btnHelp->setDisable(true);     _btnHelp->setVisible(false);

	//結束文字
	_finScore = Label::createWithTTF("NO.1 / Score : 000" , "Marker Felt.ttf",48);
	_finScore->setColor(Color3B(230,85,88));
	_finScore->setPosition(Vec2(630, 245));
	this->addChild(_finScore, 7);

	_fin = Label::createWithTTF("complete" ,"Marker Felt.ttf",100);
	_fin->setPosition(Vec2(460, 500));
	_fin->setRotation(-13);
	this->addChild(_fin, 7);

	_fin->setVisible(false);
	_finScore->setVisible(false);

	//按鍵提示
	auto att = Label::createWithTTF("Attack", "Marker Felt.ttf", 80);
	att->setColor(Color3B(224,108,106));
	att->setPosition(Vec2(280,110));
	this->addChild(att, 1);

	auto jum = Label::createWithTTF("Jump", "Marker Felt.ttf", 80);
	jum->setColor(Color3B(224, 108, 106));
	jum->setPosition(Vec2(1000, 110));
	this->addChild(jum, 1);
	
	//跑道切換
	_Line = CSLoader::createNode("Ani/Line.csb");
	_Line->setPosition(640,355);
	this->addChild(_Line,0);
	_LineAni = (ActionTimeline *)CSLoader::createTimeline("Ani/Line.csb");
	_Line->runAction(_LineAni);

	//進度條
	_timeline = (cocos2d::ui::LoadingBar*)rootNode->getChildByName("timeline");
	_timeline->setDirection(LoadingBar::Direction::LEFT);

	//分數
	_Score = (cocos2d::ui::Text *)rootNode->getChildByName("score");
	_Level = (cocos2d::ui::Text *)rootNode->getChildByName("level");
	
	//觸控
	_listener1 = EventListenerTouchOneByOne::create();	//創建一個一對一的事件聆聽器
	_listener1->onTouchBegan = CC_CALLBACK_2(GamePlay::onTouchBegan, this);		//加入觸碰開始事件
	_listener1->onTouchMoved = CC_CALLBACK_2(GamePlay::onTouchMoved, this);		//加入觸碰移動事件
	_listener1->onTouchEnded = CC_CALLBACK_2(GamePlay::onTouchEnded, this);		//加入觸碰離開事件

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener1, this);	//加入剛創建的事件聆聽器

	// 將 doStep 函式掛入 schedule list 中，每一個 frame 就都會被呼叫到
	this->schedule(CC_SCHEDULE_SELECTOR(GamePlay::doStep));
	return true;

}

void GamePlay::setMode(int m, Color3B c, Color3B c2,CScore *table) {
	Cnormal = c;
	Cattacked = c2;
	Mode = m;
	_STable = table;
	_STable->level = 1;
	_STable->score = 0;
}

void GamePlay::restart() {
	//初始化
	while (hasEnemy) {
		CEnemy *e = _HeadEnemy;
		e->GoDie = true;
		killEnemy();
	}

	if (hasBoss) {
		_Boss->GoDie = true;
		killBoss();
	}

	if (hasPlayer) {
		this->removeChild(_Player);
		delete _Player;
		hasPlayer = false;
	}

	//背景音樂
	auto bkmusic = (cocostudio::ComAudio *)rootNode->getChildByName("BG_Music")->getComponent("BG_Music");
	bkmusic->playBackgroundMusic();
	 
	//倒數計時開始
	Node *node321 = CSLoader::createNode("Ani/321ani.csb");
	ActionTimeline  *node321ani =( ActionTimeline *)CSLoader::createTimeline("Ani/321ani.csb");
	node321->runAction(node321ani);
	node321->setPosition(640,360);
	this->addChild(node321, 5);
	node321ani->gotoFrameAndPlay(0, 225, false);
	node321ani->setLastFrameCallFunc([=]()
	{
		start();
		this->removeChild(node321);
	});

	_table->setVisible(true);
	_wbg->setVisible(true);

	//角色生成
	_Player = new CPlayer(Cnormal, Cattacked);
	_Player->_hp->setPercent(100);
	_Player->_mp->setPercent(100);
	this->addChild(_Player, 2);
	hasPlayer = true;

	//分數設定
	score = 0;
	strcpy(scoreNo, "000");
	_Score->setString(scoreNo);
	complete = false;


	//level
	level = 1;
	strcpy(lvNo, "NO.6");
	_Level->setString(lvNo);

	//btn關閉
	_btnMenu->setDisable(true);

	//進度設定
	_timeline->setPercent(0);
	bossNum = 0;

	//隱藏
	_fin->setVisible(false);
	_finScore->setVisible(false);

}

void GamePlay::start() {

	//遊戲動畫撥放
	_LineAni->gotoFrameAndPlay(0, 20, true);
	_Player->start();

	//按鈕開啟
	_btnMenu->setDisable(false);

	_table->setVisible(false);
	_wbg->setVisible(false);

	//遊戲開始
	START = true;
}

void GamePlay::doStep(float dt)
{
	if (START) {
		TotalTime += dt;

		//進度條
		float timeline = _timeline->getPercent();
		if (hasBoss == false) {
			timeline += dt*3;
			_timeline->setPercent(timeline);
		}

		//怪物生成時間差
		if (renderFlag) {
			RenderESet();
			dtTime = TotalTime;
			renderFlag = false;
		}

		//生成小怪物
		if ((TotalTime - dtTime) > randomdt) {
			renderFlag = true;
			RenderEnemy();
		}
		
		//生成boss
		if ((int)timeline / 20 == (bossNum+1) && hasBoss == false) {
			RenderBoss();
			timeline += 1;
			_timeline->setPercent(timeline);
		}
		
		//回藍
		if (_Player->_mp->getPercent() < 100) {
			float t = _Player->_mp->getPercent();
			t += dt * 5;
			_Player->_mp->setPercent(t);
		}

		//碰撞判斷
		if (hasEnemy && (_HeadEnemy->hasColliEnd == false)) jumpcCollide(_HeadEnemy);
		if (hasBoss && _Player->hasBullet &&_Boss->isMoving == false) bulletCollide();
		if (hasBoss && _Boss->isMoving && (_Boss->hasColliEnd == false))jumpcCollide(_Boss);


		//人物換臉
		if ((_Player->ChangeFlag == true) && (_Player->changeTime += dt)>0.5) {
			_Player->changeTime = 0;
			_Player->changeFace(NORMAL_FACE);
		}

		if (_Player->_hp->getPercent() == 0) theEnd();

		//殺死一切
		_Player->killbullet();
		killEnemy();
		killBoss();
	}
}

void GamePlay::RenderESet() {
	int i = random(1, 5 );   //1~5 
	switch (Mode) {
	case 1:
		switch (level) {
		case 1:
		case 2:
			if (i < 2) randomdt = 0.7;
			else if(i<3) randomdt = 1.0;
			else if(i<5) randomdt = 1.5;
			else randomdt = 2;
			break;
		case 3:
		case 4:
			if (i < 2) randomdt = 0.7;
			else if (i<4) randomdt = 1.0;
			else if (i<6) randomdt = 1.5;
			break;
		case 5:
			if (i < 2) randomdt = 0.7;
			else if (i<5) randomdt = 1.0;
			else if (i<6) randomdt = 1.5;
			break;
		}
		break;
	case 2:
		switch (level) {
		case 1:
		case 2:
			if (i < 2) randomdt = 0.2;
			else if (i<3) randomdt = 0.7;
			else if (i<4) randomdt = 1.0;
			else if (i<5) randomdt = 1.5;
			else randomdt = 2;
			break;
		case 3:
		case 4:
			if (i < 2) randomdt = 0.2;
			else if (i<3) randomdt = 0.7;
			else if (i<5) randomdt = 1.0;
			else if (i<6) randomdt = 1.5;
			break;
		case 5:
			if (i < 2) randomdt = 0.2;
			else if (i<4) randomdt = 0.7;
			else if (i<6) randomdt = 1.0;
			break;
		}
		break;
	case 3:
		switch (level) {
		case 1:
		case 2:
			if (i < 2) randomdt = 0.2;
			else if (i<3) randomdt = 0.7;
			else if (i<5) randomdt = 1.0;
			else if (i<6) randomdt = 1.5;
			break;
		case 3:
		case 4:
			if (i < 2) randomdt = 0.2;
			else if (i<4) randomdt = 0.7;
			else if (i<5) randomdt = 1.0;
			else if (i<6) randomdt = 1.5;
			break;
		case 5:
			if (i<3) randomdt = 0.4;
			else if (i<35) randomdt = 0.7;
			else if (i < 6) randomdt = 1.0;
			break;
		}
		break;
	}
	
}

void GamePlay::RenderEnemy() {
	EnemyFlag = true;
	CEnemy *newEnemy = new CEnemy;
	this->addChild(newEnemy, 1);

	if (_HeadEnemy == NULL) {
		_HeadEnemy = newEnemy;
		_LastEnemy = _HeadEnemy;
		hasEnemy = true;
	}
	else {
		_LastEnemy->next = newEnemy;
		_LastEnemy = newEnemy;
	}
}

void GamePlay::RenderBoss() {
	hasBoss = true;
	_Boss = new CBoss(Mode,bossNum);
	addChild(_Boss, 2);
	bossNum++;
}

void GamePlay::killEnemy() {
	if (hasEnemy) {
		if (_HeadEnemy->GoDie) {
			CEnemy *dieEnemy = _HeadEnemy;
			if( (_HeadEnemy = _HeadEnemy->next) == NULL) hasEnemy = false;
			this->removeChild(dieEnemy);
			delete dieEnemy;
		}
	}
}

void GamePlay::killBoss() {
	if (hasBoss) {
		bool DieFlag = _Boss->GoDie;
		if (DieFlag) {
			this->removeChild(_Boss);
			delete _Boss;
			hasBoss = false;
			levelUp();
		}
		
	}
}

void GamePlay::addScore(int s) {
	SimpleAudioEngine::getInstance()->playEffect("./Audio/gain point.mp3", false);
	if (_STable->score < 999) {
		_STable->score += s;
		int i = _STable->score, j=0;
		while (i > 0) {
			scoreNo[2 - j] = i % 10 + 48;   //48 = 1的編號
			i = i / 10;
			j++;
		}
		_Score->setString(scoreNo);			
	}
	
}

void GamePlay::levelUp() {
	_STable->level++;
	lvNo[3] = (7- _STable->level) + 48;   //48 = 1的編號
	_Level->setString(lvNo);
	if (_STable->level == 5) complete = true;
}

void GamePlay::jumpcCollide(CEnemy *enemy) {
	switch(enemy->collider(_Player->getPosition())){
	case 0:  //還未到
		break;
	case 1:  //跳躍成功
		enemy->hasColliEnd = true;
		_Player->changeFace(HAPPY_FACE);
		addScore(1);
		break;
	case 2:  //跳躍失敗
		enemy->hasColliEnd = true;
		SimpleAudioEngine::getInstance()->playEffect("./Audio/attacked.WAV", false);
		_Player->changeFace(SAD_FACE);
		_Player->decreaseHP();
		break;
	}
}
void GamePlay::jumpcCollide(CBoss *boss) {
	switch (boss->collider(_Player->getPosition())) {
	case 0:  //還未到
		break;
	case 1:  //跳躍成功
		boss->hasColliEnd = true;
		_Player->changeFace(HAPPY_FACE);
		addScore(5);
		break;
	case 2:  //跳躍失敗
		boss->hasColliEnd = true;
		SimpleAudioEngine::getInstance()->playEffect("./Audio/attacked.WAV", false);
		_Player->changeFace(SAD_FACE);
		_Player->decreaseHP();
		break;
	}
}
void GamePlay::bulletCollide() {
	Point bulletpt = _Player->_HeadBullet->getPosition();
	if (_Boss->isAttacked(bulletpt)) {
		SimpleAudioEngine::getInstance()->playEffect("./Audio/attacked.WAV", false);
		_Player->_HeadBullet->dieFlag = true;
	}

}

void GamePlay::theEnd() {
	char finscore[19] = ("LV.1 / Score : 000");
	for (int i = 0; i < 4; i++)  finscore[i] = lvNo[i];
	for (int i = 15;i<18;i++) finscore[i] = scoreNo[i-15];
	
	_finScore->setString(finscore);

	if (complete) {
		_fin->setString("Complete !");
		_fin->setColor(Color3B::YELLOW);
	}
	
	else {
		_fin->setString("You Are Die");
		_fin->setColor(Color3B::RED);
	}

	_fin->setVisible(true);
	_finScore->setVisible(true);

	menuControl(true);
	actionControl(false);
	_btnClose1->setDisable(true);    _btnClose1->setVisible(false);
	
	_STable->setScore(Mode);
}


void GamePlay::menuControl(bool menuopen) {
	START = !menuopen;

	_btnMenu->setDisable(menuopen);

	_btnClose1->setDisable(!menuopen);    _btnClose1->setVisible(menuopen);
	_btnHome->setDisable(!menuopen);     _btnHome->setVisible(menuopen);
	_btnRestart->setDisable(!menuopen);  _btnRestart->setVisible(menuopen);
	_btnHelp->setDisable(!menuopen);     _btnHelp->setVisible(menuopen);
	_table->setVisible(menuopen);
	_wbg->setVisible(menuopen);
										 //_menu->setVisible(menuopen);
}

void GamePlay::actionControl(bool run) {
	if(run)_Line->onEnter();
	else _Line->onExit();
	
	_Player->actionControl(run);
	if (hasEnemy) {
		CEnemy *e = _HeadEnemy;
		while (e != NULL) {
			e->actionControl(run);
			e = e->next;
		}
	}
	if (hasBoss) {
		_Boss->actionControl(run);
	}
}


bool GamePlay::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)//觸碰開始事件
{
	Point touchLoc = pTouch->getLocation();

	//跳躍與攻擊
	if (touchLoc.y < 360  &&  START) {  
		if (touchLoc.x < 640 && _Player->BulletFlag == false) {
			_Player->RenderBullet();
			SimpleAudioEngine::getInstance()->playEffect("./Audio/bullet.WAV", false);
		}
		else if (touchLoc.x >= 640 && _Player->JumpFlag == false && _Player->JumpTime < 2) {
			_Player->JumpAct();
			SimpleAudioEngine::getInstance()->playEffect("./Audio/jump.WAV", false);
		}

	}

	_btnGo->isTouched(touchLoc);
	_btnMenu->isTouched(touchLoc);
	_btnClose1->isTouched(touchLoc);
	_btnHome->isTouched(touchLoc);
	_btnRestart->isTouched(touchLoc);
	_btnHelp->isTouched(touchLoc);
	_btnClose2->isTouched(touchLoc);

	
	return true;
}

void  GamePlay::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //觸碰移動事件
{
	Point touchLoc = pTouch->getLocation();

	_btnGo->isLeave(touchLoc);
	_btnMenu->isLeave(touchLoc);
	_btnClose1->isLeave(touchLoc);
	_btnHome->isLeave(touchLoc);
	_btnRestart->isLeave(touchLoc);
	_btnHelp->isLeave(touchLoc);
	_btnClose2->isLeave(touchLoc);
}

void  GamePlay::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //觸碰結束事件 
{
	Point touchLoc = pTouch->getLocation();

	if (hasPlayer) {
		_Player->BulletFlag = false;
		_Player->JumpFlag = false;
	}

	if (_btnGo->isUsed()) {
		restart();
		_help->setVisible(false);
		_btnGo->setDisable(true);
		_btnGo->setVisible(false);
		_table->setVisible(true);
		_wbg->setVisible(true);
		//_menu->setVisible(false);

	}
	if (_btnMenu->isUsed()) {
		menuControl(true);
		actionControl(false);
	}
	if (_btnClose1->isUsed()) {
		menuControl(false);
		actionControl(true);
	}
	if (_btnHome->isUsed()) {
		bkmusic->stopBackgroundMusic();

		CCScene *scene = CCScene::create();
		auto *layer = GameSet::createScene(_STable);
		scene->addChild(layer);
		CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f, scene));
	}
	if (_btnRestart->isUsed()) {
		menuControl(false);
		START = false;
		restart();
	}
	if (_btnHelp->isUsed()) {
		_help->setVisible(true);
		_btnClose2->setDisable(false);
		_btnClose2->setVisible(true);

		_btnHome->setDisable(true);
		_btnRestart->setDisable(true);
		_btnHelp->setDisable(true);
	}
	if (_btnClose2->isUsed()) {
		_help->setVisible(false);
		_btnClose2->setDisable(true);
		_btnClose2->setVisible(false);

		_btnHome->setDisable(false);
		_btnRestart->setDisable(false);
		_btnHelp->setDisable(false);
	}

}

