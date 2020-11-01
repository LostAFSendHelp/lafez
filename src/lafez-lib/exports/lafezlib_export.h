
#ifndef LAFEZLIB_H
#define LAFEZLIB_H

#ifdef LAFEZLIB_STATIC_DEFINE
#  define LAFEZLIB
#  define LAFEZLIB_NO_EXPORT
#else
#  ifndef LAFEZLIB
#    ifdef lafez_lib_EXPORTS
        /* We are building this library */
#      define LAFEZLIB __declspec(dllexport)
#    else
        /* We are using this library */
#      define LAFEZLIB __declspec(dllimport)
#    endif
#  endif

#  ifndef LAFEZLIB_NO_EXPORT
#    define LAFEZLIB_NO_EXPORT 
#  endif
#endif

#ifndef LAFEZLIB_DEPRECATED
#  define LAFEZLIB_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef LAFEZLIB_DEPRECATED_EXPORT
#  define LAFEZLIB_DEPRECATED_EXPORT LAFEZLIB LAFEZLIB_DEPRECATED
#endif

#ifndef LAFEZLIB_DEPRECATED_NO_EXPORT
#  define LAFEZLIB_DEPRECATED_NO_EXPORT LAFEZLIB_NO_EXPORT LAFEZLIB_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef LAFEZLIB_NO_DEPRECATED
#    define LAFEZLIB_NO_DEPRECATED
#  endif
#endif

#endif /* LAFEZLIB_H */
