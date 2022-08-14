
//---------------------------------------------------------------------------
/*
//==========================================
// Author : shenfa@shenfa.idv.tw
//==========================================
*/
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

#define		Pin_DO				(7)
#define		Pin_DI				(2)

#define		Pin_Potentiometer		(A0)
#define		Potentiometer_Const		(856)
#define		Potentiometer_Phase_Step	(22.22)

#define		Out_Level_High			(0)
#define		Out_Level_Low			(1)

#define		In_Level_High			(1)
#define		In_Level_Low			(0)

enum	Level_State__Enum {
	Level_State__Triggered,
	Level_State__Low,
	Level_State__High,

	Level_State__Enums
};


enum	Level_State__Enum	Current_State = Level_State__Enums;
unsigned int			Phase_Delay_uS = 0;
int				Potentiometer__Last = 0;

void	EInt_ISR()
{
	Current_State = Level_State__Triggered;
}


void	setup()
{
	// put your setup code here, to run once:
	Serial.begin( 9600 );

	pinMode( Pin_DI, INPUT_PULLUP );
	attachInterrupt( digitalPinToInterrupt( Pin_DI ), EInt_ISR, FALLING );

//	pinMode( Pin_DI, INPUT_PULLUP );
// 	pinMode( Pin_DI, INPUT );
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
	if( Potentiometer__Last != val ) {
		Potentiometer__Last = val;
		Serial.println( val );		// debug value
	}
	return( Potentiometer_Const - val );
}

int	Get_Phase_Delay( void )
{
	int	val;
	float	phase_step = Potentiometer_Phase_Step;

	val = Read_Potentiometer();
	if( val > 720 ) val = 720;
	val >>= 1;
	phase_step *= val;
	return( phase_step / 2 );
}

void	loop()
{
	// put your main code here, to run repeatedly:
	switch( Current_State ) {
	case Level_State__Triggered:
		Phase_Delay_uS = Get_Phase_Delay();
		Current_State = Level_State__Low;
		delayMicroseconds( Phase_Delay_uS );

	case Level_State__Low:
		digitalWrite( Pin_DO, Out_Level_Low );
		Current_State = Level_State__High;
		delayMicroseconds( 4000 );

	case Level_State__High:
		digitalWrite( Pin_DO, Out_Level_High );
// 		Phase_Delay_uS = Get_Phase_Delay();
		Current_State = Level_State__Enums;

	default:
		break;
	}
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
