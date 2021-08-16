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

	unsigned int width;
	unsigned int height;

	std::vector<std::vector<ssel::Element>> matrix;

	//--

	void update()
	{
		for (unsigned int x = 0; x < width; x++)
		{
			for (unsigned int y = 0; y < height; y++)
			{
				ssel::Element* element = &matrix[x][y];
				element->step();
			}
		}
	}

	ssel::Element getCell(unsigned int x, unsigned int y)
	{
		return matrix[x][y];
	}

	void switchCell(unsigned int currentCellX, unsigned int currentCellY, unsigned int switchingCellX, unsigned int switchingCellY)
	{
		ssel::Element switchingCell = matrix[switchingCellX][switchingCellY];
		matrix[switchingCellX][switchingCellY] = matrix[currentCellX][currentCellY];
		matrix[currentCellX][currentCellY] = switchingCell;
	}

private:
	//-- methods

	void initializeMatrix()
	{
		for (unsigned int i = 0; i < width; i++)
		{
			std::vector<ssel::Element> a;
			matrix.push_back(a);
			for (unsigned int j = 0; j < height; j++)
			{
				ssel::Element b;
				matrix[i].push_back(b);
			}
		}
	}
};

//=======

}
