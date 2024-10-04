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
	bool bateuNoChao, escada, cair, descerHabilitado;

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
	void setDescerHabilitado(bool descerHabilitado);
	void setLayer(float alturaLinha, float larguraColuna);
	void descerEscada();
	float getVelX();
	float getLayer(float alturaLinha);
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
	velY = window->getSize().y / 200.0f; //igual a gravidade
	posX = 600;
	posY = 550;
	escala = window->getSize().y / 400.0f; //escala responsiva
	bombaNormal.setScale(escala, escala);
	bombaNormal.setOrigin(16, 16); //metade do tamanho do player;
	bombaNormal.setPosition(posX, posY);
	bateuNoChao = false;
	cair = false;
	escada = false;
	descerHabilitado = false;
	qntMaxBombaNormal = 10;
}

void Bomba::mover() {
	if (bateuNoChao == true && descerHabilitado == false) {
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
		bateuNoChao = true;
	} else if (valor == 0) {
		bateuNoChao = false;
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

void Bomba::setDescerHabilitado(bool descerHabilitado) {
		this->descerHabilitado = descerHabilitado;
}

void Bomba::setLayer(float alturaLinha, float larguraColuna) {
	float altura, largura;
	altura = (alturaLinha * 2);
	largura = 7 * larguraColuna;
	setPosXPosY(largura, altura);
}

void Bomba::descerEscada() {
	if (escada == true) {
		bateuNoChao = false;
		mover();
	} else {
		escada = false;
	}
}

float Bomba::getVelX() {
	return velX;
}

float Bomba::getLayer(float alturaLinha) {
	this->posY = bombaNormal.getPosition().y;
	//Mudei a variável para int, assim fica mais fácil tratar
	int layer = posY / alturaLinha;
	layer = 10 - layer;
	return layer;
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
	return false;
}

void Bomba::spawnBombaNormal(float alturaLinha, float larguraColuna) {
	setLayer(alturaLinha, larguraColuna);
}

#endif
