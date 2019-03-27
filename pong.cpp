//Ryan Houck
//PONG in C++ using SFML

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

#include "Ball.hpp"

using namespace std;

int main(int argv, char** argc) {
    //Seeding rand
    srand(time(NULL));

    //Font
    sf::Font font;
    sf::Text text;
    font.loadFromFile("Sansation-Bold.ttf");
    text.setFont(font);
    sf::Color text_color = sf::Color(255, 255, 255, 255);
    text.setFillColor(text_color);

    enum players { P1, P2 };

    enum states { TITLE, INSTR, GAME, ENDSCREEN };

    //Setting up the window, resolution, & framerate
    sf::RenderWindow window(sf::VideoMode(1600, 900), "PONG");
    window.setFramerateLimit(60);

    sf::Color back_color = sf::Color(64, 64, 128, 255);

    //Map initialization
    Rect* map[3];
    sf::Color wall_color = sf::Color(255, 255, 255, 255);
    sf::Color midline_color = sf::Color(128, 128, 128, 255);
    map[0] = new Rect(0, 0, 1600, 20, wall_color, true);
    map[1] = new Rect(0, 880, 1600, 20, wall_color, true);
    map[2] = new Rect(790, 20, 20, 860, midline_color, false);

    //Paddle initialization
    Rect* paddles[2];
    sf::Color paddle_color = sf::Color(255, 255, 255, 255);
    paddles[0] = new Rect(20, 400, 20, 100, paddle_color, true);
    paddles[1] = new Rect(1560, 400, 20, 100, paddle_color, true);

    //Ball initialization
    sf::Color ball_color = sf::Color(255, 255, 255, 255);
    Ball* ball = new Ball(ball_color);

    //Game variables
    int p1_score = 0;
    int p2_score = 0;
    int winner = P1;
    int state = TITLE;
    stringstream ss;            //Used to write ints to a string
    bool space_pressed = false; //Used to set digital presses for the space bar

    //Main game loop
    while(window.isOpen()) {
        //Create a new event
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(back_color);

        //State-dependant code
        if(state == TITLE) {
            text.setString("PONG");
            text.setCharacterSize(150);
            text.setPosition(600, 200);
            window.draw(text);
            text.setString("By: Ryan Houck");
            text.setCharacterSize(50);
            text.setPosition(630, 350);
            window.draw(text);
            // Inside joke, ignore if looking through code xD
            /*text.setString("(And SKUHGHETTIE)");
            text.setPosition(575, 400);
            window.draw(text);*/
            text.setString("Press Enter to start!");
            text.setPosition(600, 600);
            window.draw(text);
            text.setString("(Or i for instructions)");
            text.setPosition(590, 675);
            window.draw(text);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                state = GAME;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
                state = INSTR;
            }
        }
        else if(state == INSTR) {
            text.setString("Player 1: Up='W', Down='S'");
            text.setPosition(525, 200);
            window.draw(text);
            text.setString("Player 2: Up=UP, Down=DOWN");
            text.setPosition(450, 300);
            window.draw(text);
            text.setString("SPACE: Turn off bounding (in-game)");
            text.setPosition(390, 400);
            window.draw(text);
            text.setString("You may press BACKSPACE to go back to the title screen");
            text.setPosition(150, 700);
            window.draw(text);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
                state = TITLE;
            }
        }
        else if(state == GAME) {
            //Controlling the left paddle
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                paddles[0]->move(0, -10);
                if(paddles[0]->getPos().y < 20) {
                    paddles[0]->move(0, 10);
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                paddles[0]->move(0, 10);
                if(paddles[0]->getPos().y > 880 - paddles[0]->getSize().y) {
                    paddles[0]->move(0, -10);
                }
            }

            //Controlling the right paddle
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                paddles[1]->move(0, -10);
                if(paddles[1]->getPos().y < 20) {
                    paddles[1]->move(0, 10);
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                paddles[1]->move(0, 10);
                if(paddles[1]->getPos().y > 880 - paddles[1]->getSize().y) {
                    paddles[1]->move(0, -10);
                }
            }

            //Toggling the wall stability
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                if(!space_pressed) {
                    if(map[0]->getCollision()) {
                        map[0]->setCollision(false);
                        map[0]->setColor(midline_color);
                        map[1]->setCollision(false);
                        map[1]->setColor(midline_color);
                    }
                    else {
                        map[0]->setCollision(true);
                        map[0]->setColor(wall_color);
                        map[1]->setCollision(true);
                        map[1]->setColor(wall_color);
                    }
                    space_pressed = true;
                }
            }
            else {
                space_pressed = false;
            }

            //Move the ball
            ball->move(ball->getVelocity().x, ball->getVelocity().y);

            //Paddle collision
            if(ball->collidesWith(paddles[0])) {
                ball->hitPaddle();
                ball->setPos(sf::Vector2f(paddles[0]->getPos().x + paddles[0]->getSize().x, ball->getPos().y));
            }
            else if(ball->collidesWith(paddles[1])) {
                ball->hitPaddle();
                ball->setPos(sf::Vector2f(paddles[1]->getPos().x - ball->getSize().x, ball->getPos().y));
            }

            //Wall collision
            if(ball->collidesWith(map[0])) {
                ball->hitWall();
                ball->setPos(sf::Vector2f(ball->getPos().x, map[0]->getSize().y));
            }
            else if(ball->collidesWith(map[1])) {
                ball->hitWall();
                ball->setPos(sf::Vector2f(ball->getPos().x, 900.0 - ball->getSize().y - map[1]->getSize().y));
            }

            //Wraparound logic
            if(ball->getPos().y > 900) {
                ball->setPos(sf::Vector2f(ball->getPos().x, ball->getPos().y - 900.0));
            }
            else if(ball->getPos().y < -20) {
                ball->setPos(sf::Vector2f(ball->getPos().x, ball->getPos().y + 900.0));
            }

            //If P1 scored
            if(ball->getPos().x > 1600) {
                p1_score++;
                ball->reset();
                ball->setPos(sf::Vector2f(790.0, 440.0));
                if(p1_score == 11) {
                    winner = P1;
                    state = ENDSCREEN;
                }
            }

            //If P2 scored
            if(ball->getPos().x < -20) {
                p2_score++;
                ball->reset();
                ball->setPos(sf::Vector2f(790.0, 440.0));
                if(p2_score == 11) {
                    winner = P2;
                    state = ENDSCREEN;
                }
            }

            //Drawing
            window.draw(map[0]->getShape());
            window.draw(map[1]->getShape());
            window.draw(map[2]->getShape());

            ss << p1_score;
            text.setString(ss.str());
            text.setPosition(375, 100);
            window.draw(text);
            ss.str("");
            ss.clear();
            ss << p2_score;
            text.setString(ss.str());
            text.setPosition(1175, 100);
            window.draw(text);
            ss.str("");
            ss.clear();

            window.draw(paddles[0]->getShape());
            window.draw(paddles[1]->getShape());
            window.draw(ball->getShape());
        }
        else if(state == ENDSCREEN) {
            if(winner == P1) {
                text.setString("Player 1 won!");
            }
            else {
                text.setString("Player 2 won!");
            }
            text.setPosition(630, 350);
            window.draw(text);
            text.setString("Please press Enter to start again");
            text.setPosition(450, 600);
            window.draw(text);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                state = GAME;
                p1_score = 0;
                p2_score = 0;
                ball->reset();
                ball->setPos(sf::Vector2f(790.0, 440.0));
                paddles[0]->setPos(sf::Vector2f(20.0, 400.0));
                paddles[1]->setPos(sf::Vector2f(1560.0, 400.0));
            }
        }
        window.display();
    }
    return 0;
}
