//============================================================================
// Name        : Donkey.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <SFMl\Graphics.hpp>
#include <iostream>
#include "Player.hpp"
//#include "Chao.hpp"
//#include "Parede.hpp"
#include "Bomba.hpp"
#include "Cenario.hpp"

int main(int argc, char **argv) {
	setbuf(stdout, NULL);
	sf::VideoMode video(1200, 600);
	sf::RenderWindow window(video, "King Kong");

	sf::Texture background;
	background.loadFromFile("assets/background.png");
	sf::Sprite fundo;
	fundo.setTexture(background);
	fundo.setOrigin(256, 256);
	fundo.setPosition(window.getPosition().x / 2, window.getPosition().y / 2);
	fundo.setScale(6, 6);

	sf::Event evento;

	Player player(window);
	Bomba bomba(window);
	Cenario cenario(player, &window);
	cenario.setPlayerLayer();
	cenario.setaAndarBomba(bomba);

	while (window.isOpen()) {

		while (window.pollEvent(evento)) {
			if (evento.type == sf::Event::Closed) {
				window.close();
			}
		}
		sf::sleep(sf::milliseconds(20.f));
		window.clear();

		//Desenha cenario e fundo
		window.draw(fundo);
		cenario.desenhaCenario(&window, bomba); //colisoes dentro dessa funcao
		//cenario.iniciarKong(&window);

		//movimenta elementos
		player.moverY(evento);
		player.moverX(evento);
		player.colideBomba(bomba);
		bomba.mover();

		//desenha elementos
		window.draw(player.getPlayer());
		window.draw(bomba.getBombaNormal());

		window.display();
	}

	return 0;
}
