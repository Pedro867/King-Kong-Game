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
	fonte.loadFromFile("assets/Arial.ttf");
	sf::Text fimDeJogo;
	fimDeJogo.setFont(fonte);
	fimDeJogo.setCharacterSize(100);
	fimDeJogo.setFillColor(sf::Color::White);
	//esses numeros no position sao os unicos que deixa o texto no meio da tela
	fimDeJogo.setPosition(window.getSize().x/2 - (window.getSize().x * 0.23), window.getSize().y/2 - 100);
	fimDeJogo.setString("Game Over");

	window.clear();
	window.draw(fimDeJogo);
	window.display();
}

void veceuJogo(sf::RenderWindow& window){
	//Texto
	sf::Font fonte;
	fonte.loadFromFile("assets/Arial.ttf");
	sf::Text mensagemVitoria;
	mensagemVitoria.setFont(fonte);
	mensagemVitoria.setCharacterSize(100);
	mensagemVitoria.setFillColor(sf::Color::Red);
	mensagemVitoria.setPosition((window.getSize().x / 2 - (window.getSize().x * 0.146)), (window.getSize().y / 2 - 100));
	mensagemVitoria.setString("Vitoria!");

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
	fonte.loadFromFile("assets/Arial.ttf");
	string vidasString, tempoString;
	sf::Text vidas, tempo;
	vidas.setFont(fonte);
	vidas.setCharacterSize(30);
	vidas.setOrigin(15, 15);
	vidas.setFillColor(sf::Color::Red);
	vidas.setPosition(35*(window.getSize().x/100), 5*(window.getSize().y / 100));
	tempo.setFont(fonte);
	tempo.setCharacterSize(30);
	tempo.setOrigin(15, 15);
	tempo.setFillColor(sf::Color(32, 32, 32));
	tempo.setPosition(15*(window.getSize().x/100), 5*(window.getSize().y/100));
	int contadorQuadros = 0, contadorTotal = 0;


	//Audio
	sf::SoundBuffer bufferSomDoJogo;
	sf::Sound somDoJogo;
	sf::SoundBuffer bufferSomDaMorte;
	sf::Sound somDaMorte;
	bufferSomDoJogo.loadFromFile("assets/musicaJogo.ogg");
	somDoJogo.setBuffer(bufferSomDoJogo);
	bufferSomDaMorte.loadFromFile("assets/SomDeGameOver.ogg");
	somDaMorte.setBuffer(bufferSomDaMorte);

	//Elementos
	Player player(window);
	Princesa princesa(window);
	Game Game(player, princesa, &window);

	//Booleanos de controle
	bool morreu = false, iniciouJogo = false;

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

		if(player.getPerdeuVida()){//ve se ele perdeu vida pra rodar a animacao
			animacaoMorte(window);
			player.setPerdeuVida(false);
			Game.deleteBombas();
			Game.deleteBombasEspeciais();
			Game.reiniciaKong();
			continue;
		}
		if(player.getVidas() <= 0){//ve se acabou as vidas
			if(!morreu){
				morreu = true;
				somDoJogo.pause();
				somDaMorte.play();
			}
			gameOver(window);
			continue;
		}
		if(Game.playerVenceu()){
			veceuJogo(window);
			continue;
		}

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
			vidas.setString("Vidas: " + vidasString);
			tempoString = to_string(contadorTotal);
			tempo.setString("Tempo: " + tempoString);
			window.draw(vidas);
			window.draw(tempo);
		}

		window.display();
	}

	return 0;
}
