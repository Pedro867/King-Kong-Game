#ifndef PLAYER_HPP_
#define PLAYER_HPP_
#include <SFML/Graphics.hpp>
#include "Bomba.hpp"
#include <iostream>

using namespace std;

class Player {
private:

	sf::IntRect hitbox;
	sf::Sprite player;
	sf::Texture spritesPlayer[7];
	sf::RenderWindow &window;
	float velX, velY;
	float posX, posY;
	float escala;
	bool bateu, caiu, podeMover, podeSubir, podeDescer, subindo, moveuEsquerda,
			perdeuVida, perdeu, morreuDeQueda, venceu, podeMudarSprite;
	int gravity, vidas, acabouDePular, tempo;

	sf::SoundBuffer bufferPulo;
	sf::Sound somPulo;
	sf::SoundBuffer bufferMOrte;
	sf::Sound somMorte;
public:

	Player(sf::RenderWindow &window);
	void moverX(sf::Event evento);
	void moverY(sf::Event evento);
	void sobe(float larguraColuna,float alturaLinhas);

	void reiniciaPlayer(float alturaLinha, float larguraColuna);

	//setters
	void setPodeMover(int valor);
	void setPodeSubir(int valor);
	void setPodeDescer(int valor);
	void setCaiu(bool caiu);
	void setBateu(bool bateu);
	void setMorreuDeQueda(bool morreuDeQueda);
	void setVelY(float vy);
	void setVelX(float vx);
	void setLayer(float alturaLinha, float larguraColuna);
	void setPosXPosY(float x, float y);
	void setPerdeuVida(bool valor);
	void setVenceu(bool valor);

	//getters
	float getVelY();
	float getVelX();
	int getVidas();
	float getLayer(float alturaLinha);
	bool getMorreuDeQueda();
	bool getPerdeuVida();
	sf::Sprite getPlayer();
	sf::FloatRect bounds();

	void perdeuVidas(float alturaLinha, float larguraColuna);
};

Player::Player(sf::RenderWindow &window) :
		window(window) {
	spritesPlayer[0].loadFromFile("assets/playerParado.png");
	spritesPlayer[1].loadFromFile("assets/playerCorrendo1.png");
	spritesPlayer[2].loadFromFile("assets/playerCorrendo2.png");
	spritesPlayer[3].loadFromFile("assets/playerCorrendo3.png");
	spritesPlayer[4].loadFromFile("assets/playerCorrendo4.png");
	spritesPlayer[5].loadFromFile("assets/playerCorrendo5.png");
	spritesPlayer[6].loadFromFile("assets/playerSubindoEscada.png");
	//hitbox
	hitbox.left = hitbox.top = 0;
	hitbox.height = 16;
	hitbox.width = 7;
	//-----
	player.setTexture(spritesPlayer[0]); //parado
	player.setTextureRect(hitbox);
	velX = velY = posX = posY = 0;
	tempo = 0;
	vidas = 3;
	escala = window.getSize().y / 275.0f; //escala responsiva
	gravity = window.getSize().y / 600.0f;
	player.setScale(escala, escala);
	player.setOrigin(hitbox.width / 2, hitbox.height / 2); //metade do tamanho do player;
	player.setPosition(posX, posY);
	bateu = caiu = podeSubir = podeDescer = moveuEsquerda = subindo =
			perdeuVida = perdeu = morreuDeQueda = venceu = false;
	podeMover = podeMudarSprite = true;
	acabouDePular = 0;

	bufferPulo.loadFromFile("assets/SomPulo.ogg");
	somPulo.setBuffer(bufferPulo);
	bufferMOrte.loadFromFile("assets/SomMorte.ogg");
	somMorte.setBuffer(bufferMOrte);
}

void Player::moverX(sf::Event evento) {

	player.setScale(escala, escala);
	if (podeMover == true && morreuDeQueda == false) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {

			velX = -2.5;
			posX += velX;

			if (podeMudarSprite) {
				hitbox.width = 8;
				player.setTextureRect(hitbox);
				player.setOrigin(hitbox.width / 2, hitbox.height / 2);
				//animacao
				if (tempo == 5) {
					player.setTexture(spritesPlayer[1]);
				} else if (tempo == 15) {
					player.setTexture(spritesPlayer[2]);
				} else if (tempo == 25) {
					player.setTexture(spritesPlayer[3]);
				} else if (tempo == 35) {
					player.setTexture(spritesPlayer[4]);
				} else if (tempo == 40) {
					player.setTexture(spritesPlayer[5]);
				}
				tempo++;
				if (tempo == 40) {
					tempo = 0;
				}
				player.setScale(-escala, escala);
				moveuEsquerda = true;
			}

		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {

			velX = 2.5;
			posX += -velX;

			if (podeMudarSprite) {
				hitbox.width = 9;
				player.setTextureRect(hitbox);
				player.setOrigin(hitbox.width / 2, hitbox.height / 2);
				//animacao
				if (tempo == 5) {
					player.setTexture(spritesPlayer[1]);
				} else if (tempo == 15) {
					player.setTexture(spritesPlayer[2]);
				} else if (tempo == 25) {
					player.setTexture(spritesPlayer[3]);
				} else if (tempo == 35) {
					player.setTexture(spritesPlayer[4]);
				} else if (tempo == 40) {
					player.setTexture(spritesPlayer[5]);
				}
				tempo++;
				if (tempo == 40) {
					tempo = 0;
				}
				moveuEsquerda = false;
			}

		} else {
			velX = 0;

			if (podeMudarSprite) {
				hitbox.width = 7;
				player.setTextureRect(hitbox);
				player.setOrigin(hitbox.width / 2, hitbox.height / 2);
				player.setTexture(spritesPlayer[0]); //parado
			}

			if (moveuEsquerda) {
				player.setScale(-escala, escala);
			} else {
				player.setScale(escala, escala);
			}

		}
		if (subindo == false) {
			podeMudarSprite = true;
			player.move(velX, 0);
		}
	} else if(morreuDeQueda == true){
		player.move(0, 0);
	}else{
		player.move(-velX, 0);
	}
}

void Player::moverY(sf::Event evento) {

	if (caiu == true && podeSubir == false) {
		subindo = false;
		if (acabouDePular > 0) {
			player.move(0, gravity / 3);
			acabouDePular--;

		} else {
			player.move(0, gravity);
		}
	}
	if (podeSubir == true || podeDescer == true) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && podeSubir == true) {
			subindo = true;
			velY = -gravity * 2;
			player.move(0, velY);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && podeDescer == true) {
			subindo = true; //descendo kk
			velY = gravity * 2; //da uma aceleradinha na descida
			player.move(0, velY);
		}
		if (subindo == true) {
			hitbox.width = 10;
			player.setTextureRect(hitbox);
			player.setOrigin(hitbox.width / 2, hitbox.height / 2);
			player.setTexture(spritesPlayer[6]); //escada
			podeMudarSprite = false;
		} else {
			podeMudarSprite = true;
		}
	}
	if (caiu == false && podeSubir == false) {
		subindo = false;
		//PULO
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			velY = window.getSize().y / 30.0f; //pulo responsivo
			velY = -velY;
			player.move(0, velY);
			acabouDePular = 10;
			somPulo.play();
		}
	}
}

void Player::reiniciaPlayer(float alturaLinha, float larguraColuna) {
	setLayer(alturaLinha, larguraColuna);
	morreuDeQueda = false;

}

void Player::setPodeMover(int valor) {
	if (valor == 1) {
		podeMover = true;
	} else if (valor == 0) {
		podeMover = false;
	}
}

void Player::setPodeSubir(int valor) {
	if (valor == 1) {
		podeSubir = true;
	} else if (valor == 0) {
		podeSubir = false;
	}
}
void Player::setPodeDescer(int valor) {
	if (valor == 1) {
		podeDescer = true;
	} else if (valor == 0) {
		podeDescer = false;
	}
}

void Player::setCaiu(bool caiu) {
	this->caiu = caiu;
}

void Player::setBateu(bool bateu) {
	this->bateu = bateu;
}

void Player::setMorreuDeQueda(bool morreuDeQueda) {
	this->morreuDeQueda = morreuDeQueda;
}

void Player::setVelY(float vy) {
	this->velY = vy / 3.0;
}

void Player::setVelX(float vx) {
	velX = vx;
}

void Player::setLayer(float alturaLinha, float larguraColuna) {
	float altura, largura;
	altura = (alturaLinha) - 16;
	largura = 20 * larguraColuna;
	setPosXPosY(largura, altura);
}

void Player::setPosXPosY(float x, float y) {
	//Funcao para setar o andar
	posX = x;
	posY = y;
	player.setPosition(posX, posY);
}

void Player::setPerdeuVida(bool valor) {
	perdeuVida = valor;
}

void Player::setVenceu(bool valor) {
	venceu = valor;
}

float Player::getVelY() {
	return velY;
}

float Player::getVelX() {
	return velX;
}

int Player::getVidas() {
	return vidas;
}

bool Player::getPerdeuVida() {
	return perdeuVida;
}

float Player::getLayer(float alturaLinha) {
	this->posY = player.getPosition().y;
	float layer = posY / alturaLinha;
	layer = 10 - layer;

	return layer;
}

bool Player::getMorreuDeQueda() {
	return morreuDeQueda;
}

inline void Player::sobe(float larguraColuna,float alturaLinha) {
	sf::Vector2<float> rota1(larguraColuna * 9, alturaLinha * 8); // o y eh descartavel pq nn comparo ele com nada
		player.move(-velX, velY);
}

void Player::perdeuVidas(float alturaLinha, float larguraColuna) {
	if (vidas > 0) {
		this->vidas--;
		somMorte.play();
		perdeuVida = true;
		reiniciaPlayer(alturaLinha, larguraColuna);

	} else {
		perdeu = true; //futuro gameOver, mas quero colocar a func no main
	}
}

sf::Sprite Player::getPlayer() {
	return player;
}

sf::FloatRect Player::bounds() {
	return player.getGlobalBounds();
}

#endif /* PLAYER_HPP_ */
