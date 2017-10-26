#include "Animation.h"


// Object Constructor.
Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
	// Initialize variables for method.
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;

	// Set texture width & height.
	uvRect.width = texture->getSize().x / float(imageCount.x);
	uvRect.height = texture->getSize().y / float(imageCount.y);
}

Animation::~Animation()
{
}

// Method for update the image sprite.
void Animation::Update(int row, float deltaTime) {
	currentImage.y = row;
	totalTime += deltaTime;

	// Switch image.
	if (totalTime >= deltaTime) {
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= imageCount.x) {
			currentImage.x = 0;	// Reset index if index.x more than limit.
		}
	}
	// Set image point.
	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;
}