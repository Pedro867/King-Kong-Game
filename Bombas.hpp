#ifndef BOMBAS_HPP_
#define BOMBAS_HPP_
#include <SFML/Graphics.hpp>
#include "Chao.hpp"
#include "Parede.hpp"
#include "Player.hpp"
#include <iostream>

using namespace std;


class Bombas {
private:
	sf::IntRect hitbox;
	sf::Sprite bombaNormal;
	//Projeto futuro sf::Sprite bombaEspecial;
	sf::Texture texturaBombaNormal;
	//Projeto futuro sf::Texture texturaBombaEspecial;
	sf::RenderWindow &window;
	float velX, velY;
	float posX, posY;
	bool bateu;
public:
	Bombas(sf::RenderWindow &window) :
			window(window) {
		texturaBombaNormal.loadFromFile("assets/bomba.png");
		//hitbox
		hitbox.left = 0;
		hitbox.top = 0;
		hitbox.height = 13;
		hitbox.width = 13;
		//fim da hitbox
		bombaNormal.setTexture(texturaBombaNormal);
		velX = 5;
		velY = 1;
		posX = 200;
		posY = 100;
		bombaNormal.setScale(5, 5);
		bombaNormal.setOrigin(16, 16); //metade do tamanho do player;
		bombaNormal.setPosition(posX, posY);
		bateu = false;
	}
	sf::FloatRect getBombaNormalBounds() {
		return bombaNormal.getGlobalBounds();
	}
	/*Projeto futuro sf::FloatRect getBombaEspecialBounds() {
		return bombaEspecial.getGlobalBounds();
	}*/
	void mover() {
		bombaNormal.move(velX,velY);
	}
	bool testaColisaoChao(Chao chao) {
		sf::FloatRect hitboxChao = chao.getChao().getGlobalBounds();

		if (getBombaNormalBounds().intersects(hitboxChao)) {
			return true;
		} else {
			return false;
		}
		/*if (getBombaEspecialBounds().intersects(hitboxChao)) {
			velY = 0;
		} else {
			velY = 1;
		}*/
	}
	void setVelY(float x){
		velY = x;

	}
	void setVel(float x, float y){
			velY = y;
			velX = x;

		}
	bool testaColisaoParede(Parede parede) {
		sf::FloatRect hitboxParede = parede.getParede().getGlobalBounds();
		if (getBombaNormalBounds().intersects(hitboxParede)) {
return true;
		}
		return false;
		/*if (getBombaEspecialBounds().intersects(hitboxParede)) {

			bombaEspecial.move(-velX, 0);
		}*/
	}
	sf::Sprite getBombaNormal() {
		return bombaNormal;
	}
	/*sf::Sprite getBombaEspecial() {
		return bombaEspecial;
	}*/

	float getVelX() const {
		return velX;
	}
};
#endif

