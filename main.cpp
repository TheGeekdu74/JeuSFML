#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <unistd.h>
#include <cmath>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 768

using namespace sf;
using std::cout;

typedef struct{
    int x;
    int y;
    int hp;
    int dmgX;
    int dmgY;
}Data;

Packet& operator <<(sf::Packet& packet, const Data& data)
{
    return packet << data.x;
}
Packet& operator >>(sf::Packet& packet, Data& data)
{
    return packet >> data.x;
}

int main()
{

    Data data1;
    Data data2;
    data1.x = 25;
    data1.y = WINDOW_HEIGHT - 25;
    data1.hp = 200;
    data2.hp = 200;

    RenderWindow app(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML window");
    app.setFramerateLimit(500);

    RectangleShape rect(Vector2f(50,50));
    rect.setOrigin(25,25);
    rect.setPosition(data1.x, data1.y);

    //------------- PLATFORM SETUP ---------------

    RectangleShape platform(Vector2f(200, 50));
    platform.setOrigin(100, 25);
    platform.setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);

    //------------------ FOND --------------------
    Texture fond1;
    if (!fond1.loadFromFile("Map_une.jpg"))
    {
        printf("Erreur: l'image ne s'affiche pas");
    }
    Sprite fond(fond1);
    fond.setPosition(0,0);
    app.draw(fond);

    //------------- LIFE BARS SETUP --------------

    RectangleShape lifeBar1(Vector2f(data1.hp, 50));
    lifeBar1.setFillColor(Color::Red);
    lifeBar1.setPosition(10, 10);

    RectangleShape lifeBarBorder1(Vector2f(200, 50));
    lifeBarBorder1.setFillColor(Color::Transparent);
    lifeBarBorder1.setOutlineThickness(5);
    lifeBarBorder1.setOutlineColor(Color::White);
    lifeBarBorder1.setPosition(10, 10);

    RectangleShape lifeBar2(Vector2f(data2.hp, 50));
    lifeBar2.setFillColor(Color::Red);
    lifeBar2.setPosition(1070, 10);

    RectangleShape lifeBarBorder2(Vector2f(200, 50));
    lifeBarBorder2.setFillColor(Color::Transparent);
    lifeBarBorder2.setOutlineThickness(5);
    lifeBarBorder2.setOutlineColor(Color::White);
    lifeBarBorder2.setPosition(1070, 10);

    while (app.isOpen()){
//        UdpSocket socket;
//
//        socket.setBlocking(false);
//        unsigned short port = 54000;
//
//        Packet player1;
//        Packet player2;
//        Data data;
//
//        data.x = 10;
//        data.y = 20;
//        data.hp = 100;
//
//        player1 << data;
//
//        if(socket.bind(54000) != Socket::Done){}
//
//        IpAddress recipient = "127.0.0.1";
//        if(socket.send(player1, recipient, port) != Socket::Done){}
//
//        IpAddress sender;
//        if(socket.receive(player2, sender, port) != Socket::Done){}
//
//        Data data2;
//        player2 >> data;
//        cout << data2.hp << std::endl;

        if(Keyboard::isKeyPressed(Keyboard::Z)){ //Montee jump
            while(data1.y > 200 && rect.getGlobalBounds().intersects(platform.getGlobalBounds()) == 0){
                data1.y -= 2;
                usleep(0.1);
                rect.setPosition(data1.x,data1.y);

                cout << rect.getGlobalBounds().intersects(platform.getGlobalBounds()) << std::endl;

                if(Keyboard::isKeyPressed(Keyboard::Q)){
                    if(data1.x >= 25){
                        data1.x -= 1;
                        rect.setPosition(data1.x, data1.y);
                    }
                }

                if(Keyboard::isKeyPressed(Keyboard::D)){
                    if(data1.x + 25 <= WINDOW_WIDTH){
                        data1.x += 1;
                        rect.setPosition(data1.x, data1.y);
                    }
                }

                app.clear();
                app.draw(fond);
                app.draw(rect);
                app.draw(lifeBar1);
                app.draw(lifeBarBorder1);
                app.draw(lifeBarBorder2);
                app.draw(lifeBar2);
                app.draw(platform);
                app.display();
            }
            while(data1.y + 25 < WINDOW_HEIGHT && rect.getGlobalBounds().intersects(platform.getGlobalBounds()) == 0){ //Descente jump
                data1.y += 2;
                usleep(0.1);
                rect.setPosition(data1.x,data1.y);

                if(Keyboard::isKeyPressed(Keyboard::Q)){
                    if(data1.x >= 25){
                        data1.x -= 1;
                        rect.setPosition(data1.x, data1.y);
                    }
                }

                if(Keyboard::isKeyPressed(Keyboard::D)){
                    if(data1.x + 25 <= WINDOW_WIDTH){
                        data1.x += 1;
                        rect.setPosition(data1.x, data1.y);
                    }
                }
                app.clear();
                app.draw(fond);
                app.draw(rect);
                app.draw(lifeBar1);
                app.draw(lifeBarBorder1);
                app.draw(lifeBarBorder2);
                app.draw(lifeBar2);
                app.draw(platform);
                app.display();
            }
        }

        if(Keyboard::isKeyPressed(Keyboard::Q)){
            if(data1.x >= 25){
                data1.x -= 1;
                usleep(0.5);
                rect.setPosition(data1.x, data1.y);
            }
        }
        if(Keyboard::isKeyPressed(Keyboard::S)){
            if(data1.y + 25 <= WINDOW_HEIGHT){
                data1.y += 1;
                rect.setPosition(data1.x, data1.y);
            }
        }
        if(Keyboard::isKeyPressed(Keyboard::D)){
            if(data1.x + 25 <= WINDOW_WIDTH){
                data1.x += 1;
                usleep(0.5);
                rect.setPosition(data1.x, data1.y);
            }
        }

        Event event;
        while (app.pollEvent(event)) {
            switch(event.type){
                case Event::Closed:
                    app.close();
                    break;
                case Event::MouseButtonPressed:
                    if(event.mouseButton.button == Mouse::Left){
                        if(data1.hp > 0){
                            data1.hp -= 20;
                            lifeBar1.setSize(Vector2f(data1.hp, 50));
                            app.draw(lifeBar1);
                        }
                    }
                    break;
            }
        }

        app.clear();
        app.draw(fond);
        app.draw(rect);
        app.draw(lifeBar1);
        app.draw(lifeBarBorder1);
        app.draw(lifeBarBorder2);
        app.draw(lifeBar2);
        app.draw(platform);
        app.display();

    }
    return 0;
}
