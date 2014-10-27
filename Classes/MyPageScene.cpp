//
//  MyPageScene.cpp
//  NeglecClient
//
//  Created by kyokomi on 2014/10/27.
//
//

#include "MyPageScene.h"

#include "HttpClientUtil.h"
#include "WidgetUtil.h"

#include "ui/UIListView.h"
#include "ui/UIText.h"

USING_NS_CC;
using namespace cocos2d::network;
using namespace cocostudio;

Scene* MyPageScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MyPageScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MyPageScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MyPageScene::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    ///////////////////////////
    // ここからHttp通信
    
    // login通信
    auto request = HttpClientUtil::createRequest(HttpRequest::Type::GET, "http://localhost:8000/login/hoge", [](long statusCode, std::string response) {
        CCLOG("response code: %ld response = %s", statusCode, response.c_str());
    }, [](long statusCode, std::string error) {
        CCLOG("response code: %ld error = %s", statusCode, error.c_str());
    });
    // Cookieを有効にする
    HttpClient::getInstance()->enableCookies(nullptr);
    HttpClient::getInstance()->send(request);
    request->release();
    
    // MenuItemLabelをタッチするとクエスト一覧を取得
    auto l2 = Label::createWithSystemFont("GET quest", "Arial", 20);
    auto menuItem = MenuItemLabel::create(l2, [this](Ref *ref){
        // クエスト一覧取得（要ログイン）
        auto request = HttpClientUtil::createRequest(HttpRequest::Type::GET, "http://localhost:8000/quest", [](long statusCode, std::string response) {
            CCLOG("response code: %ld response = %s", statusCode, response.c_str());
        }, [](long statusCode, std::string error) {
            CCLOG("response code: %ld error = %s", statusCode, error.c_str());
        });
        HttpClient::getInstance()->send(request);
        request->release();
    });
    menuItem->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, menuItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    // CocosStudioのLayout読み込み
    auto layout = GUIReader::getInstance()->widgetFromJsonFile("MyPageScene.json");
    this->addChild(layout);
    
    auto header = WidgetUtil::widgetHeaderFromJsonFile("HeaderParts.json");
    this->addChild(header);
    
    auto fotter = WidgetUtil::widgetFotterFromJsonFile("FotterParts.json");
    this->addChild(fotter);
    
    return true;
}

void MyPageScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
