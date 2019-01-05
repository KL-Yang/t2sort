
/**
 * Public API, the rest will be hidden private API
 * */
class T2Sort 
{
    private:    //TODO need to hide this part in opaque private class
        int     flag;
        //T2Map   map;
        int     tfd;        /* Traces file descriptor */
        int     kfd;        /* Unique Keys file */
        void    init();     /* Initiation (once) before push! */

    public:
        T2Sort();
        ~T2Sort(void);
        void push(char *t, int n);      //normal push
        void sort();
        void reset();
        void pull();                    //normal pull

        char * push(int n, int *m);     //lazy push reload
        char * pull(int n, int *m);     //lazy pull reload

        //advanced setup function, must before first call of Push!
        void set_file();
        void set_key_file();            //not use key file yet! ignore it.
};
