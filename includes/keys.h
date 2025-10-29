#ifndef KEYS_H
# define KEYS_H

/*
** This header file defines cross-platform key codes for macOS and Linux (X11).
** The C preprocessor directives (__APPLE__, __linux__) detect the OS at
** compile time and define the appropriate key codes.
*/

# ifdef __APPLE__ // macOS (using AppKit)
#  define KEY_ESC 53
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_DOWN 125
#  define KEY_UP 126
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2

# elif __linux__ // Linux (using X11)
#  define KEY_ESC 65307
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_DOWN 65364
#  define KEY_UP 65362
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100

# endif

#endif
