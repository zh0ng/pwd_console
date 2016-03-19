// COutput.cpp: implementation of the CCOutput class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IO.h"
#include "COutput.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCOutput::CCOutput()
{

}

CCOutput::~CCOutput()
{

}

void CCOutput::outputInt(const char* msg, int i)
{
	char s[256];
	sprintf(s, "%s%d\n", msg, i);
	TRACE(s);
}

void CCOutput::outputChar(const char* msg, char c)
{
	char s[256];
	sprintf(s, "%s%c\n", msg, c);
	TRACE(s);
}