// Dominik Wójt
#include <allegro.h>
#include <cmath>
#include <cstdio>

const double pi = std::acos(-1.0);
const double dt = 0.001;
const double scale = 100;

volatile unsigned long int counter = 0;

void init();
void deinit();
void tik() // every dt
{
    counter++;
}

int main()
{
    double alpha = -pi / 10, d_alpha = 0, dd_alpha = 0;
    double m = 10, g = 9.81, l = 2;
    double s_x = 320, s_y = 50;
    double x = 0, y = 0;

    double fps = 0;
    unsigned long int hopper = 0, old_counter = 0, li = 0;

    FILE* file = nullptr;
    file = fopen("data.txt", "rt");
    if (file)
    {
        fscanf(file, "%lf%lf%lf%lf%lf", &g, &m, &alpha, &dd_alpha, &l);
        fclose(file);
    }

    init();

    BITMAP *sphere = nullptr, *hook = nullptr;
    BITMAP *screen_1 = nullptr, *screen_2 = nullptr;
    BITMAP* inactive = nullptr;

    sphere = create_bitmap(31, 31);
    clear(sphere);
    circlefill(sphere, 15, 15, 15, makecol(120, 120, 200));

    hook = create_bitmap(5, 5);
    clear_bitmap(hook);
    circlefill(hook, 2, 2, 2, makecol(120, 120, 200));

    screen_1 = create_video_bitmap(SCREEN_W, SCREEN_H);
    screen_2 = create_video_bitmap(SCREEN_W, SCREEN_H);
    inactive = screen_1;

    install_int(&tik, 1000 * dt);
    hopper = counter;

    old_counter = 0;
    li = 0;

    while (!key[KEY_ESC])
    {
        while (hopper != counter) // dogonic licznik
        {
            dd_alpha = -g * std::sin(alpha) / l;
            d_alpha += dd_alpha * dt;
            alpha += d_alpha * dt;

            hopper++;
        }

        x = s_x - std::sin(alpha) * l * scale;
        y = s_y + std::cos(alpha) * l * scale;

        if (li == 0) // every 50 frames
        {
            int zc = old_counter;
            old_counter = counter;
            zc = old_counter - zc;
            if (zc)
                fps = 50.0 / (zc * dt);
            else
                fps = 0;
        }
        li = (li + 1) % 50;

        clear_bitmap(inactive);

        textprintf_ex(
            inactive,
            font,
            10,
            10,
            makecol(255, 255, 255),
            -1,
            "x:       %8.2f",
            x);
        textprintf_ex(
            inactive,
            font,
            10,
            20,
            makecol(255, 255, 255),
            -1,
            "y:       %8.2f",
            y);

        textprintf_ex(
            inactive,
            font,
            10,
            30,
            makecol(255, 255, 255),
            -1,
            "alpha:   %8.2f",
            alpha);
        textprintf_ex(
            inactive,
            font,
            10,
            40,
            makecol(255, 255, 255),
            -1,
            "d_alpha: %8.2f",
            d_alpha);
        textprintf_ex(
            inactive,
            font,
            10,
            50,
            makecol(255, 255, 255),
            -1,
            "dd_alpha:%8.2f",
            dd_alpha);

        textprintf_ex(
            inactive,
            font,
            10,
            60,
            makecol(255, 255, 255),
            -1,
            "fps:     %8.2f",
            fps);

        masked_blit(hook, inactive, 0, 0, s_x, s_y, 5, 5);
        masked_blit(sphere, inactive, 0, 0, x - 15, y - 15, 31, 31);
        show_video_bitmap(inactive);
        if (inactive == screen_1)
            inactive = screen_2;
        else
            inactive = screen_1;
    }

    destroy_bitmap(hook);
    destroy_bitmap(sphere);

    deinit();
    return 0;
}
END_OF_MAIN()

void init()
{
    allegro_init();
    int depth = desktop_color_depth();
    if (depth == 0)
        depth = 32;
    set_color_depth(depth);
    int res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 640, 2 * 480);
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
