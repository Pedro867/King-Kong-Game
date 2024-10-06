/*
 * Chao.hpp
 *
 *  Created on: 27 de ago. de 2024
 *      Author: Rafael
 */

#ifndef CHAO_HPP_
#define CHAO_HPP_

//#include "Game.hpp"

class Chao{
private:

	vector<sf::RectangleShape> chao;
	sf::Vector2<float> dimensoesChao;

public:

	Chao();
	void iniciarChao(float larguraColuna, float alturaLinha, int i);
	void chao1246andar(float larguraColuna, float alturaLinha, int i);
	void chao3andar(float larguraColuna, float alturaLinha, int i);
	void chao5andar(float larguraColuna, float alturaLinha, int i);
	void chao7andar(float larguraColuna, float alturaLinha, int i);
	void chao89andar(float larguraColuna, float alturaLinha, int i);
	void drawChao(sf::RenderWindow *window);
	sf::RectangleShape getChao1();
	sf::RectangleShape getChao2();
	sf::RectangleShape getChao3();
};

inline Chao::Chao() {
	chao.resize(3); //tem no max 3 chaos (ou choes kkkkk) por andar
}

inline void Chao::iniciarChao(float larguraColuna, float alturaLinha, int i) {

	if(i == 1 || i == 2 || i == 4 || i == 6){
		chao1246andar(larguraColuna, alturaLinha, i);
	}
	if(i == 3){
		chao3andar(larguraColuna, alturaLinha, i);
	}
	if (i == 5) {
		chao5andar(larguraColuna, alturaLinha, i);
	}
	if(i == 7){
		chao7andar(larguraColuna, alturaLinha, i);
	}
	if(i == 8 || i == 9){
		chao89andar(larguraColuna, alturaLinha, i);
	}
}

inline void Chao::chao1246andar(float larguraColuna, float alturaLinha, int i) {
	this->dimensoesChao.x = 36 * larguraColuna;
	this->dimensoesChao.y = 5.0f;
	this->chao[0].setSize(dimensoesChao);
	this->chao[0].setPosition(larguraColuna * 2, alturaLinha + alturaLinha * (9 - i)); //desenha no chao da linha na 3 coluna
	this->chao[0].setFillColor(sf::Color::Magenta);
}

inline void Chao::chao3andar(float larguraColuna, float alturaLinha, int i) {
	this->dimensoesChao.x = 12 * larguraColuna;
	this->dimensoesChao.y = 5.0f;
	this->chao[0].setSize(dimensoesChao);
	this->chao[0].setPosition(larguraColuna * 2, alturaLinha + alturaLinha * (9 - i));
	this->chao[0].setFillColor(sf::Color::Magenta);
	this->chao[2].setSize(dimensoesChao);
	this->chao[2].setPosition(larguraColuna * 26, alturaLinha + alturaLinha * (9 - i));
	this->chao[2].setFillColor(sf::Color::Magenta);

	this->dimensoesChao.x = 10 * larguraColuna;
	this->dimensoesChao.y = 5.0f;
	this->chao[1].setSize(dimensoesChao);
	this->chao[1].setPosition(larguraColuna * 15, alturaLinha + alturaLinha * (9 - i));
	this->chao[1].setFillColor(sf::Color::Magenta);
}

inline void Chao::chao5andar(float larguraColuna, float alturaLinha, int i) {
	this->dimensoesChao.x = 8 * larguraColuna;
	this->dimensoesChao.y = 5.0f;
	this->chao[0].setSize(dimensoesChao);
	this->chao[0].setPosition(larguraColuna * 2, alturaLinha + alturaLinha * (9 - i));
	this->chao[0].setFillColor(sf::Color::Magenta);
	this->chao[2].setSize(dimensoesChao);
	this->chao[2].setPosition(larguraColuna * 30, alturaLinha + alturaLinha * (9 - i));
	this->chao[2].setFillColor(sf::Color::Magenta);

	this->dimensoesChao.x = 18 * larguraColuna;
	this->dimensoesChao.y = 5.0f;
	this->chao[1].setSize(dimensoesChao);
	this->chao[1].setPosition(larguraColuna * 11, alturaLinha + alturaLinha * (9 - i));
	this->chao[1].setFillColor(sf::Color::Magenta);
}

inline void Chao::chao7andar(float larguraColuna, float alturaLinha, int i) {
	this->dimensoesChao.x = 10 * larguraColuna;
	this->dimensoesChao.y = 5.0f;
	this->chao[0].setSize(dimensoesChao);
	this->chao[0].setPosition(larguraColuna * 3, alturaLinha + alturaLinha * (9 - i));
	this->chao[0].setFillColor(sf::Color::Magenta);
	this->chao[2].setSize(dimensoesChao);
	this->chao[2].setPosition(larguraColuna * 27, alturaLinha + alturaLinha * (9 - i));
	this->chao[2].setFillColor(sf::Color::Magenta);

	this->dimensoesChao.x = 12 * larguraColuna;
	this->dimensoesChao.y = 5.0f;
	this->chao[1].setSize(dimensoesChao);
	this->chao[1].setPosition(larguraColuna * 14, alturaLinha + alturaLinha * (9 - i));
	this->chao[1].setFillColor(sf::Color::Magenta);
}

inline void Chao::chao89andar(float larguraColuna, float alturaLinha, int i) {
	this->dimensoesChao.x = 32 * larguraColuna;
	this->dimensoesChao.y = 5.0f;
	this->chao[0].setSize(dimensoesChao);
	this->chao[0].setPosition(larguraColuna * 4, alturaLinha + alturaLinha * (9 - i)); //desenha no chao da linha na 3 coluna
	this->chao[0].setFillColor(sf::Color::Magenta);
}

inline void Chao::drawChao(sf::RenderWindow *window){
	window->draw(this->chao[0]);
	window->draw(this->chao[1]);
	window->draw(this->chao[2]);
}

inline sf::RectangleShape Chao::getChao1() {
	return chao[0];
}

inline sf::RectangleShape Chao::getChao2() {
	return chao[1];
}

inline sf::RectangleShape Chao::getChao3() {
	return chao[2];
}

#endif /* CHAO_HPP_ */
