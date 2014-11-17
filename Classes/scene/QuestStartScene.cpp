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

#include "MasterData.h"

USING_NS_CC;
using namespace cocos2d::network;
using namespace cocostudio;

QuestStartScene::QuestStartScene()
: _view(nullptr)
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
    
    this->_view = QuestStartSceneView(this);
    this->_view.init("QuestStartScene.csd");

    std::vector<MasterData::MItem> equipItemArray;
    equipItemArray.push_back(MasterData::MItem{1, 1, 1, "item_1040", "木の盾",               "木で出来た盾です。"});
    equipItemArray.push_back(MasterData::MItem{2, 1, 1, "item_768",  "アイアンソード + 10",    "普通の鉄の剣です。"});
    equipItemArray.push_back(MasterData::MItem{3, 1, 1, "item_772",  "デュランダル",           "hoge"});
    equipItemArray.push_back(MasterData::MItem{4, 1, 1, "item_774",  "エクスカリバー",          "アーサー王の剣です。"});
    equipItemArray.push_back(MasterData::MItem{5, 1, 1, "item_778",  "12345678901234567890", "ふが"});
    this->_view.setupEquipItem(equipItemArray);
    std::vector<MasterData::MItem> itemArray;
    itemArray.push_back(MasterData::MItem{1, 1, 1, "item_641",  "ポーション",             "HPが回復します。"});
    itemArray.push_back(MasterData::MItem{2, 1, 1, "item_645",  "ハイポーション",          "HPが多く回復します。"});
    itemArray.push_back(MasterData::MItem{3, 1, 1, "item_654",  "エナジードリンク",         "hoge"});
    itemArray.push_back(MasterData::MItem{4, 1, 1, "item_669",  "エナジードリンクEX",       "aaa"});
    itemArray.push_back(MasterData::MItem{5, 1, 1, "item_671",  "エナジードリンクEX-SUPER", "ふが"});
    this->_view.setupItem(itemArray);
    
    return true;
}

void QuestStartScene::setup(Param param)
{
    // questIDでクエスト情報を取得
    NeglectHttpRequest::getInstance()->dataMasterLoad([this, param](json11::Json json) {
        auto mQuests = json["MQuest"];
        
        // TODO: filterつくりたい
        MasterData::MQuest selectQuest;
        for (auto item : mQuests.array_items()) {
            auto quest = MasterData::create<MasterData::MQuest>(item);
            if (quest.questID != param.questID) {
                continue;
            }
            selectQuest = quest;
            break;
        }
        
        // {xxxxxダンジョン名} 最下層 {xx}F
        auto titleStr = StringUtils::format("%s %2dF", selectQuest.questName.c_str(), selectQuest.floorCount);
        this->_view.setHeaderTitle(titleStr);
        
        this->_view.setOnClickStartButtonListener([this, selectQuest](Ref *ref){
            this->startQuest(selectQuest.questID);
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

/////////////////////////////////////
#pragma mark
#pragma mark View

void QuestStartSceneView::addChild(cocos2d::Node *node) {
    this->_scene->addChild(node);
}

void QuestStartSceneView::init(const std::string &sceneFileName)
{
    auto winSize = Director::getInstance()->getVisibleSize();
    // CocosStudioのLayout読み込み
    this->_baseLayout = CSLoader::getInstance()->createNodeFromXML(sceneFileName);
    this->_baseLayout->setPosition(winSize.width/2 - this->_baseLayout->getContentSize().width/2,
                                   winSize.height/2 - this->_baseLayout->getContentSize().height/2);
    this->addChild(this->_baseLayout);
    
    auto header = CommonHeaderParts::create();
    this->addChild(header);
    
    auto fotter = CommonFotterParts::create();
    this->addChild(fotter);
    
    _equipLayer = utils::findChildByName(*_baseLayout, "Panel_main/EquipLayer");
}

void QuestStartSceneView::setHeaderTitle(const std::string &titleText)
{
    // {xxxxxダンジョン名} 最下層 {xx}F
    this->_scene->getChildByName<CommonHeaderParts*>("Header")->setTitleText(titleText);
}

void QuestStartSceneView::setupEquipItem(const std::vector<MasterData::MItem> equipItemArray)
{
    for (int i = 0; i < 4; i++) {
        this->setOnClickEquipButtonListener(i, [this, equipItemArray](Node *equipItemNode, Ref *ref) {
            auto dialog = QuestStartSceneView::createItemListDialog(equipItemArray, [equipItemNode](MasterData::MItem mItem){
                
                auto equipName = utils::findChildByName<ui::Text*>(*equipItemNode, "Panel_main/Text_name");
                auto equipIcon = utils::findChildByName<Sprite*>(*equipItemNode, "Panel_main/Sprite_icon");
                
                equipName->setString(mItem.name);
                auto imagePath = StringUtils::format("icon_set/%s.png", mItem.imageID.c_str());
                equipIcon->setTexture(imagePath);
            });
            this->addChild(dialog);
        });
    }
}

void QuestStartSceneView::setupItem(const std::vector<MasterData::MItem> itemArray)
{
    for (int i = 0; i < 5; i++) {
        this->setOnClickItemButtonListener(i, [this, itemArray](Node *itemNode, Ref *ref) {
            auto dialog = QuestStartSceneView::createItemListDialog(itemArray, [itemNode](MasterData::MItem mItem){
                auto itemIcon = utils::findChildByName<Sprite*>(*itemNode, "Panel_main/Sprite_icon");
                
                auto imagePath = StringUtils::format("icon_set/%s.png", mItem.imageID.c_str());
                itemIcon->setTexture(imagePath);
            });
            this->addChild(dialog);
        });
    }
}

void QuestStartSceneView::setOnClickStartButtonListener(const OnClickCallback &callback)
{
    auto startButton = utils::findChildByName<ui::Button*>(*_baseLayout, "Panel_main/Button_start");
    startButton->addClickEventListener(callback);
}

void QuestStartSceneView::setOnClickItemButtonListener(int index, const ItemButtonOnClickCallback &callback)
{
    auto name = StringUtils::format("Panel_item/Item_%d", index + 1);
    auto item = utils::findChildByName(*_equipLayer, name);
    utils::findChildByName<ui::Button*>(*item, "Panel_main/Button_item")->addClickEventListener([item, callback](Ref *ref) {
        callback(item, ref);
    });
}

void QuestStartSceneView::setOnClickEquipButtonListener(int index, const ItemButtonOnClickCallback &callback)
{
    auto name = StringUtils::format("Panel_equip/EquipItem_%d", index + 1);
    auto equipItem = utils::findChildByName(*_equipLayer, name);
    utils::findChildByName<ui::Button*>(*equipItem, "Panel_main/Button_equip")->addClickEventListener([equipItem, callback](Ref *ref) {
        callback(equipItem, ref);
    });
}

#pragma mark
#pragma mark Static

cocos2d::Layer* QuestStartSceneView::createItemListDialog(const std::vector<MasterData::MItem> equipItemArray, const ItemSelectListener &listener)
{
    // TODO: Dialogを保持しておいて中身だけ切り替えるほうがいいかも
    auto dialog = DialogSelectListViewLayer::create();
    dialog->setTitleText("Show List");
    for (auto equipItem : equipItemArray) {
        auto imagePath = StringUtils::format("icon_set/%s.png", equipItem.imageID.c_str());
        auto iconText = ListViewPartsHelper::createListViewIconTextParts(imagePath, equipItem.name);
        dialog->pushListItem(iconText);
    }
    dialog->setOkListener([dialog, equipItemArray, listener](long selectedIndex) {
        if (selectedIndex >= 0 && equipItemArray.size() > selectedIndex) {
            // 選択した行をもらう
            listener(equipItemArray.at(selectedIndex));
        }
        dialog->setVisible(false);
        dialog->removeAllChildren();
    });
    return dialog;
}
