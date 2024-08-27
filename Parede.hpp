/*
 * Parede.hpp
 *
 *  Created on: 27 de ago. de 2024
 *      Author: Rafael
 */

#ifndef PAREDE_HPP_
#define PAREDE_HPP_

class Parede{
private:
	sf::RectangleShape parede1;
	sf::RectangleShape parede2;
	sf::Vector2<float> dimensoesParedes;

public:
	
	//Parede();
	void iniciarParede(float larguraColuna, float alturaLinha, int i, sf::RenderWindow *window);
	void draw(sf::RenderWindow *window);
};

inline void Parede::iniciarParede(float larguraColuna, float alturaLinha, int i, sf::RenderWindow *window){
	this->dimensoesParedes.x = larguraColuna;
	this->dimensoesParedes.y = alturaLinha;

	if(i == 0){
	 //nao tem parede na linha 0
	}
	if (i == 1) {
		this->parede1.setSize(dimensoesParedes);
		this->parede1.setPosition(larguraColuna * 4, alturaLinha * i);
		this->parede1.setFillColor(sf::Color::Magenta);

		this->parede2.setSize(dimensoesParedes);
		this->parede2.setOrigin(dimensoesParedes.x, 0);
		this->parede2.setPosition(window->getSize().x - larguraColuna * 4, alturaLinha * i); //desenha a parede na 5 coluna
		this->parede2.setFillColor(sf::Color::Magenta);
	}
	if (i == 2) {
		this->parede1.setSize(dimensoesParedes);
		this->parede1.setPosition(larguraColuna * 3, alturaLinha * i);
		this->parede1.setFillColor(sf::Color::Magenta);

		this->parede2.setSize(dimensoesParedes);
		this->parede2.setOrigin(dimensoesParedes.x, 0);
		this->parede2.setPosition(window->getSize().x - larguraColuna * 3, alturaLinha * i); //desenha a parede na 5 coluna
		this->parede2.setFillColor(sf::Color::Magenta);
	}
	if (i > 2 && i < 9) {
		this->parede1.setSize(dimensoesParedes);
		this->parede1.setPosition(larguraColuna * 2, alturaLinha * i);
		this->parede1.setFillColor(sf::Color::Magenta);

		this->parede2.setSize(dimensoesParedes);
		this->parede2.setOrigin(dimensoesParedes.x, 0);
		this->parede2.setPosition(window->getSize().x - larguraColuna * 2, alturaLinha * i); //desenha a parede na 5 coluna
		this->parede2.setFillColor(sf::Color::Magenta);
	}
}

inline void Parede::draw(sf::RenderWindow *window) {
	window->draw(parede1);
	window->draw(parede2);
}

#endif /* PAREDE_HPP_ */
