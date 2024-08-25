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
	sf::VideoMode video(1366, 700);
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
	Cenario cenario;

	while (window.isOpen()) {

		while (window.pollEvent(evento)) {
			if (evento.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear();

		/*if (((player.testaColisaoChao(cenario.getChao()))
		 || (player.testaColisaoChao(cenario.getChao()))) == true) {
		 player.setVelY(0);
		 } else {
		 player.setVelY(1);
		 }
		 player.testaColisaoParede(cenario.getParede1());
		 player.testaColisaoParede(cenario.getParede2());*/

		/*mesma logica da colisão do player com ambiente e a movimentação da bomba*/
		/*if (((bomba.testaColisaoChao(chao2)) || (bomba.testaColisaoChao(chao1)))== true) {

		 if((bomba.testaColisaoParede(paredeDireita))||(bomba.testaColisaoParede(paredeEsquerda))== true){
		 bomba.inverteVelX();
		 }

		 bomba.moverX();

		 } else {
		 bomba.moverY();
		 }*/

		//inutil com as funcoes moverY, moverX, etc
		//bomba.mover();
		//Desenha
		window.draw(fundo);
		cenario.desenhaCenario(&window, &player);
		player.mover(evento);
		window.draw(player.getPlayer());
		window.draw(bomba.getBombaNormal());

		window.display();
		sf::sleep(sf::milliseconds(20.f));
	}

	return 0;
}
