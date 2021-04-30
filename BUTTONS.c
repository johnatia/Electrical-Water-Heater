    /*
 * File:   BUTTONS.c
 * Author: JOHN_ATIA
 *
 * Created on 14/7/2020
 */


#include <xc.h>
#include"BUTTONS.h"

void Buttons_INIT(void)
{
    UP_Button_TRIS      =   ON ;        //set UP Button as INPUT
    DOWN_Button_TRIS    =   ON ;        //set DOWN Button as INPUT
}
