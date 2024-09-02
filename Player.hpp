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
	bool bateu, caiu, podeMover, podeSubir, moveuEsquerda;
	const int gravity = 5;

public:

	Player(sf::RenderWindow &window);
	void moverX(sf::Event evento);
	void moverY(sf::Event evento);
	void setPodeMover(int valor);
	void setPodeSubir(int valor);
	void setCaiu(bool caiu);
	void setVelY(float vy);
	void setVelX(float vx);
	float getVelY();
	float getVelX();
	sf::Sprite getPlayer();
	sf::FloatRect bounds();
	void setPosXPosY(float x, float y);
	void GameOver(float alturaLinha);
	bool colideBomba(Bomba &bomba);
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
		posX = 360;
		posY = 250;
		escala = 2.5;
		player.setScale(escala, escala);
		player.setOrigin(hitbox.width / 2, hitbox.height / 2); //metade do tamanho do player;
		player.setPosition(posX, posY);
		bateu = false;
		caiu = false;
		podeMover = true;
		podeSubir = false;
		moveuEsquerda = false;
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
			player.move(0, gravity);
		}
		if (podeSubir == true) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				velY = -5;
				player.move(0, velY);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				velY = 5;
				player.move(0, velY);
			}
		}
		if (podeSubir == false) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				velY = -5;
				player.move(0, velY);
				//player.move(0, gravity);
			}
		} else {
			velY = 0;
			player.move(0, velY);
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

	void Player::setVelY(float vy) {
		this->velY = vy / 3.0;
	}

	void Player::setVelX(float vx) {
		velX = vx;
	}

	float Player::getVelY() {
		return velY;
	}

	float Player::getVelX() {
		return velX;
	}

	sf::Sprite Player::getPlayer() {
		return player;
	}

	sf::FloatRect Player::bounds() {
		return player.getGlobalBounds();
	}

	void Player::setPosXPosY(float x, float y) {
		//Funcao para setar o andar
		posX = x;
		posY = y;
		player.setPosition(posX, posY);
	}

	void Player::GameOver(float alturaLinha) {
		float queda = 0;
		while (queda < alturaLinha) {
			player.move(0, velY);
			queda += velY;
		}

}

bool Player::colideBomba(Bomba &bomba) {
	sf::FloatRect hitboxPlayer = bounds();
	sf::FloatRect hitboxBomba = bomba.getBombaNormalBounds();
	if(hitboxPlayer.intersects(hitboxBomba)){
		cout << "BATEU" << endl;
	}
	return true;
}

#endif /* PLAYER_HPP_ */
