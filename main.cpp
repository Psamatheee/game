#include <iostream>
#include <SFML/Graphics.hpp>
constexpr int BLOCK_SIZE = 50;
constexpr int FALL_STEP = 1;
constexpr int STEP = 50;
constexpr int X_DIM = 10;
constexpr int Y_DIM = 15;

class Block{
public:
    Block(int X, int Y) : x(X), y(Y){}

    void moveRight(){x++;}
    void moveLeft(){x--;}
    void moveUp(){if(y - STEP > 0) y--;}
    void moveDown(){
       y++;
    }

    int getX() const{return x;}
    int getY() const{return y;}

private:
    int x;
    int y;
    bool reached_bottom;
};

class GameState{
public:
    GameState() {
        for(auto & i : board){
            for(int & j : i){
                j = 0;
            }
        }
    }

    void moveLeft(){
        if(board[curr->getX()-1][curr->getY()] == 0 && curr->getX() > 0){
            board[curr->getX()][curr->getY()] = 0;
            board[curr->getX()-1][curr->getY()] = 1;
            curr->moveLeft();
        }
    }
    void moveRight(){
        if(board[curr->getX()+1][curr->getY()] == 0 && curr->getX() + 1 < X_DIM){
            board[curr->getX()][curr->getY()] = 0;
            board[curr->getX()+1][curr->getY()] = 1;
            curr->moveRight();
        }
    }
    bool moveDown(){
        if(board[curr->getX()][curr->getY()+1] == 0 && curr->getY() +1 < Y_DIM){
            board[curr->getX()][curr->getY()] = 0;
            board[curr->getX()][curr->getY()+1] = 1;
            curr->moveDown();
            return true;
        }
        return false;
    }
    bool newBlock(){
        if(board[X_DIM/2][0] == 1) return false;
        auto* b = new Block{X_DIM/2,0};
        blocks.push_back(b);
        curr = b;
        board[X_DIM/2][0] = 1;
        return true;
    }

    std::vector<Block*>& getBlocks(){return blocks;}
private:
    Block* curr;
    int board[X_DIM][Y_DIM];
    std::vector<Block*> blocks;
};

void drawBlock(Block* block, sf::RenderWindow& window){
    sf::VertexArray quad(sf::Quads, 4);

    quad[0].position = sf::Vector2f(block->getX()*BLOCK_SIZE, block->getY()*BLOCK_SIZE);
    quad[1].position = sf::Vector2f(block->getX()*BLOCK_SIZE + BLOCK_SIZE, block->getY()*BLOCK_SIZE);
    quad[2].position = sf::Vector2f(block->getX()*BLOCK_SIZE + BLOCK_SIZE, block->getY()*BLOCK_SIZE + BLOCK_SIZE);
    quad[3].position = sf::Vector2f(block->getX()*BLOCK_SIZE, block->getY()*BLOCK_SIZE + BLOCK_SIZE);

    quad[0].color = sf::Color::Cyan;
    quad[1].color = sf::Color::Cyan;
    quad[2].color = sf::Color::Cyan;
    quad[3].color = sf::Color::Cyan;

    window.draw(quad);
}

void drawGame(std::vector<Block*>& blocks, sf::RenderWindow& window){
    for(Block* b : blocks){
        drawBlock(b,window);
    }
}

int main() {
    sf::RenderWindow window{sf::VideoMode::getDesktopMode(), "Simple Game"};
    bool key_pressed =  false;
    GameState game{};
    game.newBlock();

    auto h = window.getSize().x;
    auto w = window.getSize().y;
    bool exit = false;

    sf::Clock clock{};

    while(window.isOpen() && !exit){
        window.clear();
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        if(clock.getElapsedTime() > sf::milliseconds(100)){
            bool moves = game.moveDown();
            if(!moves){
                if(!game.newBlock()) exit = true;
            }
            clock.restart();
        }
        while (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

            if(!key_pressed) game.moveLeft() ;
            key_pressed = true;
        }
        while (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if(!key_pressed) game.moveRight() ;
            key_pressed = true;
        }

        key_pressed = false;

        drawGame(game.getBlocks(),window);
        window.display();


    }
    return 0;
}
