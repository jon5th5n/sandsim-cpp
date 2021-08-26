
#include "sandsim.hpp"
#include "sandsimelements.hpp"

using namespace ss;

//== Cellular Matrix =====

CellularMatrix::CellularMatrix(unsigned int _width, unsigned int _height)
{
	width = _width;
	height = _height;

	initializeMatrix();

	outOfBoundCell = new ssel::EmptyCell;
}

void CellularMatrix::update()
{
	for (unsigned int x = 0; x < width; x++)
	{
		for (unsigned int y = 0; y < height; y++)
		{
			ssel::Element* element = matrix[x][y];
			element->step(x, y, this);
		}
	}
}

ssel::Element* CellularMatrix::get(unsigned int x, unsigned int y)
{
	if (x >= width || y >= height)
		return outOfBoundCell;
	return matrix[x][y];
}

void CellularMatrix::setExisting(unsigned int x, unsigned int y, ssel::Element* element)
{
	if (x >= width || y >= height)
		return;
	delete matrix[x][y];
	matrix[x][y] = element;
}

void CellularMatrix::setNew(unsigned int x, unsigned int y, ssel::Elements element)
{
	if (x >= width || y >= height)
		return;
	delete matrix[x][y];
	matrix[x][y] = ssel::newElement(element);
}

void CellularMatrix::switchCells(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
	if ((x1 >= width || y1 >= height) && (x2 >= width || y2 >= height))
		return;

	if (x2 >= width || y2 >= height)
	{
		setExisting(x1, y1, new ssel::EmptyCell);
		return;
	}
	if (x1 >= width || y1 >= height)
	{
		setExisting(x2, y2, new ssel::EmptyCell);
		return;
	}

	ssel::Element* cell1 = matrix[x1][y1];
	matrix[x1][y1] = matrix[x2][y2];
	matrix[x2][y2] = cell1;
}

void CellularMatrix::initializeMatrix()
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

//=======

//== Cellular Matrix Editor =====

CellularMatrixEditor::CellularMatrixEditor(CellularMatrix* mte) :
	matrixToEdit(mte)
{}

void CellularMatrixEditor::increaseBrushSize(int m)
{
	brushSize += m;
}
void CellularMatrixEditor::decreaseBrushSize(int m)
{
	brushSize -= m;
	if (brushSize < 0)
		brushSize = 0;
}

void CellularMatrixEditor::increaseSelectedIndex(int m)
{
	selectedIndex += m;
	selectedIndex = selectedIndex % numberOfDrawableElements;
}
void CellularMatrixEditor::decreaseSelectedIndex(int m)
{
	selectedIndex -= m;
	selectedIndex = selectedIndex % numberOfDrawableElements;
}

void CellularMatrixEditor::draw(unsigned int x, unsigned int y)
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
void CellularMatrixEditor::erase(unsigned int x, unsigned int y)
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

//=======
