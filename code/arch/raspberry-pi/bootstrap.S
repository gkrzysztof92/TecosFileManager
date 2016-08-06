/*
 Tworzy sekcję pliku ELF
*/

.section ".tecos_bootstrap"

/*
 Uruchamia procesor w trybie ARM (32-bit zestaw instrukcji)
*/

.code 32

/*
 Sprawia, że wskazane symbole są widoczne dla linkera
*/

 .global tecos_entry_point

/*
 Wczytanie zewnętrznych symboli
*/

 .extern __bss_start__
 .extern __bss_end__
 .extern __init_array_start__
 .extern __init_array_end__
 .extern stack
 .extern kernel_main

/*
 Punkt wejściowy do jądra systemu
*/

 tecos_entry_point:
	ldr sp,=stack       //Wskaźnik stosu ustawiany jest na koniec RAM

	ldr r0,=__bss_start__ //Załadowanie adresów niezainicjowanych statycznych zmiennych
	ldr r1,=__bss_end__
	mov r2,#0

	bss_init_loop: //Wstawianie wartości spod r2 do wszystkich niezaincjowanych zmiennych statycznych
        cmp r0,r1
        it lt
        strlt r2,[r0],#4
        blt bss_init_loop

        ldr r0,=__init_array_start__
        ldr r1,=__init_array_end__

    globals_init_loop: //Wywołanie konstruktorów statycznych obiektów
        cmp r0,r1
        it lt
        ldrlt r2,[r0],#4
        blxlt r2
        blt globals_init_loop


    enable_vfp: //wlacza obsluge zmiennoprzecinkowych
        mrc p15, 0, r0, c1, c0, 2
        orr r0, r0, #0x300000
        orr r0, r0, #0xC00000
        mcr p15, 0, r0, c1, c0, 2
        mov r0, #0x40000000
        fmxr fpexc, r0



	ldr r3,=kernel_main //Załadowanie adresu głównej funkcji jądra systemu do rejestru r3
	blx r3		    //Wywołanie głównej funkcji jądra systemu


 hang:			    //Zawieszenie pracy urządzenia
	b  hang


