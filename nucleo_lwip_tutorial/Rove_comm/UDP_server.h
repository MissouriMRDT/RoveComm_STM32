
#ifndef UDP_server_H
#define UDP_server_H

#include <stdint.h>
#include <stddef.h>
#include "lwip/ip_addr.h"
#include "lwip/udp.h"
#define RC_Version 0x01
#define RC_Port 11000
#define maxSubscriber 14


/*typedef struct {
	uint8_t version;
	uint16_t Data_ID;
	uint16_t Count;
	uint8_t Data_type;

} RC_header_t;*/

#pragma pack(push, 1)
typedef struct {
    uint8_t  version;
    uint16_t Data_ID;
    uint16_t Count;
    uint8_t  Data_type;
} RC_header_t;
#pragma pack(pop)

extern ip_addr_t substribers[14];

void udpServer_init(void);
err_t RC_Send_Blank(struct udp_pcb *pcb, const ip_addr_t *send_IP, uint16_t data_id);
void RC_receive_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port);
void add_subscriber(const ip_addr_t *addr);
void remove_subscriber(const ip_addr_t *addr);
#endif
