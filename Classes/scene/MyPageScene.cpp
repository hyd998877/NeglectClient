//
//  MyPageScene.cpp
//  NeglecClient
//
//  Created by kyokomi on 2014/10/27.
//
//

#include "MyPageScene.h"

#include "ui/CocosGUI.h"
#include "CSLoaderUtil.h"

#include "CommonPopupLayer.h"
#include "CommonHeaderParts.h"
#include "CommonFotterParts.h"

#include "NeglectHttpRequest.h"
#include "NeglectSceneHelper.h"

#include "UserData.h"
#include "MasterData.h"

USING_NS_CC;
using namespace cocos2d::network;
using namespace cocostudio;

MyPageScene::MyPageScene()
: _baseLayout(nullptr)
, _userNameLabel(nullptr)
, _userRankLabel(nullptr)
, _detailLabel(nullptr)
{
    
}

MyPageScene::~MyPageScene()
{
    
}

// on "init" you need to initialize your instance
bool MyPageScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init()) {
        return false;
    }
    
    this->initView();
    
    return true;
}

void MyPageScene::onEnter()
{
    Layer::onEnter();
    
    NeglectHttpRequest::getInstance()->setLoadingTarget(this);
    
    this->requestMyPage();
}

void MyPageScene::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
}

void MyPageScene::initView()
{
    auto winSize = Director::getInstance()->getVisibleSize();
    // CocosStudioのLayout読み込み
    this->_baseLayout = CSLoaderUtil::create("MyPageScene");
    this->_baseLayout->setPosition(winSize.width/2 - this->_baseLayout->getContentSize().width/2,
                                   winSize.height/2 - this->_baseLayout->getContentSize().height/2);
    this->addChild(this->_baseLayout);
    
    //Label
    this->_userNameLabel = utils::findChildByName<ui::Text*>(*this->_baseLayout, "Panel_main/Panel_unitStatus/Label_name");
    this->_userRankLabel = utils::findChildByName<ui::Text*>(*this->_baseLayout, "Panel_main/Panel_unitStatus/Label_rank");
    this->_detailLabel = utils::findChildByName<ui::Text*>(*this->_baseLayout, "Panel_main/Panel_message/Label_message_1");
    // Button
    this->_playingButton = utils::findChildByName<ui::Button*>(*this->_baseLayout, "Panel_main/Button_questPlay");
    
    auto header = CommonHeaderParts::create();
    header->setTitleText("マイページ");
    this->addChild(header);
    
    auto fotter = CommonFotterParts::create();
    fotter->setLockMenu(1);
    this->addChild(fotter);
}

void MyPageScene::requestMyPage()
{
    NeglectHttpRequest::getInstance()->mypage([this](json11::Json json) {
        // アカウント情報の表示
        // TODO: #7 login時に保持したやつを使うようにする
        auto account = UserData::create<UserData::TAccount>(json["TAccount"]);
        auto accountStatus = UserData::create<UserData::TAccountStatus>(json["TAccountStatus"]);
        
        if (account.description == "") {
            account.description = "特にお知らせはないわ";
        }
        _detailLabel->setString(account.description);

        auto rankMessage = StringUtils::format("Rank %3d", accountStatus.lv);
        _userRankLabel->setString(rankMessage);
        _userNameLabel->setString(account.name);
        
        // Playクエスト情報の表示
        auto playQuest = UserData::create<UserData::TPlayQuest>(json["TPlayQuest"]);
        if (playQuest.questID > 0) {
            auto mQuest = MasterData::create<MasterData::MQuest>(json["MQuest"]);
            _detailLabel->setString("プレイ中のクエストがあるわ " + mQuest.questName);
            _playingButton->setVisible(true);
            _playingButton->addClickEventListener([](Ref *ref) {
                // QuestPlay画面へ
                NeglectSceneHelper::replaceScene(NeglectSceneHelper::SceneID::QUEST_PLAY);
            });
        } else {
            _playingButton->setVisible(false);
        }
    }, [this](long statusCode, std::string error) {
        auto errorMessage = StringUtils::format("mypage error [%ld] %s", statusCode, error.c_str());
        CCLOG("%s", errorMessage.c_str());
        CommonPopupLayer::show(this, "通信エラー", errorMessage, [](Ref *ref){});
    });
}
