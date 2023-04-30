#include <stdio.h>
#include <math.h>
#include "PID.h"
#include "MFU.c"

void PDInferenceEngine(double eP, double deD, double* uPD);
void PIInferenceEngine(double eI, double deP, double* duPI);
double consequent_equal(int conjunto, double x);
double OP_myOperations_Imp(double a, double b);
double OP_myOperations_Also(double a, double b);

void initialize_PI_Fuzzy(signed int16 _min,int16 _max,int16 _step)
{
	definir_universo_salida(_min,_max,_step,PI);
	definir_rango_salida_NBu_NBdu(0,0,0,PI_salida,PI);
	definir_rango_salida_NSu_NSdu(0,0,0,PI_salida,PI);
	definir_rango_salida_Zu_Zdu(0,0,0,PI_salida,PI);
	definir_rango_salida_PSu_PSdu(0,0,0,PI_salida,PI);
	definir_rango_salida_PBu_PBdu(0,0,0,PI_salida,PI);
}

void initialize_PD_Fuzzy(signed int16 _min,int16 _max,int16 _step)
{
	definir_universo_salida(_min,_max,_step,PD);
	definir_rango_salida_NBu_NBdu(0,0,0,PD_salida,PD);
	definir_rango_salida_NSu_NSdu(0,0,0,PD_salida,PD);
	definir_rango_salida_Zu_Zdu(0,0,0,PD_salida,PD);
	definir_rango_salida_PSu_PSdu(0,0,0,PD_salida,PD);
	definir_rango_salida_PBu_PBdu(0,0,0,PD_salida,PD);
}

/*======================================================*/
/*  Common function to compute a fuzzy number           */
/*======================================================*/

static double compute(FuzzyNumber fn,double x) {
 int length = fn.length;
 int i;
 double imp; 
 double mu; 
 
 //Implication -> minimo
 //Also -> maximo
 
 //consequent_equal(i,x) grado de pertenencia de la salida
 //fn.degree[i] grado de pertenencia de las entradas

 //min(degree of applicability,grado de pertenencia de x en la funcion de membresia determinada)
 imp = OP_myOperations_Imp(fn.degree[0],consequent_equal(0,x)); 
 mu = imp;

 for(i=1; i<length; i++) {
  imp = OP_myOperations_Imp(fn.degree[i],consequent_equal(i,x));
  mu = OP_myOperations_Also(mu,imp); 
 }
 //mu determina de todas las reglas que se disparan cual es la que tiene
 //mayor grado de pertenencia
 return mu;
}

/*======================================================*/
/*  MembershipFunction MF_xfl_triangle                  */
/*======================================================*/

/*------------------------------------------------------*/
/* Function to compute an equal relationship            */
/*------------------------------------------------------*/

//Indica el grado de pertenencia en el que valor x pertenece al
//conjunto fuzzy determinado (depende del que la llame) 
static double MF_xfl_triangle_equal(double x, double min, double max, double step, double a, double b, double c) {
    return (a<x && x<=b? (x-a)/(b-a) : (b<x && x<c? (c-x)/(c-b) : 0)); 

}

/*======================================================*/
/*  Operatorset OP_myOperations                         */
/*======================================================*/

/*------------------------------------------------------*/
/* Description of the operator AND                      */
/*------------------------------------------------------*/

static double OP_myOperations_And(double a, double b) {
    return (a<b? a : b); 

}

/*------------------------------------------------------*/
/* Description of the operator ALSO                     */
/*------------------------------------------------------*/

static double OP_myOperations_Also(double a, double b) {
    return (a>b? a : b); 

}

/*------------------------------------------------------*/
/* Description of the operator IMPLICATION              */
/*------------------------------------------------------*/

static double OP_myOperations_Imp(double a, double b) {
    return (a<b? a : b); 

}

/*------------------------------------------------------*/
/* Description of the defuzzification method            */
/*------------------------------------------------------*/

static double OP_myOperations_Defuz(FuzzyNumber mf) {
 double min = mf.min;
 double max = mf.max;
 double step = mf.step;
     double x, m, num=0, denom=0;
     for(x=min; x<=max; x+=step) {
      m = compute(mf,x);
      num += x*m;
      denom += m;
     }
     if(denom==0) return (min+max)/2;
     return num/denom;

}

/*======================================================*/
/*  Type TP_e                                           */
/*======================================================*/
//Llama a la funcion que determina el grado de pertenencia
//para un conjunto especifico (el conjunto fuzzy determinado).
/*------------------------------------------------------*/
/* Description of the label NB                          */
/*------------------------------------------------------*/

static double TP_e_NB_equal(double x){
   return MF_xfl_triangle_equal(x,-1023.0,1023.0,227.33333333333334,-1534.5,-1023.0,-511.5);
}

/*------------------------------------------------------*/
/* Description of the label NS                          */
/*------------------------------------------------------*/

static double TP_e_NS_equal(double x){
   return MF_xfl_triangle_equal(x,-1023.0,1023.0,227.33333333333334,-1023.0,-511.5,0.0);
}

/*------------------------------------------------------*/
/* Description of the label Z                           */
/*------------------------------------------------------*/

static double TP_e_Z_equal(double x){
   return MF_xfl_triangle_equal(x,-1023.0,1023.0,227.33333333333334,-511.5,0.0,511.5);
}

/*------------------------------------------------------*/
/* Description of the label PS                          */
/*------------------------------------------------------*/

static double TP_e_PS_equal(double x){
   return MF_xfl_triangle_equal(x,-1023.0,1023.0,227.33333333333334,0.0,511.5,1023.0);
}

/*------------------------------------------------------*/
/* Description of the label PB                          */
/*------------------------------------------------------*/

static double TP_e_PB_equal(double x){
   return MF_xfl_triangle_equal(x,-1023.0,1023.0,227.33333333333334,511.5,1023.0,1534.5);
}

/*======================================================*/
/*  Type TP_de                                          */
/*======================================================*/

/*------------------------------------------------------*/
/* Description of the label DB                          */
/*------------------------------------------------------*/

static double TP_de_DB_equal(double x){
   return MF_xfl_triangle_equal(x,-1023.0,1023.0,227.33333333333334,-1534.5,-1023.0,-511.5);
}

/*------------------------------------------------------*/
/* Description of the label DS                          */
/*------------------------------------------------------*/

static double TP_de_DS_equal(double x){
   return MF_xfl_triangle_equal(x,-1023.0,1023.0,227.33333333333334,-1023.0,-511.5,0.0);
}

/*------------------------------------------------------*/
/* Description of the label Z                           */
/*------------------------------------------------------*/

static double TP_de_Z_equal(double x){
   return MF_xfl_triangle_equal(x,-1023.0,1023.0,227.33333333333334,-511.5,0.0,511.5);
}

/*------------------------------------------------------*/
/* Description of the label IS                          */
/*------------------------------------------------------*/

static double TP_de_IS_equal(double x){
   return MF_xfl_triangle_equal(x,-1023.0,1023.0,227.33333333333334,0.0,511.5,1023.0);
}

/*------------------------------------------------------*/
/* Description of the label IB                          */
/*------------------------------------------------------*/

static double TP_de_IB_equal(double x){
   return MF_xfl_triangle_equal(x,-1023.0,1023.0,227.33333333333334,511.5,1023.0,1534.5);
}

/*======================================================*/
/*  Type TP_duPI                                        */
/*======================================================*/

/*------------------------------------------------------*/
/* Description of the label NBdu                          */
/*------------------------------------------------------*/

static double TP_duPI_NBdu_equal(double x){
   return MF_xfl_triangle_equal(x,PI_salida.min,PI_salida.max,PI_salida.step,NBdu.a,NBdu.b,NBdu.c);
}

/*------------------------------------------------------*/
/* Description of the label NSdu                          */
/*------------------------------------------------------*/

static double TP_duPI_NSdu_equal(double x){
   return MF_xfl_triangle_equal(x,PI_salida.min,PI_salida.max,PI_salida.step,NSdu.a,NSdu.b,NSdu.c);
}

/*------------------------------------------------------*/
/* Description of the label Zdu                           */
/*------------------------------------------------------*/

static double TP_duPI_Zdu_equal(double x){
   return MF_xfl_triangle_equal(x,PI_salida.min,PI_salida.max,PI_salida.step,Zdu.a,Zdu.b,Zdu.c);
}

/*------------------------------------------------------*/
/* Description of the label PSdu                          */
/*------------------------------------------------------*/

static double TP_duPI_PSdu_equal(double x){
   return MF_xfl_triangle_equal(x,PI_salida.min,PI_salida.max,PI_salida.step,PSdu.a,PSdu.b,PSdu.c);
}

/*------------------------------------------------------*/
/* Description of the label PBdu                          */
/*------------------------------------------------------*/

static double TP_duPI_PBdu_equal(double x){
   return MF_xfl_triangle_equal(x,PI_salida.min,PI_salida.max,PI_salida.step,PBdu.a,PBdu.b,PBdu.c);
}

/*======================================================*/
/*  Type TP_uPD                                         */
/*======================================================*/

/*------------------------------------------------------*/
/* Description of the label NBu                          */
/*------------------------------------------------------*/

static double TP_uPD_NBu_equal(double x){
   return MF_xfl_triangle_equal(x,PD_salida.min,PD_salida.max,PD_salida.step,NBu.a,NBu.b,NBu.c);
}

/*------------------------------------------------------*/
/* Description of the label NSu                          */
/*------------------------------------------------------*/

static double TP_uPD_NSu_equal(double x){
   return MF_xfl_triangle_equal(x,PD_salida.min,PD_salida.max,PD_salida.step,NSu.a,NSu.b,NSu.c);
}

/*------------------------------------------------------*/
/* Description of the label Zu                           */
/*------------------------------------------------------*/

static double TP_uPD_Zu_equal(double x){
   return MF_xfl_triangle_equal(x,PD_salida.min,PD_salida.max,PD_salida.step,Zu.a,Zu.b,Zu.c);
}

/*------------------------------------------------------*/
/* Description of the label PSu                          */
/*------------------------------------------------------*/

static double TP_uPD_PSu_equal(double x){
   return MF_xfl_triangle_equal(x,PD_salida.min,PD_salida.max,PD_salida.step,PSu.a,PSu.b,PSu.c);
}

/*------------------------------------------------------*/
/* Description of the label PBu                          */
/*------------------------------------------------------*/

static double TP_uPD_PBu_equal(double x){
   return MF_xfl_triangle_equal(x,PD_salida.min,PD_salida.max,PD_salida.step,PBu.a,PBu.b,PBu.c);
}

/*======================================================*/
/*  Rulebase RL_rules                                   */
/*======================================================*/

static void RL_rules(double e, double de, double *U, Universo salida) {
 double _rl;

 double _U_degree[25];
 FuzzyNumber _U;
 _U.min = salida.min;  //minimo del universo de la variable de control
 _U.max = salida.max;  //maximo del universo de la variable de control
 _U.step = salida.step;
 _U.length = 25;  //cantidad de reglas
 _U.degree = _U_degree;  //grado de pertenencia de cada regla(grado de aplicabilidad de cada regla)
 int _U_i = 0; //counter

 //determinando el grado de pertenencia de la entrada crisp a cada funcion 
 //de membresia fuzzy de las entradas
 //y los almacena en los arreglos de las 2 entradas
 double _e_eq[5];
 _e_eq[0] = TP_e_NB_equal(e);
 _e_eq[1] = TP_e_NS_equal(e);
 _e_eq[2] = TP_e_Z_equal(e);
 _e_eq[3] = TP_e_PS_equal(e);
 _e_eq[4] = TP_e_PB_equal(e);

 double _de_eq[5];
 _de_eq[0] = TP_de_DB_equal(de);
 _de_eq[1] = TP_de_DS_equal(de);
 _de_eq[2] = TP_de_Z_equal(de);
 _de_eq[3] = TP_de_IS_equal(de);
 _de_eq[4] = TP_de_IB_equal(de);
 
 //calculan los minimos(and es minimo) para todas las posibles combinaciones
 //de las funciones de membresia activadas para 
 //todo el conjunto de entradas
 
 //Regla 0
 _rl = OP_myOperations_And(_e_eq[0],_de_eq[0]); //NB,DB=NBu
 _U_degree[_U_i] = _rl;
 _U_i++; 

 //Regla 1
 _rl = OP_myOperations_And(_e_eq[0],_de_eq[1]); //NB,DS=NBu
 _U_degree[_U_i] = _rl;
 _U_i++;  

 //Regla 2
 _rl = OP_myOperations_And(_e_eq[0],_de_eq[2]); //NB,Z=NBu
 _U_degree[_U_i] = _rl;
 _U_i++;  

 //Regla 3
 _rl = OP_myOperations_And(_e_eq[0],_de_eq[3]); //NB,IS=NBu
 _U_degree[_U_i] = _rl;
 _U_i++;	 

 //Regla 4
 _rl = OP_myOperations_And(_e_eq[0],_de_eq[4]); //NB,IB=NBu
 _U_degree[_U_i] = _rl;
 _U_i++;  

 //Regla 5
 _rl = OP_myOperations_And(_e_eq[1],_de_eq[0]); //NS,DB=NSu
 _U_degree[_U_i] = _rl;
 _U_i++;  

 //Regla 6
 _rl = OP_myOperations_And(_e_eq[1],_de_eq[1]); //NS,DS=NSu
 _U_degree[_U_i] = _rl;
 _U_i++;  

 //Regla 7
 _rl = OP_myOperations_And(_e_eq[1],_de_eq[2]); //NS,Z=NSu
 _U_degree[_U_i] = _rl;
 _U_i++;  

 //Regla 8
 _rl = OP_myOperations_And(_e_eq[1],_de_eq[3]); //NS,IS=NSu
 _U_degree[_U_i] = _rl;
 _U_i++;  

 //Regla 9
 _rl = OP_myOperations_And(_e_eq[1],_de_eq[4]); //NS,IB=NBu
 _U_degree[_U_i] = _rl;
 _U_i++;  

 //Regla 10
 _rl = OP_myOperations_And(_e_eq[2],_de_eq[0]); //Z,DB=Zu
 _U_degree[_U_i] = _rl;
 _U_i++;  
 
 //Regla 11
 _rl = OP_myOperations_And(_e_eq[2],_de_eq[1]); //Z,DS=Zu
 _U_degree[_U_i] = _rl;
 _U_i++; 
 
 //Regla 12
 _rl = OP_myOperations_And(_e_eq[2],_de_eq[2]); //Z,Z=Zu
 _U_degree[_U_i] = _rl;
 _U_i++; 
 
 //Regla 13
 _rl = OP_myOperations_And(_e_eq[2],_de_eq[3]); //Z,IS=Zu
 _U_degree[_U_i] = _rl;
 _U_i++;
 
 //Regla 14
 _rl = OP_myOperations_And(_e_eq[2],_de_eq[4]); //Z,IB=Zu
 _U_degree[_U_i] = _rl;
 _U_i++;

 //Regla 15
 _rl = OP_myOperations_And(_e_eq[3],_de_eq[0]); //PS,DB=PSu
 _U_degree[_U_i] = _rl;
 _U_i++;  

 //Regla 16
 _rl = OP_myOperations_And(_e_eq[3],_de_eq[1]); //PS,DS=PSu
 _U_degree[_U_i] = _rl;
 _U_i++;  

 //Regla 17
 _rl = OP_myOperations_And(_e_eq[3],_de_eq[2]); //PS,Z=PSu
 _U_degree[_U_i] = _rl;
 _U_i++;  

 //Regla 18
 _rl = OP_myOperations_And(_e_eq[3],_de_eq[3]); //PS,IS=PSu
 _U_degree[_U_i] = _rl;
 _U_i++;  

 //Regla 19
 _rl = OP_myOperations_And(_e_eq[3],_de_eq[4]); //PS,IB=PBu
 _U_degree[_U_i] = _rl;
 _U_i++;  

 //Regla 20
 _rl = OP_myOperations_And(_e_eq[4],_de_eq[0]); //PB,DB=PBu
 _U_degree[_U_i] = _rl;
 _U_i++;  

 //Regla 21
 _rl = OP_myOperations_And(_e_eq[4],_de_eq[1]); //PB,DS=PBu
 _U_degree[_U_i] = _rl;
 _U_i++;  

 //Regla 22
 _rl = OP_myOperations_And(_e_eq[4],_de_eq[2]); //PB,Z=PBu
 _U_degree[_U_i] = _rl;
 _U_i++;  

 //Regla 23
 _rl = OP_myOperations_And(_e_eq[4],_de_eq[3]); //PB,IS=PBu
 _U_degree[_U_i] = _rl;
 _U_i++;  

 //Regla 24
 _rl = OP_myOperations_And(_e_eq[4],_de_eq[4]); //PB,IB=PBu
 _U_degree[_U_i] = _rl;
 _U_i++; //25

 *U = OP_myOperations_Defuz(_U);
}

/*======================================================*/
/*  Rulebase RL_rulesPI                                 */
/*======================================================*/

static void RL_rulesPI(double e, double de, double *duPI) {
	double _duPI;
	RL_rules(e,de,&_duPI,PI_salida);
  *duPI = _duPI;
}

/*======================================================*/
/*  Rulebase RL_rulesPD                                 */
/*======================================================*/

static void RL_rulesPD(double e, double de, double *uPD) {
	double _uPD;
	RL_rules(e,de,&_uPD,PD_salida);
  *uPD = _uPD;
}

/*======================================================*/
/*                   Inference Engine                   */
/*======================================================*/

void PIInferenceEngine(double eI, double deP, double *_d_duPI) {
 double duPI;
 selected = PI;
 RL_rulesPI(eI, deP, &duPI);
 *_d_duPI = duPI;
}

void PDInferenceEngine(double eP, double deD, double *_d_uPD) {
 double uPD;
 selected = PD;
 RL_rulesPD(eP, deD, &uPD);
 *_d_uPD = uPD;
}

//Ver el grado de pertenencia de x en la funcion de membresia determinada
double consequent_equal(int conjunto, double x)
{	
	if(selected == PI)
	{
		switch(conjunto)
		{
			case 0: return TP_duPI_NBdu_equal(x); break;
			case 1: return TP_duPI_NBdu_equal(x); break;
			case 2: return TP_duPI_NBdu_equal(x); break;
			case 3: return TP_duPI_NBdu_equal(x); break;
			case 4: return TP_duPI_NBdu_equal(x); break;
			case 5: return TP_duPI_NSdu_equal(x); break;
			case 6: return TP_duPI_NSdu_equal(x); break;
			case 7: return TP_duPI_NSdu_equal(x); break;
			case 8: return TP_duPI_NSdu_equal(x); break;
			case 9: return TP_duPI_NBdu_equal(x); break;
			case 10: return TP_duPI_Zdu_equal(x); break;
			case 11: return TP_duPI_Zdu_equal(x); break;
			case 12: return TP_duPI_Zdu_equal(x); break;
			case 13: return TP_duPI_Zdu_equal(x); break;
			case 14: return TP_duPI_Zdu_equal(x); break;
			case 15: return TP_duPI_PSdu_equal(x); break;
			case 16: return TP_duPI_PSdu_equal(x); break;
			case 17: return TP_duPI_PSdu_equal(x); break;
			case 18: return TP_duPI_PSdu_equal(x); break;
			case 19: return TP_duPI_PBdu_equal(x); break;
			case 20: return TP_duPI_PBdu_equal(x); break;
			case 21: return TP_duPI_PBdu_equal(x); break;
			case 22: return TP_duPI_PBdu_equal(x); break;
			case 23: return TP_duPI_PBdu_equal(x); break;
			case 24: return TP_duPI_PBdu_equal(x); break;
		}
	}
	else
	{
		switch(conjunto)
		{
			case 0: return TP_uPD_NBu_equal(x); break;
			case 1: return TP_uPD_NBu_equal(x); break;
			case 2: return TP_uPD_NBu_equal(x); break;
			case 3: return TP_uPD_NBu_equal(x); break;
			case 4: return TP_uPD_NBu_equal(x); break;
			case 5: return TP_uPD_NSu_equal(x); break;
			case 6: return TP_uPD_NSu_equal(x); break;
			case 7: return TP_uPD_NSu_equal(x); break;
			case 8: return TP_uPD_NSu_equal(x); break;
			case 9: return TP_uPD_NBu_equal(x); break;
			case 10: return TP_uPD_Zu_equal(x); break;
			case 11: return TP_uPD_Zu_equal(x); break;
			case 12: return TP_uPD_Zu_equal(x); break;
			case 13: return TP_uPD_Zu_equal(x); break;
			case 14: return TP_uPD_Zu_equal(x); break;
			case 15: return TP_uPD_PSu_equal(x); break;
			case 16: return TP_uPD_PSu_equal(x); break;
			case 17: return TP_uPD_PSu_equal(x); break;
			case 18: return TP_uPD_PSu_equal(x); break;
			case 19: return TP_uPD_PBu_equal(x); break;
			case 20: return TP_uPD_PBu_equal(x); break;
			case 21: return TP_uPD_PBu_equal(x); break;
			case 22: return TP_uPD_PBu_equal(x); break;
			case 23: return TP_uPD_PBu_equal(x); break;
			case 24: return TP_uPD_PBu_equal(x); break;
		}
	}
}