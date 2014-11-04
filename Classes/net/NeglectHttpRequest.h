//
//  NeglectHttpRequest.h
//  NeglecClient
//
//  Created by kyokomi on 2014/10/28.
//
//

#ifndef __NeglecClient__NeglectHttpRequest__
#define __NeglecClient__NeglectHttpRequest__

#include <unordered_map>

#include "HttpClientUtil.h"

#include "json11.hpp"

class NeglectHttpRequest
{
public:
    typedef std::function<void(json11::Json response)> RequestListener;
    
    static NeglectHttpRequest *getInstance();
    
    void login(const RequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener = nullptr);
    void questList(const RequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener = nullptr);
    void user(const RequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener);
private:
    NeglectHttpRequest()
    : _reqsponseCache()
    {
    }
    
    ~NeglectHttpRequest() = default;
    NeglectHttpRequest(const NeglectHttpRequest&) = delete;
    NeglectHttpRequest& operator=(const NeglectHttpRequest&) = delete;
    
    constexpr static auto BASE_URL = "http://localhost:8000";
    
    void Get(const std::string &url, const RequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener);
    void Post(const std::string &url, const json11::Json &json, const RequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener);
    
private:
    std::unordered_map<std::string, json11::Json> _reqsponseCache;
};

#endif /* defined(__NeglecClient__NeglectHttpRequest__) */
