/*
 * Cenario.hpp
 *
 *  Created on: 23 de ago. de 2024
 *      Author: Rafael
 */

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
#include "Chao.hpp"
#include "Parede.hpp"

class Cenario {
private:

	std::vector<Chao> chao;
	std::vector<Chao> buraco;
	std::vector<Parede> paredes;

	sf::Texture kongTexture;
	//fazer tudo isso em uma outra funcao para nao precisar declarar dnv quando colocar ele la embaixo no mid game
	sf::Sprite kong;
	Player &player;
	float alturaLinha; //determina a altura de cada linha (tamanho y da janela / num de linhas)
	float larguraColuna;


public:
	//Declaracao das funcoes
	Cenario(Player &player, sf::RenderWindow *window);

	void desenhaCenario(sf::RenderWindow *window);
	void desenhaEscada(sf::RenderWindow *window, float larguraColuna, float alturaLinha, int j, int i);
	void desenhaChao(sf::RenderWindow *window);
	void desenhaParede(sf::RenderWindow *window);

	bool testaColisao(int *bateuNaParede);
	bool iniciarKong(sf::RenderWindow *window);
	//---------------------
};

inline Cenario::Cenario(Player &player, sf::RenderWindow *window) : player(player) {
	alturaLinha = (window->getSize().y) / 10.0f; //determina a altura de cada linha (tamanho y da janela / num de linhas)
	larguraColuna = (window->getSize().x) / 40.0f; //determina a largura de cada coluna (tamanho x da janela / num de colunas)

	chao.resize(10); //Se isso nao acontecer o jogo crasha
	buraco.resize(10); //queria que fosse 6....
	paredes.resize(16); // Um elemento por linha

	for(int i = 0; i < 10; i++){
		chao[i].iniciarChao(larguraColuna,alturaLinha, i);
	}

	for (int i = 0; i < 10; i++) {
		buraco[i].iniciarBuraco(larguraColuna, alturaLinha, i);
	}

	for(int i = 0; i < 16; i++){ //8 linhas com 2 paredes = 16 paredes no total
		paredes[i].iniciarParede(larguraColuna,alturaLinha, i, window);
	}


	kongTexture.loadFromFile("assets/donkey.png");
	kong.setTexture(kongTexture);
	kong.setOrigin(0, 28); //seta a posi��o no p� dele
	kong.setPosition(larguraColuna * 7, alturaLinha * 9);
	kong.setScale(2.5, 2.5);
}

inline void Cenario::desenhaCenario(sf::RenderWindow *window) {

	//int cenarioMatriz[10][40];

	int bateuNoChao = 0;
	int bateuNaParede = 0;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 40; j++) {
			if (i == 0) {
				chao[i].drawChao(window);
			}
			else if (i == 1) {
				if (j == 20 || j == 21) {
					desenhaEscada(window, larguraColuna, alturaLinha, j, i);
				}
				chao[i].drawChao(window);
				paredes[i].draw(window);
			}
			else if (i == 2) {
				if (j == 6 || j == 7 || j == 34 || j == 35) {
					desenhaEscada(window, larguraColuna, alturaLinha, j, i);
				}

				chao[i].drawChao(window);
				buraco[i].drawBuraco(window);
				paredes[i].draw(window);
			}
			else if (i > 2 && i < 9) {
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
				chao[i].drawChao(window);
				paredes[i].draw(window);

				if(i == 4 || i == 6){
					buraco[i].drawBuraco(window);
				}
			}

			//bateuNoChao += testaColisao(&bateuNaParede);
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

	sf::Texture texturaEscada;
	sf::Sprite escada;
	texturaEscada.loadFromFile("assets/Escada.png");
	escada.setTexture(texturaEscada);
	escada.setOrigin(8, 0);
	escada.setScale(larguraColuna / 8, alturaLinha / 8);
	escada.setPosition(j * larguraColuna, alturaLinha * i);

	window->draw(escada);
}

inline void Cenario::desenhaChao(sf::RenderWindow *window){

}

inline void Cenario::desenhaParede(sf::RenderWindow *window) {
}

/*inline bool Cenario::testaColisao(int *bateuNaParede) {

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

/*inline bool Cenario::iniciarKong(sf::RenderWindow *window){

	//kong.move(5, 5);
	//window->draw(kong);

	int velX;
	int velY = -alturaLinha / 5.0;

	if(shape.getPosition().x <= larguraColuna * 7){
		velX = larguraColuna / 5.0;
		shape.move(velX, velY);
	}
	else if(shape.getPosition().x >= larguraColuna * 9){
		velX = velX * -1;
		shape.move(velX, velY);
	}
	else{
		shape.move(velX, velY);
	}

	window->draw(shape);



	//kong.move();

	//return true;
}*/


#endif /* CENARIO_HPP_ */
