#include <stdio.h>
#include <stdlib.h>

#include "vrt.h"
#include "cache/cache.h"
#include <IP2Location.h>

#include "vcc_if.h"

int
init_function(struct vmod_priv *priv, const struct VCL_conf *conf)
{
	return (0);
}

void
freeit(void *data)
{
	free(data);
}

VCL_VOID
vmod_init_db(const struct vrt_ctx *ctx, struct vmod_priv *priv, const char *filename)
{
	IP2Location *IP2LocationObj = IP2Location_open(filename);


	if (priv->priv == NULL)
		return;

	priv->free = freeit;
}

