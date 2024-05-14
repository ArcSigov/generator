/*----------------------------------------------------------------------
»м€................ke_errors.h
Ќазначение.........коды ошибок €дра 
-----------------------------------------------------------------------*/
#ifndef __ERRORS_H_INCLUDED__
#define __ERRORS_H_INCLUDED__

#ifndef __ASSEMBLER__

#define ErrIdToErrMask( err_id) (1 << ((err_id)-1))

/*-----------------------------------------------------------------------*/
/*
	коды ошибок, поддерживаемые €дром
	
	типы ошибок при вызовах микро€дра
		KE_ERRID_NO_ERROR       - код, соответсвующий отсутствию ошибок
	типы ошибок, соответствующие исключени€м
		KE_ERRID_MEM_RD_ACCESS  = { TLBL, ADEL }
		KE_ERRID_MEM_WR_ACCESS  = { TLB MOD, TLBS, ADES }
		KE_ERRID_IBUS_ERROR     = { IBE }
		KE_ERRID_DBUS_ERROR     = { DBE }
		KE_ERRID_SYSCALL        = { SYSCALL }	
		KE_ERRID_BREAKPOINT     = { BP }
		KE_ERRID_RESERVED_INSTR = { RI }
		KE_ERRID_COPUNUSABLE    = { CPU }
		KE_ERRID_OVERFLOW       = { OVF }
		KE_ERRID_TRAP           = { TRAP }
		KE_ERRID_RESERVED       = { Reserved }
		KE_ERRID_FPE            = { FPU Exception }
*/
typedef enum 
{ 
	KE_ERRID_NO_ERROR = 0,

	/* error ids that are used for rallbacks */
	KE_ERRID_MEM_RD_ACCESS = 0x1, /* 01 */
	KE_ERRID_MEM_WR_ACCESS,       /* 02 */
	KE_ERRID_IBUS_ERROR,          /* 03 */
	KE_ERRID_DBUS_ERROR,          /* 04 */
	KE_ERRID_SYSCALL,             /* 05 */
	KE_ERRID_BREAKPOINT,          /* 06 */
	KE_ERRID_RESERVED_INSTR,      /* 07 */
	KE_ERRID_COPUNUSABLE,         /* 08 */
	KE_ERRID_OVERFLOW,            /* 09 */
	KE_ERRID_TRAP,                /* 0A */
	KE_ERRID_FPE,                 /* 0B */

	KE_ERRID_INVALID_SERVICE,     /* 0C */
	KE_ERRID_INVALID_ARG,         /* 0D */

	/* other errors  */
	KE_ERRID_CACHE_ERR,           /* 0E */
	KE_ERRID_MEMORY_SHORTAGE,     /* 0F */
	KE_ERRID_RESOURCE_SHORTAGE,   /* 10 */
	KE_ERRID_CFG_ERROR,           /* 11 */
	KE_ERRID_INIT_ERROR,          /* 12 */

	KE_ERRID_APPLICATION_ERROR,   /* 13 */
	KE_ERRID_APP_DEADLINE_MISSED, /* 14 */
	KE_ERRID_ERR_MSG_OVERFLOW,    /* 15 */
	KE_ERRID_INTERNAL_ERROR,      /* 16 */
	KE_ERRID_UNKNOWN_ERROR,       /* 17 */
	KE_ERRID_TIME_OVF,            /* 18 */
	KE_ERRID_LOADER_ERROR,        /* 19 */
	KE_ERRID_CHECKSUM_ERROR,      /* 1A */
	KE_ERRID_RESERVED_3,          /* 1B */

	KE_ERRID_COUNT,               /* 1C */
} ke_error_id_enum_t;

#endif /* __ASSEMBLER__ */

#endif /* __ERRORS_H_INCLUDED__ */
