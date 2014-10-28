//
//  NeglectHttpRequest.h
//  NeglecClient
//
//  Created by kyokomi on 2014/10/28.
//
//

#ifndef __NeglecClient__NeglectHttpRequest__
#define __NeglecClient__NeglectHttpRequest__

#include "HttpClientUtil.h"

#include "json11.hpp"

class NeglectHttpRequest
{
public:
    static void login(const HttpClientUtil::HttpRequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener = nullptr);
    static void questList(const HttpClientUtil::HttpRequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener = nullptr);
private:
    constexpr static auto BASE_URL = "http://localhost:8000";
    
    static void Get(const std::string &url, const HttpClientUtil::HttpRequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener);
    static void Post(const std::string &url, const json11::Json &json, const HttpClientUtil::HttpRequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener);
};

#endif /* defined(__NeglecClient__NeglectHttpRequest__) */
