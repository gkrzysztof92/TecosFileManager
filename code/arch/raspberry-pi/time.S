.section ".tecos_time"

/*
 Uruchamia procesor w trybie ARM (32-bit zestaw instrukcji)
*/

.code 32

/*
 Sprawia, że wskazane symbole są widoczne dla linkera
*/

 .global DelayCycles

 /*
Odlicza określoną liczbę cykli
 */

 DelayCycles:
    subs r0, r0, #1
    bhi DelayCycles
    mov pc, lr
