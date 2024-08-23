#include <SFMl\Graphics.hpp>
#include "Player.hpp"
#include "Chao.hpp"
#include "Parede.hpp"
#include <iostream>

int main(int argc, char **argv) {
	sf::VideoMode video(720, 480);
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
	Chao chao;
	Parede paredeDireita(650), paredeEsquerda(70);

	while (window.isOpen()) {

		while (window.pollEvent(evento)) {
			if (evento.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear();

		//Move os objetos
		/*parede.isColliding(&player);
		chao.isColliding(&player);*/

		player.testaColisaoChao(chao);
		player.testaColisaoParede(paredeDireita);
		player.testaColisaoParede(paredeEsquerda);
		player.move(evento);

		//Desenha
		window.draw(fundo);
		window.draw(player.getPlayer());
		window.draw(paredeDireita.getParede());
		window.draw(paredeEsquerda.getParede());
		window.draw(chao.getChao());

		window.display();
	}

	return 0;
}
