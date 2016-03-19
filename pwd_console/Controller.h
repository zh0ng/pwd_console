// Controller.h: interface for the CController class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTROLLER_H__BDCD9CDC_3F38_4CD4_A52C_C169B3CCED8F__INCLUDED_)

#define AFX_CONTROLLER_H__BDCD9CDC_3F38_4CD4_A52C_C169B3CCED8F__INCLUDED_
#define RED 0xFE
#define GREEN 0xFD
#define YELLOW 0xFB
#define NONE 0xFF

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CController  
{
public:
	CController();
	virtual ~CController();

	char getKeyCode();

	void LCDDisplay(char c);

	void alarm();
	// 打开LED灯
	void openLED(int which);

	// 成功解锁
	void successUnlock();
private:
	// 按键按下返回true
	bool getRowCol(int &row, int &col);
	// 得到1的位置,个位是0
	int getOnePos(int x);
	// 得到字符
	char getChar(int row, int col);

	// 延时
	void delay(int t);
};

#endif // !defined(AFX_CONTROLLER_H__BDCD9CDC_3F38_4CD4_A52C_C169B3CCED8F__INCLUDED_)
