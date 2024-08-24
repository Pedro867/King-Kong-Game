#include <SFMl\Graphics.hpp>
#include "Player.hpp"
#include "Chao.hpp"
#include "Parede.hpp"
#include <iostream>
#include "Bombas.hpp"

int main(int argc, char **argv) {
	setbuf(stdout, NULL);
	sf::VideoMode video(1000, 800);
	sf::RenderWindow window(video, "King Kong");
	window.setFramerateLimit(60);

	sf::Texture background;
	background.loadFromFile("assets/background.png");
	sf::Sprite fundo;
	fundo.setTexture(background);
	fundo.setOrigin(256, 256);
	fundo.setPosition(window.getPosition().x / 2, window.getPosition().y / 2);
	fundo.setScale(3, 3);

	sf::Event evento;

	Player player(window);
	Bombas bomba(window);
	Chao chao1(500, 585, 1000), chao2(200, 300, 1000);
	Parede paredeDireita(950), paredeEsquerda(40);

	while (window.isOpen()) {

		while (window.pollEvent(evento)) {
			if (evento.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear();

		if (((player.testaColisaoChao(chao1))
				|| (player.testaColisaoChao(chao2))) == true) {
			player.setVelY(0);
		} else {
			player.setVelY(1);

		}
		player.testaColisaoParede(paredeDireita);
		player.testaColisaoParede(paredeEsquerda);
		player.move(evento);

		/*mesma logica da colisão do player com ambiente e a movimentação da bomba*/
		if (((bomba.testaColisaoChao(chao2)) || (bomba.testaColisaoChao(chao1)))== true) {

			if((bomba.testaColisaoParede(paredeDireita))||(bomba.testaColisaoParede(paredeEsquerda))== true){
				bomba.setVel(-bomba.getVelX(),0);
			}else{
				bomba.setVel(bomba.getVelX(),0);
			}
		} else {
			bomba.setVel(0,1);

		}


		bomba.mover();

		//Desenha
		window.draw(fundo);
		window.draw(player.getPlayer());
		window.draw(bomba.getBombaNormal());
		window.draw(paredeDireita.getParede());
		window.draw(paredeEsquerda.getParede());
		window.draw(chao2.getChao());
		window.draw(chao1.getChao());

		window.display();
	}

	return 0;
}
