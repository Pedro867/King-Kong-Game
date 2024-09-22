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
	void iniciarEscada(float larguraColuna, float alturaLinha);
	void draw(sf::RenderWindow *window, float larguraColuna, float alturaLinha, int i, int j);
	sf::Sprite getEscada1();
	sf::Sprite getEscada2();
	float meioEscada1();
	float meioEscada2();
};

inline Escada::Escada() {
	escada.resize(2);
}

inline void Escada::iniciarEscada(float larguraColuna, float alturaLinha) {

	texturaEscada.loadFromFile("assets/Escada.png");

	for(int i = 0; i < 2; i++){
		escada[i].setTexture(texturaEscada);
		escada[i].setScale(larguraColuna / 4, alturaLinha / 8);
	}
}

inline void Escada::draw(sf::RenderWindow *window, float larguraColuna, float alturaLinha, int i, int j) {

	int jAuxiliar = 0;

	if(jAuxiliar < j){
		escada[0].setPosition((j - 1) * larguraColuna, alturaLinha * (9 - i));
		jAuxiliar = j;
		window->draw(escada[0]);
	}
	else{
		escada[1].setPosition((j - 1) * larguraColuna, alturaLinha * (9 - i));
		window->draw(escada[1]);
	}
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
