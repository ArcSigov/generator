/*----------------------------------------------------------------------
Имя................tag_storage.h
Назначение.........объявления таблицы тэгов
-----------------------------------------------------------------------*/

#ifndef __TAG_STORAGE_H_INCLUDED__
#define __TAG_STORAGE_H_INCLUDED__

#ifndef __ASSEMBLER__

/*-----------------------------------------------------------------------------*/
/*
        get_offset - получить смещение для этого члена в структуре типа
        type: тип структуры
        member: имя поля в структуре.
*/
#define get_offset(type, member) ( (uint32_t)(  &(  ((type *)0)->member )  ) )

/*
        get_offset_dif - получить смещение для элемента из base_member в структуре типов
        type: тип структуры
        base_member:имя поля в структуре.
        member: имя поля в структуре.
*/
#define get_offset_dif(type, base_member, member) ( get_offset(type, member) - get_offset(type, base_member) )

/*---------------------------------------------------------------------------------------*/
/*
	описывает один тэг конфигурационной информации
	flags                   - флаги, определяющие тип тэга
	name_offset             - смещение от начала таблицы строк, с которого начинается имя тэга
	data                    - объединение содержащее данные (значение) тэга или информацию об их расположении  (в зависимости от значения флагов)
	data.int_value          - данные тэга в случае, когда тэг хранит целочисленное 32-х разрядное значение, т.е. установлен флаг INT32
	data.v.value_size       - размер данных тэга, в случае, когда тэг хранит значение произвольного формата, т.е. установлен флаг ANY
	data.v.value_size       - размер строки данных тэга (исключая конечный '\0'), в случае, когда тэг хранит строковое значение, т.е. установлен флаг STRING
	data.v.value_offset     - смещение данных тэга от начала области данных хранилища, в случае, когда тэг хранит значение произвольного формата, т.е. установлен флаг ANY
	data.v.value_offset     - смещение данных тэга от начала таблицы строк, в случае, когда тэг хранит строковое значение, т.е. установлен флаг STRING
*/
typedef struct {
	uint16_t        flags;
	uint16_t        name_offset;
	union {
		uint32_t      int_value;
		struct {
			uint16_t    value_size;
			uint16_t    value_offset;
		} v;
	} data;
} tag_t;

/*
	Возможные значения флагов тип тэга.
	INT32        - данные тэга представляют собой 32-разрядное целочисленное значение (int_value содержит это значение)
	STRING       - данные тэга представляют собой строку (value_offset содержит смещение от начала таблицы строк, value_size содержит размер строки, исключая конечный '\0')
	ANY          - данные тэга представляют собой значение произвольного формата 
	               (value_offset содержит смещение от начала заголовка конфигурационной информации, value_size содержит размер данных)
*/
typedef enum {
	TAG_FLAGS_DATA_TYPE   = 0xF,
	TAG_FLAGS_INT32       = 0x0,
	TAG_FLAGS_STRING      = 0x1,
	TAG_FLAGS_ANY         = 0x2,
} tag_flags_t;

/*---------------------------------------------------------------------------------------*/
/*
	описывает заголовок хранилища конфигурационной информации

	signature             - сигнатура для проверки наличия хранилища конфигурационной информации ( значение 0x, соответствующее строке "TAGS" )
	storage_size          - размер хранилища конфигурационной информации, исключая область кода циклического контроля
	crc_type              - тип кода циклического контроля (контрольной суммы), значение типа tag_storage_crc_type_t
	crc_size              - размер области кода циклического контроля (контрольной суммы)
	header_size           - размер заголовка хранилища
	flags                 - флаги, определяющие параметры хранилища

	tag_size              - размер одного тэга в байтах
	tag_count             - количество тэгов
	data_size             - размер области данных хранилища 

	вычисляемые смещения:
	tags_offset = header_size                          - смещение массива тэгов от начала структуры заголовка хранилища
	data_offset = tags_offset + tag_size * tag_count   - смещение области данных хранилища от начала структуры заголовка хранилища
	strings_offset = data_offset + data_size           - смещение таблицы строк от начала структуры заголовка хранилища
	crc_offset = storage_size                          -  смещение области кода циклического контроля (контрольной суммы) от начала структуры заголовка хранилища
*/
typedef struct {
	uint32_t     signature;
	uint32_t     storage_size;
	uint8_t      crc_type;
	uint8_t      crc_size;
	uint16_t     header_size;
	uint16_t     flags;
	uint8_t      dummy;
	uint8_t      tag_size;
	uint16_t     tag_count;
	uint16_t     data_size;
	/*
	следующие поля не принадлежат заголовку, но следуют непосредственно за ним
	tag_t                             tags[tag_count];   // массив тэгов
	any_data1_t                       data1;             // область данных хранилища
	any_data2_t                       data2;
	...
	any_dataN_t                       dataN;
	char                              strings[];         // таблица строк
	uint8_t                           crc[];             // область кода циклического контроля (контрольной суммы)
*/
} tag_storage_header_t;

/*
	сигнатура для проверки наличия хранилища конфигурационной информации, используемая в поле signature структуры tag_storage_header_t
	( значение 0x53474154, соответствующее строке "TAGS" )
*/
enum {
	TAG_STORAGE_SIGNATURE = 0x53474154  /* 'S' 'G' 'A' 'T' -> "TAGS" для организации памяти по типу little endian */
};

/*
	Флаги, используемые в поле flags структуры tag_storage_header_t
		SORTED - массив тэгов отсортирован по именам тэгов в алфавитном порядке
				 Если флаг не установлен, массив тэгов несортирован, и поиск тега по имени должен производиться линейным сравнением по всем тэгам.
*/
typedef enum {
	TAGSTORAGE_HEADER_FLAGS_SORTED = 0x1,
} tag_storage_header_flags_t;

/*
	Тип кода циклического контроля (контрольной суммы), используемого в поле crc_type структуры tag_storage_header_t
		UNUSED - код циклического контроля (контрольная сумма) не используется, поле crc_size структуры tag_storage_header_t содержит значение 0
		CRC16_CCITT - код циклического контроля, вычисляемый с помощью образующего многочлена x**16+x**12+x**5+1 (запись в виде битовой последовательности 0х1021)
		CHECKSUM64 - 64-х разрядная контрольная сумма, получаемая сложением 32-х разрядных слов данных
*/
typedef enum {
	TAGSTORAGE_HEADER_CRCTYPE_UNUSED      = 0x0,
	TAGSTORAGE_HEADER_CRCTYPE_CRC16_CCITT = 0x1,
	TAGSTORAGE_HEADER_CRCTYPE_CHECKSUM64  = 0x2,
} tag_storage_crc_type_t;

/*-------------------------------------------------------------------------*/
#define TAG_STORAGE_INIT_HEADER(type, tags_field, data_field, strings_field, sflags)                    \
  {                                                                                                   \
    .signature       = TAG_STORAGE_SIGNATURE,                                                         \
    .storage_size    = sizeof(type),                                                                  \
    .crc_type        = TAGSTORAGE_HEADER_CRCTYPE_UNUSED,                                              \
    .crc_size        = 0,                                                                             \
    .header_size     = sizeof(tag_storage_header_t),                                                  \
    .flags           = sflags,                                                                        \
    .dummy           = 0,                                                                             \
    .tag_size        = sizeof(tag_t),                                                                 \
    .tag_count       = get_offset_dif(type, tags_field, data_field) / sizeof(tag_t),                  \
    .data_size       = get_offset_dif(type, data_field, strings_field),                               \
  }

/*-------------------------------------------------------------------------*/
#define TAG_STORAGE_INIT_HEADER_USING_CRC(type, tags_field, data_field, strings_field, crc_field, sflags, crc_type) \
  {                                                                                                   \
    .signature       = TAG_STORAGE_SIGNATURE,                                                         \
    .storage_size    = get_offset(type, crc_field),                                                   \
    .crc_type        = crc_type,                                                                      \
    .crc_size        = sizeof(type) - get_offset(type, crc_field),                                    \
    .header_size     = sizeof(tag_storage_header_t),                                                  \
    .flags           = sflags,                                                                        \
    .dummy           = 0,                                                                             \
    .tag_size        = sizeof(tag_t),                                                                 \
    .tag_count       = get_offset_dif(type, tags_field, data_field) / sizeof(tag_t),                  \
    .data_size       = get_offset_dif(type, data_field, strings_field),                               \
  }

/*-------------------------------------------------------------------------*/
#define TAG_INIT_INT(strings_type, tag_name_field, value)                    \
  {                                                                        \
    .flags = TAG_FLAGS_INT32,                                              \
    .name_offset = get_offset(strings_type, tag_name_field),               \
    .data.int_value = value,                                               \
  }

/*-------------------------------------------------------------------------*/
#define TAG_INIT_STRING(strings_type, tag_name_field, string_field, string_length)  \
  {                                                                           \
    .flags = TAG_FLAGS_STRING,                                                \
    .name_offset = get_offset(strings_type, tag_name_field),                  \
    .data.v.value_size = (string_length),                                     \
    .data.v.value_offset = get_offset(strings_type, string_field),            \
  }

/*-------------------------------------------------------------------------*/
#define TAG_INIT_ANY(strings_type, tag_name_field, data_type, value_field, tag_value_size)   \
  {                                                                        \
    .flags = TAG_FLAGS_ANY,                                                \
    .name_offset = get_offset(strings_type, tag_name_field),               \
    .data.v.value_size = (tag_value_size),                                 \
    .data.v.value_offset = get_offset(data_type, value_field),             \
  }
/*-------------------------------------------------------------------------*/


#endif /* __ASSEMBLER__ */


#endif /* __TAG_STORAGE_H_INCLUDED__ */
