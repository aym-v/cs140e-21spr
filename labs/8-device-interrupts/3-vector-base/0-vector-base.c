// driver to see if relocation works; tests speedup.
#include "rpi.h"
#include "rpi-interrupts.h"
#include "vector-base.h"

// in swi-hack.S
unsigned swi_add(unsigned);

void test_swi(const char *msg);

void software_interrupt_vector(unsigned pc) {
    panic("called from %p\n", pc);
}

void bad_exception(unsigned pc) {
    panic("bad exception: called from %p\n", pc);
}

static void set_base(void *vector_base, int verbose_p) {
    if(verbose_p) 
        output("vector base=%p\n", vector_base);
    vector_base_set(vector_base);
    if(verbose_p) 
        output("vector base get=%p\n", vector_base_get());
    assert(vector_base_get() == vector_base);

    if(verbose_p) 
        printk("swi_add=%d\n", swi_add(1));
    assert(swi_add(0x12345678) == 0x12345679);
}

#include "cycle-count.h"

void notmain(void) {
    
    // in swi-hack.S
    extern uint8_t _interrupt_vector_slow;
    extern uint8_t _interrupt_vector_fast;

    set_base(&_interrupt_vector_slow, 1);
    test_swi("slower relocation (no cache)");

    set_base(&_interrupt_vector_fast, 0);
    test_swi("faster relocation (no cache)");

    enable_cache();

    set_base(&_interrupt_vector_slow, 0);
    test_swi("slower relocation (cache)");

    set_base(&_interrupt_vector_fast, 0);
    test_swi("faster relocation (cache)");

}

void test_swi(const char *msg) {
    cycle_cnt_init();
    unsigned s = cycle_cnt_read();
    swi_add(1);
    swi_add(1);
    swi_add(1);
    swi_add(1);
    swi_add(1);
    swi_add(1);
    swi_add(1);
    swi_add(1);
    swi_add(1);
    swi_add(1);
    swi_add(1);

    printk("%s: took cycles=%d\n", msg, cycle_cnt_read() - s);
}

