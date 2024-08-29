#ifndef BOMBA_HPP_
#define BOMBA_HPP_
#include <SFML/Graphics.hpp>
#include "Player.hpp"
//#include "Chao.hpp"
//#include "Parede.hpp"
#include <iostream>

using namespace std;

class Bomba {
private:

	sf::IntRect hitbox;
	sf::Sprite bombaNormal;
	//Projeto futuro sf::Sprite bombaEspecial;
	sf::Texture texturaBombaNormal;
	//Projeto futuro sf::Texture texturaBombaEspecial;
	sf::RenderWindow &window;
	float velX, velY;
	float posX, posY;
	float escala;
	bool bateu = false;

public:

	Bomba(sf::RenderWindow &window) :
			window(window) {
		texturaBombaNormal.loadFromFile("assets/bomba.png");
		//hitbox
		hitbox.left = 0;
		hitbox.top = 0;
		hitbox.height = 13;
		hitbox.width = 13;
		//fim da hitbox
		bombaNormal.setTexture(texturaBombaNormal);
		velX = 2;
		velY = 1;
		posX = 600;
		posY = 190;
		escala = 2.5;
		bombaNormal.setScale(escala, escala);
		bombaNormal.setOrigin(16, 16); //metade do tamanho do player;
		bombaNormal.setPosition(posX, posY);
		bateu = false;
	}

	sf::FloatRect getBombaNormalBounds() {
		return bombaNormal.getGlobalBounds();
	}

	void mover() {

		if(bateu == true) {
			bombaNormal.move(velX, 0);
		}else{
			bombaNormal.move(0, velY);

		}
	}

	void moverY() {
		if (bateu == true) {
			bombaNormal.move(0, velY);
		}
	}

	void moverX() {
		if (bateu == true) {
			bombaNormal.move(velX, 0);
		}
	}

	void inverteVelX() {
		velX = -velX;
	}

	void setVelY(float x) {
		velY = x;

	}

	void setVel(float x, float y) {
		velY = y;
		velX = x;

	}

	sf::Sprite getBombaNormal() {
		return bombaNormal;
	}

	float getVelX() const {
		return velX;
	}
	void setPodeMover(int valor) {
		if (valor == 1) {
			bateu = true;
		} else if (valor == 0) {
			bateu = false;
		}
	}

};
#endif

