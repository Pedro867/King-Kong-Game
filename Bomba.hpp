#ifndef BOMBA_HPP_
#define BOMBA_HPP_
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include <iostream>

using namespace std;

class Bomba {
private:

	sf::IntRect hitbox;
	sf::Sprite bombaNormal;
	//Projeto futuro sf::Sprite bombaEspecial;
	sf::Texture texturaBombaNormal;
	//Projeto futuro sf::Texture texturaBombaEspecial;

	float velX, velY;
	float posX, posY;
	float escala;
	bool bateuNoChao, escada, cair, descerHabilitado, descendo;
	bool sorteouFormaDeDescer;
	int formaDeDescer;

	int qntMaxBombaNormal;

public:

	void iniciarVelocidadeEEscalaBomba(sf::RenderWindow *window);
	void iniciarBomba();
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
	sf::FloatRect getBombaNormalBounds();
	sf::Sprite getBombaNormal();
	int getFormaDeDescer();

	int sortearFormaDeDescer(int layer, int cont);
	bool olhaSePodeSpawnarNormal(float alturaLinha, int qntAtualBombaNormal);
	void spawnBombaNormal(float alturaLinha, float larguraColuna);


};

void Bomba::iniciarVelocidadeEEscalaBomba(sf::RenderWindow *window){
	velX = window->getSize().x / 250.0f; //velocidade responsiva
	velY = window->getSize().y / 190.0f; //um pouco maior que a gravidade

	escala = window->getSize().y / 400.0f; //escala responsiva
	bombaNormal.setScale(escala, escala);
	bombaNormal.setOrigin(16, 16); //metade do tamanho do player;
	//bombaNormal.setPosition(posX, posY);
}

void Bomba::iniciarBomba(){
	texturaBombaNormal.loadFromFile("assets/bomba.png");
	bombaNormal.setTexture(texturaBombaNormal);
	//hitbox
	hitbox.left = 0;
	hitbox.top = 0;
	hitbox.height = 11.5;//menorque 13 pra melhorar a gameplay
	hitbox.width = 13;
	//fim da hitbox

	if(velX < 0){ //quando a bomba vai reespawnar mas ela ja tinha batido em uma parede antes, a velX fica negativa
		inverteVelX();
	}

	bateuNoChao = false;
	cair = false;
	escada = false;
	descerHabilitado = false;
	descendo = false;
	qntMaxBombaNormal = 10;
	sorteouFormaDeDescer = false;
}

void Bomba::mover() {
	if (bateuNoChao == true && descerHabilitado == false) {
		bombaNormal.move(velX, 0);
		posX = bombaNormal.getPosition().x + velX;
	} else {
		bombaNormal.move(0, velY);
		posY = bombaNormal.getPosition().y + velY;
	}
}

void Bomba::moverY() {
	bombaNormal.move(0, velY);
}

void Bomba::moverX() {
		bombaNormal.move(velX, 0);
}

void Bomba::inverteVelX() {
	velX = -velX;
}

void Bomba::setPosXPosY(float x, float y) {
	posX = x;
	posY = y;
	bombaNormal.setPosition(posX, posY);
}

void Bomba::setPodeMover(int valor) {
	if (valor == 1) {
		bateuNoChao = true;
	} else if (valor == 0) {
		bateuNoChao = false;
	}
}

void Bomba::setPodeDescerEscada(int valor) {
	if (valor == 1) {
		descerEscada();
	}
}

void Bomba::setPodeDescerBuraco(int valor) {
	if (valor == 1) {
		descerBuraco();
	}
}

void Bomba::setDescerHabilitado(bool descerHabilitado) {
	this->descerHabilitado = descerHabilitado;
}

void Bomba::setSorteouFormaDeDescer(bool sorteou){
	this->sorteouFormaDeDescer = sorteou;
}

void Bomba::setLayer(float alturaLinha, float larguraColuna) {
	float altura, largura;
	altura = (alturaLinha * 2);
	largura = 10 * larguraColuna;
	setPosXPosY(largura, altura);
}

void Bomba::descerEscada() {

	if(bateuNoChao == true){
		setDescerHabilitado(true);
		this->sorteouFormaDeDescer = true;
	}else{
		setDescerHabilitado(false);
		this->sorteouFormaDeDescer = false;
	}
}

void Bomba::descerBuraco() {

	setDescerHabilitado(false);
	this->sorteouFormaDeDescer = false;
}

float Bomba::getVelX() {
	return velX;
}

int Bomba::getLayer(float alturaLinha) {
	this->posY = bombaNormal.getPosition().y;
	int layer = posY / alturaLinha;
	layer = 10 - layer;

	return layer;
}

sf::FloatRect Bomba::getBombaNormalBounds() {
	return bombaNormal.getGlobalBounds();
}

sf::Sprite Bomba::getBombaNormal() {
	return bombaNormal;
}

int Bomba::getFormaDeDescer(){
	return formaDeDescer;
}

int Bomba::sortearFormaDeDescer(int layer, int cont){

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

bool Bomba::olhaSePodeSpawnarNormal(float alturaLinha, int qntAtualBombaNormal) {
	if((posY > alturaLinha) && (posY < (3 * alturaLinha))){
		return false;
	}
	else if(qntAtualBombaNormal < qntMaxBombaNormal){
		return true;
	}
	return false;
}

void Bomba::spawnBombaNormal(float alturaLinha, float larguraColuna) {
	iniciarBomba();
	setLayer(alturaLinha, larguraColuna);
}

#endif
