#include <allegro.h>

int tempo = 10;
double x=150, y=300, dx=0.25, dy=-0.25, ddy=0.001, ddx=0, oporx=0.001, opory=0.001, z;
double fps;
volatile unsigned long int licznik;
unsigned long int goniec, starylicznik, li, zl;

void init();
void deinit();
void tik()
{
	licznik+=tempo;
}
END_OF_FUNCTION(tik)



int main()
{
	init();
	
	BITMAP *pilka, *ekran1, *ekran2;
	BITMAP *nieaktywny;
	
	
	pilka = create_bitmap(31, 31);
	clear_bitmap(pilka);
	circlefill(pilka, 15, 15, 15, makecol(120, 120, 200));
	
	ekran1 = create_video_bitmap(SCREEN_W, SCREEN_H);
	ekran2 = create_video_bitmap(SCREEN_W, SCREEN_H);
	nieaktywny = ekran1;
	
	install_int(&tik, 10);
	goniec = licznik;
	
	starylicznik = 0;
	li = 0;
	
	while (!key[KEY_ESC])
	{
		while(goniec != licznik)//dogonic licznik
		{
			x += dx;
			y += dy;
			
			if(y > SCREEN_H-32)
			{
				z = y-dy;//stara wspolrzedna;
				y = SCREEN_H+SCREEN_H-64-y;//nowa wsp
				dy = -dy-ddy*(y-z)/dy;
				dy *= 0.9;
				dy -=ddy;
			}
			if(x > SCREEN_W-32)
			{
				z = x-dx;//stara wspolrzedna
				x = SCREEN_W+SCREEN_W-64-x;//nowa wsp
				dx = -dx-ddx*(x-z)/dx;
				dx *= 0.9;
				dx -= ddx;
			}
			if(y < 0)
			{
				z = y-dy;//stara wspolrzedna
				y = -y;//nowa wsp
				dy = -dy-ddy*(y-z)/dy;
				dy *= 0.9;
				dy -= ddy;
			}
			if(x < 0)
			{
				z = x-dx;//stara wspolrzedna
				x = -x;//nowa wsp
				dx = -dx-ddx*(x-z)/dx;
				dx *= 0.9;
				dx -= ddx;
			}
			
			dy += ddy;
			dx += ddx;
			
			dy = dy - opory*dy*abs(dy);
			dx = dx - oporx*dx*abs(dx);
			
			goniec++;
		}
		
		clear_bitmap(nieaktywny);
		
		textprintf_ex(nieaktywny, font, 10, 10, makecol(255, 255, 255), -1, "x:   % 8.2f", x);
		textprintf_ex(nieaktywny, font, 10, 20, makecol(255, 255, 255), -1, "y:   % 8.2f", y);
		
		textprintf_ex(nieaktywny, font, 10, 30, makecol(255, 255, 255), -1, "dx:  % 8.2f", dx);
		textprintf_ex(nieaktywny, font, 10, 40, makecol(255, 255, 255), -1, "dy:  % 8.2f", dy);
		
		if(li==0)
		{
			zl = starylicznik;
			starylicznik = licznik;
			zl = starylicznik - zl;
			if(zl)
				fps = double(50000)/zl;
			else
				fps = 0;
		}
		textprintf_ex(nieaktywny, font, 10, 50, makecol(255, 255, 255), -1, "fps: % 8.2f", fps);
		li = (li+1)%50;
		
		masked_blit(pilka, nieaktywny, 0, 0, x, y, 31, 31);
		show_video_bitmap(nieaktywny);
		if(nieaktywny == ekran1)
			nieaktywny = ekran2;
		else
			nieaktywny = ekran1;
	}
	
	destroy_bitmap(pilka);
	
	deinit();
	return 0;
}
END_OF_MAIN()

void init() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
    res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 640, 480 * 2);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
	install_mouse();
	/* add other initializations here */
	LOCK_VARIABLE(licznik);
	LOCK_FUNCTION(tik);
}

void deinit() {
	clear_keybuf();
	/* add other deinitializations here */
}
