#include <stdlib.h>
#include <stdio.h>

typedef char *Address;

/* Client state enumeratino pointer */
typedef enum client_state* state;

/* A pointer to incomplete type */
typedef struct Client* ClientPtr;

/* Create a client and return a handle to it */
ClientPtr createClient(const char* name, const Address address);

/* Destroy the given client. All handles to it will be invalidated */
void destroyClient(ClientPtr client);
