//
//  NeglectHttpRequest.cpp
//  NeglecClient
//
//  Created by kyokomi on 2014/10/28.
//
//

#include "NeglectHttpRequest.h"

using namespace json11;

// TODO: キャッシュOK
void NeglectHttpRequest::questList(const HttpClientUtil::HttpRequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener)
{
    NeglectHttpRequest::Get("/quest", listener, errorListener);
}

// TODO: キャッシュOK
void NeglectHttpRequest::user(const HttpClientUtil::HttpRequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener)
{
    NeglectHttpRequest::Get("/user", listener, errorListener);
}

void NeglectHttpRequest::Get(const std::string &url, const HttpClientUtil::HttpRequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener)
{
    // TODO: URL毎に
    
    // TODO: Loading表示
    
    auto request = HttpClientUtil::createGetRequest(BASE_URL + url, [listener](long statusCode, std::string response) {
        CCLOG("response code: %ld response = %s", statusCode, response.c_str());
        if (listener) {
            listener(statusCode, response);
        }
        // TODO: Loading終了
    }, [errorListener](long statusCode, std::string error) {
        CCLOG("response code: %ld error = %s", statusCode, error.c_str());
        if (errorListener) {
            errorListener(statusCode, error);
        }
        // TODO: Loading終了
    });
    cocos2d::network::HttpClient::getInstance()->send(request);
    request->release();
}

//////////////////////////////////////////////////////

// ログインは別でアプリ上の共通領域に持っておく
void NeglectHttpRequest::login(const HttpClientUtil::HttpRequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener)
{
    // TODO: UUIDの取得 or 生成
    auto uuid = "cocos";
    cocos2d::network::HttpClient::getInstance()->enableCookies(nullptr);
    NeglectHttpRequest::Post("/login", Json::object{{"uuid", uuid}, {"name", "kyokomi"}}, listener, errorListener);
}

void NeglectHttpRequest::Post(const std::string &url, const json11::Json &json, const HttpClientUtil::HttpRequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener)
{
    // TODO: Loading表示
    
    auto request = HttpClientUtil::createPostRequest(BASE_URL + url, "param=" + json.dump(), [listener](long statusCode, std::string response) {
        CCLOG("response code: %ld response = %s", statusCode, response.c_str());
        if (listener) {
            listener(statusCode, response);
        }
        // TODO: Loading終了
    }, [errorListener](long statusCode, std::string error) {
        CCLOG("response code: %ld error = %s", statusCode, error.c_str());
        if (errorListener) {
            errorListener(statusCode, error);
        }
        // TODO: Loading終了
    });
    cocos2d::network::HttpClient::getInstance()->send(request);
    request->release();
}
