#include <iostream>
/**
* Date: 2023-2-23 21:00
* Author: qiang
* Dsecription: this demo introduces how to use the pointer of class member function
* 
*  g++ class_func_opt.cpp -o func
*/
class Demo {

public:
    Demo(){};
    virtual ~Demo() {};

public:
    enum CaseListNo{
        CASE_0 = 0,
        CASE_1,
        CASE_2
    };

    enum CaseStatus {
        CASE_SUCCESS  = 0,
        CASE_FAIL
    };

public:
    void Run(int no, int param);
    int TestCase_0(int param);
    int TestCase_1(int param);
    int TestCase_2(int param);
};

static int (Demo::*RunCaseFunc[])(int) = {
    [Demo::CASE_0]  = &Demo::TestCase_0,
    [Demo::CASE_1]  = &Demo::TestCase_1,
    [Demo::CASE_2]  = &Demo::TestCase_2
};


int Demo::TestCase_0(int param)
{
    std::cout << "test_case_0" <<std::endl;
    return CASE_SUCCESS;
}

int Demo::TestCase_1(int param)
{
    std::cout << "test_case_1" <<std::endl;
    return CASE_SUCCESS;
}

int Demo::TestCase_2(int param)
{
    std::cout << "test_case_2" <<std::endl;
    return CASE_SUCCESS;
}

void Demo::Run(int no, int param)
{   
    (this->*RunCaseFunc[no])(param);
}

int main(int argc, char *argv[])
{
    std::cout << "Demo" <<std::endl;
    Demo *pDemo = new Demo();
    int a = 3;
    for (int i = 0; i < 3; i++) {
        pDemo->Run(i, a);
    }
    return 0;
}
