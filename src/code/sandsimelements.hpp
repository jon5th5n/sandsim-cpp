#ifndef SANDSIMELEMENTS_HPP
#define SANDSIMELEMENTS_HPP

//== forward declarations ===
namespace ss
{
class CellularMatrix;
}
//=====

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
	virtual std::string getType() = 0;
	virtual Color getColor() = 0;
	virtual void step(unsigned int x, unsigned int y, ss::CellularMatrix* matrix) = 0;

protected:
};

//---

class EmptyCell final : public Element
{
protected:
	Color color { 0, 0, 0, 255 };

public:
	std::string getType() override;
	Color getColor() override;
	void step(unsigned int x, unsigned int y, ss::CellularMatrix* matrix) override;
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
	void step(unsigned int x, unsigned int y, ss::CellularMatrix* matrix) override;
};

//---

class Sand final : public MovableSolid
{
protected:
	Color color { 255, 215, 85, 255 };

public:
	void step(unsigned int x, unsigned int y, ss::CellularMatrix* matrix) override;

	std::string getType() override;
	Color getColor() override;
};

//---

class Stone final : public ImmovableSolid
{
protected:
	Color color { 120, 120, 120, 255 };

public:
	std::string getType() override;
	Color getColor() override;
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

enum Elements : int
{
	eEmptyCell,
	eStone,
	eSand
};

Element* newElement(unsigned int index);

}

#endif