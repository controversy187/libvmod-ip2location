#IP2Location Vmod
This vmod used the Hello World vmod (https://github.com/varnish/libvmod-example/tree/master) as a base for a vmod.
You will need to purchase the IP2Location database and install the C class from their developer library to your sever.

##Prereqs
============
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
3. IP2Location database needs to exist somewhere on the system. You will be able to specify the location in your VCL.

##Installation
============
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
* make check - runs the unit tests in ``src/tests/*.vtc``
