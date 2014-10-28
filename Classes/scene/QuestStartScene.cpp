//
//  QuestStartScene.cpp
//  NeglecClient
//
//  Created by kyokomi on 2014/10/28.
//
//

#include "QuestStartScene.h"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "CommonHeaderParts.h"
#include "CommonFotterParts.h"

#include "NeglectHttpRequest.h"

USING_NS_CC;
using namespace cocos2d::network;
using namespace cocostudio;

QuestStartScene::QuestStartScene()
: _baseLayout(nullptr)
{
    
}

QuestStartScene::~QuestStartScene()
{
    
}

// on "init" you need to initialize your instance
bool QuestStartScene::init()
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
    
    // CocosStudioのLayout読み込み
    this->_baseLayout = GUIReader::getInstance()->widgetFromJsonFile("QuestStartScene.json");
    this->addChild(this->_baseLayout);
    
    auto header = CommonHeaderParts::create();
    this->addChild(header);
    
    auto fotter = CommonFotterParts::create();
    this->addChild(fotter);
    
    return true;
}