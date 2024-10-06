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
			int *playerPodeSubir, int *playerPodeDescer,
			int *playerCaiuNoBuraco, int *playerBateuNaBomba, int i);
	void bombasTestaColisao(vector<int> &bombaBateuNoChao,
			vector<int> &bombaBateuNaParede, vector<int> &BombaBateuNaEscada,
			vector<int> &bombaBateuNoBuraco, int i);
	void playerUpdate(int playerBateuNoChao, int playerBateuNaParede,
			int playerPodeSubir, int playerPodeDescer, int playerCaiuNoBuraco,
			bool playerBateuNaBomba);
	void bombaUpdate(vector<int> bombaBateuNoChao,
			vector<int> bombaBateuNaParede, vector<int> bombaBateuNaEscada, vector<int> bombaBateuNoBuraco);


	void desceBombaAndares357(int *formaDeDescer);


	void deleteBombas();
	bool playerVenceu();


	bool getIniciouKong();
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
	qntAtualBombaNormal = 0;
}

void Game::desenhaCenario(sf::RenderWindow *window) {

	int playerBateuNoChao, playerBateuNaBomba, playerCaiuNoBuraco,
			playerBateuNaParede, playerPodeSubir, playerPodeDescer;
	playerBateuNoChao = playerBateuNaBomba = playerCaiuNoBuraco =
			playerBateuNaParede = playerPodeSubir = playerPodeDescer = 0;

	vector<int> bombaBateuNoChao(10, 0), bombaBateuNaParede(10, 0),
			bombaBateuNaEscada(10, 0), bombaBateuNoBuraco(10, 0); //inicializa todos com 0
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
					&playerPodeSubir, &playerPodeDescer, &playerCaiuNoBuraco,
					&playerBateuNaBomba, i);
			bombasTestaColisao(bombaBateuNoChao, bombaBateuNaParede,
					bombaBateuNaEscada, bombaBateuNoBuraco, i);
		}
	} //for i

	if (iniciouKong == false) {
		iniciouKong = kong.AnimacaoInicialKong(larguraColuna, alturaLinha);
		window->draw(kong.getKong());
	}

	if (iniciouKong == true) {
		playerUpdate(playerBateuNoChao, playerBateuNaParede, playerPodeSubir,
				playerPodeDescer, playerCaiuNoBuraco, playerBateuNaBomba);
		bombaUpdate(bombaBateuNoChao, bombaBateuNaParede, bombaBateuNaEscada, bombaBateuNoBuraco);

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

	for (int cont = 0; cont <= qntAtualBombaNormal; cont++) {
		window->draw(bomba[cont].getBombaNormal());
	}
}

void Game::playerTestaColisao(int *playerBateuNoChao, int *playerBateuNaParede,
		int *playerPodeSubir, int *playerPodeDescer, int *playerCaiuNoBuraco,
		int *playerBateuNaBomba, int i) {

	sf::FloatRect hitboxChao1, hitboxChao2, hitboxChao3, hitboxBuraco1,
			hitboxBuraco2, hitboxParede1, hitboxParede2, hitboxEscada1Subir,
			hitboxEscada2Subir, hitboxEscada1Descer,
			hitboxEscada2Descer, hitboxPlayer, hitboxBomba;
	hitboxPlayer = player.bounds();
	hitboxChao1 = chao[i].getChao1().getGlobalBounds();
	hitboxChao2 = chao[i].getChao2().getGlobalBounds();
	hitboxChao3 = chao[i].getChao3().getGlobalBounds();
	hitboxBuraco1 = buraco[i].getBuraco1().getGlobalBounds();
	hitboxBuraco2 = buraco[i].getBuraco2().getGlobalBounds();
	hitboxParede1 = paredes[i].getParede1().getGlobalBounds();
	hitboxParede2 = paredes[i].getParede2().getGlobalBounds();
	hitboxEscada1Subir = escada[i].getHitbox1().getGlobalBounds();
	hitboxEscada2Subir = escada[i].getHitbox2().getGlobalBounds();
	hitboxEscada1Descer = escada[i].getHitboxDescer1().getGlobalBounds();
	hitboxEscada2Descer = escada[i].getHitboxDescer2().getGlobalBounds();
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
	if (hitboxPlayer.intersects(hitboxEscada1Subir)
			|| hitboxPlayer.intersects(hitboxEscada2Subir)) {
		*playerPodeSubir = 1;
	}
	if (hitboxPlayer.intersects(hitboxEscada1Descer)
			|| hitboxPlayer.intersects(hitboxEscada2Descer)) {
		*playerPodeDescer = 1;
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
		vector<int> &bombaBateuNaParede, vector<int> &BombaBateuNaEscada, vector<int> &bombaBateuNoBuraco,
		int i) {
	srand(time(NULL));

	int formaDeDescer;

	sf::FloatRect hitboxChao1;
	sf::FloatRect hitboxChao2;
	sf::FloatRect hitboxChao3;
	sf::FloatRect hitboxParede1;
	sf::FloatRect hitboxParede2;
	//sf::FloatRect Parede8;
	sf::FloatRect hitboxEscada1;
	sf::FloatRect hitboxEscada2;
	sf::FloatRect hitboxBuraco1;
	sf::FloatRect hitboxBuraco2;
	//sf::FloatRect meio1, meio2;

	for (int cont = 0; cont <= qntAtualBombaNormal; cont++) {

		hitboxChao1 = chao[i].getChao1().getGlobalBounds();
		hitboxChao2 = chao[i].getChao2().getGlobalBounds();
		hitboxChao3 = chao[i].getChao3().getGlobalBounds();
		hitboxParede1 = paredes[i].getParede1().getGlobalBounds();
		hitboxParede2 = paredes[i].getParede2().getGlobalBounds();
		hitboxEscada1 = escada[i].getEscada1().getGlobalBounds();
		hitboxEscada2 = escada[i].getEscada2().getGlobalBounds();
		hitboxEscada1.height = hitboxEscada1.height - 30;
		hitboxEscada2.height = hitboxEscada2.height - 30;
		hitboxBuraco1 = buraco[i].getBuraco1().getGlobalBounds();
		hitboxBuraco2 = buraco[i].getBuraco2().getGlobalBounds();

		int bombaLayer = bomba[cont].getLayer(alturaLinha);

		sf::FloatRect hitboxBomba = bomba[cont].getBombaNormalBounds();

		if (hitboxBomba.intersects(hitboxChao1)
				|| hitboxBomba.intersects(hitboxChao2)
				|| hitboxBomba.intersects(hitboxChao3)) {
			bombaBateuNoChao[cont] = 1;
			bomba[cont].sortearFormaDeDescer(bombaLayer, cont);
		}

		formaDeDescer = bomba[cont].getFormaDeDescer();

		if (hitboxBomba.intersects(hitboxParede1)
				|| hitboxBomba.intersects(hitboxParede2)) {
			bombaBateuNaParede[cont] = 1;
		}

		if (hitboxBomba.intersects(hitboxBuraco1)
				|| hitboxBomba.intersects(hitboxBuraco2)) {
			bombaBateuNoChao[cont] = 1;
		}

		if(bombaLayer == 3 || bombaLayer == 5 || bombaLayer == 7){
			desceBombaAndares357(&formaDeDescer);
		}

		if(formaDeDescer == 0){ //0 == seguir reto
			if(bombaBateuNaParede[cont] == 1) {
			bomba[cont].setSorteouFormaDeDescer(false);
					//se bateu na parede, sorteia outra forma de descer
			}
		}
		else if(formaDeDescer == 1){ //1 == escada1
			if(bomba[cont].getVelX() > 0) {
				hitboxEscada1.left = hitboxEscada1.left
						+ hitboxEscada1.width / 2;
				hitboxBomba.left = hitboxBomba.left - hitboxBomba.width / 2;
			}else {
				hitboxEscada1.left = hitboxEscada1.left - hitboxEscada1.width / 2;
				hitboxBomba.left = hitboxBomba.left + hitboxBomba.width / 2;
			}
			if(hitboxBomba.intersects(hitboxEscada1)) {
					BombaBateuNaEscada[cont] = 1;
			}
		}
		else if (formaDeDescer == 2) { //2 == escada2
			if(bomba[cont].getVelX() > 0) {
				hitboxEscada2.left = hitboxEscada2.left
						+ hitboxEscada2.width / 2;
				hitboxBomba.left = hitboxBomba.left - hitboxBomba.width / 2;
			}else {
				hitboxEscada2.left = hitboxEscada2.left
						- hitboxEscada2.width / 2;
				hitboxBomba.left = hitboxBomba.left + hitboxBomba.width / 2;
			}

			if(hitboxBomba.intersects(hitboxEscada2)) {
				BombaBateuNaEscada[cont] = 1;
			}
		}
		else if(formaDeDescer == 3){ //3 == buraco1
			if (bomba[cont].getVelX() > 0) {
				hitboxBuraco1.left = hitboxBuraco1.left
						+ hitboxBuraco1.width / 2;
				hitboxBomba.left = hitboxBomba.left - hitboxBomba.width / 2;
			} else {
				hitboxBuraco1.left = hitboxBuraco1.left
						- hitboxBuraco1.width / 2;
				hitboxBomba.left = hitboxBomba.left + hitboxBomba.width / 2;
			}

			if(hitboxBomba.intersects(hitboxBuraco2)){
				bombaBateuNoChao[cont] = 0;
				bombaBateuNoBuraco[cont] = 1;
			}
		}
		else if (formaDeDescer == 4) { //4 == buraco2
			if (bomba[cont].getVelX() > 0) {
				hitboxBuraco2.left = hitboxBuraco2.left
						+ hitboxBuraco2.width / 2;
				hitboxBomba.left = hitboxBomba.left - hitboxBomba.width / 2;
			} else {
				hitboxBuraco2.left = hitboxBuraco2.left
						- hitboxBuraco2.width / 2;
				hitboxBomba.left = hitboxBomba.left + hitboxBomba.width / 2;
			}

			if(hitboxBomba.intersects(hitboxBuraco2)){
				bombaBateuNoChao[cont] = 0;
				bombaBateuNoBuraco[cont] = 1;
			}
		}
	} //fim for
}

void Game::playerUpdate(int playerBateuNoChao, int playerBateuNaParede,
		int playerPodeSubir, int playerPodeDescer, int playerCaiuNoBuraco,
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

	if (playerPodeSubir > 0) {
		player.setPodeSubir(1);
	} else {
		player.setPodeSubir(0);
	}
	if (playerPodeDescer > 0) {
		player.setPodeDescer(1);
	} else {
		player.setPodeDescer(0);
	}
	if ((player.getLayer(alturaLinha)) <= 5) {
		kong.trocaDePosicao(alturaLinha);
	}
}


void Game::bombaUpdate(vector<int> bombaBateuNoChao,
		vector<int> bombaBateuNaParede, vector<int> bombaBateuNaEscada, vector<int> bombaBateuNoBuraco) {

	for (int cont = 0; cont <= qntAtualBombaNormal; cont++) {
		if (bombaBateuNoChao[cont] > 0) {
			bomba[cont].setPodeMover(1);
		} else {
			bomba[cont].setPodeMover(0);
		}
		if (bombaBateuNaParede[cont] > 0) {
			bomba[cont].inverteVelX();
		}
		if (bombaBateuNaEscada[cont] > 0) {
			bomba[cont].setPodeDescerEscada(1);
		}
		else if (bombaBateuNoBuraco[cont] > 0) {
			bomba[cont].setPodeDescerBuraco(1);
		}
		else {
			bomba[cont].setPodeDescerEscada(0);
			bomba[cont].setPodeDescerBuraco(0);
		}
		bomba[cont].mover();
	}

	bool podeSpawnarNormal =
			bomba[qntAtualBombaNormal].olhaSePodeSpawnarNormal(alturaLinha, qntAtualBombaNormal); //so spawna se a ultima bomba nao estiver mais no ultimo andar

	if (podeSpawnarNormal == true) {
		bomba[qntAtualBombaNormal + 1].spawnBombaNormal(alturaLinha, larguraColuna);
		this->qntAtualBombaNormal++;
	}
}

void Game::desceBombaAndares357(int *formaDeDescer){
	if(*formaDeDescer == 2){ //so tem 1 escada, entao 2 nao seria escada2 e sim buraco 1
		*formaDeDescer = 3;
	}
	else if(*formaDeDescer == 3){
		*formaDeDescer = 4;
	}
}

bool Game::getIniciouKong() {
	return iniciouKong;
}

void Game::deleteBombas() {
	//Deletar bombas quando player morre
	for (int i = 0; i <= qntAtualBombaNormal; ++i) {
		bomba[i].setLayer(alturaLinha, larguraColuna);
		bomba[i].setSorteouFormaDeDescer(false);
		//na verdade nao deleta, mas deixa ela pronta pra spawnar denovo
	}
	qntAtualBombaNormal = 0;
}

bool Game::playerVenceu() {
	sf::FloatRect hitboxPlayer = player.bounds();
	sf::FloatRect hitboxPrincesa = princesa.getPrincesa().getGlobalBounds();
	if(hitboxPlayer.intersects(hitboxPrincesa)){
		return true;
	}
	return false;
}

#endif /* GAME_HPP_ */
