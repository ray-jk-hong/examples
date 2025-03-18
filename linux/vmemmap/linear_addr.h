#ifndef LINEAR_ADDR_H
#define LINEAR_ADDR_H

#define __AC(X,Y)   (X##Y)
#define _AC(X,Y)    __AC(X,Y)
#define _UL(x)      (_AC(x, UL))
#define UL(x)       _UL(x)

#endif
