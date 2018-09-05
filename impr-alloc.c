#include "impr-alloc.h"

enum client_state {
	req_auth = 0,
	try_auth = 1,
	done_auth = 2
};

struct Client {
	const char* name;
	Address address;
	enum client_state auth_state;
};

/* Create client function */
ClientPtr createClient(const char* nam, const Address add) {
	
	ClientPtr client = malloc(sizeof * client);
	
	if(client) {
		client->name = nam;
		client->address = add;
		client->auth_state = 0;	
	} else {
		printf("ERROR: Memory allocaton failed!");
		return -1;
	}
	
	return client;
}

/* Cilent authentification state changing function */
ClientPtr changeState(enum client_state st, ClientPtr cli) {
	cli->auth_state = st;
}

/* Client destroy function */
void destroyClient(ClientPtr client) {
	free(client);
}

/* Disconnection symulation thread */
ClientPtr discSym(ClientPtr cli){
	int r = rand() % 30;

	if (r > 20)
		cli->auth_state = req_auth;

	return cli;
}

/* main function */
int main(int argc, const char* argv[]) {	
	
	static int run = 1;
	ClientPtr client = createClient("Kajus", "192.168.1.160");
	printf("New client connected %s", client->name);
	
	while (run) {
		switch (client->auth_state) {
		case req_auth:
			printf("Waithing for auth..");
			sleep(1);
			client->auth_state = try_auth;
			break;
		case try_auth:
			printf("Authentificating client..");
			sleep(1);
			break;
		case done_auth:
			printf("Client connected..");
			sleep(1);
			discSym(client);
			break;
		}
	}
	
	return 0;
}
