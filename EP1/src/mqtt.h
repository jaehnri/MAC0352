#include <sys/types.h>

/** ================================================================================================================= */

/**
 * These definitions are based on this documentation about MQTT 3.1.1:
 * http://www.steves-internet-guide.com/mqtt-protocol-messages-overview/#:~:text=The%20MQTT%20packet%20or%20message,)%20%2B%20Variable%20Header%20%2DExample%20PUBACK
 */

enum packet_type {
    CONNECT    = 0x1,
    CONNACK    = 0x2,
    PUBLISH    = 0x3,
    SUBSCRIBE  = 0x8,
    PINGREQ    = 0xc,
    DISCONNECT = 0xe
};

/**
 * As stated in the documentation, every MQTT 3.1.1 packet has a "fixed header" like the diagram below.
 *
 * The first byte is divided into two parts:
 * - The 4 most significant bits (big endian) store the packet type
 * - The 4 less significant bits store some flags.
 *
 * Then, the bytes from 2 to 5 store the remaining packet length, i.e., variable header and payload.
 *
 * |--------|---------------|---------------|
 * | Bit    | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 * |--------|---------------|---------------|
 * | Byte 1 | MQTT type     | Flags         |
 * |--------|-------------------------------|
 * | Byte 2 |                               |
 * | Byte 3 |           Remaining           |
 * | Byte 4 |           Length              |
 * | Byte 5 |                               |
 * |--------|---------------|---------------|
 */
typedef struct fixed_header {
    enum packet_type type;
    int length;
} fixed_header;

/**
 * Finds the type of the received packet and its remaining length.
 */
fixed_header* parse_fixed_header(unsigned char* packet);

/** ================================================================================================================= */

/**
 * Creates a CONNACK packet. It is hardcoded as such:
 * |--------|---------------|---------------|
 * | Bit    | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 * |--------|---------------|---------------|
 * | Byte 1 | CONNACK (0x2) | 0   0   0   0 |
 * |--------|-------------------------------|
 * | Byte 2 | Message Length    (2)         |
 * |--------|-------------------------------|
 * | Byte 3 | Acknowledge flags (0x00)      |
 * |--------|-------------------------------|
 * | Byte 4 | Return Code       (0x00)      |
 * |--------|---------------|---------------|
 */
u_int8_t* create_connack_packet();


/** ================================================================================================================= */

typedef struct subscribe_packet {
    u_int16_t message_identifier;
    u_int16_t topic_length;
    unsigned char* topic;
} subscribe_packet;

subscribe_packet* parse_subscribe_packet(unsigned char* recvline);

void subscribe_client(subscribe_packet* s);

/** ================================================================================================================= */
