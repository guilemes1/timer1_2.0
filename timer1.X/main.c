/*
 * File:   main.c
 * Author: 20185189
 *
 * Created on 11 de Junho de 2021, 15:59
 */

#include "botoes.h"
#include "delay.h"
#include "config.h"
#include <xc.h>
#include "dispLCD4vias.h"
#include "timers.h"

void main(void) 
{
    dispLCD_init();
    timer_init(30);
    
    (0,0,"Contador        ");
    while(1)
    {
        dispLCD_num(0,10, contador, 4);
    }    
    
    return;
}
