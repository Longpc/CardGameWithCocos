#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;
using namespace std;
class HelloWorld : public cocos2d::Layer
{
public:
	struct Card
	{
		cocos2d::Sprite* fontSprite;
		cocos2d::Sprite* backSprite;
		int type;
		int tag = 0;
		bool detected = false;
		bool onShow = false;
		bool open = false;
	};
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
private:
	///////CONST///////////////////
	 Vec2 pos1;
	 Vec2 pos2;
	 Vec2 pos3;
	 Vec2 pos4;
	 Vec2 pos5;
	 Vec2 pos6;
	 Vec2 pos7;
	 Vec2 pos8;
	///////VATIABLES///////////////
	 int clickPos1;
	 int clickPos2;
	 int clickNum = 0;
	 int remainCardNum = 8;
	 bool saveCheckFlg = false;
	std::vector<Card> cardArray;
	std::vector<Vec2> posArray;
	cocos2d::Sprite* fontSprite;
	cocos2d::Sprite* backSprite;
	int randomNumberArray[4];
	///////FUNCTION////////////////
	virtual void initGameData();
	virtual void initGameAnimation();
	virtual void flipCardWithPositionTag(int tag);
	virtual void closeCard();
	virtual void runFlipAnimation(cocos2d::Sprite* begin, cocos2d::Sprite* end);
	virtual void randomValueForArray();
	virtual Card createCard(int type);
	virtual cocos2d::Sprite* createSpriteWithType(int type);
	virtual bool showCard(int cardNo,int position);
	virtual cocos2d::Rect createClickDetectRect(Vec2 pos);
	virtual bool checkGetScore();
	virtual void cleanData();
};

#endif // __HELLOWORLD_SCENE_H__
