#ifndef CENARIO_HPP_
#define CENARIO_HPP_
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Player.hpp"
#include "Escada.hpp"
#include "Chao.hpp"
#include "Parede.hpp"
#include "Bomba.hpp"

class Cenario {
private:
	//Atributos
	std::vector<Chao> chao;
	std::vector<Chao> buraco;
	std::vector<Parede> paredes;
	std::vector<Escada> escada;

	sf::Texture kongTexture;
	//fazer tudo isso em uma outra funcao para nao precisar declarar dnv quando colocar ele la embaixo no mid game
	sf::Sprite kong;
	Player &player;
	float alturaLinha, larguraColuna; //determina a altura de cada linha (tamanho y da janela / num de linhas)

public:
	//Declaracao das funcoes
	Cenario(Player &player, sf::RenderWindow *window);

	void desenhaCenario(sf::RenderWindow *window, Bomba &bomba);
	bool playerTestaColisao(int *playerBateuNaParede, int *PlayerBateuNaEscada,
			int *playerCaiuNoBuraco, int i);
	bool bombaTestaColisao(Bomba &bomba, int *bombaBateuNaParede,
			int *BombaBateuNaEscada, int i);
	void playerUpdate(bool playerBateuNoChao, int playerBateuNaParede,
			int playerBateuNaEscada, int playerCaiuNoBuraco);
	void bombaUpdate(Bomba &bomba, bool bombaBateuNoChao,
			int bombaBateuNaParede, int bombaBateuNaEscada);
	bool iniciarKong(sf::RenderWindow *window);
	void setaAndarBomba(Bomba &bomba);
	void setPlayerLayer();
	//---------------------
};

Cenario::Cenario(Player &player, sf::RenderWindow *window) :
		player(player) {
	alturaLinha = (window->getSize().y) / 10.0f; //determina a altura de cada linha (tamanho y da janela / num de linhas)
	larguraColuna = (window->getSize().x) / 40.0f; //determina a largura de cada coluna (tamanho x da janela / num de colunas)

	chao.resize(10); //Se isso nao acontecer o jogo crasha
	buraco.resize(10); //queria que fosse 6....
	paredes.resize(16); // Um elemento por linha
	escada.resize(10);

	for (int i = 0; i < 10; i++) {
		chao[i].iniciarChao(larguraColuna, alturaLinha, i);
	}

	for (int i = 0; i < 10; i++) {
		buraco[i].iniciarBuraco(larguraColuna, alturaLinha, i);
	}

	for (int i = 0; i < 16; i++) { //8 linhas com 2 paredes = 16 paredes no total
		paredes[i].iniciarParede(larguraColuna, alturaLinha, i, window);
	}

	for (int i = 0; i < 10; i++) { //8 linhas com 2 paredes = 16 paredes no total
		escada[i].iniciarEscada(larguraColuna, alturaLinha);
	}

	kongTexture.loadFromFile("assets/donkey.png");
	kong.setTexture(kongTexture);
	kong.setOrigin(0, 28); //seta a posi  o no p  dele
	kong.setPosition(larguraColuna * 7, alturaLinha * 9);
	kong.setScale(2.5, 2.5);
	//iniciarKong(window);
}

void Cenario::desenhaCenario(sf::RenderWindow *window, Bomba &bomba) {
	bool playerBateuNoChao, bombaBateuNoChao;
	playerBateuNoChao = bombaBateuNoChao = false;
	int playerCaiuNoBuraco, playerBateuNaParede, playerBateuNaEscada;
	playerCaiuNoBuraco = playerBateuNaParede = playerBateuNaEscada = 0;
	//falta bombaCaiuNoBuraco
	int bombaBateuNaParede, bombaBateuNaEscada;
	bombaBateuNaParede = bombaBateuNaEscada = 0;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 40; j++) {
			if (i == 0) {
				chao[i].drawChao(window);
			} else if (i == 1) {
				if (j == 20) {
					escada[i].draw(window, larguraColuna, alturaLinha, i, j);
				}
				chao[i].drawChao(window);
				paredes[i].draw(window);
			} else if (i == 2) {
				if (j == 6 || j == 34) {
					escada[i].draw(window, larguraColuna, alturaLinha, i, j);
				}

				chao[i].drawChao(window);
				buraco[i].drawBuraco(window);
				paredes[i].draw(window);
			} else if (i > 2 && i < 9) {
				if (i % 2 == 0) {
					if (j == 4 || j == 36) {
						escada[i].draw(window, larguraColuna, alturaLinha, i,
								j);
					}
				}
				if (i % 2 == 1) {
					if (j == 20) {
						escada[i].draw(window, larguraColuna, alturaLinha, i,
								j);
					}
				}
				chao[i].drawChao(window);
				paredes[i].draw(window);

				if (i == 4 || i == 6) {
					buraco[i].drawBuraco(window);
				}
			}

			playerBateuNoChao += playerTestaColisao(&playerBateuNaParede,
					&playerBateuNaEscada, &playerCaiuNoBuraco, i);
			bombaBateuNoChao += bombaTestaColisao(bomba, &bombaBateuNaParede,
					&bombaBateuNaEscada, i);
		} //for j
	} //for i

	playerUpdate(playerBateuNoChao, playerBateuNaParede, playerBateuNaEscada,
			playerCaiuNoBuraco);
	bombaUpdate(bomba, bombaBateuNoChao, bombaBateuNaParede,
			bombaBateuNaEscada);

} //fim func

bool Cenario::playerTestaColisao(int *playerBateuNaParede,
		int *PlayerBateuNaEscada, int *playerCaiuNoBuraco, int i) {

	int bateuNoChao = 0;
	sf::FloatRect hitboxChao, hitboxBuraco1, hitboxBuraco2, hitboxParede1,
			hitboxParede2, hitboxEscada1, hitboxEscada2, hitboxPlayer;
	hitboxPlayer = player.bounds();

	hitboxChao = chao[i].getChao().getGlobalBounds();
	hitboxBuraco1 = buraco[i].getBuraco1().getGlobalBounds();
	hitboxBuraco2 = buraco[i].getBuraco2().getGlobalBounds();
	hitboxParede1 = paredes[i].getParede1().getGlobalBounds();
	hitboxParede2 = paredes[i].getParede2().getGlobalBounds();
	hitboxEscada1 = escada[i].getEscada1().getGlobalBounds();
	hitboxEscada2 = escada[i].getEscada2().getGlobalBounds();

	if (hitboxPlayer.intersects(hitboxChao)) {
		bateuNoChao = 1;
	} else {
		bateuNoChao = 0;
	}

	if (hitboxPlayer.intersects(hitboxParede1)
			|| hitboxPlayer.intersects(hitboxParede2)) {
		*playerBateuNaParede = 1;
	}
	if (hitboxPlayer.intersects(hitboxEscada1)
			|| hitboxPlayer.intersects(hitboxEscada2)) {
		*PlayerBateuNaEscada = 1;
	}
	if (hitboxPlayer.intersects(hitboxBuraco1)
			|| hitboxPlayer.intersects(hitboxBuraco2)) {
		*playerCaiuNoBuraco = 1;
	}

	return bateuNoChao;
}

bool Cenario::bombaTestaColisao(Bomba &bomba, int *bombaBateuNaParede,
		int *BombaBateuNaEscada, int i) {
	int bateuNoChao = 0;
	sf::FloatRect hitboxChao;
	sf::FloatRect hitboxParede1;
	sf::FloatRect hitboxParede2;
	sf::FloatRect hitboxEscada1;
	sf::FloatRect hitboxEscada2;
	//float meio1 = 0, meio2 = 0;
	sf::FloatRect hitboxBomba = bomba.getBombaNormalBounds();

	hitboxChao = chao[i].getChao().getGlobalBounds();
	hitboxParede1 = paredes[i].getParede1().getGlobalBounds();
	hitboxParede2 = paredes[i].getParede2().getGlobalBounds();
	hitboxEscada1 = escada[i].getEscada1().getGlobalBounds();
	hitboxEscada2 = escada[i].getEscada2().getGlobalBounds();
	/*meio1 = escada[i].meioEscada1();
	 meio2 = escada[i].meioEscada2();*/
	hitboxEscada1.height = hitboxEscada1.height - 30;
	hitboxEscada2.height = hitboxEscada2.height - 30;

	if (hitboxBomba.intersects(hitboxChao)) {
		bateuNoChao = 1;
	}

	if (hitboxBomba.intersects(hitboxParede1)) {
		*bombaBateuNaParede = 1;
	}
	if (hitboxBomba.intersects(hitboxParede2)) {
		*bombaBateuNaParede = 1;

	}

	/*if (bomba.getVelX() > 0) {
	 meio1 += escada[i].getEscada1().getPosition().x;
	 hitboxEscada1.width += meio1;
	 meio2 += escada[i].getEscada2().getPosition().x;
	 hitboxEscada2.width += meio2;
	 } else {
	 meio1 -= escada[i].getEscada1().getPosition().x;
	 hitboxEscada1.width -= meio1;
	 meio2 += escada[i].getEscada2().getPosition().x;
	 hitboxEscada2.width += meio2;
	 }

	 if (hitboxBomba.intersects(hitboxEscada1)) {
	 if ((bomba.getBombaNormal().getPosition().x <= meio1 || bomba.getBombaNormal().getPosition().x > meio1)) {
	 *BombaBateuNaEscada = 1;
	 }
	 }
	 if (hitboxBomba.intersects(hitboxEscada2)) {
	 if (bomba.getBombaNormal().getPosition().x <= meio2 || bomba.getBombaNormal().getPosition().x > meio2) {
	 *BombaBateuNaEscada = 1;
	 }
	 }*/

	return bateuNoChao;
}

void Cenario::playerUpdate(bool playerBateuNoChao, int playerBateuNaParede,
		int playerBateuNaEscada, int playerCaiuNoBuraco) {
	if (playerBateuNoChao > 0) {
		player.setCaiu(false);
	} else {
		player.setCaiu(true);
	}

	if (playerCaiuNoBuraco > 0) {
		player.setVelY(5);
		player.GameOver(alturaLinha);
	} else {
		player.setVelY(0);
	}

	if (playerBateuNaParede > 0) {
		player.setPodeMover(0);
	} else {
		player.setPodeMover(1);
	}

	if (playerBateuNaEscada > 0) {
		player.setPodeSubir(1);
	} else {
		player.setPodeSubir(0);
	}
}

void Cenario::bombaUpdate(Bomba &bomba, bool bombaBateuNoChao,
		int bombaBateuNaParede, int bombaBateuNaEscada) {
	if (bombaBateuNoChao == true) {
		bomba.setPodeMover(1);
	} else {
		bomba.setPodeMover(0);
	}
	if (bombaBateuNaParede > 0) {
		bomba.inverteVelX();
	}
	if (bombaBateuNaEscada > 0) {
		bomba.setPodeDescer(1);
		bomba.DescerEscada();
	} else {
		bomba.setPodeDescer(0);

	}
}

/*bool Cenario::iniciarKong(sf::RenderWindow *window) {

 int velX = larguraColuna / 10.0;
 int velY = -alturaLinha / 25.0;

 if (kong.getPosition().x <= larguraColuna * 7) {
 velX = -velX;
 } else if (kong.getPosition().x >= larguraColuna * 9) {
 //Bug ta nesse else if
 velX = -velX;
 int y = kong.getPosition().y;
 int x = kong.getPosition().x;
 kong.setPosition(x - velX, y);
 }

 kong.move(velX, velY);

 window->draw(kong);

 return true;
 }*/

void Cenario::setaAndarBomba(Bomba &bomba) {
	float altura, largura;
	altura = (alturaLinha * 2) - 13;
	largura = 7 * larguraColuna - 13;
	bomba.setPosXPosY(largura, altura);
}

void Cenario::setPlayerLayer() {
	float altura, largura;
	altura = (alturaLinha * 5) - 16;
	largura = 20 * larguraColuna - 16;
	player.setPosXPosY(largura, altura);
}

#endif /* CENARIO_HPP_ */
