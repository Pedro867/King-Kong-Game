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
	bool bateu, escada, cair;

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
		velX = 8;
		velY = 2;
		posX = 600;
		posY = 550;
		escala = 2.5;
		bombaNormal.setScale(escala, escala);
		bombaNormal.setOrigin(16, 16); //metade do tamanho do player;
		bombaNormal.setPosition(posX, posY);
		bateu = false;
		cair = false;
		escada = false;
	}

	sf::FloatRect getBombaNormalBounds() {
		return bombaNormal.getGlobalBounds();
	}

	void mover() {

		if (bateu == true) {
			bombaNormal.move(velX, 0);
		} else {
			bombaNormal.move(0, velY);

		}
	}

	void moverY() {
			bombaNormal.move(0, velY);

	}

	void moverX() {

			bombaNormal.move(velX, 0);

	}

	void inverteVelX() {
		velX = -velX;
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



	void DescerEscada(){

		if(escada == true){
			bateu = false;
			mover();
		}else{
			escada = false;
		}
	}
	void setPodeDescer(int valor) {
		if (valor == 1) {
			escada = true;
		} else if (valor == 0) {
			escada = false;
		}
	}
	void setPosXPosY(float x, float y) {
		posX = x;
		posY = y;
		bombaNormal.setPosition(posX, posY);
	}
};
#endif

