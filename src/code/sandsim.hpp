#ifndef SANDSIM_HPP
#define SANDSIM_HPP

#include "sandsimelements.hpp"

namespace ss
{

//== Cellular Matrix =====

class CellularMatrix
{
public:
	CellularMatrix(unsigned int _width, unsigned int _height)
	{
		width = _width;
		height = _height;

		initializeMatrix();
	}

public:
	unsigned int width;
	unsigned int height;

	std::vector<std::vector<ssel::Element*>> matrix;

public:
	void update()
	{
		for (unsigned int x = 0; x < width; x++)
		{
			for (unsigned int y = 0; y < height; y++)
			{
				// ssel::Element* element = matrix[x][y];
				// element->step(x, y, this);
			}
		}
	}

	ssel::Element* get(unsigned int x, unsigned int y)
	{
		return matrix[x][y];
	}

	void setExisting(unsigned int x, unsigned int y, ssel::Element* element)
	{
		delete matrix[x][y];
		matrix[x][y] = element;
	}

	void setNew(unsigned int x, unsigned int y, ssel::Elements element)
	{
		delete matrix[x][y];
		matrix[x][y] = ssel::newElement(element);
	}

	void switchCells(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
	{
		ssel::Element* cell1 = matrix[x1][y1];
		matrix[x1][y1] = matrix[x2][y2];
		matrix[x2][y2] = cell1;
	}

private:
	void initializeMatrix()
	{
		for (unsigned int i = 0; i < width; i++)
		{
			std::vector<ssel::Element*> a;
			matrix.push_back(a);
			for (unsigned int j = 0; j < height; j++)
			{
				matrix[i].push_back(new ssel::EmptyCell);
			}
		}
	}
};

//=======

//== Cellular Matrix Editor =====

class CellularMatrixEditor
{
public:
	CellularMatrixEditor(CellularMatrix* mte) :
		matrixToEdit(mte)
	{}

public:
	CellularMatrix* matrixToEdit;

	int brushSize = 10;
	int selectedIndex = 0;

	const unsigned int numberOfDrawableElements = 2;

public:
	void increaseBrushSize(int m = 1)
	{
		brushSize += m;
	}
	void decreaseBrushSize(int m = 1)
	{
		brushSize -= m;
		if (brushSize < 0)
			brushSize = 0;
	}

	void increaseSelectedIndex(int m = 1)
	{
		selectedIndex += m;
		selectedIndex = selectedIndex % numberOfDrawableElements;
	}
	void decreaseSelectedIndex(int m = 1)
	{
		selectedIndex -= m;
		selectedIndex = selectedIndex % numberOfDrawableElements;
	}

	void draw(unsigned int x, unsigned int y)
	{
		for (int i = -brushSize; i < brushSize; i++)
		{
			for (int j = -brushSize; j < brushSize; j++)
			{
				int posX = x + i;
				int posY = y + j;

				if (posX < 0 || posX > (int)matrixToEdit->width - 1 || posY < 0 || posY > (int)matrixToEdit->height)
					continue;

				ssel::Element* drawingElement = ssel::newElement(selectedIndex + 1);

				if (typeid(matrixToEdit->matrix[posX][posY]) == typeid(*drawingElement))
				{
					delete drawingElement;
					continue;
				}

				matrixToEdit->setExisting(posX, posY, drawingElement);
			}
		}
	}
	void erase(unsigned int x, unsigned int y)
	{
		for (int i = -brushSize; i < brushSize; i++)
		{
			for (int j = -brushSize; j < brushSize; j++)
			{
				int posX = x + i;
				int posY = y + j;

				if (posX < 0 || posX > (int)matrixToEdit->width - 1 || posY < 0 || posY > (int)matrixToEdit->height)
					continue;

				if (typeid(matrixToEdit->matrix[posX][posY]) == typeid(ssel::EmptyCell))
					continue;

				matrixToEdit->setExisting(posX, posY, new ssel::EmptyCell);
			}
		}
	}
};

//=======

}

#endif
