#include "contiki.h"
#include "net/routing/routing.h"
#include "random.h"
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


PROCESS(udp_client_process, "UDP client");
AUTOSTART_PROCESSES(&udp_client_process);


static void
udp_rx_callback(struct simple_udp_connection *c,
         const uip_ipaddr_t *sender_addr,
         uint16_t sender_port,
         const uip_ipaddr_t *receiver_addr,
         uint16_t receiver_port,
         const uint8_t *data,
         uint16_t datalen)
{


  if (strncmp((char *) data, "LIGHT6: TURNED_ON", datalen) == 0) {

    printf("LIGHT6 SUCCESSFULLY TURNED_ON\n");
  }
  else if (strncmp((char *) data, "WRONG REQ.", datalen) == 0) {

   printf("LIGHT6 PROCESS FAILED\n");
  }
}


PROCESS_THREAD(udp_client_process, ev, data)

{
static struct etimer periodic_timer;
static char str[32];
uip_ipaddr_t dest_ipaddr;
static uint32_t tx_count;


PROCESS_BEGIN();


simple_udp_register(&udp_conn, UDP_CLIENT_PORT, NULL,
UDP_SERVER_PORT, udp_rx_callback);


etimer_set(&periodic_timer, random_rand() % SEND_INTERVAL);
while(1) {
PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));


if(NETSTACK_ROUTING.node_is_reachable() &&
   NETSTACK_ROUTING.get_root_ipaddr(&dest_ipaddr)) {

  if(tx_count%5!=0){
  snprintf(str, sizeof(str), "LIGHT6: TURN_ON");
  simple_udp_sendto(&udp_conn, str, strlen(str), &dest_ipaddr);
  tx_count++;
  }else{
	  snprintf(str, sizeof(str), "ANY_OTHER_MESSAGES");
	  simple_udp_sendto(&udp_conn, str, strlen(str), &dest_ipaddr);
	  tx_count++;
  }
}

etimer_set(&periodic_timer, SEND_INTERVAL
            - CLOCK_SECOND + (random_rand() % (2 * CLOCK_SECOND)));

}

PROCESS_END();
}