/*ConsolePixelDrawing.cpp*/
#include "ConsolePixelDrawing.h"

ConsolePixelFrame::ConsolePixelFrame(int px, int py)		// costructor
{
	console = GetConsoleWindow();			// get window console
	console_DC = GetDC(console);
	pShapes = new Shape * [MAX_NUM_SHAPES];		// dynamic memory allocation
	num_shapes = 0;
	capacity = MAX_NUM_SHAPES;
	cpfr_px = px;
	cpfr_py = py;
}

ConsolePixelFrame::~ConsolePixelFrame()						// destructor
{
	//delete[] shapes;
	//ReleaseDC(console, console_DC);
}

void ConsolePixelFrame::addShape(Shape* pNew_shape)			// add Shape
{
	if (num_shapes >= capacity)							// shape이 용량을 초과한경우
	{
		cout << "ConsolePixelFrame::addShape ==> Expanding capacity to " << capacity * 2 << "shapes " << endl;
		Shape** old_shapes = pShapes;
		pShapes = new Shape * [capacity * 2];
		if (pShapes == NULL)
		{
			cout << "Error in expanding dynamic array for shapes capacity "
				<< capacity * 2 << "shapes " << endl;
			exit;
		}
		for (int i = 0; i <	num_shapes; i++)
		{
			pShapes[i] = old_shapes[i];
		}
		capacity = capacity * 2;
		delete[] old_shapes;
	}
	pShapes[num_shapes] = pNew_shape;			// newShape 입력
	num_shapes++;
}

void ConsolePixelFrame::drawShapes()		// draw
{
	//system("mode con: lines=50 cols=150 | title ANTL");		// console 화면의 크기 및 title 설정
	cout << "Drawing " << num_shapes << " shapes :" << endl;
	if (num_shapes > 0)
	{
		for (int i = 0; i < num_shapes; i++)
			pShapes[i]->draw(*this);		// draw late binding
	}
}

bool ConsolePixelFrame::isValidIndex(int index)			// index check
{
	if ((index < 0) || (index >= num_shapes))			// 잘못된 index인 경우 return false
	{
		cout << "Error in ConsolePixelFrame::isValidIndex : current number of shapes (" << num_shapes << "), index : " << index << ") !!" << endl;
		return false;
	}
	else
		return true;
}