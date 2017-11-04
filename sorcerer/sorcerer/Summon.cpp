#include "Summon.h"
#include <SFML\Graphics.hpp>
#include "Animation.h"

Summon::Summon(sf::Texture* texture, sf::Vector2u imageCount, float switchTime) 
	: animation(texture, imageCount, switchTime)
{
	body.setSize(sf::Vector2f(32.0f, 32.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(texture);
	exploded = false;

	Animation animation(texture, imageCount, switchTime);
	textureSize = texture->getSize();
	textureSize.x /= 3;
	textureSize.y /= 1;
}


Summon::~Summon()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) {
		if (playerSkill < 15 && playerSkill >= 20) {

		} else if (playerSkill < 20 && playerSkill >= 25) {

		}
	}
}

void Summon::Update(float deltaTime)
{
}

void Summon::Draw(sf::RenderWindow & window)
{
	if (!exploded) window.draw(body);
}
