/********************************************************************************
* setup.c: Inneh�ller initieringsrutiner.
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
* init_ports: S�tter lysdiodernas pinnar till utportar genom ettst�llning av
*             motsvarande bitar i datariktningsregister DDRB.
********************************************************************************/
static inline void init_ports(void)
{
   DDRB = (1 << LED1) | (1 << LED2) | (1 << LED3);
   return;
}

/********************************************************************************
* init_timers: Initierar timerkretsar Timer 0 - Timer 2 s� att timergenererat
*              avbrott sker var 0.128:e millisekund. Alla timerkretsar aktiveras
*              direkt f�r att toggla var sin lysdiod efter en viss tid.
*
*              1. Aktiverar avbrott globalt via ettst�llning av I-flaggan
*                 (Global Interrupt Enable) i statusregister SREG via
*                 assemblerinstruktionen SEI (Set Interrupt Flag).
*
*              2. Vi st�ller in uppr�kningsfrekvens p� Timer 0 s� att avbrott
*                 sker var 128:e mikrosekund via ettst�llning av biten CS01
*                 (Clock Select 0 bit 1) i kontrollregistret TCCR0B 
*                 (Timer/Counter Control Register 0 B). Detta ger d� en 
*                 prescaler p� 8, vilket medf�r en uppr�kningsfrekvens p� 
*                 16 MHz / 8 = 2 MHz. D�rmed sker inkrementering var 0.5:e us,
*                 vilket medf�r 256 * 0.5u = 128 us mellan varje avbrott.
*                 Eftersom vi anv�nder Timer 0 i Normal Mode (uppr�kning tills
*                 r�knaren blir �verfull) beh�ver inget annat st�llas in.
*
*              3. Vi aktiverar overflow-avbrott s� att en avbrottsrutin anropas
*                 n�r vi f�r overflow p� Timer 0, allts� n�r denna r�knat upp
*                 till 256, vilket sker var 0.128:e ms. Vi ettst�ller d�rmed
*                 biten TOIE0 (Timer/Counter Overflow Interrupt Enable 0) i
*                 maskregistret TIMSK0 (Timer/Counter Mask Register 0).
*                 Avbrottsrutinen har avbrottsvektor TIMER0_OVF_vect.
*
*              4. Vi st�ller in Timer 1 till att arbeta i CTC Mode (Clear Timer
*                 On Compare Match), s� att avbrott sker vi uppr�kning av ett
*                 f�rvalt v�rde som vi l�gger i registret OCR1A (Output Compare
*                 Register 1 A). Vi l�gger v�rdet 256 i OCR1A, s� att Timer 1
*                 r�knar upp till 256, s� som �vriga timerkretsar. D�rmed kommer
*                 avbrott ske var 0.128 ms, s� som �vriga timerkretsar. Annars
*                 om vi hade k�rt Normal Mode hade det tagit ca 32.8 ms mellan
*                 varje avbrott. F�r att genomf�ra detta ettst�lls biten WGM12
*                 (Waveform Generator Mode 1 bit 2) i kontrollregistret TCCR1B
*                 Timer/Counter Control Register 1 B).
*
*                 Dessutom s�tts uppr�kningsfrekvensen till 2 MHz s� att vi
*                 f�r avbrott var 0.128 ms (vid uppr�kning till 256) genom att
*                 ettst�ller biten CS11 (Clock Select 1 bit 1) i samma register.
*
*              5. Vi aktiverar avbrott i CTC Mode n�r r�knaren TCNT1 har r�knat
*                 upp till v�rdet i registret OCR1A. Eftersom toppv�rdet 256
*                 ligger i A-registret, s� ettst�lls biten OCIE1A (Output Compare
*                 Interrupt Enable 1 A) i maskregistret TIMSK1 (Timer/Counter
*                 Mask Register 1). Avbrottsrutinens avbrottsvektor �r
*                 TIMER1_COMPA_vect.
*
*              6.  Vi st�ller in uppr�kningsfrekvens p� Timer 2 s� att avbrott
*                  sker var 128:e mikrosekund via ettst�llning av biten CS21
*                  (Clock Select 2 bit 1) i kontrollregistret TCCR2B
*                  (Timer/Counter Control Register 0 B). Detta ger d� en
*                  prescaler p� 8, vilket medf�r en uppr�kningsfrekvens p�
*                  16 MHz / 8 = 2 MHz. D�rmed sker inkrementering var 0.5:e us,
*                  vilket medf�r 256 * 0.5u = 128 us mellan varje avbrott.
*                  Eftersom vi anv�nder Timer 2 i Normal Mode (uppr�kning tills
*                  r�knaren blir �verfull), s� beh�ver inget annat st�llas in.
*
*              7. Vi aktiverar overflow-avbrott s� att en avbrottsrutin anropas
*                 n�r vi f�r overflow p� Timer 2, allts� n�r denna r�knat upp
*                 till 256, vilket sker var 0.128:e ms. Vi ettst�ller d�rmed
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