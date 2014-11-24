//
//  QuestPlayScene.cpp
//  NeglecClient
//
//  Created by kyokomi on 2014/10/30.
//
//

#include "QuestPlayScene.h"

#include <chrono>

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "CommonHeaderParts.h"
#include "CommonFotterParts.h"

#include "NeglectHttpRequest.h"

#include "DialogSelectListViewLayer.h"
#include "DialogShowListViewLayer.h"
#include "ListViewPartsHelper.h"

#include "UserData.h"

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
    
    this->initView();
    
    return true;
}
void QuestPlayScene::onEnter()
{
    Layer::onEnter();
    
    NeglectHttpRequest::getInstance()->setLoadingTarget(this);
    
    // プレイ中クエストの情報を通信で取得
    this->requestPlayingQuest();
}

void QuestPlayScene::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
}

void QuestPlayScene::initView()
{
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
        // TODO: クエストプレイログの情報をUIに反映する
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
}

void QuestPlayScene::requestPlayingQuest()
{
    // プレイ中クエストの情報を通信で取得
    NeglectHttpRequest::getInstance()->playingQuest([this](json11::Json json) {
        CCLOG("playing quest %s", json.dump().c_str());
        
        // クエストプレイ中の情報をUIに反映する
        auto playQuest = UserData::create<UserData::TPlayQuest>(json["TPlayQuest"]);
        time_t startTime = playQuest.startTime;
        time_t endTime = playQuest.endTime;
        time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        
        // 経過時間（秒）
        auto playTime = difftime(now, startTime);
        CCLOG("playTime 開始から %f秒経過", playTime);
        // 終了までの時間（秒）
        auto playEndTime = difftime(endTime, now);
        CCLOG("playEndTime 終了まで %f秒", playEndTime);
        
        time_t diffTime = playEndTime;
        auto endTm = gmtime(&diffTime);
        // 秒は切り上げ
        auto min = endTm->tm_sec > 0 ? endTm->tm_min + 1 : endTm->tm_min;
        this->setTextQuestDetail(playQuest.floorCount, endTm->tm_hour, min);
        
        auto accountStatus = UserData::create<UserData::TAccountStatus>(json["TAccountStatus"]);
        this->setTextStatus(accountStatus.lv,
                            accountStatus.hp,
                            accountStatus.maxHp,
                            accountStatus.mp,
                            accountStatus.maxMp);
        
        // TODO: クエストプレイログの情報をUIに反映する
        std::string message = "";
        for (auto item : json["TPlayQuestLogs"].array_items()) {
            message += item["Message"].string_value();
            message += "\n";
        }
        this->setTextLogMessage(message);
        
    }, [](long status, std::string error) {
        // TODO: ダイアログを表示してマイページへ戻る
        CCLOG("errorだよ status %ld quest %s", status, error.c_str());
    });
}

#pragma mark
#pragma mark View

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
