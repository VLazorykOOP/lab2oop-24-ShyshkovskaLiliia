#include <iostream>

int main() {
    int a, b, c, d;
    std::cout << "Enter values for a, b, c, d: ";
    std::cin >> a >> b >> c >> d;

    int x = (b << 8) + (b << 5) + (b << 3) + (b << 2) + b // 303 * b = (256 + 32 + 8 + 4 + 2 + 1) * b
               + (((d << 4) - d + (c << 3) + (c << 2)) >> 9) // (d * 15 + c * 12) / 512
               - ((a << 6) + a) // 65 * a = (64 + 1) * a
               + ((d << 4) - (d << 1)) + d; // d * 14 = (16 - 2) * d

    std::cout << "Result: " << x << std::endl;
    return 0;
}
