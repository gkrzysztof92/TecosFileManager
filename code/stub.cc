#include <sys/stat.h>
#include <errno.h>

#undef errno

extern int errno;
register char* stack_ptr asm("sp");

//Kończy działanie programu
extern "C"
void _exit()
{
    while(true)
    { }
}

//Zwraca stan otwartego pliku
extern "C"
int _fstat(int file, struct stat* st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

//Ustawia pozycję kursora pliku
extern "C"
int _lseek(int file, int ptr, int dir)
{
    return 0;
}

//Otwiera plik
extern "C"
int _open(const char* name, int flags, int mode)
{
    return -1;
}

//Zamyka plik
extern "C"
int _close(int file)
{
    return -1;
}

//Odczytuje z pliku
extern "C"
int _read(int file, char* ptr, int len)
{
    return 0;
}

//Zapisuje do pliku
extern "C"
int _write(int file, char* ptr, int len)
{
    return len;
}

//Pobiera ID procesu
extern "C"
int _getpid()
{
    return 1;
}

//Unicestwienie procesu
extern "C"
int _kill(int pid, int sig)
{
    errno = EINVAL;
    return -1;
}

//Sprawdza czy ma do czynienia z konsolą
extern "C"
int _isatty(int filen)
{
    return 1;
}

//Zajmuje się przydzielaniem pamięci wolnej
extern "C"
caddr_t _sbrk(int incr)
{
    extern char end;
    static char* heap_end;
    char* prev_heap_end;

    if(heap_end == nullptr)
    {
        heap_end = &end;
    }

    prev_heap_end = heap_end;

    if((heap_end + incr) > stack_ptr)
    {
        errno = ENOMEM;
        return (caddr_t)-1;
    }

    heap_end += incr;
    return (caddr_t)prev_heap_end;
}

//Wskazuje adres, pod którym zostanie umieszczona para wskaźników statycznego obiektu,
//na którą składają się:
// - wskaźnik do destruktora obiektu
// - wskaźnik do obiektu

void* __dso_handle = nullptr;
