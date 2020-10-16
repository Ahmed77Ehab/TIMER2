
#ifndef   _TMR2_INT_H
#define   _TMR2_INT_H



void TMR2_VidInit(void);
void TMR2_VidOverFlowInterruptEnable(void);
void TMR2_VidOutputCompareMatchInterruptEnable(void);
void TMR2_VidSetCallBackForCTC(void (*Lpfunc)(void));
void TMR2_VidSetCallBackForOVF(void (*Lpfunc)(void));
void TMR2_VidPreLoadingTheCounter(u8 LOC_u8PreLoading_Value);
void TMR2_VidCompareMatchValue(u8 LOC_u8CompareMatchValue);
void TMR2_VidSetDutyCycle(u8 LOC_u8DutyPercentage);


#endif






