T<sup>2</sup>Sort
=============

Terabyte Trace Sort.

Problem.
=========
Use up to a few GB memory as first level buffer and the same amount of disk space as the 
data being sorted for second level buffer
to sort trace flow in arbitrary order to another arbitrary order on single commodity PC.

Assume sequential I/O of second level buffer is much faster than random I/O.
Which means the I/O bandwidth is relatively large but the IOPS is limited.
The algorithm try to maximum the utilization of second level buffer (disk) I/O bandwidth,
and minimize the number of I/O operation.

This is very true for Mechanical Hard Disk Drive, especially those with SMR technology. 
While SSD has much better IOPS compares to HDD.
However, for TLC/QLC SSD, sustained random 4K read speed is still one tenth to one third of sequential.
And sustained 4K random write speed is about one half to one quarter of sequential.
Still leaves space for optimal sorting algorithm.
DIO and io_uring may still greatly reduce the CPU cost of sorting.

Will use io_submit(2), io_uring_setup(2), fallocate(2), FALLOC_FL_PUNCH_HOLE, O_DIRECT(see open(2)).

Originally: Start a Toy project to practice my C++ skill.
Now: gradually abandon C++ code.
It's interesting on some old Linux distribution std::sort() seems much faster than qsort,
but on Debian 10, seems C99 qsort is faster instead? Make me doubt performance of C++ template.
Will further evaluate, but anyway it's not a big issue here.

TODO.
=========
Use new abstraction, memory management on a ring buffer, allocation on the ring buffer, 
and return to the ring buffer in the same order!
It garrantee continuous memory region, and aligned if required.
ring_malloc()
ring_return()
ring_aalloc(int *ntr, int trln, [int ext1,] int ext0)
note ext1 will be tracked by ring buffer itself! user only provide ntr and missalignment at begining.

