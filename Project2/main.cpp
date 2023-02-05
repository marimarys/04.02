#include <SFML/Graphics.hpp>
#include "settings.h"
#include "ball.h"
#include "bat.h"
#include "textobj.h"
#include "brick.h"
#include "brickfield.h"
#include "functions.h"
using namespace sf;
enum GameState { PLAY, GAME_OVER };
int main()
{
	RenderWindow window(
		VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
		WINDOW_TITLE,
		Style::Titlebar | Style::Close
	);
	window.setFramerateLimit(60);

	GameState gameState = PLAY;

	Ball ball;
	ballInit(ball);
	Bat bat;
	batInit(bat);
	TextObj scoreText;
	textInit(scoreText, std::to_string(ball.score), TEXT_POS);

	TextObj gameOverText;
	textInit(gameOverText, "GAME OVER", Vector2f{ (WINDOW_WIDTH - 300.f) / 2,
		(WINDOW_HEIGHT - 100) / 2 });
	BrickField field;
	brickFieldInit(field);


	while (window.isOpen())
	{
		//1 îáðàáîòêà ñîáûòèé
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		switch (gameState) {
		case PLAY:
			//îáíîâëåíèå èãðîâûõ îáúåêòîâ (ôóíêöèè update)
			ballUpdate(ball);
			if (ball.shape.getPosition().y + 2 * BALL_RADIUS >= WINDOW_HEIGHT)
				gameState = GAME_OVER;
			batUpdate(bat);
			textUpdate(scoreText, ball.score);
			brickFieldUpdate(field);
			//ïðîâåðêà ñòîëêíîâåíèé
			ballCollideWithBat(ball, bat);
			ballCollidedWithBricks(ball, field);
			//îòðèñîâêà îáúåêòîâ è îáíîâëåíèå îêíà
			window.clear();
			brickFieldDraw(window, field);
			ballDraw(window, ball);
			batDraw(window, bat);
			textDraw(window, scoreText);
			window.display();
			break;
		case GAME_OVER:
			window.clear();
			textDraw(window, gameOverText);
			window.display();
		}
	}

	return 0;
}