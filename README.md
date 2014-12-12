# tmux-utils

small and nonportable collection of little helpers to be used in my
tmux.conf. the primary purpose is to use small executables instead
of 'awk' etc to reduce the impact on low-end systems

## n_sys_users

counts the number of logged in users. it's equivalent to
`who -u --ips | wc -l`

## load_avg

shows the load average as it's displayed by the first 3 fields
of /proc/loadavg (linux) or systemctl vm.loadavg (freebsd)



## license:

public domain
