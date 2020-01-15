#include <allegro.h>
using namespace std;

const double dt = 0.01;

double fps;
volatile unsigned long int licznik;
unsigned long int goniec, starylicznik, li, zl;

void init();
void deinit();
void tik() // co dt
{
    licznik++;
}
END_OF_FUNCTION(tik)

int main(int argc, char* argv[])
{
    init();

    BITMAP *ekran1, *ekran2;
    BITMAP* nieaktywny;

    int h = 100;
    bool ot = false;

    ekran1 = create_video_bitmap(SCREEN_W, SCREEN_H);
    ekran2 = create_video_bitmap(SCREEN_W, SCREEN_H);
    nieaktywny = ekran1;

    install_int(&tik, 1000 * dt);
    goniec = licznik;

    starylicznik = 0;
    li = 0;

    while (!key[KEY_ESC])
    {
        while (goniec != licznik) // dogonic licznik
        {
            if (h == 100)
                ot = false;
            if (h == 0)
                ot = true;

            if (ot)
                h += 5;
            else
                h -= 5;
            goniec++;
        }

        if (li == 0) // co 50 klatek
        {
            zl = starylicznik;
            starylicznik = licznik;
            zl = starylicznik - zl;
            if (zl)
                fps = double(50) / (zl * dt);
            else
                fps = 0;
        }
        li = (li + 1) % 50;

        clear_bitmap(nieaktywny);

        textprintf_ex(
            nieaktywny,
            font,
            10,
            10,
            makecol(255, 255, 255),
            -1,
            "fps:   %8.2f",
            fps);

        circlefill(nieaktywny, 100, 100, 100, 0x99ffee44);

        arc(nieaktywny, 100, 100, itofix(32), itofix(223), 100, 0xffffffff);

        triangle(nieaktywny, 100, 100, 200, 100 - h, 200, 100 + h, 0x00000000);

        circlefill(nieaktywny, 100, 50, 10, 0xaaaaaaaa);

        show_video_bitmap(nieaktywny);
        if (nieaktywny == ekran1)
            nieaktywny = ekran2;
        else
            nieaktywny = ekran1;
    }

    deinit();

    return 0;
}
END_OF_MAIN()

void init()
{
    int depth, res;
    allegro_init();
    depth = desktop_color_depth();
    if (depth == 0)
        depth = 32;
    set_color_depth(depth);
    res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 640, 2 * 480);
    if (res != 0)
    {
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

void deinit()
{
    clear_keybuf();
    /* add other deinitializations here */
}
