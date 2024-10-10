//============================================================================
// Nome        : King Kong Game
// Autores     : Lucas Lenz, Pedro Lucas e Rafael Torres
//============================================================================

#include <SFMl/Graphics.hpp>
#include <SFML/audio.hpp>
#include <iostream>
#include <ctime>
#include "Player.hpp"
#include "Bomba.hpp"
#include "Game.hpp"

void animacaoMorte(sf::RenderWindow& window){
	sf::RectangleShape tela;
	sf::Vector2f tamanho(window.getSize().x, window.getSize().y);
	tela.setSize(tamanho);
	sf::Vector2f origem(tamanho.x/2, tamanho.y/2);
	tela.setOrigin(origem);
	tela.setPosition(window.getSize().x/2, window.getSize().y/2);

	for (int cont = 0; cont < 40; cont++) {//40 quadros eh a duracao
		window.clear();
		if(cont % 20 <= 10){
			tela.setFillColor(sf::Color(28,28,28));
		}
		if(cont % 20 > 10){
			tela.setFillColor(sf::Color(169,169,169));
		}
		window.draw(tela);
		window.display();
	}
}

void gameOver(sf::RenderWindow& window){
	//Texto
	sf::Font fonte;
	fonte.loadFromFile("assets/8-BIT WONDER.ttf");
	sf::Text fimDeJogo;
	fimDeJogo.setFont(fonte);
	fimDeJogo.setCharacterSize(100);
	fimDeJogo.setFillColor(sf::Color::White);
	//esses numeros no position sao os unicos que deixa o texto no meio da tela
	fimDeJogo.setPosition(window.getSize().x/8 , window.getSize().y/2 - 100);
	fimDeJogo.setString("Game Over");

	window.clear();
	window.draw(fimDeJogo);
	window.display();
}

void veceuJogo(sf::RenderWindow& window){
	//Texto
	sf::Font fonte;
	fonte.loadFromFile("assets/8-BIT WONDER.ttf");
	sf::Text mensagemVitoria;
	mensagemVitoria.setFont(fonte);
	mensagemVitoria.setCharacterSize(100);
	mensagemVitoria.setFillColor(sf::Color::Red);
	mensagemVitoria.setPosition((window.getSize().x / 4), (window.getSize().y / 3));
	mensagemVitoria.setString("Vitoria");

	//Quadrado na tela
	sf::RectangleShape tela;
	sf::Vector2f tamanho(window.getSize().x, window.getSize().y);
	tela.setSize(tamanho);
	sf::Vector2f origem(tamanho.x / 2, tamanho.y / 2);
	tela.setOrigin(origem);
	tela.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	tela.setFillColor(sf::Color::Blue);

	window.clear();
	window.draw(tela);
	window.draw(mensagemVitoria);
	window.display();
}

int main(int argc, char **argv) {

	setbuf(stdout, NULL);
	sf::VideoMode video(1200, 600);
	sf::RenderWindow window(video, "King Kong");
	sf::Event evento;
	int framerate = 40;
	window.setFramerateLimit(framerate);

	//Fundo
	sf::Texture background;
	background.loadFromFile("assets/background.png");
	sf::Sprite fundo;
	fundo.setTexture(background);
	fundo.setOrigin(256, 256);
	fundo.setPosition(window.getPosition().x / 2, window.getPosition().y / 2);
	fundo.setScale(6, 6);


	//Texto
	sf::Font fonte;
	fonte.loadFromFile("assets/8-BIT WONDER.ttf");

	string vidasString, tempoString;
	sf::Text vidas, tempo;
	vidas.setFont(fonte);
	vidas.setCharacterSize((window.getSize().x)/20);
	vidas.setFillColor(sf::Color::Red);
	vidas.setPosition((window.getSize().x) * 28/40, -5);

	tempo.setFont(fonte);
	tempo.setCharacterSize((window.getSize().x)/20);
	tempo.setFillColor(sf::Color(32, 32, 32));
	tempo.setPosition((window.getSize().x)/40, -5);
	int contadorQuadros = 0, contadorTotal = 0;


	//Audio
	sf::SoundBuffer bufferSomDoJogo;
	sf::Sound somDoJogo;
	sf::SoundBuffer bufferSomDaMorte;
	sf::Sound somDaMorte;
	sf::SoundBuffer bufferSomDaVitoria;
		sf::Sound SomDaVitoria;
	bufferSomDoJogo.loadFromFile("assets/musicaJogo.ogg");
	somDoJogo.setBuffer(bufferSomDoJogo);
	bufferSomDaMorte.loadFromFile("assets/SomDeGameOver.ogg");
	somDaMorte.setBuffer(bufferSomDaMorte);
	bufferSomDaVitoria.loadFromFile("assets/SomDeVitoria.ogg");
	SomDaVitoria.setBuffer(bufferSomDaVitoria);

	//Elementos
	Player player(window);
	Princesa princesa(window);
	Game Game(player, princesa, &window);

	//Booleanos de controle
	bool morreu = false, iniciouJogo = false, ganhou = false;

	while (window.isOpen()) {

		while (window.pollEvent(evento)) {
			if (evento.type == sf::Event::Closed) {
				window.close();
			}
		}

		if(!iniciouJogo){
			iniciouJogo = true;
			somDoJogo.setVolume(70);
			somDoJogo.play();
			somDoJogo.setLoop(true);
		}

		window.clear();

		//Desenha cenario e fundo
		window.draw(fundo);

		Game.desenhaCenario(&window); //colisoes dentro dessa funcao

		//movimenta elementos se o kong tiver iniciado
		if (Game.getIniciouKong()) {
			Game.bombasTestaColisao();
			Game.bombasEspeciaisTestaColisao();
			//Game.playerTestaColisao();
			player.moverY(evento);
			player.moverX(evento);
			contadorQuadros++;
			if (contadorQuadros >= framerate) {
				contadorTotal++;
				contadorQuadros = 0;
			}
			vidasString = to_string(player.getVidas());
			vidas.setString(vidasString + " Vidas");
			tempoString = to_string(contadorTotal);
			tempo.setString(tempoString);
			window.draw(vidas);
			window.draw(tempo);
		}

		if(player.getPerdeuVida()){//ve se ele perdeu vida pra rodar a animacao
			animacaoMorte(window);
			contadorTotal = 0;
			player.setPerdeuVida(false);
			Game.deleteBombas();
			Game.deleteBombasEspeciais();
			Game.reiniciaKong();
			continue;
		}
		if(player.getVidas() <= 0 || contadorTotal > 79){//ve se acabou as vidas
			if(!morreu){
				morreu = true;
				somDoJogo.pause();
				somDaMorte.play();
			}
			gameOver(window);
			continue;
		}
		if(Game.playerVenceu()){
			if(!ganhou){
				ganhou = true;
				somDoJogo.pause();
				SomDaVitoria.play();

			}
			veceuJogo(window);
			continue;
		}

		window.display();
	}

	return 0;
}
