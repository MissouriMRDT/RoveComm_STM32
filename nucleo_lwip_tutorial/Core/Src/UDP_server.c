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



void udpServer_init(void)
{
    struct udp_pcb *upcb;
    err_t err;
    upcb = udp_new();

    ip_addr_t myIPADDR;
    IP_ADDR4(&myIPADDR,198,162,0,10 );
    err = udp_bind(upcb, &myIPADDR, 11000);

    if(err == ERR_OK)
    {
        //udp_recv(upcb, udp_receive_callback, NULL);
    }
    else
    {
        udp_remove(upcb);
    }
}

err_t RC_Send_Blank(struct udp_pcb *pcb, ip_addr_t *send_IP, uint16_t data_id){
	//size of header
	size_t pack_bytes =sizeof(RC_header_t);
	//creation of the buffer being sent
	struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, (uint16_t)pack_bytes, PBUF_RAM);
	//creation of header
	RC_header_t hdr;
	hdr.version =RC_Version;
	hdr.Data_ID = htons(data_id);
	hdr.Count = htons(0);
	hdr.Data_type = htons(0);
	//adding the header into the buffer no payload for this send
	memcpy((uint8_t)p->payload, &hdr, pack_bytes);

	err_t err = udp_sendto(pcb, p, send_IP, RC_Port);
	pbuf_free(p);
	return err;
}
