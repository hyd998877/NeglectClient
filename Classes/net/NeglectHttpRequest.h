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
    struct Option {
        bool cache;
    };
    
    typedef std::function<void(json11::Json response)> RequestListener;
    
    static NeglectHttpRequest *getInstance();
    
    // POST
    void login(const RequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener = nullptr);
    void startQuest(int questID, const RequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener = nullptr);
    
    // GET
    void mypage(const RequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener = nullptr);
    void dataMasterLoad(const RequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener = nullptr);
    void playingQuest(const RequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener = nullptr);
    void user(const RequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener = nullptr);
    
    void onLocalMode() { this->_localMode = true; }
    void offLocalMode() { this->_localMode = false; }
    bool isLocalMode() const { return _localMode; }
private:
    NeglectHttpRequest()
    : _reqsponseCache()
    , _localMode(false)
    {
    }
    
    ~NeglectHttpRequest() = default;
    NeglectHttpRequest(const NeglectHttpRequest&) = delete;
    NeglectHttpRequest& operator=(const NeglectHttpRequest&) = delete;
    
    // TODO: AppConfigとかで持つようにする
    constexpr static auto BASE_URL = "https://neglect-game.herokuapp.com";
    
    void Get(const std::string &url, const RequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener, Option option = {});
    void Post(const std::string &url, const json11::Json &json, const RequestListener &listener, const HttpClientUtil::HttpRequestErrorListener &errorListener);
    
    std::string createURL(const std::string &url);
private:
    bool _localMode;
    std::unordered_map<std::string, json11::Json> _reqsponseCache;
};

#endif /* defined(__NeglecClient__NeglectHttpRequest__) */
