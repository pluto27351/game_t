#include "GameSet.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "gameScene/GamePlay.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;
using namespace CocosDenshion;


Scene* GameSet::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameSet::create();
	layer->SetTable(NULL);
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

Scene* GameSet::createScene(CScore *table)
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameSet::create();
	layer->SetTable(table);
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

GameSet::~GameSet() {
	this->removeChild(_btnPlay);
	delete _btnPlay;
	SimpleAudioEngine::getInstance()->unloadEffect("./Audio/button.WAV");
}

// on "init" you need to initialize your instance
bool GameSet::init()
{
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("MainScene.csb");
	
	addChild(rootNode);

	//����.����
	SimpleAudioEngine::getInstance()->preloadEffect("./Audio/button.WAV");
	auto bkmusic = (cocostudio::ComAudio *)rootNode->getChildByName("BG_Music")->getComponent("BG_Music");
	bkmusic->playBackgroundMusic();

	//���s
	_btnPlay = new C3Button(Vec2(1055,120), "b_playOn.png","b_playDown.png", "b_playDown.png");
	this->addChild(_btnPlay,1);
	_btnTable = new C3Button(Vec2(855, 120), "b_scoreOn.png", "b_scoreDown.png", "b_scoreDown.png");
	this->addChild(_btnTable, 1);
	_btnClose = new C3Button(Vec2(890, 665), "s_closeOn.png", "s_closeDown.png", "s_closeDown.png");
	_btnClose->setDisable(true);
	_btnClose->setVisible(false);
	this->addChild(_btnClose, 11);

	//�]�w�}�� �M Ĳ���I
	_PR = dynamic_cast<Sprite*>(rootNode->getChildByName("PR"));  SetRect(_PR,&rPR);
	_PY = dynamic_cast<Sprite*>(rootNode->getChildByName("PY"));  SetRect(_PY,&rPY);
	_PG = dynamic_cast<Sprite*>(rootNode->getChildByName("PG"));  SetRect(_PG,&rPG);
	_PB = dynamic_cast<Sprite*>(rootNode->getChildByName("PB"));  SetRect(_PB,&rPB);
	_Easy = dynamic_cast<Text*>(rootNode->getChildByName("Mode_E"));  SetRect(_Easy, &rEasy);
	_Normal = dynamic_cast<Text*>(rootNode->getChildByName("Mode_N"));  SetRect(_Normal, &rNormal);
	_Hard = dynamic_cast<Text*>(rootNode->getChildByName("Mode_H"));  SetRect(_Hard, &rHard);

	//��ܸ}��ʵe
	_Running = CSLoader::createNode("Ani/Runner.csb");
	_Running->setPosition(_PR->getPosition());
	_body = (cocos2d::Sprite *)_Running->getChildByName("body");
	_mouth = (cocos2d::Sprite *)_Running->getChildByName("Normal")->getChildByName("mouth");
	_body->setColor(_PR->getColor());
	_mouth->setColor(_PR->getColor());
	this->addChild(_Running);
	_RunAction = (ActionTimeline *)CSLoader::createTimeline("Ani/Runner.csb");
	_Running->runAction(_RunAction);
	_RunAction->gotoFrameAndPlay(0, 24, true);

	PColor = _PR->getColor();
	PColor2 = Color3B(180,53,44);

	//�����Q��ܪ��Ϥ�
	_PR->setVisible(false);
	_PY->setVisible(true); _PG->setVisible(true); _PB->setVisible(true);

	//�Ʀ�]
	_wbg = Sprite::createWithSpriteFrameName("w_bg.png");
	_wbg->setPosition(640, 360);
	_wbg->setScale(10, 10);
	_tablebg = Sprite::createWithSpriteFrameName("scoretable.png");
	_tablebg->setPosition(640, 360);

	_tableNode = new Node;
	_tableNode->addChild(_wbg, 1);
	_tableNode->addChild(_tablebg, 2);
	this->addChild(_tableNode, 10);
	_tableNode->setVisible(false);

	//Ĳ��
	_listener1 = EventListenerTouchOneByOne::create();	//�Ыؤ@�Ӥ@��@���ƥ��ť��
	_listener1->onTouchBegan = CC_CALLBACK_2(GameSet::onTouchBegan, this);		//�[�JĲ�I�}�l�ƥ�
	_listener1->onTouchMoved = CC_CALLBACK_2(GameSet::onTouchMoved, this);		//�[�JĲ�I���ʨƥ�
	_listener1->onTouchEnded = CC_CALLBACK_2(GameSet::onTouchEnded, this);		//�[�JĲ�I���}�ƥ�

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener1, this);	//�[�J��Ыت��ƥ��ť��


	// �N doStep �禡���J schedule list ���A�C�@�� frame �N���|�Q�I�s��
	return true;
}
void GameSet::SetTable(CScore *table) {
	if (table == NULL) {
		_STable = new CScore;
	}
	else {
		//_tableNode->removeChild(_STable);
		_STable = table;
		//_tableNode->addChild(_STable, 3);
	}
	_tableNode->addChild(_STable, 3);
}


void GameSet::SetRect(Sprite *P, Rect *R){
	Point pt = P->getPosition();
	Size sz = (P->getContentSize());
	*R = Rect(pt.x - sz.width / 2, pt.y - sz.height / 2, sz.width, sz.height);
}

void GameSet::SetRect(Text *P, Rect *R) {
	Point pt = P->getPosition();
	Size sz = (P->getContentSize());
	*R = Rect(pt.x - sz.width / 2, pt.y - sz.height / 2, sz.width, sz.height);
}

void GameSet::ChageAni(Sprite *selected, Sprite *unselec_1, Sprite *unselec_2, Sprite *unselec_3,Color3B c) {
	PColor = selected->getColor();
	PColor2 = c;
	_Running->setPosition(selected->getPosition());
	_body->setColor(PColor);
	_mouth->setColor(PColor);
	selected->setVisible(false);
	unselec_1->setVisible(true); unselec_2->setVisible(true); unselec_3->setVisible(true);
}

void GameSet::ChageMode(Text *selected, Text *unselec_1, Text *unselec_2) {
	selected->setTextColor(Color4B(255, 255, 255, 255));
	selected->enableShadow(Color4B(110, 110, 110, 255));

	unselec_1->setTextColor(Color4B(0, 0, 0, 255));
	unselec_1->enableShadow(Color4B(110, 110, 110, 0));
	unselec_2->setTextColor(Color4B(0, 0, 0, 255));
	unselec_2->enableShadow(Color4B(110, 110, 110, 0));
}


bool  GameSet::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)//Ĳ�I�}�l�ƥ�
{
	Point touchLoc = pTouch->getLocation();
	if (rPR.containsPoint(touchLoc)){
		SimpleAudioEngine::getInstance()->playEffect("./Audio/button.WAV", false);
		ChageAni(_PR, _PY, _PG, _PB, Color3B(180, 53, 44));
	}
	else if (rPY.containsPoint(touchLoc)) {
		SimpleAudioEngine::getInstance()->playEffect("./Audio/button.WAV", false);
		ChageAni(_PY, _PR, _PG, _PB, Color3B(134,140,43));
	}
	else if (rPG.containsPoint(touchLoc)) {
		SimpleAudioEngine::getInstance()->playEffect("./Audio/button.WAV", false);
		ChageAni(_PG, _PY, _PR, _PB, Color3B(40,97,42));
	}
	else if (rPB.containsPoint(touchLoc)) {
		SimpleAudioEngine::getInstance()->playEffect("./Audio/button.WAV", false);
		ChageAni(_PB, _PY, _PG, _PR, Color3B(40,91,143));
	}


	if (rEasy.containsPoint(touchLoc)) {
		SimpleAudioEngine::getInstance()->playEffect("./Audio/button.WAV", false);
		ChageMode(_Easy, _Normal, _Hard);
		Mode = 1;
	}
	else if (rNormal.containsPoint(touchLoc)) {
		SimpleAudioEngine::getInstance()->playEffect("./Audio/button.WAV", false);
		ChageMode(_Normal, _Easy, _Hard);
		Mode = 2;
	}
	else if (rHard.containsPoint(touchLoc)) {
		SimpleAudioEngine::getInstance()->playEffect("./Audio/button.WAV", false);
		ChageMode(_Hard,_Normal, _Easy);
		Mode = 3;
	}
	
	_btnPlay->isTouched(touchLoc);
	_btnClose->isTouched(touchLoc);
	_btnTable->isTouched(touchLoc);

	return true;
}

void  GameSet::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //Ĳ�I���ʨƥ�
{
	Point touchLoc = pTouch->getLocation();

	_btnPlay->isLeave(touchLoc);
	_btnClose->isLeave(touchLoc);
	_btnTable->isLeave(touchLoc);
}

void  GameSet::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //Ĳ�I�����ƥ� 
{
	Point touchLoc = pTouch->getLocation();

	//�����
	if (_btnPlay->isUsed()) {
		//SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		bkmusic->stopBackgroundMusic();

		CCScene *scene = CCScene::create();
		auto *layer = GamePlay::createScene(Mode, PColor, PColor2,_STable);
		scene->addChild(layer);
		CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f, scene));
	}
	if (_btnClose->isUsed()) {
		_tableNode->setVisible(false);
		_btnClose->setVisible(false);
		_btnClose->setDisable(true);
		_btnTable->setVisible(true);
		_btnTable->setDisable(false);

	}
	if (_btnTable->isUsed()) {
		_tableNode->setVisible(true);
		_btnClose->setVisible(true);
		_btnClose->setDisable(false);
		_btnTable->setVisible(false);
		_btnTable->setDisable(true);

	}
	
}
