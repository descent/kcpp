#include "services.h"
#include "cpp_support.h"


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
      service_puts("obj ctor\n");
    }
    ~Obj()
    {
      service_puts("obj dtor\n");
    }
  private:
};


static Driver* driver;
// Driver g_driver;
Obj obj;

extern "C" {
	int cpp_init(void);
	void cpp_exit(void);
        void _GLOBAL__sub_I_g_driver();
}

double f(double d);
double f(double d)
{
  return d*=0.1;
}

int cpp_init() {
  volatile double i=0.3;

  i *= 0.5;


  i = f(i);
  service_printk("float: %f\n", i);
  //_GLOBAL__sub_I_g_driver();
  //driver = new Driver();

  driver = 0;
  return(0);
}

void cpp_exit() {
  //delete driver;
  //g_dtor();
}
