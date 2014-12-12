/* ---------------------------------------------------------------- *\

  file    : n_sys_users.c
  author  : m. gumz <mg@2hoch5.com>
  date    : 20141212

  license : public domain, use at own risk

  about   :

    same as, just shorter (in terms of used resources)
    $> who -u --ips | wc -l

\* ---------------------------------------------------------------- */

#include "djb/fmt.h"

#include <utmpx.h>
#include <unistd.h>

enum {
    NDIGITS = 6  // 999999 active users? :)
};

int main(int argc, char* argv[]) {

    char buf[NDIGITS];
    int  n = 0;
    struct utmpx* u;

    for (u = getutxent(); u ; u = getutxent()) {
        if (u->ut_type == USER_PROCESS) {
            n++;
        }
    }

    n = fmt_ulong(buf, n);

    write(1, buf, n);
    write(1, "\n", 1);

    return 0;
}

