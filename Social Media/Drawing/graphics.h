#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <math.h>
#include <windows.h>
#include <Windows.h>
using namespace std;

HPEN  getPen(int iPEN_STYLE, int iPEN_SIZE, int iCOLORREF);
BOOL  SetPoint(HDC hDC, HPEN hPen, COORD PNT);
BOOL  PlotLine(HDC hDC, HPEN hPen, COORD BGN, COORD END);
BOOL  PlotRect(HDC hDC, HPEN hPen, COORD BGN, COORD END);
BOOL  PlotCirc(HDC hDC, HPEN hPen, COORD BGN, COORD END);
COORD setCordScale(COORD POS, RECT pRECT);

HDC hDC;
HPEN PEN;
HANDLE StdOut;
WORD COLOR;
COORD BGN, POS;

short mov;
short movx;

void initgraph(void)
{
	system("cls");
	mov = 30;
	movx = 0;
	HWND hWnd = GetForegroundWindow();
    RECT    pRECT= {0};
    COORD   POS1  = {0};
    COORD   BGN1  = setCordScale(POS1,pRECT);
    GetWindowRect(hWnd,&pRECT);
    hDC = GetWindowDC(hWnd);		
	PEN = getPen(PS_SOLID, 2, RGB(255,255,255));
	StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
}

void changey(int value) { if (value>-1000 & value <1000) mov = (short)value; }
void changex(int value) { if (value>-1000 & value <1000) movx = (short)value; }
int getmaxx(void) { return 640; }
int getmaxy(void) { return 300; }

wchar_t* convertCharArrayToLPCWSTR(const char* charArray)
{
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}
void drawText(int x, int y, const char*mess, int r, int g, int b) {
	RECT rect;
	LPCWSTR message = convertCharArrayToLPCWSTR(mess);
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);
	GetWindowRect(console_handle, &rect);

	//Here's a 5 pixels wide RED line [from initial 0,0] to 300,300
	SelectObject(device_context, PEN);
	SetTextColor(device_context, RGB(r, g, b));
	SetBkMode(device_context, TRANSPARENT);
	rect.left = x;
	rect.top = y;
	DrawText(device_context, message, -1, &rect, DT_SINGLELINE | DT_NOCLIP);

	ReleaseDC(console_handle, device_context);

}


void setcolorRGB(int r, int g, int b, int size)
{
	PEN = getPen(PS_SOLID, size, RGB(r,g,b));
}
void setcolor(int color, int size)
{
	if (color < 0) color = -color;
	if (color > 15) color %= 16;
	switch (color)
	{
		case 0: PEN = getPen(PS_SOLID, 2, RGB(0,0,0)); break;
		case 1: PEN = getPen(PS_SOLID, 2, RGB(0,0,128)); break;
		case 2: PEN = getPen(PS_SOLID, 2, RGB(0,128,0)); break;
		case 3: PEN = getPen(PS_SOLID, 2, RGB(128,0,0)); break;
		case 4: PEN = getPen(PS_SOLID, 2, RGB(0,128,128)); break;
		case 5: PEN = getPen(PS_SOLID, size, RGB(128,0,128)); break;
		case 6: PEN = getPen(PS_SOLID, 2, RGB(128,128,0)); break;
		case 7: PEN = getPen(PS_SOLID, 2, RGB(0,0,255)); break;
		case 8: PEN = getPen(PS_SOLID, 2, RGB(0,255,0)); break;
		case 9: PEN = getPen(PS_SOLID, 2, RGB(255,0,0)); break;
		case 10: PEN = getPen(PS_SOLID, 2, RGB(0,255,255)); break;
		case 11: PEN = getPen(PS_SOLID, 2, RGB(255,0,255)); break;
		case 12: PEN = getPen(PS_SOLID, 2, RGB(255,255,0)); break;
		case 13: PEN = getPen(PS_SOLID, 2, RGB(192,192,192)); break;
		case 14: PEN = getPen(PS_SOLID, 2, RGB(192,192,192)); break;
		case 15: PEN = getPen(PS_SOLID, size, RGB(255,255,255)); break;
	}
}

void setfontcolor(int color)
{
	if (color < 0) color = -color;
	if (color > 15) color %= 16;
	switch (color)
	{
		case 0: COLOR = (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED); COLOR = COMMON_LVB_REVERSE_VIDEO; break;
		case 1: COLOR = (FOREGROUND_BLUE); break;
		case 2: COLOR = (FOREGROUND_GREEN); break;
		case 3: COLOR = (FOREGROUND_RED); break;
		case 4: COLOR = (FOREGROUND_BLUE | FOREGROUND_GREEN); break;
		case 5: COLOR = (FOREGROUND_BLUE | FOREGROUND_RED); break;
		case 6: COLOR = (FOREGROUND_GREEN | FOREGROUND_RED); break;
		case 7: COLOR = (FOREGROUND_BLUE | FOREGROUND_INTENSITY); break;
		case 8: COLOR = (FOREGROUND_GREEN | FOREGROUND_INTENSITY); break;
		case 9: COLOR = (FOREGROUND_RED | FOREGROUND_INTENSITY); break;
		case 10: COLOR = (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY); break;
		case 11: COLOR = (FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY); break;
		case 12: COLOR = (FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY); break;
		case 13: COLOR = (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);break;
		case 14: COLOR = (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | COMMON_LVB_REVERSE_VIDEO); break;
		case 15: COLOR = (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | COMMON_LVB_REVERSE_VIDEO | FOREGROUND_INTENSITY);break;
	}
	SetConsoleTextAttribute(StdOut, COLOR);
}



void line(int x1,int y1,int x2,int y2)
{
	BGN.X = (short)x1+movx; 
	BGN.Y = (short)y1+mov; 
	POS.X = (short)x2+movx; 
	POS.Y = (short)y2+mov; 
	PlotLine(hDC, PEN, BGN, POS);
}


void putpixel(int x,int y)
{
	line(x,y,x,y);
}

void circle(int x,int y, int radius)
{
	BGN.X = (short)x+movx-radius/2; 
	BGN.Y = (short)y+mov-radius/2; 
	POS.X = (short)x+movx+radius/2; 
	POS.Y = (short)y+mov+radius/2; 
	PlotCirc (hDC, PEN, BGN, POS);
}

void fillcircle(int x, int y, int radius)
{
	for (int k = radius; k >= 0; k--)
	{
		BGN.X = (short)x + movx - radius / 2;
		BGN.Y = (short)y + mov - radius / 2;
		POS.X = (short)x + movx + radius / 2;
		POS.Y = (short)y + mov + radius / 2;
		PlotCirc(hDC, PEN, BGN, POS);
		radius--;
	}
}

void pie(int left, int top, int right, int bot, int x1, int y1, int x2, int y2)
{
	SelectObject(hDC, PEN);
	Pie(hDC, left, top, right, bot, x1, y1, x2, y2);
}

void arc(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	SelectObject(hDC, PEN);
	Arc(hDC, x1, y1, x2, y2, x3, y3, x4, y4);
}

void ellip(int left, int top, int right, int bot)
{
	SelectObject(hDC, PEN);
	Ellipse(hDC, left, top, right, bot);
}

void fillellip(int left, int top, int right, int bot)
{
	while ((right - left) > 1)
	{
		SelectObject(hDC, PEN);
		Ellipse(hDC, left, top, right, bot);
		right--;
		left++;
	}
	while ((bot - top) > 1)
	{
		SelectObject(hDC, PEN);
		Ellipse(hDC, left, top, right, bot);
		bot--;
		top++;
	}
}

void rectangle(int x1,int y1,int x2,int y2)
{
	BGN.X = (short)x1+movx; 
	BGN.Y = (short)y1+mov; 
	POS.X = (short)x2+movx; 
	POS.Y = (short)y2+mov; 
	PlotRect(hDC, PEN, BGN, POS);
}

void fillrectangle(int x1, int y1, int x2, int y2)
{
	while (x1!=x2||y1!=y2)
	{
		BGN.X = (short)x1 + movx;
		BGN.Y = (short)y1 + mov;
		POS.X = (short)x2 + movx;
		POS.Y = (short)y2 + mov;
		PlotRect(hDC, PEN, BGN, POS);
		x1++; y1++;
		if (x2 - x1 == 0)
		{
			x1--;
		}
		if (y2 - y1 == 0)
		{
			y1--;
		}
		if (x2 - x1 == 1 && y2 - y1 == 1)
		{
			break;
		}
	}
}

void printText(string mes, RECT pos, int fontSize, int r1, int g1, int b1, int r2, int g2, int b2)
{
	HFONT f1 =
		CreateFont(fontSize, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_DONTCARE, NULL);
	UINT format = DT_NOCLIP | DT_SINGLELINE | DT_CENTER;
	SelectObject(hDC, f1);
	SetTextColor(hDC, RGB(r1, g1, b1));
	SetBkColor(hDC, RGB(r2, g2, b2));
	int y = (pos.bottom - pos.top) / 2 + 8;
	pos.top += y;
	pos.bottom += y;
	DrawTextA(hDC, mes.c_str(), -1, &pos, format);
	DeleteObject(f1);
}
void fillbigrectangle(int x1, int y1, int x2, int y2)
{
	while (x1 != x2 || y1 != y2)
	{
		BGN.X = (short)x1 + movx;
		BGN.Y = (short)y1 + mov;
		POS.X = (short)x2 + movx;
		POS.Y = (short)y2 + mov;
		PlotRect(hDC, PEN, BGN, POS);
		x1 = x1 + 10; y1 = y1 + 10;
		if (x2 - x1 == 0)
		{
			x1 = x1 - 10;
		}
		if (y2 - y1 == 0)
		{
			y1 = y1 - 10;
		}
		if (x2 - x1 == 10 && y2 - y1 == 10)
		{
			break;
		}
	}
}

void gotoxy(int x, int y)
{
	BGN.X = (short)x; 
	BGN.Y = (short)y; 
    SetConsoleCursorPosition(StdOut, BGN);
}

void outtextxy(int x, int y, string text)
{
	gotoxy(x/8,y/12);
	std::cout << text;
}

void clrscr()
{
	setcolor(0,4);
	for (int i=5;i<=1645;i++)
		line(i-movx,32-mov,i-movx,331-mov);
}

HPEN getPen(int iPEN_STYLE, int iPEN_SIZE, int iCOLORREF)
{
        return CreatePen(iPEN_STYLE, iPEN_SIZE, iCOLORREF);
}
 
BOOL SetPoint(HDC hDC, HPEN hPen, COORD PNT)
{
        EXTLOGPEN pINFO;
        GetObject(hPen,sizeof(EXTLOGPEN),&pINFO);
        SelectObject(hDC,hPen);
        return Ellipse
        (
                hDC,
                PNT.X - pINFO.elpWidth,
                PNT.Y + pINFO.elpWidth, 
                PNT.X + pINFO.elpWidth,
                PNT.Y - pINFO.elpWidth
        );
}
 
BOOL PlotLine(HDC hDC, HPEN hPen, COORD BGN, COORD END)
{
        SelectObject(hDC,hPen);
        MoveToEx(hDC,BGN.X,BGN.Y,NULL);
        return LineTo(  hDC,END.X,END.Y);
}


BOOL PlotRect(HDC hDC, HPEN hPen, COORD BGN, COORD END)
{
    SelectObject(hDC,hPen);
    return Rectangle(hDC,BGN.X, BGN.Y, END.X, END.Y);
}
 
BOOL  PlotCirc(HDC hDC, HPEN hPen, COORD BGN, COORD END)
{
    SelectObject(hDC,hPen);
    return Ellipse(hDC,BGN.X, BGN.Y, END.X, END.Y);
}

COORD setCordScale(COORD POS, RECT pRECT)
{
        if(POS.X == 0)
                POS.X = 1;
        if(POS.Y == 0)
                POS.Y = 1;
 
        int nROWS = 25;
        int nCOLS = 80;
 
        double CX = (pRECT.right - pRECT.left)/nCOLS;
        double CY = (pRECT.bottom - pRECT.top)/nROWS;
 
        //??? ????????? ??????(text mode) ?????  ???????  ??  ??????
		//(80  ??? 40 ??????? ? ?????? ? 25 ????? ? ??????)
        POS.X *= CX;
        POS.Y *= CY;
 
        int xBORDER = GetSystemMetrics(SM_CXBORDER);//?????? ??????? ????
        int yBORDER = GetSystemMetrics(SM_CYMENU);  //?????? ????????? ???? ~= ?????? ????? ????
        int xDRAG       = GetSystemMetrics(SM_CXDRAG);  //????? ???????? ?? ????? ???????? ????
        int yDRAG       = GetSystemMetrics(SM_CYDRAG);  //????? ???????? ?? ?????? ???????? ????
 
        POS.X += xBORDER + xDRAG;//?????? ??????? ???? + ????? ???????? ?? ???????? ????
        POS.Y += yBORDER + yDRAG;
        return POS;
}

#endif
