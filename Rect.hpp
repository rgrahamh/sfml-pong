#ifndef RECT_H
#define RECT_H
#include <SFML/Graphics.hpp>

class Rect {
  public:
    Rect();
    Rect(float x, float y, float w, float h, sf::Color color, bool collidable);
    ~Rect();

    //Getters and setters
    sf::Vector2f getPos();
    void setPos(sf::Vector2f pos);
    sf::Vector2f getSize();
    bool getCollision();
    void setCollision(bool c);
    void setColor(sf::Color color);

    //Wrappers for the operations
    void move(float x, float y);
    const sf::RectangleShape getShape();

    //Collision detection
    bool collidesWith(Rect* other);

  private:
    sf::RectangleShape rect;
    bool collision;
};
#endif
