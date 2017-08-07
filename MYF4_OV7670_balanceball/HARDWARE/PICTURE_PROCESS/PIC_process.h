#ifndef __PIC_PROCESS_H
#define __PIC_PROCESS_H
#include "sys.h"
#include "Figure.h"

#define LENGTH 160
#define HEIGHT 120

//extern u8 frame_data[LENGTH][HEIGHT];
extern u8 blackline[HEIGHT][3];
extern u8 whiteline;
void picture_filter(void);
void get_blackline(void);
void blackline_filter(void);
void get_blackmid(void);
void blackmid_continue(void);
u16 my_abs(int canshu);
#endif
