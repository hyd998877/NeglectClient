//
//  QuestListScene.h
//  NeglecClient
//
//  Created by kyokomi on 2014/10/28.
//
//

#ifndef __NeglecClient__QuestListScene__
#define __NeglecClient__QuestListScene__

#include "cocos2d.h"

class QuestListScene : public cocos2d::Layer
{
public:
    QuestListScene();
    virtual ~QuestListScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    
    // implement the "static create()" method manually
    CREATE_FUNC(QuestListScene);
    
private:
    void initView();
    void requestDataMasterLoad();
private:
    cocos2d::ui::Widget *_baseLayout;
};

#endif /* defined(__NeglecClient__QuestListScene__) */
