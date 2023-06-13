#include "contiki.h"
#include "net/routing/rpl-classic/rpl.h"
#include "net/ipv6/uip.h"
#include "net/ipv6/uip-ds6.h"
#include "net/ipv6/uip-udp-packet.h"
#include "dev/leds.h"

#define PORT 3001

static struct uip_udp_conn *client_conn;

static uip_ipaddr_t sixth_node_ipaddr;
static uip_ipaddr_t first_node_ipaddr;


PROCESS( ara_dugum_process, "UDP server");
AUTOSTART_PROCESSES(&ara_dugum_process);

void send_to_sixth_node(char *msg) {

  uip_udp_packet_sendto(client_conn, msg, strlen(msg),
                        &sixth_node_ipaddr, UIP_HTONS(PORT));
}

void send_to_first_node(char *msg) {


  uip_udp_packet_sendto(client_conn, msg, strlen(msg),
                        &first_node_ipaddr, UIP_HTONS(PORT));
}

PROCESS_THREAD( ara_dugum_process, ev, data )
{
  PROCESS_BEGIN();


  client_conn = udp_new(NULL, UIP_HTONS(0), NULL);
  udp_bind(client_conn, UIP_HTONS(PORT));
  uip_ip6addr(&first_node_ipaddr, 0xfe80, 0, 0, 0, 0x212, 0x7401, 0x1, 0x101);
  uip_ip6addr(&sixth_node_ipaddr, 0xfe80, 0, 0, 0, 0x212, 0x7406, 0x6, 0x606);

  while(1) {
    PROCESS_YIELD();

    if(ev == tcpip_event) {

      char *msg = (char *)uip_appdata;


		if(uip_ipaddr_cmp(&UIP_IP_BUF->srcipaddr, &sixth_node_ipaddr)) {
		send_to_first_node(msg);
		}else {
		send_to_sixth_node(msg);
		}
    }
  }

  PROCESS_END();
}
