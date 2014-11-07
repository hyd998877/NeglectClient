//
//  QuestPlayScene.cpp
//  NeglecClient
//
//  Created by kyokomi on 2014/10/30.
//
//

#include "QuestPlayScene.h"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "CommonHeaderParts.h"
#include "CommonFotterParts.h"

#include "NeglectHttpRequest.h"

#include "DialogSelectListViewLayer.h"
#include "DialogShowListViewLayer.h"
#include "ListViewPartsHelper.h"

USING_NS_CC;
using namespace cocos2d::network;
using namespace cocostudio;

QuestPlayScene::QuestPlayScene()
: _baseLayout(nullptr)
{
    
}

QuestPlayScene::~QuestPlayScene()
{
    
}

// on "init" you need to initialize your instance
bool QuestPlayScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto winSize = Director::getInstance()->getVisibleSize();
    // CocosStudioのLayout読み込み
    this->_baseLayout = CSLoader::getInstance()->createNodeFromXML("QuestPlayScene.csd");
    this->_baseLayout->setPosition(winSize.width/2 - this->_baseLayout->getContentSize().width/2,
                                   winSize.height/2 - this->_baseLayout->getContentSize().height/2);
    this->addChild(this->_baseLayout);
    
    auto header = CommonHeaderParts::create();
    header->setTitleText("最果ての洞窟 最下層 99F");
    this->addChild(header);
    
    auto fotter = CommonFotterParts::create();
    this->addChild(fotter);
    
    utils::findChildByName<ui::Button*>(*_baseLayout, "Button_more")->addClickEventListener([this](Ref *ref) {
        auto dialog = DialogShowListViewLayer::create();
        dialog->setTitleText("Show List");
        for (int i = 0; i < 5; i++) {
            auto iconText = ListViewPartsHelper::createListViewShortTextParts("10分前: 99Fに到達した。");
            dialog->pushListItem(iconText);
        }
//        dialog->setCloseListener([]() {});
        this->addChild(dialog);
    });
    
    utils::findChildByName<ui::Button*>(*_baseLayout, "Button_item")->addClickEventListener([](Ref *ref) {
        
    });
    utils::findChildByName<ui::Button*>(*_baseLayout, "Button_menu")->addClickEventListener([](Ref *ref) {
        
    });

    // プレイ中クエストの情報を通信で取得
    NeglectHttpRequest::getInstance()->playingQuest([this](json11::Json json) {
        CCLOG("playing quest %s", json.dump().c_str());

        // TODO: クエストプレイ中の情報をUIに反映する
        
        /*
         {"MQuest": {"FloorCount": 5, "QuestDetail": "", "QuestID": 2, "QuestName": "hoge2"}, "TAccountStatus": {"AccountID": 1261213315, "EquipItem1ID": 1, "EquipItem2ID": 2, "EquipItem3ID": 3, "EquipItem4ID": 4, "Exp": 50, "Hp": 100, "Lv": 20, "MaxHp": 200, "MaxMp": 100, "Mp": 100}, "TPlayQuest": {"AccountID": 1261213315, "EndTime": "2014-11-07T10:54:16+09:00", "QuestID": 2, "StartTime": "2014-11-07T10:49:16+09:00"}, "TPlayQuestLogs": [{"AccountID": 1261213315, "Message": "10分前: ポーションを拾った", "QuestID": 2, "SeqID": 1}], "TQuest": {"AccountID": 1261213315, "Clear": 3, "QuestID": 2}, "TUserItems": []}
         */
        this->setTextQuestDetail(1, 1, 15);
        
        int lv    = json["TAccountStatus"]["Lv"].int_value();
        int hp    = json["TAccountStatus"]["Hp"].int_value();
        int maxHP = json["TAccountStatus"]["MaxHp"].int_value();
        int mp    = json["TAccountStatus"]["Mp"].int_value();
        int maxMP = json["TAccountStatus"]["MaxMp"].int_value();
        this->setTextStatus(lv, hp, maxHP, mp, maxMP);
        
        std::string message = "";
        for (auto item : json["TPlayQuestLogs"].array_items()) {
            message += item["Message"].string_value();
            message += "\n";
        }
        this->setTextLogMessage(message);
        
    });
    
    return true;
}

void QuestPlayScene::setTextQuestDetail(int floorCount, int hour, int minute)
{
    auto titleStr = StringUtils::format("現在 %2dF 　(残り時間：約%d時間%d分)", floorCount, hour, minute);
    utils::findChildByName<ui::Text*>(*_baseLayout, "Panel_detail/Text_detail")->setString(titleStr);
}

void QuestPlayScene::setTextStatus(int lv, int hp, int maxHp, int mp, int maxMp)
{
    auto status1Str = StringUtils::format("Lv %3d  HP %3d/%3d", lv, hp, maxHp);
    utils::findChildByName<ui::Text*>(*_baseLayout, "Panel_play/Text_status1")->setString(status1Str);
    
    int hirou = mp == 0 ? 0 : mp / maxMp;
    auto status2Str = StringUtils::format("疲労度%2d％", hirou);
    utils::findChildByName<ui::Text*>(*_baseLayout, "Panel_play/Text_status2")->setString(status2Str);
}

void QuestPlayScene::setTextLogMessage(const std::string &message)
{
    utils::findChildByName<ui::Text*>(*_baseLayout, "Panel_log/Text_log")->setString(message);
}
