//
//  NeglectHttpRequest.cpp
//  NeglecClient
//
//  Created by kyokomi on 2014/10/28.
//
//

#include "NeglectHttpRequest.h"

#include "deprecated/CCString.h"

#include "ApplicationUtil.h"
#include "UUIDUtil.h"

#include "LoadingDialogLayer.h"

using namespace json11;

NeglectHttpRequest *NeglectHttpRequest::getInstance() {
    static NeglectHttpRequest instance;
    return &instance;
}

void NeglectHttpRequest::mypage(const RequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener)
{
    NeglectHttpRequest::Get("/", listener, errorListener);
}

// キャッシュOK
void NeglectHttpRequest::dataMasterLoad(const RequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener)
{
    NeglectHttpRequest::Get("/data/master/load", listener, errorListener, Option{true});
}

// TODO: キャッシュOK 1分？
void NeglectHttpRequest::playingQuest(const RequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener)
{
    NeglectHttpRequest::Get("/play-quest", listener, errorListener);
}

// キャッシュなし
void NeglectHttpRequest::resultQuest(const RequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener)
{
    NeglectHttpRequest::Get("/result-quest", listener, errorListener);
}

// TODO: キャッシュOK
void NeglectHttpRequest::user(const RequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener)
{
    NeglectHttpRequest::Get("/user", listener, errorListener);
}

void NeglectHttpRequest::Get(const std::string &url, const RequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener, Option option)
{
    // URL毎にキャッシュを持っている
    if (option.cache && _reqsponseCache.find(url) != _reqsponseCache.end()) {
        listener(_reqsponseCache[url]);
        return;
    }
    
    // TODO: #6 Loading表示
    auto loadingDialog = LoadingDialogLayer::create();
    if (_loadingTarget) {
        _loadingTarget->addChild(loadingDialog);
    }
    
    auto request = HttpClientUtil::createGetRequest(createURL(url), [this, loadingDialog, url, listener, errorListener](long statusCode, std::string response) {
        CCLOG("response code: %ld response = %s", statusCode, response.c_str());

        std::string err = "";
        auto json = json11::Json::parse(response, err);
        
        if (!err.empty()) {
            CCLOG("json parse error %s", err.c_str());
            errorListener(403, err);
            return;
        }

        this->_reqsponseCache[url] = json;
        
        if (listener) {
            listener(json);
        }
        // TODO: #6 Loading終了
        this->_loadingTarget->removeChild(loadingDialog);
        
    }, [this, loadingDialog, errorListener](long statusCode, std::string error) {
        CCLOG("response code: %ld error = %s", statusCode, error.c_str());
        if (errorListener) {
            errorListener(statusCode, error);
        }
        // TODO: #6 Loading終了
        this->_loadingTarget->removeChild(loadingDialog);
    });
    cocos2d::network::HttpClient::getInstance()->send(request);
    request->release();
}

//////////////////////////////////////////////////////

// ログインは別でアプリ上の共通領域に持っておく
void NeglectHttpRequest::login(const RequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener)
{
    std::string uuid;
    auto saveData = ApplicationUtil::loadData();
    if (!saveData.empty()) {
        uuid = saveData.at("uuid").asString();
    } else {
        // 新規登録
        uuid = UUIDUtil::generateUUID();
        ApplicationUtil::saveData(uuid);
    }
    cocos2d::network::HttpClient::getInstance()->enableCookies(nullptr);
    NeglectHttpRequest::Post("/login", Json::object{{"uuid", uuid}, {"name", "kyokomi"}}, listener, errorListener);
}

void NeglectHttpRequest::startQuest(int questID, const RequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener)
{
    auto url = cocos2d::StringUtils::format("/quest/%d", questID);
    NeglectHttpRequest::Post(url, json11::Json::NUL, listener, errorListener);
}

void NeglectHttpRequest::Post(const std::string &url, const json11::Json &json, const RequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener)
{
    // TODO: #6 Loading表示
    auto loadingDialog = LoadingDialogLayer::create();
    if (_loadingTarget) {
        _loadingTarget->addChild(loadingDialog, 99999);
    }
    
    auto request = HttpClientUtil::createPostRequest(createURL(url), "param=" + json.dump(), [this, loadingDialog, listener, errorListener](long statusCode, std::string response) {
        CCLOG("response code: %ld response = %s", statusCode, response.c_str());
        
        std::string err = "";
        auto json = json11::Json::parse(response, err);
        
        if (!err.empty()) {
            CCLOG("json parse error %s", err.c_str());
            errorListener(403, err);
            return;
        }
        
        if (listener) {
            listener(json);
        }
        // TODO: #6 Loading終了
        this->_loadingTarget->removeChild(loadingDialog);
        
    }, [this, loadingDialog, errorListener](long statusCode, std::string error) {
        CCLOG("response code: %ld error = %s", statusCode, error.c_str());
        if (errorListener) {
            errorListener(statusCode, error);
        }
        // TODO: #6 Loading終了
        this->_loadingTarget->removeChild(loadingDialog);
    });
    cocos2d::network::HttpClient::getInstance()->send(request);
    request->release();
}

void NeglectHttpRequest::setLoadingTarget(cocos2d::Node *target)
{
    _loadingTarget = target;
}

/////////////////////

std::string NeglectHttpRequest::createURL(const std::string &url)
{
    if (isLocalMode()) {
        return "http://localhost:8000" + url;
    } else {
        return BASE_URL + url;
    }
}


