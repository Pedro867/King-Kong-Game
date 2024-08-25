/*
 * Cenario.hpp
 *
 *  Created on: 23 de ago. de 2024
 *      Author: Rafael
 */

#ifndef CENARIO_HPP_
#define CENARIO_HPP_
#include <iostream>
#include <vector>
#include "Player.hpp"

class Cenario {
private:
	sf::RectangleShape parede1;
	sf::RectangleShape parede2;
	sf::RectangleShape chao;
	sf::Vector2<float> dimensoesChao;
	sf::Vector2<float> dimensoesParedes;
	Player &player;

public:
	//Declaracao das funcoes
	Cenario(Player &player);
	void desenhaCenario(sf::RenderWindow *window);
	void desenhaEscada(sf::RenderWindow *window, float larguraColuna,
			float alturaLinha, int j, int i);
	bool testaColisao(int *bateuNaParede);
	//---------------------
};

inline Cenario::Cenario(Player &player) :
		player(player) {
}

inline void Cenario::desenhaCenario(sf::RenderWindow *window) {

	//int cenarioMatriz[9][40];

	float alturaLinha = (window->getSize().y) / 9; //determina a altura de cada linha (tamanho y da janela / num de linhas)
	float larguraColuna = (window->getSize().x) / 40; //determina a largura de cada coluna (tamanho x da janela / num de colunas)

	int bateuNoChao = 0;
	int bateuNaParede = 0;

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 40; j++) {
			if (i == 0) {
				dimensoesChao.x = (window->getSize().x)
						- (4 * larguraColuna) * 2; //declarar isso ali em cima
				dimensoesChao.y = 5.f;
				chao.setSize(dimensoesChao);
				chao.setPosition(larguraColuna * 4,
						alturaLinha + alturaLinha * i); //desenha no chao da linha na 5 coluna
				chao.setFillColor(sf::Color::Magenta);
				window->draw(chao);
			} else if (i == 1) {
				if (j == 20 || j == 21) {
					desenhaEscada(window, larguraColuna, alturaLinha, j, i);
				}
				dimensoesChao.x = (window->getSize().x)
						- (4 * larguraColuna) * 2;
				dimensoesChao.y = 5.f;
				chao.setSize(dimensoesChao);
				chao.setPosition(larguraColuna * 4,
						alturaLinha + alturaLinha * i); //desenha no chao da linha na 5 coluna
				chao.setFillColor(sf::Color::Magenta);
				window->draw(chao);

				dimensoesParedes.x = (window->getSize().x) * 1 / 40;
				dimensoesParedes.y = alturaLinha;

				parede1.setSize(dimensoesParedes);
				parede1.setPosition(larguraColuna * 4, alturaLinha * i);
				parede1.setFillColor(sf::Color::Magenta);
				window->draw(parede1);

				parede2.setSize(dimensoesParedes);
				parede2.setOrigin(dimensoesParedes.x, 0);
				parede2.setPosition(window->getSize().x - larguraColuna * 4,
						alturaLinha * i); //desenha a parede na 5 coluna
				parede2.setFillColor(sf::Color::Magenta);
				window->draw(parede2);
			} else if (i == 2) {
				if (j == 6 || j == 7 || j == 34 || j == 35) {
					desenhaEscada(window, larguraColuna, alturaLinha, j, i);
				}
				dimensoesChao.x = (window->getSize().x)
						- (3 * larguraColuna) * 2;
				dimensoesChao.y = 5.f;
				chao.setSize(dimensoesChao);
				chao.setPosition(larguraColuna * 3,
						alturaLinha + alturaLinha * i);
				chao.setFillColor(sf::Color::Magenta);
				window->draw(chao);

				dimensoesParedes.x = (window->getSize().x) * 1 / 40;
				dimensoesParedes.y = alturaLinha; // declarar isso la em cima

				parede1.setSize(dimensoesParedes);
				parede1.setPosition(larguraColuna * 3, alturaLinha * i);
				parede1.setFillColor(sf::Color::Magenta);
				window->draw(parede1);

				parede2.setSize(dimensoesParedes);
				parede2.setOrigin(dimensoesParedes.x, 0);
				parede2.setPosition(window->getSize().x - larguraColuna * 3,
						alturaLinha * i);
				parede2.setFillColor(sf::Color::Magenta);
				window->draw(parede2);
			} else if (i > 2 && i < 9) {
				if (i % 2 == 0) {
					if (j == 4 || j == 5 || j == 36 || j == 37) {
						desenhaEscada(window, larguraColuna, alturaLinha, j, i);
					}
				}
				if (i % 2 == 1) {
					if (j == 20 || j == 21) {
						desenhaEscada(window, larguraColuna, alturaLinha, j, i);
					}
				}
				dimensoesChao.x = (window->getSize().x)
						- (2 * larguraColuna) * 2;
				dimensoesChao.y = 5.f;
				chao.setSize(dimensoesChao);
				chao.setPosition(larguraColuna * 2,
						alturaLinha + alturaLinha * i);
				chao.setFillColor(sf::Color::Magenta);
				window->draw(chao);

				dimensoesParedes.x = (window->getSize().x) * 1 / 40;
				dimensoesParedes.y = alturaLinha; // declarar isso la em cima

				parede1.setSize(dimensoesParedes);
				parede1.setPosition(larguraColuna * 2, alturaLinha * i);
				parede1.setFillColor(sf::Color::Magenta);
				window->draw(parede1);

				parede2.setSize(dimensoesParedes);
				parede2.setOrigin(dimensoesParedes.x, 0);
				parede2.setPosition(window->getSize().x - larguraColuna * 2,
						alturaLinha * i);
				parede2.setFillColor(sf::Color::Magenta);
				window->draw(parede2);
			}
			bateuNoChao += testaColisao(&bateuNaParede);
		} //for j
	} //for i
	  //logica: se ele bateu em algum chao, bateuNoChao>0
	  //entao ele zera a velocidade
	if (bateuNoChao > 0) {
		player.setVelY(0);
	} else {
		player.setVelY(5);
	}

	if(bateuNaParede > 0){
		player.setPodeMover(0);
	}else{
		player.setPodeMover(1);
	}
} //fim func

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

inline bool Cenario::testaColisao(int *bateuNaParede) {

	int bateuNoChao = 0;
	sf::FloatRect hitboxChao;
	sf::FloatRect hitboxParede1;
	sf::FloatRect hitboxParede2;
	sf::FloatRect hitboxPlayer = player.playerBounds();

	hitboxChao = chao.getGlobalBounds();
	hitboxParede1 = parede1.getGlobalBounds();
	hitboxParede2 = parede2.getGlobalBounds();

	if (hitboxPlayer.intersects(hitboxChao)) {
		bateuNoChao = 1;
	}

	if (hitboxPlayer.intersects(hitboxParede1)) {
		*bateuNaParede = 1;
	}
	if (hitboxPlayer.intersects(hitboxParede2)) {
		*bateuNaParede = 1;
	}

	return bateuNoChao;
}

#endif /* CENARIO_HPP_ */
