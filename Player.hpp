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
		velY = 1;
		posX = 360;
		posY = 440;
		player.setScale(5, 5);
		player.setOrigin(16, 16); //metade do tamanho do player;
		player.setPosition(posX, posY);
		bateu = false;
	}

	sf::FloatRect playerBounds() {
		return player.getGlobalBounds();
	}

	void setGravity(int x) {
		this->velY = x;
		posY += velY;
		player.move(velX, velY);
	}

	void testaColisaoChao(Chao chao) {
		sf::FloatRect hitboxChao = chao.getChao().getGlobalBounds();

		if (playerBounds().intersects(hitboxChao)) {
			velY = 0;
		} else {
			velY = 1;
		}
	}
	void testaColisaoParede(Parede parede) {
		sf::FloatRect hitboxParede = parede.getParede().getGlobalBounds();
		if (playerBounds().intersects(hitboxParede)) {
			bateu = true;
			player.move(-velX, 0);
		} else {
			bateu = false;
		}
	}

	void move(sf::Event evento) {
		if (bateu) {
			velX = 0;
		} else {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				velX = -3;
				posX += velX;
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				velX = 3;
				posX += velX;
			} else {
				velX = 0;
			}
		}
		player.move(velX, velY);
	}

	sf::Sprite getPlayer() {
		return player;
	}
};
#endif
