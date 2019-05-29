CFLAGS+=-Wall -g -lm -lcrypt -pipe -ansi
NOANSIFLAGS+=-Wall -g -lm -lcrypt -pipe 
#CFLAGS+=-Wall -g -lm -lcrypt -O2 -pipe -ansi

threaded_example: threaded_example.c
	$(CC) $< -pthread -std=c99 $(NOANSIFLAGS) -o $@
	#cc -std=c99 -pthread  -Wall -g   threaded_example.c   -o threaded_example

deadlock: deadlock.c
	$(CC) $< -pthread -std=c99 $(NOANSIFLAGS) -o $@

pipe_communication: pipe_communication.c
	$(CC) $< -std=c99 $(NOANSIFLAGS) -o $@

consumer_producer: consumer_producer.c
	$(CC) $< -pthread -std=c99 $(NOANSIFLAGS) -o $@

circular_queue: circular_queue.c
	$(CC) $< -pthread -std=c99 $(NOANSIFLAGS) -o $@

circular_queue_mutex: circular_queue_mutex.c
	$(CC) $< -pthread -std=gnu11 $(NOANSIFLAGS) -o $@

circular_queue_cond: circular_queue_cond.c
	$(CC) $< -pthread -std=c99 $(NOANSIFLAGS) -o $@

circular_queue_one_cond: circular_queue_one_cond.c
	$(CC) $< -pthread -std=c99 $(NOANSIFLAGS) -o $@

consumer_producer_sem: consumer_producer_sem.c
	$(CC) $< -pthread $(NOANSIFLAGS) -std=c99 -o $@

circular_queue_lockless: circular_queue_lockless.c
	$(CC) $< -pthread -DDEBUG $(NOANSIFLAGS) -std=c99 -o $@

compare_atomics: compare_atomics.c
	$(CC) $< -lpthread -o $@

threadpool: threadpool.c
	$(CC) $< -pthread $(NOANSIFLAGS) -o $@

client_server: client_server.c
	$(CC) $< -pthread -luuid $(NOANSIFLAGS) -o $@

client: client.c
	$(CC) $< -pthread -luuid $(NOANSIFLAGS) -o $@

useuuid: useuuid.c
	$(CC) $< -pthread -luuid $(NOANSIFLAGS) -std=c99 -o $@

test_thread_local: test_thread_local.c
	$(CC) $< -pthread $(NOANSIFLAGS) -std=c99 -o $@

