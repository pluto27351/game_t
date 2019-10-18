#include "CBullet.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;
using namespace CocosDenshion;

CBullet::~CBullet() {
}

CBullet::CBullet() {
}

CBullet::CBullet(Point pt) {
	_bullet = Sprite::createWithSpriteFrameName("triblock.png");
	_bullet->setPosition(pt);
	_bullet->setScale(-0.243, 0.243);
	_bullet->setRotation(-90);
	this->addChild(_bullet, 1);

	ccBezierConfig bezier;
	bezier.controlPoint_1 = Point(500, 900);
	bezier.controlPoint_2 = Point(850, 600);
	bezier.endPosition = Point(1136, 340);
	BezierTo *bezierto = BezierTo::create(1.5f, bezier);
	auto callback = CallFunc::create(this, callfunc_selector(CBullet::GoDie));
	_bullet->runAction(Sequence::create(bezierto, callback, NULL));

}

void CBullet::GoDie() {
	dieFlag = true;
	CCLOG("bullet die");
}

Rect CBullet::colliArea() {
	Rect c;
	c = Rect(_bullet->getPositionX() - 25 , _bullet->getPositionY() - 25 ,50 ,45);
	return (c);
}

Point CBullet::getPosition() {
	return ( _bullet->getPosition());
}

void CBullet::actionControl(bool run) {
	if (run) {
		_bullet->onEnter();
	}
	else {
		_bullet->onExit();
	}
}