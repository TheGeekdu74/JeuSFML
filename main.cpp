#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

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
    RenderWindow app(VideoMode(800, 600), "SFML window");
    RectangleShape rectangle(Vector2f(200,200));

    while (app.isOpen())
    {
        UdpSocket socket;
        socket.setBlocking(false);
        unsigned short port = 80;

        Packet player1;
        Packet player2;
        Data data;

        data.x = 10;
        data.y = 20;
        data.hp = 100;

        player1 << data;

        // lie la socket à un port
        if(socket.bind(port) != Socket::Done)
            printf("Erreur de connexion au port");

        IpAddress recipient = "127.0.0.1";

        if(socket.send(player1, recipient, port) != Socket::Done)
            printf("Erreur d'envoi");

        IpAddress sender;

        if(socket.receive(player2, sender, port) != Socket::Done)
            printf("Erreur de reception");

        Data data2;
        player2 >> data;
        cout << data2.hp << std::endl;


        Event event;
        while (app.pollEvent(event)) {
            if (event.type == Event::Closed)
                app.close();
        }
        app.clear();
        app.display();
    }
    return 0;
}
