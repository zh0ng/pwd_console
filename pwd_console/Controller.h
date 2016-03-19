// Controller.h: interface for the CController class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTROLLER_H__BDCD9CDC_3F38_4CD4_A52C_C169B3CCED8F__INCLUDED_)

#define AFX_CONTROLLER_H__BDCD9CDC_3F38_4CD4_A52C_C169B3CCED8F__INCLUDED_
#define RED 0xEF
#define GREEN 0xDF
#define YELLOW 0xBF
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
	// ��LED��
	void openLED(int which);

	// �ɹ�����
	void successUnlock();
private:
	// �������·���true
	bool getRowCol(int &row, int &col);
	// �õ�1��λ��,��λ��0
	int getOnePos(int x);
	// �õ��ַ�
	char getChar(int row, int col);

	// ��ʱ
	void delay(int t);
};

#endif // !defined(AFX_CONTROLLER_H__BDCD9CDC_3F38_4CD4_A52C_C169B3CCED8F__INCLUDED_)
