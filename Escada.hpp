#ifndef ESCADA_HPP_
#define ESCADA_HPP_

class Escada{
private:

	vector<sf::Sprite> escada;
	vector<sf::Sprite> hitbox;
	vector<sf::Sprite> hitboxDescer;
	sf::Texture texturaEscada;
	sf::Texture texturaHitbox;
	sf::Texture texturaHitboxDescer;

public:
	Escada();
	void iniciarEscada(float larguraColuna, float alturaLinha, int i);
	void draw(sf::RenderWindow *window);
	sf::Sprite getEscada1();
	sf::Sprite getEscada2();
	sf::Sprite getHitbox1();
	sf::Sprite getHitbox2();
	sf::Sprite getHitboxDescer1();
	sf::Sprite getHitboxDescer2();
};

Escada::Escada() {
	escada.resize(2);
	hitbox.resize(2);
	hitboxDescer.resize(2);
}

void Escada::iniciarEscada(float larguraColuna, float alturaLinha, int i) {

	texturaEscada.loadFromFile("assets/Escada.png");
	texturaHitbox.loadFromFile("assets/hitboxEscada.png");
	texturaHitboxDescer.loadFromFile("assets/hitboxEscadaDescer.png");


	for(int cont = 0; cont < 2; cont++){
		escada[cont].setTexture(texturaEscada);
		escada[cont].setScale(larguraColuna / 4, alturaLinha / 8);
		hitbox[cont].setTexture(texturaHitbox);
		hitboxDescer[cont].setTexture(texturaHitboxDescer);
	}

	if(i == 0 || i == 9){
		escada[0].setScale(0, 0);
		escada[1].setScale(0, 0);
		hitbox[0].setScale(0, 0);
		hitbox[1].setScale(0, 0);
		hitboxDescer[0].setScale(0, 0);
		hitboxDescer[1].setScale(0, 0);
	}
	if(i == 1 || i == 3 || i == 5){
		escada[0].setPosition(3 * larguraColuna, alturaLinha * (9 - i));
		escada[1].setPosition(35 * larguraColuna, alturaLinha * (9 - i));
	}
	if(i == 2 || i == 4 || i == 6 || i == 8){
		escada[0].setPosition(19 * larguraColuna, alturaLinha * (9 - i));
		escada[1].setScale(0, 0);
		hitbox[1].setScale(0, 0);
		hitboxDescer[1].setScale(0, 0);
	}
	if(i == 7){
		escada[0].setPosition(5 * larguraColuna, alturaLinha * (9 - i));
		escada[1].setPosition(33 * larguraColuna, alturaLinha * (9 - i));
	}

	//Para a hitbox da escada ficar certa
	for (int i = 0; i < 2; ++i) {
		hitbox[i].setScale(larguraColuna / 4, alturaLinha / 10);
		float posQuadradoX = escada[i].getPosition().x + (larguraColuna/2);//move pro meio
		float posQuadradoY = escada[i].getPosition().y + alturaLinha/32;
		hitbox[i].setPosition(posQuadradoX, posQuadradoY);

		hitboxDescer[i].setScale(larguraColuna / 4, alturaLinha / 4.5);
		posQuadradoY = escada[i].getPosition().y - alturaLinha/32;
		hitboxDescer[i].setPosition(posQuadradoX, posQuadradoY);
	}
}

void Escada::draw(sf::RenderWindow *window) {
	window->draw(escada[0]);
	window->draw(escada[1]);
	//window->draw(hitbox[0]);//descomentar para ver a hitbox
	//window->draw(hitbox[1]);
	//window->draw(hitboxDescer[0]);
	//window->draw(hitboxDescer[1]);
}

sf::Sprite Escada::getEscada1() {
	return escada[0];
}

sf::Sprite Escada::getEscada2() {
	return escada[1];
}

sf::Sprite Escada::getHitbox1() {
	return hitbox[0];
}

sf::Sprite Escada::getHitbox2() {
	return hitbox[1];
}

sf::Sprite Escada::getHitboxDescer1() {
	return hitboxDescer[0];
}

sf::Sprite Escada::getHitboxDescer2() {
	return hitboxDescer[1];
}

#endif /* ESCADA_HPP_ */
