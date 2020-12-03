/*!
 * \file Platform.hpp
 * \brief Defines macros to determine the platform being used.
 *
**/
#ifndef INCG_PHI_CONFIG_PLATFORM_HPP
#define INCG_PHI_CONFIG_PLATFORM_HPP

#define PHI_PLATFORM_WINDOWS()       0
#define PHI_PLATFORM_APPLE()         0
#define PHI_PLATFORM_MACOS()         0
#define PHI_PLATFORM_LINUX()         0
#define PHI_PLATFORM_ANDROID()       0
#define PHI_PLATFORM_FREEBSD()       0
#define PHI_PLATFORM_SOLARIS()       0
#define PHI_PLATFORM_IOS()           0
#define PHI_PLATFORM_IOS_SIMULATOR() 0
#define PHI_PLATFORM_OPENBSD()       0
#define PHI_PLATFORM_BSD()           0
#define PHI_PLATFORM_UNIX()          0
#define PHI_PLATFORM_DOS()           0
#define PHI_PLATFORM_WEB()           0

#if defined(_WIN32)
#    undef PHI_PLATFORM_WINDOWS
#    define PHI_PLATFORM_WINDOWS() 1
#    define PHI_PLATFORM_NAME()    "Windows"
#elif defined(__APPLE__) && defined(__MACH__)
#    undef PHI_PLATFORM_APPLE
#    undef PHI_PLATFORM_UNIX
#    define PHI_PLATFORM_APPLE() 1
#    define PHI_PLATFORM_UNIX()  1

// Apple platform, see which one it is
#    include "TargetConditionals.h"
#    if TARGET_OS_IPHONE
#        undef PHI_PLATFORM_IOS
#        define PHI_PLATFORM_IOS()  1
#        define PHI_PLATFORM_NAME() "IPhone"
#    elif TARGET_IPHONE_SIMULATOR
#         #        undef PHI_PLATFORM_IOS
#        undef PHI_PLATFORM_IOS_SIMULATOR
#        define PHI_PLATFORM_IOS()           1
#        define PHI_PLATFORM_IOS_SUMULATOR() 1
#        define PHI_PLATFORM_NAME()          "IPhone Simulator"
#    elif TARGET_OS_MAC
#        undef PHI_PLATFORM_MACOS
#        define PHI_PLATFORM_MACOS() 1
#        define PHI_PLATFORM_NAME()  "MacOS"
#    else
#        warning "Unknown Apple based operating system"
#        define PHI_PLATFORM_NAME() "Unknown"
#    endif
#elif defined(__unix__) || defined(__unix) // Unix based OS
#    undef PHI_PLATFORM_UNIX
#    define PHI_PLATFORM_UNIX() 1

#    if defined(__ANDROID__)
#        undef PHI_PLATFORM_ANDROID
#        define PHI_PLATFORM_ANDOIRD() 1
#        define PHI_PLATFORM_NAME()    "Android"
#    elif defined(__linux__)
#        undef PHI_PLATFORM_LINUX
#        define PHI_PLATFORM_LINUX() 1
#        define PHI_PLATFORM_NAME()  "Linux"
#    elif defined(__FreeBSD__)
#        undef PHI_PLATFORM_BSD
#        undef PHI_PLATFORM_FREEBSD
#        define PHI_PLATFORM_BSD()     1
#        define PHI_PLATFORM_FREEBSD() 1
#        define PHI_PLATFORM_NAME()    "FreeBSD"
#    elif defined(__OpenBSD__)
#        undef PHI_PLATFORM_BSD
#        undef PHI_PLATFORM_OPENBSD
#        define PHI_PLATFORM_BSD()     1
#        define PHI_PLATFORM_OPENBSD() 1
#        define PHI_PLATFORM_NAME()    "OpenBSD"
#    else
#        define PHI_PLATFORM_NAME() "Unknown"
#        warning "Unknown Unix based operating system"
#    endif
#elif defined(__sun) && defined(__SVR4)
#    undef PHI_PLATFORM_UNIX
#    undef PHI_PLATFORM_SOLARIS
#    define PHI_PLATFORM_UNIX()    1
#    define PHI_PLATFORM_SOLARIS() 1
#    define PHI_PLATFORM_NAME()    "Solaris"
#elif defined(__EMSCRIPTEN__)
#    undef PHI_PLATFORM_WEB
#    define PHI_PLATFORM_WEB()  1
#    define PHI_PLATFORM_NAME() "Web"
#else
#    define PHI_PLATFORM_NAME() "Unknown"
#    warning "Platform could not be detected"
#endif

#define PHI_PLATFORM_IS(platform) (PHI_PLATFORM_##platform())

#define PHI_PLATFORM_IS_NOT(platform) (!(PHI_PLATFORM_IS(platform)))

#endif // INCG_CPPBASE_OS_HPP
