CFLAGS+=-Wall -g -lm -lcrypt -pipe -ansi
#CFLAGS+=-Wall -g -lm -lcrypt -O2 -pipe -ansi

threaded_example: threaded_example.c
	$(CC) $< -pthread -std=c99 $(CFLAGS) -o $@
	#cc -std=c99 -pthread  -Wall -g   threaded_example.c   -o threaded_example

deadlock: deadlock.c
	$(CC) $< -pthread -std=c99 $(CFLAGS) -o $@

pipe_communication: pipe_communication.c
	$(CC) $< -std=c99 $(CFLAGS) -o $@

consumer_producer: consumer_producer.c
	$(CC) $< -pthread -std=c99 $(CFLAGS) -o $@

circular_queue: circular_queue.c
	$(CC) $< -pthread -std=c99 $(CFLAGS) -o $@

circular_queue_cond: circular_queue_cond.c
	$(CC) $< -pthread -std=c99 $(CFLAGS) -o $@

consumer_producer_sem: consumer_producer_sem.c
	$(CC) $< -pthread $(CFLAGS) -std=c99 -o $@

circular_queue_lockless: circular_queue_lockless.c
	$(CC) $< -pthread -DDEBUG $(CFLAGS) -std=c99 -o $@

compare_atomics: compare_atomics.c
	$(CC) $< -pthread $(CFLAGS) -std=c99 -o $@
