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

namespace GLViewUtil {
    
    void fitDesignResolutionSize(cocos2d::GLView *glview, float width, float height, float scale = 1.0f)
    {
        auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
        
        float baseScaleWidth  = width * scale;
        float baseScaleHeight = height * scale;
        
        int widthDiff = abs((int)visibleSize.width - (int)width);
        int heightDiff = abs((int)visibleSize.height - (int)height);
        
        if (widthDiff == 0 && heightDiff == 0) {
            glview->setDesignResolutionSize(baseScaleWidth,
                                            baseScaleHeight,
                                            ResolutionPolicy::SHOW_ALL);
        } else {
            float divX = visibleSize.width / baseScaleWidth;
            float divY = visibleSize.height / baseScaleHeight;
            float fixWidth = widthDiff / divY;
            float fixHeight = heightDiff / divX;
            glview->setDesignResolutionSize(baseScaleWidth + fixWidth,
                                            baseScaleHeight + fixHeight,
                                            ResolutionPolicy::SHOW_ALL);
        }
    }
}

#endif
