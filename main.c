/********************************************************************************
* main.c: Demonstration av timerkretsar Timer 0 - Timer 2. Tre lysdioder
*         anslutna till pin 8 - 10 (PORTB0 - PORTB2) togglas med olika 
*         hastigheter via var sin timerkrets.
********************************************************************************/
#include "header.h"

/********************************************************************************
* main: Initierar systemet vid start. H�ller sedan ig�ng programmet s� l�nge
*       matningssp�nning tillf�rs. Resten av programmet �r avbrottsgenererat.
********************************************************************************/
int main(void)
{
   setup();

   while (1)
   {

   }

   return 0;
}

