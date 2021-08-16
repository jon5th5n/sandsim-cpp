#include "../Platform/Platform.hpp"
#include "sandsim.cpp"

void drawGridToTexture(sf::Texture*);

int main()
{
	util::Platform platform;

	std::cout << "Hello World!" << std::endl;

	sf::RenderWindow window;
	// in Windows at least, this must be called before creating the window
	float screenScalingFactor = platform.getScreenScalingFactor(window.getSystemHandle());
	// Use the screenScalingFactor
	window.create(sf::VideoMode(300 * screenScalingFactor, 200 * screenScalingFactor), "Falling Sand Simulation");
	window.setFramerateLimit(60);

	sf::Event event;

	float fps;
	sf::Clock clock;
	sf::Time previousTime = clock.getElapsedTime();
	sf::Time currentTime;

	//-----------------------

	unsigned int width = 300;
	unsigned int height = 200;

	ss::CellularMatrix cellularMatrix { width, height };

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

		drawGridToTexture(&gridTexture);

		//-------------

		//-- draw -----
		window.clear(sf::Color(255, 255, 255, 255));

		window.draw(gridSprite);

		window.display();
		//-------------

		currentTime = clock.getElapsedTime();
		fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds()); // the asSeconds returns a float
		std::cout << "fps: " << floor(fps) << std::endl;				   // flooring it will make the frame rate a rounded number
		previousTime = currentTime;
	}

	return 0;
}

void drawGridToTexture(sf::Texture* texture)
{
	sf::Image image;
	image.create(300, 200, sf::Color::White);

	for (unsigned int x = 0; x < image.getSize().x; x++)
	{
		for (unsigned int y = 0; y < image.getSize().y; y++)
		{
			image.setPixel(x, y, sf::Color::Magenta);
		}
	}

	texture->loadFromImage(image);
}
