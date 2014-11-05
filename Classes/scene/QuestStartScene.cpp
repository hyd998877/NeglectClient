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
    
    // TODO: 所持アイテム、装備品と倉庫情報を取得
    
    auto winSize = Director::getInstance()->getVisibleSize();
    // CocosStudioのLayout読み込み
    this->_baseLayout = CSLoader::getInstance()->createNodeFromXML("QuestStartScene.csd");
    this->_baseLayout->setPosition(winSize.width/2 - this->_baseLayout->getContentSize().width/2,
                                   winSize.height/2 - this->_baseLayout->getContentSize().height/2);
    this->addChild(this->_baseLayout);

    auto equipLayer = utils::findChildByName(*_baseLayout, "Panel_main/EquipLayer");

    for (int i = 0; i < 4; i++) {
        auto name = StringUtils::format("Panel_equip/EquipItem_%d", i + 1);
        auto equipItem = utils::findChildByName(*equipLayer, name);
        auto equipName = utils::findChildByName<ui::Text*>(*equipItem, "Panel_main/Text_name");
        auto equipIcon = utils::findChildByName<Sprite*>(*equipItem, "Panel_main/Sprite_icon");
        utils::findChildByName<ui::Button*>(*equipItem, "Panel_main/Button_equip")->addClickEventListener([this, equipName, equipIcon](Ref *ref) {
            
            // TODO: テスト用
            std::vector<std::tuple<std::string, std::string>> itemArray {
                {"木の盾",                 "icon_set/item_1040.png"},
                {"アイアンソード + 10",      "icon_set/item_768.png"},
                {"デュランダル",             "icon_set/item_772.png"},
                {"エクスカリバー",           "icon_set/item_774.png"},
                {"レイピア",               "icon_set/item_778.png"},
                {"12345678901234567890",  "icon_set/item_780.png"},
            };
            
            // TODO: Dialogを保持しておいて中身だけ切り替えるほうがいいかも
            auto dialog = DialogSelectListViewLayer::create();
            dialog->setTitleText("Show List");
            for (auto item : itemArray) {
                auto iconText = ListViewPartsHelper::createListViewIconTextParts(std::get<1>(item), std::get<0>(item));
                dialog->pushListItem(iconText);
            }
            dialog->setOkListener([dialog, itemArray, equipName, equipIcon](long selectedIndex) {
                if (selectedIndex >= 0 && itemArray.size() > selectedIndex) {
                    // 選択した行をもらう
                    auto item = itemArray.at(selectedIndex);
                    equipName->setString(std::get<0>(item));
                    equipIcon->setTexture(std::get<1>(item));
                }
                dialog->setVisible(false);
                dialog->removeAllChildren();
            });
            this->addChild(dialog);
        });
    }
    
    for (int i = 0; i < 5; i++) {
        auto name = StringUtils::format("Panel_item/Item_%d", i + 1);
        auto item = utils::findChildByName(*equipLayer, name);
        auto itemIcon = utils::findChildByName<Sprite*>(*item, "Panel_main/Sprite_icon");
        utils::findChildByName<ui::Button*>(*item, "Panel_main/Button_item")->addClickEventListener([this, itemIcon](Ref *ref) {
            
            // TODO: テスト用
            std::vector<std::tuple<std::string, std::string>> itemArray {
                {"ポーション",             "icon_set/item_641.png"},
                {"ハイポーション",          "icon_set/item_645.png"},
                {"帰還石",                 "icon_set/item_654.png"},
                {"エナジードリンク",         "icon_set/item_669.png"},
                {"エナジードリンクEX",       "icon_set/item_670.png"},
                {"エナジードリンクEX-SUPER", "icon_set/item_671.png"},
            };
            // TODO: Dialogを保持しておいて中身だけ切り替えるほうがいいかも
            auto dialog = DialogSelectListViewLayer::create();
            dialog->setTitleText("Show List");
            for (auto item : itemArray) {
                auto iconText = ListViewPartsHelper::createListViewIconTextParts(std::get<1>(item), std::get<0>(item));
                dialog->pushListItem(iconText);
            }
            dialog->setOkListener([dialog, itemArray, itemIcon](long selectedIndex) {
                if (selectedIndex >= 0 && itemArray.size() > selectedIndex) {
                    // 選択した行をもらう
                    auto item = itemArray.at(selectedIndex);
                    itemIcon->setTexture(std::get<1>(item));
                }
                dialog->setVisible(false);
                dialog->removeAllChildren();
            });
            this->addChild(dialog);
        });
    }
    
    auto header = CommonHeaderParts::create();
    this->addChild(header);
    
    auto fotter = CommonFotterParts::create();
    this->addChild(fotter);
    
    return true;
}

void QuestStartScene::setup(Param param)
{
    // questIDでクエスト情報を取得
    NeglectHttpRequest::getInstance()->questList([this, param](json11::Json json) {
        
        // TODO: filterつくりたい
        json11::Json selectQuest;
        for (auto quest : json.array_items()) {
            if (quest["QuestID"] != param.questID) {
                continue;
            }
            selectQuest = quest;
            break;
        }
        
        // {xxxxxダンジョン名} 最下層 {xx}F
        std::string questName = selectQuest["QuestName"].string_value();
        int floorCount = selectQuest["FloorCount"].int_value();
        auto titleStr = StringUtils::format("%s %2dF", questName.c_str(), floorCount);
        this->getChildByName<CommonHeaderParts*>("Header")->setTitleText(titleStr);
        
        int questID = selectQuest["QuestID"].int_value();
        auto startButton = utils::findChildByName<ui::Button*>(*_baseLayout, "Panel_main/Button_start");
        startButton->addClickEventListener([this, questID](Ref *ref){
            this->startQuest(questID);
        });
    });
}

void QuestStartScene::startQuest(int questID)
{
    // questIDで通信してクエストを開始
    NeglectHttpRequest::getInstance()->startQuest(questID, [](json11::Json json) {
        // Play中ページへ飛ぶ
        NeglectSceneHelper::replaceScene(NeglectSceneHelper::SceneID::QUEST_PLAY);
    }, [](int statusCode, std::string error) {
        // TODO: #12 errorダイアログ表示
        CCLOG("errorだよ");
    });
}
