#include "C3Button.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;
using namespace CocosDenshion;

C3Button::~C3Button() {
	SimpleAudioEngine::getInstance()->unloadEffect("./Audio/button.WAV");
}

C3Button::C3Button(){

}

C3Button::C3Button(Point pt, char *n,char *t,char *d) {
	_normal = n; _touched = t; _disable = d;
	_show = Sprite::createWithSpriteFrameName(n);
	Size sz = _show->getContentSize();
	_show->setPosition(pt);
	touchArea = Rect(pt.x - sz.width / 2, pt.y - sz.height / 2, sz.width, sz.height);
	this->addChild(_show, 0);
	SimpleAudioEngine::getInstance()->preloadEffect("./Audio/button.WAV");
	
}

void C3Button::isTouched(Point touchPt){
	if (isDisable == false) {
		if (touchArea.containsPoint(touchPt)) {
			SimpleAudioEngine::getInstance()->playEffect("./Audio/button.WAV", false);
			touchedFlag = true;
			_show->setSpriteFrame(_touched);
			_show->setScale(1.2);
		}
	}
	
}
void C3Button::isLeave(Point touchPt) {
	if (touchedFlag) {
		if (touchArea.containsPoint(touchPt) == false) {
			touchedFlag = false;
			_show->setSpriteFrame(_normal);
			_show->setScale(1);
		}
	}
}
bool C3Button::isUsed() {
	if (touchedFlag) {
		_show->setSpriteFrame(_normal);
		_show->setScale(1);
		touchedFlag = false;
		return true;
	}
	return false;
}

void C3Button::setDisable(bool disable) {
	isDisable = disable;
	if (isDisable) {
		_show->setSpriteFrame(_disable);
		_show->setScale(1);
	}
	else {
		_show->setSpriteFrame(_normal);
		_show->setScale(1);
	}
}