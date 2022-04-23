#define TOPICS_SIZE 1000

/**
 * Instead of creating a structure that would carry 1 name, the number of subscribers and the array of subscribers,
 * we are creating a structure that just carries a bunch of arrays.
 *
 * Basically, it makes it easier to create the arrays. Otherwise, we would need to malloc a new topic everytime.
 */
typedef struct topic {
    int* subscribers_length;
    int** subscribers;
    unsigned char** names;
} topic;

extern topic topics;

void create_topic_structure();

void clean_topic_structure();

void send_message(unsigned char* message, unsigned char* topic);

void subscribe(unsigned char* topic);
