//
//  HttpClientUtil.h
//  NeglecClient
//
//  Created by kyokomi on 2014/10/27.
//
//

#ifndef NeglecClient_HttpClientUtil_h
#define NeglecClient_HttpClientUtil_h

#include "network/HttpClient.h"

namespace HttpClientUtil {
    typedef std::function<void(long status, std::string response)> HttpRequestListener;
    typedef std::function<void(long status, std::string error)> HttpRequestErrorListener;
    
    static cocos2d::network::HttpRequest* createRequest(cocos2d::network::HttpRequest::Type method,
                                                        const std::string &requestURL,
                                                        const std::string &requestData,
                                                        const HttpRequestListener &listener,
                                                        const HttpRequestErrorListener &errorListener)
    {
        cocos2d::network::HttpRequest* request = new cocos2d::network::HttpRequest();
        request->setUrl(requestURL.c_str());
        request->setRequestType(method);
        request->setRequestData(requestData.c_str(), requestData.size());
        request->setResponseCallback([listener, errorListener](cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response) {
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
    
    static cocos2d::network::HttpRequest* createGetRequest(const std::string &requestURL, const HttpRequestListener &listener, const HttpRequestErrorListener &errorListener)
    {
        return HttpClientUtil::createRequest(cocos2d::network::HttpRequest::Type::GET, requestURL, "", listener, errorListener);
    }
    
    static cocos2d::network::HttpRequest* createPostRequest(const std::string &requestURL, const std::string &requestData, const HttpRequestListener &listener, const HttpRequestErrorListener &errorListener)
    {
        return HttpClientUtil::createRequest(cocos2d::network::HttpRequest::Type::POST, requestURL, requestData, listener, errorListener);
    }
}
#endif
