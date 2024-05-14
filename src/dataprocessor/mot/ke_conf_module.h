/*----------------------------------------------------------------------
���................ke_conf_module2.h
����������.........���������� ������ ������������ �������
-----------------------------------------------------------------------*/

#ifndef __KE_CONF_MODULE2_H_INCLUDED__
#define __KE_CONF_MODULE2_H_INCLUDED__

#ifndef __ASSEMBLER__

/* ��������� ��� ����� ������������ ������ */
#define MEMREGIONS_CFG_INFO_TAG_NAME    "MREGIONS_CFG_INFO"
#define MEMMAPPINGS_CFG_INFO_TAG_NAME   "MMAPPINGS_CFG_INFO"
#define SPORTS_CFG_INFO_TAG_NAME        "SPORTS_CFG_INFO"
#define QPORTS_CFG_INFO_TAG_NAME        "QPORTS_CFG_INFO"
#define RESOURCE_SETS_CFG_INFO_TAG_NAME "RSETS_CFG_INFO"
#define SNODES_CFG_INFO_TAG_NAME        "SNODES_CFG_INFO"
#define QNODES_CFG_INFO_TAG_NAME        "QNODES_CFG_INFO"
#define PARTITIONS_CFG_INFO_TAG_NAME    "PARTITIONS_CFG_INFO"
#define PART_HM_TBLS_CFG_INFO_TAG_NAME  "PHMTBLS_CFG_INFO"
#define PWINDOWS_CFG_INFO_TAG_NAME      "WINDOWS_CFG_INFO"
#define STASKS_CFG_INFO_TAG_NAME        "STASKS_CFG_INFO"
#define MODULE_CFG_INFO_TAG_NAME        "MODULE_CFG_INFO"

enum {
  KE_CONF_NAME_LEN = 32,
  KE_CONF_APEX_NAME_LEN = 30
};

/*---------------------------------------------------------------------------------------*/
/*
  ��������� ������� ���������� ������ ������.
    ��������� ��������� ������� ���������� ������, ��������� ��� �������������.

  ���� ���������:
    flags    - �����, ������������ ��� ������� ������
    paddr    - ��������� ���������� ����� ����������� ������� ������.
    saddr    - ��������� ���������� ����� ������, ���������� � ����������� ������� ������.
    size     - ������ ����������� ������� ������.
*/
typedef struct {
  uint32_t          flags;
  uint32_t          size;
  uint32_t          paddr;
  uint32_t          saddr;
} ke_conf_mregion_t;

/*
  ��������� �������� ������ ������� ���������� ������.
    SYSTEM      - ������� �������������� ��
    PRIVATE     - ��� �������: ����� ����������. ����� ��������, ���� ������ ���� SYSTEM.
    COMMON      - ��� �������: ����������� �����������. ����� ��������, ���� ������ ���� SYSTEM.
    KERNEL      - ����� �������������� ��� ������ ����. ����� ��������, ���� ������ ���� SYSTEM.
    ALLOCATE    - ���������� �������� ���������� ������ ��� ������� (paddr �� ������������),
                  ����� (RESERVE) ���������� ������ ��� ������� ��������������� � ������ paddr
    PAGED       - ������� ������ ���� �������� ��� ����� ���������� �������, ����� ����������
                  ������� ����� ���� �� ����������� �� ������� �������� � ������ �� ����� ����
                  �� ������ ������� ��������.	����� ��������, ���� ������ ���� ALLOCATE.
    COPY        - ���������� ������ �� [saddr; saddr+size[ � ���������� ������� ������
                  (ALLOCATE=1) ��� ����������������� ������� [paddr; paddr+size[ (ALLOCATE=0)
    ZERO        - �������� ���������� ������� ������ (ALLOCATE=1) ��� �����������������
                  ������� [paddr; paddr+size[ (ALLOCATE=0)
*/
typedef enum {
  KE_CONF_MREG_FLAGS_SYSTEM = 0x1,
  KE_CONF_MREG_FLAGS_PRIVATE = 0,
  KE_CONF_MREG_FLAGS_COMMON = 0x2,
  KE_CONF_MREG_FLAGS_KERNEL = 0x4,
  KE_CONF_MREG_FLAGS_ALLOCATE = 0x10,
  KE_CONF_MREG_FLAGS_PAGED = 0x20,
  KE_CONF_MREG_FLAGS_COPY = 0x40,
  KE_CONF_MREG_FLAGS_ZERO = 0x80,
} ke_conf_mreg_flags_t;


/*---------------------------------------------------------------------------------------*/
/*
  ��������� ����������� ������� ����������� ������.
    ��������� �������� ���������� � ����������� ������� ����������� ������ [vaddr; vaddr+size].
    ������� ���������� � ��� �������, � �������� ��������� ��������.

  ���� ���������:
    vaddr    -  ��������� ����������� ����� ���������� �������.
    vsize    -  ������ ���������� �������.
    mreg_id  -  ������ ������� ������ � ������� ���������� �������� ���������� ������ ������.
    attr     -  �������� ���������� ������� (��. ke_conf_mmap_attr_t).
    roffset  -  �������� ������ ���������� ������� ������.

  ������ �� ������, ����������� ������� ������:
    ������ ���������� �������� ���������� ������ ������ (�������� ���� ke_conf_mregion_t) 
*/
typedef struct {
  uint32_t      vaddr;
  uint32_t      vsize;
  uint32_t      roffset;
  uint16_t      attr;
	uint16_t      mreg_id;
} ke_conf_mmapping_t;

/*
  ��� �����������
    READ                     - ���������� ������� �������� ��� ������
    WRITE                    - ���������� ������� �������� ��� ������
    GLOBAL                   - ���������� ������� �������� ����������
    UNCACHED                 - ���������� ������� �� �������� ����������
    CACHED                   - ���������� ������� �������� ����������
    CACHED_WR_BACK           - Cachable, Write Back 
    CACHED_WR_THROUGH        - Cachable, Write Through, Not Write Allocate
    CACHED_WR_THROUGH_ALLOC  - Cachable, Write Through, Write Allocate
    CACHED_DEFAULT           - ������������ ��� �����������, �������� �� ���������
*/
typedef enum {
  KE_CONF_MMAP_ATTR_READ                    = 0x1,
  KE_CONF_MMAP_ATTR_WRITE                   = 0x2,
  KE_CONF_MMAP_ATTR_GLOBAL                  = 0x4,
  KE_CONF_MMAP_ATTR_UNCACHED                = 0x0,
  KE_CONF_MMAP_ATTR_CACHED                  = 0xF0,
  KE_CONF_MMAP_ATTR_CACHED_WR_BACK          = 0x10,
  KE_CONF_MMAP_ATTR_CACHED_WR_THROUGH       = 0x20,
  KE_CONF_MMAP_ATTR_CACHED_WR_THROUGH_ALLOC = 0x30,
  KE_CONF_MMAP_ATTR_CACHED_DEFAULT          = 0x80,
  KE_CONF_MMAP_ATTR_RW                      = KE_CONF_MMAP_ATTR_READ | KE_CONF_MMAP_ATTR_WRITE,
  KE_CONF_MMAP_ATTR_RWG                     = KE_CONF_MMAP_ATTR_READ | KE_CONF_MMAP_ATTR_WRITE | KE_CONF_MMAP_ATTR_GLOBAL,
} ke_conf_mmap_attr_t;

/*---------------------------------------------------------------------------------------*/
/*
  ��������� ����� ��� �������.
    ��������� �������� ���������� � ������������ ����� ��� �������.

  ���� ���������:
    flags         - �����
    max_msg_size  - ������������ ������ ��������� (� ������)
    refresh_time  - ����� ����������
    snode_id      - ����� ������� snode, � ������� ������ ���� � ������� ���������� ����� ���������� ������ ��� ������� ������.
    name_off      - �������� ����� ����� �� ������ ������ ��������� ������ ��������� 

  ������ �� ������, ����������� ������� ������:
    ������ ���������� ����� ���������� ������ ��� ������� ������ (�������� ���� ke_conf_snode_t)
*/
typedef struct {
  uint32_t      refresh_time_lo;
  uint32_t      refresh_time_hi;
  uint16_t      max_msg_size;
  uint16_t      flags;
  uint16_t      name_off;
  uint16_t      snode_id;
} ke_conf_sport_t;

/*
  �����, ������������ � ���� flags ��������� ke_conf_sport_t
*/
typedef enum {
  KE_CONF_SPORT_FLAGS_DIRECTION    = 0x1,
  KE_CONF_SPORT_FLAGS_SND          = 0x1,
  KE_CONF_SPORT_FLAGS_EVENT        = 0x2,
  KE_CONF_SPORT_FLAGS_CONNECTED    = 0x4,
  KE_CONF_SPORT_FLAGS_CREATE_EMPTY = 0x8,
} ke_conf_sport_flags_t;

/*---------------------------------------------------------------------------------------*/
/*
  ��������� ����� � ��������.
    ��������� �������� ���������� � ������������ ����� � ��������.

  ���� ���������:
    flags         - �����
    max_msg_size  - ������������ ������ ��������� (� ������)
    max_msg_count - ������������ ���������� ���������
    qnode_id      - ����� ������� qnode, � ������� ������ ���� � ������� ���������� ����� ���������� ������ � �������� ������.
    name_off      - �������� ����� ����� �� ������ ������ ��������� ������ ���������

  ������ �� ������, ����������� ������� ������:
    ������ ���������� ����� ���������� ������ � �������� ������ (�������� ���� ke_conf_qnode_t)
*/
typedef struct {
  uint16_t      flags;
  uint16_t      max_msg_size;
  uint16_t      max_msg_count;
  uint16_t      name_off;  
  uint16_t      qnode_id;
  uint16_t      dummy;
} ke_conf_qport_t;

/*
  �����, ������������ � ���� flags ��������� ke_conf_qport_t
*/
typedef enum {
  KE_CONF_QPORT_FLAGS_SND              = 0x1,
  KE_CONF_QPORT_FLAGS_EVENT            = 0x2,
  KE_CONF_QPORT_FLAGS_QDISCIPLINE_PRIO = 0x4,
  KE_CONF_QPORT_FLAGS_BUF_SEPARATE     = 0x8,
  KE_CONF_QPORT_FLAGS_CONNECTED        = 0x10,
  KE_CONF_QPORT_FLAGS_NULL             = 0x20,
  KE_CONF_QPORT_FLAGS_CREATE_EMPTY     = 0x40,
} ke_conf_qport_flags_t;


/*----------------------------------------------------------------------------------------------*/
/*
  ��������� ������ ��������
    �������� ���������� � ������ ��������

  ���� ���������:
    flags                 - �����
    mmapping_index        - ������ ������� ��������� ������� �����������, ������������ � ������� ������ ��������, � ������� ���������� �������� ����������� ������
    mmapping_count        - ���������� �������� �����������, ������������ � ������� ������ ��������,
    sport_index           - ������ ������� ��������� ����� ��� �������, ������������ � ������� ������ ��������
    sport_count           - ���������� ���������� ������ ��� �������, ������������ � ������� ������ ��������
    qport_index           - ������ ������� ��������� ����� � ��������, ������������ � ������� ������ ��������
    qport_count           - ���������� ���������� ������ � ��������, ������������ � ������� ������ ��������

  ������ �� ������, ����������� ������� ������:
    ������ ���������� �������� ����������� ������ (�������� ���� ke_conf_mmapping_t)
    ������ ���������� ������ ��� ������� ������ (�������� ���� ke_conf_sport_t)
    ������ ���������� ������ � �������� ������ (�������� ���� ke_conf_qport_t)
*/
typedef struct {
  uint8_t      flags;
  uint8_t      mmapping_count;
  uint16_t     mmapping_index;
  uint16_t     sport_index;
  uint16_t     sport_count;
  uint16_t     qport_index;
  uint16_t     qport_count;
}  ke_conf_rset_t;

/*
  �����, ������������ � ���� flags ��������� ke_conf_rset_header_t
    GLOBAL             - ���������� ����� ��������, ������������ � ��� ����� ����������� �������� ����������
    SYSTEM             - ����� �������� ��������� ������, ������������ � ��� ����� ��� ������� ������� �������� �������
    CFG_DATA_SIZE_MASK - ����� ���-�� 32-��������� ���� ���������������� ������ ��� ������� ����� � ������ ��������
*/
typedef enum
{
  KE_CONF_RSFLAGS_GLOBAL_MAPPING = 0x1,
  KE_CONF_RSFLAGS_SYSTEM = 0x2,
  KE_CONF_RSFLAGS_APP = 0x4,
  KE_CONF_RSFLAGS_CFG_DATA_SIZE_MASK = 0x30,
  KE_CONF_RSFLAGS_CFG_DATA_SIZE_SHIFT = 4,
} ke_conf_rset_flags_t;


/*---------------------------------------------------------------------------------------*/
/*
  ��������� ���� ���������� ����� ��� �������
    �������� ���������� � ������������ ������ sampling channel

  ���� ���������:
    max_msg_size	- ������������ ������ ��������� (� ������)
    flags					- ����� 
    rm_region_id  - ������ ������� ������, ������������� ��� ������ ������, � ������� ���������� �������� ���������� ������ ������.

  ������ �� ������, ����������� ������� ������:
    ������ ���������� �������� ���������� ������ ������ (�������� ���� ke_conf_mregion_t)
*/
typedef struct {
  uint16_t      max_msg_size;
  uint8_t       flags;
  uint8_t       rm_region_id;
} ke_conf_snode_t;

/*
  ����� ����������
    KE_CONF_SNODE_FLAGS_ALLOCATE_MEM - ������ ��� ������ ������ ���������� ��
    KE_CONF_SNODE_FLAGS_RESERVED_MEM - ������ ��� ������ ������ ����������� �������� ������
    KE_CONF_SNODE_FLAGS_ALIGN64      - ������ ��� ������ ������ ������ ���� ��������� �� ������� 64� ���������� �����
*/
typedef enum {
  KE_CONF_SNODE_FLAGS_ALLOCATE_MEM    = 0x0,
  KE_CONF_SNODE_FLAGS_RESERVED_MEM    = 0x1,
  KE_CONF_SNODE_FLAGS_ALIGN32         = 0x2,
  KE_CONF_SNODE_FLAGS_ALIGN64         = 0x4,
  KE_CONF_SNODE_FLAGS_EXCESS          = 0x8,
} ke_conf_snode_flags_t;

/*---------------------------------------------------------------------------------------*/
/*
  ��������� ���� ���������� ����� � ��������
    �������� ���������� � ������������ ������ queuing channel
  
  ���� ���������:
    max_msg_size	- ������������ ������ ��������� (� ������)
    flags					- ����� 
    rm_region_id  - ������ ������� � ������� rm_regions ������, ������������ ������ ��� ������ 
    rm_region_id  - ������ ������� ������, ������������� ��� ������ ������, � ������� ���������� �������� ���������� ������ ������.

  ������ �� ������, ����������� ������� ������:
    ������ ���������� �������� ���������� ������ ������ (�������� ���� ke_conf_mregion_t)
    */
typedef struct {
  uint16_t      max_msg_size;
  uint8_t       flags;
  uint8_t       rm_region_id;
} ke_conf_qnode_t;

/*
  ����� ����������
		KE_CONF_QNODE_FLAGS_ALLOCATE_MEM - ������ ��� ������ ������ ���������� ��
		KE_CONF_QNODE_FLAGS_RESERVED_MEM - ������ ��� ������ ������ ����������� �������� ������
		KE_CONF_QNODE_FLAGS_ALIGN64      - ������ ��� ������ ������ ������ ���� ��������� �� ������� 64� ���������� �����
*/
typedef enum {
  KE_CONF_QNODE_FLAGS_ALLOCATE_MEM    = 0x0,
  KE_CONF_QNODE_FLAGS_RESERVED_MEM    = 0x1,
  KE_CONF_QNODE_FLAGS_ALIGN32         = 0x2,
  KE_CONF_QNODE_FLAGS_ALIGN64         = 0x4,
  KE_CONF_QNODE_FLAGS_EXCESS          = 0x8,
} ke_conf_qnode_flags_t;


/*---------------------------------------------------------------------------------------*/
/*
  ��������� �������
    �������� ���������� � ������������ �������

  ���� ���������:
    partition_id           - ������������� �������
    flags                  - �����  �������
    rset_id                - ������������� ������ �������� ������� - ������ � ������� ���������� ������� �������� ������
    hm_table_id            - ������ � ������� ������ �������� ��������� ������

    period                 - ������ ������� �� ��������� ��������� (���-�� ������ � APEX)
    duration               - ������������ ������� �� ��������� ��������� (���-�� ������ � APEX)

    phys_mem_size          - ����� ������ ���������� ������, ���������� ������� (��� app � sysm)
                             ���� �� ������ ������� ����� sysm, ���������� ������ ���������,
                             ���������� � ��� ������� � ���������� ������, ������������ ��� ��� ����� ������

    name_off                - �������� ����� ������� �� ������ ������ ��������� ������ ���������
    app_filename_off        - �������� ����� ����� ���������� �� ������ ������ ��������� ������ ���������

    app_stacks_vaddr        - ����� ������� ������������ ��������� ������������ ����������, ������� ������������ ��� ����������� ������ ��������� ����������
    app_stacks_vsize        - ������ ������� ������������ ��������� ������������ ����������, ������� ������������ ��� ����������� ������ ��������� ����������
    apex_init_addr          - ����������� ����� ���� (�������) �������� ������������� ����������
    apex_init_stack_size    - ������ ����� �������� ������������� ���������� � ������

    apex_err_msg_count      - ���������� ��������� � ������� ��������� ��������-����������� ������
    apex_process_count      - ������������ ���������� ���������, ������������ �����������, 
                              ������� ������� ������������� � �������-���������� ������
    apex_event_count        - ������������ ���������� �������� ���� EVENT, ������������ �����������, 
    apex_sem_count          - ������������ ���������� �������� ���� SEMAPHORE, ������������ �����������, 
    apex_buf_count          - ������������ ���������� �������� ���� BUFFER, ������������ �����������, 
    apex_bboard_count       - ������������ ���������� �������� ���� BLACKBOARD, ������������ �����������, 

  ������ �� ������, ����������� ������� ������:
    ������ ���������� ������� �������� ������ (�������� ���� ke_conf_rset_t)
    ������ ������ �������� ��������� ������ (�������� ���� ke_conf_rset_t)
*/
typedef struct {
  uint8_t       partition_id;
  uint8_t       flags;
  uint8_t       rset_id;
  uint8_t       hm_table_id;

  uint32_t      period_lo;
  uint32_t      period_hi;
  uint32_t      duration_lo;
  uint32_t      duration_hi;

  uint32_t      phys_mem_size;

  uint16_t      name_off;
  uint16_t      app_file_name_off;

  uint32_t      app_stacks_vaddr;
  uint32_t      app_stacks_vsize;
  uint32_t      apex_init_addr;
  uint32_t      apex_init_stack_size;

  uint8_t       apex_err_msg_count;
  uint8_t       dummy3;
  uint16_t      apex_process_count;
  uint16_t      apex_event_count;
  uint16_t      apex_sem_count;

  uint16_t      apex_buf_count;
  uint16_t      apex_bboard_count;
} ke_conf_partition_t;

/*
  �����, ������������ � ���� flags ��������� ke_conf_partion_t
    FAKE             - ������ �������� ���������, �.�. ������ ��������� � ��������� IDLE
    APP_CODE_CACHED  - ��� ������� ���������� � ��������� �����������
    APP_STACK_CACHED - ����� ��������� ������� ���������� � ��������� �����������
    APP_DATA_CACHED  - ������ ������� ���������� � ��������� �����������
*/
typedef enum 
{ 
  KE_CONF_PFLAGS_FAKE              = 0x1,
  KE_CONF_PFLAGS_APP_CODE_CACHED   = 0x2,
  KE_CONF_PFLAGS_APP_STACK_CACHED  = 0x4,
  KE_CONF_PFLAGS_APP_DATA_CACHED   = 0x8
} ke_conf_partition_flags_t;



/*---------------------------------------------------------------------------------------*/
/*
  ������� �������� ��������� �������.
  ��������� ������ �������� �������� ������ ����� ������� �� ������. ��� ������ ���������� ������ � �������.
  uint8_t      hm_table[KE_ERRID_COUNT];
*/

/*
  ���� ������� �� ������
*/
typedef enum 
{ 
  KE_CONF_ERR_ACTION_IGNORE   = 0x0,
  KE_CONF_ERR_ACTION_IDLE     = 0x1,
  KE_CONF_ERR_ACTION_CSTART   = 0x2,
  KE_CONF_ERR_ACTION_WSTART   = 0x3,
  KE_CONF_ERR_ACTION_RESTART  = 0x2,
  KE_CONF_ERR_ACTION_SHUTDOWN = 0x3,
} ke_conf_err_actions_t;


/*-------------------------------------------------------*/
/*
  ��������� ���� ��������� ���������
    �������� ���������� � ���������� ���� ��������� ���������.

  ���� ���������:
    partition_id - ������������� �������, ������������ � ����, - ������ � ������� ���������� �������� ������
    flags        - ����� ����
    duration     - ������������ ����

  ������ �� ������, ����������� ������� ������:
    ������ ���������� �������� ������ (�������� ���� ke_conf_partition_t)
*/
typedef struct {
  uint8_t       partition_id;
  uint8_t       flags;
  uint16_t      dummy;
  uint32_t      duration_lo;
  uint32_t      duration_hi;
} ke_conf_pwindow_t;

/*
  ����� ����������
    KE_CONF_PWFLAGS_RELEASE_POINT  - ������ ���� �������� ������ ������������� �������
    KE_CONF_PWFLAGS_EMPTY          - ���� �� ����������� �������� �������
*/
typedef enum {
  KE_CONF_PWFLAGS_RELEASE_POINT     = 0x1,
  KE_CONF_PWFLAGS_EMPTY							= 0x2,
} ke_conf_pwindow_flags_t;


/*---------------------------------------------------------------------------------------*/
/*
  ��������� ��������� ������.
    �������� ���������� � ������������ ��������� ������
    
  ���� ���������:
    flags             - �����  ������
    rset_id           - ������������� ������ �������� ������ - ������ � ������� ���������� ������� �������� ������
    name_off          - �������� ����� ������ �� ������ ������ ��������� ������ ���������
    cfg_string_off    - �������� ������ ������������ ������ �� ������ ������ ��������� ������ ���������

  ������ �� ������, ����������� ������� ������:
    ������ ���������� ������� �������� ������ (�������� ���� ke_conf_rset_t)
*/
typedef struct {
  uint8_t       flags;
  uint8_t       rset_id;
  uint16_t      dummy;

  uint16_t      name_off;
  uint16_t      cfg_string_off;
} ke_conf_system_task_t;

/*
  �����, ������������ � ���� flags ��������� ke_conf_system_task_t
*/
/*
typedef enum 
{ 
} ke_conf_systask_flags_t;
*/

/*---------------------------------------------------------------------------------------*/
/*
  ��������� ������������ ������.
    �������� ���������� � ������������ ������

  ���� ���������:
    flags                 - �����
    rset_id               - ������������� ������ �������� ���� (��� �������� 0xFF �� ������������) - ������ � ������� ���������� ������� �������� ������
    vas_count             - ���������� �������������� �������� ���� ���� ����������� �������� ������������
    event_count           - ���������� �������������� �������� ���� ���� ������� 
    thread_count          - ���������� �������������� �������� ���� ���� ����� 

  ������ �� ������, ����������� ������� ������:
    ������ ���������� ������� �������� ������ (�������� ���� ke_conf_rset_t)
*/
typedef struct {
  uint8_t      flags;
  uint8_t      rset_id;
  uint8_t      vas_count;
  uint8_t      dummy;
  uint16_t     event_count;
  uint16_t     thread_count;
} ke_conf_module_t;

/*
  �����, ������������ � ���� flags ��������� ke_conf_module_header_t
*/
/*
typedef enum
{
} ke_conf_mod_flags_t;
*/

/*---------------------------------------------------------------------------------------*/
/*
	������� �������� ��������� ��� �������.

	���� ���������:
		error_actions          - ������ ����, ������ �� ������� ������ ��� ������� �� ������. ������������� (����) ������ �������� �������� � �������.

*/
typedef struct {
	uint8_t      error_actions[KE_ERRID_COUNT];
} ke_conf_phmtable_t;


/*-----------------------------------------------------------*/
/* ������� ��� ������������� �������� ������ ������������    */
#define INITCONF_MEM_REGION(flags, size, paddr, saddr)      \
    {                                               \
      /* flags = */ flags,                          \
      /* size = */  size,	                          \
      /* paddr = */ paddr,                          \
      /* saddr = */ saddr                           \
    }

#define INITCONF_MEM_MAPPING(vaddr, vsize, mreg_id, roffset, attr )   \
    {                                                         \
      /* vaddr = */ vaddr,                                    \
      /* vsize = */ vsize,                                    \
      /* roffset = */ roffset,                                \
      /* attr = */ attr,                                      \
      /* mreg_id = */ mreg_id,                                \
    }

#define INITCONF_PWINDOW(pid, flags, duration)			            \
    {                                                           \
      /* partition_id = */ pid,                                 \
      /* flags = */ flags,																			\
      /* dummy = */ 0,																					\
      /* duration_lo = */ (duration) & 0xFFFFFFFF,              \
      /* duration_hi = */ ((duration) >> 32) & 0xFFFFFFFF,			\
    }

#define INITCONF_EMPTY_PWINDOW(duration)												\
    {                                                           \
      /* partition_id = */ 0,                                   \
      /* flags = */ KE_CONF_PWFLAGS_EMPTY,											\
      /* dummy = */ 0,																					\
      /* duration_lo = */ (duration) & 0xFFFFFFFF,              \
      /* duration_hi = */ ((duration) >> 32) & 0xFFFFFFFF,			\
    }


#define INITCONF_SPORT(flags, max_msg_size, refresh_time, name_off, snode_id )   \
    {																																\
			/* refresh_time_lo = */ (refresh_time) & 0xFFFFFFFF,					\
			/* refresh_time_hi = */ ((refresh_time) >> 32) & 0xFFFFFFFF,	\
			/* max_msg_size = */ max_msg_size,														\
      /* flags = */ flags,																					\
      /* name_off = */ name_off,																		\
      /* snode_id = */ snode_id,																		\
    }

#define INITCONF_SRC_SPORT(flags, max_msg_size, refresh_time, name_off, snode_id )    INITCONF_SPORT(flags|KE_CONF_SPORT_FLAGS_SND, max_msg_size, refresh_time, name_off, snode_id )

#define INITCONF_DST_SPORT(flags, max_msg_size, refresh_time, name_off, snode_id)   INITCONF_SPORT(flags, max_msg_size, refresh_time, name_off, snode_id )

#define INITCONF_DST_SPORT_WITH_EVENT(flags, max_msg_size, refresh_time, name_off, snode_id)  INITCONF_SPORT(flags|KE_CONF_SPORT_FLAGS_EVENT, max_msg_size, refresh_time, name_off, snode_id )

#define INITCONF_QPORT(flags, max_msg_size, max_msg_count, name_off, qnode_id )   \
    {                                                       \
      /* flags = */ flags,																  \
      /* max_msg_size = */ max_msg_size,									  \
      /* max_msg_count = */ max_msg_count,									\
      /* name_off = */ name_off,														\
      /* qnode_id = */ qnode_id,														\
      /* dummy = */ 0,																			\
    }

#define INITCONF_SRC_QPORT(flags, max_msg_size, max_msg_count, name_off, qnode_id)   \
      INITCONF_QPORT(flags | KE_CONF_QPORT_FLAGS_SND, max_msg_size, max_msg_count, name_off, qnode_id )

#define INITCONF_SRC_EV_QPORT(flags, max_msg_size, max_msg_count, name_off, qnode_id)   \
      INITCONF_QPORT(flags | KE_CONF_QPORT_FLAGS_SND | KE_CONF_QPORT_FLAGS_EVENT, max_msg_size, max_msg_count, name_off, qnode_id )

#define INITCONF_DST_QPORT(flags, max_msg_size, max_msg_count, name_off, qnode_id)   \
      INITCONF_QPORT(flags, max_msg_size, max_msg_count, name_off, qnode_id )

#define INITCONF_DST_EV_QPORT(flags, max_msg_size, max_msg_count, name_off, qnode_id)   \
      INITCONF_QPORT(flags | KE_CONF_QPORT_FLAGS_EVENT, max_msg_size, max_msg_count, name_off, qnode_id )


#define INITCONF_SNODE(flags, max_msg_size, rm_region_id)    \
    {                                                        \
      /* max_msg_size = */ max_msg_size,                     \
      /* flags = */ flags,                                   \
      /* rm_region_id = */ rm_region_id,                     \
    }

#define INITCONF_QNODE(flags, max_msg_size, rm_region_id)    \
    {                                                        \
      /* max_msg_size = */ max_msg_size,                     \
      /* flags = */ flags,                                   \
      /* rm_region_id = */ rm_region_id,                     \
    }

#define INITCONF_RSET(flags, mmapping_index, mmapping_count, sport_index, sport_count, qport_index, qport_count)    \
    {                                                         \
      /* flags = */          flags,                           \
      /* mmapping_count = */ mmapping_count,                  \
      /* mmapping_index = */ mmapping_index,                  \
      /* sport_index = */    sport_index,                     \
      /* sport_count = */    sport_count,                     \
      /* qport_index = */    qport_index,                     \
      /* qport_count = */    qport_count,                     \
    }

#define INITCONF_PARTITION_HMT(default_act, app_act, deadline_act)    \
    {                                                                         \
      /* KE_ERRID_NO_ERROR = */						default_act,												\
      /* KE_ERRID_MEM_RD_ACCESS = */			default_act,												\
      /* KE_ERRID_MEM_WR_ACCESS = */			default_act,												\
      /* KE_ERRID_IBUS_ERROR = */					default_act,												\
      /* KE_ERRID_DBUS_ERROR = */					default_act,												\
      /* KE_ERRID_SYSCALL = */						default_act,												\
      /* KE_ERRID_BREAKPOINT = */					default_act,												\
      /* KE_ERRID_RESERVED_INSTR = */			default_act,												\
      /* KE_ERRID_COPUNUSABLE = */				default_act,												\
      /* KE_ERRID_OVERFLOW = */						default_act,												\
      /* KE_ERRID_TRAP = */								default_act,												\
      /* KE_ERRID_FPE = */								default_act,												\
      /* KE_ERRID_INVALID_SERVICE = */		default_act,												\
      /* KE_ERRID_INVALID_ARG = */				default_act,												\
      /* KE_ERRID_CACHE_ERR = */					default_act,												\
      /* KE_ERRID_MEMORY_SHORTAGE = */		default_act,												\
      /* KE_ERRID_RESOURCE_SHORTAGE = */	default_act,												\
      /* KE_ERRID_CFG_ERROR = */					default_act,												\
      /* KE_ERRID_INIT_ERROR = */					default_act,												\
      /* KE_ERRID_APPLICATION_ERROR = */	app_act,														\
      /* KE_ERRID_APP_DEADLINE_MISSED = */deadline_act,												\
      /* KE_ERRID_ERR_MSG_OVERFLOW = */		default_act,												\
      /* KE_ERRID_INTERNAL_ERROR = */			default_act,												\
      /* KE_ERRID_UNKNOWN_ERROR = */			default_act,												\
      /* KE_ERRID_TIME_OVF = */						default_act,												\
      /* KE_ERRID_LOADER_ERROR = */				default_act,										  	\
      /* KE_ERRID_CHECKSUM_ERROR = */			default_act,										  	\
      /* KE_ERRID_RESERVED_3 = */					default_act 										  	\
    }

#define INITCONF_SYSTASK(flags, rset_id, name_off, cfg_string_off)    \
    {                                                        \
      /* flags = */ flags,                                   \
      /* rset_id = */ rset_id,                               \
      /* dummy = */ 0,                                       \
      /* name_off = */ name_off,                             \
      /* cfg_string_off = */ cfg_string_off,                 \
    }

#define INITCONF_MODULE(flags, rset_id, vas_count, event_count, thread_count)    \
    {                                                    \
      /* flags = */        flags,                        \
      /* rset_id = */      rset_id,                      \
      /* vas_count = */    vas_count,                    \
      /* dummy = */        0,                            \
      /* event_count = */  event_count,                  \
      /* thread_count = */ thread_count,                 \
    }

#endif /* __ASSEMBLER__ */


#endif /* __KE_CONF_MODULE2_H_INCLUDED__ */





