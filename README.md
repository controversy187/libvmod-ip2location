#IP2Location Vmod
This vmod used the Hello World vmod (https://github.com/varnish/libvmod-example/tree/master) as a base for a vmod, and draws heavily on simonvik's MaxMind DB VMOD (https://github.com/simonvik/libvmod_maxminddb).
You will need to purchase the IP2Location database and install the C class from their developer library to your sever.

##Prereqs
==============
###Packages:
1. pkg-config
2. build-essential
3. autoconf
4. libtool
6. python-docutils
7. varnish
8. libvarnishapi-dev

###Other software
1. Varnish needs to be installed, and the Varnish source available. (eg, if installed from the Debian repo, after following the installation instructions on http://varnish-cache.org, Make sure there is a deb-rc line similar to: "deb-src https://repo.varnish-cache.org/debian/ wheezy varnish-4.0" in your /etc/apt/sources.list.d/varnish-cache.list. This allows you to get the source for your installed package using sudo apt-get source varnish)
2. IP2Location needs to be built and installed on the system. The source can be gotten from http://ip2location.com/developers
3. IP2Location database needs to be placed in the VMOD directory. You will be able to specify the exact location and binfile in your VCL.

##Installation
==============
    ./autogen.sh
    ./configure VARNISHSRC=DIR [VMODDIR=DIR]

`VARNISHSRC` is the directory of the Varnish source tree for which to
compile your vmod. Both the `VARNISHSRC` and `VARNISHSRC/include`
will be added to the include search paths for your module.

Optionally you can also set the vmod install directory by adding
`VMODDIR=DIR` (defaults to the pkg-config discovered directory from your
Varnish installation).

Make targets:

* make - builds the vmod
* make install - installs your vmod in `VMODDIR`

##Usage
==============
```
import ip2location;

sub vcl_init{
  ip2location.init_db("/path/to/ip2location_db.bin");
}

sub vcl_recv {
  set req.http.X-Time-Zone = ip2location.lookup_tz(client.ip);
  set req.http.X-Country = ip2location.lookup_country(client.ip);
  set req.http.X-Country-Long = ip2location.lookup_country_long(client.ip);
  set req.http.X-Region = ip2location.lookup_region(client.ip);
  set req.http.X-City = ip2location.lookup_city(client.ip);
  set req.http.X-ISP = ip2location.lookup_isp(client.ip);
  set req.http.X-Domain = ip2location.lookup_domain(client.ip);
  set req.http.X-Zipcode = ip2location.lookup_zipcode(client.ip);
  set req.http.X-Netspeed = ip2location.lookup_netspeed(client.ip);
  set req.http.X-IDDCode = ip2location.lookup_iddcode(client.ip);
  set req.http.X-Area-Code = ip2location.lookup_areacode(client.ip);
  set req.http.X-Weatherstation-Code = ip2location.lookup_weatherstationcode(client.ip);
  set req.http.X-Weatherstation-Name = ip2location.lookup_weatherstationname(client.ip);
  set req.http.X-MCC = ip2location.lookup_mcc(client.ip);
  set req.http.X-MNC = ip2location.lookup_mnc(client.ip);
  set req.http.X-Mobile-Brand = ip2location.lookup_mobilebrand(client.ip);
  set req.http.X-Usage-Type = ip2location.lookup_usagetype(client.ip);
}
```