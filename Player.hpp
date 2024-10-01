/*
 * Player.hpp
 *
 *  Created on: 25 de ago. de 2024
 *      Author: Rafael
 */

#ifndef PLAYER_HPP_
#define PLAYER_HPP_
#include <SFML/Graphics.hpp>
//#include "Chao.hpp"
//#include "Parede.hpp"
//#include "Cenario.hpp"
#include "Bomba.hpp"
#include <iostream>

using namespace std;

class Player {
private:

	sf::IntRect hitbox;
	sf::Sprite player;
	sf::Texture texturePlayer;
	sf::RenderWindow &window;
	float velX, velY;
	float posX, posY;
	float escala;
	bool bateu, caiu, podeMover, podeSubir, subindo, moveuEsquerda;
	int gravity, vidas, acabouDePular;

	sf::SoundBuffer bufferPulo;
	sf::Sound somPulo;
public:

	Player(sf::RenderWindow &window);
	void moverX(sf::Event evento);
	void moverY(sf::Event evento);
	void setPodeMover(int valor);
	void setPodeSubir(int valor);
	void setCaiu(bool caiu);
	void setBateu(bool bateu);
	void setVelY(float vy);
	void setVelX(float vx);
	void setLayer(float alturaLinha, float larguraColuna);
	void setPosXPosY(float x, float y);
	float getVelY();
	float getVelX();
	int getVidas();
	void perdeuVidas();
	sf::Sprite getPlayer();
	sf::FloatRect bounds();
	void GameOver(float alturaLinha);
	bool colideBomba(Bomba &bomba);
	bool gameOver();
};

	Player::Player(sf::RenderWindow &window) :
			window(window) {
		texturePlayer.loadFromFile("assets/playerParado.png");
		//hitbox
		hitbox.left = hitbox.top = 0;
		hitbox.height = 16;
		hitbox.width = 7;
		//-----
		player.setTexture(texturePlayer);
		player.setTextureRect(hitbox);
		velX = 0;
		velY = 0;
		posX = 0;
		posY = 0;
		vidas = 3;
		escala = window.getSize().y / 275.0f; //escala responsiva
		gravity = window.getSize().y / 600.0f;
		player.setScale(escala, escala);
		player.setOrigin(hitbox.width / 2, hitbox.height / 2); //metade do tamanho do player;
		player.setPosition(posX, posY);
		bateu = false;
		caiu = false;
		podeMover = true;
		podeSubir = false;
		moveuEsquerda = false;
		subindo = false;
		acabouDePular = 0;
		//essa aqui bugou tudo, mas eh necessaria
		//pro player nao poder mover na escada

		bufferPulo.loadFromFile("assets/SomPulo.ogg");
		somPulo.setBuffer(bufferPulo);
	}

	void Player::moverX(sf::Event evento) {

		player.setScale(escala, escala);
		if (podeMover) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {

				velX = -5;
				posX += velX;

				hitbox.width = 9;
				player.setTextureRect(hitbox);

				player.setOrigin(hitbox.width / 2, hitbox.height / 2);
				texturePlayer.loadFromFile("assets/playerCorrendoEsquerda.png");
				moveuEsquerda = true;

			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {

				velX = 5;
				posX += -velX;

				hitbox.width = 9;
				player.setTextureRect(hitbox);

				player.setOrigin(hitbox.width / 2, hitbox.height / 2);
				texturePlayer.loadFromFile("assets/playerCorrendoDireita.png");
				moveuEsquerda = false;

			} else {
				velX = 0;

				hitbox.width = 7;
				player.setTextureRect(hitbox);

				player.setOrigin(hitbox.width / 2, hitbox.height / 2);
				texturePlayer.loadFromFile("assets/playerParado.png");

				if (moveuEsquerda) {
					player.setScale(-escala, escala);
				} else {
					player.setScale(escala, escala);
				}

			}
			player.move(velX, 0);
		} else {
			player.move(-velX, 0);
		}
	}

	void Player::moverY(sf::Event evento) {

		if (caiu == true && podeSubir == false) {
			//subindo = false;
			if(acabouDePular > 0){
				player.move(0, gravity/3);
				acabouDePular--;
			}else{
				player.move(0, gravity);
			}
		}
		if (podeSubir == true) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				//subindo = true;
				velY = -gravity*2;
				player.move(0, velY);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				//subindo = true;
				velY = gravity*2;
				player.move(0, velY);
			}
		}
		if (podeSubir == false && caiu == false) {
			//subindo = false;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				velY = window.getSize().y / 30.0f; //pulo responsivo
				velY = -velY;
				player.move(0, velY);
				acabouDePular = 10;
				somPulo.play();
			}
		}
	}

	void Player::setPodeMover(int valor) {
		if (valor == 1) {
			podeMover = true;
		} else if (valor == 0) {
			podeMover = false;
		}
	}

	//por enquanto sao iguais
	void Player::setPodeSubir(int valor) {
		if (valor == 1) {
			podeSubir = true;
		} else if (valor == 0) {
			podeSubir = false;
		}
	}

	void Player::setCaiu(bool caiu) {
		this->caiu = caiu;
	}

	void Player::setBateu(bool bateu) {
		this->bateu = bateu;
	}

	void Player::setVelY(float vy) {
		this->velY = vy / 3.0;
	}

	void Player::setVelX(float vx) {
		velX = vx;
	}

	inline void Player::setLayer(float alturaLinha, float larguraColuna) {
	float altura, largura;
	altura = (alturaLinha * 5) - 16;
	largura = 20 * larguraColuna;
	setPosXPosY(largura, altura);
	}

	void Player::setPosXPosY(float x, float y) {
	//Funcao para setar o andar
	posX = x;
	posY = y;
	player.setPosition(posX, posY);
	}

	float Player::getVelY() {
		return velY;
	}

	float Player::getVelX() {
		return velX;
	}

	int Player::getVidas(){
		return vidas;
	}

	void Player::perdeuVidas(){
		this->vidas--;
	}

	sf::Sprite Player::getPlayer() {
		return player;
	}

	sf::FloatRect Player::bounds() {
		return player.getGlobalBounds();
	}

	void Player::GameOver(float alturaLinha) {
		player.move(0, velY);
}

#endif /* PLAYER_HPP_ */
