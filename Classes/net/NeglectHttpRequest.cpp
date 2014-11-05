//
//  NeglectHttpRequest.cpp
//  NeglecClient
//
//  Created by kyokomi on 2014/10/28.
//
//

#include "NeglectHttpRequest.h"

using namespace json11;

NeglectHttpRequest *NeglectHttpRequest::getInstance() {
    static NeglectHttpRequest instance;
    return &instance;
}

// TODO: キャッシュOK
void NeglectHttpRequest::questList(const RequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener)
{
    NeglectHttpRequest::Get("/quest", listener, errorListener, Option{true});
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
    
    auto request = HttpClientUtil::createGetRequest(BASE_URL + url, [this, url, listener, errorListener](long statusCode, std::string response) {
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
    }, [errorListener](long statusCode, std::string error) {
        CCLOG("response code: %ld error = %s", statusCode, error.c_str());
        if (errorListener) {
            errorListener(statusCode, error);
        }
        // TODO: #6 Loading終了
    });
    cocos2d::network::HttpClient::getInstance()->send(request);
    request->release();
}

//////////////////////////////////////////////////////

// ログインは別でアプリ上の共通領域に持っておく
void NeglectHttpRequest::login(const RequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener)
{
    // TODO: #9 UUID生成
    // TODO: #7 #10 UUIDをアプリ情報から取得
    auto uuid = "cocos";
    cocos2d::network::HttpClient::getInstance()->enableCookies(nullptr);
    NeglectHttpRequest::Post("/login", Json::object{{"uuid", uuid}, {"name", "kyokomi"}}, listener, errorListener);
}

void NeglectHttpRequest::Post(const std::string &url, const json11::Json &json, const RequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener)
{
    // TODO: #6 Loading表示
    
    auto request = HttpClientUtil::createPostRequest(BASE_URL + url, "param=" + json.dump(), [listener, errorListener](long statusCode, std::string response) {
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
    }, [errorListener](long statusCode, std::string error) {
        CCLOG("response code: %ld error = %s", statusCode, error.c_str());
        if (errorListener) {
            errorListener(statusCode, error);
        }
        // TODO: #6 Loading終了
    });
    cocos2d::network::HttpClient::getInstance()->send(request);
    request->release();
}
