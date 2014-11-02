//
//  QuestStartScene.h
//  NeglecClient
//
//  Created by kyokomi on 2014/10/28.
//
//

#ifndef __NeglecClient__QuestStartScene__
#define __NeglecClient__QuestStartScene__

#include "cocos2d.h"

class QuestStartScene : public cocos2d::Layer
{
public:
    QuestStartScene();
    virtual ~QuestStartScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(QuestStartScene);
    
    struct Param {
        int questID;
    };
    
    void setup(Param param);
private:
    cocos2d::Node *_baseLayout;
};

#endif /* defined(__NeglecClient__QuestStartScene__) */
