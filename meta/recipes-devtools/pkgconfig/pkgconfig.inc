SUMMARY = "Helper tool used when compiling"
DESCRIPTION = "pkg-config is a helper tool used when compiling applications and libraries. It helps determined \
the correct compiler/link options.  It is also language-agnostic."
HOMEPAGE = "http://pkg-config.freedesktop.org/wiki/"
BUGTRACKER = "http://bugs.freedesktop.org/buglist.cgi?product=pkg-config"
SECTION = "console/utils"

LICENSE = "GPLv2+"
LIC_FILES_CHKSUM = "file://COPYING;md5=b234ee4d69f5fce4486a80fdaf4a4263"

DEPENDS = "glib-2.0 popt"
DEPENDS_class-native = ""
DEPENDS_class-nativesdk = ""

SRC_URI = "http://pkgconfig.freedesktop.org/releases/pkg-config-${PV}.tar.gz"

S = "${WORKDIR}/pkg-config-${PV}/"

inherit autotools

EXTRA_OECONF = "--with-installed-glib --with-installed-popt --disable-legacy-scripts"
EXTRA_OECONF_class-native = "--disable-legacy-scripts"
EXTRA_OECONF_class-nativesdk = "--disable-legacy-scripts"

acpaths = "-I ."
do_configure_prepend () {
	mkdir --parents ${B}/glib-1.2.10
	install -m 0644 ${WORKDIR}/glibconfig-sysdefs.h ${B}/glib-1.2.10/
}

BBCLASSEXTEND = "native nativesdk"

# Set an empty dev package to ensure the base PN package gets
# the pkg.m4 macros, pkgconfig does not deliver any other -dev
# files.
FILES_${PN}-dev = ""
FILES_${PN} += "${datadir}/aclocal/pkg.m4"

# When using the RPM generated automatic package dependencies, some packages
# will end up requiring 'pkgconfig(pkg-config)'.  Allow this behavior by
# specifying an appropriate provide.
RPROVIDES_${PN} += "pkgconfig(pkg-config) (= ${PV})"

# Install a pkg-config-native wrapper that will use the native sysroot instead
# of the MACHINE sysroot, for using pkg-config when building native tools.
do_install_append_class-native () {
    sed -e "s|@PATH_NATIVE@|${PKG_CONFIG_PATH}|" \
        -e "s|@LIBDIR_NATIVE@|${PKG_CONFIG_LIBDIR}|" \
        < ${WORKDIR}/pkg-config-native.in > ${B}/pkg-config-native
    install -m755 ${B}/pkg-config-native ${D}${bindir}/pkg-config-native
}
