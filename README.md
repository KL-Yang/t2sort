T<sup>2</sup>Sort
=============

Terabyte Trace Sort.

Problem.
=========
Use up to a few GB memory as first level buffer and up to a few TB disk as second level buffer
to sort trace flow in arbitrary order to another arbitrary order on single commodity PC.

Assume sequential I/O of second level buffer is much faster than random I/O.
Which means the I/O bandwidth is relatively large but the IOPS is limited.
The algorithm try to maximum the utilization of second level buffer (disk) I/O bandwidth.

This is very true for Mechanical Hard Disk Drive. While SSD has much better IOPS compares to HDD.
For TLC and QLC SSD, sustained random 4K read is still one tenth to one third of sequential read.
And sustained 4K random write is about half to a quarter of sequential write.
Still leaves space for optimal sorting algorithm.
DIO and io_uring may still greatly reduce the CPU cost of sorting.

Will use io_submit(2), io_uring_setup(2), fallocate(2), FALLOC_FL_PUNCH_HOLE, O_DIRECT(see open(2)).

Originally: Start a Toy project to practice my C++ skill.
Now: gradually abandon C++ code.
It's interesting on some old Linux distribution std::sort() seems much faster than C99 qsort,
but on Debian 10, seems C99 qsort is faster? Not a big issue.
