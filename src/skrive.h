#pragma once

#include "skrive/formatter-hk.h"
#include <sstream>

namespace sk {
    inline Writer out = Writer{ std::cout };
    inline Writer err = Writer{ std::cerr };

    template<typename... Ts>
    void print(const char* fmt, const Ts&... args) {
        out.print(fmt, args...);
    }

    template<typename... Ts>
    void println(const char* fmt, const Ts&... args) {
        out.println(fmt, args...);
    }

    template<typename... Ts>
    void eprint(const char* fmt, const Ts&... args) {
        err.print(fmt, args...);
    }

    template<typename... Ts>
    void eprintln(const char* fmt, const Ts&... args) {
        err.println(fmt, args...);
    }

    void print(const char* fmt, Args args) {
        out.print(fmt, args);
    }

    void println(const char* fmt, Args args) {
        out.println(fmt, args);
    }

    void eprint(const char* fmt, Args args) {
        err.print(fmt, args);
    }

    void eprintln(const char* fmt, Args args) {
        err.println(fmt, args);
    }

    template<typename... Ts>
    std::string format(const char* fmt, const Ts&... args) {
        std::stringstream ss;
        auto writer = Writer{ ss };
        writer.print(fmt, args...);
        return ss.str();
    }

    std::string format(const char* fmt, Args args) {
        std::stringstream ss;
        auto writer = Writer{ ss };
        writer.print(fmt, args);
        return ss.str();
    }
}
