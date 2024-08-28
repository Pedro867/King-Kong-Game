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
	Cenario cenario(player, bomba, &window);

	while (window.isOpen()) {

		while (window.pollEvent(evento)) {
			if (evento.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear();

		/*mesma logica da colis�o do player com ambiente e a movimenta��o da bomba*/
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
		cenario.desenhaCenario(&window);//colisoes dentro dessa funcao
		player.moverY();
		player.moverX(evento);
		window.draw(player.getPlayer());
		window.draw(bomba.getBombaNormal());

		window.display();
		sf::sleep(sf::milliseconds(20.f));
	}

	return 0;
}
