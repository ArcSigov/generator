/*----------------------------------------------------------------------
���................tag_storage.h
����������.........���������� ������� �����
-----------------------------------------------------------------------*/

#ifndef __TAG_STORAGE_H_INCLUDED__
#define __TAG_STORAGE_H_INCLUDED__

#ifndef __ASSEMBLER__

/*-----------------------------------------------------------------------------*/
/*
        get_offset - �������� �������� ��� ����� ����� � ��������� ����
        type: ��� ���������
        member: ��� ���� � ���������.
*/
#define get_offset(type, member) ( (uint32_t)(  &(  ((type *)0)->member )  ) )

/*
        get_offset_dif - �������� �������� ��� �������� �� base_member � ��������� �����
        type: ��� ���������
        base_member:��� ���� � ���������.
        member: ��� ���� � ���������.
*/
#define get_offset_dif(type, base_member, member) ( get_offset(type, member) - get_offset(type, base_member) )

/*---------------------------------------------------------------------------------------*/
/*
	��������� ���� ��� ���������������� ����������
	flags                   - �����, ������������ ��� ����
	name_offset             - �������� �� ������ ������� �����, � �������� ���������� ��� ����
	data                    - ����������� ���������� ������ (��������) ���� ��� ���������� �� �� ������������  (� ����������� �� �������� ������)
	data.int_value          - ������ ���� � ������, ����� ��� ������ ������������� 32-� ��������� ��������, �.�. ���������� ���� INT32
	data.v.value_size       - ������ ������ ����, � ������, ����� ��� ������ �������� ������������� �������, �.�. ���������� ���� ANY
	data.v.value_size       - ������ ������ ������ ���� (�������� �������� '\0'), � ������, ����� ��� ������ ��������� ��������, �.�. ���������� ���� STRING
	data.v.value_offset     - �������� ������ ���� �� ������ ������� ������ ���������, � ������, ����� ��� ������ �������� ������������� �������, �.�. ���������� ���� ANY
	data.v.value_offset     - �������� ������ ���� �� ������ ������� �����, � ������, ����� ��� ������ ��������� ��������, �.�. ���������� ���� STRING
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
	��������� �������� ������ ��� ����.
	INT32        - ������ ���� ������������ ����� 32-��������� ������������� �������� (int_value �������� ��� ��������)
	STRING       - ������ ���� ������������ ����� ������ (value_offset �������� �������� �� ������ ������� �����, value_size �������� ������ ������, �������� �������� '\0')
	ANY          - ������ ���� ������������ ����� �������� ������������� ������� 
	               (value_offset �������� �������� �� ������ ��������� ���������������� ����������, value_size �������� ������ ������)
*/
typedef enum {
	TAG_FLAGS_DATA_TYPE   = 0xF,
	TAG_FLAGS_INT32       = 0x0,
	TAG_FLAGS_STRING      = 0x1,
	TAG_FLAGS_ANY         = 0x2,
} tag_flags_t;

/*---------------------------------------------------------------------------------------*/
/*
	��������� ��������� ��������� ���������������� ����������

	signature             - ��������� ��� �������� ������� ��������� ���������������� ���������� ( �������� 0x, ��������������� ������ "TAGS" )
	storage_size          - ������ ��������� ���������������� ����������, �������� ������� ���� ������������ ��������
	crc_type              - ��� ���� ������������ �������� (����������� �����), �������� ���� tag_storage_crc_type_t
	crc_size              - ������ ������� ���� ������������ �������� (����������� �����)
	header_size           - ������ ��������� ���������
	flags                 - �����, ������������ ��������� ���������

	tag_size              - ������ ������ ���� � ������
	tag_count             - ���������� �����
	data_size             - ������ ������� ������ ��������� 

	����������� ��������:
	tags_offset = header_size                          - �������� ������� ����� �� ������ ��������� ��������� ���������
	data_offset = tags_offset + tag_size * tag_count   - �������� ������� ������ ��������� �� ������ ��������� ��������� ���������
	strings_offset = data_offset + data_size           - �������� ������� ����� �� ������ ��������� ��������� ���������
	crc_offset = storage_size                          -  �������� ������� ���� ������������ �������� (����������� �����) �� ������ ��������� ��������� ���������
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
	��������� ���� �� ����������� ���������, �� ������� ��������������� �� ���
	tag_t                             tags[tag_count];   // ������ �����
	any_data1_t                       data1;             // ������� ������ ���������
	any_data2_t                       data2;
	...
	any_dataN_t                       dataN;
	char                              strings[];         // ������� �����
	uint8_t                           crc[];             // ������� ���� ������������ �������� (����������� �����)
*/
} tag_storage_header_t;

/*
	��������� ��� �������� ������� ��������� ���������������� ����������, ������������ � ���� signature ��������� tag_storage_header_t
	( �������� 0x53474154, ��������������� ������ "TAGS" )
*/
enum {
	TAG_STORAGE_SIGNATURE = 0x53474154  /* 'S' 'G' 'A' 'T' -> "TAGS" ��� ����������� ������ �� ���� little endian */
};

/*
	�����, ������������ � ���� flags ��������� tag_storage_header_t
		SORTED - ������ ����� ������������ �� ������ ����� � ���������� �������
				 ���� ���� �� ����������, ������ ����� ������������, � ����� ���� �� ����� ������ ������������� �������� ���������� �� ���� �����.
*/
typedef enum {
	TAGSTORAGE_HEADER_FLAGS_SORTED = 0x1,
} tag_storage_header_flags_t;

/*
	��� ���� ������������ �������� (����������� �����), ������������� � ���� crc_type ��������� tag_storage_header_t
		UNUSED - ��� ������������ �������� (����������� �����) �� ������������, ���� crc_size ��������� tag_storage_header_t �������� �������� 0
		CRC16_CCITT - ��� ������������ ��������, ����������� � ������� ����������� ���������� x**16+x**12+x**5+1 (������ � ���� ������� ������������������ 0�1021)
		CHECKSUM64 - 64-� ��������� ����������� �����, ���������� ��������� 32-� ��������� ���� ������
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
