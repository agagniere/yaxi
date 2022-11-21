#include "yaxi/yaxi.h"

#include <mlx.h>

#include <stdlib.h>

t_yaxi yaxi_new()
{
	t_yaxi ans = mlx_init();
	mlx_do_key_autorepeaton(ans);
	return ans;
}

void yaxi_free(t_yaxi* yaxi)
{
	mlx_destroy_display(*yaxi);
	free(*yaxi);
}
