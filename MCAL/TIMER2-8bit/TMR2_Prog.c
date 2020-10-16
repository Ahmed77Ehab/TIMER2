#include"../../LIB/STD_TYPES.h"
#include"../../LIB/BIT_MATH.h"
#include"TMR2_Priv.h"
#include"TMR2_Config.h"
#include"../Global Interrupt/GIE_Config.h"


/**GLOBAL POINTER TO FUNCTION**/
static void (*Gpfunc1)(void)=NULL;
static void (*Gpfunc2)(void)=NULL;
/********CALL BACK FUNCTION*****/
void TMR2_VidSetCallBackForOVF(void (*Lpfunc)(void))
{
	Gpfunc1=Lpfunc;
}
void TMR2_VidSetCallBackForCTC(void (*Lpfunc)(void))
{
	Gpfunc2=Lpfunc;
}

/*************ISR FOR TIMR2**********/
ISR(__vector_5)
{
	if(Gpfunc1 != NULL)
	{
		Gpfunc1();
	}
}

ISR(__vector_4)
{
	if(Gpfunc2 != NULL)
	{
		Gpfunc2();
	}
}

void TMR2_VidInit(void)
{
	/***************************MOODS OF TIMER0************************************/
	#if     TIMER2_Mood==Normal_MOOD
    CLR_BIT(TCCR2,WGM20);
    CLR_BIT(TCCR2,WGM21);
    #elif   TIMER2_Mood==PWM_PhaseCorrect_MOOD
    SET_BIT(TCCR2,WGM20);
    CLR_BIT(TCCR2,WGM21);
    #elif    TIMER2_Mood==CTC_MOOD
    CLR_BIT(TCCR2,WGM20);
    SET_BIT(TCCR2,WGM21);
    #elif   TIMER2_Mood==FAST_PWM_MOOD 
    SET_BIT(TCCR2,WGM20);
    SET_BIT(TCCR2,WGM21);
    #endif
	
	/***************************MOODS OF PRESCALER************************************/
	#if      Prescaler_Mood_TIMER2 ==NO_CLOCK_TIMER2
    CLR_BIT(TCCR2,CS20);
    CLR_BIT(TCCR2,CS21);
    CLR_BIT(TCCR2,CS22);
    #elif    Prescaler_Mood_TIMER2 ==NO_PRESCALER_TIMER2 
    CLR_BIT(TCCR2,CS20);
    SET_BIT(TCCR2,CS21);
    CLR_BIT(TCCR2,CS22);
    #elif    Prescaler_Mood_TIMER2 ==PRESCALER_TIMER2_8
    CLR_BIT(TCCR2,CS20);
    SET_BIT(TCCR2,CS21);
    CLR_BIT(TCCR2,CS22);
    #elif    Prescaler_Mood_TIMER2 ==PRESCALER_TIMER2_64
    SET_BIT(TCCR2,CS20);
    SET_BIT(TCCR2,CS21);
    CLR_BIT(TCCR2,CS22);
    #elif    Prescaler_Mood_TIMER2 ==PRESCALER_TIMER2_256 
    CLR_BIT(TCCR2,CS20);
    CLR_BIT(TCCR2,CS21);
    SET_BIT(TCCR2,CS22);
    #elif    Prescaler_Mood_TIMER2 ==PRESCALER_TIMER2_1024
    SET_BIT(TCCR2,CS20);
    CLR_BIT(TCCR2,CS21);
    SET_BIT(TCCR2,CS22);
    #elif    Prescaler_Mood_TIMER2 ==EXT_CLOCK_TIMER2_FALLING
    CLR_BIT(TCCR2,CS20);
    SET_BIT(TCCR2,CS21);
    SET_BIT(TCCR2,CS22);
	#elif    Prescaler_Mood_TIMER2 ==EXT_CLOCK_TIMER2_RISING
    SET_BIT(TCCR2,CS20);
    SET_BIT(TCCR2,CS21);
    SET_BIT(TCCR2,CS22);
	#endif
	/*************************** TIMER2 OC2_PIN**********************/
	#if  OC2_MOOD==Normal_port_operation
    CLR_BIT(TCCR2,COM20);
    CLR_BIT(TCCR2,COM21);
    #elif   OC2_MOOD==Toggle_OC2 
    SET_BIT(TCCR2,COM20);
    CLR_BIT(TCCR2,COM21);
	#elif   OC2_MOOD==Reserved
    SET_BIT(TCCR2,COM20);
    CLR_BIT(TCCR2,COM21);
    #elif    OC2_MOOD==Clear_OC2 
    CLR_BIT(TCCR2,COM20);
    SET_BIT(TCCR2,COM21);
    #elif   OC2_MOOD==Set_OC2 
    SET_BIT(TCCR2,COM20);
    SET_BIT(TCCR2,COM21);
    #endif
}

void TMR2_VidOverFlowInterruptEnable(void)
{
	SET_BIT(TIMSK,TOIE2);
}

void TMR2_VidOutputCompareMatchInterruptEnable(void)
{
	SET_BIT(TIMSK,OCIE2);
}

void TMR2_VidPreLoadingTheCounter(u8 LOC_u8PreLoading_Value)
{
	TCNT2=LOC_u8PreLoading_Value;
}

void TMR2_VidCompareMatchValue(u8 LOC_u8CompareMatchValue)
{
	OCR2=LOC_u8CompareMatchValue;
}

void TMR2_VidSetDutyCycle(u8 LOC_u8DutyPercentage)
{
	OCR2=(LOC_u8DutyPercentage*255)/100;
}
