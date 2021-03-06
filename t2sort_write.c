
/**
 *
 * dump
 * copy buffer to the pile, pile align at 4K page.
 * (nice-1)*pile form one sorted block
 * memory is continous within one pile, each pile an aio handle
 *
 * because 4K alignment, size of each pile need to be carefully
 * computed? or 
 *
 * read to fill (nice-1)*pile
 * each sorted block may be read at most once, but may be split
 * if have to across pile.
 * */
