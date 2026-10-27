#include "lwip/udp.h"
#include "lwip/pbuf.h"
#include "stdio.h"
#include "lwip/api.h"
#include "lwip/sys.h"
#include "lwip/ip_addr.h"
#include "lwip/init.h"
#include "lwip/def.h"
#include <string.h>
#include "UDP_server.h"
#include "main.h"



ip_addr_t substribers[14];
ip_addr_t Zero_IP;


void udpServer_init(void)
{

    struct udp_pcb *upcb;
    err_t err;
    upcb = udp_new();

    ip_addr_t myIPADDR;
    IP_ADDR4(&myIPADDR,192,168,2,110);
    IP_ADDR4(&Zero_IP,0,0,0,0);
    err = udp_bind(upcb, &myIPADDR, 11000);

    if(err == ERR_OK)
    {
        udp_recv(upcb, RC_receive_callback, NULL);
    }
    else
    {
        udp_remove(upcb);
    }
}

err_t RC_Send_Blank(struct udp_pcb *pcb, const ip_addr_t *send_IP, uint16_t data_id){
	//size of header
	size_t pack_bytes =sizeof(RC_header_t);
	//creation of the buffer being sent
	struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, (uint16_t)pack_bytes, PBUF_RAM);
	//creation of header
	RC_header_t hdr;
	hdr.version =0x19;
	hdr.Data_ID = htons(data_id);
	hdr.Count = htons(0);
	hdr.Data_type = 0;
	//adding the header into the buffer no payload for this send
	memcpy((uint8_t *)p->payload, &hdr, pack_bytes);

	err_t err = udp_sendto(pcb, p, send_IP, RC_Port);
	pbuf_free(p);
	return err;
}

void RC_receive_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port){

	RC_header_t hdr;
	RC_header_t hdr_raw;

	HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, 1);


	pbuf_copy_partial(p, &hdr_raw, sizeof(RC_header_t),0);

	hdr.version =hdr_raw.version;
	hdr.Data_ID = ntohs(hdr_raw.Data_ID);
	hdr.Count = ntohs(hdr_raw.Count);
	hdr.Data_type = hdr_raw.Data_type;




		// rovecomm standard commands
	switch(hdr.Data_ID){
	case 1:
		RC_Send_Blank(upcb, addr,2);
	case 3:
		//subscribe IP
		add_subscriber(addr);
	case 4:
		//un subscribe IP
		remove_subscriber(addr);

	}



}

void add_subscriber(const ip_addr_t *addr){
	//check for duplicate
	for (int i =0; i<maxSubscriber; i++){
		if (ip_addr_cmp(&substribers[i], addr)){
			return;
		}
	}

	//find open spot
	for (int i=0; i<maxSubscriber; i++){
		if(ip_addr_cmp(&substribers[i], &Zero_IP)){
			ip_addr_copy(substribers[i], *addr);
			return;
		}
	}


}
void remove_subscriber(const ip_addr_t *addr){
	//temp
	for (int i =0; i<maxSubscriber; i++){
			if (ip_addr_cmp(&substribers[i], addr)){
				ip_addr_copy(substribers[i], Zero_IP);
			}
		}


}
