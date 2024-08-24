#ifndef CHAO_HPP_
#define CHAO_HPP_
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.hpp"

using namespace std;

//usei somente para testar colisao com o chao
//pode ser subtituido por qualquer cenarios
class Chao {
private:
	sf::RectangleShape chao;
public:
	Chao(float posicaoX,float posicaoY,float tamanho){
		chao.setSize(sf::Vector2f(tamanho, 30));
		chao.setOrigin(500,15);
		chao.setPosition(posicaoX, posicaoY);
		chao.setFillColor(sf::Color::Red);
	}

	sf::RectangleShape getChao(){
		return chao;
	}
};
#endif
