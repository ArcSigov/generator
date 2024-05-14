/*----------------------------------------------------------------------
Имя................ke_conf_module2.h
Назначение.........объявления данных конфигурации системы
-----------------------------------------------------------------------*/

#ifndef __KE_CONF_MODULE2_H_INCLUDED__
#define __KE_CONF_MODULE2_H_INCLUDED__

#ifndef __ASSEMBLER__

/* константы для тэгов конфигурации модуля */
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
  Описатель региона физической памяти модуля.
    Структура описывает область физической памяти, доступной для распределения.

  Поля структуры:
    flags    - флаги, определяющие тип области памяти
    paddr    - начальный физический адрес описываемой области памяти.
    saddr    - начальный физический адрес данных, копируемых в описываемую область памяти.
    size     - размер описываемой области памяти.
*/
typedef struct {
  uint32_t          flags;
  uint32_t          size;
  uint32_t          paddr;
  uint32_t          saddr;
} ke_conf_mregion_t;

/*
  Возможные значения флагов области физической памяти.
    SYSTEM      - область распределяется ОС
    PRIVATE     - тип доступа: одним роцессором. Имеет значение, если указан флаг SYSTEM.
    COMMON      - тип доступа: несколькими роцессорами. Имеет значение, если указан флаг SYSTEM.
    KERNEL      - может использоваться для данных ядра. Имеет значение, если указан флаг SYSTEM.
    ALLOCATE    - необходимо выделить физическую память для области (paddr не используется),
                  иначе (RESERVE) физическая память для области зарезервирована с адреса paddr
    PAGED       - область должна быть выделена как целое количество страниц, иначе выделяемая
                  область может быть не выровненной на границу страницы и размер ее может быть
                  не кратен размеру страницы.	Имеет значение, если указан флаг ALLOCATE.
    COPY        - копировать память из [saddr; saddr+size[ в выделенную область памяти
                  (ALLOCATE=1) или зарезервированную область [paddr; paddr+size[ (ALLOCATE=0)
    ZERO        - обнулить выделенную область памяти (ALLOCATE=1) или зарезервированную
                  область [paddr; paddr+size[ (ALLOCATE=0)
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
  Описатель отображения региона виртуальной памяти.
    Структура содержит информацию о мапировании области виртуальной памяти [vaddr; vaddr+size].
    Область мапируется в ВАП раздела, к которому относится описание.

  Поля структуры:
    vaddr    -  начальный виртуальный адрес мапируемой области.
    vsize    -  размер мапируемой области.
    mreg_id  -  индекс региона памяти в массиве описателей регионов физической памяти модуля.
    attr     -  атрибуты мапируемой области (см. ke_conf_mmap_attr_t).
    roffset  -  смещение внутри указанного региона памяти.

  Ссылки на данные, описываемые другими тэгами:
    массив описателей регионов физической памяти модуля (структур типа ke_conf_mregion_t) 
*/
typedef struct {
  uint32_t      vaddr;
  uint32_t      vsize;
  uint32_t      roffset;
  uint16_t      attr;
	uint16_t      mreg_id;
} ke_conf_mmapping_t;

/*
  тип мапирования
    READ                     - мапируемая область доступна для чтения
    WRITE                    - мапируемая область доступна для чтения
    GLOBAL                   - мапируемая область является глобальной
    UNCACHED                 - мапируемая область не является кэшируемой
    CACHED                   - мапируемая область является кэшируемой
    CACHED_WR_BACK           - Cachable, Write Back 
    CACHED_WR_THROUGH        - Cachable, Write Through, Not Write Allocate
    CACHED_WR_THROUGH_ALLOC  - Cachable, Write Through, Write Allocate
    CACHED_DEFAULT           - используется тип кэширования, принятый по умолчанию
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
  Описатель порта без очереди.
    Структура содержит информацию о конфигурации порта без очереди.

  Поля структуры:
    flags         - флаги
    max_msg_size  - максимальный размер сообщения (в байтах)
    refresh_time  - время обновления
    snode_id      - идекс объекта snode, с которым связан порт в массиве описателей узлов соединений портов без очереди модуля.
    name_off      - смещение имени порта от начала секции строковых данных хранилища 

  Ссылки на данные, описываемые другими тэгами:
    массив описателей узлов соединений портов без очереди модуля (структур типа ke_conf_snode_t)
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
  Флаги, используемые в поле flags структуры ke_conf_sport_t
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
  Описатель порта с очередью.
    Структура содержит информацию о конфигурации порта с очередью.

  Поля структуры:
    flags         - флаги
    max_msg_size  - максимальный размер сообщения (в байтах)
    max_msg_count - максимальное количество сообщений
    qnode_id      - идекс объекта qnode, с которым связан порт в массиве описателей узлов соединений портов с очередью модуля.
    name_off      - смещение имени порта от начала секции строковых данных хранилища

  Ссылки на данные, описываемые другими тэгами:
    массив описателей узлов соединений портов с очередью модуля (структур типа ke_conf_qnode_t)
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
  флаги, используемые в поле flags структуры ke_conf_qport_t
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
  Описатель набора ресурсов
    Содержит информацию о наборе ресурсов

  Поля структуры:
    flags                 - флаги
    mmapping_index        - индекс первого описателя области мапирования, относящегося к данному набору ресурсов, в массиве описателей областей мапирования модуля
    mmapping_count        - количество областей мапирования, относящегося к данному набору ресурсов,
    sport_index           - индекс первого описателя порта без очереди, относящегося к данному набору ресурсов
    sport_count           - количество описателей портов без очереди, относящегося к данному набору ресурсов
    qport_index           - индекс первого описателя порта с очередью, относящегося к данному набору ресурсов
    qport_count           - количество описателей портов с очередью, относящегося к данному набору ресурсов

  Ссылки на данные, описываемые другими тэгами:
    массив описателей областей мапирования модуля (структур типа ke_conf_mmapping_t)
    массив описателей портов без очереди модуля (структур типа ke_conf_sport_t)
    массив описателей портов с очередью модуля (структур типа ke_conf_qport_t)
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
  флаги, используемые в поле flags структуры ke_conf_rset_header_t
    GLOBAL             - глобальный набор ресурсов, определенный в нем набор мапирования является глобальным
    SYSTEM             - набор ресурсов системной задачи, определенные в нем порты без очереди требуют создания события
    CFG_DATA_SIZE_MASK - маска кол-ва 32-разрядных слов конфигурационных данных для каждого порта в наборе ресурсов
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
  Описатель узла соединения порта без очереди
    Содержит информацию о конфигурации канала sampling channel

  Поля структуры:
    max_msg_size	- максимальный размер сообщения (в байтах)
    flags					- флаги 
    rm_region_id  - индекс региона памяти, используемого для буфера канала, в массиве описателей регионов физической памяти модуля.

  Ссылки на данные, описываемые другими тэгами:
    массив описателей регионов физической памяти модуля (структур типа ke_conf_mregion_t)
*/
typedef struct {
  uint16_t      max_msg_size;
  uint8_t       flags;
  uint8_t       rm_region_id;
} ke_conf_snode_t;

/*
  флаги соединения
    KE_CONF_SNODE_FLAGS_ALLOCATE_MEM - память для буфера данных выделяется ОС
    KE_CONF_SNODE_FLAGS_RESERVED_MEM - память для буфера данных описывается регионом памяти
    KE_CONF_SNODE_FLAGS_ALIGN64      - память для буфера данных должна быть выровнена на границу 64х разрядного слова
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
  Описатель узла соединения порта с очередью
    Содержит информацию о конфигурации канала queuing channel
  
  Поля структуры:
    max_msg_size	- максимальный размер сообщения (в байтах)
    flags					- флаги 
    rm_region_id  - индекс региона в массиве rm_regions модуля, описывающего память для буфера 
    rm_region_id  - индекс региона памяти, используемого для буфера канала, в массиве описателей регионов физической памяти модуля.

  Ссылки на данные, описываемые другими тэгами:
    массив описателей регионов физической памяти модуля (структур типа ke_conf_mregion_t)
    */
typedef struct {
  uint16_t      max_msg_size;
  uint8_t       flags;
  uint8_t       rm_region_id;
} ke_conf_qnode_t;

/*
  флаги соединения
		KE_CONF_QNODE_FLAGS_ALLOCATE_MEM - память для буфера данных выделяется ОС
		KE_CONF_QNODE_FLAGS_RESERVED_MEM - память для буфера данных описывается регионом памяти
		KE_CONF_QNODE_FLAGS_ALIGN64      - память для буфера данных должна быть выровнена на границу 64х разрядного слова
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
  Описатель раздела
    Содержит информацию о конфигурации раздела

  Поля структуры:
    partition_id           - идентификатор раздела
    flags                  - флаги  раздела
    rset_id                - идентификатор набора ресурсов раздела - индекс в массиве описателей наборов ресурсов модуля
    hm_table_id            - индекс в массиве таблиц монитора состояния модуля

    period                 - период раздела во временной диаграмме (исп-ся только в APEX)
    duration               - длительность раздела во временной диаграмме (исп-ся только в APEX)

    phys_mem_size          - общий размер физической памяти, выделяемой разделу (для app и sysm)
                             сюда не входит область стека sysm, физическая память устройств,
                             мапируемая в ВАП раздела и физическая память, используемая для зон общей памяти

    name_off                - смещение имени раздела от начала секции строковых данных хранилища
    app_filename_off        - смещение имени файла приложения от начала секции строковых данных хранилища

    app_stacks_vaddr        - адрес области виртуального адресного пространства приложения, которая используется для отображения стеков процессов приложения
    app_stacks_vsize        - размер области виртуального адресного пространства приложения, которая используется для отображения стеков процессов приложения
    apex_init_addr          - виртуальный адрес кода (функции) процесса инициализации приложения
    apex_init_stack_size    - размер стека процесса инициализации приложения в байтах

    apex_err_msg_count      - количество сообщений в очереди сообщений процесса-обработчика ошибок
    apex_process_count      - максимальное количество процессов, используемое приложением, 
                              включая процесс инициализации и процесс-обработчик ошибок
    apex_event_count        - максимальное количество объектов типа EVENT, используемое приложением, 
    apex_sem_count          - максимальное количество объектов типа SEMAPHORE, используемое приложением, 
    apex_buf_count          - максимальное количество объектов типа BUFFER, используемое приложением, 
    apex_bboard_count       - максимальное количество объектов типа BLACKBOARD, используемое приложением, 

  Ссылки на данные, описываемые другими тэгами:
    массив описателей наборов ресурсов модуля (структур типа ke_conf_rset_t)
    массив таблиц монитора состояния модуля (структур типа ke_conf_rset_t)
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
  флаги, используемые в поле flags структуры ke_conf_partion_t
    FAKE             - раздел является фиктивным, т.е. всегда находится в состоянии IDLE
    APP_CODE_CACHED  - код раздела мапируется с атрибутом кеширования
    APP_STACK_CACHED - стеки процессов раздела мапируются с атрибутом кеширования
    APP_DATA_CACHED  - данные раздела мапируются с атрибутом кеширования
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
  Таблица монитора состояния раздела.
  Структура данных содержит байтовый массив кодов реакции на ошибки. Тип ошибки определяет индекс в массиве.
  uint8_t      hm_table[KE_ERRID_COUNT];
*/

/*
  Коды реакций на ошибки
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
  Описатель окна временной диаграммы
    Содержит информацию о параметрах окна временной диаграммы.

  Поля структуры:
    partition_id - идентификатор раздела, выполняемого в окне, - индекс в массиве описателей разделов модуля
    flags        - флаги окна
    duration     - длительность окна

  Ссылки на данные, описываемые другими тэгами:
    массив описателей разделов модуля (структур типа ke_conf_partition_t)
*/
typedef struct {
  uint8_t       partition_id;
  uint8_t       flags;
  uint16_t      dummy;
  uint32_t      duration_lo;
  uint32_t      duration_hi;
} ke_conf_pwindow_t;

/*
  флаги прерывания
    KE_CONF_PWFLAGS_RELEASE_POINT  - начало окна является точкой синхронизации раздела
    KE_CONF_PWFLAGS_EMPTY          - окно не принадлежит никакому разделу
*/
typedef enum {
  KE_CONF_PWFLAGS_RELEASE_POINT     = 0x1,
  KE_CONF_PWFLAGS_EMPTY							= 0x2,
} ke_conf_pwindow_flags_t;


/*---------------------------------------------------------------------------------------*/
/*
  Описатель системной задачи.
    Содержит информацию о конфигурации системной задачи
    
  Поля структуры:
    flags             - флаги  задачи
    rset_id           - идентификатор набора ресурсов задачи - индекс в массиве описателей наборов ресурсов модуля
    name_off          - смещение имени задачи от начала секции строковых данных хранилища
    cfg_string_off    - смещение строки конфигурации задачи от начала секции строковых данных хранилища

  Ссылки на данные, описываемые другими тэгами:
    массив описателей наборов ресурсов модуля (структур типа ke_conf_rset_t)
*/
typedef struct {
  uint8_t       flags;
  uint8_t       rset_id;
  uint16_t      dummy;

  uint16_t      name_off;
  uint16_t      cfg_string_off;
} ke_conf_system_task_t;

/*
  Флаги, используемые в поле flags структуры ke_conf_system_task_t
*/
/*
typedef enum 
{ 
} ke_conf_systask_flags_t;
*/

/*---------------------------------------------------------------------------------------*/
/*
  Описатель конфигурации модуля.
    Содержит информацию о конфигурации модуля

  Поля структуры:
    flags                 - флаги
    rset_id               - идентификатор набора ресурсов ядра (при значении 0xFF не используется) - индекс в массиве описателей наборов ресурсов модуля
    vas_count             - количество дополнительных объектов ядра типа виртуальное адресное пространство
    event_count           - количество дополнительных объектов ядра типа событие 
    thread_count          - количество дополнительных объектов ядра типа поток 

  Ссылки на данные, описываемые другими тэгами:
    массив описателей наборов ресурсов модуля (структур типа ke_conf_rset_t)
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
  флаги, используемые в поле flags структуры ke_conf_module_header_t
*/
/*
typedef enum
{
} ke_conf_mod_flags_t;
*/

/*---------------------------------------------------------------------------------------*/
/*
	Таблица монитора состояния для раздела.

	Поля структуры:
		error_actions          - массив байт, каждый из которых хранит код реакции на ошибку. Идентификатор (кода) ошибки является индексом в массиве.

*/
typedef struct {
	uint8_t      error_actions[KE_ERRID_COUNT];
} ke_conf_phmtable_t;


/*-----------------------------------------------------------*/
/* макросы для инициализации структур данных конфигурации    */
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





