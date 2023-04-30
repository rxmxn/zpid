/*
					"Membership_Functions_and_Universe"
			PARA CREAR EL UNIVERSO DE LA VARIABLE DE salida
			Y LAS 5 FUNCIONES DE MEMBRESIA.
*/

typedef struct {double min,max,step;} Universo;

typedef struct {double a,b,c;} Conjunto;

#case
Universo PD_salida,PI_salida;
Conjunto NBu,NSu,Zu,PSu,PBu;
Conjunto NBdu,NSdu,Zdu,PSdu,PBdu;

/*
	Para seleccionar la variante 'por defecto' llamar a la funcion
	enviandole todos los parametros en 0.
*/

void guardar_cambios(Universo salida, BOOLEAN select)
{
	if(select==PD)
	{
		PD_salida.min = salida.min;
		PD_salida.max = salida.max;
		PD_salida.step = salida.step;
	}
	else
	{
		PI_salida.min = salida.min;
		PI_salida.max = salida.max;
		PI_salida.step = salida.step;
	}
}

void definir_universo_salida(double min, double max, double step, BOOLEAN select) 
{
	Universo salida;

	if(min < max)
	{
		salida.min = (min > 0 ? 0 : (min < -1023 ? -1023 : min));
		salida.max = (max < 0 ? 0 : (max > 1023 ? 1023 : max));
		salida.step = (step < 2 ? (max + fabs(min))/9 
											: (step > (max + fabs(min))/2 ? 
											(max + fabs(min))/2 : step));
	}
	else  //por defecto
	{
		if(select==PD)
		{
			salida.min = -600; //-100
			salida.max = 600; //100
			salida.step = 300; // 200/9=22.22222222222 (cardinality=10)
		}
		else
		{
			salida.min = -20;
			salida.max = 20;
			salida.step = 10; // 40/9=4.444444444444445 (cardinality=10)
		}
	}
	
	guardar_cambios(salida, select);
}

/*
	Si se desean todos los conjuntos iguales y que corten en 0.5
	llamar a las funciones con los parametros en 0.
*/

void definir_rango_salida_NBu_NBdu(double a, double b, double c, Universo salida, BOOLEAN select)
{
	double intervalo = (salida.max + fabs(salida.min))/4;  //4 porque son 5 conjuntos

/*	if(a < b && b < c)
	{
		NBu.a = a;
		NBu.b = b;
		NBu.c = c;
	}
	else //por defecto
	{*/
	if(select==PD)
	{
		NBu.a = salida.min - intervalo;
		NBu.b = NBu.a + intervalo;
		NBu.c = NBu.b + intervalo;
	}
	else
	{
		NBdu.a = salida.min - intervalo;
		NBdu.b = NBdu.a + intervalo;
		NBdu.c = NBdu.b + intervalo;
	}
//	}
}

void definir_rango_salida_NSu_NSdu(double a, double b, double c, Universo salida, BOOLEAN select)
{
	double intervalo = (salida.max + fabs(salida.min))/4;  //4 porque son 5 conjuntos

/*	if(a < b && b < c)
	{
		NSu.a = a;
		NSu.b = b;
		NSu.c = c;
	}
	else //por defecto
	{*/
	if(select==PD)
	{
		NSu.a = NBu.b;
		NSu.b = NSu.a + intervalo;
		NSu.c = NSu.b + intervalo;
	}
	else
	{
		NSdu.a = NBdu.b;
		NSdu.b = NSdu.a + intervalo;
		NSdu.c = NSdu.b + intervalo;
	}
//	}
}

void definir_rango_salida_Zu_Zdu(double a, double b, double c, Universo salida, BOOLEAN select)
{
	double intervalo = (salida.max + fabs(salida.min))/4;  //4 porque son 5 conjuntos

/*	if(a < b && b < c)
	{
		Zu.a = a;
		Zu.b = b;
		Zu.c = c;
	}
	else //por defecto
	{*/
	if(select==PD)
	{
		Zu.a = NSu.b;
		Zu.b = Zu.a + intervalo;
		Zu.c = Zu.b + intervalo;
	}
	else
	{
		Zdu.a = NSdu.b;
		Zdu.b = Zdu.a + intervalo;
		Zdu.c = Zdu.b + intervalo;
	}
//	}
}

void definir_rango_salida_PSu_PSdu(double a, double b, double c, Universo salida, BOOLEAN select)
{
	double intervalo = (salida.max + fabs(salida.min))/4;  //4 porque son 5 conjuntos

/*	if(a < b && b < c)
	{
		PSu.a = a;
		PSu.b = b;
		PSu.c = c;
	}
	else //por defecto
	{*/
	if(select==PD)
	{
		PSu.a = Zu.b;
		PSu.b = PSu.a + intervalo;
		PSu.c = PSu.b + intervalo;
	}
	else
	{
		PSdu.a = Zdu.b;
		PSdu.b = PSdu.a + intervalo;
		PSdu.c = PSdu.b + intervalo;
	}
//	}
}

void definir_rango_salida_PBu_PBdu(double a, double b, double c, Universo salida, BOOLEAN select)
{
	double intervalo = (salida.max + fabs(salida.min))/4;  //4 porque son 5 conjuntos

/*	if(a < b && b < c)
	{
		PBu.a = a;
		PBu.b = b;
		PBu.c = c;
	}
	else //por defecto
	{*/
	if(select==PD)
	{
		PBu.a = PSu.b;
		PBu.b = PBu.a + intervalo;
		PBu.c = PBu.b + intervalo;
	}
	else
	{
		PBdu.a = PSdu.b;
		PBdu.b = PBdu.a + intervalo;
		PBdu.c = PBdu.b + intervalo;
	}
//	}
}
