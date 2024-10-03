//============================================================================
// Nome        : King Kong Game
// Autores     : Lucas Lenz, Pedro Lucas e Rafael Torres
//============================================================================

#include <SFMl/Graphics.hpp>
#include <SFML/audio.hpp>
#include <iostream>
#include "Player.hpp"
#include "Bomba.hpp"
#include "Cenario.hpp"

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
			tela.setFillColor(sf::Color::Magenta);
		}
		if(cont % 20 > 10){
			tela.setFillColor(sf::Color::Blue);
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
	//fimDeJogo.setOrigin(50, 50);
	fimDeJogo.setFillColor(sf::Color::White);

	//esses numeros no position sao os unicos que deixa o texto no meio, nn sei a logica
	fimDeJogo.setPosition(window.getSize().x/2 - 275, window.getSize().y/2 - 100);
	fimDeJogo.setString("Game Over");



	window.clear();
	window.draw(fimDeJogo);
	window.display();

}

int main(int argc, char **argv) {
	setbuf(stdout, NULL);
	sf::VideoMode video(1000, 600);
	sf::RenderWindow window(video, "King Kong");
	sf::Event evento;
	window.setFramerateLimit(50);

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
	sf::Text vidas;
	vidas.setFont(fonte);
	vidas.setCharacterSize(30);
	vidas.setOrigin(15, 15);
	vidas.setFillColor(sf::Color::Red);
	vidas.setPosition(45*(window.getSize().x / 100), 5*(window.getSize().y / 100));

	//Elementos
	Player player(window);
	Princesa princesa(window);
	Cenario cenario(player, princesa, &window);

	while (window.isOpen()) {

		while (window.pollEvent(evento)) {
			if (evento.type == sf::Event::Closed) {
				window.close();
			}
		}
		window.clear();

		//Desenha cenario e fundo
		window.draw(fundo);

		if(player.getPerdeuVida()){//ve se ele perdeu vida pra rodar a animacao
			animacaoMorte(window);
			player.setPerdeuVida(false);
			continue;
		}
		if(player.getVidas() <= 0){//ve se acabou as vidas
			gameOver(window);
			sf::SoundBuffer bufferSomDaMorte;
				sf::Sound somDaMorte;
				bufferSomDaMorte.loadFromFile("assets/SomDeGameOver.ogg");
						somDaMorte.setBuffer(bufferSomDaMorte);
						somDaMorte.play();
			continue;
		}

		cenario.desenhaCenario(&window); //colisoes dentro dessa funcao

		//movimenta elementos se o kong tiver iniciado
		if (cenario.getIniciouKong()) {
			player.moverY(evento);
			player.moverX(evento);
			//cenario.moverBombas();
		}

		string vidasString = to_string(player.getVidas());
		vidas.setString("Vidas: " + vidasString);
		window.draw(vidas);

		window.display();
	}

	return 0;
}
