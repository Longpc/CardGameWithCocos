#include "HelloWorldScene.h"

USING_NS_CC;
using namespace cocos2d;
using namespace std;
struct Card
{
	cocos2d::Sprite* fontSprite;
	cocos2d::Sprite* backSprite;
	int type;
};
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	pos1 = Vec2(visibleSize.width*0.125, visibleSize.height*0.75);
	pos2 = Vec2(visibleSize.width*0.375, visibleSize.height*0.75);
	pos3 = Vec2(visibleSize.width*0.625, visibleSize.height*0.75);
	pos4 = Vec2(visibleSize.width*0.875, visibleSize.height*0.75);
	pos5 = Vec2(visibleSize.width*0.125, visibleSize.height*0.25);
	pos6 = Vec2(visibleSize.width*0.375, visibleSize.height*0.25);
	pos7 = Vec2(visibleSize.width*0.625, visibleSize.height*0.25);
	pos8 = Vec2(visibleSize.width*0.875, visibleSize.height*0.25);
	posArray.push_back(pos1);
	posArray.push_back(pos2);
	posArray.push_back(pos3);
	posArray.push_back(pos4);
	posArray.push_back(pos5);
	posArray.push_back(pos6);
	posArray.push_back(pos7);
	posArray.push_back(pos8);
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    //this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
   // this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
   // this->addChild(sprite, 0);
	fontSprite = cocos2d::Sprite::create("0.png");
	fontSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	fontSprite->setScaleX(0);
	addChild(fontSprite, 1);
	backSprite = cocos2d::Sprite::create("back.png");
	backSprite->setPosition(fontSprite->getPosition());
	addChild(backSprite, 2);
	//fontSprite->setVisible(false);
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	srand(time(NULL));
	initGameData();
    return true;
}

bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	/*cocos2d::Rect rect = backSprite->getBoundingBox();
	cocos2d::Vec2 p = touch->getLocation();
	if (rect.containsPoint(p)) {

		runFlipAnimation(backSprite, fontSprite);
		return true;
	}
	rect = fontSprite->getBoundingBox();
	if (rect.containsPoint(p)) {
		runFlipAnimation(fontSprite, backSprite);
		return true;
	}
	return false; */
	cocos2d::Rect rect;
	cocos2d::Vec2 p = touch->getLocation();
	for (int i = 0; i < posArray.size(); i++) {
		rect = createClickDetectRect(posArray[i]);
		if (rect.containsPoint(p)) {
			clickNum +=1;
			if (saveCheckFlg == false && clickNum >2 &&clickNum%2 ==1 ) {
				closeCard();
			}
			//if (i + 1 == clickPos1 || i + 1 == clickPos2) return false;
			flipCardWithPositionTag(i + 1);
			cocos2d::log("HIT %d", i + 1);
			
			if (clickNum % 2 == 0) {
				if (clickPos1 != i + 1) {
					clickPos2 = i + 1;
					saveCheckFlg = checkGetScore();
				}
				else {
					clickNum -= 1;
				}
			}
			else {
				clickPos1 = i + 1;
			}
			return true;
		}
	}
	return false;
}
void HelloWorld::closeCard() {
	if (clickPos1 == clickPos2) return;
	cocos2d::log("Close: %d & %d", clickPos1, clickPos2);
	int saveIndex1;
	int saveIndex2;
	for (int i = 0; i < cardArray.size(); i++)
	{
		if (cardArray[i].tag == clickPos1) {
			saveIndex1 = i;
			continue;
		}
		if (cardArray[i].tag == clickPos2) {
			saveIndex2 = i;
			continue;
		}
	}
	cardArray[saveIndex1].open = false;
	runFlipAnimation(cardArray[saveIndex1].fontSprite, cardArray[saveIndex1].backSprite);
	cardArray[saveIndex2].open = false;
	runFlipAnimation(cardArray[saveIndex2].fontSprite, cardArray[saveIndex2].backSprite);
	//clickPos1 = -1;
	//clickPos2 = -1;
}
void HelloWorld::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
	cocos2d::log("TOuch ended");
	
}
void HelloWorld::onTouchMoved(cocos2d::Touch* touch, Event* event) {

}
void HelloWorld::onTouchCancelled(Touch* touch, Event* event) {

}
cocos2d::Rect HelloWorld::createClickDetectRect(Vec2 pos) {
	Sprite* temp = cocos2d::Sprite::create("back.png");
	cocos2d::Size size = temp->getContentSize();
	return cocos2d::CCRectMake(pos.x - size.width / 2, pos.y - size.height / 2, size.width, size.height);
}
void HelloWorld::initGameData() {
	cleanData();
	randomValueForArray();
	for (int i = 0; i < 4; i++) {
		cardArray.push_back(createCard(randomNumberArray[i]));
		cardArray.push_back(createCard(randomNumberArray[i]));
	}
	initGameAnimation();
}
void HelloWorld::initGameAnimation() {
	for (int i = 0; i < 8; i++) {
		while (showCard(rand() % 8, i) == false)
		{
		}
	}
}
bool HelloWorld::showCard(int no,int pos) {
	if (cardArray[no].onShow == true) return false;
	cardArray[no].tag = pos + 1;
	cardArray[no].onShow = true;
	cardArray[no].backSprite->setPosition(posArray[pos]);
	cardArray[no].fontSprite->setPosition(cardArray[no].backSprite->getPosition());
	addChild(cardArray[no].backSprite, 1);
	addChild(cardArray[no].fontSprite, 1);
	return true;
	
}
void HelloWorld::randomValueForArray() {
	int i = 0;
	int rnum = 0;
	while (i<4)
	{
		rnum = rand() % 14;
		if (rnum != randomNumberArray[0] && rnum != randomNumberArray[1] && rnum != randomNumberArray[2] && rnum != randomNumberArray[3]) {
			randomNumberArray[i] = rnum;
			i++;
		}
	}
}
HelloWorld::Card HelloWorld::createCard(int type) {
	HelloWorld::Card card;
	card.backSprite = cocos2d::Sprite::create("back.png");
	card.fontSprite = createSpriteWithType(type);
	card.fontSprite->setScaleX(0);
	card.type = type;
	return card;
}
cocos2d::Sprite* HelloWorld::createSpriteWithType(int type) {
	std::stringstream name;
	name << "" << type << ".png";
	return cocos2d::Sprite::create(name.str().c_str());
}
void HelloWorld::cleanData() {
	while (cardArray.size() > 0)
	{
		cardArray.erase(cardArray.begin());
	}
	for (int i = 0; i < 4; i++) {
		randomNumberArray[i] = -1;
	}
	removeAllChildren();
	clickPos1 = -1;
	clickPos2 = -1;
	remainCardNum = 8;
	clickNum = 0;
	saveCheckFlg = false;
}
void HelloWorld::flipCardWithPositionTag(int tag) {
	for (int i = 0; i < cardArray.size(); i++)
	{
		//cocos2d::log("tag: %d", cardArray[i].tag);
		if (cardArray[i].tag == tag ) {
			//cocos2d::log("in check");
			if (cardArray[i].open == false && cardArray[i].detected == false) {
				//open Card
				cardArray[i].open = true;
				runFlipAnimation(cardArray[i].backSprite, cardArray[i].fontSprite);
			}
			/*else {
				//Close card
				cardArray[i].open = false;
				runFlipAnimation(cardArray[i].fontSprite, cardArray[i].backSprite);
			}*/
			return;
		}
	}
}
void HelloWorld::runFlipAnimation(cocos2d::Sprite* beginS, cocos2d::Sprite* endS) {
	//if ()
	if (beginS->getNumberOfRunningActions() > 0 || endS->getNumberOfRunningActions() > 0) return;
	cocos2d::Vector<cocos2d::FiniteTimeAction*> actions;
	actions.pushBack(cocos2d::ScaleTo::create(0.4f,0,1));
	actions.pushBack(cocos2d::TargetedAction::create(endS,ScaleTo::create(0.4f,1)));
	auto sequence = cocos2d::Sequence::create(actions);
	beginS->runAction(sequence);
}
bool HelloWorld::checkGetScore() {
	if (clickPos1 < 0 || clickPos2 < 0 || clickPos1 == clickPos2) return false;
	int saveIndex1 = -1;
	int saveIndex2 = -1;
	for (int i = 0; i < cardArray.size(); i++)
	{
		if (cardArray[i].tag == clickPos1) {
			saveIndex1 = i;
			continue;
		}
		if (cardArray[i].tag == clickPos2) {
			saveIndex2 = i;
			continue;
		}
	}
	if(cardArray[saveIndex1].type == cardArray[saveIndex2].type) {
		cardArray[saveIndex1].detected = true;
		cardArray[saveIndex2].detected = true;
		remainCardNum -= 2;
		if (remainCardNum == 0) {
			//cleandata and repeat
			cocos2d::log("YOU WIN");
			CCDelayTime * delayAction = CCDelayTime::create(2);
			CCCallFunc * callFunc = CCCallFunc::create(this, callfunc_selector(HelloWorld::initGameData));
			this->runAction(CCSequence::createWithTwoActions(delayAction, callFunc));
		}
		return true;
	}
	return false;
	
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
