#include "HelloWorldScene.h"
#include "network/HttpClient.h"

#include "cocostudio/CocoStudio.h"
#include "ui/UIListView.h"
#include "ui/UIText.h"

USING_NS_CC;
using namespace cocos2d::network;
using namespace cocostudio;

typedef std::function<void(long status, std::string response)> HttpRequestListener;
typedef std::function<void(long status, std::string error)> HttpRequestErrorListener;
HttpRequest* createRequest(HttpRequest::Type method, const std::string &requestURL,
                           const HttpRequestListener &listener,
                           const HttpRequestErrorListener &errorListener);

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
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
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    ///////////////////////////
    // ここからHttp通信
    
    // login通信
    auto request = createRequest(HttpRequest::Type::GET, "http://localhost:8000/login/hoge", [](long statusCode, std::string response) {
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
        auto request = createRequest(HttpRequest::Type::GET, "http://localhost:8000/quest", [](long statusCode, std::string response) {
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

    // ListView
    
    // CocosStudioのLayout読み込み
    auto layout = GUIReader::getInstance()->widgetFromJsonFile("ListScene/ListScene.json");
    // Listを取得
    auto listView = layout->getChildByName<ui::ListView*>("ListView_2");
    // Listの中身をセット
    for (int i = 0; i < 10; i++) {
        auto listParts = GUIReader::getInstance()->widgetFromJsonFile("ListParts/ListParts.json");
        auto text = StringUtils::format("Label Text %d", i);
        listParts->getChildByName<ui::Text*>("Label_2")->setString(text);
        listView->pushBackCustomItem(listParts);
    }
    listView->addEventListener([](Ref *ref, ui::ListView::EventType eventType){
        if (eventType == ui::ListView::EventType::ON_SELECTED_ITEM_END) {
            auto listView = static_cast<ui::ListView*>(ref);
            // 選択状態を戻す
            for (auto widget : listView->getItems()) {
                widget->getChildByName<ui::Text*>("Label_2")->setColor(Color3B::WHITE);
            }
            // 選択した行の色を変える
            auto selectedIndex = listView->getCurSelectedIndex();
            listView->getItem(selectedIndex)->getChildByName<ui::Text*>("Label_2")->setColor(Color3B::GREEN);
            
            CCLOG("selected index %ld", selectedIndex);
        }
    });
    this->addChild(layout);
    
    return true;
}

HttpRequest* createRequest(HttpRequest::Type method, const std::string &requestURL, const HttpRequestListener &listener, const HttpRequestErrorListener &errorListener)
{
    HttpRequest* request = new HttpRequest();
    request->setUrl(requestURL.c_str());
    request->setRequestType(method);
    request->setResponseCallback([listener, errorListener](HttpClient* client, HttpResponse* response) {
        if (!response) {
            errorListener(500L, "response is null");
            return;
        }
        // error
        if (!response->isSucceed()) {
            errorListener(response->getResponseCode(), std::string(response->getErrorBuffer()));
            return;
        }
        
        long statusCode = response->getResponseCode();
        
        std::string responseString(response->getResponseData()->begin(), response->getResponseData()->end());
        listener(statusCode, responseString);
    });
    request->setTag(requestURL.c_str());
    
    return request;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
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
