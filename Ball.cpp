#include "Ball.hpp"

#include <stdlib.h>

#define RAND_SPD (float)((rand() % 20) - 10)

/**
 * Parameterized constructor
 * @param color The color of the ball
 */
Ball::Ball(sf::Color color) : Rect(790.0, 440.0, 20.0, 20.0, color, true) {
    setRandSpeed();
}

/**
 * Destructor
 */
Ball::~Ball() {
}

/**
 * Returns the ball's velocity
 * @return velocity
 */
sf::Vector2f Ball::getVelocity() {
    return velocity;
}

/**
 * What the ball does when it hits the paddle
 */
void Ball::hitPaddle() {
    velocity.x = velocity.x * -1.0;
    bumpSpeed();
}

/**
 * What the ball does when it hits the wall
 */
void Ball::hitWall() {
    velocity.y = velocity.y * -1.0;
}

/**
 * Resets the ball's attributes after scoring a point
 */
void Ball::reset() {
    setRandSpeed();
}

/**
 * Bumps up the speed of the ball a little bit
 */
void Ball::bumpSpeed() {
    if(velocity.x < 20.0 && velocity.x > 0) {
        velocity.x += 1;
    }
    else if(velocity.x > -20.0 && velocity.x < 0) {
        velocity.x -= 1;
    }
    if(velocity.y < 20.0 && velocity.y > 0) {
        velocity.y += 1;
    }
    else if(velocity.y > -20.0 && velocity.y < 0) {
        velocity.y -= 1;
    }
}

/**
 * Sets the ball to a pseudo-random speed (within a certain range)
 */
void Ball::setRandSpeed() {
    float x = RAND_SPD;
    float y = RAND_SPD;
    while(x < 3 && x > -3 || y < 3 && y > -3) {
        x = RAND_SPD;
        y = RAND_SPD;
    }

    velocity.x = x;
    velocity.y = y;
}