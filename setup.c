/********************************************************************************
* setup.c: Innehåller initieringsrutiner.
********************************************************************************/
#include "header.h"

/* Statiska funktioner: */
static inline void init_ports(void);
static inline void init_timers(void);

/********************************************************************************
* setup: Initierar I/O-portar samt timerkretsar.
********************************************************************************/
void setup(void)
{
   init_ports();
   init_timers();
   return;
}

/********************************************************************************
* init_ports: Sätter lysdiodernas pinnar till utportar genom ettställning av
*             motsvarande bitar i datariktningsregister DDRB.
********************************************************************************/
static inline void init_ports(void)
{
   DDRB = (1 << LED1) | (1 << LED2) | (1 << LED3);
   return;
}

/********************************************************************************
* init_timers: Initierar timerkretsar Timer 0 - Timer 2 så att timergenererat
*              avbrott sker var 0.128:e millisekund. Alla timerkretsar aktiveras
*              direkt för att toggla var sin lysdiod efter en viss tid.
*
*              1. Aktiverar avbrott globalt via ettställning av I-flaggan
*                 (Global Interrupt Enable) i statusregister SREG via
*                 assemblerinstruktionen SEI (Set Interrupt Flag).
*
*              2. Vi ställer in uppräkningsfrekvens på Timer 0 så att avbrott
*                 sker var 128:e mikrosekund via ettställning av biten CS01
*                 (Clock Select 0 bit 1) i kontrollregistret TCCR0B 
*                 (Timer/Counter Control Register 0 B). Detta ger då en 
*                 prescaler på 8, vilket medför en uppräkningsfrekvens på 
*                 16 MHz / 8 = 2 MHz. Därmed sker inkrementering var 0.5:e us,
*                 vilket medför 256 * 0.5u = 128 us mellan varje avbrott.
*                 Eftersom vi använder Timer 0 i Normal Mode (uppräkning tills
*                 räknaren blir överfull) behöver inget annat ställas in.
*
*              3. Vi aktiverar overflow-avbrott så att en avbrottsrutin anropas
*                 när vi får overflow på Timer 0, alltså när denna räknat upp
*                 till 256, vilket sker var 0.128:e ms. Vi ettställer därmed
*                 biten TOIE0 (Timer/Counter Overflow Interrupt Enable 0) i
*                 maskregistret TIMSK0 (Timer/Counter Mask Register 0).
*                 Avbrottsrutinen har avbrottsvektor TIMER0_OVF_vect.
*
*              4. Vi ställer in Timer 1 till att arbeta i CTC Mode (Clear Timer
*                 On Compare Match), så att avbrott sker vi uppräkning av ett
*                 förvalt värde som vi lägger i registret OCR1A (Output Compare
*                 Register 1 A). Vi lägger värdet 256 i OCR1A, så att Timer 1
*                 räknar upp till 256, så som övriga timerkretsar. Därmed kommer
*                 avbrott ske var 0.128 ms, så som övriga timerkretsar. Annars
*                 om vi hade kört Normal Mode hade det tagit ca 32.8 ms mellan
*                 varje avbrott. För att genomföra detta ettställs biten WGM12
*                 (Waveform Generator Mode 1 bit 2) i kontrollregistret TCCR1B
*                 Timer/Counter Control Register 1 B).
*
*                 Dessutom sätts uppräkningsfrekvensen till 2 MHz så att vi
*                 får avbrott var 0.128 ms (vid uppräkning till 256) genom att
*                 ettställer biten CS11 (Clock Select 1 bit 1) i samma register.
*
*              5. Vi aktiverar avbrott i CTC Mode när räknaren TCNT1 har räknat
*                 upp till värdet i registret OCR1A. Eftersom toppvärdet 256
*                 ligger i A-registret, så ettställs biten OCIE1A (Output Compare
*                 Interrupt Enable 1 A) i maskregistret TIMSK1 (Timer/Counter
*                 Mask Register 1). Avbrottsrutinens avbrottsvektor är
*                 TIMER1_COMPA_vect.
*
*              6.  Vi ställer in uppräkningsfrekvens på Timer 2 så att avbrott
*                  sker var 128:e mikrosekund via ettställning av biten CS21
*                  (Clock Select 2 bit 1) i kontrollregistret TCCR2B
*                  (Timer/Counter Control Register 0 B). Detta ger då en
*                  prescaler på 8, vilket medför en uppräkningsfrekvens på
*                  16 MHz / 8 = 2 MHz. Därmed sker inkrementering var 0.5:e us,
*                  vilket medför 256 * 0.5u = 128 us mellan varje avbrott.
*                  Eftersom vi använder Timer 2 i Normal Mode (uppräkning tills
*                  räknaren blir överfull), så behöver inget annat ställas in.
*
*              7. Vi aktiverar overflow-avbrott så att en avbrottsrutin anropas
*                 när vi får overflow på Timer 2, alltså när denna räknat upp
*                 till 256, vilket sker var 0.128:e ms. Vi ettställer därmed
*                 biten TOIE2 (Timer/Counter Overflow Interrupt Enable 2) i
*                 maskregistret TIMSK2 (Timer/Counter Mask Register 2).
*                 Avbrottsrutinen har avbrottsvektor TIMER2_OVF_vect.
********************************************************************************/
static inline void init_timers(void)
{
   asm("SEI");
   TCCR0B = (1 << CS01);
   TIMSK0 = (1 << TOIE0);

   TCCR1B = (1 << WGM12) | (1 << CS11);
   OCR1A = 256;
   TIMSK1 = (1 << OCIE1A);

   TCCR2B = (1 << CS21);
   TIMSK2 = (1 << TOIE2);
   return;
}