#ifndef __MODEL_PLAYER_H__
#define __MODEL_PLAYER_H__

#include "cocos2d.h"
#include "Entity.h"

class Player : public Entity
{
public:
    /** 
     * create Player with role 
     * @return Player Object
     */
    static Player * create(const std::string& id, const std::string& role);
    
    enum class Status : std::int8_t
    {
        FREE,
        FREEZE,
        DIE
    };

    enum class Direction : std::int8_t
    {
        LEFT,
        RIGHT,
        UP,
        DOWN,
        NONE
    };

    struct Attr
    {
        uint8_t speed;
        uint8_t damage;
        uint8_t maxBubble;
        uint8_t currentBubble;
    };

    uint8_t getSpeed();
    void setSpeed(uint8_t speed);

    uint8_t getDamage();
    void setDamage(uint8_t damage);

    uint8_t getBubble();
    void setBubble(uint8_t bubble);

    void setStatus(Status);
    Status getStatus();

    void setDirectionByKey(Direction direction);
    void removeDirectionByKey(Direction direction);
    void updateDirection();
    void setDirection(Direction direction);
    Direction getDirection();
    
    // TODO
    void setAnimation();

private:
    Status _status;
    Attr attr;
    cocos2d::Size size;
    // record what time the direction was set
    time_t directions[4];
    Direction direction;

    bool init();
    bool initWithRole(const std::string& role);
    bool initAnimation();

};
#endif
