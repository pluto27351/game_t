#include "CEnemy.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;
using namespace CocosDenshion;

CEnemy::~CEnemy() {

}

CEnemy::CEnemy() {
	_action = CSLoader::createNode("Ani/Obstale.csb");
	_actionAni = (ActionTimeline *)CSLoader::createTimeline("Ani/Obstale.csb");
	/*Node *_fire = CSLoader::createNode("Ani/Fire.csb");
	ActionTimeline *_fireAni = (ActionTimeline *)CSLoader::createTimeline("Ani/Fire.csb");*/

	pt = Vec2(950, 300);

	_action->setPosition(pt);
	//_fire->setPosition(pt - Vec2(8.96,2.03));
	this->addChild(_action, 1);
	//this->addChild(_fire, 2);
	_action->runAction(_actionAni);
	//_fire->runAction(_fireAni);

	//callback function ���ʵe+����
	_actionAni->setLastFrameCallFunc([=]()
	{
		moveAni();
	});

	_actionAni->gotoFrameAndPlay(0, 40, false);  //35
	//_fireAni->gotoFrameAndPlay(0, 40, false);

}

void CEnemy::moveAni() {
	//���ʵe
	/*this->removeChild(_action);
	_action = CSLoader::createNode("Ani/EnemyMove.csb");
	_actionAni = (ActionTimeline *)CSLoader::createTimeline("Ani/EnemyMove.csb");
	_action->setPosition(pt);
	_action->runAction(_actionAni);
	this->addChild(_action, 1);
	_actionAni->gotoFrameAndPlay(0, 14, true);*/

	//����
	MoveTo *_moveAction = cocos2d::MoveTo::create(1.5f, Point(0, pt.y));
	auto callback = CallFunc::create(this, callfunc_selector(CEnemy::lifeEnd));
	_action->runAction(Sequence::create(_moveAction, callback, NULL));

}

void CEnemy::lifeEnd(){
	// do something on complete
	GoDie = true;
	CCLOG("action completed!");
}

int CEnemy::collider(Point player) {
	Size s = _action->getContentSize();
	Rect colliderArea;
	pt = _action->getPosition();
	colliderArea = Rect(pt.x - 50,pt.y-50,100,130);
	if (colliderArea.containsPoint(player)) return 2;  //����
	else if (_action->getPositionX() < 120) return 1;  //���\
	else return 0;									   //�٦����|
}

void CEnemy::actionControl(bool run) {
	if (run) {
		_action->onEnter();
	}
	else {
		_action->onExit();
	}
}

//Point CCharacter::getPosition() {
//	return (_action->getPosition() + Vec2(0,65));
//}


