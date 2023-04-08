#include <iostream>
#include <SFML/Graphics.hpp>
constexpr int BLOCK_SIZE = 50;

class Block{
public:
    Block() : x(0), y(0){}

    void moveRight(){x++;}
    void moveLeft(){x--;}
    void moveUp(){y--;}
    void moveDown(){y++;}

    int getX() const{return x;}
    int getY(){return y;}

private:
    int x;
    int y;
};

void drawBlock(Block& block, sf::RenderWindow& window){
    sf::VertexArray quad(sf::Quads, 4);

    quad[0].position = sf::Vector2f(block.getX(), block.getY());
    quad[1].position = sf::Vector2f(block.getX() + BLOCK_SIZE, block.getY());
    quad[2].position = sf::Vector2f(block.getX() + BLOCK_SIZE, block.getY() + BLOCK_SIZE);
    quad[3].position = sf::Vector2f(block.getX(), block.getY() + BLOCK_SIZE);

    quad[0].color = sf::Color::Cyan;
    quad[1].color = sf::Color::Cyan;
    quad[2].color = sf::Color::Cyan;
    quad[3].color = sf::Color::Cyan;

    window.draw(quad);
}

int main() {
    sf::RenderWindow window{sf::VideoMode::getDesktopMode(), "Simple Game"};
    Block tester{};
    bool key_pressed =  false;

    while(window.isOpen()){
        window.clear();
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        while (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !key_pressed)
        {
            tester.moveLeft();
            key_pressed = true;
        }
        while (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !key_pressed)
        {
            tester.moveDown();
            key_pressed = true;
        }
        while (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !key_pressed)
        {
            tester.moveRight();
            key_pressed = true;
        }
        while (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !key_pressed)
        {
            tester.moveUp();
            key_pressed = true;
        }
        key_pressed = false;

        drawBlock(tester,window);
        window.display();

    }
    return 0;
}
