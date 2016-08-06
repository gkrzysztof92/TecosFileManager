ENTRY(tecos_entry_point)

MEMORY
{
  RAM(rwx): ORIGIN = 0x8000, LENGTH = 64M
}

SECTIONS
{
/*
* Zawiera kod programu
*/
  .text : {
     KEEP(*(.tecos_bootstrap))
     *(.tecos_time)
     *(.text)
  } > RAM

/*
* Zawiera zaincjowane dane programu
*/
  .data : {
    *(.data)
  } > RAM

/*
* Zawiera niezaincjowane programu
*/
  .bss : {
    __bss_start__ = .;
    *(.bss)
    *(.bss.*)
    __bss_end__ = .;
  } > RAM

/*
* Zawiera adresy statycznych obiektów
*/
  .init_array : {
    __init_array_start__ = .;
    *(.init_array)
    *(.init_array.*)
    __init_array_end__ = .;
  } > RAM

 /*
* Wymaganie do obsługi wyjątków
*/
  .ARM.exidx : {
    __exidx_start = .;
    *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    __exidx_end = .;
  } > RAM

/*
* Określnie rozmiaru wolnej pamięci (sterta + stos)
*/
  end = .;

  stack = ORIGIN(RAM) + LENGTH(RAM);
}
