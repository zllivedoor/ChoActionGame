#ifndef Philon_cocos2dx_PompaDroid_OPTIONLAYER_H_
#define Philon_cocos2dx_PompaDroid_OPTIONLAYER_H_
#pragma once

#include "cocos2d.h"
#include "CCEventDispatcher.h"
#include "CCEventListenerTouch.h"


#include "extensions/cocos-ext.h"

USING_NS_CC;

class OptionDelegate
{
public:
    // “∆∂Ø£¨directionŒ™œÚ¡ø£¨distance «”Î∆µ„µƒ÷±œﬂæ‡¿Î
    virtual void onWalk(cocos2d::Point direction, float distance) = 0;
    // π•ª˜
    virtual void onAttack() = 0;
    // Õ£÷π“∆∂Ø
    virtual void onStop() = 0;
};

class OptionLayer : public cocos2d::Layer
{
public:
    OptionLayer();
    ~OptionLayer();
    
    virtual bool init();
    CREATE_FUNC(OptionLayer);
    
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event  *event);
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event  *event);
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event  *event);
    CC_SYNTHESIZE(OptionDelegate*, _delegator, Delegator);
    
    
private:
    // “°∏À£¨∑÷Œ™°∞“°∏À°±°¢°∞“°∏Àª˘◊˘°±¡Ω∏ˆ≤ø∑÷
    cocos2d::Sprite *_joystick;
    cocos2d::Sprite *_joystick_bg;
    // º§ªÓ°∞“°∏Àæ´¡È°±£¨≤¢∏¸–¬∆‰◊¯±Í
    void _activityJoystick(cocos2d::Point position);
    // “˛≤ÿ°∞“°∏Àæ´¡È°±£¨≤¢Ω´°∞“°∏À°±÷√”⁄°∞“°∏Àª˘◊˘°±÷––ƒ
    void _inactivityJoystick();
    // À¢–¬°∞“°∏À°±œ‡∂‘”⁄°∞“°∏Àª˘◊˘°±µƒŒª÷√£®∏˘æ›¥•øÿ ÷ ∆£©
    void _updateJoystick(cocos2d::Point direction, float distance);
};

#endif // End of Philon_cocos2dx_PompaDroid_GAMELAYER_H_
