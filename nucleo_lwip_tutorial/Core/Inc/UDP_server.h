
#ifndef UDP_server_H
#define UDP_server_H

#include <stdint.h>
#include <stddef.h>
#include "lwip/ip_addr.h"
#include "lwip/udp.h"
#define RC_Version 0x03
#define RC_Port 11000

typedef struct {
	uint8_t version;
	uint16_t Data_ID;
	uint16_t Count;
	uint8_t Data_type;

} RC_header_t;

void udpServer_init(void);
err_t RC_Send_Blank(struct udp_pcb *pcb, ip_addr_t *send_IP, uint16_t data_id);
#endif
