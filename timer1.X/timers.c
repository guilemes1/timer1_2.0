/*
 * File:   timers.c
 * Author: 20185189
 *
 * Created on 11 de Junho de 2021, 16:03
 * 
 * ciclo de máquina: 1us
 * 
 * estouro: TMR1 * preescaler * ciclo de máquina
 */

#include “botoes.h”
#include "delay.h"
#include <xc.h>

int contador;
unsigned long tlseg;

void timer_init (int contagem)
{
    TRISDbits.RD0 = 0;
    PORTDbits.RD0 = 0;     //Inicializa LED de sinalização

    INTCONbits.GIE = 0;    //Desliga disjuntor geral
    INTCONbits.PEIE = 1;   
    PIE1bits.TMR1IE = 1;   //ENEBLE da interrupção do TMR1
    
    // REGISTRADOR DE BLOCOS DO DIAGRAMA
    T1CONbits.TMR1CS = 0;
    T1CONbits.T1SYNC = 1;
    T1CONbits.TMR1GE = 0;
    T1CONbits.TMR1ON = 0;   //Habilita ou desabilita o timer 1   
    T1CONbits.T1CKPS0 = 0;  //Preescaler
    T1CONbits.T1CKPS1 = 0;  //Preescaler
    
    TMR1L = 156;            //100 & 0x00FF;
    TMR1H = 255;            //(100 & 0xFF00) >> 8;
    
    contador = contagem;
    tlseg = 10000;
    
    INTCONbits.GIE = 1;    //Liga disjuntor geral
}

void __interrupt() deni_son(void)
{
    if( PIR1bits.TMR1IF )       //SE HOUVER O ESTOURO
    {
        PIR1bits.TMR1IF = 0;    //LIMPA A FLAG VIA SOFTWARE
        
        TMR1L = 156;            //100 & 0x00FF;
        TMR1H = 255;            //(100 & 0xFF00) >> 8;
        --tlseg;
        if(tlseg == 0)
        {
            tlseg = 10000;
            —-contador;
        }
        
        if( S1() && contador > 0)
        {
            T1CONbits.TMR1ON = 0;            //Pausa
            while( T1CONbits.TMR1ON == 0 )
            {
                 if( S1() )                  //Retomada
                 T1CONbits.TMR1ON = 1;

                 if( S0() )                  //Reset
                 {
                      contador = contagem;
                      T1CONbits.TMR1ON = 1;
                 }
            }
        }
        

        if(contador == 0)
        {
            PORTDbits.RD0 = 1;      //LED de sinalização para término de contagem
            T1CONbits.TMR1ON = 0;   //Desliga o Timer 1

            while( T1CONbits.TMR1ON == 0 )
            {
                 if( S0() )                 //Reset
                 {
                      contador = contagem;
                      T1CONbits.TMR1ON = 1;
                 }
            }
        }
    }         
}
