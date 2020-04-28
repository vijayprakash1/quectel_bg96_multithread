/*
*@file    app.c
*@brief   this file contains all the tast entry function
*
*  ---------------------------------------------------------------------------
*
*  Copyright (c) 2020 Vijay Prakash.
*  All Rights Reserved.
*  Confidential and Proprietary - Vijay Prakash (Lazy Smart)
*/

#include "qapi_timer.h"
#include "txm_module.h"



#include "qc_uart.h"




#define TASK_BYTE_POOL_SIZE (128 * 8 * 1024)
UINT byte_pool_remaining = TASK_BYTE_POOL_SIZE;
TX_BYTE_POOL *byte_pool_task = NULL;
char free_memory_for_task[TASK_BYTE_POOL_SIZE];


int qc_create_byte_pool()
{
    int ret = TX_SUCCESS;
    /*Creating Byte Pool*/
    //Function Definition:  txm_module_object_allocate((VOID **) obj_ptr, ULONG object_size)
    ret += txm_module_object_allocate(&byte_pool_task, sizeof(TX_BYTE_POOL));
    if (ret != TX_SUCCESS)
    {
        return ret;
    }
    /*Allocates memory to the created Byte Pool*/
    //Function Definition:  tx_byte_pool_create(TX_BYTE_POOL* pool_ptr, char* name_ptr, void* pool_start, ULONG pool_size)
    ret += tx_byte_pool_create(byte_pool_task, "Application Pool", free_memory_for_task, TASK_BYTE_POOL_SIZE);
    if (ret != TX_SUCCESS)
    {
       
        return ret;
    }
    else
    return ret;
    /*Creation of Byte Pool Successful*/
}

int quectel_task_entry(void)
{

    qapi_Timer_Sleep(10, QAPI_TIMER_UNIT_SEC, true); // Necessary Incase you using QEFS to flash code
    qc_create_byte_pool();
    _log_setup();
    while (1)
    {
        _log("Lets Start the Adventure");
        qapi_Timer_Sleep(10, QAPI_TIMER_UNIT_SEC, true);

    }
}
