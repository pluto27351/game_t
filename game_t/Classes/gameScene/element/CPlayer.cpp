#include "CPlayer.h"
//#include "cocostudio/CocoStudio.h"
//#include "ui/CocosGUI.h"
//#include "CBullet.h"

USING_NS_CC;

//using namespace cocostudio::timeline;
//using namespace ui;
//using namespace CocosDenshion;

// on "init" you need to initialize your instance
CPlayer::~CPlayer()
{
	if (hasBullet) {
		CBullet *b = _HeadBullet;
		while (b != NULL) {
			CBullet *die = b;
			b = b->next;
			delete b;
		}
	}
}
CPlayer::CPlayer()
{

}
CPlayer::CPlayer(Color3B color, Color3B color2)
{
	//圖片
	pt = Vec2(154.5, 350);
	_Player = CSLoader::createNode("Ani/Runner.csb");
	_Player->setPosition(pt);
	_Player->setScale(-0.88, 0.88);
	Sprite *_body = (cocos2d::Sprite *)_Player->getChildByName("body");
	Sprite *_mouth = (cocos2d::Sprite *)_Player->getChildByName("Normal")->getChildByName("mouth");
	_body->setColor(color);
	_mouth->setColor(color);

	this->addChild(_Player);

	_PlayerAni = (ActionTimeline *)CSLoader::createTimeline("Ani/Runner.csb");
	_Player->runAction(_PlayerAni);


	this->color = color;
	this->color2 = color2;

	//血條
	_hp = LoadingBar::create("sliderProgress.png", 100);
	_hp->setPosition(pt + Vec2(-6.5, -125));
	_hp->setColor(Color3B(255, 0, 0));
	_hp->setDirection(LoadingBar::Direction::LEFT);
	this->addChild(_hp, 2);
	_mp = LoadingBar::create("sliderProgress.png", 100);
	_mp->setPosition(pt + Vec2(-6.5,-150));
	_mp->setColor(Color3B(0,129,255));
	_mp->setDirection(LoadingBar::Direction::LEFT);
	this->addChild(_mp, 2);

}

void CPlayer::start() {
	_PlayerAni->gotoFrameAndPlay(0, 24, true);
}

//子彈生成
void CPlayer::RenderBullet() {
	if (_mp->getPercent() > 10) {
		hasBullet = true;
		CBullet *_NewBullet = new CBullet(Vec2(_Player->getPositionX(), _Player->getPositionY() + 105));

		if (_HeadBullet == NULL) {
			_HeadBullet = _NewBullet;
			_LastBullet = _HeadBullet;
		}
		else {
			_LastBullet->next = _NewBullet;
			_LastBullet = _NewBullet;
		}

		this->addChild(_NewBullet, 2);

		float m = _mp->getPercent();
		m = m - 10;
		_mp->setPercent(m);

		BulletFlag = true;
	}
}

//跳躍動作
void CPlayer::JumpAct() {
	_Player->stopActionByTag(1);
	JumpFlag = true;

	Sequence *sequence;
	JumpTo *jumpAction = cocos2d::JumpTo::create(0.6f, pt, 200, 1);
	CallFunc *callback = CallFunc::create(this, callfunc_selector(CPlayer::JumpFlagChange));
	if (JumpTime == 0) {
		sequence = Sequence::create(jumpAction, callback, NULL);
	}
	else {
		RotateBy *rotateto = RotateBy::create(0.6f, 360.0f);
		Spawn *spawn = Spawn::createWithTwoActions(jumpAction, rotateto);
		sequence = Sequence::create(spawn, callback, NULL);
	}

	sequence->setTag(1);
	JumpTime += 1;

	_Player->runAction(sequence);
}

//避免多重觸碰
void CPlayer::JumpFlagChange() {
	//JumpFlag = false;
	JumpTime = 0;
}

//殺死不用的子彈
void CPlayer::killbullet() {
	if (_HeadBullet != NULL) {
		if (_HeadBullet->dieFlag) {
			CBullet *_dieBullet = _HeadBullet;
			_HeadBullet = _HeadBullet->next;

			this->removeChild(_dieBullet);
			delete _dieBullet;

			if (_HeadBullet == NULL) hasBullet = false;
		}
	}
}

Point CPlayer::getPosition() {
	return (_Player->getPosition() - Vec2(0, 50));
}

//變臉變色
void CPlayer::changeFace(int mood) {
	Layout *_normal = (cocos2d::ui::Layout *)_Player->getChildByName("Normal");
	Layout *_happy = (cocos2d::ui::Layout *)_Player->getChildByName("Happy");
	Layout *_sad = (cocos2d::ui::Layout *)_Player->getChildByName("Sad");
	Sprite *_body = (cocos2d::Sprite *)_Player->getChildByName("body");
	Sprite *_mouth;
	switch (mood) {
	case 0:  //normal
		_mouth = (cocos2d::Sprite *)_normal->getChildByName("mouth");

		_normal->setVisible(true);
		_happy->setVisible(false);
		_sad->setVisible(false);

		_body->setColor(color);
		_mouth->setColor(color);
		ChangeFlag = false;
		break;
	case 1:  //happy
		_mouth = (cocos2d::Sprite *)_happy->getChildByName("mouth");
		_normal->setVisible(false);
		_happy->setVisible(true);
		_sad->setVisible(false);
		_body->setColor(color2);
		_mouth->setColor(color2);
		ChangeFlag = true;
		break;
	case 2:  //sad
		_mouth = (cocos2d::Sprite *)_sad->getChildByName("mouth");
		Sprite *_eyebrow = (cocos2d::Sprite *)_sad->getChildByName("eyebrow");
		_normal->setVisible(false);
		_happy->setVisible(false);
		_sad->setVisible(true);
		_body->setColor(color2);
		_mouth->setColor(color2);
		_eyebrow->setColor(color2);
		ChangeFlag = true;
		break;
	}

}

void CPlayer::decreaseHP() {
	float h = _hp->getPercent();
	h -= 5;
	_hp->setPercent(h);
}

int CPlayer::jumpCollider(Point enemy) {
	Rect colliderArea;
	colliderArea = Rect(_Player->getPositionX() - 65, _Player->getPositionY() - 20,180, 120);
	if (colliderArea.containsPoint(enemy)) return 2;  //失敗
	else if (enemy.x < 140) return 1;  //成功
	else return 0;									   //還有機會
}

bool CPlayer::bulletCollider(Point boss) {
	Rect c = _HeadBullet->colliArea();
	if (c.containsPoint(boss)) {
		_HeadBullet->dieFlag = true;
		return (true);
	}
	else return (false);
}

//停止動畫
void CPlayer::actionControl(bool run) {
	if (run) {
		_Player->onEnter();
	}
	else {
		_Player->onExit();
	}
	if (hasBullet) {
		CBullet *b = _HeadBullet;
		while (b != NULL) {
			b->actionControl(run);
			b = b->next;
		}
	}
}



