//
//  CommonFotterParts.cpp
//  NeglecClient
//
//  Created by kyokomi on 2014/10/28.
//
//

#include "CommonFotterParts.h"

#include "WidgetUtil.h"
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
    // create Header
    _baseLayout = WidgetUtil::widgetFotterFromJsonFile("FotterParts.json");
    // Button setting
    _baseLayout->getChildByName<ui::Button*>("Button_1")->addClickEventListener([](Ref *ref){
        NeglectSceneHelper::replaceScene(NeglectSceneHelper::SceneID::MY_PAGE);
    });
    _baseLayout->getChildByName<ui::Button*>("Button_2")->addClickEventListener([](Ref *ref){
        NeglectSceneHelper::replaceScene(NeglectSceneHelper::SceneID::QUEST_LIST);
    });
    _baseLayout->getChildByName<ui::Button*>("Button_3")->addClickEventListener([](Ref *ref){
        // 倉庫へ
        CCLOG("まだ未実装");
    });
    _baseLayout->getChildByName<ui::Button*>("Button_4")->addClickEventListener([](Ref *ref){
        // お店へ
        CCLOG("まだ未実装");
    });
    _baseLayout->getChildByName<ui::Button*>("Button_5")->addClickEventListener([](Ref *ref){
        // メニュー
        CCLOG("まだ未実装");
    });
    
    this->addChild(_baseLayout);
    
    return true;
}

void CommonFotterParts::setLockMenu(int menuId)
{
    auto button = _baseLayout->getChildByName<ui::Button*>(cocos2d::StringUtils::format("Button_%d", menuId));
    button->setTitleColor(Color3B::GREEN);
    button->setColor(Color3B::GREEN);
    button->setEnabled(false);
}
