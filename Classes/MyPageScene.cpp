//
//  MyPageScene.cpp
//  NeglecClient
//
//  Created by kyokomi on 2014/10/27.
//
//

#include "MyPageScene.h"

#include "WidgetUtil.h"

#include "ui/UIListView.h"
#include "ui/UIText.h"

#include "NeglectHttpRequest.h"

USING_NS_CC;
using namespace cocos2d::network;
using namespace cocostudio;

MyPageScene::MyPageScene()
: _baseLayout(nullptr)
{
    
}

MyPageScene::~MyPageScene()
{
    
}

Scene* MyPageScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MyPageScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MyPageScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    // login通信
    NeglectHttpRequest::login([this](long statusCode, std::string response) {
        std::string err = "";
        auto json = json11::Json::parse(response, err);
        
        if (!err.empty()) {
            CCLOG("json parse error %s", err.c_str());
            return;
        }
        
//        // クエスト情報取得（要login）
//        NeglectHttpRequest::questList([](long statusCode, std::string response) {
//            
//        });
    });
    
    // TODO: Loading表示（画面ロック）

    // CocosStudioのLayout読み込み
    this->_baseLayout = GUIReader::getInstance()->widgetFromJsonFile("MyPageScene.json");
    this->addChild(this->_baseLayout);
    
    auto header = WidgetUtil::widgetHeaderFromJsonFile("HeaderParts.json");
    this->addChild(header);
    
    auto fotter = WidgetUtil::widgetFotterFromJsonFile("FotterParts.json");
    this->addChild(fotter);
    
    return true;
}



