#include "CScore.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#define GetString UserDefault::getInstance()->getStringForKey
#define SetString UserDefault::getInstance()->setStringForKey
#define UserDefault UserDefault::getInstance()
#define k "E1"
USING_NS_CC;

using namespace std;
using namespace cocostudio::timeline;
using namespace ui;
using namespace CocosDenshion;

bool CScore::first = true;
CScore::~CScore() {

}

CScore::CScore(){
	UserDefault->setStringForKey("E1", "xxxxxxxxx");
	UserDefault->setStringForKey("E2", "xxxxxxxxx");
	UserDefault->setStringForKey("E3", "xxxxxxxxx");
	UserDefault->setStringForKey("N1", "xxxxxxxxx");
	UserDefault->setStringForKey("N2", "xxxxxxxxx");
	UserDefault->setStringForKey("N3", "xxxxxxxxx");
	UserDefault->setStringForKey("H1", "xxxxxxxxx");
	UserDefault->setStringForKey("H2", "xxxxxxxxx");
	UserDefault->setStringForKey("H3", "xxxxxxxxx");

	string ret = UserDefault->getStringForKey("string");

	if (UserDefault->isXMLFileExist()) //是否存在
	{
		string path = UserDefault->getXMLFilePath();
		CCLOG("XML file is exist!");
		CCLOG("XML file path : %s", path.c_str());
	}
	else
	{
		CCLOG("XML file is not exist!");
	}


	//保存数据
	UserDefault->flush();
	auto title = Label::createWithTTF("Score Table", "Marker Felt.ttf", 48);
	title->setColor(Color3B::WHITE);
	title->setPosition(Vec2(640,600));
	this->addChild(title, 1);
	for (int i = 0; i < 3; i++) {
		int y = 500;
		char no[3] = "E1";
		if (i == 0) {
			no[0] = 'E';
			auto Easy = Label::createWithTTF("Easy Score :", "Marker Felt.ttf", 40);
			Easy->setColor(Color3B::WHITE);
			Easy->setPosition(Vec2(500, y));
			this->addChild(Easy, 1);
		}
		else if (i == 1) {
			no[0] = 'N';
			y = 350;
			auto Normal = Label::createWithTTF("Normal Score :", "Marker Felt.ttf", 40);
			Normal->setColor(Color3B::WHITE);
			Normal->setPosition(Vec2(520, y));
			this->addChild(Normal, 1);
		}
		else {
			no[0] = 'H';
			y = 200;
			auto Hard = Label::createWithTTF("Hard Score :", "Marker Felt.ttf", 40);
			Hard->setColor(Color3B::WHITE);
			Hard->setPosition(Vec2(500, y));
			this->addChild(Hard, 1);
		}
		for (int j = 0; j < 3; j++) {
			int n = i * 3 + j;
			no[1] = j + 1+48;
			No[n] = Label::createWithTTF(UserDefault->getStringForKey(no), "Marker Felt.ttf", 30);
			No[n]->setColor(Color3B::WHITE);
			No[n]->setPosition(Vec2(730, y-j*50));
			this->addChild(No[n],1);
		}
	}

}

void CScore::setScore(int mode) {  //1.2.3
	for (int i = 0; i < 3; i++) {
		int num = (mode - 1) * 3 + i;
		auto n = No[num]->getString();
		if (n == "xxxxxxxxx") {
			upload(num);
			i = 3;
		}
		else if ((n[3]-48 > 7 - level)) {  //  no.5 >no.3  成績覆蓋
			upload(num);
			i = 3;
		}
		else if ((n[3] - 48 == 7-level)) {  //  //no.5 = no.5
			if (n[15] - 48 < score / 100) {    // 100 <200
				upload(num);
				i = 3;
			}
			else if (n[15] - 48 == score / 100) {   //100 =100
				if (n[16] - 48 < (score % 100) / 10) {  //10 <20
					upload(num);
					i = 3;
				}
				else if (n[16] - 48 == (score % 100) / 10) {  //10 = 10
					if (n[17] - 48 < (score % 100) % 10) {  // 1<2
						upload(num);
						i = 3;
					}
					else if (n[17] - 48 < (score % 100) % 10) {  // 1=2
						upload(num);
						i = 3;
					}
				}
			}
		
		}
		
	}
}

void CScore::upload(int num) {
	if (num % 3 == 0) {
		No[num + 2]->setString(No[num + 1]->getString());
		No[num + 1]->setString(No[num]->getString());
	}
	else if (num % 3 == 1) {
		No[num + 1]->setString(No[num]->getString());
	}

	char finscore[19] = ("No.1 / Score : 000");
	int n = score,j=1;
	finscore[3] = (7 - level + 48);
	for (int i = 15; i < 18; i++) {
		if(i == 15) finscore[i] = (n / 100) + 48;   //48 = 1的編號
		else if(i == 16) finscore[i] = (n % 100)/10 + 48;   //48 = 1的編號
		else finscore[i] = (n % 100) % 10 + 48;   //48 = 1的編號
		
	}
	No[num]->setString(finscore);
	CCLOG("11");
	update();
}

void CScore::update() {
	for (int i = 0; i < 3; i++) {
		char no[3] = "E1";
		if (i == 0) no[0] = 'E';
		else if (i == 1) no[0] = 'N';
		else no[0] = 'H';
		for (int j = 0; j < 3; j++) {
			int n = i * 3 + j;
			no[1] = j + 1 + 48;
			UserDefault->setStringForKey(no, No[n]->getString());
		}
	}
}