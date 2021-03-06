/**
 *
 * Copyright (C) Sierra Wireless Inc. Use of this work is subject to license.
 */


/** @file hex.c
 *
 * Copyright (C) Sierra Wireless Inc. Use of this work is subject to license.
 */
#include "legato.h"


//--------------------------------------------------------------------------------------------------
/**
 * Convert a numeric value into a uppercase character representing the hexidecimal value of the
 * input.
 *
 * @return Hexidecimal character in the range [0-9A-F] or 0 if the input value was too large
 */
//--------------------------------------------------------------------------------------------------
static char DecToHex(uint8_t hex)
{
    if (hex < 10) {
        return (char)('0'+hex);  // for number
    }
    else if (hex < 16) {
        return (char)('A'+hex-10);  // for A,B,C,D,E,F
    }
    else {
        LE_DEBUG("value %u cannot be converted in HEX string", hex);
        return 0;
    }
}

//--------------------------------------------------------------------------------------------------
/**
 * Convert a string of valid hexadecimal characters [0-9a-fA-F] into a byte array where each
 * element of the byte array holds the value corresponding to a pair of hexadecimal characters.
 *
 * @return
 *      - number of bytes written into binaryPtr
 *      - -1 if the binarySize is too small or stringLength is odd or stringPtr contains an invalid
 *        character
 *
 * @note The input string is not required to be NULL terminated.
 */
//--------------------------------------------------------------------------------------------------
int32_t le_hex_StringToBinary
(
    const char *stringPtr,     ///< [IN] string to convert
    uint32_t    stringLength,  ///< [IN] string length
    uint8_t    *binaryPtr,     ///< [OUT] binary result
    uint32_t    binarySize     ///< [IN] size of the binary table.  Must be >= stringLength / 2
)
{
    uint32_t idxString;
    uint32_t idxBinary;
    char*    refStrPtr = "0123456789ABCDEF";

    if (stringLength % 2 != 0)
    {
        LE_DEBUG("The input stringLength=%u is not a multiple of 2", stringLength);
        return -1;
    }

    if (stringLength / 2 > binarySize)
    {
        LE_DEBUG(
            "The stringLength (%u) is too long to convert into a byte array of length (%u)",
            stringLength,
            binarySize);
        return -1;
    }

    for (idxString=0,idxBinary=0 ; idxString<stringLength ; idxString+=2,idxBinary++)
    {
        char* ch1Ptr;
        char* ch2Ptr;


        if ( ((ch1Ptr = strchr(refStrPtr, toupper(stringPtr[idxString]))) && *ch1Ptr) &&
             ((ch2Ptr = strchr(refStrPtr, toupper(stringPtr[idxString+1]))) && *ch2Ptr) )
        {
            binaryPtr[idxBinary] = ((ch2Ptr - refStrPtr) & 0x0F) |
                                   (((ch1Ptr - refStrPtr)<<4) & 0xF0);
        }
        else
        {
            LE_DEBUG("Invalid string to convert (%s)", stringPtr);
            return -1;
        }
    }

    return idxBinary;
}

//--------------------------------------------------------------------------------------------------
/**
 * Convert a byte array into a string of uppercase hexadecimal characters.
 *
 * @return number of characters written to stringPtr or -1 if stringSize is too small for
 *         binarySize
 *
 * @note the string written to stringPtr will be NULL terminated.
 */
//--------------------------------------------------------------------------------------------------
int32_t le_hex_BinaryToString
(
    const uint8_t *binaryPtr,  ///< [IN] binary array to convert
    uint32_t       binarySize, ///< [IN] size of binary array
    char          *stringPtr,  ///< [OUT] hex string array, terminated with '\0'.
    uint32_t       stringSize  ///< [IN] size of string array.  Must be >= (2 * binarySize) + 1
)
{
    int32_t idxString,idxBinary;

    if (stringSize < (2 * binarySize) + 1)
    {
        LE_DEBUG(
            "Hex string array (%u) is too small to convert (%u) bytes",
            stringSize,
            binarySize);
        return -1;
    }

    for(idxBinary=0,idxString=0;
        idxBinary<binarySize;
        idxBinary++,idxString=idxString+2)
    {
        stringPtr[idxString]   = DecToHex( (binaryPtr[idxBinary]>>4) & 0x0F);
        stringPtr[idxString+1] = DecToHex(  binaryPtr[idxBinary]     & 0x0F);
    }
    stringPtr[idxString] = '\0';

    return idxString;
}

//--------------------------------------------------------------------------------------------------
/**
 * Convert a NULL terminated string of valid hexadecimal characters [0-9a-fA-F] into an integer.
 *
 * @return
 *      - Positive integer corresponding to the hexadecimal input string
 *      - -1 if the input contains an invalid character or the value will not fit in an integer
 */
//--------------------------------------------------------------------------------------------------
int le_hex_HexaToInteger
(
    const char *stringPtr ///< [IN] string of hex chars to convert into an int
)
{
    int result = 0;
    while (*stringPtr != '\0')
    {
        if (result > (INT_MAX / 16))
        {
            // Consuming more input data may overflow the integer value
            return -1;
        }

        char base;
        if (*stringPtr >= '0' && *stringPtr <='9')
        {
            base = '0';
        }
        else if (*stringPtr >= 'a' && *stringPtr <= 'f')
        {
            base = 'a' - 10;
        }
        else if (*stringPtr >= 'A' && *stringPtr <= 'F')
        {
            base = 'A' - 10;
        }
        else
        {
            // Invalid input character
            return -1;
        }

        result = (result << 4) | (*stringPtr - base);
        stringPtr++;
    }

    return result;
}
