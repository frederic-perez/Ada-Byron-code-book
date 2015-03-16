// -- 

// Unfortulately __func__ is not understood by vs12. This is a workaround:
#ifndef __func__
#define __func__ __FUNCTION__
#endif

// -- eof
