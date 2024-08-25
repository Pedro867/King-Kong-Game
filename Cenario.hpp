#ifndef CENARIO_HPP_
#define CENARIO_HPP_
#include<iostream>
#include "Player.hpp"
#include "Bomba.hpp"

class Cenario {
private:
	sf::RectangleShape parede1;
	sf::RectangleShape parede2;
	sf::RectangleShape chao;
	sf::Vector2<float> dimensoesChao;
	sf::Vector2<float> dimensoesParedes;

public:
	Cenario();
	void desenhaCenario(sf::RenderWindow *window, Player *player);
	void desenhaEscada(sf::RenderWindow *window, float larguraColuna,
			float alturaLinha, int j, int i);
	void testaColisao(Player *player);

	const sf::RectangleShape& getChao() const {
		return chao;
	}

	const sf::RectangleShape& getParede2() const {
		return parede2;
	}

	const sf::RectangleShape& getParede1() const {
		return parede1;
	}
};

inline Cenario::Cenario() { //coloquei no construtor mas pode ser em uma funcao "inicializarCenario"
	sf::Vector2<float> dimensoes(10.f, 100.f);
	parede1.setSize(dimensoes);
}

void Cenario::testaColisao(Player *player) {
	sf::FloatRect hitboxChao = chao.getGlobalBounds();
	sf::FloatRect hitboxParede1 = parede1.getGlobalBounds();
	sf::FloatRect hitboxParede2 = parede2.getGlobalBounds();
	sf::FloatRect hitboxPlayer = player->playerBounds();

	if (hitboxPlayer.intersects(hitboxChao)) {
		player->setVelY(0);
		player->moverY();
	} else {
		player->setVelY(1);
	}

	if (hitboxPlayer.intersects(hitboxParede1)) {
		player->getPlayer().move(-(player->getVelX()), 0);
	}

	if (hitboxPlayer.intersects(hitboxParede2)) {
		player->getPlayer().move(-(player->getVelX()), 0);
	}
}

inline void Cenario::desenhaCenario(sf::RenderWindow *window, Player *player) {

	//int cenarioMatriz[9][39];

	float alturaLinha = (window->getSize().y) / 9; //determina a altura de cada linha (tamanho y da janela / num de linhas)
	float larguraColuna = (window->getSize().x) / 39; //determina a largura de cada coluna (tamanho x da janela / num de colunas)

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 39; j++) {
			if (i == 0) {
				dimensoesChao.x = (window->getSize().x) * 7 / 10; //declarar isso ali em cima
				dimensoesChao.y = 5.f;
				chao.setSize(dimensoesChao);
				chao.setPosition((window->getSize().x) * 3 / 20,
						alturaLinha + alturaLinha * i); //desenha no chao da linha
				chao.setFillColor(sf::Color::Magenta);
				window->draw(chao);
			} else if (i == 1) {
				if (j == 20 || j == 21) {
					desenhaEscada(window, larguraColuna, alturaLinha, j, i);
				}
				dimensoesChao.x = (window->getSize().x) * 3 / 4;
				dimensoesChao.y = 5.f;
				chao.setSize(dimensoesChao);
				chao.setPosition((window->getSize().x) * 1 / 8,
						alturaLinha + alturaLinha * i);
				chao.setFillColor(sf::Color::Magenta);
				window->draw(chao);

				dimensoesParedes.x = (window->getSize().x) * 1 / 40;
				dimensoesParedes.y = alturaLinha;

				parede1.setSize(dimensoesParedes);
				parede1.setPosition((window->getSize().x) * 3 / 20,
						alturaLinha * i);
				parede1.setFillColor(sf::Color::Magenta);
				window->draw(parede1);

				parede2.setSize(dimensoesParedes);
				parede2.setOrigin(dimensoesParedes.x, 0);
				parede2.setPosition(window->getSize().x * 17 / 20,
						alturaLinha * i);
				parede2.setFillColor(sf::Color::Magenta);
				window->draw(parede2);
			} else if (i == 2) {
				if (j == 6 || j == 7 || j == 33 || j == 34) {
					desenhaEscada(window, larguraColuna, alturaLinha, j, i);
				}
				dimensoesChao.x = (window->getSize().x) * 31 / 40;
				dimensoesChao.y = 5.f;
				chao.setSize(dimensoesChao);
				chao.setPosition((window->getSize().x) * 1 / 8,
						alturaLinha + alturaLinha * i);
				chao.setFillColor(sf::Color::Magenta);
				window->draw(chao);

				dimensoesParedes.x = (window->getSize().x) * 1 / 40;
				dimensoesParedes.y = alturaLinha; // declarar isso la em cima

				parede1.setSize(dimensoesParedes);
				parede1.setPosition((window->getSize().x) * 1 / 8,
						alturaLinha * i);
				parede1.setFillColor(sf::Color::Magenta);
				window->draw(parede1);

				parede2.setSize(dimensoesParedes);
				parede2.setOrigin(dimensoesParedes.x, 0);
				parede2.setPosition(window->getSize().x * 7 / 8,
						alturaLinha * i);
				parede2.setFillColor(sf::Color::Magenta);
				window->draw(parede2);
			} else if (i > 2 && i < 9) {
				dimensoesChao.x = (window->getSize().x) * 4 / 5;
				dimensoesChao.y = 5.f;
				chao.setSize(dimensoesChao);
				chao.setPosition((window->getSize().x) * 1 / 10,
						alturaLinha + alturaLinha * i);
				chao.setFillColor(sf::Color::Magenta);
				window->draw(chao);

				dimensoesParedes.x = (window->getSize().x) * 1 / 40;
				dimensoesParedes.y = alturaLinha; // declarar isso la em cima

				parede1.setSize(dimensoesParedes);
				parede1.setPosition((window->getSize().x) * 1 / 10,
						alturaLinha * i);
				parede1.setFillColor(sf::Color::Magenta);
				window->draw(parede1);

				parede2.setSize(dimensoesParedes);
				parede2.setOrigin(dimensoesParedes.x, 0);
				parede2.setPosition(window->getSize().x * 9 / 10,
						alturaLinha * i);
				parede2.setFillColor(sf::Color::Magenta);
				window->draw(parede2);
			}
			testaColisao(player);
		}
	}
}

inline void Cenario::desenhaEscada(sf::RenderWindow *window,
		float larguraColuna, float alturaLinha, int j, int i) { //int j para desenhar exatamente na chunk

	/*sf::RectangleShape layer;
	 sf::Vector2<float> dimensoes(larguraColuna, 3);

	 for(int cont = 1; cont < 6; cont++){
	 layer.setSize(dimensoes);
	 layer.setFillColor(sf::Color::Magenta);
	 layer.setOrigin(larguraColuna, 3);
	 layer.setPosition(j * larguraColuna, alturaLinha + 3 * cont);
	 window->draw(layer);
	 }*/

	sf::Texture texturaEscada;
	sf::Sprite escada;
	texturaEscada.loadFromFile("assets/Escada.png");
	escada.setTexture(texturaEscada);

	escada.setOrigin(8, 0);
	escada.setScale(larguraColuna / 8, alturaLinha / 8);
	escada.setPosition(j * larguraColuna, alturaLinha * i);

	window->draw(escada);

}

#endif /* CENARIO_HPP_ */
