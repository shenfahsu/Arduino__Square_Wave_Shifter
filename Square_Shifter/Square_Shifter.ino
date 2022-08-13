
//---------------------------------------------------------------------------
/*
//==========================================
// Author : shenfa@shenfa.idv.tw
//==========================================
*/
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

#define		Pin_DO			(13)
#define		Pin_DI			(2)

#define		Pin_Potentiometer	(A0)
#define		Potentiometer_Const	(856)

#define		Out_Level_High		(0)
#define		Out_Level_Low		(1)

#define		In_Level_High		(1)
#define		In_Level_Low		(0)


void	setup()
{
	Serial.begin( 9600 );

	// put your setup code here, to run once:
//	pinMode( Pin_DI, INPUT_PULLUP );
	pinMode( Pin_DI, INPUT );
	pinMode( Pin_DO, OUTPUT );

	digitalWrite( Pin_DO, Out_Level_Low );

	Serial.println("Initialized!");
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



int	Read_Potentiometer( void )
{
	int	val;

	val = analogRead( Pin_Potentiometer );
	return( Potentiometer_Const - val );
}

void	loop()
{
	// put your main code here, to run repeatedly:

	int	val;

	val = Read_Potentiometer();
	Serial.println( val );		// debug value

	delay( 1000 );
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
