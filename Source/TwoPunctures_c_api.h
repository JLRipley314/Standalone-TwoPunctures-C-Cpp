/*
 * C api for the standalone TwoPunctures code
 */
#ifndef _TWOPUNCTURES_C_API_H_
#define _TWOPUNCTURES_C_API_H_

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

/* An opaque type for the TwoPunctures class */
typedef void* TP_t;

EXTERNC TP_t twopunctures_init();
EXTERNC void twopunctures_destroy(TP_t self);
EXTERNC void twopunctures_run(TP_t self);
EXTERNC void twopunctures_interpolate(TP_t self, const double *pos, double *Q);

#endif /* _TWOPUNCTURES_C_API_H_ */
