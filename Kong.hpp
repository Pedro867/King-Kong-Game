/*
 * Kong.hpp
 *
 *  Created on: 23 de set. de 2024
 *      Author: Rafael
 */

#ifndef KONG_HPP_
#define KONG_HPP_

class Kong{
private:
	sf::Sprite kong;
	sf::Texture kongTexture;
	float velX;
	float velY;
	float scaleX = 2.5;
	float scaleY = 2.5;

	bool concluiuRota1 = false;
	bool concluiuRota2 = true;
	bool bateuNoPeito = false;

	int timer = 0; //talvez fazer com sf::Clock...
	int batidasNoPeito = 0;

public:

	void IniciaKong(float larguraColuna, float alturaLinha);
	bool AnimacaoInicialKong(float larguraColuna, float alturaLinha);
	void AnimacaoKong();
	void bateNoPeito();
	void rota1(float larguraColuna, float alturaLinha);
	void rota2(float larguraColuna, float alturaLinha);
	sf::Sprite getKong();
};

inline void Kong::IniciaKong(float larguraColuna, float alturaLinha){
	kongTexture.loadFromFile("assets/donkey.png");
	kong.setTexture(kongTexture);
	kong.setOrigin(25, 28); //seta a posicao no pe dele (28) e no centro dele (25)
	kong.setPosition(larguraColuna * 14, alturaLinha * 9);
	kong.setScale(scaleX, scaleY);

	this->velX = larguraColuna / 10.f;
	this->velY = - (alturaLinha / 50.f);
}

bool Kong::AnimacaoInicialKong(float larguraColuna, float alturaLinha) {

	if(bateuNoPeito == false){
		bateNoPeito();
	}

	if(concluiuRota1 == false && bateuNoPeito == true)
	rota1(larguraColuna, alturaLinha);

	if(concluiuRota2 == false && bateuNoPeito == true)
	rota2(larguraColuna, alturaLinha);

	if(kong.getPosition().y <= alturaLinha * 2){
		kong.setPosition(larguraColuna * 9, alturaLinha * 2);
		return true;
	}else{
		return false;
	}
}

inline void Kong::AnimacaoKong(){
	timer++;

	if (timer == 15) {
		this->scaleX = -scaleX;
		kong.setScale(scaleX, scaleY);
		timer = 0;
	}
}

inline void Kong::bateNoPeito() {
	timer++;

	if(timer == 15){
		this->scaleX = -scaleX;
		kong.setScale(scaleX, scaleY);
		timer = 0;
		batidasNoPeito++;
	}
	if(batidasNoPeito == 10){
		bateuNoPeito = true;
	}
}

inline void Kong::rota1(float larguraColuna, float alturaLinha) {

	sf::Vector2<float> rota1(larguraColuna * 9, alturaLinha * 8); // o y eh descartavel pq nn comparo ele com nada
	kong.move(-velX, velY);

	if(kong.getPosition().x <= rota1.x){
		concluiuRota1 = true;
		concluiuRota2 = false;
	}
}

inline void Kong::rota2(float larguraColuna,
		float alturaLinha) {

	sf::Vector2<float> rota2(larguraColuna * 14, alturaLinha * 8); //ali tá * 8 mas tanto faz pq nn comparo ele com nada
	kong.move(velX, velY);

	if (kong.getPosition().x >= rota2.x) {
		concluiuRota1 = false;
		concluiuRota2 = true;
	}
}

inline sf::Sprite Kong::getKong() {
	return kong;
}

#endif /* KONG_HPP_ */
