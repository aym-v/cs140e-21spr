### A quick and dirty guide to making a r/pi simulator.

The file `fake-pi.c` implements a trivial fake r/pi system that will allow
you to debug your `gpio.c` code on your laptop.  You can compile it along
with `gpio.c` and whatever driver you want to produce an executable that
you can run on your laptop.

        cd 2-cross-check/fake-pi
        # not necessary but makes things easier:
        #    make a sym link to shorten the paths.
        % ln -s ../../1-gpio/code code

        % gcc -g -Wall -Icode code/gpio.c code/1-blink.c  fake-pi.c -o 1-blink
        % ./1-blink
        calling pi code
        GET32(20200008) = 643c9869
        ... bunch of PUT32/GET32's ...
        PUT32(2020001c) = 100000
        PUT32(20200028) = 100000
        pi exited cleanly

        % gcc -g -Wall -Icode code/gpio.c code/2-blink.c  fake-pi.c -o 2-blink
        % ./2-blink
        calling pi code
        GET32(20200008) = 643c9869
        PUT32(20200008) = 643c9869
        ... bunch of calls ...
        PUT32(20200028) = 100000
        PUT32(2020001c) = 200000
        pi exited cleanly

        % gcc -g -Wall -Icode code/gpio.c code/3-input.c fake-pi.c -o 3-input
        % ./3-input
        calling pi code
        GET32(20200008) = 643c9869
        PUT32(20200008) = 643c9869
        GET32(20200008) = 643c9869
        PUT32(20200008) = 643c9841
        GET32(20200034) = 19495cff
        PUT32(20200028) = 100000
        GET32(20200034) = 2ae8944a
        ... repeats forever ...

You can also just use:

        % make
        % ls
        1-blink  2-blink  3-input  fake-pi.c  Makefile	README.md

Some nice things:

    1. You can run the "pi" program using a debugger;
    2. You have memory protection, so null pointer writes get detected.
    3. You can run with tools (e.g., valgrind) to look for other errors.
    4. Finally: By comparing the actual put/get values can check your
       code against other people (today's lab).  If your sequence of is 
       identical to theirs, that proves your code is equivalant (on that run)
       to theirs, despite the two implementations looking very different.

While `fake-pi.c` is laughably simple and ignores more than it handles,
it can still get enough accuracy (fidelity) with how the code behaves
on the r/pi to be useful.  How:

   1. Most of your code is just straight C code, which runs the same on
      your laptop and the r/pi.
   2. While there is some ARM assembly (in `start.S`), which we cannot run
      it's small/simple enough we can replace it with C versions.
      If you look in `fake-pi.c` you'll see implementations of `PUT32`,
      `GET32` as well as the code that runs before `notmain`.
   3. The main pi specific thing we need to handle is what exactly
      happens when you read/write GPIO addresses.   Given how simple
      these are, we can get away with just treating them as memory, where
      the next read returns the value of the last write.  For fancier
      hardware, or for a complete set of possible GPIO behaviors we
      might have to do something more elaborate.  But for our GPIO usage,
      this is enough.

      NOTE: this problem of how to model devices accurately is a big
      challenge both for virtual machines and machine simulators.

It's good to understand what is going on here.  both why it works,
and when you can use this kind of trick in other places.

   - If you step back and think, one intersting thing leaps out
     immediately: we can transparently take code that you wrote explicitly
     to run bare-metal on the pi ARM cpu, and interact with the weird
     broadcom chip and run it on your laptop, which has neither, *without
     making any change!*

   - Another interesting hack: if you keep everything the same, but
     replace the `PUT32` and `GET32` with code that sends `PUT32` and
     `GET32` messages over to the pi using the UART, you can have a tiny
     driver on the pi wait for these and then act on them.  This lets you
     control the pi hardware "for real" just as you would when running
     on the pi, while still having all your code run on your laptop,
     with its nice environment.  

     We will do a hack like this in an upcoming lab.  It's especially cool
     when you do this over a network, and broadcast the messages to many
     pi's that operate in unison.  (E.g., for large light installations.)
