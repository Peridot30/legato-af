//-------------------------------------------------------------------------------------------------
/**
 * @file cm_info.h
 *
 * Handle info related functionality
 *
 * Copyright (C) Sierra Wireless Inc. Use of this work is subject to license.
 */
//-------------------------------------------------------------------------------------------------

#include "legato.h"
#include "interfaces.h"
#include "cm_info.h"
#include "cm_common.h"

//-------------------------------------------------------------------------------------------------
/**
 * Print the data help text to stdout.
 */
//-------------------------------------------------------------------------------------------------
void cm_info_PrintInfoHelp
(
    void
)
{
    printf("Info usage\n"
            "==========\n\n"
            "To print all known info:\n"
            "\tcm info\n"
            "\tcm info all\n\n"
            "To print the device model:\n"
            "\tcm info device\n\n"
            "To print the IMEI:\n"
            "\tcm info imei\n\n"
            "To print the serial number:\n"
            "\tcm info fsn\n\n"
            "To print the firmware version:\n"
            "\tcm info firmware\n\n"
            "To print the bootloader version:\n"
            "\tcm info bootloader\n\n"
            "To print the PRI part and the PRI revision:\n"
            "\tcm info pri\n\n"
            "To print the SKU:\n"
            "\tcm info sku\n\n"
            );
}

//-------------------------------------------------------------------------------------------------
/**
 * Print the IMEI
 */
//-------------------------------------------------------------------------------------------------
void cm_info_PrintImei
(
    bool withHeaders
)
{
    char imei[LE_INFO_IMEI_MAX_BYTES] = {0};

    le_info_GetImei(imei, sizeof(imei));

    if(withHeaders)
    {
        cm_cmn_FormatPrint("IMEI", imei);
    }
    else
    {
        printf("%s\n", imei);
    }
}

//-------------------------------------------------------------------------------------------------
/**
 * Print the serial number
 */
//-------------------------------------------------------------------------------------------------
void cm_info_PrintSerialNumber
(
    bool withHeaders
)
{
    char serialNumber[LE_INFO_MAX_PSN_BYTES] = {0};

    le_info_GetPlatformSerialNumber(serialNumber, sizeof(serialNumber));

    if(withHeaders)
    {
        cm_cmn_FormatPrint("FSN", serialNumber);
    }
    else
    {
        printf("%s\n", serialNumber);
    }
}

//-------------------------------------------------------------------------------------------------
/**
 * Print the firmware version
 */
//-------------------------------------------------------------------------------------------------
void cm_info_PrintFirmwareVersion
(
    bool withHeaders
)
{
    char version[LE_INFO_MAX_VERS_BYTES] = {0};

    le_info_GetFirmwareVersion(version, sizeof(version));

    if(withHeaders)
    {
        cm_cmn_FormatPrint("Firmware", version);
    }
    else
    {
        printf("%s\n", version);
    }
}

//-------------------------------------------------------------------------------------------------
/**
 * Print the bootloader version
 */
//-------------------------------------------------------------------------------------------------
void cm_info_PrintBootloaderVersion
(
    bool withHeaders
)
{
    char version[LE_INFO_MAX_VERS_BYTES] = {0};

    le_info_GetBootloaderVersion(version, sizeof(version));

    if(withHeaders)
    {
        cm_cmn_FormatPrint("Bootloader", version);
    }
    else
    {
        printf("%s\n", version);
    }
}

//--------------------------------------------------------------------------------------------------
/**
 * Print the device model identity (Target Hardware Platform).
 */
//--------------------------------------------------------------------------------------------------
void cm_info_PrintDeviceModel
(
    bool withHeaders
)
{
    char model[LE_INFO_MAX_MODEL_BYTES] = {0};

    le_info_GetDeviceModel(model, sizeof(model));

    if(withHeaders)
    {
        cm_cmn_FormatPrint("Device", model);
    }
    else
    {
        printf("%s\n", model);
    }
}

//--------------------------------------------------------------------------------------------------
/**
 * Print the product requirement information (PRI) part number and revision number.
 */
//--------------------------------------------------------------------------------------------------
void cm_info_PrintGetPriId
(
    bool withHeaders
)
{
    char priIdPn[LE_INFO_MAX_PRIID_PN_BYTES] = {0};
    char priIdRev[LE_INFO_MAX_PRIID_REV_BYTES] = {0};

    le_info_GetPriId(priIdPn, LE_INFO_MAX_PRIID_PN_BYTES, priIdRev, LE_INFO_MAX_PRIID_REV_BYTES);

    if(withHeaders)
    {
        cm_cmn_FormatPrint("priIdPn", priIdPn);
        cm_cmn_FormatPrint("priIdRev", priIdRev);
    }
    else
    {
        printf("%s %s\n", priIdPn, priIdRev);
    }
}


//--------------------------------------------------------------------------------------------------
/**
 * Print the product stock keeping unit number (SKU).
 */
//--------------------------------------------------------------------------------------------------
void cm_info_PrintGetSku
(
    bool withHeaders
)
{
    char skuId[LE_INFO_MAX_SKU_BYTES] = {0};

    le_info_GetSku(skuId, LE_INFO_MAX_SKU_BYTES);

    if(withHeaders)
    {
        cm_cmn_FormatPrint("skuId", skuId);
    }
    else
    {
        printf("%s\n", skuId);
    }
}


//--------------------------------------------------------------------------------------------------
/**
 * Process commands for info service.
 */
//--------------------------------------------------------------------------------------------------
void cm_info_ProcessInfoCommand
(
    const char * command,   ///< [IN] Command
    size_t numArgs          ///< [IN] Number of arguments
)
{
    if (strcmp(command, "help") == 0)
    {
        cm_info_PrintInfoHelp();
    }
    else if (strcmp(command, "all") == 0)
    {
        cm_info_PrintDeviceModel(true);
        cm_info_PrintImei(true);
        cm_info_PrintSerialNumber(true);
        cm_info_PrintFirmwareVersion(true);
        cm_info_PrintBootloaderVersion(true);
        cm_info_PrintGetPriId(true);
        cm_info_PrintGetSku(true);
    }
    else if (strcmp(command, "firmware") == 0)
    {
        cm_info_PrintFirmwareVersion(false);
    }
    else if (strcmp(command, "bootloader") == 0)
    {
        cm_info_PrintBootloaderVersion(false);
    }
    else if (strcmp(command, "device") == 0)
    {
        cm_info_PrintDeviceModel(false);
    }
    else if (strcmp(command, "imei") == 0)
    {
        cm_info_PrintImei(false);
    }
    else if (strcmp(command, "fsn") == 0)
    {
        cm_info_PrintSerialNumber(false);
    }
    else if (strcmp(command, "pri") == 0)
    {
        cm_info_PrintGetPriId(false);
    }
    else if (strcmp(command, "sku") == 0)
    {
        cm_info_PrintGetSku(false);
    }
    else
    {
        printf("Invalid command for info service.\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
