/*
 * buraco.hpp
 *
 *  Created on: 21 de set. de 2024
 *      Author: Rafael
 */

#ifndef BURACO_HPP_
#define BURACO_HPP_

class Buraco{
private:

	sf::Sprite buraco1;
	sf::Sprite buraco2;
	sf::FloatRect hitboxBuraco;
	sf::Vector2<float> dimensoesBuraco;
	sf::Texture texturaBuraco;

public:

	void iniciarBuraco(float larguraColuna, float alturaLinha, int i);
	void drawBuraco(sf::RenderWindow *window);
	sf::Sprite getBuraco1();
	sf::Sprite getBuraco2();
};

inline void Buraco::iniciarBuraco(float larguraColuna, float alturaLinha, int i){
	this->dimensoesBuraco.x = larguraColuna / 512.00f; //x = largura / 512 logo x . 512 = largura
	this->dimensoesBuraco.y = 5.0f / 512.00f; //y = 512 / 5 logo x . 512 = 5

	//hitboxBuraco.left = hitboxBuraco.top = 0;
	//hitboxBuraco.height = 16;
	//hitboxBuraco.width = 7;

	this->texturaBuraco.loadFromFile("assets/background.png");
	this->buraco1.setTexture(texturaBuraco);
	this->buraco1.setScale(dimensoesBuraco);

	this->buraco2.setTexture(texturaBuraco);
	this->buraco2.setScale(dimensoesBuraco);

	if(i == 3){
		this->buraco1.setPosition(larguraColuna * 14, alturaLinha + alturaLinha * (9 - i));
		this->buraco2.setPosition(larguraColuna * 25, alturaLinha + alturaLinha * (9 - i));
	}
	if(i == 5){
		this->buraco1.setPosition(larguraColuna * 10, alturaLinha + alturaLinha * (9 - i));
		this->buraco2.setPosition(larguraColuna * 29, alturaLinha + alturaLinha * (9 - i));
	}
	if(i == 7){
		this->buraco1.setPosition(larguraColuna * 13, alturaLinha + alturaLinha * (9 - i));
		this->buraco2.setPosition(larguraColuna * 26, alturaLinha + alturaLinha * (9 - i));
	}
}

inline void Buraco::drawBuraco(sf::RenderWindow *window){

	window->draw(this->buraco1);
	window->draw(this->buraco2);
}

inline sf::Sprite Buraco::getBuraco1() {
	return buraco1;
}

inline sf::Sprite Buraco::getBuraco2() {
	return buraco2;
}

#endif /* BURACO_HPP_ */
