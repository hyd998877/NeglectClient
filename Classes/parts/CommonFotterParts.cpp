//
//  CommonFotterParts.cpp
//  NeglecClient
//
//  Created by kyokomi on 2014/10/28.
//
//

#include "CommonFotterParts.h"

#include "ui/CocosGUI.h"
#include "CSLoaderUtil.h"

#include "CommonPopupLayer.h"

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
    this->_baseLayout = CSLoaderUtil::create("FotterParts");
    _baseLayout->setScale(winSize.width / _baseLayout->getContentSize().width);
    _baseLayout->setPosition(cocos2d::Vec2(winSize.width/2, _baseLayout->getContentSize().height/2));
    
    // Button setting
    utils::findChildByName<ui::Button*>(*_baseLayout, "Panel_main/Button_1")->addClickEventListener([](Ref *ref){
        NeglectSceneHelper::replaceScene(NeglectSceneHelper::SceneID::MY_PAGE);
    });
    utils::findChildByName<ui::Button*>(*_baseLayout, "Panel_main/Button_2")->addClickEventListener([](Ref *ref){
        NeglectSceneHelper::replaceScene(NeglectSceneHelper::SceneID::QUEST_LIST);
    });
    utils::findChildByName<ui::Button*>(*_baseLayout, "Panel_main/Button_3")->addClickEventListener([this](Ref *ref){
        // 倉庫へ
        CCLOG("まだ未実装");
        CommonPopupLayer::show(this, "まだ未実装", "ダンジョンで獲得したアイテムの整理や\n装備の整理をできるようにする予定です。", [](Ref *ref){});
    });
    utils::findChildByName<ui::Button*>(*_baseLayout, "Panel_main/Button_4")->addClickEventListener([this](Ref *ref){
        // お店へ
        CCLOG("まだ未実装");
        CommonPopupLayer::show(this, "まだ未実装", "ダンジョンで獲得したアイテムの売却や\nアイテムの購入をする予定です。", [](Ref *ref){});
    });
    utils::findChildByName<ui::Button*>(*_baseLayout, "Panel_main/Button_5")->addClickEventListener([this](Ref *ref){
        // メニュー
        CCLOG("まだ未実装");
        CommonPopupLayer::show(this, "まだ未実装", "設定とかその他色々の\nメニューを表示する予定です。", [](Ref *ref){});
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
