//
//  CommonPopupLayer.h
//  NeglecClient
//
//  Created by kyokomi on 2014/11/29.
//
//

#ifndef __NeglecClient__CommonPopupLayer__
#define __NeglecClient__CommonPopupLayer__

#include "cocos2d.h"

namespace cocos2d {
    namespace ui {
        class Text;
        class Button;
    }
}

class CommonPopupLayer : public cocos2d::Layer
{
    
public:
    typedef std::function<void(Ref*)> ButtonClickCallback;
    
    CommonPopupLayer();
    virtual ~CommonPopupLayer();
    virtual bool init();
    CREATE_FUNC(CommonPopupLayer);
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    
    static void show(cocos2d::Node* target,
                     const std::string& titleText,
                     const std::string& messageText,
                     const ButtonClickCallback &callbackOK,
                     const std::string &buttonNameOK = "OK",
                     const std::string& cautionText = "");
    static void show(cocos2d::Node* target,
                     const std::string& titleText,
                     const std::string& messageText,
                     const ButtonClickCallback &callbackOK,
                     const std::string &buttonNameOK,
                     const ButtonClickCallback &callbackNG,
                     const std::string &buttonNameNG,
                     const std::string& cautionText = "");
    
public:
    void setTitleText(const std::string& titleText);
    void setMessageText(const std::string& messageText);
    void setCautionText(const std::string& cautionText, cocos2d::Color3B textColor = cocos2d::Color3B::YELLOW);
    void setOKButtonListener(const ButtonClickCallback &callback, const std::string &buttonName = "OK");
    void setNGButtonListener(const ButtonClickCallback &callback, const std::string &buttonName = "CLOSE");
    
    void close();
    void centerButtonOK();
    void runShowAnimation();
protected:
    
private:
    void initView();
    
private:
    cocos2d::Node* _baseLayout;
    
    cocos2d::Node* _mainPanel;
    cocos2d::ui::Button* _buttonOK;
    cocos2d::ui::Button* _buttonNG;
    
    cocos2d::ui::Text* _textTitle;
    cocos2d::ui::Text* _textMessage;
    cocos2d::ui::Text* _textCaution;
};


#endif /* defined(__NeglecClient__CommonPopupLayer__) */
