// Controller.cpp: implementation of the CController class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IO.h"
#include "Controller.h"
#include "COutput.h"
#include "..\qth9054fun.h"
#define P8255A     0x20
#define P8255B     0x21
#define P8255C     0x22
#define P8255MODE  0x23

#define P8254_T0  0x00
#define P8254_T1  0x01
#define P8254_T2  0x02
#define P8254MODE 0x03

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CController::CController()
{
	IO8bWrite(P8255MODE, 0x81);
	//IO8bWrite(P8255A,0x00);
}

char CController::getKeyCode()
{
	int row, col, preRow, preCol;
	bool prePressed = false, pressed = false;
	while (1)
	{
		if (!pressed && prePressed)
		{
			//CCOutput::outputInt("row=", preRow);
			//CCOutput::outputInt("col=", preCol);
			return getChar(preRow, preCol);
		}
		prePressed = pressed;
		preRow = row;
		preCol = col;
		pressed = getRowCol(row, col);
		//CCOutput::outputInt("row=", row);
		//CCOutput::outputInt("col=", col);
		Sleep(10);
	}
	return 0;
}


bool CController::getRowCol(int &row, int &col)
{
	for (int i = 0; i < 4; i++)
	{
		row = i;
		int state = IO8bRead(P8255B);
		state &= 0xF0;
		state |= (1 << i);
		IO8bWrite(P8255B, state);

		int c = IO8bRead(P8255C);
		//CCOutput::outputInt("c=", c);
		col = getOnePos(c);
		//CCOutput::outputInt("col=", col);
		if (col != -1)
		{
			return true;
		}
	}
	return false;
}

int CController::getOnePos(int x)
{
	for (int i = 0; i < 30; i++)
	{
		if ( (1 << i) == x)
			return i;
	}
	return -1;
}

char CController::getChar(int row, int col)
{
	char s[][4] =
	{
		{'1', '2', '3', 'M'},
		{'4', '5', '6', 'O'},
		{'7', '8', '9', 'A'},
		{'0', '#', '*', 'S'}
	};
	return s[row][col];
}


void CController::LCDDisplay(char c)
{
	c = '*';
	//IO8bWrite(P8255A, c);
	//IO8bWrite(P8255MODE, 0x0E);
	//IO8bWrite(P8255MODE, 0x0F);

	IO8bWrite(0x20, c);
}

CController::~CController()
{

}

void CController::alarm()
{
	openLED(YELLOW);
	delay(5000);
	openLED(NONE);
}

void CController::openLED(int which)
{
	int c = IO8bRead(P8255C) & 0x0F;
	CCOutput::outputInt("c=", c);
	c |= which;
	CCOutput::outputInt("c=", c);
	IO8bWrite(P8255C, c);
}


void CController::delay(int t)
{
	//Sleep(t);
	IO8bWrite(P8254MODE, 0x31);
	IO8bWrite(P8254_T0, t / 1000 - 1);
	IO8bWrite(P8254_T0, 0x00);

	//ÖÃ1
	int b = IO8bRead(P8255B) & 0xFF;
	b &= 0x7F;
	IO8bWrite(P8255B, b);
	b |= 0x80;
	IO8bWrite(P8255B, b);

	int c = IO8bRead(P8255C) & 0xFF;
	while (!(c & 0x80))
	{
		c = IO8bRead(P8255C) & 0xFF;
		if (c)
			CCOutput::outputInt("c=", c);
	}
	CCOutput::outputInt("ccc=", c);

	//IO8bWrite(P8254_T0, 0x0A);
	//IO8bWrite(P8254_T0, 0x00);

	//int a = IO8bRead(P8255A) & 0xFF;
	//IO8bWrite(P8255A, a | 0xF7);
	//IO8bWrite(P8255A, a | 0x08);

//	int b = IO8bRead(P8255B) & 0xFF;
//	while(~(b & 0x80))
//	{
//		b = IO8bRead(P8255B) & 0xFF;
//	}
}

void CController::successUnlock()
{
	openLED(GREEN);
	delay(10000);
	openLED(NONE);
}