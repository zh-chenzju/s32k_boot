/*
 * bsp_can.h
 *
 *  Created on: 2023年8月23日
 *      Author: 姚山建
 */

#ifndef BSP_CAN_H_
#define BSP_CAN_H_

#define CAN1_ID 0x180u
//#define CAN2_ID 0x280u
//#define CAN3_ID 0x380u
//#define CAN4_ID 0x480u
//#define CAN5_ID 0x580u
//#define CAN6_ID 0x680u

#define RX_MB_IDX 10U
#define RX_1_MB_IDX 11U
#define TX_MB_IDX 12U

extern void CAN0_ORED_0_31_MB_IRQHandler(void);
//extern void CAN1_ORED_0_31_MB_IRQHandler(void);
//extern void CAN2_ORED_0_31_MB_IRQHandler(void);
//extern void CAN3_ORED_0_31_MB_IRQHandler(void);
//extern void CAN4_ORED_0_31_MB_IRQHandler(void);
//extern void CAN5_ORED_0_31_MB_IRQHandler(void);

extern void can_set_mode(void);
extern void setupCan( void );
extern void main_can_init(void);
extern void can_senddata(void);
void can_isr_set(void);
#endif /* BSP_CAN_H_ */
