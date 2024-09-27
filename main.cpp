//============================================================================
// Name        : King Kong Game
// Author      : Lucas Lenz, Pedro Lucas e Rafael Torres
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <SFMl\Graphics.hpp>
#include <iostream>
#include "Player.hpp"
#include "Bomba.hpp"
#include "Cenario.hpp"

int main(int argc, char **argv) {
	setbuf(stdout, NULL);
	sf::VideoMode video(1200, 600);
	sf::RenderWindow window(video, "King Kong");
	sf::Event evento;

	//Fundo
	sf::Texture background;
	background.loadFromFile("assets/background.png");
	sf::Sprite fundo;
	fundo.setTexture(background);
	fundo.setOrigin(256, 256);
	fundo.setPosition(window.getPosition().x / 2, window.getPosition().y / 2);
	fundo.setScale(6, 6);

	//Texto
	sf::Font fonte;
	fonte.loadFromFile("assets/Arial.ttf");
	sf::Text vidas;
	vidas.setFont(fonte);
	vidas.setCharacterSize(30);
	vidas.setOrigin(15, 15);
	vidas.setFillColor(sf::Color::Red);
	vidas.setPosition(45*(window.getSize().x / 100), 5*(window.getSize().y / 100));

	//Elementos
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

		//movimenta elementos se o kong tiver iniciado
		if (cenario.getIniciouKong()) {
			player.moverY(evento);
			player.moverX(evento);
			player.colideBomba(bomba);
			bomba.mover();
		}

		//	OS ELEMENTOS ESTAVAM SENDO DESENHADOS AQUI, PASSEI PRA FUNCAO DESENHA CENARIO
		string vidasString = to_string(player.getVidas());

		vidas.setString("Vidas: " + vidasString);

		window.draw(vidas);

		window.display();
	}

	return 0;
}
