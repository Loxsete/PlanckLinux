cmd_kernel/rcu/built-in.a := echo >/dev/null; rm -f kernel/rcu/built-in.a; ar cDPrST kernel/rcu/built-in.a kernel/rcu/update.o kernel/rcu/sync.o kernel/rcu/srcutiny.o kernel/rcu/tiny.o
