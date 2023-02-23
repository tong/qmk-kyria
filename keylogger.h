/**/
//#pragma once

#include <stdio.h>

int get_keylogs_idx(void);
//char code_to_char(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);
