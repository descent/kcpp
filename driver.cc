#include "services.h"
#include "cpp_support.h"

#define TEST_VF

class Driver {
public:
	int x;
	Driver() {
		service_puts("inside constructor!\n");
	}
	~Driver() {
		service_puts("inside destructor!\n");
	}
};

class Obj 
{
  public:
    Obj()
    {
      //service_puts("obj ctor\n");
      id_ = self_id_;
      service_printk("%d ## obj ctor\n", id_);
      ++self_id_;
    }
    ~Obj()
    {
      //service_puts("obj dtor\n");
      --self_id_;
      service_printk("obj dtor: %d\n", id_);
    }
  private:
    static int self_id_;
    int id_;
};

int Obj::self_id_=0;



class BaseClass
{
  public:
    BaseClass(int base=5): base_(base)
    {
      service_puts("BaseClass\n");
    }
    virtual void vfunc()
    {
      service_puts("BaseClass vfunc\n");
    }
#ifdef TEST_VF
    virtual void pf()=0;
#endif
  private:
    int base_;
};


class DeriveClass : public BaseClass
{
  public:
    DeriveClass(int d=10): BaseClass(99), d_(d)
    {
      service_puts("DeriveClass\n");
    }
    virtual void vfunc()
    {
      service_puts("DeriveClass vfunc\n");
    }
    virtual void pf()
    {
      service_puts("DeriveClass pure vfunc\n");
    }
  private:
    int d_;
};


static Driver* driver;
Driver g_driver;
Obj obj[10];

extern "C" 
{
  int cpp_init(void);
  void cpp_exit(void);
  void _GLOBAL__sub_I_g_driver();
  void _GLOBAL__sub_I__ZN3Obj8self_id_E();
}

int cpp_init() 
{
#ifdef TEST_VF
  BaseClass *bp = 0;
#else
  BaseClass *bp = new BaseClass();
#endif
  DeriveClass *dp = new DeriveClass();

#ifndef TEST_VF
  service_puts("base vfunc\n");
  bp->vfunc();
#endif
  bp = dp;
  service_puts("derive vfunc\n");
  bp->vfunc();

  //_GLOBAL__sub_I_g_driver();
  _GLOBAL__sub_I__ZN3Obj8self_id_E();
  driver = new Driver();

  return(0);
}

void cpp_exit() {
	delete driver;
  g_dtor();
}
