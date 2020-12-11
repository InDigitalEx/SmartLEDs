#ifndef DEFINES_H
#define DEFINES_H


#ifdef ALWAYS_INLINE
#undef ALWAYS_INLINE
#endif
#define ALWAYS_INLINE __attribute__((__always_inline__)) inline


#endif // DEFINES_H