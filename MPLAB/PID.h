#define PI FALSE
#define PD TRUE

BOOLEAN selected;  //true PD, false PI

#ifndef XFUZZY
#define XFUZZY
/*------------------------------------------------------*/
/* Fuzzy Number                                         */
/*------------------------------------------------------*/

 typedef struct {
   double min;
   double max;
   double step;
   double imp;
   double also;
   int length;
   double* degree;
   int inputlength;
   double* input;
 } FuzzyNumber;

#endif /* XFUZZY */