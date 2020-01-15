#include <allegro.h>
#include <thread>

void init();
void deinit();

double sqrt(double x, double a = 1414, unsigned int i = 15)
{
    while (i--)
        a = 0.5 * (a + x / a);
    return a;
}

void draw_koch(double ax, double ay, double bx, double by, int level)
{
    if (level > 0)
    {
        const double cx = (ax + bx) / 2 + sqrt(3) * (by - ay) / 6;
        const double cy = (ay + by) / 2 - sqrt(3) * (bx - ax) / 6;
        draw_koch(ax, ay, (2 * ax + bx) / 3, (2 * ay + by) / 3, level - 1);
        draw_koch((2 * ax + bx) / 3, (2 * ay + by) / 3, cx, cy, level - 1);
        draw_koch(cx, cy, (ax + 2 * bx) / 3, (ay + 2 * by) / 3, level - 1);
        draw_koch((ax + 2 * bx) / 3, (ay + 2 * by) / 3, bx, by, level - 1);
        ;
    }
    else
    {
        line(screen, ax, ay, bx, by, makecol(0xff, 0xff, 0xff));
    }
}

int main()
{
    init();

    draw_koch(210, 10, 410, 356, 8);
    draw_koch(410, 356, 10, 356, 8);
    draw_koch(10, 356, 210, 10, 8);

    while (!key[KEY_ESC])
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        /* put your code here */
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
    res = set_gfx_mode(GFX_AUTODETECT, 640, 480, 0, 0);
    if (res != 0)
    {
        allegro_message(allegro_error);
        exit(-1);
    }

    install_timer();
    install_keyboard();
    install_mouse();
    /* add other initializations here */
}

void deinit()
{
    clear_keybuf();
    /* add other deinitializations here */
}
