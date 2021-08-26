
#include "sandsimelements.hpp"
#include "sandsim.hpp"

using namespace ssel;

//== Elements =====

//-- EmptyCell ---

std::string EmptyCell::getType()
{
	return "Empty";
}

Element::Color EmptyCell::getColor()
{
	return color;
}
void EmptyCell::step(unsigned int x, unsigned int y, ss::CellularMatrix* matrix)
{}

//=======

//== Solids =====

//-- MovableSolid ---

//-- ImmovableSolid ---

void ImmovableSolid::step(unsigned int x, unsigned int y, ss::CellularMatrix* matrix)
{}

//---------------

//-- Sand ---

void Sand::step(unsigned int x, unsigned int y, ss::CellularMatrix* matrix)
{
	if (matrix->get(x, y + 1)->getType() == "Empty")
		matrix->switchCells(x, y, x, y + 1);
	else if (matrix->get(x + 1, y + 1)->getType() == "Empty")
		matrix->switchCells(x, y, x + 1, y + 1);
	else if (matrix->get(x - 1, y + 1)->getType() == "Empty")
		matrix->switchCells(x, y, x - 1, y + 1);
}

std::string Sand::getType()
{
	return "Sand";
}

Element::Color Sand::getColor()
{
	return color;
}

//---------------

//-- Stone ---

std::string Stone::getType()
{
	return "Stone";
}

Element::Color Stone::getColor()
{
	return color;
}

//=======

//== Fluids =====

//=======

//== Gases =====

//=======

Element* ssel::newElement(unsigned int index)
{
	switch (index)
	{
		case Elements::eEmptyCell:
			return new EmptyCell;
		case Elements::eStone:
			return new Stone;
		case Elements::eSand:
			return new Sand;
		default:
			return new EmptyCell;
	}
}