/*
 * Bomba.hpp
 *
 *  Created on: 25 de ago. de 2024
 *      Author: Rafael
 */

#ifndef BOMBA_HPP_
#define BOMBA_HPP_
#include <SFML/Graphics.hpp>
#include "Cenario.hpp"
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
	bool bateu;

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
		posY = 90;
		escala = 2.5;
		bombaNormal.setScale(escala, escala);
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
		bombaNormal.move(velX, velY);
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

	void testaColisaoChao(Chao chao) {
		sf::FloatRect hitboxChao = chao.getChao().getGlobalBounds();

		if (getBombaNormalBounds().intersects(hitboxChao)) {
			moverX();
		} else {
			moverY();
		}

		/*if (getBombaEspecialBounds().intersects(hitboxChao)) {
		 velY = 0;
		 } else {
		 velY = 1;
		 }*/
	}

	void testaColisaoParede(Parede paredes) {
		sf::FloatRect hitboxParede1 = paredes.getParede1().getGlobalBounds();
		sf::FloatRect hitboxParede2 = paredes.getParede2().getGlobalBounds();
		if (getBombaNormalBounds().intersects(hitboxParede1)) {
			inverteVelX();
		}

		if (getBombaNormalBounds().intersects(hitboxParede2)) {
			inverteVelX();
		}
		/*if (getBombaEspecialBounds().intersects(hitboxParede)) {

		 bombaEspecial.move(-velX, 0);
		 }*/
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

	/*sf::Sprite getBombaEspecial() {
	 return bombaEspecial;
	 }*/

	float getVelX() const {
		return velX;
	}
};
#endif

