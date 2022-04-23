#include "mqtt.h"
#include "util.h"

#include <stdlib.h>
#include <unistd.h>

/** ================================================================================================================= */

fixed_header* parse_fixed_header(unsigned char* recvline) {
    fixed_header* header = malloc(sizeof(fixed_header));

    // Here, we get only the 4 most significant bits, as these
    // represent the packet type. Any flags are ignored.
    header->type = recvline[0] >> 4;

    header->length = recvline[1];

    return header;
}

/** ================================================================================================================= */

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

    return connack_packet;
}

/** ================================================================================================================= */

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

u_int8_t* create_suback_packet(u_int16_t message_id) {
    int i = 0;
    int length = 5;

    u_int8_t* suback_packet = malloc((length + 1) * sizeof(u_int8_t));

    // Packet type + flags
    suback_packet[i++] = SUBACK << 4;

    // Message Length
    suback_packet[i++] = 3;

    // Message ID
    suback_packet[i++] = (u_int8_t)(message_id >> 8);
    suback_packet[i++] = (u_int8_t)message_id;

    // Granted QoS is "Fire and Forget"
    suback_packet[i++] = 0x00;

    return suback_packet;
}

void subscribe_client(subscribe_packet* s) {
    pid_t pid = getpid();
}
/** ================================================================================================================= */
