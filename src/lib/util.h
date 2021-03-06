/*
 * This file is part of brisk-menu.
 *
 * Copyright © 2016-2017 Brisk Menu Developers
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#pragma once

#define _STRINGIFY(x) #x

#if defined(__GNUC__)

/**
 * With newer GCC versions, we see compiler warnings simply from including any glib/gtk header.
 * Many of these make it very hard to debug genuine compiler warnings for the project itself, which
 * ideally should be completely clear.
 *
 * This provides a quick useful macro to wrap around the inclusion of GTK/GLib header files
 */
#define _BRISK_BEGIN_PEDANTIC(COMP)                                                                \
        _Pragma(_STRINGIFY(COMP diagnostic push))                                                  \
            _Pragma(_STRINGIFY(COMP diagnostic ignored "-Wpedantic"))

/**
 * End the includes block, i.e. by popping the diagnostic once more
 */
#define _BRISK_END_PEDANTIC(COMP) _Pragma(_STRINGIFY(COMP diagnostic pop))

/**
 * Clang unfortunately also defines __GNUC__ meaning a second level of tests
 */
#if defined(__clang__)

/**
 * Specifically use clang in pragma for older versions of Clang that don't understand
 * pragma GCC
 */
#define BRISK_BEGIN_PEDANTIC _BRISK_BEGIN_PEDANTIC(clang)
#define BRISK_END_PEDANTIC _BRISK_END_PEDANTIC(clang)
#else /* __clang__ */

/**
 * Specifically use GCC pragma for GCC
 */
#define BRISK_BEGIN_PEDANTIC _BRISK_BEGIN_PEDANTIC(GCC)
#define BRISK_END_PEDANTIC _BRISK_END_PEDANTIC(GCC)
#endif

#else /* __GNUC__ */
/**
 * Unknown compiler, don't expose the functionality
 */
#define BRISK_BEGIN_PEDANTIC
#define BRISK_END_PEDANTIC
#endif

/* Useful macros */

/**
 * Useful during development to silence compiler warnings
 */
#define __brisk_unused__ __attribute__((unused))

/**
 * All symbols are hidden by default so must be explicitly be made public
 * to define the ABI
 */
#define __brisk_public__ __attribute__((visibility("default")))

/**
 * Mark the function as a pure function to the compiler
 */
#define __brisk_pure__ __attribute__((pure))

/**
 * Taken out of libnica
 */
#define DEF_AUTOFREE(N, C)                                                                         \
        static inline void _autofree_func_##N(void *p)                                             \
        {                                                                                          \
                if (p && *(N **)p) {                                                               \
                        C(*(N **)p);                                                               \
                        (*(void **)p) = NULL;                                                      \
                }                                                                                  \
        }

#define autofree(N) __attribute__((cleanup(_autofree_func_##N))) N

/*
 * Editor modelines  -  https://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 8
 * tab-width: 8
 * indent-tabs-mode: nil
 * End:
 *
 * vi: set shiftwidth=8 tabstop=8 expandtab:
 * :indentSize=8:tabSize=8:noTabs=true:
 */
