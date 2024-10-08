#ifndef DEBUG_BOMBAESPECIAL_HPP_
#define DEBUG_BOMBAESPECIAL_HPP_
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include <iostream>

using namespace std;

class BombaEspecial {
private:

	sf::IntRect hitbox;
	sf::Sprite bombaEspecial;
	sf::Sprite hitboxPulo;
	sf::Texture texturahitboxPulo;

	sf::Texture texturaBombaEspecial;

	float velX, velY;
	float posX, posY;
	float escala;
	bool bateuNoChao, escada, cair, descerHabilitado, descendo;
	bool sorteouFormaDeDescer;
	int formaDeDescer;

	int qntMaxBombaEspecial;

public:

	void iniciarVelocidadeEEscalaBombaEspecial(sf::RenderWindow *window);
	void iniciarBombaEspecial();
	void mover();
	void moverY();
	void moverX();
	void inverteVelX();

	//setters
	void setPosXPosY(float x, float y);
	void setPodeMover(int valor);
	void setPodeDescerEscada(int valor);
	void setPodeDescerBuraco(int valor);
	void setDescerHabilitado(bool descerHabilitado);
	void setSorteouFormaDeDescer(bool sorteou);
	void setLayer(float alturaLinha, float larguraColuna);

	void descerEscada();
	void descerBuraco();

	//getters
	float getVelX();
	int getLayer(float alturaLinha);
	sf::FloatRect getBombaEspecialBounds();
	sf::FloatRect getPuloBounds();
	sf::Sprite getBombaEspecial();
	sf::Sprite getHitboxDoPulo();
	int getFormaDeDescer();

	int sortearFormaDeDescer(int layer, int cont);
	bool olhaSePodeSpawnarEspecial(float alturaLinha, int qntAtualBombaEspecial);
	void spawnBombaEspecial(float alturaLinha, float larguraColuna);


};

void BombaEspecial::iniciarVelocidadeEEscalaBombaEspecial(sf::RenderWindow *window){

	velX = window->getSize().x / 250.0f; //velocidade responsiva
	velY = window->getSize().y / 190.0f; //igual a gravidade
	//posX = 600;
	//posY = 550;
	escala = window->getSize().y / 400.0f; //escala responsiva
	bombaEspecial.setScale(escala, escala);
	bombaEspecial.setOrigin(16, 16); //metade do tamanho do player;
	hitboxPulo.setOrigin(16,16);
	hitboxPulo.setScale(escala,escala+3);
	//bombaEspecial.setPosition(posX, posY);
}

void BombaEspecial::iniciarBombaEspecial(){
	texturaBombaEspecial.loadFromFile("assets/BombaEspecial.png");
	texturahitboxPulo.loadFromFile("assets/AreaDeHitboxDopulo.png");
	//hitbox
	hitbox.left = 0;
	hitbox.top = 50;
	hitbox.height = 11.5;//menorque 13 pra melhorar a gameplay
	hitbox.width = 13;

	//fim da hitbox
	bombaEspecial.setTexture(texturaBombaEspecial);
	hitboxPulo.setTexture(texturahitboxPulo);

	if (velX < 0) { //quando a bomba vai reespawnar mas ela ja tinha batido em uma parede antes, a velX fica negativa
		inverteVelX();
	}

	//bombaEspecial.setPosition(posX, posY);
	bateuNoChao = false;
	cair = false;
	escada = false;
	descerHabilitado = false;
	descendo = false;
	qntMaxBombaEspecial = 10;
	sorteouFormaDeDescer = false;
}

void BombaEspecial::mover() {
	if (bateuNoChao == true && descerHabilitado == false) {
		bombaEspecial.move(velX, 0);
		hitboxPulo.move(velX,0);
		posX = bombaEspecial.getPosition().x + velX;

	} else {
		bombaEspecial.move(0, velY);
		hitboxPulo.move(0,velY);
		posY = bombaEspecial.getPosition().y + velY;
	}
}

void BombaEspecial::moverY() {
	bombaEspecial.move(0, velY);
	hitboxPulo.move(0,velY);
}

void BombaEspecial::moverX() {
	if(descendo == false){
		bombaEspecial.move(velX, 0);
		hitboxPulo.move(velX,0);
	}
}

void BombaEspecial::inverteVelX() {
	velX = -velX;
}

void BombaEspecial::setPosXPosY(float x, float y) {
	posX = x;
	posY = y;
	bombaEspecial.setPosition(posX, posY);
	hitboxPulo.setPosition(posX, posY+13);
}

void BombaEspecial::setPodeMover(int valor) {
	if (valor == 1) {
		bateuNoChao = true;
	} else if (valor == 0) {
		bateuNoChao = false;
	}
}

void BombaEspecial::setPodeDescerEscada(int valor) {
	if (valor == 1) {
		descerEscada();
	}
}

void BombaEspecial::setPodeDescerBuraco(int valor) {
	if (valor == 1) {
		descerBuraco();
	}
}

void BombaEspecial::setDescerHabilitado(bool descerHabilitado) {
	this->descerHabilitado = descerHabilitado;
}

void BombaEspecial::setSorteouFormaDeDescer(bool sorteou){
	this->sorteouFormaDeDescer = sorteou;
}

void BombaEspecial::setLayer(float alturaLinha, float larguraColuna) {
	float altura, largura;
	altura = (alturaLinha * 2)+6;
	largura = 10 * larguraColuna;
	setPosXPosY(largura, altura);
}

void BombaEspecial::descerEscada() {

	if(bateuNoChao == true){
		setDescerHabilitado(true);
		this->sorteouFormaDeDescer = true;
	}else{
		setDescerHabilitado(false);
		this->sorteouFormaDeDescer = false;
	}
}

void BombaEspecial::descerBuraco() {

	setDescerHabilitado(false);
	this->sorteouFormaDeDescer = false;
}

float BombaEspecial::getVelX() {
	return velX;
}

int BombaEspecial::getLayer(float alturaLinha) {
	this->posY = bombaEspecial.getPosition().y;
	int layer = posY / alturaLinha;
	layer = 10 - layer;

	return layer;
}

sf::FloatRect BombaEspecial::getBombaEspecialBounds() {
	return bombaEspecial.getGlobalBounds();
}
sf::FloatRect BombaEspecial::getPuloBounds() {
	return hitboxPulo.getGlobalBounds();
}

sf::Sprite BombaEspecial::getBombaEspecial() {
	return bombaEspecial;
}

int BombaEspecial::getFormaDeDescer(){
	return formaDeDescer;
}

int BombaEspecial::sortearFormaDeDescer(int layer, int cont){

	if(sorteouFormaDeDescer == false){
		//desceu = false;
		if (layer == 1) {
			this->formaDeDescer = (rand() % 3);
			this->sorteouFormaDeDescer = true;
			//Para esse andar, existem 2 possibilidades: sumir do mapa ou bater na parede e voltar
		}
		if (layer == 8) {
			this->formaDeDescer = 3;
			this->sorteouFormaDeDescer = true;
		}
		if (layer == 2 || layer == 4 || layer == 6) {
			this->formaDeDescer = (rand() % 5);
			this->sorteouFormaDeDescer = true;
			//Para esses andares, existem 2 formas de descer (as duas escadas), 2 numeros pra cada e 1 para seguir reto
		}
		if(layer == 3 || layer == 5 || layer == 7) {
			this->formaDeDescer = (rand() % 7);
			this->sorteouFormaDeDescer = true;
			//Para esses andares, existem 3 formas de descer (a escada e os dois buracos), 2 numeros pra cada e 1 para seguir reto
		}
//		cout<< "bomba " << cont << ": ";
//		cout << formaDeDescer;
//		cout << " - " << layer << endl;
	}
	return formaDeDescer;
}

bool BombaEspecial::olhaSePodeSpawnarEspecial(float alturaLinha, int qntAtualBombaEspecial) {
	if((posY > alturaLinha) && (posY < (3 * alturaLinha))){
		return false;
	}
	else if(qntAtualBombaEspecial < qntMaxBombaEspecial){
		return true;
	}
	return false;
}

inline sf::Sprite BombaEspecial::getHitboxDoPulo() {
	return hitboxPulo;
}

void BombaEspecial::spawnBombaEspecial(float alturaLinha, float larguraColuna) {
	setLayer(alturaLinha, larguraColuna);
}

#endif /* DEBUG_BOMBAESPECIAL_HPP_ */
