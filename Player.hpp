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
	bool bateu, podeMover, moveuEsquerda;

public:

	Player(sf::RenderWindow &window) :
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
		posY = 190;
		escala = 2.5;
		player.setScale(escala, escala);
		player.setOrigin(hitbox.width / 2, hitbox.height / 2); //metade do tamanho do player;
		player.setPosition(posX, posY);
		bateu = false;
		podeMover = true;
		moveuEsquerda = false;
	}

	void moverX(sf::Event evento) {

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
				}else{
					player.setScale(escala, escala);
				}

			}
			player.move(velX, 0);
		} else {
			player.move(-velX, 0);
		}
	}

	void moverY() {
		player.move(0, velY);
	}

	void setVelY(float vy) {
		this->velY = vy;
	}

	float getVelX() {
		return velX;
	}

	float getVelY() {
		return velY;
	}

	void setVelX(int vx) {
		velX = vx;
	}

	void setPodeMover(int valor) {
		if (valor == 1) {
			podeMover = true;
		} else if (valor == 0) {
			podeMover = false;
		}
	}

	sf::Sprite getPlayer() {
		return player;
	}

	sf::FloatRect playerBounds() {
		return player.getGlobalBounds();
	}
};
#endif /* PLAYER_HPP_ */

