
#ifndef UDP_server_H
#define UDP_server_H

#include <stdint.h>
#include <stddef.h>
#include "lwip/ip_addr.h"
#include "lwip/udp.h"
#define RC_maxPayload 65535
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

typedef struct {
	uint8_t  Data_type;
	uint16_t Count;
	union {
	uint8_t from_uint8[RC_maxPayload/sizeof(uint8_t)];
	int8_t from_int8[RC_maxPayload/sizeof(int8_t)];
	int16_t from_int16[RC_maxPayload/sizeof(int16_t)];
	uint16_t from_uint16[RC_maxPayload/sizeof(uint16_t)];
	int32_t from_int32[RC_maxPayload/sizeof(int32_t)];
	uint32_t from_uint32[RC_maxPayload/sizeof(uint32_t)];
	float from_float[RC_maxPayload/sizeof(float)];
	double from_double[RC_maxPayload/sizeof(double)];
	char from_char[RC_maxPayload/sizeof(char)];
	};

} RC_payload_t;

extern ip_addr_t substribers[14];

void udpServer_init(void);
err_t RC_Send_Blank(struct udp_pcb *pcb, const ip_addr_t *send_IP, uint16_t data_id);
void RC_receive_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port);
void add_subscriber(const ip_addr_t *addr);
void remove_subscriber(const ip_addr_t *addr);
void Send_subscriber(uint16_t data_id, uint16_t data_length, uint8_t data_size,uint8_t data_type, const void *data);

//for none
void RC_write_blank(uint16_t data_id);
// for single
void RC_write_u8(uint16_t data_id, uint8_t data);
void RC_write_8(uint16_t data_id, int8_t data);
void RC_write_16(uint16_t data_id, int16_t data);
void RC_write_u16(uint16_t data_id,  uint16_t data);
void RC_write_32(uint16_t data_id,  int32_t data);
void RC_write_u32(uint16_t data_id,  uint32_t data);
void RC_write_float(uint16_t data_id, float data);
void RC_write_double(uint16_t data_id, double data);
void RC_write_char(uint16_t data_id, char data);
//for multiple
void RC_write_u8_arr(uint16_t data_id, uint16_t data_length, uint8_t data[]);
void RC_write_8_arr(uint16_t data_id, uint16_t data_length, int8_t data[]);
void RC_write_16_arr(uint16_t data_id, uint16_t data_length, int16_t data[]);
void RC_write_u16_arr(uint16_t data_id, uint16_t data_length, uint16_t data[]);
void RC_write_32_arr(uint16_t data_id, uint16_t data_length, int32_t data[]);
void RC_write_u32_arr(uint16_t data_id, uint16_t data_length, uint32_t data[]);
void RC_write_float_arr(uint16_t data_id, uint16_t data_length, float data[]);
void RC_write_double_arr(uint16_t data_id, uint16_t data_length, double data[]);
void RC_write_char_arr(uint16_t data_id, uint16_t data_length, char data[]);

#endif
