
#include <lib/number.h>
#include <iostream>


int main() {
    uint2022_t value1,  value2;

    // parse int
    uint32_t temp = 23;
    value1 = from_uint(temp);
    std::cout << "parse from int: " << value1 << std::endl;

    // parse char
    value2 = from_string("354634563456");
    std::cout << "parse from char: " << value2 << "\n";

    // add two uint2022_t
    value1 = from_string("2938475289345289345");
    value2 = from_string("999999999999999999999");
    std::cout << "add: " << value1 << " " << value2 << " ";
    value1 = value1 + value2;
    std::cout << value1 << "\n";

    // diff two unit2022_t
    value1 = from_string("25234095209435820523094520935209345");
    value2 = from_string("22908234905823409809524382093408952");
    std::cout << "diff: " << value1 << " " << value2 << " ";
    value1 = value1 - value2;
    std::cout << value1 << "\n";

    //mull two unit2022_t
    value1 = from_string("90062345233532253222");
    value2 = from_string("2677840070560517533");
    std::cout << "mul: " << value1 << " " << value2 << " ";
    value1 = value1 * value2;
    std::cout << value1 << "\n";

    //div two uint2022_t
    value1 = from_string("134643456436544563651566133654615465341646341556");
    value2 = from_string("23654265344565234465524");
    std::cout << "div: " << value1 << " " << value2 << " ";
    value1 = value1 / value2;
    std::cout << value1 << "\n";
    return 0;
}
