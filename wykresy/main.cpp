#include <allegro.h>
#include <math.h>

using namespace std;

void init();
void deinit();
double f1(double x);
double f2(double x);

int main()
{
    init();

    double (*f)(double x);
    int i, biel, poprzedni, aktualny;

    f = &f1;
    biel = makecol(255, 255, 255);

    acquire_screen();
    fastline(screen, SCREEN_W / 2, 0, SCREEN_W / 2, SCREEN_H, biel);
    fastline(
        screen,
        SCREEN_W / 2 - 5,
        SCREEN_H / 2 - 20,
        SCREEN_W / 2 + 5,
        SCREEN_H / 2 - 20,
        biel);
    fastline(screen, 0, SCREEN_H / 2, SCREEN_W, SCREEN_H / 2, biel);
    fastline(
        screen,
        SCREEN_W / 2 + 20,
        SCREEN_H / 2 - 5,
        SCREEN_W / 2 + 20,
        SCREEN_H / 2 + 5,
        biel);

    poprzedni = int((*f)(double(-SCREEN_W / 2) / 20) * (-20)) + SCREEN_H / 2;
    for (i = 1; i < SCREEN_W; i++)
    {
        aktualny =
            int((*f)(double(i - SCREEN_W / 2) / 20) * (-20)) + SCREEN_H / 2;
        // line(screen, i-1, poprzedni, i, aktualny, biel);
        putpixel(screen, i, aktualny, biel);
        poprzedni = aktualny;
    }
    release_screen();

    readkey();

    /*	while (!key[KEY_ESC]) {
                    ;
            }
    */

    deinit();
    return 0;
}
END_OF_MAIN()

double f1(double x) { return 5 * x * x + 18 * x + 9; }

double f2(double x) { return (4 - sin(x)) / cos(x); }

void init()
{
    int depth, res;
    allegro_init();
    depth = desktop_color_depth();
    if (depth == 0)
        depth = 32;
    set_color_depth(depth);
    res = set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 640, 480, 0, 0);
    if (res != 0)
    {
        allegro_message(allegro_error);
        exit(-1);
    }

    //	install_timer();
    install_keyboard();
    //	install_mouse();
    /* add other initializations here */
}

void deinit()
{
    clear_keybuf();
    /* add other deinitializations here */
}
