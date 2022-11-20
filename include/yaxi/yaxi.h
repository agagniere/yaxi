#pragma once

#include "yaxi/point.h"

#include <ft_array.h>
#include <ft_prepro/raii.h>
#include <libft.h>

#include <stdbool.h>
#include <stdint.h>

typedef struct window t_window;
typedef struct hooks  t_hooks;
typedef void*         t_yaxi;
typedef int         (*t_fnct)();

RAII_DECLARE_TYPE(t_yaxi);
RAII_DECLARE_TYPE(t_window);

#define Yaxi   RAII(t_yaxi)
#define Window RAII(t_window)*

struct hooks
{
	t_fnct loop;
	t_fnct expose;
	t_fnct repaint;
	t_fnct key_press;
	t_fnct key_release;
	t_fnct mouse_click;
	t_fnct mouse_move;
	t_fnct mouse_drag;
	t_fnct destroy;
};

struct window
{
	t_hooks     hooks;
	void*       mlx_ptr;
	void*       mlx_win;
	void*       mlx_img;
	uint8_t*    pixels;
	t_dimension dim;
	int         bit_per_pixel;
	int         line_size;
	int         endian;
};

#define DEFAULT_HOOKS \
	(struct hooks) { .expose = default_expose, .destroy = window_clear }

#define NEW_WINDOW \
	(struct window) { .hooks = DEFAULT_HOOKS }

t_yaxi yaxi_new();
void   yaxi_free(t_yaxi*);
bool   yaxi_loop(t_yaxi);

t_window* window_new(void* yaxi, t_dimension dim, const char* name, t_hooks hooks);
void      window_free(t_window**);
bool      window_init(t_window* out_win, void* yaxi, t_dimension dim, const char* name, t_hooks hooks);
bool      window_clear(t_window*);

bool draw_line(t_window* win, t_point2_int from, t_point2_int to, int color);
bool set_pixel(t_window* win, unsigned x, unsigned y, int color);
bool is_in_frame(t_window* win, unsigned x, unsigned y);

int default_expose(t_window*);

#define cleanup_t_yaxi   yaxi_free
#define cleanup_t_window window_free
