#include "lwip/netif.h"
/*Static IP ADDRESS: IP_ADDR0.IP_ADDR1.IP_ADDR2.IP_ADDR3 */
#define IP_ADDR0 ((uint8_t) 192U)
#define IP_ADDR1 ((uint8_t) 168U)
#define IP_ADDR2 ((uint8_t) 2U)
#define IP_ADDR3 ((uint8_t) 110U)
/*NETMASK*/
#define NETMASK_ADDR0 ((uint8_t) 255U)
#define NETMASK_ADDR1 ((uint8_t) 255U)
#define NETMASK_ADDR2 ((uint8_t) 255U)
#define NETMASK_ADDR3 ((uint8_t) 0U)
/*Gateway Address*/
#define GW_ADDR0 ((uint8_t) 192U)
#define GW_ADDR1 ((uint8_t) 168U)
#define GW_ADDR2 ((uint8_t) 0U)
#define GW_ADDR3 ((uint8_t) 1U)
void ethernet_link_status_updated(struct netif *netif);
void Ethernet_Link_Periodic_Handle(struct netif *netif);
void udp_led_server_init(void);
#if LWIP_DHCP
void DHCP_Process(struct netif *netif);
void DHCP_Periodic_Handle(struct netif *netif);
#endif
