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
#include "NeglectSceneHelper.h"

#include "DialogSelectListViewLayer.h"
#include "DialogShowListViewLayer.h"
#include "ListViewPartsHelper.h"

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
    
    auto winSize = Director::getInstance()->getVisibleSize();
    // CocosStudioのLayout読み込み
    this->_baseLayout = CSLoader::getInstance()->createNodeFromXML("QuestStartScene.csd");
    this->_baseLayout->setPosition(winSize.width/2 - this->_baseLayout->getContentSize().width/2,
                                   winSize.height/2 - this->_baseLayout->getContentSize().height/2);
    auto startButton = utils::findChildByName<ui::Button*>(*_baseLayout, "Panel_main/Button_start");
    startButton->addClickEventListener([](Ref *ref){
        NeglectSceneHelper::replaceScene(NeglectSceneHelper::SceneID::QUEST_PLAY);
    });
    this->addChild(this->_baseLayout);

    auto equipLayer = utils::findChildByName(*_baseLayout, "Panel_main/EquipLayer");

    for (int i = 0; i < 4; i++) {
        auto name = StringUtils::format("Panel_equip/EquipItem_%d", i + 1);
        auto equipItem = utils::findChildByName(*equipLayer, name);
        utils::findChildByName<ui::Button*>(*equipItem, "Panel_main/Button_equip")->addClickEventListener([this](Ref *ref) {
            auto dialog = DialogSelectListViewLayer::create();
            dialog->setTitleText("Show List");
            for (int i = 0; i < 10; i++) {
                auto iconText = ListViewPartsHelper::createListViewIconTextParts("icon_set/item_1040.png", "木の盾");
                dialog->pushListItem(iconText);
            }
            dialog->setOkListener([]() {
                // TODO: 選択した行をもらう
            });
            this->addChild(dialog);
        });
    }
    
    for (int i = 0; i < 5; i++) {
        auto name = StringUtils::format("Panel_item/Item_%d", i + 1);
        auto item = utils::findChildByName(*equipLayer, name);
        utils::findChildByName<ui::Button*>(*item, "Panel_main/Button_item")->addClickEventListener([this](Ref *ref) {
            auto dialog = DialogSelectListViewLayer::create();
            dialog->setTitleText("Show List");
            for (int i = 0; i < 4; i++) {
                auto iconText = ListViewPartsHelper::createListViewIconTextParts("icon_set/item_641.png", "ポーション");
                dialog->pushListItem(iconText);
            }
            dialog->setOkListener([]() {
                // TODO: 選択した行をもらう
            });
            this->addChild(dialog);
        });
    }
    
    auto header = CommonHeaderParts::create();
    header->setTitleText("最果ての洞窟 最下層 99F");
    this->addChild(header);
    
    auto fotter = CommonFotterParts::create();
    this->addChild(fotter);
    
    return true;
}
