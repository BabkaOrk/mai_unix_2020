fork:
	gcc -o fork practice_1_fork.c
shm:
	gcc -o shm_write practice_2_sharedm_write.c -lrt 
	gcc -o shm_print practice_2_sharedm_print.c -lrt 
udp:
	gcc -o server practice_3_udp_server.c
	gcc -o client practice_3_udp_client.c
clean:
	rm fork shm_print shm_write client server