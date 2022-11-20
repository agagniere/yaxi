#include "yaxi/yaxi.h"

#include <mlx.h>

#include <stdlib.h>

t_yaxi yaxi_init() { return mlx_init(); }

void yaxi_free(t_yaxi* yaxi)
{
	mlx_destroy_display(*yaxi);
	free(*yaxi);
}
