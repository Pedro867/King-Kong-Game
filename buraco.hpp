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

	vector<sf::Sprite> buraco;
	sf::FloatRect hitboxBuraco;
	sf::Vector2<float> dimensoesBuraco;
	sf::Texture texturaBuraco;

public:

	Buraco();
	void iniciarBuraco(float larguraColuna, float alturaLinha, int i);
	void drawBuraco(sf::RenderWindow *window);
	sf::Sprite getBuraco1();
	sf::Sprite getBuraco2();
};

inline Buraco::Buraco(){
	buraco.resize(2);
}

inline void Buraco::iniciarBuraco(float larguraColuna, float alturaLinha, int i){
	this->dimensoesBuraco.x = larguraColuna / 512.00f; //x = largura / 512 logo x . 512 = largura
	this->dimensoesBuraco.y = 5.0f / 512.00f; //y = 512 / 5 logo x . 512 = 5

	//hitboxBuraco.left = hitboxBuraco.top = 0;
	//hitboxBuraco.height = 16;
	//hitboxBuraco.width = 7;

	this->texturaBuraco.loadFromFile("assets/background.png");

	for(int cont = 0; cont < 2; cont++){
		buraco[cont].setTexture(texturaBuraco);
		buraco[cont].setScale(dimensoesBuraco);
	}

	if(i != 3 && i != 5 && i != 7){
		this->buraco[0].setScale(0, 0);
		this->buraco[1].setScale(0, 0);
	}
	if(i == 3){
		this->buraco[0].setPosition(larguraColuna * 14, alturaLinha + alturaLinha * (9 - i));
		this->buraco[1].setPosition(larguraColuna * 25, alturaLinha + alturaLinha * (9 - i));
	}
	if(i == 5){
		this->buraco[0].setPosition(larguraColuna * 10, alturaLinha + alturaLinha * (9 - i));
		this->buraco[1].setPosition(larguraColuna * 29, alturaLinha + alturaLinha * (9 - i));
	}
	if(i == 7){
		this->buraco[0].setPosition(larguraColuna * 13, alturaLinha + alturaLinha * (9 - i));
		this->buraco[1].setPosition(larguraColuna * 26, alturaLinha + alturaLinha * (9 - i));
	}
}

inline void Buraco::drawBuraco(sf::RenderWindow *window){

	window->draw(buraco[0]);
	window->draw(buraco[1]);
}

inline sf::Sprite Buraco::getBuraco1() {
	return buraco[0];
}

inline sf::Sprite Buraco::getBuraco2() {
	return buraco[1];
}

#endif /* BURACO_HPP_ */
