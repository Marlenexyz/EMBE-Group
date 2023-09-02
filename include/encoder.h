#include <digital_in.h>
#include <digital_out.h>

class Encoder{
    public:
    int position();
    void init(Digital_in C1, Digital_in C2, Digital_out LED);

    private:
    Digital_in C1;
    Digital_in C2;
    Digital_out LED;
    bool lastState;
    bool currentState;
    int count;
    

    
};