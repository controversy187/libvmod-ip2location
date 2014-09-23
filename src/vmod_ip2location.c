#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "vrt.h"
#include "cache/cache.h"
#include "vcc_if.h"
#include "config.h"

#include <IP2Location.h>
#include <string.h>

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
	if (IP2LocationObj == NULL)
	{
		printf("Please install the database in correct path.\n");
		return -1;
	}

	priv->priv = IP2LocationObj;

	if (priv->priv == NULL)
		return;

	priv->free = freeit;
}

VCL_STRING
vmod_lookup_tz(const struct vrt_ctx *ctx, struct vmod_priv *priv, const char *ip)
{
	IP2Location_open_mem(priv->priv, IP2LOCATION_SHARED_MEMORY);
	IP2LocationRecord *record = IP2Location_get_all(priv->priv, ip);

	if ( record != NULL ){
		return record->timezone;
	}

	//Make sure to detatch from the shared memory!
	IP2Location_close(priv->priv);

	return "test";
}
