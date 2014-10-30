//
//  QuestPlayScene.cpp
//  NeglecClient
//
//  Created by kyokomi on 2014/10/30.
//
//

#include "QuestPlayScene.h"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "CommonHeaderParts.h"
#include "CommonFotterParts.h"

#include "NeglectHttpRequest.h"

USING_NS_CC;
using namespace cocos2d::network;
using namespace cocostudio;

QuestPlayScene::QuestPlayScene()
: _baseLayout(nullptr)
{
    
}

QuestPlayScene::~QuestPlayScene()
{
    
}

// on "init" you need to initialize your instance
bool QuestPlayScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    // login通信
    //    NeglectHttpRequest::questDetail(1, [this](long statusCode, std::string response) {
    //        std::string err = "";
    //        auto json = json11::Json::parse(response, err);
    //
    //        if (!err.empty()) {
    //            CCLOG("json parse error %s", err.c_str());
    //            return;
    //        }
    //
    //
    //    });
    
    // TODO: Loading表示（画面ロック）
    
    auto winSize = Director::getInstance()->getVisibleSize();
    // CocosStudioのLayout読み込み
    this->_baseLayout = CSLoader::getInstance()->createNodeFromXML("QuestPlayScene.csd");
    this->_baseLayout->setPosition(winSize.width/2 - this->_baseLayout->getContentSize().width/2,
                                   winSize.height/2 - this->_baseLayout->getContentSize().height/2);
    this->addChild(this->_baseLayout);
    
    auto header = CommonHeaderParts::create();
    header->setTitleText("最果ての洞窟 最下層 99F");
    this->addChild(header);
    
    auto fotter = CommonFotterParts::create();
    this->addChild(fotter);
    
    return true;
}
