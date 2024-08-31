/*
 * Escada.hpp
 *
 *  Created on: 27 de ago. de 2024
 *      Author: Rafael
 */

#ifndef ESCADA_HPP_
#define ESCADA_HPP_

class Escada{
private:
	sf::Sprite escada1;
	sf::Sprite escada2;
	sf::Texture texturaEscada;
	sf::FloatRect hitbox;

public:
	void iniciarEscada(float larguraColuna, float alturaLinha);
	void draw(sf::RenderWindow *window, float larguraColuna, float alturaLinha, int i, int j);
	sf::Sprite getEscada1();
	sf::Sprite getEscada2();
};

inline void Escada::iniciarEscada(float larguraColuna, float alturaLinha) {

	texturaEscada.loadFromFile("assets/Escada.png");

	escada1.setTexture(texturaEscada);
	escada1.setScale(larguraColuna / 4, alturaLinha / 8);

	escada2.setTexture(texturaEscada);
	escada2.setScale(larguraColuna / 4, alturaLinha / 8);

	//hitbox = escada2.getGlobalBounds(); //hitbox da 2 == hitbox 1
}

inline void Escada::draw(sf::RenderWindow *window, float larguraColuna, float alturaLinha, int i, int j) {

	int jAuxiliar = 0;

	if(jAuxiliar < j){
		escada1.setPosition((j - 1) * larguraColuna, alturaLinha * i);
		jAuxiliar = j;
		window->draw(escada1);
	}
	else{
		escada2.setPosition((j - 1) * larguraColuna, alturaLinha * i);
		window->draw(escada2);
	}
}

inline sf::Sprite Escada::getEscada1() {
	return escada1;
}

inline sf::Sprite Escada::getEscada2() {
	return escada2;
}

#endif /* ESCADA_HPP_ */
