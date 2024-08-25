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
	bool bateu, podeMover;

public:

	Player(sf::RenderWindow &window) :
			window(window) {
		texturePlayer.loadFromFile("assets/Player.png");
		//hitbox
		hitbox.left = 0;
		hitbox.top = 0;
		hitbox.height = 16;
		hitbox.width = 7;
		//-----
		player.setTexture(texturePlayer);
		player.setTextureRect(hitbox);
		velX = 0;
		velY = 0;
		posX = 360;
		posY = 150;
		player.setScale(3, 3);
		player.setOrigin(16, 16); //metade do tamanho do player;
		player.setPosition(posX, posY);
		bateu = false;
		podeMover = true;
	}

	/*bool testaColisaoChao(sf::RectangleShape chao) {
	 sf::FloatRect hitboxChao = chao.getGlobalBounds();

	 if (playerBounds().intersects(hitboxChao)) {
	 velY = 0;
	 return true;
	 }
	 return false;
	 }*/

	/*bool testaColisaoParede(sf::RectangleShape parede) {
	 sf::FloatRect hitboxParede = parede.getGlobalBounds();
	 if (playerBounds().intersects(hitboxParede)) {
	 bateu = true;
	 player.move(-velX, 0);
	 return true;
	 }
	 return false;
	 }*/

	void moverX(sf::Event evento) {

		if (podeMover) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				velX = -5;
				posX += velX;
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				velX = 5;
				posX += -velX;
			} else {
				velX = 0;
			}
			player.move(velX, 0);
		}else{
			player.move(-velX, 0);
		}
	}

	void moverY() {
		player.move(0, velY);
	}

	void setGravity(int x) {
		this->velY = x;
		posY += velY;
		player.move(velX, velY);
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

