#include "../Platform/Platform.hpp"
#include "sandsim.hpp"
#include "sandsimelements.hpp"

void drawToGrid(ss::CellularMatrixEditor*, sf::RenderWindow*, unsigned int);
void drawGridToTexture(ss::CellularMatrix*, sf::Texture*, unsigned int);

int main()
{
	util::Platform platform;

	std::cout << "Hello World!" << std::endl;

	int windowWidth = 900;
	int windowHeight = 600;

	sf::RenderWindow window;
	// in Windows at least, this must be called before creating the window
	float screenScalingFactor = platform.getScreenScalingFactor(window.getSystemHandle());
	// Use the screenScalingFactor
	window.create(sf::VideoMode(windowWidth * screenScalingFactor, windowHeight * screenScalingFactor), "Falling Sand Simulation");
	// window.setFramerateLimit(60);

	sf::Event event;

	float fps = 0;
	sf::Clock clock;
	sf::Time previousTime = clock.getElapsedTime();
	sf::Time currentTime;

	//-----------------------

	sf::Font mainFont;
	mainFont.loadFromFile("C:/Users/kappl/Documents/github/sandsim-cpp/content/Roboto-Regular.ttf");

	//-----------------------

	unsigned int scalingFactor = 3;
	unsigned int width = windowWidth / scalingFactor;
	unsigned int height = windowHeight / scalingFactor;

	ss::CellularMatrix cellularMatrix(width, height);
	ss::CellularMatrixEditor matrixEditor(&cellularMatrix);

	//-- setup matrix sprite
	sf::Image image;
	image.create(windowWidth, windowHeight, sf::Color::Magenta);
	sf::Texture gridTexture;
	gridTexture.loadFromImage(image);
	sf::Sprite gridSprite;
	gridSprite.setTexture(gridTexture);
	//--

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		//-- process --

		drawToGrid(&matrixEditor, &window, scalingFactor);
		cellularMatrix.update();
		drawGridToTexture(&cellularMatrix, &gridTexture, scalingFactor);

		sf::Text fpsCounter(std::to_string((int)fps), mainFont, 20);

		//-------------

		//-- draw -----
		window.clear(sf::Color(255, 255, 255, 255));

		window.draw(gridSprite);
		window.draw(fpsCounter);

		window.display();
		//-------------

		currentTime = clock.getElapsedTime();
		fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds());
		previousTime = currentTime;
	}

	return 0;
}

void drawGridToTexture(ss::CellularMatrix* grid, sf::Texture* texture, unsigned int scalingFactor)
{
	unsigned int gridWidth = grid->width;
	unsigned int gridHeight = grid->height;

	sf::Image image;
	image.create(gridWidth * scalingFactor, gridHeight * scalingFactor, sf::Color::White);

	for (unsigned int x = 0; x < gridWidth; x++)
	{
		for (unsigned int y = 0; y < gridHeight; y++)
		{
			sf::Color color(
				grid->matrix[x][y]->getColor().r,
				grid->matrix[x][y]->getColor().g,
				grid->matrix[x][y]->getColor().b,
				grid->matrix[x][y]->getColor().a);

			for (unsigned int i = 0; i < scalingFactor; i++)
			{
				for (unsigned int j = 0; j < scalingFactor; j++)
				{
					image.setPixel(x * scalingFactor + i, y * scalingFactor + j, color);
				}
			}
		}
	}

	texture->loadFromImage(image);
}

void drawToGrid(ss::CellularMatrixEditor* editor, sf::RenderWindow* window, unsigned int scalingFactor)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		sf::Vector2i pos = sf::Mouse::getPosition(*static_cast<sf::Window*>(window));
		editor->draw(pos.x / scalingFactor, pos.y / scalingFactor);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
	{
		sf::Vector2i pos = sf::Mouse::getPosition(*static_cast<sf::Window*>(window));
		editor->erase(pos.x / scalingFactor, pos.y / scalingFactor);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		editor->increaseBrushSize();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		editor->decreaseBrushSize();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		editor->increaseSelectedIndex();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		editor->decreaseSelectedIndex();
	}
}
