/*
 * Cenario.hpp
 *
 *  Created on: 23 de ago. de 2024
 *      Author: Rafael
 */

#ifndef CENARIO_HPP_
#define CENARIO_HPP_
#include <vector>
#include "Player.hpp"

class Cenario{
private:
	std::vector<sf::RectangleShape> parede1;
	std::vector<sf::RectangleShape> parede2;
	std::vector<sf::RectangleShape> chao;
	sf::Vector2<float> dimensoesChao;
	sf::Vector2<float> dimensoesParedes;

public:
	Cenario();
	void desenhaCenario(sf::RenderWindow *window, Player *player);
	void desenhaEscada(sf::RenderWindow *window, float larguraColuna, float alturaLinha, int j, int i);
	void testaColisao(Player *player);
};

inline Cenario::Cenario(){
	 parede1.resize(9); // um elemento por linha
	 parede2.resize(9);
	 chao.resize(9);
}

inline void Cenario::desenhaCenario(sf::RenderWindow *window, Player *player){

	//int cenarioMatriz[9][40];

	float alturaLinha = (window->getSize().y) / 9; //determina a altura de cada linha (tamanho y da janela / num de linhas)
	float larguraColuna = (window->getSize().x) / 40; //determina a largura de cada coluna (tamanho x da janela / num de colunas)

	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 40; j++){
			if(i == 0){
				dimensoesChao.x = (window->getSize().x) - (4 * larguraColuna) * 2; //declarar isso ali em cima
				dimensoesChao.y = 5.f;
				chao[i].setSize(dimensoesChao);
				chao[i].setPosition(larguraColuna * 4, alturaLinha + alturaLinha * i); //desenha no chao da linha na 5 coluna
				chao[i].setFillColor(sf::Color::Magenta);
				window->draw(chao[i]);
			}
			else if(i == 1){
				if(j == 20 || j == 21){
					desenhaEscada(window, larguraColuna, alturaLinha, j, i);
				}
				dimensoesChao.x = (window->getSize().x) - (4 * larguraColuna) * 2;
				dimensoesChao.y = 5.f;
				chao[i].setSize(dimensoesChao);
				chao[i].setPosition(larguraColuna * 4, alturaLinha + alturaLinha * i); //desenha no chao da linha na 5 coluna
				chao[i].setFillColor(sf::Color::Magenta);
				window->draw(chao[i]);

				dimensoesParedes.x = (window->getSize().x) * 1/ 40;
				dimensoesParedes.y = alturaLinha;

				parede1[i].setSize(dimensoesParedes);
				parede1[i].setPosition(larguraColuna * 4, alturaLinha * i);
				parede1[i].setFillColor(sf::Color::Magenta);
				window->draw(parede1[i]);

				parede2[i].setSize(dimensoesParedes);
				parede2[i].setOrigin(dimensoesParedes.x, 0);
				parede2[i].setPosition(window->getSize().x - larguraColuna * 4, alturaLinha * i); //desenha a parede na 5 coluna
				parede2[i].setFillColor(sf::Color::Magenta);
				window->draw(parede2[i]);
			}
			else if(i == 2){
				if (j == 6 || j == 7 || j == 34 || j == 35) {
					desenhaEscada(window, larguraColuna, alturaLinha, j, i);
				}
				dimensoesChao.x = (window->getSize().x) - (3 * larguraColuna) * 2;
				dimensoesChao.y = 5.f;
				chao[i].setSize(dimensoesChao);
				chao[i].setPosition(larguraColuna * 3, alturaLinha + alturaLinha * i);
				chao[i].setFillColor(sf::Color::Magenta);
				window->draw(chao[i]);

				dimensoesParedes.x = (window->getSize().x) * 1/40;
				dimensoesParedes.y = alturaLinha; // declarar isso la em cima

				parede1[i].setSize(dimensoesParedes);
				parede1[i].setPosition(larguraColuna * 3, alturaLinha * i);
				parede1[i].setFillColor(sf::Color::Magenta);
				window->draw(parede1[i]);

				parede2[i].setSize(dimensoesParedes);
				parede2[i].setOrigin(dimensoesParedes.x, 0);
				parede2[i].setPosition(window->getSize().x - larguraColuna * 3, alturaLinha * i);
				parede2[i].setFillColor(sf::Color::Magenta);
				window->draw(parede2[i]);
			}
			else if(i > 2 && i < 9){
				if(i % 2 == 0){
					if (j == 4 || j == 5 || j == 36 || j == 37) {
						desenhaEscada(window, larguraColuna, alturaLinha, j, i);
					}
				}
				if(i % 2 == 1){
					if (j == 20 || j == 21) {
						desenhaEscada(window, larguraColuna, alturaLinha, j, i);
					}
				}
				dimensoesChao.x = (window->getSize().x) - (2 * larguraColuna) * 2;
				dimensoesChao.y = 5.f;
				chao[i].setSize(dimensoesChao);
				chao[i].setPosition(larguraColuna * 2, alturaLinha + alturaLinha * i);
				chao[i].setFillColor(sf::Color::Magenta);
				window->draw(chao[i]);

				dimensoesParedes.x = (window->getSize().x) * 1/ 40;
				dimensoesParedes.y = alturaLinha; // declarar isso la em cima

				parede1[i].setSize(dimensoesParedes);
				parede1[i].setPosition(larguraColuna * 2, alturaLinha * i);
				parede1[i].setFillColor(sf::Color::Magenta);
				window->draw(parede1[i]);

				parede2[i].setSize(dimensoesParedes);
				parede2[i].setOrigin(dimensoesParedes.x, 0);
				parede2[i].setPosition(window->getSize().x - larguraColuna * 2, alturaLinha * i);
				parede2[i].setFillColor(sf::Color::Magenta);
				window->draw(parede2[i]);
			}
			//testaColisao(player);
		}
	}
}

inline void Cenario::desenhaEscada(sf::RenderWindow *window, float larguraColuna, float alturaLinha, int j, int i){ //int j para desenhar exatamente na chunk

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

inline void Cenario::testaColisao(Player *player){

	std::vector<sf::FloatRect> hitboxChao;
	std::vector<sf::FloatRect> hitboxParede1;
	std::vector<sf::FloatRect> hitboxParede2;
	sf::FloatRect hitboxPlayer = player->playerBounds();
	for(int i = 0; i < 9; i++){
		hitboxChao[i] = chao[i].getGlobalBounds();
		hitboxParede1[i] = parede1[i].getGlobalBounds();
		hitboxParede2[i] = parede2[i].getGlobalBounds();
	}

	if (hitboxPlayer.intersects(hitboxChao[8])){
		player->setVelY(0);
		player->moverY();
	}
	else {
		player->setVelY(1);
	}
	if (hitboxPlayer.intersects(hitboxParede1[8])) {
		player->getPlayer().move(-(player->getVelX()), 0);
	}
	if (hitboxPlayer.intersects(hitboxParede2[8])) {
		player->getPlayer().move(-(player->getVelX()), 0);
	}
}

#endif /* CENARIO_HPP_ */
