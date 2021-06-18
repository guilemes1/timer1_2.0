/*
 * File:   delay.c
 * Author: 20185189
 *
 * Created on 3 de Fevereiro de 2021, 17:46
 */

#include <xc.h>

void botoes_init (void)
{
     TRISCbits.RC0 = 1;
     TRISCbits.RC1 = 1;
}

char S1 ( void )
{
     return(PORTCbits.RC1);
}

char S0 ( void )
{
     return(PORTCbits.RC0);
}
