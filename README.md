# Anteckningar - 2022-12-15
Implementering av timerkretsar Timer 0 - Timer 2 för timergenererade avbrott med mikrodator ATmega328P.
Specifikt används respektive timerkrets för att toggla var sin lysdiod LED1 - LED3
anslutna till pin 8 - 10 (PORTB0 - PORTB2) efter en viss tid enligt nedan:

Timer 0 togglar lysdiod 1 ansluten till pin 8 (PORTB0) var 100:e millisekund.
Timer 1 togglar lysdiod 2 ansluten till pin 9 (PORTB1) var 200:e millisekund.
Timer 2 togglar lysdiod 3 ansluten till pin 10 (PORTB2) var 1000:e millisekund.

Filen "header.h" innehåller diverse definitioner och deklarationer för implementering av systemet.

Filen "setup.c" innehåller initieringsrutiner för I/O-portar samt timerkretsarna.

Filen "interrupts.c" innehåller avbrottsrutiner för att toggla lysdioderna via timergenererade avbrott.

I filen "main.c" initieras systemet vid start, följt av att programmet hålls igång så länge matningsspänning tillförs.

Filen "timer_exercise.zip" utgör ett lösningsförslag på dagens övningsuppgift.