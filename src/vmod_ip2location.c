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
		return;
	}

	//Attach to the shared memory
	IP2Location_open_mem(IP2LocationObj, IP2LOCATION_SHARED_MEMORY);

	priv->priv = IP2LocationObj;

	if (priv->priv == NULL)
		return;

	priv->free = freeit;
}

VCL_STRING
vmod_lookup_tz(const struct vrt_ctx *ctx, struct vmod_priv *priv, const char *ip)
{
	if( priv->priv != NULL ){
		//Lookup Record
		IP2LocationRecord *record = IP2Location_get_all(priv->priv, ip);

		char* timezone;

		if ( record != NULL ){
			int tz_len = strlen(record->timezone);
			char temp_timezone[tz_len+1];
			strcpy(temp_timezone, record->timezone);

			temp_timezone[tz_len] = '\0';
			timezone = temp_timezone;

			IP2Location_free_record(record);
		} else {
			timezone = "--";
		}

		return timezone;
	} else {
		return "-";
	}
}

VCL_STRING
vmod_lookup_country(const struct vrt_ctx *ctx, struct vmod_priv *priv, const char *ip)
{
	if( priv->priv != NULL ){
		//Lookup Record
		IP2LocationRecord *record = IP2Location_get_all(priv->priv, ip);

		char* country;

		if ( record != NULL ){
			int country_len = strlen(record->country_short);
			char temp_country[country_len+1];
			strcpy(temp_country, record->country_short);

			temp_country[country_len] = '\0';
			country = temp_country;

			IP2Location_free_record(record);
		} else {
			country = "--";
		}

		return country;
	} else {
		return "-";
	}
}