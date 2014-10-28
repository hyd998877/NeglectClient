//
//  NeglectHttpRequest.cpp
//  NeglecClient
//
//  Created by kyokomi on 2014/10/28.
//
//

#include "NeglectHttpRequest.h"

using namespace json11;

void NeglectHttpRequest::login(const HttpClientUtil::HttpRequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener)
{
    // TODO: UUIDの取得 or 生成
    auto uuid = "hoge";
    cocos2d::network::HttpClient::getInstance()->enableCookies(nullptr);
    NeglectHttpRequest::Post("/login", Json::object{{"uuid", uuid}}, listener, errorListener);
}

void NeglectHttpRequest::questList(const HttpClientUtil::HttpRequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener)
{
    NeglectHttpRequest::Get("/quest", listener, errorListener);
}

void NeglectHttpRequest::Get(const std::string &url, const HttpClientUtil::HttpRequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener)
{
    auto request = HttpClientUtil::createGetRequest(BASE_URL + url, [listener](long statusCode, std::string response) {
        CCLOG("response code: %ld response = %s", statusCode, response.c_str());
        if (listener) {
            listener(statusCode, response);
        }
    }, [errorListener](long statusCode, std::string error) {
        CCLOG("response code: %ld error = %s", statusCode, error.c_str());
        if (errorListener) {
            errorListener(statusCode, error);
        }
    });
    cocos2d::network::HttpClient::getInstance()->send(request);
    request->release();
}

void NeglectHttpRequest::Post(const std::string &url, const json11::Json &json, const HttpClientUtil::HttpRequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener)
{
    auto request = HttpClientUtil::createPostRequest(BASE_URL + url, json.dump(), [listener](long statusCode, std::string response) {
        CCLOG("response code: %ld response = %s", statusCode, response.c_str());
        if (listener) {
            listener(statusCode, response);
        }
    }, [errorListener](long statusCode, std::string error) {
        CCLOG("response code: %ld error = %s", statusCode, error.c_str());
        if (errorListener) {
            errorListener(statusCode, error);
        }
    });
    cocos2d::network::HttpClient::getInstance()->send(request);
    request->release();
}
