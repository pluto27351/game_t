#include "CBoss.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#define HP 25
#define SPEED 3.0
#define Red Color3B(209,73,63)
#define Red2 Color3B(180,53,44)
#define Yellow Color3B(200,209,63)
#define Yellow2 Color3B(134,140,43)
#define Green Color3B(75,155,77)
#define Green2 Color3B(40,97,42)
#define Blue Color3B(82,131,151)
#define Blue2 Color3B(40,91,143)

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;
using namespace CocosDenshion;

CBoss::~CBoss() {

}

CBoss::CBoss(int mode,int num) {
	Mode = mode, Num = num;   // num->速度 血量
	int i = random(1, 3);
	int j = random(1, 4);
	switch (i) {
		case 1:
			runner = "Ani/Runner2.csb";   break;
		case 2:
			runner = "Ani/Runner3.csb";   break;
		case 3:
			runner = "Ani/Runner4.csb";   break;
	}
	switch (j) {
		case 1:
			color  = Red;   color2 = Red2;   break;
		case 2:
			color  = Yellow;   color2 = Yellow2;   break;
		case 3:
			color  = Green;   color2 = Green2;  break;
		case 4:
			color  = Blue;   color2 = Blue2;  break;
	}

	derseHP = HP - ( Num * 5);   // 25,20,15,10,5
	reHP = 25 + (10 * Num);      // 25,35,45,55,65
	speed = SPEED - (Num / 2)*0.5;			//3.0,2.5,2.0

	//載入動畫
	pt = Vec2(1407, 340);
	_action = CSLoader::createNode(runner);
	_actionAni = (ActionTimeline *)CSLoader::createTimeline(runner);
	_action->setPosition(pt); _action->setScale(-0.8,0.8);
	this->addChild(_action, 1);
	_action->runAction(_actionAni);

	//改顏色
	Sprite *_body = (cocos2d::Sprite *)_action->getChildByName("body");
	Sprite *_mouth = (cocos2d::Sprite *)_action->getChildByName("Normal")->getChildByName("mouth");
	Sprite *_mouth2 = (cocos2d::Sprite *)_action->getChildByName("Sad")->getChildByName("mouth");
	_body->setColor(color);
	_mouth->setColor(color);
	_mouth2->setColor(color2);

	//進場
	MoveTo *_moveAction = cocos2d::MoveTo::create(2.0f, Point(1136, pt.y));
	auto callback = CallFunc::create(this, callfunc_selector(CBoss::running));
	_action->runAction(Sequence::create(_moveAction, callback, NULL));

	_actionAni->gotoFrameAndPlay(0, 24, true);

}

void CBoss::running() {
	pt = _action->getPosition();

	_hp = LoadingBar::create("sliderProgress.png", 100);
	_hp->setColor(Color3B(255,0,0));
	_hp->setPosition(Vec2(pt.x, pt.y - 120));
	_hp->setDirection(LoadingBar::Direction::LEFT);

	startAttacked = true;
	colliderArea = Rect(pt.x - 90, pt.y - 77, 200, 200);
	this->addChild(_hp, 2);
}

bool CBoss::isAttacked(Point bullet) {
	if (startAttacked) {
		if (colliderArea.containsPoint(bullet)) {
			decreaseHP();
			if (_hp->getPercent() > 0) changeFace(true);
			else { changeFace(false); moveAni(); }
			return true;
		}
		else return false;
	}
	return false;
}

void CBoss::decreaseHP() {
	float hp = _hp->getPercent();
	hp -= derseHP;
	_hp->setPercent(hp);

}

void CBoss::changeFace(bool callback) {
	Layout *_normal = (cocos2d::ui::Layout *)_action->getChildByName("Normal");
	Layout *_sad = (cocos2d::ui::Layout *)_action->getChildByName("Sad");
	Sprite *_body = (cocos2d::Sprite *)_action->getChildByName("body");
	_normal->setVisible(false);
	_sad->setVisible(true);
	_body->setColor(color2);
	_body->stopActionByTag(1);

	if (callback) {
		TintTo *tintto = TintTo::create(0.5f, color);
		auto callback = CallFunc::create(this, callfunc_selector(CBoss::changeFaceEnd));
		auto *s = Sequence::create(tintto, callback, NULL);
		s->setTag(1);
		_body->runAction(s);
		CCLOG("123");

	}
	
}

void CBoss::changeFaceEnd() {
	Layout *_normal = (cocos2d::ui::Layout *)_action->getChildByName("Normal");
	Layout *_sad = (cocos2d::ui::Layout *)_action->getChildByName("Sad");
	_normal->setVisible(true);
	_sad->setVisible(false);
	
}

void CBoss::moveAni() {
	isMoving = true;
	moveAct = cocos2d::MoveTo::create(speed, Point(-65, pt.y));
	auto callback = CallFunc::create(this, callfunc_selector(CBoss::lifeEnd));
	auto *sequence = Sequence::create(moveAct, callback, NULL);
	sequence->setTag(2);
	_action->runAction(sequence);
}

void CBoss::lifeEnd() {
	GoDie = true;
}


int CBoss::collider(Point player) {
	Rect colliderArea;
	colliderArea = Rect(_action->getPositionX() - 80, _action->getPositionY() - 70, 140, 150);
	if (colliderArea.containsPoint(player)) {     //失敗
		reback();
		return 2;
	}
	else if (_action->getPositionX() < 140) return 1;  //成功
	else return 0;									   //還有機會
}

void CBoss::reback() {
	Sprite *_body = (cocos2d::Sprite *)_action->getChildByName("body");
	_body->setColor(color);
	changeFaceEnd();

	_action->stopActionByTag(2);
	moveAct = cocos2d::MoveTo::create(3.0f, pt);
	auto callback = CallFunc::create(this, callfunc_selector(CBoss::reset));
	_action->runAction(Sequence::create(moveAct, callback, NULL));
}

void CBoss::reset() {
	isMoving = false;
	_hp->setPercent(reHP);
	hasColliEnd = false;
}

void CBoss::actionControl(bool run) {
	if (run) {
		_action->onEnter();
	}
	else {
		_action->onExit();
	}
}

