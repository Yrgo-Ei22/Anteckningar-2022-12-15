/********************************************************************************
* isr.c: Innehåller avbrottsrutiner.
********************************************************************************/
#include "header.h"

/********************************************************************************
* ISR (TIMER0_OVF_vect): Avbrottsrutin som äger rum vid overflow av Timer 0,
*                        vilket äger rum var 0.128:e ms. Efter 100 ms togglas
*                        lysdiod 1. Därmed kommer 100m / 0.128m = 781 avbrott 
*                        passera mellan varje toggling. Antalet avbrott räknas
*                        upp via en 16-bitars statisk variabel, som lagras i
*                        SRAM, så att minnet för den kvarstår hela programmet.
*
*                        1. Räknar upp antalet exekverade avbrott.
*
*                        2. När räknaren har räknat upp till 781 har 100 ms
*                           passerat. Då togglas lysdioden och räknaren 
*                           nollställs inför nästa uppräkning.
********************************************************************************/
ISR (TIMER0_OVF_vect)
{
   static volatile uint16_t counter = 0;

   if (++counter >= timer_get_max_count(100))
   {
      LED1_TOGGLE;
      counter = 0;
   }

   return;
}

/********************************************************************************
* ISR (TIMER1_COMPA_vect): Avbrottsrutin som äger rum när Timer 1 har räknat 
*                          upp till toppvärdet i register OCR1A, vilket är 256.
*                          Därmed äger avbrott rum var 0.128:e ms, precis som
*                          för övriga timerkretsar. 
*
*                          Efter 200 ms togglas lysdiod 2. Därmed kommer det ske
*                          200m / 0.128m = 1563 avbrott mellan varje toggling. 
*                          Antalet exekverade avbrott räknas upp via en 
*                          16-bitars statisk variabel, som lagras i SRAM så att 
*                          minnet kvarstår hela programmet.
*
*                          1. Räknar upp antalet exekverade avbrott.
*
*                          2. När räknaren har räknat upp till 1563 har 200 ms
*                             passerat. Då togglas lysdioden och räknaren
*                             nollställs inför nästa uppräkning.
********************************************************************************/
ISR (TIMER1_COMPA_vect)
{
   static volatile uint16_t counter = 0;

   if (++counter >= timer_get_max_count(200))
   {
      LED2_TOGGLE;
      counter = 0;
   }

   return;
}

/********************************************************************************
* ISR (TIMER2_OVF_vect): Avbrottsrutin som äger rum vid overflow av Timer 2,
*                        vilket äger rum var 0.128:e ms. Efter 1000 ms togglas
*                        lysdiod 3. Därmed kommer 1000m / 0.128m = 7813 avbrott
*                        passera mellan varje toggling. Antalet avbrott räknas
*                        upp via en 16-bitars statisk variabel, som lagras i
*                        SRAM, så att minnet för den kvarstår hela programmet.
*
*                        1. Räknar upp antalet exekverade avbrott.
*
*                        2. När räknaren har räknat upp till 7813 har 1000 ms
*                           passerat. Då togglas lysdioden och räknaren
*                           nollställs inför nästa uppräkning.
********************************************************************************/
ISR (TIMER2_OVF_vect)
{
   static volatile uint16_t counter = 0;

   if (++counter >= timer_get_max_count(1000))
   {
      LED3_TOGGLE;
      counter = 0;
   }

   return;
}