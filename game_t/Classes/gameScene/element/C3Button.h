#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;
using namespace CocosDenshion;

class C3Button : public cocos2d::Node
{
private:
	Point pt;
	Rect touchArea;
	char *_normal, *_touched, *_disable;
	Sprite *_show;

	bool isDisable = false;
public:
	bool touchedFlag=false;
	~C3Button();
	C3Button();
	C3Button(Point,char *, char *,char *);
	void isTouched(Point );
	void isLeave(Point);
	bool isUsed();
	void setDisable(bool);

	// implement the "static create()" method manually
	CREATE_FUNC(C3Button);
};

