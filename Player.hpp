#ifndef PLAYER_HPP_
#define PLAYER_HPP_
#include <SFML/Graphics.hpp>
#include "Chao.hpp"
#include "Parede.hpp"
#include <iostream>

using namespace std;

#define gravity 1

class Player {
private:

	sf::IntRect hitbox;
	sf::Sprite player;
	sf::Texture texturePlayer;
	sf::RenderWindow &window;
	float velX, velY;
	float posX, posY;
	bool bateu;

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
		velY = 2;
		posX = 360;
		posY = 10;
		player.setScale(3, 3);
		player.setOrigin(16, 16); //metade do tamanho do player;
		player.setPosition(posX, posY);
		bateu = false;
	}

	bool testaColisaoChao(sf::RectangleShape chao) {
		sf::FloatRect hitboxChao = chao.getGlobalBounds();

		if (playerBounds().intersects(hitboxChao)) {
			velY = 0;
			return true;
		}
		return false;
	}

	bool testaColisaoParede(sf::RectangleShape parede) {
		sf::FloatRect hitboxParede = parede.getGlobalBounds();
		if (playerBounds().intersects(hitboxParede)) {
			bateu = true;
			player.move(-velX, 0);
			return true;
		}
		return false;
	}

	void mover(sf::Event evento) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			velX = -3;
			posX += velX;
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			velX = 3;
			posX += velX;
		} else {
			velX = 0;
		}

		//cout << "Vy = " << velY<< endl;
		player.move(velX, velY);
	}

	void moverY(){
		player.move(0,velY);
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

	sf::Sprite getPlayer() {
		return player;
	}

	sf::FloatRect playerBounds() {
		return player.getGlobalBounds();
	}
};
#endif
