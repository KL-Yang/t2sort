#ifndef C_AIO_POSIX_T2SORT
#define C_AIO_POSIX_T2SORT
/**
 * wrap posix-aio, linux-aio and io-uring to the same API.
 * as drivers, set the aio-driver function pointer at initiation.
 * */
void t2sort_aio_setup() {   /* do nothing */ }
void t2sort_aio_destroy() { /* do nothing */ }

void
t2sort_aio_write(t2sort_aio_t *t2cb, int fd, void *buf, 
            size_t count, off_t offset)
{
    //some system posix-aio can only write up to 2GB at once
    t2cb->paio.aio_fildes = fd;
    t2cb->paio.aio_buf    = buf;
    t2cb->paio.aio_nbytes = count;
    t2cb->paio.aio_offset = offset;
    aio_write(&t2cb->paio);
}

void
t2sort_aio_read(t2sort_aio_t *t2cb, int fd, void *buf, 
            size_t count, off_t offset)
{
    t2cb->paio.aio_fildes = fd;
    t2cb->paio.aio_buf    = buf;
    t2cb->paio.aio_nbytes = count;
    t2cb->paio.aio_offset = offset;
    aio_read(&t2cb->paio);
}

//int aio_suspend(const struct aiocb * const aiocb_list[],
//int nitems, const struct timespec *timeout);
void t2sort_aio_wait(t2sort_aio_t *t2cb, int n)
{
    const struct aiocb * cblist[n];
    for(int i=0; i<n; i++)
        cblist[i] = &t2cb[i].paio;
    aio_suspend(cblist, n, NULL);
}
#endif