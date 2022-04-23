#include "mqtt.h"
#include "util.h"

#include <stdlib.h>
#include <unistd.h>

fixed_header* parse_fixed_header(unsigned char* recvline) {
    fixed_header* header = malloc(sizeof(fixed_header));

    // Here, we get only the 4 most significant bits, as these
    // represent the packet type. Any flags are ignored.
    header->type = recvline[0] >> 4;

    header->length = recvline[1];

    return header;
}

u_int8_t* create_connack_packet() {
    int i = 0;
    int length = 4;

    u_int8_t* connack_packet = malloc((length + 1) * sizeof(u_int8_t));

    // Packet type + flags
    connack_packet[i++] = CONNACK << 4;

    // Message Length
    connack_packet[i++] = 2;

    // Acknowledge flags
    connack_packet[i++] = 0x00;

    // Return code
    connack_packet[i++] = 0x00;

    print_hex(connack_packet, 4);

    return connack_packet;
}

subscribe_packet* parse_subscribe_packet(unsigned char* recvline) {
    subscribe_packet* s = malloc(sizeof(subscribe_packet));

    // We hardcode i = 2 so we skip the fixed header in recvline.
    int i = 2;

    s->message_identifier = (1 << 8) * recvline[i] + recvline[i + 1]; i += 2;
    s->topic_length       = (1 << 8) * recvline[i] + recvline[i + 1]; i += 2;

    s->topic              = malloc((s->topic_length + 1) * sizeof(unsigned char));
    memcpy(s->topic, &recvline[i], s->topic_length);
    s->topic[s->topic_length] = 0;

    return s;
}

void subscribe_client(subscribe_packet* s) {
    pid_t pid = getpid();
}