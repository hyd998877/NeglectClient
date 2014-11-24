//
//  StartScene.cpp
//  NeglecClient
//
//  Created by kyokomi on 2014/11/23.
//
//

#include "StartScene.h"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "NeglectHttpRequest.h"
#include "NeglectSceneHelper.h"

//#include "UserData.h"
//#include "MasterData.h"

USING_NS_CC;
using namespace cocos2d::network;
using namespace cocostudio;

StartScene::StartScene()
: _baseLayout(nullptr)
, _startButton(nullptr)
{
    
}

StartScene::~StartScene()
{
    
}

// on "init" you need to initialize your instance
bool StartScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init()) {
        return false;
    }
    
    this->initView();
    
    return true;
}

void StartScene::onEnter()
{
    Layer::onEnter();
    
    this->requestLogin();
}

void StartScene::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
}

void StartScene::initView()
{
    auto winSize = Director::getInstance()->getVisibleSize();
    // CocosStudioのLayout読み込み
    this->_baseLayout = CSLoader::getInstance()->createNodeFromXML("StartScene.csd");
    this->_baseLayout->setPosition(winSize.width/2 - this->_baseLayout->getContentSize().width/2,
                                   winSize.height/2 - this->_baseLayout->getContentSize().height/2);
    this->addChild(this->_baseLayout);
    
    // Button
    this->_startButton = utils::findChildByName<ui::Button*>(*this->_baseLayout, "Button_start");
}

void StartScene::requestLogin()
{
    // login通信
    NeglectHttpRequest::getInstance()->login([this](json11::Json json) {
        // Mypageへ
        this->_startButton->addClickEventListener([](Ref *ref) {
            NeglectSceneHelper::replaceScene(NeglectSceneHelper::SceneID::MY_PAGE);
        });
    }, [](long statusCode, std::string error) {
        // TODO: login失敗のダイアログ -> リトライボタン
        CCLOG("login error[%ld] %s", statusCode, error.c_str());
    });
}
