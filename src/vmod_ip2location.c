#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "vrt.h"
#include "cache/cache.h"
#include "vcc_if.h"
#include "config.h"

#include <IP2Location.h>
#include <string.h>

#define TZ                  1
#define COUNTRY             2
#define COUNTRY_LONG        3
#define REGION              4
#define CITY                5
#define ISP                 6
#define DOMAIN              7
#define ZIPCODE             8
#define NETSPEED            9
#define IDDCODE            10
#define AREACODE           11
#define WEATHERSTATIONCODE 12
#define WEATHERSTATIONNAME 13
#define MCC                14
#define MNC                15
#define MOBILEBRAND        16
#define USAGETYPE          17

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

void *
lookup_field(const struct vrt_ctx *ctx, struct vmod_priv *priv, const char *ip, int field)
{
	char *p = NULL;
	if (priv->priv != NULL) {
		IP2LocationRecord *record = IP2Location_get_all(priv->priv, ip);
		if (record != NULL) {
			switch( field ){
				case TZ:
						if (record->timezone != NULL)	p = WS_Copy(ctx->ws, record->timezone, -1);
					break;
				case COUNTRY:
						if (record->country_short != NULL)	p = WS_Copy(ctx->ws, record->country_short, -1);
					break;
				case COUNTRY_LONG:
						if (record->country_long != NULL)	p = WS_Copy(ctx->ws, record->country_long, -1);
					break;
				case REGION:
						if (record->region != NULL)	p = WS_Copy(ctx->ws, record->region, -1);
					break;
				case CITY:
						if (record->city != NULL)	p = WS_Copy(ctx->ws, record->city, -1);
					break;
				case ISP:
						if (record->isp != NULL)	p = WS_Copy(ctx->ws, record->isp, -1);
					break;
				case DOMAIN:
						if (record->domain != NULL)	p = WS_Copy(ctx->ws, record->domain, -1);
					break;
				case ZIPCODE:
						if (record->zipcode != NULL)	p = WS_Copy(ctx->ws, record->zipcode, -1);
					break;
				case NETSPEED:
						if (record->netspeed != NULL)	p = WS_Copy(ctx->ws, record->netspeed, -1);
					break;
				case IDDCODE:
						if (record->iddcode != NULL)	p = WS_Copy(ctx->ws, record->iddcode, -1);
					break;
				case AREACODE:
						if (record->areacode != NULL)	p = WS_Copy(ctx->ws, record->areacode, -1);
					break;
				case WEATHERSTATIONCODE:
						if (record->weatherstationcode != NULL)	p = WS_Copy(ctx->ws, record->weatherstationcode, -1);
					break;
				case WEATHERSTATIONNAME:
						if (record->weatherstationname != NULL)	p = WS_Copy(ctx->ws, record->weatherstationname, -1);
					break;
				case MCC:
						if (record->mcc != NULL)	p = WS_Copy(ctx->ws, record->mcc, -1);
					break;
				case MNC:
						if (record->mnc != NULL)	p = WS_Copy(ctx->ws, record->mnc, -1);
					break;
				case MOBILEBRAND:
						if (record->mobilebrand != NULL)	p = WS_Copy(ctx->ws, record->mobilebrand, -1);
					break;
				case USAGETYPE:
						if (record->usagetype != NULL)	p = WS_Copy(ctx->ws, record->usagetype, -1);
					break;
				default:
					p = NULL;
			}
			IP2Location_free_record(record);
		}
	}
	if (p == NULL)
		p = WS_Copy(ctx->ws, "-", -1);
	return (p);
}

VCL_STRING
vmod_lookup_tz(const struct vrt_ctx *ctx, struct vmod_priv *priv, const char *ip)
{
	char *p = NULL;
	p = lookup_field(ctx, priv, ip, TZ);
	return (p);
}

VCL_STRING
vmod_lookup_country(const struct vrt_ctx *ctx, struct vmod_priv *priv, const char *ip)
{
	char *p = NULL;
	p = lookup_field(ctx, priv, ip, COUNTRY);
	return (p);
}

VCL_STRING
vmod_lookup_country_long(const struct vrt_ctx *ctx, struct vmod_priv *priv, const char *ip)
{
	char *p = NULL;
	p = lookup_field(ctx, priv, ip, COUNTRY_LONG);
	return (p);
}

VCL_STRING
vmod_lookup_region(const struct vrt_ctx *ctx, struct vmod_priv *priv, const char *ip)
{
	char *p = NULL;
	p = lookup_field(ctx, priv, ip, REGION);
	return (p);
}

VCL_STRING
vmod_lookup_city(const struct vrt_ctx *ctx, struct vmod_priv *priv, const char *ip)
{
	char *p = NULL;
	p = lookup_field(ctx, priv, ip, CITY);
	return (p);
}

VCL_STRING
vmod_lookup_isp(const struct vrt_ctx *ctx, struct vmod_priv *priv, const char *ip)
{
	char *p = NULL;
	p = lookup_field(ctx, priv, ip, ISP);
	return (p);
}

VCL_STRING
vmod_lookup_domain(const struct vrt_ctx *ctx, struct vmod_priv *priv, const char *ip)
{
	char *p = NULL;
	p = lookup_field(ctx, priv, ip, DOMAIN);
	return (p);
}

VCL_STRING
vmod_lookup_zipcode(const struct vrt_ctx *ctx, struct vmod_priv *priv, const char *ip)
{
	char *p = NULL;
	p = lookup_field(ctx, priv, ip, ZIPCODE);
	return (p);
}

VCL_STRING
vmod_lookup_netspeed(const struct vrt_ctx *ctx, struct vmod_priv *priv, const char *ip)
{
	char *p = NULL;
	p = lookup_field(ctx, priv, ip, NETSPEED);
	return (p);
}

VCL_STRING
vmod_lookup_iddcode(const struct vrt_ctx *ctx, struct vmod_priv *priv, const char *ip)
{
	char *p = NULL;
	p = lookup_field(ctx, priv, ip, IDDCODE);
	return (p);
}

VCL_STRING
vmod_lookup_areacode(const struct vrt_ctx *ctx, struct vmod_priv *priv, const char *ip)
{
	char *p = NULL;
	p = lookup_field(ctx, priv, ip, AREACODE);
	return (p);
}

VCL_STRING
vmod_lookup_weatherstationcode(const struct vrt_ctx *ctx, struct vmod_priv *priv, const char *ip)
{
	char *p = NULL;
	p = lookup_field(ctx, priv, ip, WEATHERSTATIONCODE);
	return (p);
}

VCL_STRING
vmod_lookup_weatherstationname(const struct vrt_ctx *ctx, struct vmod_priv *priv, const char *ip)
{
	char *p = NULL;
	p = lookup_field(ctx, priv, ip, WEATHERSTATIONNAME);
	return (p);
}

VCL_STRING
vmod_lookup_mcc(const struct vrt_ctx *ctx, struct vmod_priv *priv, const char *ip)
{
	char *p = NULL;
	p = lookup_field(ctx, priv, ip, MCC);
	return (p);
}

VCL_STRING
vmod_lookup_mnc(const struct vrt_ctx *ctx, struct vmod_priv *priv, const char *ip)
{
	char *p = NULL;
	p = lookup_field(ctx, priv, ip, MNC);
	return (p);
}

VCL_STRING
vmod_lookup_mobilebrand(const struct vrt_ctx *ctx, struct vmod_priv *priv, const char *ip)
{
	char *p = NULL;
	p = lookup_field(ctx, priv, ip, MOBILEBRAND);
	return (p);
}

VCL_STRING
vmod_lookup_usagetype(const struct vrt_ctx *ctx, struct vmod_priv *priv, const char *ip)
{
	char *p = NULL;
	p = lookup_field(ctx, priv, ip, USAGETYPE);
	return (p);
}
