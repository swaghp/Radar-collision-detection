// THIS IS AN AUTOMATICALLY GENERATED FILE.  DO NOT MODIFY
// BY HAND!!
//
// Generated by lcm-gen

#include <stdint.h>
#include <stdlib.h>
#include <lcm/lcm_coretypes.h>
#include <lcm/lcm.h>

#ifndef _Trajectory_h
#define _Trajectory_h

#ifdef __cplusplus
extern "C" {
#endif

#include "TrajectoryFrame.h"
typedef struct _Trajectory Trajectory;
struct _Trajectory
{
    int16_t    speed;
    int16_t    distance;
    int16_t    mode;
    int16_t    count;
    TrajectoryFrame *trajectory;
};

/**
 * Create a deep copy of a Trajectory.
 * When no longer needed, destroy it with Trajectory_destroy()
 */
Trajectory* Trajectory_copy(const Trajectory* to_copy);

/**
 * Destroy an instance of Trajectory created by Trajectory_copy()
 */
void Trajectory_destroy(Trajectory* to_destroy);

/**
 * Identifies a single subscription.  This is an opaque data type.
 */
typedef struct _Trajectory_subscription_t Trajectory_subscription_t;

/**
 * Prototype for a callback function invoked when a message of type
 * Trajectory is received.
 */
typedef void(*Trajectory_handler_t)(const lcm_recv_buf_t *rbuf,
             const char *channel, const Trajectory *msg, void *userdata);

/**
 * Publish a message of type Trajectory using LCM.
 *
 * @param lcm The LCM instance to publish with.
 * @param channel The channel to publish on.
 * @param msg The message to publish.
 * @return 0 on success, <0 on error.  Success means LCM has transferred
 * responsibility of the message data to the OS.
 */
int Trajectory_publish(lcm_t *lcm, const char *channel, const Trajectory *msg);

/**
 * Subscribe to messages of type Trajectory using LCM.
 *
 * @param lcm The LCM instance to subscribe with.
 * @param channel The channel to subscribe to.
 * @param handler The callback function invoked by LCM when a message is received.
 *                This function is invoked by LCM during calls to lcm_handle() and
 *                lcm_handle_timeout().
 * @param userdata An opaque pointer passed to @p handler when it is invoked.
 * @return 0 on success, <0 if an error occured
 */
Trajectory_subscription_t* Trajectory_subscribe(lcm_t *lcm, const char *channel, Trajectory_handler_t handler, void *userdata);

/**
 * Removes and destroys a subscription created by Trajectory_subscribe()
 */
int Trajectory_unsubscribe(lcm_t *lcm, Trajectory_subscription_t* hid);

/**
 * Sets the queue capacity for a subscription.
 * Some LCM providers (e.g., the default multicast provider) are implemented
 * using a background receive thread that constantly revceives messages from
 * the network.  As these messages are received, they are buffered on
 * per-subscription queues until dispatched by lcm_handle().  This function
 * how many messages are queued before dropping messages.
 *
 * @param subs the subscription to modify.
 * @param num_messages The maximum number of messages to queue
 *  on the subscription.
 * @return 0 on success, <0 if an error occured
 */
int Trajectory_subscription_set_queue_capacity(Trajectory_subscription_t* subs,
                              int num_messages);

/**
 * Encode a message of type Trajectory into binary form.
 *
 * @param buf The output buffer.
 * @param offset Encoding starts at this byte offset into @p buf.
 * @param maxlen Maximum number of bytes to write.  This should generally
 *               be equal to Trajectory_encoded_size().
 * @param msg The message to encode.
 * @return The number of bytes encoded, or <0 if an error occured.
 */
int Trajectory_encode(void *buf, int offset, int maxlen, const Trajectory *p);

/**
 * Decode a message of type Trajectory from binary form.
 * When decoding messages containing strings or variable-length arrays, this
 * function may allocate memory.  When finished with the decoded message,
 * release allocated resources with Trajectory_decode_cleanup().
 *
 * @param buf The buffer containing the encoded message
 * @param offset The byte offset into @p buf where the encoded message starts.
 * @param maxlen The maximum number of bytes to read while decoding.
 * @param msg Output parameter where the decoded message is stored
 * @return The number of bytes decoded, or <0 if an error occured.
 */
int Trajectory_decode(const void *buf, int offset, int maxlen, Trajectory *msg);

/**
 * Release resources allocated by Trajectory_decode()
 * @return 0
 */
int Trajectory_decode_cleanup(Trajectory *p);

/**
 * Check how many bytes are required to encode a message of type Trajectory
 */
int Trajectory_encoded_size(const Trajectory *p);

// LCM support functions. Users should not call these
int64_t __Trajectory_get_hash(void);
uint64_t __Trajectory_hash_recursive(const __lcm_hash_ptr *p);
int __Trajectory_encode_array(void *buf, int offset, int maxlen, const Trajectory *p, int elements);
int __Trajectory_decode_array(const void *buf, int offset, int maxlen, Trajectory *p, int elements);
int __Trajectory_decode_array_cleanup(Trajectory *p, int elements);
int __Trajectory_encoded_array_size(const Trajectory *p, int elements);
int __Trajectory_clone_array(const Trajectory *p, Trajectory *q, int elements);

#ifdef __cplusplus
}
#endif

#endif
