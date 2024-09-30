/*
 * Princesa.hpp
 *
 *  Created on: 29 de set. de 2024
 *      Author: Rafael
 */

#ifndef PRINCESA_HPP_
#define PRINCESA_HPP_

class Princesa{
private:

	sf::IntRect hitbox;
	sf::Sprite princesa;
	sf::Texture texturePrincesa;
	sf::RenderWindow &window;

	float escala;
	int posX, posY;

public:

	Princesa(sf::RenderWindow &window);
	void AnimacaoPrincesa();

	sf::Sprite getPrincesa();
	void setLayer(float alturaLinha, float larguraColuna);
	void setPosXPosY(float x, float y);
};

Princesa::Princesa(sf::RenderWindow &window) : window(window) {
	texturePrincesa.loadFromFile("assets/princesa.png");
	//hitbox
	hitbox.left = hitbox.top = 0;
	hitbox.height = 19;
	hitbox.width = 13;
	//-----
	princesa.setTexture(texturePrincesa);
	princesa.setTextureRect(hitbox);
	escala = window.getSize().y / 275.0f; //escala responsiva
	princesa.setScale(escala, escala);
	princesa.setOrigin(hitbox.width / 2, hitbox.height / 2); //metade do tamanho da princesa;
	posX = 0;
	posY = 0;
}

void Princesa::AnimacaoPrincesa() {
}

inline sf::Sprite Princesa::getPrincesa() {
	return princesa;
}

void Princesa::setLayer(float alturaLinha, float larguraColuna) {
	float altura, largura;
	altura = (alturaLinha * 1) - 19;
	largura = 20 * larguraColuna;
	setPosXPosY(largura, altura);
}

void Princesa::setPosXPosY(float x, float y) {
	posX = x;
	posY = y;
	princesa.setPosition(posX, posY);
}

#endif /* PRINCESA_HPP_ */
