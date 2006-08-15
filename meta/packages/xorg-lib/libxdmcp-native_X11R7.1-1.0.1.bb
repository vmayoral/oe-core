SECTION = "x11/libs"
PRIORITY = "optional"
#MAINTAINER = ""
LICENSE = "BSD-X"

DEPENDS = "xproto-native util-macros-native"

SRC_URI = "${XORG_MIRROR}/X11R7.1/src/lib/libXdmcp-${PV}.tar.bz2"
S = "${WORKDIR}/libXdmcp-${PV}"

inherit native autotools pkgconfig
