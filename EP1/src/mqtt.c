#include "mqtt.h"

#include <stdio.h>
#include <stdlib.h>

fixed_header* parse_fixed_header(unsigned char* recvline) {
    fixed_header* header = malloc(sizeof(fixed_header));

    // Here, we get only the 4 most significant bits, as these
    // represent the packet type. Any flags are ignored.
    printf("%s", recvline);
    header->type = recvline[0] >> 4;

    header->length = recvline[1];

    return header;
}
