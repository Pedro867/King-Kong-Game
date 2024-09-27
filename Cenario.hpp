#ifndef CENARIO_HPP_
#define CENARIO_HPP_
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>

#include "Player.hpp"
#include "Escada.hpp"
#include "Chao.hpp"
#include "Buraco.hpp"
#include "Parede.hpp"
#include "Bomba.hpp"
#include "Kong.hpp"

class Cenario {
private:
	//Atributos
	std::vector<Chao> chao;
	std::vector<Buraco> buraco;
	std::vector<Parede> paredes;
	std::vector<Escada> escada;

	//fazer tudo isso em uma outra funcao para nao precisar declarar dnv quando colocar ele la embaixo no mid game
	bool iniciouKong;
	Player &player;
	Kong kong;
	float alturaLinha, larguraColuna; //determina a altura de cada linha (tamanho y da janela / num de linhas)

public:
	//Declaracao das funcoes
	Cenario(Player &player, sf::RenderWindow *window);

	void desenhaCenario(sf::RenderWindow *window, Bomba &bomba);
	void desenhaAndar1ao6(int i, sf::RenderWindow *window, Chao *chao,
			Parede *paredes, Escada *escada, Buraco *buraco);
	void desenhaAndar7(int i, sf::RenderWindow *window, Chao *chao,
			Parede *paredes, Escada *escada, Buraco *buraco);
	void desenhaAndar8(int i, sf::RenderWindow *window, Chao *chao,
			Parede *paredes, Escada *escada, Buraco *buraco);
	void desenhaAndar9(sf::RenderWindow *window, Chao *chao);

	bool playerTestaColisao(int *playerBateuNaParede, int *PlayerBateuNaEscada,
			int *playerCaiuNoBuraco, int i);
	bool bombaTestaColisao(Bomba &bomba, int *bombaBateuNaParede,
			int *BombaBateuNaEscada, int i, int tipoDesce);
	void playerUpdate(bool playerBateuNoChao, int playerBateuNaParede,
			int playerBateuNaEscada, int playerCaiuNoBuraco);
	void bombaUpdate(Bomba &bomba, bool bombaBateuNoChao,
			int bombaBateuNaParede, int bombaBateuNaEscada);
	bool iniciarKong(sf::RenderWindow *window);
	void setaAndarBomba(Bomba &bomba);
	void setPlayerLayer();
	bool getIniciouKong();
	int sorteadorDeNumeros(int andar);
	//---------------------
};

Cenario::Cenario(Player &player, sf::RenderWindow *window) :
		player(player) {
	alturaLinha = (window->getSize().y) / 10.0f; //determina a altura de cada linha (tamanho y da janela / num de linhas)
	larguraColuna = (window->getSize().x) / 40.0f; //determina a largura de cada coluna (tamanho x da janela / num de colunas)

	float escalaKong = window->getSize().y / 280.f; //escala kong responsiva
	kong.IniciaKong(larguraColuna, alturaLinha, escalaKong);
	iniciouKong = false;

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
		escada[i].iniciarEscada(larguraColuna, alturaLinha, i);
	}
}

void Cenario::desenhaCenario(sf::RenderWindow *window, Bomba &bomba) {
	bool playerBateuNoChao, bombaBateuNoChao;
	playerBateuNoChao = bombaBateuNoChao = false;
	int playerCaiuNoBuraco, playerBateuNaParede, playerBateuNaEscada;
	playerCaiuNoBuraco = playerBateuNaParede = playerBateuNaEscada = 0;
	//falta bombaCaiuNoBuraco
	int bombaBateuNaParede, bombaBateuNaEscada;
	bombaBateuNaParede = bombaBateuNaEscada = 0;
	//mapa [10][40]

	for (int i = 0; i < 10; i++) {
		if (i > 0 && i < 7) {
			desenhaAndar1ao6(i, window, &chao[i], &paredes[i], &escada[i],
					&buraco[i]);
		} else if (i == 7) {
			desenhaAndar7(i, window, &chao[i], &paredes[i], &escada[i],
					&buraco[i]);
		} else if (i == 8) {
			desenhaAndar8(i, window, &chao[i], &paredes[i], &escada[i],
					&buraco[i]);
		} else if (i == 9) {
			desenhaAndar9(window, &chao[i]);
		}
		//iniciouKong = kong.iniciarKong(window, larguraColuna, alturaLinha);

		if (iniciouKong == true) {
			int tipoDesce = sorteadorDeNumeros(i); //sorteia escada pra bomba
			playerBateuNoChao += playerTestaColisao(&playerBateuNaParede,
					&playerBateuNaEscada, &playerCaiuNoBuraco, i);
			bombaBateuNoChao += bombaTestaColisao(bomba, &bombaBateuNaParede,
					&bombaBateuNaEscada, i, tipoDesce);
		}
	} //for i

	if (iniciouKong == false) {
		iniciouKong = kong.AnimacaoInicialKong(larguraColuna, alturaLinha);
		window->draw(kong.getKong());
	}

	if (iniciouKong == true) {
		playerUpdate(playerBateuNoChao, playerBateuNaParede,
				playerBateuNaEscada, playerCaiuNoBuraco);
		bombaUpdate(bomba, bombaBateuNoChao, bombaBateuNaParede,
				bombaBateuNaEscada);
		kong.AnimacaoKong();
		//desenha elementos
		window->draw(player.getPlayer());
		window->draw(bomba.getBombaNormal());
		window->draw(kong.getKong());
	}
} //fim func

void Cenario::desenhaAndar1ao6(int i, sf::RenderWindow *window, Chao *chao,
		Parede *paredes, Escada *escada, Buraco *buraco) {
	for (int j = 0; j < 40; j++) {
		if (i % 2 == 1) {
			if (j == 4 || j == 36) {
				escada->draw(window);
			}
		}
		if (i % 2 == 0) {
			if (j == 20) {
				escada->draw(window);
			}
		}
		chao->drawChao(window);
		paredes->draw(window);
		buraco->drawBuraco(window); //s� vai desenhar nas linhas 3 e 5
	}
}

void Cenario::desenhaAndar7(int i, sf::RenderWindow *window, Chao *chao,
		Parede *paredes, Escada *escada, Buraco *buraco) {
	for (int j = 0; j < 40; j++) {
		if (j == 5 || j == 35) {
			escada->draw(window);
		}
		chao->drawChao(window);
		paredes->draw(window);
		buraco->drawBuraco(window);
	}
}

void Cenario::desenhaAndar8(int i, sf::RenderWindow *window, Chao *chao,
		Parede *paredes, Escada *escada, Buraco *buraco) {
	for (int j = 0; j < 40; j++) {
		if (j == 20) {
			escada->draw(window);
		}

		chao->drawChao(window);
		buraco->drawBuraco(window);
		paredes->draw(window);
	}
}

void Cenario::desenhaAndar9(sf::RenderWindow *window, Chao *chao) {
	chao->drawChao(window);
}

bool Cenario::playerTestaColisao(int *playerBateuNaParede,
		int *PlayerBateuNaEscada, int *playerCaiuNoBuraco, int i) {

	int bateuNoChao = 0;
	sf::FloatRect hitboxChao1, hitboxChao2, hitboxChao3, hitboxBuraco1,
			hitboxBuraco2, hitboxParede1, hitboxParede2, hitboxEscada1,
			hitboxEscada2, hitboxPlayer;
	hitboxPlayer = player.bounds();

	hitboxChao1 = chao[i].getChao1().getGlobalBounds();
	hitboxChao2 = chao[i].getChao2().getGlobalBounds();
	hitboxChao3 = chao[i].getChao3().getGlobalBounds();
	hitboxBuraco1 = buraco[i].getBuraco1().getGlobalBounds();
	hitboxBuraco2 = buraco[i].getBuraco2().getGlobalBounds();
	hitboxParede1 = paredes[i].getParede1().getGlobalBounds();
	hitboxParede2 = paredes[i].getParede2().getGlobalBounds();
	hitboxEscada1 = escada[i].getEscada1().getGlobalBounds();
	hitboxEscada2 = escada[i].getEscada2().getGlobalBounds();

	if (hitboxPlayer.intersects(hitboxChao1)
			|| hitboxPlayer.intersects(hitboxChao2)
			|| hitboxPlayer.intersects(hitboxChao3)) {
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
		int *BombaBateuNaEscada, int i, int tipoDesce) {
	int bateuNoChao = 0;
	srand(time(NULL));

	sf::FloatRect hitboxChao1;
	sf::FloatRect hitboxChao2;
	sf::FloatRect hitboxChao3;
	sf::FloatRect hitboxParede1;
	sf::FloatRect hitboxParede2;
	sf::FloatRect Parede8;
	sf::FloatRect hitboxEscada1;
	sf::FloatRect hitboxEscada2;
	sf::FloatRect meio1, meio2;
	sf::FloatRect hitboxBomba = bomba.getBombaNormalBounds();

	hitboxChao1 = chao[i].getChao1().getGlobalBounds();
	hitboxChao2 = chao[i].getChao2().getGlobalBounds();
	hitboxChao3 = chao[i].getChao3().getGlobalBounds();
	hitboxParede1 = paredes[i].getParede1().getGlobalBounds();
	hitboxParede2 = paredes[i].getParede2().getGlobalBounds();
	hitboxEscada1 = escada[i].getEscada1().getGlobalBounds();
	hitboxEscada2 = escada[i].getEscada2().getGlobalBounds();
	Parede8 = paredes[8].getParede2().getGlobalBounds();
//	meio1 = escada[i].meioEscada1();
//	meio2 = escada[i].meioEscada2();
	hitboxEscada1.height = hitboxEscada1.height - 30;
	hitboxEscada2.height = hitboxEscada2.height - 30;

	if (hitboxBomba.intersects(hitboxChao1)
			|| hitboxBomba.intersects(hitboxChao2)
			|| hitboxBomba.intersects(hitboxChao3)) {
		bateuNoChao = 1;
	}

	if (hitboxBomba.intersects(hitboxParede1)) {
		*bombaBateuNaParede = 1;
	}
	if (hitboxBomba.intersects(hitboxParede2)) {
		*bombaBateuNaParede = 1;
	}

	if (bomba.getVelX() > 0) {
		hitboxEscada1.left = hitboxEscada1.left + hitboxEscada1.width / 2;
		hitboxBomba.left = hitboxBomba.left - hitboxBomba.width / 2;
		hitboxEscada2.left = hitboxEscada2.left + hitboxEscada2.width / 2;

	} else {
		hitboxEscada1.left = hitboxEscada1.left - hitboxEscada1.width / 2;
		hitboxBomba.left = hitboxBomba.left + hitboxBomba.width / 2;
		hitboxEscada2.left = hitboxEscada2.left - hitboxEscada2.width / 2;
	}

	//Parte da bomba descer escada
	int random;
	if (tipoDesce == 1) { //duas escadas
		random = rand() % 2;
	}
	if (tipoDesce == 2) { //uma escada e dois buracos
		random = rand() % 3;
	}
	if (tipoDesce == 0) { //nem um nem outro
		random = 8; //valor aleatório kkk
	}
	cout << random;
	if (hitboxBomba.intersects(hitboxEscada1)) {
		if (random == 0) {
			*BombaBateuNaEscada = 1;
		}
	}
	if (hitboxBomba.intersects(hitboxEscada2)) {
		if (tipoDesce == 1) {
			if (random == 1) {
				*BombaBateuNaEscada = 1;
			}
		}
	}

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
		//player.setVelY(1);
		player.GameOver(alturaLinha); //isso depois
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
	} else {
		bomba.setPodeDescer(0);
	}
}

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

bool Cenario::getIniciouKong() {
	return iniciouKong;
}

int Cenario::sorteadorDeNumeros(int andar) {
	if (andar > 0 && andar < 9) {
		if (andar % 2 == 0) {
			return 1; //uma escada e dois buracos
		}
		if (andar % 2 == 1) {
			return 2; //duas escadas
		}
	}
	return 0;

}

#endif /* CENARIO_HPP_ */
