#ifndef SANDSIM_HPP
#define SANDSIM_HPP

//== forward declarations ===
namespace ssel
{
class Element;
enum Elements : int;
}
//=====

namespace ss
{

//== Cellular Matrix =====

class CellularMatrix
{
public:
	CellularMatrix(unsigned int _width, unsigned int _height);

public:
	unsigned int width;
	unsigned int height;

	std::vector<std::vector<ssel::Element*>> matrix;

	ssel::Element* outOfBoundCell;

public:
	void update();

	ssel::Element* get(unsigned int x, unsigned int y);

	void setExisting(unsigned int x, unsigned int y, ssel::Element* element);

	void setNew(unsigned int x, unsigned int y, ssel::Elements element);

	void switchCells(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);

private:
	void initializeMatrix();
};

//=======

//== Cellular Matrix Editor =====

class CellularMatrixEditor
{
public:
	CellularMatrixEditor(CellularMatrix* mte);

public:
	CellularMatrix* matrixToEdit;

	int brushSize = 10;
	int selectedIndex = 0;

	const unsigned int numberOfDrawableElements = 2;

public:
	void increaseBrushSize(int m = 1);
	void decreaseBrushSize(int m = 1);

	void increaseSelectedIndex(int m = 1);
	void decreaseSelectedIndex(int m = 1);

	void draw(unsigned int x, unsigned int y);
	void erase(unsigned int x, unsigned int y);
};

//=======

}

#endif
