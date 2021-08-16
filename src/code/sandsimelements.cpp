struct Color
{
	Color(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a)
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}

	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
};

namespace ssel
{

class Element
{
	Element(std::unordered_map<std::string, std::any> config)
	{
	}

public:
	std::string type;
	float mass;
	std::unordered_map<std::string, int> color = {
		{ "r", 0 },
		{ "g", 0 },
		{ "b", 0 },
		{ "a", 0 }
	};

private:
public:
	virtual void step()
	{
	}

private:
};

std::unordered_map<std::string, std::any> EmptyCell = {
	{ "type", "empty" },
	{ "mass", std::make_any<float>(0.0) },
	{ "color", std::make_any<Color>(0, 0, 0, 0) },
	{ "step", std::make_any<std::function<void(ss::CellularMatrix)>>([](ss::CellularMatrix cellularMatrix) {}) },
};

std::unordered_map<std::string, std::any> Sand = {
	{ "type", "movableSolid" },
	{ "mass", std::make_any<float>(1.0) },
	{ "color", std::make_any<Color>(150, 105, 0, 255) },
	{ "step", std::make_any<std::function<void(ss::CellularMatrix, unsigned int, unsigned int)>>([](ss::CellularMatrix cellularMatrix, unsigned int x, unsigned int y) {
	 }) },
};

}