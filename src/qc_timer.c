#include "qc_timer.h"
#include "qc_uart.h"
#include "qurt_timetick.h"


qapi_TIMER_handle_t timer_handle;
qapi_TIMER_define_attr_t timer_def_attr;
qapi_TIMER_set_attr_t timer_set_attr;

qapi_Status_t status = QAPI_OK;

int volatile cnt = 0;
extern int volatile mode;
void cb_timer(uint32_t data)
{
	
	
	cnt++;
	if(cnt == 10)
	{

		mode = 1; 
		cnt = 0;

	}
	cnt &= 0xffffffff;
	
}

int timer_utils_init(){

    memset(&timer_def_attr, 0, sizeof(timer_def_attr));
	timer_def_attr.cb_type	= QAPI_TIMER_FUNC1_CB_TYPE;
	timer_def_attr.deferrable = false;
	timer_def_attr.sigs_func_ptr = cb_timer;
	timer_def_attr.sigs_mask_data = 0x11;
	status = qapi_Timer_Def(&timer_handle, &timer_def_attr);


    memset(&timer_set_attr, 0, sizeof(timer_set_attr));
	timer_set_attr.reload = 1;
	timer_set_attr.time = 1;
	timer_set_attr.unit = QAPI_TIMER_UNIT_SEC;
	status = qapi_Timer_Set(timer_handle, &timer_set_attr);

    return status;
}

unsigned int millis(void)
{

return qurt_timer_get_ticks() / 19200;

}








