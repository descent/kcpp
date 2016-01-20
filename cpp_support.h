#ifndef CPP_SUPPORT_H
#define CPP_SUPPORT_H


extern void *__dso_handle;

struct DObjs
{
  void (*dtor_) (void *);
  void *arg_;
  void *dso_handle_;
};

extern "C"
{
  int  __cxa_atexit(void (*)(void*), void*, void* );
}

void g_dtor();

#endif
