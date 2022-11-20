#include "yaxi/yaxi.h"

#include <mlx.h>

#include <stdlib.h>

t_yaxi yaxi_new() { return mlx_init(); }

void yaxi_free(t_yaxi* yaxi)
{
	mlx_destroy_display(*yaxi);
	free(*yaxi);
}

bool yaxi_loop(t_yaxi yaxi)
{
	mlx_loop(yaxi);
	return true;
}
