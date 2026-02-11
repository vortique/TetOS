/* Tell the linker to produce an ELF64 executable for x86-64 architecture */
OUTPUT_FORMAT(elf64-x86-64)

/* Set the entry point of our kernel */
ENTRY(kmain)

/* Define the program headers so we get right MMU permissions */
/* from bootloader */
PHDRS
{
    limine_requests PT_LOAD;
    text            PT_LOAD;
    rodata          PT_LOAD;
    data            PT_LOAD;
}

SECTIONS
{
    /* Half kernel loading logic. We want to place the kernel at the top */
    /* 2 GiB of addresses space. */
    . = 0xffffffff80000000;

    /* Define a section for containing limine requests and assign it to */
    /* its own program header */
    .limine_requests : {
        KEEP(*(.limine_requests_start))
        KEEP(*(.limine_requests))
        KEEP(*(.limine_requests_end))
    } : limine_requests

    /* Move to the next memory page for text */
    . = ALIGN(CONSTANT(MAXPAGESIZE));

    .text : {
        *(.text .text.*)
    } : text

    . = ALIGN(CONSTANT(MAXPAGESIZE));

    .rodata : {
        *(.rodata .rodata.*)
    } : rodata

    .note.gnu.build-id : {
        *(.note.gnu.build-id)
    } : rodata

    . = ALIGN(CONSTANT(MAXPAGESIZE));

    .data : {
        *(.data .data.*)
    } : data

    /* BSS should be the last thing mapped to .data. */
    /* If mapped randomly there will be useless zeros in binary. */
    /* NOTE: Teto doesn't want this. */
    .bss : {
        *(.bss .bss.*)
        *(COMMON)
    } : data    

    /DISCARD/ : {
        *(.eh_frame*)
        *(.note .note.*)
    }
}