#include "../Platform/Platform.hpp"
#include "sandsim.hpp"

void drawToGrid(ss::CellularMatrixEditor*, sf::RenderWindow*);
void drawGridToTexture(ss::CellularMatrix*, sf::Texture*);

int main()
{
	util::Platform platform;

	std::cout << "Hello World!" << std::endl;

	sf::RenderWindow window;
	// in Windows at least, this must be called before creating the window
	float screenScalingFactor = platform.getScreenScalingFactor(window.getSystemHandle());
	// Use the screenScalingFactor
	window.create(sf::VideoMode(900 * screenScalingFactor, 600 * screenScalingFactor), "Falling Sand Simulation");
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

	unsigned int width = 900;
	unsigned int height = 600;

	ss::CellularMatrix cellularMatrix(width, height);
	ss::CellularMatrixEditor matrixEditor(&cellularMatrix);

	//-- setup matrix sprite
	sf::Image image;
	image.create(width, height, sf::Color::Black);
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

		drawToGrid(&matrixEditor, &window);
		cellularMatrix.update();
		drawGridToTexture(&cellularMatrix, &gridTexture);

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

void drawGridToTexture(ss::CellularMatrix* grid, sf::Texture* texture)
{
	unsigned int width = grid->width;
	unsigned int height = grid->height;

	sf::Image image;
	image.create(width, height, sf::Color::White);

	for (unsigned int x = 0; x < width; x++)
	{
		for (unsigned int y = 0; y < height; y++)
		{
			sf::Color color(
				grid->matrix[x][y]->getColor().r,
				grid->matrix[x][y]->getColor().g,
				grid->matrix[x][y]->getColor().b,
				grid->matrix[x][y]->getColor().a);

			image.setPixel(x, y, color);
		}
	}

	texture->loadFromImage(image);
}

void drawToGrid(ss::CellularMatrixEditor* editor, sf::RenderWindow* window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		sf::Vector2i pos = sf::Mouse::getPosition(*static_cast<sf::Window*>(window));
		editor->draw(pos.x, pos.y);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
	{
		sf::Vector2i pos = sf::Mouse::getPosition(*static_cast<sf::Window*>(window));
		editor->erase(pos.x, pos.y);
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
