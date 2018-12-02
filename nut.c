/*
 * NUT: Nano Unit Tests for CARME
 *
 * Copyright (c) 2018 Dmitriy Purgin
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include <PicoGUI.h>
#include <pg_font.h>
#include <pxa270.h>

#define PG_COL_DARKBLUE 0x000066
#define PG_COL_DARKRED 0x660000
#define PG_COL_DARKGREEN 0x006600
#define PG_COL_GRAY 0xa8a8a8

static int g_currentY = 0;
static int g_passes = 0;
static int g_fails = 0;

static void nut_next_page(void)
{
	g_currentY = 9;

	PG_Init(0);
	PG_SetBackGroundColor(PG_ColorRGB(PG_COL_DARKBLUE));
	PG_SetForeGroundColor(PG_ColorRGB(PG_COL_YELLOW));
	PG_Clear();

	PG_SetForeGroundColor(PG_ColorRGB(PG_COL_GRAY));
	PG_DrawFilledRectangle(0, 0, PG_GetXres(), 10);

	PG_SetFont(&font_rom8x8);
	PG_GotoXY(0, g_currentY);

	PG_SetForeGroundColor(PG_ColorRGB(PG_COL_BLACK));
	PG_SetBackGroundColor(PG_ColorRGB(PG_COL_GRAY));
	PG_PutString("  Nano Unit Tests");

	PG_SetForeGroundColor(PG_ColorRGB(PG_COL_DARKRED));
	PG_GotoXY(16, g_currentY);
	PG_PutChar('N');

	PG_GotoXY(56, g_currentY);
	PG_PutChar('U');

	PG_GotoXY(96, g_currentY);
	PG_PutChar('T');
}

static void nut_wait_input(void)
{
	PG_SetForeGroundColor(PG_ColorRGB(PG_COL_GRAY));
	PG_DrawFilledRectangle(0, PG_GetYres() - 10, PG_GetXres(), PG_GetYres());

	PG_SetForeGroundColor(PG_ColorRGB(PG_COL_BLACK));
	PG_SetBackGroundColor(PG_ColorRGB(PG_COL_GRAY));
	PG_GotoXY(0, PG_GetYres() - 1);
	PG_PutString("Press T0..T3 to continue");

	while ((GPLR3 & 0xE8) == 0);
}

void nut_init(void)
{
	g_passes = 0;
	g_fails = 0;
	nut_next_page();
}

void nut_end(void)
{
	nut_wait_input();

	nut_next_page();

	int total = g_passes + g_fails;
	int passedWidth = (float)PG_GetXres() * g_passes / total;

	PG_SetForeGroundColor(PG_ColorRGB(PG_COL_DARKGREEN));
	PG_DrawFilledRectangle(0, 29, passedWidth, 39);

	PG_SetForeGroundColor(PG_ColorRGB(PG_COL_DARKRED));
	PG_DrawFilledRectangle(passedWidth, 29, PG_GetXres(), 39);

	PG_SetForeGroundColor(PG_ColorRGB(PG_COL_YELLOW));
	PG_SetBackGroundColor(PG_ColorRGB(PG_COL_DARKBLUE));
	PG_GotoXY(0, 49);
	PG_PutString("Total tests:");
	PG_GotoXY(0, 59);
	PG_PutString("     Passes:");
	PG_GotoXY(0, 69);
	PG_PutString("      Fails:");

	PG_SetForeGroundColor(PG_ColorRGB(PG_COL_WHITE));

	PG_GotoXY(104, 49);
	PG_PutDec(total, 0);
	PG_GotoXY(104, 59);
	PG_PutDec(g_passes, 0);
	PG_GotoXY(104, 69);
	PG_PutDec(g_fails, 0);

	nut_wait_input();
}

void nut_next_test(const char* name)
{
	if (g_currentY >= PG_GetYres() - 20)
	{
		nut_wait_input();
		nut_next_page();
	}

	g_currentY += 10;

	PG_SetForeGroundColor(PG_ColorRGB(PG_COL_YELLOW));
	PG_SetBackGroundColor(PG_ColorRGB(PG_COL_DARKBLUE));
	PG_GotoXY(0, g_currentY);
	PG_PutString(name);
}

void nut_test_passes()
{
	++g_passes;

	PG_SetForeGroundColor(PG_ColorRGB(PG_COL_GREEN));
	PG_SetBackGroundColor(PG_ColorRGB(PG_COL_DARKBLUE));
	PG_GotoXY(PG_GetXres() - 24, g_currentY);
	PG_PutString(" OK");
}

void nut_test_fails()
{
	++g_fails;

	PG_SetForeGroundColor(PG_ColorRGB(PG_COL_RED));
	PG_SetBackGroundColor(PG_ColorRGB(PG_COL_DARKBLUE));
	PG_GotoXY(PG_GetXres() - 40, g_currentY);
	PG_PutString(" FAIL");
}
