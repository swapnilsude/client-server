all:
		gcc server_swapnil.c -o server_swapnil
		gcc client_swapnil.c -o client_swapnil
server: server_swapnil.c
		gcc server_swapnil.c -o server_swapnil
client: client_swapnil.c
		gcc client_swapnil.c -o client_swapnil
clean:
		rm server_swapnil
		rm client_swapnil
clean_server:
		rm server_swapnil
clean_client:
		rm client_swapnil