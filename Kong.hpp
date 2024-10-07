#ifndef KONG_HPP_
#define KONG_HPP_

class Kong{
private:
	sf::Sprite kong;
	sf::Texture kongTexture;
	float velX;
	float velY;
	float scaleX;
	float scaleY;

	bool estaEmCima = true;
	bool concluiuRota1 = false;
	bool concluiuRota2 = true;
	bool bateuNoPeito = false;

	int rotas = 0;
	int timer = 0; //talvez fazer com sf::Clock...
	int batidasNoPeito = 0;

public:

	void iniciaKong(float larguraColuna, float alturaLinha, sf::RenderWindow *window);

	bool AnimacaoInicialKong(float larguraColuna, float alturaLinha);
	void AnimacaoKong();
	void bateNoPeito();
	void trocaDePosicaoBaixo(float alturaLinha, float larguraColuna);
	void trocaDePosicaoAlto(float alturaLinha, float larguraColuna);

	void rota1(float larguraColuna, float alturaLinha);
	void rota2(float larguraColuna, float alturaLinha);

	void setPosition(float largura, float altura);
	sf::Sprite getKong();
};

inline void Kong::iniciaKong(float larguraColuna, float alturaLinha, sf::RenderWindow *window){
	kongTexture.loadFromFile("assets/donkey.png");
	kong.setTexture(kongTexture);
	kong.setOrigin(25, 28); //seta a posicao no pe dele (28) e no centro dele (25)
	kong.setPosition(larguraColuna * 9, alturaLinha * 9);
	float escala = window->getSize().y / 235.f; //escala kong responsiva
	scaleX = scaleY = escala;
	kong.setScale(scaleX, scaleY);

	//multipliquei tudo por 3 para ir mais rapido nos testes
	//acelerei o timer tambem
	this->velX = (larguraColuna / 10.f);
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

	if(kong.getPosition().y <= alturaLinha * 3){
		kong.setPosition(larguraColuna * 9, alturaLinha * 3);
		rotas = 0;
		return true;
	}else{
		return false;
	}
}

void Kong::AnimacaoKong(){
	timer++;

	if (timer == 15) {
		this->scaleX = -scaleX;
		kong.setScale(scaleX, scaleY);
		timer = 0;
	}
}

void Kong::bateNoPeito() {
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

void Kong::trocaDePosicaoBaixo(float alturaLinha, float larguraColuna){

	if(estaEmCima == true){
		if(concluiuRota1 == false){
			rota1(larguraColuna, alturaLinha);
		}
		else if(concluiuRota2 == false){
			rota2(larguraColuna, alturaLinha);
		}

		if(kong.getPosition().y < alturaLinha){ //se ele for pra fora do mapa
			kong.setPosition(larguraColuna * 9, alturaLinha * 11);
		}

		if(rotas == 5){
			kong.setPosition(larguraColuna * 9, alturaLinha * 9);
			estaEmCima = false;
			rotas = 0;
		}
	}else{
		trocaDePosicaoAlto(alturaLinha,larguraColuna);
	}
}

void Kong::trocaDePosicaoAlto(float alturaLinha, float larguraColuna){
	/*if(estaEmCima == false){
		if(concluiuRota1 == false)
		rota1(larguraColuna, alturaLinha);

		if(concluiuRota2 == false)
		rota2(larguraColuna, alturaLinha);

		if(kong.getPosition().y <= alturaLinha * 9){
			kong.setPosition(larguraColuna * 9, alturaLinha * 9);
			estaEmCima = true;
		}
	}*/
}

void Kong::rota1(float larguraColuna, float alturaLinha) {

	sf::Vector2<float> rota1(larguraColuna * 9, alturaLinha * 8); // o y eh descartavel pq nn comparo ele com nada
	kong.move(-velX, velY);

	if(kong.getPosition().x <= rota1.x){
		concluiuRota1 = true;
		concluiuRota2 = false;
		rotas++;
	}
}

void Kong::rota2(float larguraColuna,
		float alturaLinha) {

	sf::Vector2<float> rota2(larguraColuna * 14, alturaLinha * 8); //ali t� * 8 mas tanto faz pq nn comparo ele com nada
	kong.move(velX, velY);

	if (kong.getPosition().x >= rota2.x) {
		concluiuRota1 = false;
		concluiuRota2 = true;
		rotas++;
	}
}

void Kong::setPosition(float largura, float altura){
	kong.setPosition(largura, altura);
}

inline sf::Sprite Kong::getKong() {
	return kong;
}

#endif /* KONG_HPP_ */
