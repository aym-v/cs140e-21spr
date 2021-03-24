## CS140E: embedded operating systems (Engler, Spring 2021)

***This is currently being updated***




This is a lab-based class with no explicit lectures.  We will do two
three-to-five hour labs each week.  You should be able to complete
almost all of the lab in one sitting.  There will be several homeworks,
that act as mini-captone projects tying together the preceding labs.
Since we are breaking new ground by having the class virtual only,
we may add an additional discussion section to help people that need it.

By the end of the class you will have built your own simple, clean OS
for the widely-used, ARM-based raspberry pi --- including interrupts,
threads, virtual memory, and a simple file system.  Your OS should serve
as a good base for interesting, real, sensor-based / embedded projects.

We try to work directly with primary-sources (the Broadcom and ARM6
manuals, various datasheets) since learning to understand such prose is
one of the super-powers of good systems hackers.  It will also give you
the tools to go off on your own after the course and fearlessly build
sensor-based devices using only their datasheets.

This course differs from most OS courses in that it uses real hardware
instead of a fake simulator, and almost all of the code will be written
by you.

After this quarter, you'll know/enact many cool things your peers do not.
You will also have a too-rare concrete understanding of how computation
works on real hardware.   This understanding will serve you in many other
contexts.  For what it is worth, everything you build will be stuff we
found personally useful.   There will be zero (intentional) busy-work.

### Who should take this class.

The goal of the class is to help students who are very motivated and/or
very good to go far, quickly.  We focus on building small, simple but
real OS subsystems --- threading, virtual memory, etc --- that can be
used to build many other things.

You should take this class if:

   1. You write code well OR (you don't yet write code well AND have
      a lot of time to devote to the class);

   2. AND you find these systems topics interesting.

The people that found the class valuable in the past were entirely drawn
from this demographic.  I would say that if you struggle building stuff
and are not already interested in the topic, then it's probably better
to take a different class.  I would particularly advise against taking
this class if you were looking for an easier way to satisfy a cs140
requirement.

   1. It always helps, but you do not need any background in hardware
      or OS stuff to do well in the class.  In fact, you don't even need
      to have been trained in CS: one of the best students from last year
      was a physics PhD student with fairly minimal background in coding,
      so we've had fantastic luck with non-CS folks :) With that said,
      the less background you have, the more motivation you might need.

      By the end of the class you'll have learned how to comfortably do
      many things that may well seem like superpowers and could easily
      serve you well for the next few decades.

   2. If you have background in the "embedded" space, it's worth taking
      b/c you'll learn a bunch of useful but not widely-known tricks
      (I'll pay for your supplies and a pitcher of beer if this claim
      turns out to be false!)

   3. It's also super fun.   The code you'll write can be used to
      as a basis for building many interesting systems.

      As one measure: Last year, I taught two extra follow-on classes
      (cs240lx and cs340lx) ``for free'' because of all the interesting
      things that came up from cs140e.   In addition, it's caused me
      to write more code than I have since grad school.  At my age,
      that's an unusual result :)


### What this class is not

A quick skim might falsely pattern-match on a couple of things:

   1. cs140e is *NOT* an easier version of cs140.  In fact, it can
      be quite a bit harder, since we work with raw hardware, and
      primarily use raw datasheets and ARMv6 architecture manuals
      rather than pre-digested text books or simulators.

      I'd say about 1/3 of the teaching evals from last year explicitly
      stated "do not take cs140e as an easier cs140".

      On the plus side, this approach is the adult way to do things,
      so you will be better prepared after the class for operating
      autonomously in the real world without safety nets or help.
      Everything you'll build will be stuff we personally found useful.
      There is no (intentional) busywork.

   2. Similarly, while we do use a raspberry pi for this class, and there
      are tons of blog posts/instructables/classes for novices showing
      how to use the r/pi to do simple things, this class is not that.

      You'll be writing virtual memory systems, SD card file systems,
      threads, i2c device drivers on raw hardware rather than
      cut-and-pasting some python on a library to blinky a light.

      We use the r/pi because its fairly cheap, holds up to electrical
      mistakes pretty well, runs a legit processor with legit hardware
      and is small enough to carry around easily.

With that said, I set aside the entire quarter to work on this course,
so am happy to help people that need it --- some of the biggest success
stories last year were from students that had an initially large gap
between their understanding and the topic but started to really "get it"
after some weeks of struggle.

### Stanford-specific: CS140e vs CS140

CS140e can count as a substitute for CS140 (including for PhD students
that need to fulfill a OS breadth requirement).  It is perhaps 80% of
the coding work of CS140, but likely requires a more strenuous type of
thinking at some points.  The main differences:

 1. We work with raw hardware (the r/pi A+) versus a simulator.  At the
    end you should have a simple, but actually useful embedded system
    you can do interesting tricks with.

 2. Most of the reading involves primary hardware documents, rather
    than high level discussions.   The ability to read and act on
    such documents is a super-power that will serve you well the rest of
    your career:  once you get good at it, almost anything is easy.

 3. Most of the code at the end (I hope) will be written by you, rather
    than you having to deal with a large, complicated code base.
    The downside is that we give up functionality that CS140 implements,
    the hoped-for upside is that you will have a much more thorough
    understanding of what we do cover.

 4. We focus much more on checking, somewhat-verifying your code rather
    than tossing it over the wall to TA's to grade at the end of
    an assignment.  Most of these techniques are simple (since we
    only have 10 weeks) but effective and, unfortunately, appear not
    widely-known/used by most programmers.

With that said, you are strongly encouraged to sit in the cs140
lectures: Mazieres is incredibly knowledgeable, and will serve as a
great counter-point to what we do.

### Lab policies.

   - You should be able to complete almost all of the lab in one sitting.
     If not, you *must* complete the lab within a week.  We will not
     accept a lab after this.

   - To repeat: You *must* complete the lab within a week of it being
     issued.

   - PRELABS: Before each lab there will be some preparatory reading,
     which will typically include a short set of questions you need to
     answer and turn in *before* the lab begins.  This is an attempt
     to make the labs more information-dense by handling basic stuff
     outside of it, and focusing mostly on any tricky details in it.

   - Labs are not optional!   If you are going to miss a lab you need
     to make arrangements with us before hand, and missing more than
     one or two is going to affect your grade even if you turn in the
     work on time.

We had a more flexible policy in the past.  Unfortunately, since
labs typically build on each other, once people fell behind they got
seriously lost.  Further, this year we short-staffed for the amount of
students taking the course, so don't have the resources to walk a few
students each week through makeup labs.

### Grading policy

We are currently debating whether there will be a final project.
Grading will be adjusted accordingly:
  - No project: labs 60%, homework 30%, participation 10%.
  - Final project: labs 50%, homework 20%, final project 20%,
    participation 10%.

Since this is a virtual class, and we are short-staffed, you are strongly
encouraged to help other people!    We will try to keep a note of who
does so effectively, and will guarantee that you will be pushed up a
grade if you are on the border.

Notes:
 1. Prelabs must be completed before class, and labs must be completed
    within a week to receive credit.

 2. There will be three homeworks total, which will consist of integrating
    previous labs and submitting working code.

 4. Participation: Based on class attendance and discussion,
    and newsgroup replies. Students are allowed to miss 1-2 classes,
    but must notify the instructor beforehand.

### Staff

Dawson Engler (engler@) and Akshay Srivatsan (akshay01@).

### What to do now.

First things first: 

 1. clone the class repository:

       git clone git@github.com:dddrrreee/cs140e-21spr.git

    You may need to install `git`, create a `github` account and register
    a key with github (if you don't want to do the latter, use the
    `http` clone method).  See the [PRELAB](labs/0-blink/PRELAB.md)
    for more discussion.

 2. Make sure you have access to the [cs140e
    newsgroup](https://groups.google.com/g/cs140e-21spr).  Email us
    if not!

 3. Look in the [docs](./docs) directory to get a feel for what is there.

 4. Look in the [labs](labs/README.md) directory and read through the labs in
    [0-blink](./labs/0-blink) and [1-gpio](./labs/1-gpio) which are our
    startup labs to make sure everyone is on the same page.
