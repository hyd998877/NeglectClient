//
//  MyPageScene.cpp
//  NeglecClient
//
//  Created by kyokomi on 2014/10/27.
//
//

#include "MyPageScene.h"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "CommonHeaderParts.h"
#include "CommonFotterParts.h"

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
        
        auto userNameText = utils::findChildByName<ui::Text*>(*_baseLayout, "Panel_main/Panel_unitStatus/Label_name");
        auto detailText = utils::findChildByName<ui::Text*>(*_baseLayout, "Panel_main/Panel_message/Label_message_1");
        
        auto detail = json["Description"].string_value();
        if (detail == "") {
            detail = "特にお知らせはないわ";
        }
        detailText->setString(detail);
        userNameText->setString(json["Name"].string_value());
    });
    
    // TODO: Loading表示（画面ロック）

    // CocosStudioのLayout読み込み
    this->_baseLayout = GUIReader::getInstance()->widgetFromJsonFile("MyPageScene.json");
    this->addChild(this->_baseLayout);
    
    auto header = CommonHeaderParts::create();
    this->addChild(header);

    auto fotter = CommonFotterParts::create();
    fotter->setLockMenu(1);
    this->addChild(fotter);
    
    return true;
}



