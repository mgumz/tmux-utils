CC?=cc

ALL=n_sys_users load_avg

N_SYS_USERS=n_sys_users.c djb/fmt_ulong.c
LOAD_AVG=load_avg.c djb/fmt_ulong.c djb/open_read.c

all: $(ALL)

clean:
	rm -vf $(ALL)

n_sys_users: $(N_SYS_USERS)
	$(CC) -o $@ $(CFLAGS) -Idjb $(N_SYS_USERS)

load_avg: $(LOAD_AVG)
	$(CC) -o $@ $(CFLAGS) -Idjb $(LOAD_AVG)

diet:
	$(MAKE) CC="diet -Os cc"
