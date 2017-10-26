#pragma once
#include <SFML\Graphics.hpp>
class Animation
{
public:
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	~Animation();
	void Update(int row, float deltaTime);

public:
	sf::IntRect uvRect;					// Rect for image.

private:
	sf::Vector2u imageCount;			// Counting the image.
	sf::Vector2u currentImage;			// Current image index.

	float totalTime;					// Time for switching frame.
	float switchTime;
};