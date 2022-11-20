#include "yaxi/yaxi.h"

#include <mlx.h>
#include <stdlib.h>

int default_expose(t_window* win)
{
	mlx_put_image_to_window(win->mlx_ptr, win->mlx_win, win->mlx_img, 0, 0);
	return 0;
}

bool window_init(t_window* out, t_yaxi yaxi, t_dimension dim, const char* name, t_hooks hooks)
{
	out->dim     = dim;
	out->hooks   = hooks;
	out->mlx_ptr = yaxi;
	out->mlx_img = mlx_new_image(yaxi, dim.x, dim.y);
	out->mlx_win = mlx_new_window(yaxi, dim.x, dim.y, (char*)name);
	if (out->mlx_win == NULL || out->mlx_img == NULL)
		return false;
	out->pixels = (uint8_t*)mlx_get_data_addr(out->mlx_img, &(out->bit_per_pixel),
	                                          &(out->line_size), &(out->endian));
	if (hooks.expose)
		mlx_expose_hook(out->mlx_win, hooks.expose, out);
	if (hooks.key_press)
		mlx_key_hook(out->mlx_win, hooks.key_press, out);
	return true;
}

t_window* window_new(t_yaxi yaxi, t_dimension dim, const char* name, t_hooks hooks)
{
	t_window* result = malloc(sizeof(t_window));

	if (result)
		window_init(result, yaxi, dim, name, hooks);
	return result;
}

bool window_clear(t_window* win)
{
	if (win->mlx_img)
		mlx_destroy_image(win->mlx_ptr, win->mlx_img);
	if (win->mlx_win)
		mlx_destroy_window(win->mlx_ptr, win->mlx_win);
	ft_bzero(win, sizeof(win));
	return true;
}

void window_free(t_window** win)
{
	window_clear(*win);
	free(*win);
	*win = NULL;
}
