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
Driver g_driver;
Obj obj;

extern "C" {
	int cpp_init(void);
	void cpp_exit(void);
        void _GLOBAL__sub_I_g_driver();
}

int cpp_init() {
  _GLOBAL__sub_I_g_driver();
  driver = new Driver();

  return(0);
}

void cpp_exit() {
	delete driver;
  g_dtor();
}
