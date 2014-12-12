/* ---------------------------------------------------------------- *\

  file    : load_avg.c
  author  : m. gumz <mg@2hoch5.com>
  date    : 20141212

  license : public domain, use at own risk

  about   :

    gets the loadavg and formats it like the first 3 fields of 
     /proc/loadavg on linux

  note    : why not use getloadavg()? it yields strange values (-0.0) 
            in the first field and the order is strange as well

\* ---------------------------------------------------------------- */

#include "djb/fmt.h"
#include "djb/open.h"

#include <stdlib.h>
#include <unistd.h>
#include <sys/param.h>

int print_load_avg(int out_fd);
int first_n_fields(int out_fd, int in_fd, char sep, int nfields);
int double_to(int out_fd, double val);


int main(int arcg, char* argv[]) {
    print_load_avg(1);
    return 0;
}

#if defined(BSD)
#include <sys/sysctl.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <vm/vm_param.h>

int print_load_avg(int out_fd) {

    struct loadavg     load;
    size_t load_size = sizeof(load);
    int nelems =       sizeof(load.ldavg)/sizeof(fixpt_t);
    int                i;
    int                mib[2] = {CTL_VM, VM_LOADAVG};
    char               buf[3];
    const char         sep[2] = " \n";
    int                blen;
    double             v;

    if (sysctl(mib, 2, &load, &load_size, 0, 0) != 0) {
        return 0;
    }

    for (i = 0; i < sizeof(load.ldavg)/sizeof(fixpt_t); i++) {
        double_to(out_fd, (double)load.ldavg[i] / (double)load.fscale);
        write(out_fd, &sep[i == (nelems-1)], 1);
    }

    return 0;
}

#else

int print_load_avg(int out_fd) {
    int fd = open_read("/proc/loadavg");
    if (fd == -1) {
        return 0;
    }
    return first_n_fields(out_fd, fd, ' ', 3);
}

#endif


// copy the bytes from 'in_fd' to 'out_fd', stop after finding
// 'n' chars 'sep'
int first_n_fields(int out_fd, int in_fd, char sep, int n) {

    int r;
    char c;

    for ( ;; ) {

        r = read(in_fd, &c, 1);
        if (r <= 0) {
            break;
        }

        if (c == sep) {
            n--;
        }

        if (n <= 0) {
            write(out_fd, "\n", 1);
            break;
        }

        write(out_fd, &c, 1);
    }

    return 1;
}


// val between 0-255, precision .2
int double_to(int out_fd, double val) {

    char buf[3];
    int blen;

    blen = fmt_ulong(buf, (int)val);
    write(out_fd, buf, blen);
    write(out_fd, ".", 1);

    val = val * 100.0;

    blen = fmt_ulong(buf, ((int)val)%100);
    if (blen == 1) {
        write(out_fd, "0", 1);
    }

    write(out_fd, buf, blen);

    return 1;
}

