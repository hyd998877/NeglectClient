#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "MyPageScene.h"

USING_NS_CC;

void fitDesignResolutionSize(GLView *glview, float width, float height, float scale = 1.00f);

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // CocosStudioで作ったレイアウトサイズにする
    fitDesignResolutionSize(glview, 640, 960);

    // create a scene. it's an autorelease object
    auto scene = MyPageScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

void fitDesignResolutionSize(GLView *glview, float width, float height, float scale)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    const float baseScaleWidth  = width * scale;
    const float baseScaleHeight = height * scale;
    
    const int widthDiff = abs((int)visibleSize.width - (int)width);
    const int heightDiff = abs((int)visibleSize.height - (int)height);
    
    if (widthDiff == 0 && heightDiff == 0) {
        glview->setDesignResolutionSize(baseScaleWidth,
                                        baseScaleHeight,
                                        ResolutionPolicy::SHOW_ALL);
    } else {
        float divX = visibleSize.width / width;
        float divY = visibleSize.height / height;
        float fixWidth = 0.0f;
        float fixHeight = 0.0f;
        if (width > height) {
            // 横画面
            fixWidth = widthDiff / divX;
            fixHeight = heightDiff / divY;
        } else {
            // 縦画面
            fixWidth = widthDiff / divY;
            fixHeight = heightDiff / divX;
        }
        glview->setDesignResolutionSize(baseScaleWidth + fixWidth,
                                        baseScaleHeight + fixHeight,
                                        ResolutionPolicy::SHOW_ALL);
    }
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
