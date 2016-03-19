// COutput.h: interface for the CCOutput class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COUTPUT_H__728C78F7_329A_49EC_9788_45EDF236989B__INCLUDED_)
#define AFX_COUTPUT_H__728C78F7_329A_49EC_9788_45EDF236989B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCOutput  
{
public:
	CCOutput();
	virtual ~CCOutput();
	static void outputInt(const char* ,int i);
	static void outputChar(const char* ,char c);
};

#endif // !defined(AFX_COUTPUT_H__728C78F7_329A_49EC_9788_45EDF236989B__INCLUDED_)
