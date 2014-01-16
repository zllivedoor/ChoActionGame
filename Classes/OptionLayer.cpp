#include "OptionLayer.h"

using namespace cocos2d;

OptionLayer::OptionLayer()
{}

OptionLayer::~OptionLayer()
{}

bool OptionLayer::init()
{
    bool ret = false;
    
    do {
        CC_BREAK_IF(!Layer::init());
        
        _joystick = Sprite::create("joystick.png");
        _joystick_bg = Sprite::create("joystick_bg.png");
        this->addChild(_joystick_bg);
        this->addChild(_joystick);
        
        _inactivityJoystick();
        
        setTouchEnabled(true);
    
        
        ret = true;
    } while(0);
    
    
    return ret;
}


void OptionLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event  *event)
{
    
    log("###########onTouchesBegan###########");
    
    Size winSize = Director::getInstance()->getWinSize();
    
    
    for (auto &item: touches)
    {
        auto touch = static_cast<Touch*>(item);
        Point location = touch->getLocation();
        
        if (location.x <= winSize.width / 2) {
            _activityJoystick(location);
        } else {
            _delegator->onAttack();
        }
        
    }
    
    
}

void OptionLayer::onTouchesMoved(const std::vector<Touch*>& touches, Event  *event)
{
    log("###########onTouchesMoved###########");

    Size winSize = Director::getInstance()->getWinSize();
    
    
    for (auto &item: touches)
    {
        auto touch = static_cast<Touch*>(item);
        
        Point location = touch->getLocation();
        Point start = touch->getStartLocation();
        
        if (start.x > winSize.width / 2) {
            return;
        }
        
        float distance = start.getDistance(location);
        Point direction = (location - start).normalize();
        _updateJoystick(direction, distance);
        _delegator->onWalk(direction, distance);
        
    }
    
    
}

void OptionLayer::onTouchesEnded(const std::vector<Touch*>& touches, Event  *event)
{
    log("###########onTouchesEnded###########");
    
    if (_joystick_bg->isVisible()) {
        _inactivityJoystick();
        _delegator->onStop();
    }
}

void OptionLayer::_activityJoystick(Point position)
{
    
     _joystick->setPosition(position);
     _joystick_bg->setPosition(position);
     _joystick->setVisible(true);
     _joystick_bg->setVisible(true);
    
    
}

void OptionLayer::_inactivityJoystick()
{
    _joystick->setPosition(_joystick_bg->getPosition());
    _joystick->setVisible(false);
    _joystick_bg->setVisible(false);
}

void OptionLayer::_updateJoystick(Point direction, float distance)
{
    // “‘°∞“°∏Àª˘◊˘°±µƒ‘≤–ƒŒ™¥•øÿ∆µ„≤Œøº£¨°∞“°∏À°±◊ˆœ‡”¶µƒ±„“À
    Point start = _joystick_bg->getPosition();
    
    if (distance < 32) {
        // »Áπ˚“∆∂ØŒ¥≥¨≥ˆ°∞“°∏Àª˘◊˘°±£¨°∞“°∏À°±‘⁄°∞ª˘◊˘°±◊ˆ∆´“∆
        _joystick->setPosition(start + (direction * distance));
    } else if (distance > 96) {
        // »Áπ˚“∆∂Ø≥¨≥ˆ°∞“°∏Àª˘◊˘°±£¨°∞“°∏À°±‘≤–ƒ º÷’‘⁄°∞ª˘◊˘°±±ﬂ‘µ◊ˆ∆´“∆
        _joystick->setPosition(start + (direction * 64));
    } else {
        // »Áπ˚“∆∂Ø≥¨≥ˆ°∞“°∏Àª˘◊˘°±£¨°∞“°∏À°±±ﬂ‘µ º÷’‘⁄°∞ª˘◊˘°±±ﬂ‘µ◊ˆ∆´“∆
        _joystick->setPosition(start + (direction * 32));
    }
}
