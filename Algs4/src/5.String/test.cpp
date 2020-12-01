#include <string>
#include <iostream>
#include <vector>


class Test {
public:
    explicit Test(int val) :
        value(val) {}

    int get() const {
        return value;
    }

private:
    int value;
};


int main(void)
{
    Test test(42);
    std::cout << test.get() << std::endl;
    return 0;
}