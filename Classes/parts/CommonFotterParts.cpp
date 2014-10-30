//
//  CommonFotterParts.cpp
//  NeglecClient
//
//  Created by kyokomi on 2014/10/28.
//
//

#include "CommonFotterParts.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "NeglectSceneHelper.h"

USING_NS_CC;

using namespace cocostudio;
using namespace ui;

CommonFotterParts::CommonFotterParts()
{
    
}

CommonFotterParts::~CommonFotterParts()
{
    
}

bool CommonFotterParts::init()
{
    if (!Layer::init()) {
        return false;
    }
    auto winSize = Director::getInstance()->getVisibleSize();
    
    // create Header
    this->_baseLayout = CSLoader::getInstance()->createNodeFromXML("FotterParts.csd");
    _baseLayout->setContentSize(cocos2d::Size(winSize.width, _baseLayout->getContentSize().height));
    _baseLayout->setPosition(cocos2d::Vec2(winSize.width/2, _baseLayout->getContentSize().height/2));
    
    // Button setting
    utils::findChildByName<ui::Button*>(*_baseLayout, "Panel_main/Button_1")->addClickEventListener([](Ref *ref){
        NeglectSceneHelper::replaceScene(NeglectSceneHelper::SceneID::MY_PAGE);
    });
    utils::findChildByName<ui::Button*>(*_baseLayout, "Panel_main/Button_2")->addClickEventListener([](Ref *ref){
        NeglectSceneHelper::replaceScene(NeglectSceneHelper::SceneID::QUEST_LIST);
    });
    utils::findChildByName<ui::Button*>(*_baseLayout, "Panel_main/Button_3")->addClickEventListener([](Ref *ref){
        // 倉庫へ
        CCLOG("まだ未実装");
    });
    utils::findChildByName<ui::Button*>(*_baseLayout, "Panel_main/Button_4")->addClickEventListener([](Ref *ref){
        // お店へ
        CCLOG("まだ未実装");
    });
    utils::findChildByName<ui::Button*>(*_baseLayout, "Panel_main/Button_5")->addClickEventListener([](Ref *ref){
        // メニュー
        CCLOG("まだ未実装");
        NeglectSceneHelper::replaceScene(NeglectSceneHelper::SceneID::QUEST_DETAIL);
    });
    
    this->addChild(_baseLayout);
    
    return true;
}

void CommonFotterParts::setLockMenu(int menuId)
{
    auto button = utils::findChildByName<ui::Button*>(*_baseLayout, cocos2d::StringUtils::format("Panel_main/Button_%d", menuId));
    button->setTitleColor(Color3B::GREEN);
    button->setColor(Color3B::GREEN);
    button->setEnabled(false);
}
