#include "Rect.hpp"

Rect::Rect() {
    rect = sf::RectangleShape(sf::Vector2f(20, 20));
    rect.setPosition(sf::Vector2f(0, 0));
    rect.setFillColor(sf::Color(255, 255, 255, 255));
    collision = false;
}

/**
 * Parameterized constructor for Rect
 * @param x The x position of the rectangle
 * @param y The y position of the rectangle
 * @param w The width of the rectangle
 * @param h The height of the rectangle
 * @param color The color of the rectangle
 * @param collidable If the rectangle should have collision detection
 */
Rect::Rect(float x, float y, float w, float h, sf::Color color, bool collidable = false) {
    rect = sf::RectangleShape(sf::Vector2f(w, h));
    rect.setPosition(sf::Vector2f(x, y));
    rect.setFillColor(color);
    collision = collidable;
}

/**
 * Destructor for Rect
 */
Rect::~Rect() {
    delete &rect;
}

/**
 * Tells us if it's colliding with another rectangle
 * @param other The other rectangle
 * @return true if it's colliding, false otherwise
 */
bool Rect::collidesWith(Rect* other) {
    if(other->getCollision() && this->collision) {
        sf::Vector2f rect1_pos = this->rect.getPosition();
        sf::Vector2f rect1_size = this->rect.getSize();
        sf::Vector2f rect2_pos = other->getPos();
        sf::Vector2f rect2_size = other->getSize();

        //Checking if the top left point is in rect2
        int check_x = rect1_pos.x;
        int check_y = rect1_pos.y;

        for(int i = 0; i < 2; i++) {
            for(int i = 0; i < 4; i++) {
                //If the point being checked is in rect2, return true
                if(check_x < rect2_pos.x + rect2_size.x && check_x > rect2_pos.x && check_y < rect2_pos.y + rect2_size.y && check_y > rect2_pos.y) {
                    return true;
                }
                switch(i) {
                    case 0:
                        //Checking if the bottom left point is in rect2
                        check_x = rect1_pos.x + rect1_size.x;
                        break;
                    case 1:
                        //Checking if the top right point is in rect2
                        check_x = rect1_pos.x;
                        check_y = rect1_pos.y + rect1_size.y;
                        break;
                    case 2:
                        //Checking if the bottom right point is in rect2
                        check_x = rect1_pos.x + rect1_size.x;
                        break;
                }
            }
            //Switch which rectangle's corners are being checked
            sf::Vector2f tempVal = rect1_pos;
            rect1_pos = rect2_pos;
            rect2_pos = tempVal;
            tempVal = rect1_size;
            rect1_size = rect2_size;
            rect2_size = tempVal;
        }
    }
    //If none of the 8 points checked are in the other rectangle or either rectangle isn't collidable, return false
    return false;
}

/**
 * Getter for the rect's x value
 * @return the rect's x value
 */
sf::Vector2f Rect::getPos() {
    return rect.getPosition();
}

void Rect::setPos(sf::Vector2f pos) {
    rect.setPosition(pos);
}

/**
 * Getter for the rect's height
 * @return the rect's height
 */
sf::Vector2f Rect::getSize() {
    return rect.getSize();
}

/**
 * Getter for if the rect has collision
 * @return the rect's collision status
 */
bool Rect::getCollision() {
    return collision;
}

/**
 * Sets if the surface is collidable or not
 * @param c If the surface should be collidable
 */
void Rect::setCollision(bool c) {
    collision = c;
}

/**
 * Sets the color of the rectangle
 * @param color The new color of the rectangle
 */
void Rect::setColor(sf::Color color) {
    rect.setFillColor(color);
}

/**
 * Moves the rectangle by (x,y)
 * @param x The x value the rectangle should be moved by
 * @param y The y value the rectangle should be moved by
 */
void Rect::move(float x, float y) {
    rect.move(x, y);
}

/**
 * Returns the rectangle's shape
 * @return The rectangle's shape
 */
const sf::RectangleShape Rect::getShape() {
    return rect;
}