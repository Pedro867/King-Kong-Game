/*
 * Escada.hpp
 *
 *  Created on: 27 de ago. de 2024
 *      Author: Rafael Torres, Pedro Lucas, Lucas lenz
 */

#ifndef ESCADA_HPP_
#define ESCADA_HPP_

class Escada{
private:
	vector<sf::Sprite> escada;
	sf::Texture texturaEscada;
	//vector<sf::FloatRect> hitbox;

public:
	Escada();
	void iniciarEscada(float larguraColuna, float alturaLinha, int i);
	void draw(sf::RenderWindow *window);
	sf::Sprite getEscada1();
	sf::Sprite getEscada2();
	float meioEscada1();
	float meioEscada2();
};

inline Escada::Escada() {
	escada.resize(2);
}

inline void Escada::iniciarEscada(float larguraColuna, float alturaLinha, int i) {

	texturaEscada.loadFromFile("assets/Escada.png");

	for(int cont = 0; cont < 2; cont++){
		escada[cont].setTexture(texturaEscada);
		escada[cont].setScale(larguraColuna / 4, alturaLinha / 8);
	}

	if(i == 0 || i == 9){
		escada[0].setScale(0, 0);
		escada[1].setScale(0, 0);
	}
	if(i == 1 || i == 3 || i == 5){
		escada[0].setPosition(3 * larguraColuna, alturaLinha * (9 - i));
		escada[1].setPosition(35 * larguraColuna, alturaLinha * (9 - i));
	}
	if(i == 2 || i == 4 || i == 6 || i == 8){
		escada[0].setPosition(19 * larguraColuna, alturaLinha * (9 - i));
		escada[1].setScale(0, 0);
	}
	if(i == 7){
		escada[0].setPosition(5 * larguraColuna, alturaLinha * (9 - i));
		escada[1].setPosition(33 * larguraColuna, alturaLinha * (9 - i));
	}
}

inline void Escada::draw(sf::RenderWindow *window) {
		window->draw(escada[0]);
		window->draw(escada[1]);
}

inline sf::Sprite Escada::getEscada1() {
	return escada[0];
}

inline sf::Sprite Escada::getEscada2() {
	return escada[1];
}

/*inline float Escada::meioEscada1() {
	float meio1 = escada[0].getPosition().x + escada[0].getScale().x/2;
	return meio1;
}

inline float Escada::meioEscada2() {
	float meio2 = escada[1].getPosition().x + escada[1].getScale().x/2;
	return meio2;
}*/

#endif /* ESCADA_HPP_ */
