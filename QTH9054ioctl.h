// QTH9054ioctl.h
//
// Define control codes for QTH9054 driver
//

#ifndef __QTH9054ioctl__h_
#define __QTH9054ioctl__h_

#include <winioctl.h>

#define WM_PCI9054_INTERRUPT		WM_USER + 0x100

#define IOCTL_PCI_CON CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_IO_READ CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_IO_WRITE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_MEM_READ CTL_CODE(FILE_DEVICE_UNKNOWN, 0x803, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_MEM_WRITE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x804, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_INT_OPEN CTL_CODE(FILE_DEVICE_UNKNOWN, 0x805, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_INT_CLOSE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x806, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_STR_ADR CTL_CODE(FILE_DEVICE_UNKNOWN, 0x807, METHOD_BUFFERED, FILE_ANY_ACCESS)


#define IOCTL_IO8b_READ CTL_CODE(FILE_DEVICE_UNKNOWN, 0x808, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_IO8b_WRITE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x809, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_MEM8b_READ CTL_CODE(FILE_DEVICE_UNKNOWN, 0x80a, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_MEM8b_WRITE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x80b, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_IO16b_READ CTL_CODE(FILE_DEVICE_UNKNOWN, 0x80c, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_IO16b_WRITE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x80d, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_MEM16b_READ CTL_CODE(FILE_DEVICE_UNKNOWN, 0x80e, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_MEM16b_WRITE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x80f, METHOD_BUFFERED, FILE_ANY_ACCESS)

struct pci_cfg
{
	ULONG	MemBase[2];         //memory base address
	ULONG	MemLength[2];		//memory length
	ULONG	IOBase[2];		    //IO base address
	ULONG	IOPortLength[2];    //IO base length 
	ULONG	IRQ;			    //Interrupt number
};//*pci;						

struct Buffers
{
	ULONG	Address;
	ULONG	Data;
};//*prd;

struct Start_adr
{
	ULONG address;
	ULONG mode;
};//*pstr;


BOOL  Init9054();
void  RAM32bWrite(ULONG adr,ULONG dat);
ULONG RAM32bRead(ULONG adr);
void  IO32bWrite(ULONG adr,ULONG dat);
ULONG IO32bRead(ULONG adr);
void  IO8bWrite(ULONG adr,ULONG dat);
ULONG IO8bRead(ULONG adr);
void  RAM8bWrite(ULONG adr,ULONG dat);
ULONG RAM8bRead(ULONG adr);

void  IO16bWrite(ULONG adr,USHORT dat);
ULONG IO816Read(ULONG adr);
void  RAM16bWrite(ULONG adr,ULONG dat);
ULONG RAM16bRead(ULONG adr);

BOOL  OpenInt(void);
BOOL  CloseInt(void);
void  DMAWrite32(ULONG adr,ULONG len,ULONG dat);
void DMAWrite(ULONG adr,ULONG len,UINT * dat);
void  DMARead(ULONG adr,ULONG len,UINT *buf);
void  MRAM8bWrite(int Seg,int dat);
CString MRam8bRead(int Seg);
CString MRam8bDRead(int Seg);
void  MRAM32bWrite(int Seg,int dat);
CString MRam32bRead(int Seg);
CString MRam32bDRead(int Seg);

UINT InterruptAttachThreadLocalInt(LPVOID pParam);
int StartIrqThread(HWND hWnd);
int StopIrqThread();

extern HANDLE hDevice;
extern HANDLE hEvent;
extern DWORD nRet;
extern struct pci_cfg *pci;
extern struct Buffers *prd;
extern struct Start_adr *pstr;


#endif
