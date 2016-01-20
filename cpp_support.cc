#include "cpp_support.h"
#include "services.h"


void *__dso_handle;
static int obj_count=0;
static const int DOBJS_SIZE = 10;
DObjs dobjs_vec[DOBJS_SIZE];

/* to satisfy the kernel dynamic linker */
/* These are only needed if you dont supply flags
to the compiler to remove exception handling, run time
type information and the like... */
int __gxx_personality_v0;
int _Unwind_Resume;
//int _GLOBAL_OFFSET_TABLE_;

/* support code for new and delete */
void *operator new(unsigned int x) {
	return(service_malloc(x));
}


void operator delete(void *pointer) {
	service_free(pointer);
}


extern "C"
{
  int __cxa_atexit(void (*destructor) (void *), void *arg, void *__dso_handle)
  {
    DObjs dobj;

    dobj.dtor_ = destructor;
    dobj.arg_ = arg;
    dobj.dso_handle_ = __dso_handle;

    if (obj_count >= DOBJS_SIZE)
    {
      return -1;
    }
    dobjs_vec[obj_count] = dobj;
    ++obj_count;

    return 0;
  }

  int __aeabi_atexit (void *arg, void (*func) (void *), void *d);
  int __aeabi_atexit (void *arg, void (*func) (void *), void *d)
  {
    return __cxa_atexit (func, arg, d);
  }
}
