#include <iostream>
#include <vector>

#include "skrive.h"

struct Vector2 {
    float x, y;
};

template<> struct sk::Formatter<Vector2> {
    static void format(const Vector2& vec, std::string_view fmt, sk::Writer& writer) {
        writer.print("({:g}, {:g})", vec.x, vec.y);
    }
};

int main(void) {
    sk::print("Hello there, {}\n", 69);

    auto vec = Vector2{ 3.1f, 9.9f };
    sk::print("The vector is {}\n", vec);

    sk::println("Hello, skrive!!!");

    sk::println("{} + {} = {}", 1, 2, 1 + 2);

    sk::eprint("[ERR]: The error was ");
    sk::eprintln("something terrible!");

    sk::print("{0:04}-{1:04}-{0:04}-{1:04}\n", 0, 1);

    std::vector<int> ints = { 1, 2, 3, 4, 5 };
    sk::println("ints = {:#}", ints);

    sk::println("Is it true? {:C}", true);

    sk::println("Balance: ${:.2}", 565.34f);

    sk::println("Vector2{{ {:.1}, {:.1} }} = {}", vec.x, vec.y, vec);

    sk::print("Please enter your name: ");
    std::string name;
    std::getline(std::cin, name);
    sk::println("Hello, {}!", name);

    sk::println("x: {:>5}", true);
    sk::println("y: {:>5}", false);

    return 0;
}
