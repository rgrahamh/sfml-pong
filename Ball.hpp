#ifndef BALL_H
#define BALL_H

#include "Rect.hpp"
class Ball : public Rect {
  public:
    Ball(sf::Color color);
    ~Ball();
    sf::Vector2f getVelocity();
    void hitPaddle();
    void hitWall();
    void reset();

  private:
    Rect rect;
    sf::Vector2f velocity;

    //Helper functions
    void bumpSpeed();
    void setRandSpeed();
};
#endif
