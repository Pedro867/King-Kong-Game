/*
 * Chao.hpp
 *
 *  Created on: 27 de ago. de 2024
 *      Author: Rafael
 */

#ifndef CHAO_HPP_
#define CHAO_HPP_

#include "Cenario.hpp"

class Chao{
private:

	sf::RectangleShape chao;
	sf::Vector2<float> dimensoesChao;
	sf::Sprite buraco1;
	sf::Sprite buraco2;
	sf::FloatRect hitboxBuraco;
	sf::Vector2<float> dimensoesBuraco;
	sf::Texture texturaBuraco;

public:

	void iniciarChao(float larguraColuna, float alturaLinha, int i);
	void iniciarBuraco(float larguraColuna, float alturaLinha, int i);
	void drawChao(sf::RenderWindow *window);
	void drawBuraco(sf::RenderWindow *window);
	sf::RectangleShape getChao();
	sf::Sprite getBuraco1();
	sf::Sprite getBuraco2();
};

inline void Chao::iniciarChao(float larguraColuna, float alturaLinha, int i) {
	if(i == 0 || i == 1){
		this->dimensoesChao.x = 32 * larguraColuna;
		this->dimensoesChao.y = 5.0f;
		this->chao.setSize(dimensoesChao);
		this->chao.setPosition(larguraColuna * 4, alturaLinha + alturaLinha * i); //desenha no chao da linha na 5 coluna
	}
	if(i == 2){
		this->dimensoesChao.x = 34 * larguraColuna; //só muda aqui
		this->dimensoesChao.y = 5.0f;
		this->chao.setSize(dimensoesChao);
		this->chao.setPosition(larguraColuna * 3, alturaLinha + alturaLinha * i); //desenha no chao da linha na 5 coluna
	}
	if(i > 2 && i < 9){
		this->dimensoesChao.x = 36 * larguraColuna; //só muda aqui
		this->dimensoesChao.y = 5.0f;
		this->chao.setSize(dimensoesChao);
		this->chao.setPosition(larguraColuna * 2, alturaLinha + alturaLinha * i); //desenha no chao da linha na 5 coluna
	}

	this->chao.setFillColor(sf::Color::Magenta);
}

inline void Chao::iniciarBuraco(float larguraColuna, float alturaLinha, int i){
	this->dimensoesBuraco.x = larguraColuna / 512.00f; //x = largura / 512 logo x . 512 = largura
	this->dimensoesBuraco.y = 5.0f / 512.00f; //y = 512 / 5 logo x . 512 = 5

	hitboxBuraco.left = hitboxBuraco.top = 0;
	hitboxBuraco.height = 16;
	hitboxBuraco.width = 7;

	this->texturaBuraco.loadFromFile("assets/background.png");
	this->buraco1.setTexture(texturaBuraco);
	this->buraco1.setScale(dimensoesBuraco);

	this->buraco2.setTexture(texturaBuraco);
	this->buraco2.setScale(dimensoesBuraco);

	if(i == 2){
		this->buraco1.setPosition(larguraColuna * 13, alturaLinha + alturaLinha * i);
		this->buraco2.setPosition(larguraColuna * 26, alturaLinha + alturaLinha * i);
	}
	if(i == 4){
		this->buraco1.setPosition(larguraColuna * 10, alturaLinha + alturaLinha * i);
		this->buraco2.setPosition(larguraColuna * 29, alturaLinha + alturaLinha * i);
	}
	if(i == 6){
		this->buraco1.setPosition(larguraColuna * 14, alturaLinha + alturaLinha * i);
		this->buraco2.setPosition(larguraColuna * 25, alturaLinha + alturaLinha * i);
	}
}

inline void Chao::drawChao(sf::RenderWindow *window){
	window->draw(this->chao);
}

inline void Chao::drawBuraco(sf::RenderWindow *window){

	window->draw(this->buraco1);
	window->draw(this->buraco2);
}

inline sf::RectangleShape Chao::getChao() {
	return chao;
}

inline sf::Sprite Chao::getBuraco1() {
	return buraco1;
}

inline sf::Sprite Chao::getBuraco2() {
	return buraco2;
}

#endif /* CHAO_HPP_ */
