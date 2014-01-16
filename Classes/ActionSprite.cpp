#include "ActionSprite.h"

#include "cocos2d.h"

using namespace cocos2d;

ActionSprite::ActionSprite()
{
    _idleAction = NULL;
    _walkAction = NULL;
    _attackAction = NULL;
    _hurtAction = NULL;
    _knockoutAction = NULL;
}

ActionSprite::~ActionSprite()
{}


void ActionSprite::idle()
{
    if (_changeState(ACTION_STATE_IDLE)) {
        runAction(_idleAction);
    }
}

void ActionSprite::attack()
{
    if (_changeState(ACTION_STATE_ATTACK)) {
        runAction(_attackAction);
    }

}

void ActionSprite::walk()
{
    if (_changeState(ACTION_STATE_WALK)) {
        runAction(_walkAction);
    }
}

void ActionSprite::hurt()
{
    if (_changeState(ACTION_STATE_HURT)) {
        runAction(_hurtAction);
    }
}

void ActionSprite::knockout()
{
    if (_changeState(ACTION_STATE_KNOCKOUT)) {
        runAction(_knockoutAction);
    }
}

bool ActionSprite::_changeState(ActionState state)
{
    bool ret = false;

    // �����Ѿ���������Game Over�����Ͳ����ٳ������������ˣ�
    if (_currentState == ACTION_STATE_KNOCKOUT) {
        goto change_state_failed;
    }
    
    // �����Ѿ�����Ҫ�ı��״̬����û��Ҫ�ڸı��ˣ�
    if (_currentState == state) {
        goto change_state_failed;
    }

    // �ı䶯��֮ǰ����ֹͣ���ж���
    this->stopAllActions();

    _currentState = state;
    ret = true;

change_state_failed:
    return ret;
}

Animation *ActionSprite::createAnimation(const char *fmt, int count, float fps)
{
    Array *frames = Array::createWithCapacity(count);
    int i = 0;

    for (i = 0; i < count; i++) {
        const char *png = String::createWithFormat(fmt, i)->getCString();
        SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(png);
        frames->addObject(frame);
    }

    return Animation::createWithSpriteFrames(frames, 1 / fps);
}
