#include <iwdg.h>

//IWDG_Config(IWDG_Prescaler_64 ,625);//1s�ӿ��Ź�

void IWDG_Config(uint8_t prv ,uint16_t rlv)
{    
    // ʹ�� Ԥ��Ƶ�Ĵ���PR����װ�ؼĴ���RLR��д
    IWDG_WriteAccessCmd( IWDG_WriteAccess_Enable );
    
    // ����Ԥ��Ƶ��ֵ
    IWDG_SetPrescaler( prv );
    
    // ������װ�ؼĴ���ֵ
    IWDG_SetReload( rlv );
    
    // ����װ�ؼĴ�����ֵ�ŵ���������
    IWDG_ReloadCounter();
    
    // ʹ�� IWDG
    IWDG_Enable();    
}

/*************************************

#if WATCH_DOG
        IWDG_Feed();//ι��
#endif

*************************************/

void IWDG_Feed(void)
{
    // ����װ�ؼĴ�����ֵ�ŵ��������У�ι������ֹIWDG��λ
    // ����������ֵ����0��ʱ������ϵͳ��λ
    IWDG_ReloadCounter();
}