//
//  StartScene.cpp
//  NeglecClient
//
//  Created by kyokomi on 2014/11/23.
//
//

#include "StartScene.h"

#include "ui/CocosGUI.h"
#include "CSLoaderUtil.h"

#include "CommonPopupLayer.h"

#include "NeglectHttpRequest.h"
#include "NeglectSceneHelper.h"

#include "LoadingDialogLayer.h"

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
    NeglectHttpRequest::getInstance()->setLoadingTarget(this);
}

void StartScene::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
}

void StartScene::initView()
{
    auto winSize = Director::getInstance()->getVisibleSize();
    // CocosStudioのLayout読み込み
    this->_baseLayout = CSLoaderUtil::create("StartScene");
    this->_baseLayout->setPosition(winSize.width/2 - this->_baseLayout->getContentSize().width/2,
                                   winSize.height/2 - this->_baseLayout->getContentSize().height/2);
    this->addChild(this->_baseLayout);
    
    // Button
    this->_startButton = utils::findChildByName<ui::Button*>(*this->_baseLayout, "Button_start");
    this->_startButton->addClickEventListener([this](Ref *ref) {
        this->requestLogin();
    });
    
    auto localModeButton = utils::findChildByName<ui::Button*>(*this->_baseLayout, "Button_localMode");
    localModeButton->addClickEventListener([localModeButton](Ref *ref) {
        if (NeglectHttpRequest::getInstance()->isLocalMode()) {
            NeglectHttpRequest::getInstance()->offLocalMode();
            localModeButton->setTitleText("LOCAL_MODE_OFF");
        } else {
            NeglectHttpRequest::getInstance()->onLocalMode();
            localModeButton->setTitleText("LOCAL_MODE_ON");
        }
    });
}

void StartScene::requestLogin()
{
    auto dataLoadFunc = std::bind(&NeglectHttpRequest::dataMasterLoad, NeglectHttpRequest::getInstance(), [](json11::Json json) {
        // Mypageへ
        NeglectSceneHelper::replaceScene(NeglectSceneHelper::SceneID::MY_PAGE);
    }, [this](long statusCode, std::string error) {
        // TODO: login失敗のダイアログ -> リトライボタン
        auto errorMessage = StringUtils::format("dataMasterLoad error [%ld] %s", statusCode, error.c_str());
        CCLOG("%s", errorMessage.c_str());
        CommonPopupLayer::show(this, "通信エラー", errorMessage, [](Ref *ref){});
    });
    
    // login通信
    NeglectHttpRequest::getInstance()->login([dataLoadFunc](json11::Json json) {
        dataLoadFunc();
    }, [this](long statusCode, std::string error) {
        // TODO: login失敗のダイアログ -> リトライボタン
        auto errorMessage = StringUtils::format("login error [%ld] %s", statusCode, error.c_str());
        CCLOG("%s", errorMessage.c_str());
        CommonPopupLayer::show(this, "通信エラー", errorMessage, [](Ref *ref){});
    });
}
