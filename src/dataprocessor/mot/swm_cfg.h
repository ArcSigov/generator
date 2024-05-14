/*----------------------------------------------------------------------
Name............swm.h
Purpose.........SpaceWire configuration data
Comment.........
-----------------------------------------------------------------------*/

#ifndef __SPACEWIRE_CONFIG_INCLUDED__
#define __SPACEWIRE_CONFIG_INCLUDED__

/* константа для тэга конфигурации */
#define SWM_CFG_INFO_TAG_NAME    "SWM_CFG_INFO"

/*-----------------------------------------------------------------------------
    resource set configuration structure definition 
-----------------------------------------------------------------------------*/
typedef struct 
{
	uint32_t		flags;								/* зарезервировано */
	uint16_t		apex_port_id_ones_own;				/* Идентификатор APEX порта в данном модуле */
	uint8_t			addr_modul_ones_own;				/* Логический адрес в коммутаторе для данного модуля */
	uint8_t			protokol_info;						/* Идентификатор протокола, значение типа swm_protokol_id_t */
	uint16_t		apex_port_id_other;					/* Идентификатор APEX порта, с которым идет обмен */
	uint8_t			addr_modul_other;					/* Логический адрес модуля, с которым идет обмен */
	uint8_t			sw_cycle;							/* Частота обмена, значение типа swm_frequency_t, для порта-отправителя должно быть 0 */
	uint16_t		apex_port_id_answer;				/* Идентификатор APEX порта в данном модуле, по которому следует передать ответ, указывается при необходимости */
	uint16_t		sw_info;
} swm_conf_port_info_t;

typedef enum 
{
	SWM_PROT_SAMPLING = 1,   /* Identifier of sampling ports protocol */
	SWM_PROT_QUEUING = 2     /* Identifier of queuing ports protocol */
} swm_protokol_id_t;

typedef enum 
{
	SWM_CYCLE_NO = 0,              /* f = 0 */
	SWM_CYCLE_SEND_50_hertz = 1,   /* f = 50 */
	SWM_CYCLE_SEND_25_hertz = 2,   /* f = 25 */
	SWM_CYCLE_SEND_12_5_hertz = 3  /* f = 12,5 */
} swm_frequency_t;

/*-------------------------------------------------------*/
#define INIT_SWM_PORT_INFO(port_id_1, addr_1, prot, port_id_2, addr_2, port_id_answer, port_cycle)  \
    {																								\
		/*flags;*/						1,															\
		/*apex_port_id_ones_own;*/		port_id_1,													\
		/*addr_modul_ones_own;*/		addr_1,														\
		/*protokol_info;*/				prot,														\
		/*apex_port_id_other;*/			port_id_2,													\
		/*addr_modul_other;*/			addr_2,														\
		/*sw_cycle;*/					port_cycle,													\
		/*apex_port_id_answer;*/		port_id_answer,												\
		/*sw_info;*/					0															\
    }               

#endif /** __SPACEWIRE_CONFIG_INCLUDED__ */
