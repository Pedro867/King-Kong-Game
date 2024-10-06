#ifndef GAME_HPP_
#define GAME_HPP_
#include <SFML/Graphics.hpp>
#include <SFML/audio.hpp>
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
#include "Princesa.hpp"

class Game {
private:
	//Atributos
	std::vector<Chao> chao;
	std::vector<Buraco> buraco;
	std::vector<Parede> paredes;
	std::vector<Escada> escada;

	//fazer tudo isso em uma outra funcao para nao precisar declarar dnv quando colocar ele la embaixo no mid game
	bool iniciouKong;
	Player &player;
	std::vector<Bomba> bomba;
	Kong kong;
	Princesa &princesa;
	float alturaLinha, larguraColuna; //determina a altura de cada linha (tamanho y da janela / num de linhas)

	int qntAtualBombaNormal;

public:
	//Declaracao das funcoes
	Game(Player &player, Princesa &princesa, sf::RenderWindow *window);

	void desenhaCenario(sf::RenderWindow *window);
	void desenhaAndar1ao6(int i, sf::RenderWindow *window, Chao *chao,
			Parede *paredes, Escada *escada);
	void desenhaAndar7(int i, sf::RenderWindow *window, Chao *chao,
			Parede *paredes, Escada *escada);
	void desenhaAndar8(int i, sf::RenderWindow *window, Chao *chao,
			Parede *paredes, Escada *escada);
	void desenhaAndar9(sf::RenderWindow *window, Chao *chao);
	void desenhaElementos(sf::RenderWindow *window);

	void playerTestaColisao(int *playerBateuNoChao, int *playerBateuNaParede,
			int *PlayerBateuNaEscada, int *playerCaiuNoBuraco,
			int *playerBateuNaBomba, int i);
	void bombasTestaColisao(vector<int> &bombaBateuNoChao,
			vector<int> &bombaBateuNaParede, vector<int> &BombaBateuNaEscada,
			int i);
	void playerUpdate(int playerBateuNoChao, int playerBateuNaParede,
			int playerBateuNaEscada, int playerCaiuNoBuraco,
			bool playerBateuNaBomba);
	void bombaUpdate(vector<int> bombaBateuNoChao,
			vector<int> bombaBateuNaParede, vector<int> bombaBateuNaEscada);
	void deleteBombas();
	bool playerVenceu();

	bool getIniciouKong();
	int olhaAndarBomba(int cont);
	//---------------------
};

Game::Game(Player &player, Princesa &princesa, sf::RenderWindow *window) :
		player(player), princesa(princesa) {

	alturaLinha = (window->getSize().y) / 10.0f; //determina a altura de cada linha (tamanho y da janela / num de linhas)
	larguraColuna = (window->getSize().x) / 40.0f; //determina a largura de cada coluna (tamanho x da janela / num de colunas)

	float escalaKong = window->getSize().y / 280.f; //escala kong responsiva
	kong.iniciaKong(larguraColuna, alturaLinha, escalaKong);
	iniciouKong = true; //mudar para testar mais rápido

	chao.resize(10); //Se isso nao acontecer o jogo crasha
	buraco.resize(10); //queria que fosse 6....
	paredes.resize(16); // Um elemento por linha
	escada.resize(10);
	bomba.resize(10); //No max 10 bombas normais

	for (int i = 0; i < 10; i++) {
		chao[i].iniciarChao(larguraColuna, alturaLinha, i);
	}

	for (int i = 0; i < 10; i++) {
		buraco[i].iniciarBuraco(larguraColuna, alturaLinha, i);
	}

	for (int i = 0; i < 16; i++) { //8 linhas com 2 paredes = 16 paredes no total
		paredes[i].iniciarParede(larguraColuna, alturaLinha, i, window);
	}

	for (int i = 0; i < 10; i++) {
		escada[i].iniciarEscada(larguraColuna, alturaLinha, i);
	}

	for (int i = 0; i < 10; i++) {
		bomba[i].iniciarBomba(window);
	}

	player.setLayer(alturaLinha, larguraColuna);
	princesa.setLayer(alturaLinha, larguraColuna);
	bomba[0].setLayer(alturaLinha, larguraColuna);
	qntAtualBombaNormal = 1;
}

void Game::desenhaCenario(sf::RenderWindow *window) {

	int playerBateuNoChao, playerBateuNaBomba, playerCaiuNoBuraco,
			playerBateuNaParede, playerBateuNaEscada;
	playerBateuNoChao = playerBateuNaBomba = playerCaiuNoBuraco =
			playerBateuNaParede = playerBateuNaEscada = 0;

	vector<int> bombaBateuNoChao(10, 0), bombaBateuNaParede(10, 0),
			bombaBateuNaEscada(10, 0); //inicializa todos com 0
	//bombaBateuNoChao = bombaBateuNaParede = bombaBateuNaEscada = 0;
	//mapa [10][40]

	for (int i = 0; i < 10; i++) {
		if (i > 0 && i < 7) {
			desenhaAndar1ao6(i, window, &chao[i], &paredes[i], &escada[i]);
		} else if (i == 7) {
			desenhaAndar7(i, window, &chao[i], &paredes[i], &escada[i]);
		} else if (i == 8) {
			desenhaAndar8(i, window, &chao[i], &paredes[i], &escada[i]);
		} else if (i == 9) {
			desenhaAndar9(window, &chao[i]);
		}
		//iniciouKong = kong.iniciarKong(window, larguraColuna, alturaLinha);

		if (iniciouKong == true) {
			playerTestaColisao(&playerBateuNoChao, &playerBateuNaParede,
					&playerBateuNaEscada, &playerCaiuNoBuraco,
					&playerBateuNaBomba, i);
			bombasTestaColisao(bombaBateuNoChao, bombaBateuNaParede,
					bombaBateuNaEscada, i);
		}
	} //for i

	if (iniciouKong == false) {
		iniciouKong = kong.AnimacaoInicialKong(larguraColuna, alturaLinha);
		window->draw(kong.getKong());
	}

	if (iniciouKong == true) {
		playerUpdate(playerBateuNoChao, playerBateuNaParede,
				playerBateuNaEscada, playerCaiuNoBuraco, playerBateuNaBomba);
		bombaUpdate(bombaBateuNoChao, bombaBateuNaParede, bombaBateuNaEscada);

		kong.AnimacaoKong();
		princesa.animacaoPrincesa(larguraColuna);
		desenhaElementos(window);
	}
} //fim func

void Game::desenhaAndar1ao6(int i, sf::RenderWindow *window, Chao *chao,
		Parede *paredes, Escada *escada) {

	escada->draw(window);
	chao->drawChao(window);
	paredes->draw(window);
}

void Game::desenhaAndar7(int i, sf::RenderWindow *window, Chao *chao,
		Parede *paredes, Escada *escada) {

	escada->draw(window);
	chao->drawChao(window);
	paredes->draw(window);
}

void Game::desenhaAndar8(int i, sf::RenderWindow *window, Chao *chao,
		Parede *paredes, Escada *escada) {

	escada->draw(window);
	chao->drawChao(window);
	paredes->draw(window);

}

void Game::desenhaAndar9(sf::RenderWindow *window, Chao *chao) {
	chao->drawChao(window);
}

void Game::desenhaElementos(sf::RenderWindow *window) {
	window->draw(player.getPlayer());
	window->draw(kong.getKong());
	window->draw(princesa.getPrincesa());

	for (int cont = 0; cont < qntAtualBombaNormal; cont++) {
		window->draw(bomba[cont].getBombaNormal());
	}
}

void Game::playerTestaColisao(int *playerBateuNoChao, int *playerBateuNaParede,
		int *PlayerBateuNaEscada, int *playerCaiuNoBuraco,
		int *playerBateuNaBomba, int i) {

	sf::FloatRect hitboxChao1, hitboxChao2, hitboxChao3, hitboxBuraco1,
			hitboxBuraco2, hitboxParede1, hitboxParede2, hitboxEscada1,
			hitboxEscada2, hitboxPlayer, hitboxBomba;
	hitboxPlayer = player.bounds();

	hitboxChao1 = chao[i].getChao1().getGlobalBounds();
	hitboxChao2 = chao[i].getChao2().getGlobalBounds();
	hitboxChao3 = chao[i].getChao3().getGlobalBounds();
	hitboxBuraco1 = buraco[i].getBuraco1().getGlobalBounds();
	hitboxBuraco2 = buraco[i].getBuraco2().getGlobalBounds();
	hitboxParede1 = paredes[i].getParede1().getGlobalBounds();
	hitboxParede2 = paredes[i].getParede2().getGlobalBounds();
	hitboxEscada1 = escada[i].getHitbox1().getGlobalBounds();
	hitboxEscada2 = escada[i].getHitbox2().getGlobalBounds();
	hitboxChao1.width = hitboxChao1.width - 5;
	hitboxChao2.width = hitboxChao2.width - 5;
	hitboxChao3.width = hitboxChao3.width - 5;
	hitboxChao1.left = hitboxChao1.left + 3;
	hitboxChao2.left = hitboxChao2.left + 3;
	hitboxChao3.left = hitboxChao3.left + 3;
	hitboxBuraco1.left = hitboxBuraco1.left + 15;
	hitboxBuraco2.left = hitboxBuraco2.left + 15;
	hitboxBuraco1.width = hitboxBuraco1.width - 22.5;
	hitboxBuraco2.width = hitboxBuraco2.width - 22.5;

	if (hitboxPlayer.intersects(hitboxChao1)
			|| hitboxPlayer.intersects(hitboxChao2)
			|| hitboxPlayer.intersects(hitboxChao3)) {
		*playerBateuNoChao = 1;

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

	for (int cont = 0; cont < qntAtualBombaNormal; cont++) {
		hitboxBomba = bomba[cont].getBombaNormalBounds();
		hitboxBomba.top = hitboxBomba.top + 10;
		hitboxBomba.height = hitboxBomba.height - 10;
		if (hitboxPlayer.intersects(hitboxBomba)) {

			*playerBateuNaBomba = 1;

		}
	}
}

void Game::bombasTestaColisao(vector<int> &bombaBateuNoChao,
		vector<int> &bombaBateuNaParede, vector<int> &BombaBateuNaEscada,
		int i) {
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
	hitboxChao1 = chao[i].getChao1().getGlobalBounds();
	hitboxChao2 = chao[i].getChao2().getGlobalBounds();
	hitboxChao3 = chao[i].getChao3().getGlobalBounds();
	hitboxParede1 = paredes[i].getParede1().getGlobalBounds();
	hitboxParede2 = paredes[i].getParede2().getGlobalBounds();
	hitboxEscada1 = escada[i].getEscada1().getGlobalBounds();
	hitboxEscada2 = escada[i].getEscada2().getGlobalBounds();
	hitboxEscada1.height = hitboxEscada1.height - 30;
	hitboxEscada2.height = hitboxEscada2.height - 30;

	for (int cont = 0; cont < qntAtualBombaNormal; cont++) {

		sf::FloatRect hitboxBomba = bomba[cont].getBombaNormalBounds();

		if (hitboxBomba.intersects(hitboxChao1)
				|| hitboxBomba.intersects(hitboxChao2)
				|| hitboxBomba.intersects(hitboxChao3)) {
			bombaBateuNoChao[cont] = 1;
		}

		if (hitboxBomba.intersects(hitboxParede1)) {
			bombaBateuNaParede[cont] = 1;
		}
		if (hitboxBomba.intersects(hitboxParede2)) {
			bombaBateuNaParede[cont] = 1;
		}

		if (bomba[cont].getVelX() > 0) {
			hitboxEscada1.left = hitboxEscada1.left + hitboxEscada1.width / 2;
			hitboxBomba.left = hitboxBomba.left - hitboxBomba.width / 2;
			hitboxEscada2.left = hitboxEscada2.left + hitboxEscada2.width / 2;

		} else {
			hitboxEscada1.left = hitboxEscada1.left - hitboxEscada1.width / 2;
			hitboxBomba.left = hitboxBomba.left + hitboxBomba.width / 2;
			hitboxEscada2.left = hitboxEscada2.left - hitboxEscada2.width / 2;
		}

		//Parte da bomba descer escada

		//cout << random;
//		cout << "Bomba[" << 1 << "]:" << bomba[cont].Descer[bomba[cont].getLayer(alturaLinha)]
//		<< " \n";
//		if (((bomba[cont].getLayer(alturaLinha) == 2)
//				&& (bomba[cont].Descer[0] == 0))
//				|| ((bomba[cont].getLayer(alturaLinha) == 3)
//						&& (bomba[cont].Descer[1] == 1))
//				|| ((bomba[cont].getLayer(alturaLinha) == 4)
//						&& (bomba[cont].Descer[2] == 0))
//				|| ((bomba[cont].getLayer(alturaLinha) == 5)
//						&& (bomba[cont].Descer[3] == 1))
//				|| ((bomba[cont].getLayer(alturaLinha) == 6)
//						&& (bomba[cont].Descer[4] == 0))
//				|| ((bomba[cont].getLayer(alturaLinha) == 7)
//						&& (bomba[cont].Descer[5] == 1))
//				|| ((bomba[cont].getLayer(alturaLinha) == 8)
//						&& (bomba[cont].Descer[6] == 0))
//				|| ((bomba[cont].getLayer(alturaLinha) == 9)
//						&& (bomba[cont].Descer[7] == 1))
//				|| ((bomba[cont].getLayer(alturaLinha) == 10)
//						&& (bomba[cont].Descer[8] == 0))) {
//			if (hitboxBomba.intersects(hitboxEscada1)) {
//				cout << "Bomba[" << cont << "]:" << bomba[cont].Descer[1]
//						<< " \n";
//				BombaBateuNaEscada[cont] = 1;
//
//			}
//		}
//		if (((bomba[cont].getLayer(alturaLinha) == 2)
//						&& (bomba[cont].Descer[0] == 0))
//
//						|| ((bomba[cont].getLayer(alturaLinha) == 4)
//								&& (bomba[cont].Descer[2] == 0))
//
//						|| ((bomba[cont].getLayer(alturaLinha) == 6)
//								&& (bomba[cont].Descer[4] == 0))
//
//						|| ((bomba[cont].getLayer(alturaLinha) == 8)
//								&& (bomba[cont].Descer[6] == 0))
//
//						|| ((bomba[cont].getLayer(alturaLinha) == 10)
//								&& (bomba[cont].Descer[8] == 0))) {
//		if (hitboxBomba.intersects(hitboxEscada2)) {
//			cout << "Bomba[" << cont << "]:" << bomba[cont].Descer[1] << " \n";
//			BombaBateuNaEscada[cont] = 1;
//
//		}}
		if (hitboxBomba.intersects(hitboxEscada1)) {
			if ((bomba[cont].getLayer(alturaLinha) == 2)
					&& (bomba[cont].Descer[0] == 0)) {

				BombaBateuNaEscada[cont] = 1;
			}
		}

		if (hitboxBomba.intersects(hitboxEscada2)) {
			if ((bomba[cont].getLayer(alturaLinha) == 2)
					&& (bomba[cont].Descer[0] == 1)) {
				BombaBateuNaEscada[cont] = 1;
			}
		}

		//AQUI TA FALTANDO A COLISSAO ENTRE BOMBA E BURACO, ELA SO CAI DIRETO SE ESTIVER FORA DO CHAO
	} //fim for
}

void Game::playerUpdate(int playerBateuNoChao, int playerBateuNaParede,
		int playerBateuNaEscada, int playerCaiuNoBuraco,
		bool playerBateuNaBomba) {

	if (playerBateuNaBomba > 0) {
		player.perdeuVidas(alturaLinha, larguraColuna);
	}
	if (playerBateuNoChao > 0) {
		player.setCaiu(false);
		if (player.getMorreuDeQueda() == true) {
			player.perdeuVidas(alturaLinha, larguraColuna);
		}
	} else {
		player.setCaiu(true);
	}

	if (playerCaiuNoBuraco == true) {
		player.setPodeMover(0);
	}

	if (playerBateuNaParede > 0) {
		player.setPodeMover(0);
	} else {
		player.setPodeMover(1);
	}

	//cairno buraco
	if (playerCaiuNoBuraco > 0 && playerBateuNoChao == 0) {
		player.setMorreuDeQueda(true);
		player.setPodeMover(0);
	}

	if (playerBateuNaEscada > 0) {
		player.setPodeSubir(1);
	} else {
		player.setPodeSubir(0);
	}
	if ((player.getLayer(alturaLinha)) <= 5) {
		kong.trocaDePosicao(alturaLinha);
	}
}

void Game::bombaUpdate(vector<int> bombaBateuNoChao,
		vector<int> bombaBateuNaParede, vector<int> bombaBateuNaEscada) {

	for (int cont = 0; cont < qntAtualBombaNormal; cont++) {
		if (bombaBateuNoChao[cont] == true) {
			bomba[cont].setPodeMover(1);
		} else {
			bomba[cont].setPodeMover(0);
		}
		if (bombaBateuNaParede[cont] > 0) {
			bomba[cont].inverteVelX();
		}
		if (bombaBateuNaEscada[cont] > 0) {
			bomba[cont].setPodeDescer(1);
		} else {
			bomba[cont].setPodeDescer(0);
		}

		bomba[cont].mover();
	}

	bool podeSpawnarNormal =
			bomba[qntAtualBombaNormal - 1].olhaSePodeSpawnarNormal(alturaLinha,
					qntAtualBombaNormal); //so spawna se a ultima bomba nao estiver mais no ultimo andar

	if (podeSpawnarNormal == true) {
		//bomba.resize();
		bomba[qntAtualBombaNormal].spawnBombaNormal(alturaLinha, larguraColuna);
		this->qntAtualBombaNormal++;
	}
}

bool Game::getIniciouKong() {
	return iniciouKong;
}

void Game::deleteBombas() {
	//Deletar bombas quando player morre
	for (int i = 0; i < qntAtualBombaNormal; ++i) {
		bomba.pop_back();
	}
	qntAtualBombaNormal = 0;
}

bool Game::playerVenceu() {
	sf::FloatRect hitboxPlayer = player.bounds();
	sf::FloatRect hitboxPrincesa = princesa.getPrincesa().getGlobalBounds();
	if (hitboxPlayer.intersects(hitboxPrincesa)) {
		return true;
	}
	return false;
}

int Game::olhaAndarBomba(int cont) {
	int andar;
	andar = bomba[cont].getLayer(alturaLinha); //pega o andar da bomba
	if (andar > 0 && andar < 9) {
		if (andar == 2) {
			return 3; //primeiro andar
		}
		if (andar % 2 == 0) {
			return 1; //uma escada e dois buracos
		}
		if (andar % 2 == 1) {
			return 2; //duas escadas
		}
	}

	return 0;
}

#endif /* GAME_HPP_ */
