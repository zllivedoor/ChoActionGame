#include "Robot.h"

#include "cocos2d.h"
#include "ActionSprite.h"

using namespace cocos2d;

Robot::Robot()
{}

Robot::~Robot()
{}

bool Robot::init()
{
    bool ret = false;

    do {
        CC_BREAK_IF(!ActionSprite::initWithSpriteFrameName("robot_idle_00.png"));

        // ֮ǰ��CallFunc::create(this, callfunc_selector(Robot::idle))�Ѿ���������
        // ����c++11�������ص�
        CallFunc *callbackIdle = CallFunc::create(std::bind(&Robot::idle, this));

        // ����idle�����У����������ú󷴸�����
        Animation *idle = createAnimation("robot_idle_%02d.png", 5, 12);
        setIdleAction(RepeatForever::create(Animate::create(idle)));

        // ����walk�����ߣ�������ͬ�����ú󷴸�����
        Animation *walk = createAnimation("robot_walk_%02d.png", 6, 18);
        setWalkAction(RepeatForever::create(Animate::create(walk)));

        // ����attact�����������������ź�ص���idle����
        Animation *attack1 = createAnimation("robot_attack_%02d.png", 5, 30);
        setAttackAction(Sequence::create(Animate::create(attack1), callbackIdle, NULL));

        // ����hurt�����ˣ����������ź�ص���idle����
        Animation *hurt = createAnimation("robot_hurt_%02d.png", 3, 20);
        setHurtAction(Sequence::create(Animate::create(hurt), callbackIdle, NULL));

        // ����knockout�������������������ź����κε���
        Animation *knockout = createAnimation("robot_knockout_%02d.png", 5, 12);
        setKnockoutAction(Sequence::create(Animate::create(knockout), NULL));

        setATK(20); // ������
        setHP(100); // ����ֵ

        _aiState = ROBOT_AI_STATE_WAIT;
        _executeTime = 0;

        ret = true;
    } while (0);

    return ret;
}

void Robot::decide(Point target)
{
    Point location = this->getPosition();
    float distance  = location.getDistance(target);
    bool isFlipX = this->isFlipX();
    bool onTargetLeft = (location.x < target.x) ? true : false;

    // ��������˷�ת��(�泯��)������Ŀ������
    // ����û�з�ת(�泯��)���Ҳ���Ŀ�����
    // ������������ڻ����˱�����Ŀ�꣬������������Ŀ��
    if ((isFlipX && onTargetLeft) || (!isFlipX && !onTargetLeft)) {
        if (CCRANDOM_0_1() > 0.5) {
            _aiState = ROBOT_AI_STATE_PATROL;
        } else {
            _aiState = ROBOT_AI_STATE_STAND;
        }
    } else {
        if (distance <= ROBOT_VIEW_FIELD) {
            if (distance <= ROBOT_ATTACK_FIELD) {
                if (CCRANDOM_0_1() < 0.6) {
                    if (getActionState() == ACTION_STATE_IDLE) {
                        _aiState = ROBOT_AI_STATE_ATTACK;
                    }
                } else {
                    _aiState = ROBOT_AI_STATE_WAIT;
                }
            }
            else {
                _aiState = ROBOT_AI_STATE_FOLLOW;
            }
        } else {
            if (CCRANDOM_0_1() > 0.5) {
                _aiState = ROBOT_AI_STATE_PATROL;
            } else {
                _aiState = ROBOT_AI_STATE_STAND;
            }
        }
    }

    switch (_aiState)
    {
    case ROBOT_AI_STATE_ATTACK:
        this->attack();
        this->onAttack();
        _executeTime = 50;
        break;
    case ROBOT_AI_STATE_FOLLOW:
        this->walk();
        _moveDirection = (target - location).normalize();
        _executeTime = 10;
        break;
    case ROBOT_AI_STATE_PATROL:
        this->walk();
        _moveDirection.x = CCRANDOM_MINUS1_1();
        if (_moveDirection.x > 0) {
            _moveDirection.x += 0.5;
        } else {
            _moveDirection.x -= 0.5;
        }
        _moveDirection.y = CCRANDOM_MINUS1_1();
        if (_moveDirection.y > 0) {
            _moveDirection.y += 0.5;
        } else {
            _moveDirection.y -= 0.5;
        }
        _executeTime = CCRANDOM_0_1() * 100;
        break;
    case ROBOT_AI_STATE_STAND:
        this->idle();
        _executeTime = CCRANDOM_0_1() * 100;
        break;
    case ROBOT_AI_STATE_WAIT:
        this->idle();
        _executeTime = 30;
        break;
    default:
        break;
    }
}

void Robot::execute(Point target)
{
    if (_executeTime == 0) {
        decide(target);
    } else {
        _executeTime--;
    }
}

// Philon
// 2013-10-17
