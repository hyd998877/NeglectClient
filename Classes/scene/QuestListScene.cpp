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
    
    // login通信
    NeglectHttpRequest::questList([this](long statusCode, std::string response) {
        std::string err = "";
        auto json = json11::Json::parse(response, err);
        
        if (!err.empty()) {
            CCLOG("json parse error %s", err.c_str());
            return;
        }
        
        // Listを取得
        auto listView = utils::findChildByName<ui::ListView*>(*_baseLayout, "Panel_main/ListView_quest");
        // Listの中身をセット
        for (auto item : json.array_items()) {
            auto listParts = ListViewPartsHelper::createListViewTextParts(item["QuestName"].string_value(),
                                                                          StringUtils::format("%2dF", item["FloorCount"].int_value()));
            // 行選択用にQuestIDをtagに埋め込む（いらないかも）
            listParts->setTag(item["QuestID"].int_value());
            
            auto winSize = Director::getInstance()->getVisibleSize();
            auto baseWidth = utils::findChildByName(*_baseLayout, "Panel_main")->getContentSize().width;
            listParts->setContentSize(Size(listParts->getContentSize().width * (winSize.width / baseWidth),
                                          listParts->getContentSize().height));
            listView->pushBackCustomItem(listParts);
        }
        // Listの行選択イベントを制御
        listView->addEventListener([json](Ref *ref, ui::ListView::EventType eventType){
            if (eventType != ui::ListView::EventType::ON_SELECTED_ITEM_END) {
                return;
            }
            auto listView = static_cast<ui::ListView*>(ref);
            auto selectedIndex = listView->getCurSelectedIndex();
            auto listItem = listView->getItem(selectedIndex);
            listItem->getChildByName<ui::Layout*>("Panel_main")->setColor(Color3B::GREEN);
            
            // TODO: questIdを何とかして渡す
            auto quest = json.array_items().at(selectedIndex);
            // クエスト詳細画面へ
            auto scene = NeglectSceneHelper::createScene(NeglectSceneHelper::SceneID::QUEST_DETAIL);
            scene->getChildByName<QuestStartScene*>("SceneLayer")->setup(QuestStartScene::Param{
                quest["QuestID"].int_value(),
            });
            Director::getInstance()->replaceScene(scene);
        });
    });
    
    // CocosStudioのLayout読み込み
    this->_baseLayout = GUIReader::getInstance()->widgetFromJsonFile("QuestListScene.json");
    this->addChild(this->_baseLayout);
    
    auto header = CommonHeaderParts::create();
    header->setTitleText("ダンジョン一覧");
    this->addChild(header);
    
    auto fotter = CommonFotterParts::create();
    fotter->setLockMenu(2);
    this->addChild(fotter);
    
    return true;
}
