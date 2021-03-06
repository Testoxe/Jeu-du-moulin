﻿#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include "MenuScene.h"
#include "GameplayScene.h"
#include "SimpleAudioEngine.h"
#include "Gif/GifBase.h"
#include "Gif/InstantGif.h"
#include "Gif/CacheGif.h"
#include "Enums.h"
#define ANIMATED_SLPASH_SHOW_TIME 2.0f
USING_NS_CC;

using namespace CocosDenshion;
Scene* MenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = MenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{

	// init origin & visible size
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();



	//Setting the backgroun audio
	auto audio = SimpleAudioEngine::getInstance();

	// set the background music and continuously play it.
	if(!audio->isBackgroundMusicPlaying())audio->playBackgroundMusic("SpongeBob Closing Theme Song.mp3", true);


	//the animated splash
	std::string name = "animatedSplash.gif";
	name = FileUtils::getInstance()->fullPathForFilename(name.c_str());
	GifBase *splash = InstantGif::create(name.c_str());//InstantGif ：parsing and playing at the same time
	splash->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(splash, -1);
	rX = visibleSize.width / splash->getContentSize().width;
	rY = visibleSize.height / splash->getContentSize().height;
	splash->setScaleX(rX);	
	splash->setScaleY(rY);

	//Menu 1 configuration
	menu1 = Layer::create();
	
	Button *PlayervPlayerButton = Button::create("res/playerVSplayer.png", "res/playerVSplayer.png");//InstantGif ：parsing and playing at the same time
	PlayervPlayerButton->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height*0.58f + origin.y));
	menu1->addChild(PlayervPlayerButton);
	PlayervPlayerButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::ENDED:
			GameplayScene* newScene  = GameplayScene::create();
			newScene->setGameType(GameTypes::pvp);
			Director::getInstance()->replaceScene(TransitionFade::create(0.5f, newScene));
			
		}
	});

	menu1->setScale(rY);
	this->addChild(menu1);

    return true;
}



void MenuScene::ShowMenu(Layer* menutoShow, Layer* menutoHide) {

	//Pop up animation (Showing off)
	auto nullify = ScaleTo::create(0, 0);
	auto showup = ScaleTo::create(0.4F, 1*rY);
	EaseBackOut *easeAction = EaseBackOut::create(showup);
	auto BoxAnimation = Sequence::create(nullify, easeAction, nullptr);

	//Show the menutoShow and hide menutoHide
	menutoShow->setVisible(true); 
	menutoHide->setVisible(false); 
	menutoShow->runAction(BoxAnimation); 

}

void MenuScene::switchToMenu(float dt) {
	ShowMenu(menu1, menu2);
}
