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

struct Matrix3x3 {
    float components[3*3];
};

template<> struct sk::Formatter<Matrix3x3> {
    static void format(const Matrix3x3& mat, std::string_view, sk::Writer& writer) {
        const char* fmt =
            "┌{: g} {: g} {: g} ┐\n"
            "│{: g} {: g} {: g} │\n"
            "└{: g} {: g} {: g} ┘";

        writer.print(fmt, 
            mat.components[0], mat.components[1], mat.components[2],
            mat.components[3], mat.components[4], mat.components[5],
            mat.components[6], mat.components[7], mat.components[8]
        );
    }
};

void test_noargs() {
    std::string result = sk::format("hello, world!");
    assert(result == "hello, world!");

    std::cout << __func__ << " passed!\n";
}

void test_1_primitive() {
    std::string result = sk::format("the number is {}", 69);
    assert(result == "the number is 69");

    std::cout << __func__ << " passed!\n";
}

void test_1_custom() {
    auto vec = Vector2{ 3.1f, 9.9f };
    std::string result = sk::format("The vector is {}", vec);
    assert(result == "The vector is (3.1, 9.9)");

    std::cout << __func__ << " passed!\n";
}

void test_positional_args() {
    std::string result = sk::format("{0:04}-{1:04}-{0:04}-{1:04}", 0, 1);
    assert(result == "0000-0001-0000-0001");

    std::cout << __func__ << " passed!\n";
}

void test_complex_format() {
    std::string r1 = sk::format("x: {:>5}", true);
    std::string r2 = sk::format("y: {:>5}", false);

    assert(r1 == "x:  true");
    assert(r2 == "y: false");

    std::cout << __func__ << " passed!\n";
}

void test_sign() {
    // omitted
    {
        std::string zero = sk::format("{}", 0);
        std::string positive = sk::format("{}", 1);
        std::string negative = sk::format("{}", -1);

        assert(zero == "0");
        assert(positive == "1");
        assert(negative == "-1");
    }

    // both
    {
        std::string zero = sk::format("{:+}", 0);
        std::string positive = sk::format("{:+}", 1);
        std::string negative = sk::format("{:+}", -1);

        assert(zero == "+0");
        assert(positive == "+1");
        assert(negative == "-1");
    }

    // negative
    {
        std::string zero = sk::format("{:-}", 0);
        std::string positive = sk::format("{:-}", 1);
        std::string negative = sk::format("{:-}", -1);

        assert(zero == "0");
        assert(positive == "1");
        assert(negative == "-1");
    }

    // space
    {
        std::string zero = sk::format("{: }", 0);
        std::string positive = sk::format("{: }", 1);
        std::string negative = sk::format("{: }", -1);

        assert(zero == " 0");
        assert(positive == " 1");
        assert(negative == "-1");
    }

    std::cout << __func__ << " passed!\n";
}

void test_sign_with_fill_and_width() {
    // omitted
    {
        std::string zero = sk::format("{:04}", 0);
        std::string positive = sk::format("{:04}", 1);
        std::string negative = sk::format("{:04}", -1);

        assert(zero == "0000");
        assert(positive == "0001");
        assert(negative == "-001");
    }

    // both
    {
        std::string zero = sk::format("{:+04}", 0);
        std::string positive = sk::format("{:+04}", 1);
        std::string negative = sk::format("{:+04}", -1);

        assert(zero == "+000");
        assert(positive == "+001");
        assert(negative == "-001");
    }

    // negative
    {
        std::string zero = sk::format("{:-04}", 0);
        std::string positive = sk::format("{:-04}", 1);
        std::string negative = sk::format("{:-04}", -1);

        assert(zero == "0000");
        assert(positive == "0001");
        assert(negative == "-001");
    }

    // space
    {
        std::string zero = sk::format("{: 04}", 0);
        std::string positive = sk::format("{: 04}", 1);
        std::string negative = sk::format("{: 04}", -1);

        assert(zero == " 000");
        assert(positive == " 001");
        assert(negative == "-001");
    }

    std::cout << __func__ << " passed!\n";
}

void example_working_with_stdin() {
    sk::print("Please enter your name: ");
    std::string name;
    std::getline(std::cin, name);
    sk::println("Hello, {}!", name);  

    std::cout << __func__ << " passed!\n";
}

void example_printing_matrix() {
    Matrix3x3 mat3;
    mat3.components[0] = 3;
    mat3.components[1] = -7;
    mat3.components[2] = 0;
    mat3.components[3] = 9;
    mat3.components[4] = -1;
    mat3.components[5] = 4;
    mat3.components[6] = 5;
    mat3.components[7] = 8;
    mat3.components[8] = -2;

    sk::println("{}", mat3);
}

int main() {
    //* Tests
    std::cout << "\nRunning Tests:\n";
    test_noargs();
    test_1_primitive();
    test_1_custom();
    test_positional_args();
    test_complex_format();
    test_sign();
    // test_sign_with_fill_and_width();
    //*/

    //* Examples
    std::cout << "\nRunning Examples:\n";
    // example_working_with_stdin();
    example_printing_matrix();
    //*/

    return 0;
}
