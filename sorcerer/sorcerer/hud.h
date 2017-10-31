#pragma once
#include <SFML\Graphics.hpp>
class Hud
{
public:
	Hud();
	~Hud();
	
	void Draw(sf::RenderWindow &window);
	void ChangeScore(unsigned int player, unsigned int score);
	void DrawResultText(sf::RenderWindow &window);
	void SetResultText(unsigned int state);
public:

private:
	sf::Font font;
	sf::Text player_1_text;
	sf::Text player_2_text;
	sf::Text resultText;
private:

};