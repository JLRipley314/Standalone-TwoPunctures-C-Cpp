#include "TwoPunctures.h"
#include "TwoPunctures_c_api.h"

using namespace TP;

TP_t twopunctures_init()
{
   return new TwoPunctures;   
}
void twopunctures_destroy(TP_t self)
{
   TwoPunctures *typed_self = static_cast<TwoPunctures*>(self);
   delete typed_self;
}
void twopunctures_run(TP_t self)
{
   TwoPunctures *typed_self = static_cast<TwoPunctures*>(self);
   typed_self->Run();
}
void twopunctures_interpolate(TP_t self, const double *pos, double *Q)
{
   TwoPunctures *typed_self = static_cast<TwoPunctures*>(self);
   typed_self->Interpolate(pos, Q);
}
