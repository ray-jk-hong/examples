#ifndef MTTY_H
#define MTTY_H

int mtty_init(void);
void mtty_uninit(void);
struct device *mtty_get_dev(void);

#endif