fork:
	gcc -o fork practice_1_fork.c
shm:
	gcc -o shm_write practice_2_sharedm_write.c -lrt 
	gcc -o shm_print practice_2_sharedm_print.c -lrt 
udp:
	gcc -o server_udp practice_3_udp_server.c
	gcc -o client_udp practice_3_udp_client.c
client-server:
	gcc -o server practice_4_server.c
	gcc -o client practice_4_client.c
memory:
	gcc -o memory practice_5_memory.c
	gcc -o cache practice_5_cache.c
clean:
	rm fork shm_print shm_write client_udp server_udp client server memory cache