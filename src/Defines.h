#ifndef DEFINES_H
#define DEFINES_H


#include <stdint.h>


#define BYTE								uint_fast8_t
#define FREQUENCY							uint_fast32_t /* Frequência máxima que um símbolo pode ter */
//#define DEBUG								1

#define SYMBOL								uint_fast8_t
#define SIZE								uint_fast16_t // Imediatamente maior que SYMBOL
#define POWER_SIZE							uint_fast32_t // Imediatamente maior que SIZE
#define FILE_SIZE							uint_fast32_t // Tamanho máximo do arquivo
#define BITS_CODIFICATION					8
#define BYTE_BIT							8
#define SIZEOF_SYMBOL						1
#define POWER_BITS_CODIFICATION				256
#define ALIGN_NODE							2
#define ALIGN_NODE_ARRAY					6
#define ALIGN_TREE_ARRAY					6
#define ALIGN_STACK							6
#define ALIGN_CODIFICATION					5
#define ALIGN_CODIFICATION_ARRAY_ELEMENT	6



#define GET_BYTE(a, b)			*((BYTE *)(a)+(b))
#define SET_BIT(a, b)			(GET_BYTE((a), ((b)/BYTE_BIT)) |= (1 << (BYTE_BIT - 1 - (b) % BYTE_BIT)))
#define CLEAR_BIT(a, b)			(GET_BYTE((a), ((b)/BYTE_BIT)) &= ~(1 << (BYTE_BIT - 1 - (b) % BYTE_BIT)))
#define GET_BIT(a, b)			(GET_BYTE((a), ((b)/BYTE_BIT)) >> (BYTE_BIT - 1 - (b) % BYTE_BIT)) & 0x1



#endif // DEFINES_H
