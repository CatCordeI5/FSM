ENTRY(_start)
SECTIONS {
    . = 0x7C00;
    .boot : { *(.boot) }
    . = 0x10000;
    .text : { *(.text) }
    .data : { *(.data) }
    .bss : { *(.bss) }
}
