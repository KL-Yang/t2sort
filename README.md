T<sup>2</sup>Sort
=============

Terabyte Trace Sort.

Problem.
=========
Use up to a few GB memory as first level buffer and up to a few TB disk as second level buffer
to sort trace flow in arbitrary order to another arbitrary order on single commodity PC.

Assume sequential I/O of second level buffer is much faster than random I/O.
The algorithm try to maximum second level buffer (disk) I/O bandwidth.

Will use io_submit(2), fallocate(2), FALLOC_FL_PUNCH_HOLE, O_DIRECT(see open(2)).

Originally: Start a Toy project to practice my C++ skill.
Now: gradually remove C++ code.
It's interesting on some old Linux distribution std::sort() seems much faster than C99 qsort,
but on Debian 10, seems C99 qsort is faster? Not a big issue.
