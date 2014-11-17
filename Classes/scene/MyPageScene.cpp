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

#include "UserData.h"

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
    NeglectHttpRequest::getInstance()->login([this](json11::Json json) {
        auto userNameText = utils::findChildByName<ui::Text*>(*_baseLayout, "Panel_main/Panel_unitStatus/Label_name");
        auto detailText = utils::findChildByName<ui::Text*>(*_baseLayout, "Panel_main/Panel_message/Label_message_1");
        
        // アカウント情報の表示
        auto account = UserData::create<UserData::TAccount>(json);
        
        if (account.description == "") {
            account.description = "特にお知らせはないわ";
        }
        detailText->setString(account.description);
        userNameText->setString(account.name);
        
        // TODO: Playクエスト情報の表示（通信でもらってない）
    });
    
    auto winSize = Director::getInstance()->getVisibleSize();
    // CocosStudioのLayout読み込み
    this->_baseLayout = CSLoader::getInstance()->createNodeFromXML("MyPageScene.csd");
    this->_baseLayout->setPosition(winSize.width/2 - this->_baseLayout->getContentSize().width/2,
                                   winSize.height/2 - this->_baseLayout->getContentSize().height/2);
    this->addChild(this->_baseLayout);
    
    auto header = CommonHeaderParts::create();
    header->setTitleText("マイページ");
    this->addChild(header);

    auto fotter = CommonFotterParts::create();
    fotter->setLockMenu(1);
    this->addChild(fotter);
    
    return true;
}
