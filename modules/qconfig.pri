#configuration
CONFIG +=  shared qpa no_mocdepend release qt_framework
host_build {
    QT_ARCH = x86_64
    QT_TARGET_ARCH = x86_64
} else {
    QT_ARCH = x86_64
    QMAKE_DEFAULT_LIBDIRS  = 
    QMAKE_DEFAULT_INCDIRS  = 
}
QT_EDITION = OpenSource
QT_CONFIG +=  minimal-config small-config medium-config large-config full-config build_all debug_and_release no-pkg-config accessibility opengl shared qpa reduce_exports getaddrinfo ipv6ifname getifaddrs png freetype no-harfbuzz system-zlib nis cups iconv openssl rpath corewlan concurrent audio-backend debug release qt_framework

#versioning
QT_VERSION = 5.2.1
QT_MAJOR_VERSION = 5
QT_MINOR_VERSION = 2
QT_PATCH_VERSION = 1

#namespaces
QT_LIBINFIX = 
QT_NAMESPACE = 

QT_APPLE_CLANG_MAJOR_VERSION = 5
QT_APPLE_CLANG_MINOR_VERSION = 0
