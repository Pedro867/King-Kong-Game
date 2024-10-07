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
#include "BombaEspecial.hpp"
#include "Kong.hpp"
#include "Princesa.hpp"

class Game {
private:
	//Atributos
	std::vector<Chao> chao;
	std::vector<Buraco> buraco;
	std::vector<Parede> paredes;
	std::vector<Escada> escada;

	//elementos
	bool iniciouKong;
	Player &player;
	std::vector<Bomba> bomba;
	std::vector<BombaEspecial> bombaEspecial;
	Kong kong;
	Princesa &princesa;

	float alturaLinha, larguraColuna; //determina a altura de cada linha (tamanho y da janela / num de linhas)

	int nasceuBombaNormal;
	int qntAtualBombaNormal;
	int qntAtualBombaEspecial;

public:
	//Declaracao das funcoes
	Game(Player &player, Princesa &princesa, sf::RenderWindow *window);
	void iniciaElementos(sf::RenderWindow *window);

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
	void bombasTestaColisao();
	void bombasEspeciaisTestaColisao();
	void playerUpdate(int playerBateuNoChao, int playerBateuNaParede,
			int playerPodeSubir, int playerPodeDescer, int playerCaiuNoBuraco,
			bool playerBateuNaBomba);
	void bombaUpdate(vector<int> bombaBateuNoChao,
			vector<int> bombaBateuNaParede, vector<int> bombaBateuNaEscada, vector<int> bombaBateuNoBuraco, vector<int> bombaSaiuDoMapa);
	void bombaEspecialUpdate(vector<int> bombaEspecialBateuNoChao,
				vector<int> bombaEspecialBateuNaParede, vector<int> bombaEspecialBateuNaEscada, vector<int> bombaEspecialBateuNoBuraco, vector<int> bombaEspecialSaiuDoMapa);

	void bombaColisoesNecessarias(vector<int> &bombaBateuNoChao,
			vector<int> &bombaBateuNaParede, vector<int> bombaBateuNoBuraco, vector<int> ignorarParede, vector<int> &bombaSaiuDoMapa, int bombaLayer, int cont);
	void bombaEspecialColisoesNecessarias(vector<int> &bombaEspecialBateuNoChao,
				vector<int> &bombaEspecialBateuNaParede, vector<int> bombaEspecialBateuNoBuraco, vector<int> ignorarParede, vector<int> &bombaEspecialSaiuDoMapa, int bombaEspecialLayer, int cont);

	//formas da bomba descer
	void desce0(vector<int> &bombaBateuNaParede, int bombaLayer, int cont);
	void desce1ou2(vector<int> &bombaBateuNaEscada, vector<int> &ignorarParede, int bombaLayer, int cont);
	void desce3ou4(vector<int> &bombaBateuNaEscada, vector<int> &ignorarParede, int bombaLayer, int cont);
	void desce5ou6(vector<int> &bombaBateuNoChao, vector<int> &bombaBateuNoBuraco, int bombaLayer, int cont);
	void desce7ou8(vector<int> &bombaBateuNoChao, vector<int> &bombaBateuNoBuraco, int bombaLayer, int cont);

	void desce0Especial(vector<int> &bombaEspecialBateuNaParede, int bombaEspecialLayer, int cont);
		void desce1ou2Especial(vector<int> &bombaEspecialBateuNaEscada, vector<int> &ignorarParede, int bombaEspecialLayer, int cont);
		void desce3ou4Especial(vector<int> &bombaEspecialBateuNaEscada, vector<int> &ignorarParede, int bombaEspecialLayer, int cont);
		void desce5ou6Especial(vector<int> &bombaEspecialBateuNoChao, vector<int> &bombaBateuEspecialNoBuraco, int bombaEspecialLayer, int cont);
		void desce7ou8Especial(vector<int> &bombaEspecialBateuNoChao, vector<int> &bombaBateuEspecialNoBuraco, int bombaEspecialLayer, int cont);


	void desceBombaAndares357(int *formaDeDescer);
	void desceBombaEspecialAndares357(int *formaDeDescer);

	void deleteBombas();
	void deleteBombasEspeciais();
	void reiniciaKong();
	bool playerVenceu();


	bool getIniciouKong();
	//---------------------
};

Game::Game(Player &player, Princesa &princesa, sf::RenderWindow *window) :
		player(player), princesa(princesa) {

	alturaLinha = (window->getSize().y) / 10.0f; //determina a altura de cada linha (tamanho y da janela / num de linhas)
	larguraColuna = (window->getSize().x) / 40.0f; //determina a largura de cada coluna (tamanho x da janela / num de colunas)

	kong.iniciaKong(larguraColuna, alturaLinha, window);
	iniciouKong = false; //mudar para testar mais r�pido

	iniciaElementos(window);

	player.setLayer(alturaLinha, larguraColuna);
	princesa.setLayer(alturaLinha, larguraColuna);
	qntAtualBombaNormal = 0;
	qntAtualBombaEspecial = 0;
	nasceuBombaNormal = 0;
}

void Game::iniciaElementos(sf::RenderWindow *window){
	chao.resize(10); //Se isso nao acontecer o jogo crasha
	buraco.resize(10); //queria que fosse 6....
	paredes.resize(16); // Um elemento por linha
	escada.resize(10);
	bomba.resize(10); //No max 10 bombas normais
	bombaEspecial.resize(4);

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
		bomba[i].setLayer(alturaLinha,larguraColuna);
	}
	for (int i = 0; i < 4; i++) {
		bombaEspecial[i].iniciarBombaEspecial(window);
		bombaEspecial[i].setLayer(alturaLinha,larguraColuna);
	}
}

void Game::desenhaCenario(sf::RenderWindow *window) {

	int playerBateuNoChao, playerBateuNaBomba, playerCaiuNoBuraco,
			playerBateuNaParede, playerPodeSubir, playerPodeDescer;
	playerBateuNoChao = playerBateuNaBomba = playerCaiuNoBuraco =
			playerBateuNaParede = playerPodeSubir = playerPodeDescer = 0;

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

		if (iniciouKong == true) {
			playerTestaColisao(&playerBateuNoChao, &playerBateuNaParede,
					&playerPodeSubir, &playerPodeDescer, &playerCaiuNoBuraco,
					&playerBateuNaBomba, i);
		}
	} //for i

	if (iniciouKong == false) {
		iniciouKong = kong.AnimacaoInicialKong(larguraColuna, alturaLinha);
		window->draw(kong.getKong());
	}

	if (iniciouKong == true) {
		playerUpdate(playerBateuNoChao, playerBateuNaParede, playerPodeSubir,
				playerPodeDescer, playerCaiuNoBuraco, playerBateuNaBomba);

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
	for (int cont = 0; cont < qntAtualBombaEspecial; cont++) {

		window->draw(bombaEspecial[cont].getBombaEspecial());
		}
}

void Game::playerTestaColisao(int *playerBateuNoChao, int *playerBateuNaParede,
		int *playerPodeSubir, int *playerPodeDescer, int *playerCaiuNoBuraco,
		int *playerBateuNaBomba, int i) {

	sf::FloatRect hitboxChao1, hitboxChao2, hitboxChao3, hitboxBuraco1,
			hitboxBuraco2, hitboxParede1, hitboxParede2, hitboxEscada1Subir,
			hitboxEscada2Subir, hitboxEscada1Descer,
			hitboxEscada2Descer, hitboxPlayer, hitboxBombaNormal, hitboxBombaEspecial,HitboxDoPulo;
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

	for (int cont = 0; cont <= qntAtualBombaNormal; cont++) {
		HitboxDoPulo = bombaEspecial[cont].getPuloBounds();
		hitboxBombaNormal = bomba[cont].getBombaNormalBounds();
		hitboxBombaEspecial = bombaEspecial[cont].getBombaEspecialBounds();

		hitboxBombaNormal.top = hitboxBombaNormal.top + 10;
		hitboxBombaNormal.height = hitboxBombaNormal.height - 10;

		hitboxBombaEspecial.top = hitboxBombaEspecial.top + 10;
		hitboxBombaEspecial.height = hitboxBombaEspecial.height - 10;

		if (hitboxPlayer.intersects(hitboxBombaNormal) || hitboxPlayer.intersects(hitboxBombaEspecial)) {
			*playerBateuNaBomba = 1;
		}if (hitboxPlayer.intersects(HitboxDoPulo)) {
			player.sobe(larguraColuna,alturaLinha);
		}

	}
}

void Game::bombasTestaColisao() {

	int formaDeDescer;
	int bombaLayer;

	vector<int> bombaBateuNoChao(10, 0), bombaBateuNaParede(10, 0),
				bombaBateuNaEscada(10, 0), bombaBateuNoBuraco(10, 0), ignorarParede(10, 0), bombaSaiuDoMapa(10, 0); //inicializa todos com 0


	for (int cont = 0; cont <= qntAtualBombaNormal; cont++) {

		bombaLayer = bomba[cont].getLayer(alturaLinha);

		if(bombaLayer >= 0){
			formaDeDescer = bomba[cont].getFormaDeDescer();

			if (bombaLayer == 3 || bombaLayer == 5 || bombaLayer == 7) {
				desceBombaAndares357(&formaDeDescer);
			}

			if (formaDeDescer == 0) { //0 == seguir reto
				desce0(bombaBateuNaParede, bombaLayer, cont);
			} else if (formaDeDescer == 1 || formaDeDescer == 2) { //1 || 2 == escada1
				desce1ou2(bombaBateuNaEscada, ignorarParede, bombaLayer, cont);
			} else if (formaDeDescer == 3 || formaDeDescer == 4) { //3 || 4 == escada2
				desce3ou4(bombaBateuNaEscada, ignorarParede, bombaLayer,  cont);
			} else if (formaDeDescer == 5 || formaDeDescer == 6) { //5 || 6 == buraco1
				desce5ou6(bombaBateuNoChao, bombaBateuNoBuraco, bombaLayer, cont);
			} else if (formaDeDescer == 7 || formaDeDescer == 8) { //7 || 8 == buraco2
				desce7ou8(bombaBateuNoChao, bombaBateuNoBuraco, bombaLayer, cont);
			}
			bombaColisoesNecessarias(bombaBateuNoChao, bombaBateuNaParede,
					bombaBateuNoBuraco, ignorarParede, bombaSaiuDoMapa, bombaLayer, cont);
		}
	} //fim for
	bombaUpdate(bombaBateuNoChao, bombaBateuNaParede, bombaBateuNaEscada, bombaBateuNoBuraco, bombaSaiuDoMapa);
}
void Game::bombasEspeciaisTestaColisao(){

	int formaDeDescer;
	int bombaEspecialLayer;


	vector<int> bombaEspecialBateuNoChao(10, 0), bombaEspecialBateuNaParede(10, 0),
				bombaEspecialBateuNaEscada(10, 0), bombaEspecialBateuNoBuraco(10, 0), ignorarParede(10, 0), bombaEspecialSaiuDoMapa(10, 0); //inicializa todos com 0


	for (int cont = 0; cont < qntAtualBombaEspecial; cont++) {

		bombaEspecialLayer = bombaEspecial[cont].getLayer(alturaLinha);


		if(bombaEspecialLayer >= 0){
			formaDeDescer = bombaEspecial[cont].getFormaDeDescer();

			if (bombaEspecialLayer == 3 || bombaEspecialLayer == 5 || bombaEspecialLayer == 7) {
				desceBombaEspecialAndares357(&formaDeDescer);
			}

			if (formaDeDescer == 0) { //0 == seguir reto
				desce0Especial(bombaEspecialBateuNaParede, bombaEspecialLayer, cont);
			} else if (formaDeDescer == 1 || formaDeDescer == 2) { //1 || 2 == escada1
				desce1ou2Especial(bombaEspecialBateuNaEscada, ignorarParede, bombaEspecialLayer, cont);
			} else if (formaDeDescer == 3 || formaDeDescer == 4) { //3 || 4 == escada2
				desce3ou4Especial(bombaEspecialBateuNaEscada, ignorarParede, bombaEspecialLayer,  cont);
			} else if (formaDeDescer == 5 || formaDeDescer == 6) { //5 || 6 == buraco1
				desce5ou6Especial(bombaEspecialBateuNoChao, bombaEspecialBateuNoBuraco, bombaEspecialLayer, cont);
			} else if (formaDeDescer == 7 || formaDeDescer == 8) { //7 || 8 == buraco2
				desce7ou8Especial(bombaEspecialBateuNoChao, bombaEspecialBateuNoBuraco, bombaEspecialLayer, cont);
			}
			bombaEspecialColisoesNecessarias(bombaEspecialBateuNoChao, bombaEspecialBateuNaParede,
					bombaEspecialBateuNoBuraco, ignorarParede, bombaEspecialSaiuDoMapa, bombaEspecialLayer, cont);
		}
	} //fim for
	bombaEspecialUpdate(bombaEspecialBateuNoChao, bombaEspecialBateuNaParede, bombaEspecialBateuNaEscada, bombaEspecialBateuNoBuraco, bombaEspecialSaiuDoMapa);
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
	if ((playerCaiuNoBuraco > 0) && (playerBateuNoChao == 0)) {
		player.setPodeMover(0);
		player.setMorreuDeQueda(true);
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
}


void Game::bombaUpdate(vector<int> bombaBateuNoChao,
		vector<int> bombaBateuNaParede, vector<int> bombaBateuNaEscada, vector<int> bombaBateuNoBuraco, vector<int> bombaSaiuDoMapa) {

	for (int cont = 0; cont <= qntAtualBombaNormal; cont++) {
		if(bombaSaiuDoMapa[cont] == 1){
			bool podeVoltarAoTopo =
					bomba[qntAtualBombaNormal].olhaSePodeSpawnarNormal(
							alturaLinha, qntAtualBombaNormal); //so spawna se a ultima bomba nao estiver mais no ultimo andar

			if (podeVoltarAoTopo == true) {
				bomba[cont].spawnBombaNormal(alturaLinha, larguraColuna);
			}
		}
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
	}//fim for

	if ((qntAtualBombaNormal < 9) && (nasceuBombaNormal < 2)){
		bool podeSpawnarNormal =
				bomba[qntAtualBombaNormal].olhaSePodeSpawnarNormal(alturaLinha,
						qntAtualBombaNormal); //so spawna se a ultima bomba nao estiver mais no ultimo andar

		bool podeSpawnarEspecial;

		if(qntAtualBombaEspecial == 0){
			podeSpawnarEspecial = true;
		}else{
			podeSpawnarEspecial = bombaEspecial[qntAtualBombaEspecial - 1].olhaSePodeSpawnarEspecial(alturaLinha, qntAtualBombaEspecial); //so spawna se a ultima bomba nao estiver mais no ultimo andar
		}


		if (podeSpawnarNormal == true && podeSpawnarEspecial == true) {
			bomba[qntAtualBombaNormal + 1].spawnBombaNormal(alturaLinha,
					larguraColuna);
			this->qntAtualBombaNormal++;
			this->nasceuBombaNormal++;
		}
	}

}
void Game::bombaEspecialUpdate(vector<int> bombaEspecialBateuNoChao,
		vector<int> bombaEspecialBateuNaParede, vector<int> bombaEspecialBateuNaEscada, vector<int> bombaEspecialBateuNoBuraco, vector<int> bombaEspecialSaiuDoMapa) {

	for (int cont = 0; cont < qntAtualBombaEspecial; cont++) {
		if(bombaEspecialSaiuDoMapa[cont] == 1){
			bool podeVoltarAoTopo =
					bombaEspecial[qntAtualBombaEspecial].olhaSePodeSpawnarEspecial(
							alturaLinha, qntAtualBombaEspecial); //so spawna se a ultima bomba nao estiver mais no ultimo andar

			if (podeVoltarAoTopo == true) {
				bombaEspecial[cont].spawnBombaEspecial(alturaLinha, larguraColuna);
			}
		}
		if (bombaEspecialBateuNoChao[cont] > 0) {
			bombaEspecial[cont].setPodeMover(1);
		} else {
			bombaEspecial[cont].setPodeMover(0);
		}
		if (bombaEspecialBateuNaParede[cont] > 0) {
			bombaEspecial[cont].inverteVelX();
		}
		if (bombaEspecialBateuNaEscada[cont] > 0) {
			bombaEspecial[cont].setPodeDescerEscada(1);
		}
		else if (bombaEspecialBateuNoBuraco[cont] > 0) {
			bombaEspecial[cont].setPodeDescerBuraco(1);
		}
		else {
			bombaEspecial[cont].setPodeDescerEscada(0);
			bombaEspecial[cont].setPodeDescerBuraco(0);
		}
		bombaEspecial[cont].mover();
	}//fim for

	if ((qntAtualBombaEspecial < 5) && (nasceuBombaNormal == 2)){
		bool podeSpawnarNormal =
				bomba[qntAtualBombaNormal].olhaSePodeSpawnarNormal(alturaLinha,
						qntAtualBombaNormal); //so spawna se a ultima bomba nao estiver mais no ultimo andar

		if (podeSpawnarNormal == true) {
			bombaEspecial[qntAtualBombaEspecial + 1].spawnBombaEspecial(alturaLinha,
					larguraColuna);
			this->qntAtualBombaEspecial++;
			this->nasceuBombaNormal = 0;
		}
	}
}
void Game::bombaColisoesNecessarias(vector<int> &bombaBateuNoChao,
			vector<int> &bombaBateuNaParede, vector<int> bombaBateuNoBuraco, vector<int> ignorarParede, vector<int> &bombaSaiuDoMapa, int bombaLayer, int cont){

	sf::FloatRect hitboxChao1, hitboxChao2, hitboxChao3, hitboxParede1, hitboxParede2, hitboxBuraco1, hitboxBuraco2;

	hitboxChao1 = chao[bombaLayer].getChao1().getGlobalBounds();
	hitboxChao2 = chao[bombaLayer].getChao2().getGlobalBounds();
	hitboxChao3 = chao[bombaLayer].getChao3().getGlobalBounds();
	hitboxParede1 = paredes[bombaLayer].getParede1().getGlobalBounds();
	hitboxParede2 = paredes[bombaLayer].getParede2().getGlobalBounds();
	hitboxBuraco1 = buraco[bombaLayer].getBuraco1().getGlobalBounds();
	hitboxBuraco2 = buraco[bombaLayer].getBuraco2().getGlobalBounds();

	sf::FloatRect hitboxBomba = bomba[cont].getBombaNormalBounds();
	if(bombaBateuNoBuraco[cont] == 0){
		if (hitboxBomba.intersects(hitboxChao1)
				|| hitboxBomba.intersects(hitboxChao2)
				|| hitboxBomba.intersects(hitboxChao3)) {
			bombaBateuNoChao[cont] = 1;
			bomba[cont].sortearFormaDeDescer(bombaLayer, cont);
		}
	}

	if(ignorarParede[cont] == 0){
		if (hitboxBomba.intersects(hitboxParede1)
				|| hitboxBomba.intersects(hitboxParede2)) {
			bombaBateuNaParede[cont] = 1;
		}
	}

	if(bombaBateuNoBuraco[cont] == 0){
		if (hitboxBomba.intersects(hitboxBuraco1)
					|| hitboxBomba.intersects(hitboxBuraco2)) {
				bombaBateuNoChao[cont] = 1;
			}
		}

	if(bomba[cont].getBombaNormal().getPosition().y >= 10 * alturaLinha){
		bombaSaiuDoMapa[cont] = 1;
	}
}
void Game::bombaEspecialColisoesNecessarias(vector<int> &bombaEspecialBateuNoChao,
			vector<int> &bombaEspecialBateuNaParede, vector<int> bombaEspecialBateuNoBuraco, vector<int> ignorarParede, vector<int> &bombaEspecialSaiuDoMapa, int bombaEspecialLayer, int cont){

	sf::FloatRect hitboxChao1, hitboxChao2, hitboxChao3, hitboxParede1, hitboxParede2, hitboxBuraco1, hitboxBuraco2;

	hitboxChao1 = chao[bombaEspecialLayer].getChao1().getGlobalBounds();
	hitboxChao2 = chao[bombaEspecialLayer].getChao2().getGlobalBounds();
	hitboxChao3 = chao[bombaEspecialLayer].getChao3().getGlobalBounds();
	hitboxParede1 = paredes[bombaEspecialLayer].getParede1().getGlobalBounds();
	hitboxParede2 = paredes[bombaEspecialLayer].getParede2().getGlobalBounds();
	hitboxBuraco1 = buraco[bombaEspecialLayer].getBuraco1().getGlobalBounds();
	hitboxBuraco2 = buraco[bombaEspecialLayer].getBuraco2().getGlobalBounds();

	sf::FloatRect hitboxBomba = bombaEspecial[cont].getBombaEspecialBounds();

	if(bombaEspecialBateuNoBuraco[cont] == 0){
		if (hitboxBomba.intersects(hitboxChao1)
				|| hitboxBomba.intersects(hitboxChao2)
				|| hitboxBomba.intersects(hitboxChao3)) {
			bombaEspecialBateuNoChao[cont] = 1;
			bombaEspecial[cont].sortearFormaDeDescer(bombaEspecialLayer, cont);
		}
	}

	if(ignorarParede[cont] == 0){
		if (hitboxBomba.intersects(hitboxParede1)
				|| hitboxBomba.intersects(hitboxParede2)) {
			bombaEspecialBateuNaParede[cont] = 1;
		}
	}

	if(bombaEspecialBateuNoBuraco[cont] == 0){
		if (hitboxBomba.intersects(hitboxBuraco1)
					|| hitboxBomba.intersects(hitboxBuraco2)) {
				bombaEspecialBateuNoChao[cont] = 1;
			}
		}

	if(bombaEspecial[cont].getBombaEspecial().getPosition().y >= 10 * alturaLinha){
		bombaEspecialSaiuDoMapa[cont] = 1;
	}
}
void Game::desce0Especial(vector<int> &bombaEspecialBateuNaParede, int bombaEspecialLayer, int cont){

	sf::FloatRect hitboxBomba = bombaEspecial[cont].getBombaEspecialBounds();

	sf::FloatRect hitboxParede1 = paredes[bombaEspecialLayer].getParede1().getGlobalBounds();
	sf::FloatRect hitboxParede2 = paredes[bombaEspecialLayer].getParede2().getGlobalBounds();

	if (hitboxBomba.intersects(hitboxParede1)
			|| hitboxBomba.intersects(hitboxParede2)) {
		bombaEspecial[cont].setSorteouFormaDeDescer(false);
		//se bateu na parede, sorteia outra forma de descer
	}
}
void Game::desce0(vector<int> &bombaBateuNaParede, int bombaLayer, int cont){

	sf::FloatRect hitboxBomba = bomba[cont].getBombaNormalBounds();

	sf::FloatRect hitboxParede1 = paredes[bombaLayer].getParede1().getGlobalBounds();
	sf::FloatRect hitboxParede2 = paredes[bombaLayer].getParede2().getGlobalBounds();

	if (hitboxBomba.intersects(hitboxParede1)
			|| hitboxBomba.intersects(hitboxParede2)) {
		bomba[cont].setSorteouFormaDeDescer(false);
		//se bateu na parede, sorteia outra forma de descer
	}
}

void Game::desce1ou2(vector<int> &bombaBateuNaEscada, vector<int> &ignorarParede, int bombaLayer, int cont){

	sf::FloatRect hitboxBomba = bomba[cont].getBombaNormalBounds();

	if(bombaLayer <= 1){
		ignorarParede[cont] = 1;
	}
	else{
		sf::FloatRect hitboxEscada1 = escada[bombaLayer - 1].getEscada1().getGlobalBounds();
		sf::FloatRect hitboxEscada2 = escada[bombaLayer - 1].getEscada2().getGlobalBounds();
		hitboxEscada1.height = hitboxEscada1.height - 30;
		hitboxEscada2.height = hitboxEscada2.height - 30;

		if (bomba[cont].getVelX() > 0) {
			hitboxEscada1.left = hitboxEscada1.left + hitboxEscada1.width / 2;
			hitboxBomba.left = hitboxBomba.left - hitboxBomba.width / 2;
		} else {
			hitboxEscada1.left = hitboxEscada1.left - hitboxEscada1.width / 2;
			hitboxBomba.left = hitboxBomba.left + hitboxBomba.width / 2;
		}
		if (hitboxBomba.intersects(hitboxEscada1)) {
			bombaBateuNaEscada[cont] = 1;
		}
	}
}
void Game::desce1ou2Especial(vector<int> &bombaEspecialBateuNaEscada, vector<int> &ignorarParede, int bombaEspecialLayer, int cont){

	sf::FloatRect hitboxBomba = bombaEspecial[cont].getBombaEspecialBounds();

	if(bombaEspecialLayer <= 1){
		ignorarParede[cont] = 1;
	}
	else{
		sf::FloatRect hitboxEscada1 = escada[bombaEspecialLayer - 1].getEscada1().getGlobalBounds();
		sf::FloatRect hitboxEscada2 = escada[bombaEspecialLayer - 1].getEscada2().getGlobalBounds();
		hitboxEscada1.height = hitboxEscada1.height - 30;
		hitboxEscada2.height = hitboxEscada2.height - 30;

		if (bombaEspecial[cont].getVelX() > 0) {
			hitboxEscada1.left = hitboxEscada1.left + hitboxEscada1.width / 2;
			hitboxBomba.left = hitboxBomba.left - hitboxBomba.width / 2;
		} else {
			hitboxEscada1.left = hitboxEscada1.left - hitboxEscada1.width / 2;
			hitboxBomba.left = hitboxBomba.left + hitboxBomba.width / 2;
		}
		if (hitboxBomba.intersects(hitboxEscada1)) {
			bombaEspecialBateuNaEscada[cont] = 1;
		}
	}
}
void Game::desce3ou4(vector<int> &bombaBateuNaEscada, vector<int> &ignorarParede, int bombaLayer, int cont){

	sf::FloatRect hitboxBomba = bomba[cont].getBombaNormalBounds();

	sf::FloatRect hitboxEscada1 =
			escada[bombaLayer - 1].getEscada1().getGlobalBounds();
	sf::FloatRect hitboxEscada2 =
			escada[bombaLayer - 1].getEscada2().getGlobalBounds();
	hitboxEscada1.height = hitboxEscada1.height - 30;
	hitboxEscada2.height = hitboxEscada2.height - 30;

	if (bomba[cont].getVelX() > 0) {
		hitboxEscada2.left = hitboxEscada2.left + hitboxEscada2.width / 2;
		hitboxBomba.left = hitboxBomba.left - hitboxBomba.width / 2;
	} else {
		hitboxEscada2.left = hitboxEscada2.left - hitboxEscada2.width / 2;
		hitboxBomba.left = hitboxBomba.left + hitboxBomba.width / 2;
	}

	if (hitboxBomba.intersects(hitboxEscada2)) {
		bombaBateuNaEscada[cont] = 1;
	}
}
void Game::desce3ou4Especial(vector<int> &bombaEspecialBateuNaEscada, vector<int> &ignorarParede, int bombaEspecialLayer, int cont){

	sf::FloatRect hitboxBomba = bombaEspecial[cont].getBombaEspecialBounds();

	sf::FloatRect hitboxEscada1 =
			escada[bombaEspecialLayer - 1].getEscada1().getGlobalBounds();
	sf::FloatRect hitboxEscada2 =
			escada[bombaEspecialLayer - 1].getEscada2().getGlobalBounds();
	hitboxEscada1.height = hitboxEscada1.height - 30;
	hitboxEscada2.height = hitboxEscada2.height - 30;

	if (bombaEspecial[cont].getVelX() > 0) {
		hitboxEscada2.left = hitboxEscada2.left + hitboxEscada2.width / 2;
		hitboxBomba.left = hitboxBomba.left - hitboxBomba.width / 2;
	} else {
		hitboxEscada2.left = hitboxEscada2.left - hitboxEscada2.width / 2;
		hitboxBomba.left = hitboxBomba.left + hitboxBomba.width / 2;
	}

	if (hitboxBomba.intersects(hitboxEscada2)) {
		bombaEspecialBateuNaEscada[cont] = 1;
	}
}

void Game::desce5ou6(vector<int> &bombaBateuNoChao, vector<int> &bombaBateuNoBuraco, int bombaLayer, int cont){

	sf::FloatRect hitboxBomba = bomba[cont].getBombaNormalBounds();
	sf::FloatRect hitboxBuraco1;

	hitboxBuraco1 = buraco[bombaLayer].getBuraco1().getGlobalBounds();

	if (bomba[cont].getVelX() > 0) {
		hitboxBuraco1.left = hitboxBuraco1.left + hitboxBuraco1.width / 2;
		hitboxBomba.left = hitboxBomba.left - hitboxBomba.width / 2;
	} else {
		hitboxBuraco1.left = hitboxBuraco1.left - hitboxBuraco1.width / 2;
		hitboxBomba.left = hitboxBomba.left + hitboxBomba.width / 2;
	}

	if (hitboxBomba.intersects(hitboxBuraco1)) {
		bombaBateuNoChao[cont] = 0;
		bombaBateuNoBuraco[cont] = 1;
	}
}
void Game::desce5ou6Especial(vector<int> &bombaEspecialBateuNoChao, vector<int> &bombaEspecialBateuNoBuraco, int bombaEspecialLayer, int cont){

	sf::FloatRect hitboxBomba = bombaEspecial[cont].getBombaEspecialBounds();
	sf::FloatRect hitboxBuraco1;

	hitboxBuraco1 = buraco[bombaEspecialLayer].getBuraco1().getGlobalBounds();

	if (bombaEspecial[cont].getVelX() > 0) {
		hitboxBuraco1.left = hitboxBuraco1.left + hitboxBuraco1.width / 2;
		hitboxBomba.left = hitboxBomba.left - hitboxBomba.width / 2;
	} else {
		hitboxBuraco1.left = hitboxBuraco1.left - hitboxBuraco1.width / 2;
		hitboxBomba.left = hitboxBomba.left + hitboxBomba.width / 2;
	}

	if (hitboxBomba.intersects(hitboxBuraco1)) {
		bombaEspecialBateuNoChao[cont] = 0;
		bombaEspecialBateuNoBuraco[cont] = 1;
	}
}

void Game::desce7ou8(vector<int> &bombaBateuNoChao, vector<int> &bombaBateuNoBuraco, int bombaLayer, int cont){

	sf::FloatRect hitboxBomba = bomba[cont].getBombaNormalBounds();
	sf::FloatRect hitboxBuraco2;

	hitboxBuraco2 = buraco[bombaLayer].getBuraco2().getGlobalBounds();

	if (bomba[cont].getVelX() > 0) {
		hitboxBuraco2.left = hitboxBuraco2.left + hitboxBuraco2.width / 2;
		hitboxBomba.left = hitboxBomba.left - hitboxBomba.width / 2;
	} else {
		hitboxBuraco2.left = hitboxBuraco2.left - hitboxBuraco2.width / 2;
		hitboxBomba.left = hitboxBomba.left + hitboxBomba.width / 2;
	}

	if (hitboxBomba.intersects(hitboxBuraco2)) {
		bombaBateuNoChao[cont] = 0;
		bombaBateuNoBuraco[cont] = 1;
	}
}
void Game::desce7ou8Especial(vector<int> &bombaEspecialBateuNoChao, vector<int> &bombaEspecialBateuNoBuraco, int bombaEspecialLayer, int cont){

	sf::FloatRect hitboxBomba = bombaEspecial[cont].getBombaEspecialBounds();
	sf::FloatRect hitboxBuraco2;

	hitboxBuraco2 = buraco[bombaEspecialLayer].getBuraco2().getGlobalBounds();

	if (bombaEspecial[cont].getVelX() > 0) {
		hitboxBuraco2.left = hitboxBuraco2.left + hitboxBuraco2.width / 2;
		hitboxBomba.left = hitboxBomba.left - hitboxBomba.width / 2;
	} else {
		hitboxBuraco2.left = hitboxBuraco2.left - hitboxBuraco2.width / 2;
		hitboxBomba.left = hitboxBomba.left + hitboxBomba.width / 2;
	}

	if (hitboxBomba.intersects(hitboxBuraco2)) {
		bombaEspecialBateuNoChao[cont] = 0;
		bombaEspecialBateuNoBuraco[cont] = 1;
	}
}

void Game::desceBombaAndares357(int *formaDeDescer){
	if(*formaDeDescer == 3){ //so tem 1 escada, entao 3 nao seria escada2 e sim buraco 2
		*formaDeDescer = 7;
	}
	else if(*formaDeDescer == 4){//so tem 1 escada, entao 4 nao seria escada2 e sim buraco 2
		*formaDeDescer = 8;
	}
}
void Game::desceBombaEspecialAndares357(int *formaDeDescer){
	if(*formaDeDescer == 3){ //so tem 1 escada, entao 3 nao seria escada2 e sim buraco 2
		*formaDeDescer = 7;
	}
	else if(*formaDeDescer == 4){//so tem 1 escada, entao 4 nao seria escada2 e sim buraco 2
		*formaDeDescer = 8;
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
void Game::deleteBombasEspeciais() {
	//Deletar bombas quando player morre
	for (int i = 0; i <= qntAtualBombaEspecial; ++i) {
		bombaEspecial[i].setLayer(alturaLinha, larguraColuna);
		bombaEspecial[i].setSorteouFormaDeDescer(false);
		//na verdade nao deleta, mas deixa ela pronta pra spawnar denovo
	}
	qntAtualBombaEspecial = 0;
}

void Game::reiniciaKong(){
	kong.setPosition(larguraColuna * 9, alturaLinha * 3);
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
