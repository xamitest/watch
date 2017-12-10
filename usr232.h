#include <cortexm3_macro.h>

extern void initUSR232(void);
extern void SendtoServer(u8 i);
extern u8 FillBuff(void);
extern u8 CheckOK(vu8* buf);
extern vu16 SostUSR;
extern vu16 ComTimeUSR;
extern vu8 ErrCountUSR;

extern const u8 HTTPPHtempl[];
extern vu8 POST_Len;
extern vu16 Data_Len;
extern vu8 Data[];
extern vu8 POST[1024];