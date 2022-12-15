/********************************************************************************
* isr.c: Inneh�ller avbrottsrutiner.
********************************************************************************/
#include "header.h"

/********************************************************************************
* ISR (TIMER0_OVF_vect): Avbrottsrutin som �ger rum vid overflow av Timer 0,
*                        vilket �ger rum var 0.128:e ms. Efter 100 ms togglas
*                        lysdiod 1. D�rmed kommer 100m / 0.128m = 781 avbrott 
*                        passera mellan varje toggling. Antalet avbrott r�knas
*                        upp via en 16-bitars statisk variabel, som lagras i
*                        SRAM, s� att minnet f�r den kvarst�r hela programmet.
*
*                        1. R�knar upp antalet exekverade avbrott.
*
*                        2. N�r r�knaren har r�knat upp till 781 har 100 ms
*                           passerat. D� togglas lysdioden och r�knaren 
*                           nollst�lls inf�r n�sta uppr�kning.
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
* ISR (TIMER1_COMPA_vect): Avbrottsrutin som �ger rum n�r Timer 1 har r�knat 
*                          upp till toppv�rdet i register OCR1A, vilket �r 256.
*                          D�rmed �ger avbrott rum var 0.128:e ms, precis som
*                          f�r �vriga timerkretsar. 
*
*                          Efter 200 ms togglas lysdiod 2. D�rmed kommer det ske
*                          200m / 0.128m = 1563 avbrott mellan varje toggling. 
*                          Antalet exekverade avbrott r�knas upp via en 
*                          16-bitars statisk variabel, som lagras i SRAM s� att 
*                          minnet kvarst�r hela programmet.
*
*                          1. R�knar upp antalet exekverade avbrott.
*
*                          2. N�r r�knaren har r�knat upp till 1563 har 200 ms
*                             passerat. D� togglas lysdioden och r�knaren
*                             nollst�lls inf�r n�sta uppr�kning.
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
* ISR (TIMER2_OVF_vect): Avbrottsrutin som �ger rum vid overflow av Timer 2,
*                        vilket �ger rum var 0.128:e ms. Efter 1000 ms togglas
*                        lysdiod 3. D�rmed kommer 1000m / 0.128m = 7813 avbrott
*                        passera mellan varje toggling. Antalet avbrott r�knas
*                        upp via en 16-bitars statisk variabel, som lagras i
*                        SRAM, s� att minnet f�r den kvarst�r hela programmet.
*
*                        1. R�knar upp antalet exekverade avbrott.
*
*                        2. N�r r�knaren har r�knat upp till 7813 har 1000 ms
*                           passerat. D� togglas lysdioden och r�knaren
*                           nollst�lls inf�r n�sta uppr�kning.
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