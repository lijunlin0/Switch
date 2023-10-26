#include<graphics.h>
#include<conio.h>
#include<math.h>
#include<iostream>
#include"time.h"
using namespace std;
long long time::update_ms = 0;
void move(COLORREF cc, COLORREF rc,bool is_right)
{
	int index = 0;
	//COLORREF circle_color = RGB(30, 144, 255);
	//COLORREF roundrect_color = RGB(135, 135, 135);
	COLORREF background_color;
	if (is_right)
	{
		int bkcolor = 0;
		int color_index = 0;
		while (index <= 300)
		{
			long long current = time::current_time();
			if (current - time::update_ms < time::frame_ms)
			{
				continue;
			}
			time::update_ms = current;


			BeginBatchDraw();

			//背景色
			setfillcolor(RGB(255 - bkcolor, 255 - bkcolor, 255 - bkcolor));
			solidrectangle(0, 0, 800, 800);

			//矩形
			setfillcolor(RGB((GetRValue(rc) + color_index), (GetGValue(rc) + color_index), (GetBValue(rc) + color_index)));
			solidroundrect(150, 300, 650, 500, 200, 200);

			//圆
			setfillcolor(cc);
			solidcircle(250 + index, 400, 80);

			EndBatchDraw();
			
			
			index += 5;
			color_index += 2;
			bkcolor += 4;
		}
	}
	else
	{
		int bkcolor = 0;
		int color_index = 0;
		while (index >= -300)
		{
			long long current = time::current_time();
			if (current - time::update_ms < time::frame_ms)
			{
				continue;
			}
			time::update_ms = current;

			background_color = WHITE;

			BeginBatchDraw();

			//背景色
			setfillcolor(RGB(0 + bkcolor, 0 + bkcolor, 0 + bkcolor));
			solidrectangle(0, 0, 800, 800);
			
			//矩形
			setfillcolor(RGB(255 - color_index, 255 - color_index, 255 - color_index));
			solidroundrect(150, 300, 650, 500, 200, 200);

			//圆
			setfillcolor(cc);
			solidcircle(550 + index, 400, 80);
			EndBatchDraw();

			index -= 5;
			color_index += 2;
			bkcolor += 4;
		}
	}
}

void on_off()
{
	ExMessage m;
	bool is_big = false;
	//背景填充颜色
	COLORREF background_color = RGB(255, 255, 255);
	//圆形填充颜色
	COLORREF circle_color = RGB(30, 144, 255);
	//矩形填充颜色
	COLORREF roundrect_color = RGB(135, 135, 135);
	COLORREF roundrect_color_none = RGB(60, 60, 60);

	setfillcolor(background_color);
	solidrectangle(0, 0, 800, 800);
	//圆角矩形
	setfillcolor(roundrect_color_none);
	solidroundrect(150, 300, 650, 500, 200, 200);

	//圆形4
	int r = 80;
	setfillcolor(circle_color);
	solidcircle(250, 400, r);
	bool is_left = true;
	setlinestyle(5);

	while (true)
	{
		bool b = peekmessage(&m,EX_MOUSE);

		//变大（按下并在区域内）
		if (b&&m.message == WM_LBUTTONDOWN && m.x >= 200 && m.x <= 600 && m.y >= 300 && m.y <= 500)
		{
			is_big = true;
			while (r <= 90)
			{
				long long current = time::current_time();
				if (current - time::update_ms < time::frame_ms)
				{
					continue;
				}
				time::update_ms = current;

				BeginBatchDraw();

				setfillcolor(RGB(30, 144, 255));
				if (is_left)
				{
					solidcircle(250, 400, r);
				}
				else
				{
					solidcircle(550,400, r);
				}

				EndBatchDraw();
				r += 1;
			}
			r = 80;
		}
		//变小（弹起并在区域外）
		if (is_big && b && m.message == WM_LBUTTONUP && !(m.x >= 200 && m.x <= 600 && m.y >= 300 && m.y <= 500))
		{
			is_big = false;
			r = 90;
			while (r >= 80)
			{
				long long current = time::current_time();
				if (current - time::update_ms < time::frame_ms)
				{
					continue;
				}
				time::update_ms = current;

				BeginBatchDraw();
				if (is_left)
				{
					setfillcolor(RGB(135, 135, 135));
					solidcircle(250, 400, r);
					setfillcolor(RGB(30, 144, 255));
					solidcircle(250, 400, r -= 1);
				}
				else
				{
					setfillcolor(RGB(255, 255, 255));
					solidcircle(550, 400, r);
					setfillcolor(RGB(30, 144, 255));
					solidcircle(550, 400, r -= 1);
				}
				EndBatchDraw();
			}
		}
		//移动（弹起并在区域内）
		if (b&&m.message == WM_LBUTTONUP && m.x >= 200 && m.x <= 600 && m.y >= 300 && m.y <= 500)
		{
			is_big = false;
			if (is_left)
			{
				is_left = false;
				move(circle_color,roundrect_color,true);
			}
			else
			{
				is_left = true;
				move(circle_color, roundrect_color,false);
			}
		}
	}
}

int main()
{
	initgraph(800, 800);
	int r = 0, g = 0, b = 0;
	double t = 0;
	const double PI = 3.14159265358979323846;

	on_off();

	while (true)
	{
		r = (int)(127.5 * (sin(t) + 1));
		g = (int)(127.5 * (sin(t + 2 * PI / 3) + 1));
		b = (int)(127.5 * (sin(t + 4 * PI / 3) + 1));
		//cout << r << ' ' << g << ' ' << b << endl;
		//cout << t << endl;
		COLORREF c = RGB(r,g,b);
		setfillcolor(c);
		solidcircle(400, 400, 200);
		t += 0.0001;
	}
	

	system("pause");
	return 0;
}