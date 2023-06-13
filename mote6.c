#include "contiki.h"
#include "net/routing/routing.h"
#include "net/netstack.h"
#include "net/ipv6/simple-udp.h"
#include <stdint.h>
#include <inttypes.h>
#include <string.h>

#include "sys/log.h"
#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_INFO

#define UDP_CLIENT_PORT 8765
#define UDP_SERVER_PORT 5678

#define SEND_INTERVAL (60 * CLOCK_SECOND)

static struct simple_udp_connection udp_conn;


PROCESS(udp_server_process, "UDP server");
AUTOSTART_PROCESSES(&udp_server_process);

static void
udp_rx_callback(struct simple_udp_connection *c,
const uip_ipaddr_t *sender_addr,
uint16_t sender_port,
const uip_ipaddr_t *receiver_addr,
uint16_t receiver_port,
const uint8_t *data,
uint16_t datalen)
{
char *response_str;
uint16_t response_len;

if (strncmp((char *) data, "LIGHT6: TURN_ON", datalen) == 0) {
response_str = "LIGHT6: TURNED_ON";
response_len = strlen(response_str);
simple_udp_sendto(&udp_conn, response_str, response_len, sender_addr);
} else {
response_str = "WRONG REQ.";
response_len = strlen(response_str);
simple_udp_sendto(&udp_conn, response_str, response_len, sender_addr);
}
}


PROCESS_THREAD(udp_server_process, ev, data)
{
PROCESS_BEGIN();

NETSTACK_ROUTING.root_start();

simple_udp_register(&udp_conn, UDP_SERVER_PORT, NULL,
UDP_CLIENT_PORT, udp_rx_callback);

PROCESS_END();
}
