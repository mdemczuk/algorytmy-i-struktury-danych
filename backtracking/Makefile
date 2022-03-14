CFLAGS	= -Ofast -march=native -mtune=native

outputs = euler-fleury euler-hierholzer hamilton hamilton-no-cycle

all: $(outputs)

clean:
	$(RM) $(outputs)

euler-fleury: euler.c fleury.h
	$(CC) -o $@ $(CFLAGS) -DFLEURY $<

euler-hierholzer: euler.c hierholzer.h
	$(CC) -o $@ $(CFLAGS) -DHIERHOLZER $<

hamilton: hamilton.c
	$(CC) -o $@ $(CFLAGS) $<

hamilton-no-cycle: hamilton.c
	$(CC) -o $@ $(CFLAGS) -DHAMILTON_NO_CYCLE $<
