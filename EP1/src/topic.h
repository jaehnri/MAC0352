#define TOPICS_SIZE 1000

/**
 * Instead of creating a structure that would carry 1 name, the number of subscribers and the array of subscribers,
 * we are creating a structure that just carries a bunch of arrays.
 * The access to a certain topic will be done accessing the index.
 *
 * topic.subscribers_length[i], topic.subscribers[i], and topic.names[i] refer to the same topic.
 *
 * Basically, it makes it easier to create the arrays, i.e, we can malloc everything (the shared memory) before
 * start listening.
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
