#ifndef PAREDE_HPP_
#define PAREDE_HPP_
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.hpp"

using namespace std;

//ler comentarios do chao.hpp
class Parede {
private:
	sf::RectangleShape parede;
public:
	Parede(int posX) {
		parede.setSize(sf::Vector2f(20, 400));
		parede.setOrigin(10, 200);
		parede.setPosition(posX, 400);
		parede.setFillColor(sf::Color::Blue);
	}

	sf::RectangleShape getParede() {
		return parede;
	}
};
#endif
