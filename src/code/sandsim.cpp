

namespace ss
{
class CellularMatrix;

//== Elements =====

class Element
{
public:
	void step()
	{
		std::cout << "Base " << a << std::endl;
	}
	int a = 5;
};

//---

class EmptyCell : public Element
{
public:
	void step()
	{
		std::cout << "Derived " << a << std::endl;
	}
	int a = 3;
};

//-- Solids -----

class Solid : public Element
{
};

class MovableSolid : public Solid
{
};

class ImmovableSolid : public Solid
{
};

//---

//-- Fluids -----

class Liquid : public Element
{
};

//---

//-- Gases -----

class Gas : public Element
{
};

//---

//== Cellular Matrix =====

class CellularMatrix
{
public:
	CellularMatrix(unsigned int _width, unsigned int _height)
	{
		width = _width;
		height = _height;

		initializeMatrix();

		// Element* el = new EmptyCell;
		// el->step();
	}

	unsigned int width;
	unsigned int height;

	std::vector<std::vector<Element*>> matrix;

	//-- methods

	void update()
	{
		for (unsigned int x = 0; x < width; x++)
		{
			for (unsigned int y = 0; y < height; y++)
			{
				Element* element = matrix[x][y];
				element->step();
			}
		}
	}

private:
	//-- methods

	void initializeMatrix()
	{
		for (unsigned int i = 0; i < width; i++)
		{
			std::vector<Element*> a;
			matrix.push_back(a);
			for (unsigned int j = 0; j < height; j++)
			{
				matrix[i].push_back(new EmptyCell);
			}
		}
	}
};

//=======

}
