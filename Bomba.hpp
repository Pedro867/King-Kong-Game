#ifndef BOMBA_HPP_
#define BOMBA_HPP_
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include <iostream>

using namespace std;

class Bomba {
private:

	sf::IntRect hitbox;
	sf::Sprite bombaNormal;
	//Projeto futuro sf::Sprite bombaEspecial;
	sf::Texture texturaBombaNormal;
	//Projeto futuro sf::Texture texturaBombaEspecial;

	float velX, velY;
	float posX, posY;
	float escala;
	bool bateu, escada, cair;

	int qntMaxBombaNormal;

public:

	void iniciarBomba(sf::RenderWindow *window);
	void mover();
	void moverY();
	void moverX();
	void inverteVelX();
	void setPosXPosY(float x, float y);
	void setPodeMover(int valor);
	void setPodeDescer(int valor);
	void setLayer(float alturaLinha, float larguraColuna);
	void descerEscada();
	float getVelX();
	sf::FloatRect getBombaNormalBounds();
	sf::Sprite getBombaNormal();
	bool olhaSePodeSpawnarNormal(float alturaLinha, int qntAtualBombaNormal);
	void spawnBombaNormal(float alturaLinha, float larguraColuna);

};

void Bomba::iniciarBomba(sf::RenderWindow *window){
	texturaBombaNormal.loadFromFile("assets/bomba.png");
	//hitbox
	hitbox.left = 0;
	hitbox.top = 0;
	hitbox.height = 11.5;//menorque 13 pra melhorar a gameplay
	hitbox.width = 13;
	//fim da hitbox
	bombaNormal.setTexture(texturaBombaNormal);
	velX = window->getSize().x / 250.0f; //velocidade responsiva
	velY = window->getSize().y / 200.0f; //imita a gravidade
	posX = 600;
	posY = 550;
	escala = window->getSize().y / 400.0f; //escala responsiva
	bombaNormal.setScale(escala, escala);
	bombaNormal.setOrigin(16, 16); //metade do tamanho do player;
	bombaNormal.setPosition(posX, posY);
	bateu = false;
	cair = false;
	escada = false;
	qntMaxBombaNormal = 10;
}

void Bomba::mover() {
	if (bateu == true) {
		bombaNormal.move(velX, 0);
		posX = bombaNormal.getPosition().x + velX;
	} else {
		bombaNormal.move(0, velY);
		posY = bombaNormal.getPosition().y + velY;
	}
}

void Bomba::moverY() {
	bombaNormal.move(0, velY);
}

void Bomba::moverX() {
	bombaNormal.move(velX, 0);
}

void Bomba::inverteVelX() {
	velX = -velX;
}

void Bomba::setPosXPosY(float x, float y) {
	posX = x;
	posY = y;
	bombaNormal.setPosition(posX, posY);
}

void Bomba::setPodeMover(int valor) {
	if (valor == 1) {
		bateu = true;
	} else if (valor == 0) {
		bateu = false;
	}
}

void Bomba::setPodeDescer(int valor) {
	if (valor == 1) {
		escada = true;
		descerEscada();
	} else if (valor == 0) {
		escada = false;
	}
}

inline void Bomba::setLayer(float alturaLinha, float larguraColuna) {
	float altura, largura;
	altura = (alturaLinha * 2) - 13;
	largura = 7 * larguraColuna - 13;
	setPosXPosY(largura, altura);
}

void Bomba::descerEscada() {
	if (escada == true) {
		bateu = false;
		mover();
	} else {
		escada = false;
	}
}

float Bomba::getVelX() {
	return velX;
}

sf::FloatRect Bomba::getBombaNormalBounds() {
	return bombaNormal.getGlobalBounds();
}

sf::Sprite Bomba::getBombaNormal() {
	return bombaNormal;
}

bool Bomba::olhaSePodeSpawnarNormal(float alturaLinha, int qntAtualBombaNormal) {
	if((posY > alturaLinha) && (posY < (3 * alturaLinha))){
		return false;
	}
	else if(qntAtualBombaNormal < qntMaxBombaNormal){
		return true;
	}
}

void Bomba::spawnBombaNormal(float alturaLinha, float larguraColuna) {
	setLayer(alturaLinha, larguraColuna);
}

#endif

