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
	vector<sf::RectangleShape> parede;
	sf::Vector2<float> dimensoesParedes;

public:
	
	Parede();
	void iniciarParede(float larguraColuna, float alturaLinha, int i, sf::RenderWindow *window);
	void paredes1a6andar(int i, sf::RenderWindow *window, float larguraColuna, float alturaLinha);
	void paredes7andar(int i, sf::RenderWindow *window, float larguraColuna, float alturaLinha);
	void paredes8andar(int i, sf::RenderWindow *window, float larguraColuna, float alturaLinha);
	void draw(sf::RenderWindow *window);
	sf::RectangleShape getParede1();
	sf::RectangleShape getParede2();
};

Parede::Parede(){
	parede.resize(2);
}

void Parede::iniciarParede(float larguraColuna, float alturaLinha, int i, sf::RenderWindow *window){
	this->dimensoesParedes.x = larguraColuna;
	this->dimensoesParedes.y = alturaLinha;

	if(i == 0 || i == 9){
	 //nao tem parede na linha 0 || linha 9
	}
	if (i > 0 && i < 7) {
		paredes1a6andar(i, window, larguraColuna, alturaLinha);
	}
	if (i == 7) {
		paredes7andar(i, window, larguraColuna, alturaLinha);
	}
	if (i == 8) {
		paredes8andar(i, window, larguraColuna, alturaLinha);
	}
}

void Parede::paredes1a6andar(int i, sf::RenderWindow *window, float larguraColuna, float alturaLinha) {
	this->parede[0].setSize(dimensoesParedes);
	this->parede[0].setPosition(larguraColuna * 2, alturaLinha * (9 -i));
	this->parede[0].setFillColor(sf::Color::Magenta);

	this->parede[1].setSize(dimensoesParedes);
	this->parede[1].setOrigin(dimensoesParedes.x, 0);
	this->parede[1].setPosition(window->getSize().x - larguraColuna * 2, alturaLinha * (9 -i)); //desenha a parede na 5 coluna
	this->parede[1].setFillColor(sf::Color::Magenta);
}

void Parede::paredes7andar(int i, sf::RenderWindow *window, float larguraColuna, float alturaLinha) {
	this->parede[0].setSize(dimensoesParedes);
	this->parede[0].setPosition(larguraColuna * 3, alturaLinha * (9 -i));
	this->parede[0].setFillColor(sf::Color::Magenta);

	this->parede[1].setSize(dimensoesParedes);
	this->parede[1].setOrigin(dimensoesParedes.x, 0);
	this->parede[1].setPosition(window->getSize().x - larguraColuna * 3, alturaLinha * (9 -i)); //desenha a parede na 5 coluna
	this->parede[1].setFillColor(sf::Color::Magenta);
}

void Parede::paredes8andar(int i, sf::RenderWindow *window, float larguraColuna, float alturaLinha) {
	this->parede[0].setSize(dimensoesParedes);
	this->parede[0].setPosition(larguraColuna * 4, alturaLinha * (9 -i));
	this->parede[0].setFillColor(sf::Color::Magenta);

	this->parede[1].setSize(dimensoesParedes);
	this->parede[1].setOrigin(dimensoesParedes.x, 0);
	this->parede[1].setPosition(window->getSize().x - larguraColuna * 4, alturaLinha * (9 -i)); //desenha a parede na 5 coluna
	this->parede[1].setFillColor(sf::Color::Magenta);
}

void Parede::draw(sf::RenderWindow *window) {
	window->draw(parede[0]);
	window->draw(parede[1]);
}

sf::RectangleShape Parede::getParede1() {
	return parede[0];
}

sf::RectangleShape Parede::getParede2() {
	return parede[1];
}

#endif /* PAREDE_HPP_ */
