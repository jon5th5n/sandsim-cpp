#ifndef SANDSIMELEMENTS_HPP
#define SANDSIMELEMENTS_HPP

#include "sandsim.hpp"

namespace ssel
{

//== Elements =====

class Element
{
public:
	virtual ~Element() = default;

public:
	struct Color
	{
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;
	};

public:
protected:
	Color color { 5, 5, 5, 255 };

public:
	virtual Color getColor() = 0;

	// virtual void step(unsigned int x, unsigned int y, ss::CellularMatrix* matrix)
	// {}

protected:
};

//---

class EmptyCell final : public Element
{
protected:
	Color color { 0, 0, 0, 255 };

public:
	Color getColor() override
	{
		return color;
	}
	// void step(unsigned int x, unsigned int y, ss::CellularMatrix* matrix) override
	// {
	// }
};

//-----

//-- Solids -----

class Solid : public Element
{
};

class MovableSolid : public Solid
{
};

class ImmovableSolid : public Solid
{
public:
	// void step(unsigned int x, unsigned int y, ss::CellularMatrix* matrix) override
	// {
	// }
};

//---

class Sand final : public MovableSolid
{
protected:
	Color color { 255, 215, 85, 255 };

public:
	// void step(unsigned int x, unsigned int y, ss::CellularMatrix* matrix) override
	// {
	// 	if (typeid(*matrix->get(x, y + 1)) == typeid(ssel::EmptyCell))
	// 		matrix->switchCells(x, y, x, y + 1);
	// 	else if (typeid(*matrix->get(x + 1, y + 1)) == typeid(ssel::EmptyCell))
	// 		matrix->switchCells(x, y, x + 1, y + 1);
	// 	else if (typeid(*matrix->get(x - 1, y + 1)) == typeid(ssel::EmptyCell))
	// 		matrix->switchCells(x, y, x - 1, y + 1);
	// }

	Color getColor() override
	{
		return color;
	}
};

//---

class Stone final : public ImmovableSolid
{
protected:
	Color color { 120, 120, 120, 255 };

public:
	Color getColor() override
	{
		return color;
	}
};

//-----

//-- Fluids -----

class Liquid : public Element
{
};

//-----

//-- Gases -----

class Gas : public Element
{
};

//-----

enum Elements
{
	eEmptyCell,
	eStone,
	eSand
};

Element* newElement(unsigned int);
Element* newElement(unsigned int index)
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

}

#endif