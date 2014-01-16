#ifndef Philon_cocos2dx_PompaDroid_ACTIONSPRITE_H_
#define Philon_cocos2dx_PompaDroid_ACTIONSPRITE_H_
#pragma once

#include "cocos2d.h"

// ����pd_sprites.plist�õ�����������������״̬
typedef enum {
    ACTION_STATE_NONE = 0,
    ACTION_STATE_IDLE,
    ACTION_STATE_WALK,
    ACTION_STATE_ATTACK,
    ACTION_STATE_HURT,
    ACTION_STATE_KNOCKOUT,
} ActionState;

class ActionSprite : public cocos2d::Sprite
{
public:
    ActionSprite();
    ~ActionSprite();

    void idle();
    void walk();
    void attack();
    void hurt();
    void knockout();

    // ����ÿ��״̬������get/set����
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _idleAction, IdleAction);
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _attackAction, AttackAction);
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _hurtAction, HurtAction);
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _knockoutAction, KnockoutAction);
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _walkAction, WalkAction);

    // ����ĵ�ǰ״̬
    CC_SYNTHESIZE(ActionState, _currentState, ActionState);

    CC_SYNTHESIZE(unsigned int, _hp, HP); // ����ֵ
    CC_SYNTHESIZE(unsigned int, _atk, ATK); // ������

protected:
    // ����һ������״̬�����ķ���
    // fmt   - ״̬��ͼƬ����ʽ(�鿴pd_sprites.plist,ÿ��״̬��ʽ������hero_idle_xx.png)
    // count - ״̬ͼƬ���е�����
    // fps   - �����Ĳ���֡��
    static cocos2d::Animation *createAnimation(const char *fmt, int count, float fps);

private:
    // �л���Ա�ĵ�ǰ״̬
    bool _changeState(ActionState state);
};

#endif // End of Philon_cocos2dx_PompaDroid_ACTIONSPRITE_H_
