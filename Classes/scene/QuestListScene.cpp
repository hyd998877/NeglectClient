//
//  QuestListScene.cpp
//  NeglecClient
//
//  Created by kyokomi on 2014/10/28.
//
//

#include "QuestListScene.h"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "CommonHeaderParts.h"
#include "CommonFotterParts.h"

#include "NeglectHttpRequest.h"

#include "NeglectSceneHelper.h"
#include "QuestStartScene.h"
#include "ListViewPartsHelper.h"

#include "MasterData.h"

USING_NS_CC;
using namespace cocos2d::network;
using namespace cocostudio;

QuestListScene::QuestListScene()
: _baseLayout(nullptr)
{
    
}

QuestListScene::~QuestListScene()
{
    
}

// on "init" you need to initialize your instance
bool QuestListScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    // TODO: #1 ccs v2対応する
    // CocosStudioのLayout読み込み
    this->_baseLayout = GUIReader::getInstance()->widgetFromJsonFile("QuestListScene.json");
    this->addChild(this->_baseLayout);
    
    NeglectHttpRequest::getInstance()->dataMasterLoad([this](json11::Json json) {
        
        auto mQuests = json["MQuest"];
        
        // Listを取得
        auto listView = utils::findChildByName<ui::ListView*>(*_baseLayout, "Panel_main/ListView_quest");
        // Listの中身をセット
        for (auto item : mQuests.array_items()) {
            auto quest = MasterData::create<MasterData::MQuest>(item);
            
            auto listParts = ListViewPartsHelper::createListViewTextParts(quest.questName,
                                                                          StringUtils::format("%2dF", quest.floorCount));
            auto winSize = Director::getInstance()->getVisibleSize();
            auto baseWidth = utils::findChildByName(*_baseLayout, "Panel_main")->getContentSize().width;
            listParts->setContentSize(Size(listParts->getContentSize().width * (winSize.width / baseWidth),
                                          listParts->getContentSize().height));
            listView->pushBackCustomItem(listParts);
        }
        // Listの行選択イベントを制御
        listView->addEventListener([mQuests](Ref *ref, ui::ListView::EventType eventType){
            if (eventType != ui::ListView::EventType::ON_SELECTED_ITEM_END) {
                return;
            }
            auto listView = static_cast<ui::ListView*>(ref);
            auto selectedIndex = listView->getCurSelectedIndex();
            auto listItem = listView->getItem(selectedIndex);
            listItem->getChildByName<ui::Layout*>("Panel_main")->setColor(Color3B::GREEN);
            
            auto quest = MasterData::create<MasterData::MQuest>(mQuests.array_items().at(selectedIndex));
            // クエスト詳細画面へ
            auto scene = NeglectSceneHelper::createScene(NeglectSceneHelper::SceneID::QUEST_DETAIL);
            scene->getChildByName<QuestStartScene*>("SceneLayer")->setup(QuestStartScene::Param{quest.questID});
            Director::getInstance()->replaceScene(scene);
        });
    });
    
    auto header = CommonHeaderParts::create();
    header->setTitleText("ダンジョン一覧");
    this->addChild(header);
    
    auto fotter = CommonFotterParts::create();
    fotter->setLockMenu(2);
    this->addChild(fotter);
    
    return true;
}
