#ifndef MOSQUITTO_EMBED_H
#define MOSQUITTO_EMBED_H

#include "mosquitto_broker_internal.h"
#include "mqtt_protocol.h"


typedef void * mosq_user_context_t;
// typedef void (*FUNC_plugin_sub__on_send)(
// 	struct mosquitto_db *db, 
// 	struct mosquitto *context, 
// 	const char *topic, 
// 	struct mosquitto_msg_store *store, 
//  mosquitto_property *properties
// 	void* plugin_context);
typedef FUNC_plugin_sub__on_send mosq_subscribe_callback;

// Embedded API
struct mosquitto_db *mosquitto__get_db(void);
void mosquitto__get_listensock(mosq_sock_t **lsock,int *lsock_count);
int mosquitto_init(int argc, char *argv[]);
int mosquitto_deinit();

typedef void (*mosquitto__on_accept_cb)(struct mosquitto * mosq_context, mosq_sock_t sock, mosq_user_context_t user_context);
typedef void (*mosquitto__on_write_block_cb)(struct mosquitto * mosq_context, mosq_sock_t sock, mosq_user_context_t user_context);
void mosquitto__readsock(struct mosquitto_db *db, mosq_sock_t ready_sock, mosquitto__on_accept_cb on_accept, mosq_user_context_t user_context);
void mosquitto__writesock(struct mosquitto_db *db, mosq_sock_t ready_sock);
void mosquitto__closesock(struct mosquitto_db *db, mosq_sock_t ready_sock);
void mosquitto__on_write_block(struct mosquitto * mosq_context, mosquitto__on_write_block_cb on_write_block_cb, mosq_user_context_t user_context);
void mosquitto__loop_step(struct mosquitto_db *db);

// Plugin API
struct mosquitto * mosquitto_plugin__create_context(struct mosquitto_db *db, char* client_id);
int mosquitto_plugin__subscribe(struct mosquitto_db *db, struct mosquitto * mosq_context, char *sub, mosq_subscribe_callback subscribe_callback, mosq_user_context_t user_context);
int mosquitto_plugin__unsubscribe(struct mosquitto_db *db, struct mosquitto * mosq_context, char *sub);
int mosquitto_plugin__publish(
	struct mosquitto_db *db, 
	struct mosquitto *mosq_context,
	char *topic, 
	int qos, 
	uint32_t payloadlen, 
	uint8_t * payload_ptr,
	int retain, 
	uint32_t message_expiry_interval,
	mosquitto_property *msg_properties);

// see mosquitto_property_add_* in mosquitto.h
// MQTT_PROP_PAYLOAD_FORMAT_INDICATOR = 1,		/* Byte :				PUBLISH, Will Properties */
// MQTT_PROP_MESSAGE_EXPIRY_INTERVAL = 2,		/* 4 byte int :			PUBLISH, Will Properties */
// MQTT_PROP_CONTENT_TYPE = 3,					/* UTF-8 string :		PUBLISH, Will Properties */
// MQTT_PROP_RESPONSE_TOPIC = 8,				/* UTF-8 string :		PUBLISH, Will Properties */
// MQTT_PROP_CORRELATION_DATA = 9,				/* Binary Data :		PUBLISH, Will Properties */
// MQTT_PROP_SUBSCRIPTION_IDENTIFIER = 11,		/* Variable byte int :	PUBLISH, SUBSCRIBE */
// MQTT_PROP_TOPIC_ALIAS = 35,					/* 2 byte int :			PUBLISH */


#endif /* MOSQUITTO_EMBED_H */
