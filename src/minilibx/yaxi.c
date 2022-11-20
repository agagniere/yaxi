#include "yaxi/yaxi.h"

#include <mlx.h>

void* init_yaxi()
{
	return mlx_init();
}

void cleanup_yaxi(void** yaxi)
{
	mlx_destroy_display(*yaxi);
}
