#include <sys/types.h>
#include <stddef.h>
#include <stdio.h>
#include <errno.h>

caddr_t sbrk(int incr) {
  errno = ENOMEM;
  return (caddr_t)-1;
}
