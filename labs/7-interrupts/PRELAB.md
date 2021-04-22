## Prelab for interrupts

For this lab, we're going to do interrupts and use them to build a
statistical profiler.   You'll need to implement a simple `kmalloc`
to do so.

---------------------------------------------------------------------------
### Readings

You should definitely make sure to read the two pdf's in the `7-interrupts/docs`:

  - `BCM2835-ARM-timer-int.annot.pdf` --- excerpt from the Broadcom document,
     discusses how to enable both general and timer interrupts.

   - `armv6-interrupts.annot.pdf` ---  excerpt from the ARMv6 document in 
     our main `doc` directory.  Discusses where and how interrupts are delivered.
     You should figure out where the handler lives, and registers are written
     what values, and how to restore them.


-------------------------------------------------------------------------------
###  Implement the unfinished routines in  `0-kmalloc/kmalloc.c`

In today's lab we want to allocate an array the size of the text (code)
segment, so we would like a kernel memory allocator.   To let us focus
on getting things done easily, we are are just going to do a trivial one
that does not support free's of individual blocks.  The great thing about
memory allocation without free is that it is trivial: simply increment
a pointer!  (Note, we do have a free of the entire memory space: it's
called `rpi_reboot`).

The first problem we have is figuring out where the heap starts.  We will
use a simple hack: just put it at the end of the pi program:

  - If you look at the linker script `libpi/memmap`, you can see that it
    tells the linker to place a symbol `__heap_start__` at the end of
    the executable so we can locate it.  The address of this variable
    is the address of the start of the heap.

The second problem we have is that when we allocate, we have to make
sure that the memory returned can be accessed without causing an
alignment fault.  Since the pi only requires 4-byte alignment, we can
just make sure every returned block is at least 4-byte aligned (i.e.,
the lower two bits should be 0).

Your implementation should do the following:
   1. In `kmalloc_init` set the heap to be the address `__heap_start__`
      is located at.  Make sure it is 4-byte aligned.  Print it to make
      sure the address makes sense.

   2. `kmalloc_init_set_start(unsigned addr)` should work the same as
      `kmalloc_init`, but set the heap to start at `addr`.

   3. In `kmalloc(nbytes)` roundup `nbytes` to be a
      multiple of four (use the `roundup` macro) and increment
      the heap pointer by the result so that the next allocation
      occurs afterwards.  Assert that the result makes sense.

   4. `kmalloc_aligned`: make sure the returned pointer is aligned to
      `alignment` and is of size `nbytes`.


When you are done:
  1. Make sure all the tests pass by running `make check`.
  2. Copy `kmalloc.c` to `libpi/src` and update your `put-your-src-here.mk`.
  3. In `0-kmalloc/Makefile` comment out 

            # USE_LOCAL_KMALLOC = ./kmalloc.c

     and make sure `make check` still passes.

Various further readings:
  - A reasonable article on [linker scripts](https://interrupt.memfault.com/blog/how-to-write-linker-scripts-for-firmware)
  - [Regon allocation] (https://en.wikipedia.org/wiki/Region-based_memory_management).
  - [Arena allocation] (http://drhanson.s3.amazonaws.com/storage/documents/fastalloc.pdf).

