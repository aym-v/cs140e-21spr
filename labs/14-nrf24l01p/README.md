## Build a bi-directional network stack with nrf24l01p chips


***NOTE: Make sure you start with the [PRELAB](PRELAB.md)!***

How to navigate:
  - `nrf-config.h`: this has the `nrf_config` structure and a bunch of santity checking
    for the different options (data rate, retransmission attempts, channel frequency, etc).
  - `nrf-internal.h`: contains the register definitions for the device and a bunch of helpers to
    get useful information (e.g., is the RX or TX message FIFO full or empty, get and 
    clear different interrupts, etc).
  - `nrf-internal.c`: has `nrf_dump` and the different routines to that use SPI to
    communicate with the device.  You should definitely look over `nrf_dump` to see
    how to read the different values.  You will use it to check that your `nrf_init`
    is correct.
  - `nrf-public.c`: this has the routines that call your driver.  It is currently
    setup to call our versions (with the `staff_*` prefix) --- you will just go
    through and implement these yourself one at a time and swap to using yours.

  
--------------------------------------------------------------------------------
#### Part 1: Implement `nrf_init`.

This is the longest part, since you need to set all the regsiters,
but it's also probably the most superficial, in that you can just
use `nrf_dump` to get our hardware configuration and then walk down,
replicating it.

It can get setup either for acknowledgements (`ack_p=1`) or no
acknwledgements (`ack_p=0`) but not both.
   0. `ack_p=0`: for this you only have to enable pipe 1.  No other pipe should be
      enabled.  This is used by the first test `1-*one-way` which sends bytes with
      no retransmissions from a server to a client.

   1. `ack_p=1`: for this you will have to enable both pipe 0 and pipe 1.  This is
      used by a test `2-*pingpong` which sends a 4 byte value back and forth between
      the client and the server.

You'll want to make sure that the output after running each test program
matches up.

When you swap in your `nrf_init`, both tests should work.  Open up two terminals.

To run test 1:
    1. In one terminal do:

            make crun1

    2. In the other do 

            make srun1


To run test 2 (pingpong):

    1. In one terminal do:

            make crun

    2. In the other do 

            make srun



--------------------------------------------------------------------------------
#### Part 2: Implement `nrf-driver.c:nrf_tx_send_noack`.

You'll implement sending without acknowledgements.
   1. Set the device to TX mode.
   2. Set the TX address.
   3. Use `nrf_putn` and `NRF_W_TX_PAYLOAD` to write the message to the device
   4. Pulse the `CE` pin.
   5. Wait until the TX fifo is empty.
   6. Clear the TX interrupt.
   7. When you are done, don't forget to set the device back in RX mode.

When you change `nrf_send_noack` to call your `nrf_tx_send_noack` the first test
should still work.

--------------------------------------------------------------------------------
#### Part 3: Implement `nrf-driver.c:nrf_get_pkts`.

For this part, you'll just spin until the RX fifo is empty, pulling packets off 
the RX fifo and pushing them onto their associated pipe.  For today, we're only
using a single pipe (pipe 1) so you should assert all packets are for it (you 
can use `nrf_rx_get_pipeid` for this).  For each packet you get, the code will
push it onto the pipe's circular queue (just as we did in previous labs).  You should
clear the RX interrupt.  When the RX fifo is empty, return the byte count.

When you swap in `nrf_get_pkts` in `nrf-public/nrf_pipe_nbytes` both of the tests
should still work.

--------------------------------------------------------------------------------
#### Part 4: Implement `nrf-driver.c:nrf_tx_send_ack`.

You'll implement sending with acknowledgements.  It will look similar to 
the no-ack version, except:
   1. You need to set the P0 pipe to the same address you are sending to (for acks).
   2. You need to check success using the TX interrupt (and clear it).
   3. You need to check for failure using the max retransmission interrupt (and clear it).
   4. When you are done, don't forget to set the device back in RX mode.

The second test should still work when you swap in.

Congratulations!  You now have a very useful networking system.


--------------------------------------------------------------------------------
#### Extensions

The main one I'd suggest:  change it to use interrupts!  This should
not take that long.

  1. Connect the NRF interrupt pin to GPIO pin 21.
  2. Grab the code from the GPIO interrupt lab.  and steal the initialization and 
     interrupt handler code.
  3. Should hopefully just take 20 minutes or so.
 
Do a remove put32/get32:
  1. You can write a small piece of code that waits for PUT32 and GET32 messages and
     performs them locally.
  2. This lets remote pi's control it.
  3. Should be pretty easy to make a small shim library that can run your old programs
     remotely.

Do a network bootloader.

  
Many many extensions:
  1. Use more pipes.
  2. See how fast you can go
  3. Change the interface to make it easy to change the different messages sizes.
