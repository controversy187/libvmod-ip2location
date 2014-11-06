#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "vrt.h"
#include "cache/cache.h"
#include "vcc_if.h"
#include "config.h"

#include <IP2Location.h>
#include <string.h>

void
freeit(struct vmod_priv *priv)
{
	IP2Location_close(priv->priv);
	IP2Location_delete_shm(priv->priv);
}

VCL_VOID
vmod_init_db(const struct vrt_ctx *ctx, struct vmod_priv *priv, const char *filename)
{
	IP2Location *IP2LocationObj = IP2Location_open(filename);
	IP2Location_open_mem(priv->priv, IP2LOCATION_SHARED_MEMORY);
	priv->priv = IP2LocationObj;
	AN(priv->priv);
	priv->free = freeit;
}

VCL_STRING
vmod_lookup_tz(const struct vrt_ctx *ctx, struct vmod_priv *priv, const char *ip)
{
	char *p = NULL;
	if (priv->priv != NULL) {
		IP2LocationRecord *record = IP2Location_get_all(priv->priv, ip);
		if (record != NULL) {
			if (record->timezone != NULL)
				p = WS_Copy(ctx->ws, record->timezone, -1);
			IP2Location_free_record(record);
		}
		//IP2Location_close(priv->priv);
	}
	if (p == NULL)
		p = WS_Copy(ctx->ws, "-", -1);
	return (p);
}

VCL_STRING
vmod_lookup_country(const struct vrt_ctx *ctx, struct vmod_priv *priv, const char *ip)
{
	char *p = NULL;
	if (priv->priv != NULL) {
		IP2LocationRecord *record = IP2Location_get_all(priv->priv, ip);
		if (record != NULL) {
			if (record->country_short != NULL)
				p = WS_Copy(ctx->ws, record->country_short, -1);
			IP2Location_free_record(record);
		}
		//IP2Location_close(priv->priv);
	}
	if (p == NULL)
		p = WS_Copy(ctx->ws, "-", -1);
	return (p);
}

VCL_STRING
vmod_lookup_country_long(const struct vrt_ctx *ctx, struct vmod_priv *priv, const char *ip)
{
	char *p = NULL;
	if (priv->priv != NULL) {
		IP2LocationRecord *record = IP2Location_get_all(priv->priv, ip);
		if (record != NULL) {
			if (record->country_short != NULL)
				p = WS_Copy(ctx->ws, record->country_long, -1);
			IP2Location_free_record(record);
		}
		//IP2Location_close(priv->priv);
	}
	if (p == NULL)
		p = WS_Copy(ctx->ws, "-", -1);
	return (p);
}