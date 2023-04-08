#include <iostream>
#include <SFML/Graphics.hpp>
constexpr int BLOCK_SIZE = 50;
constexpr int FALL_STEP = 1;
constexpr int STEP = 50;

class Block{
public:
    Block(unsigned int maxX, unsigned int maxY) : x(maxX/2 - BLOCK_SIZE), y(0), max_x(maxX), max_y(maxY){}

    void moveRight(){if(x + BLOCK_SIZE + STEP < max_x  && !reached_bottom) x+=STEP;}
    void moveLeft(){if(x - STEP > 0 && !reached_bottom)x-=STEP;}
    void moveUp(){if(y - STEP > 0) y-=STEP;}
    void moveDown(){
        if(y + BLOCK_SIZE + STEP < max_y) y+=FALL_STEP;
        else reached_bottom = true;
    }

    int getX() const{return x;}
    int getY(){return y;}

private:
    int x;
    int y;
    unsigned int max_x;
    unsigned int max_y;
    bool reached_bottom;
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
    bool key_pressed =  false;

    auto h = window.getSize().x;
    auto w = window.getSize().y;

    sf::Clock clock{};

    Block tester{h,w};

    while(window.isOpen()){
        window.clear();
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        if(clock.getElapsedTime() > sf::milliseconds(5)){
            tester.moveDown();
            clock.restart();
        }
        while (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if(!key_pressed) tester.moveLeft();
            key_pressed = true;
        }
        while (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if(!key_pressed) tester.moveRight();
            key_pressed = true;
        }

        key_pressed = false;

        drawBlock(tester,window);
        window.display();

    }
    return 0;
}
