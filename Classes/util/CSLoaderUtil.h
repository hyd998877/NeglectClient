//
//  CSLoaderUtil.h
//  NeglecClient
//
//  Created by kyokomi on 2014/11/29.
//
//

#ifndef NeglecClient_CSLoaderUtil_h
#define NeglecClient_CSLoaderUtil_h

#include "cocostudio/CocoStudio.h"

namespace CSLoaderUtil {

    static cocos2d::Node* create(const std::string &filePath) {
#if 1
        return cocos2d::CSLoader::getInstance()->createNode(filePath + ".csb");
#else
        return cocos2d::CSLoader::getInstance()->createNodeFromXML(filePath + ".csd");
#endif
    }
}

#endif
