//
//  GLViewUtil.h
//  NeglecClient
//
//  Created by kyokomi on 2014/10/28.
//
//

#ifndef NeglecClient_GLViewUtil_h
#define NeglecClient_GLViewUtil_h

#include "base/CCDirector.h"
#include "platform/CCGLView.h"
#include "math/CCGeometry.h"

namespace GLViewUtil {
    
    cocos2d::Size getFitDesignResolutionSize(float width, float height, float scale = 1.0f)
    {
        auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
        
        float baseScaleWidth  = width * scale;
        float baseScaleHeight = height * scale;
        
        int widthDiff = abs((int)visibleSize.width - (int)width);
        int heightDiff = abs((int)visibleSize.height - (int)height);
        
        if (widthDiff == 0 && heightDiff == 0) {
            return cocos2d::Size(baseScaleWidth, baseScaleHeight);
        }
        
        float divX = visibleSize.width / baseScaleWidth;
        float divY = visibleSize.height / baseScaleHeight;
        float fixWidth = widthDiff / divY;
        float fixHeight = heightDiff / divX;
        return cocos2d::Size(baseScaleWidth + fixWidth, baseScaleHeight + fixHeight);
    }
}

#endif
