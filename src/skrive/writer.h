#pragma once

#include <string_view>
#include <iostream>
#include <assert.h>

#include "formatter.h"

namespace sk {
    class Writer;
    typedef void(*Printer)(const void* obj, std::string_view fmt, Writer& writer);
    
    struct Arg {
        Printer printer;
        const void* value_ptr;
    };

    struct Args {
        size_t size;
        Arg* args;
    };

    class Writer {
    public:
        Writer(std::ostream& stream);

    public:
        void write(const char* s, Format fmt = {});
        void write(size_t n, const char* s, Format fmt = {});

        void write(bool b, Format fmt = {});

        void write(char c, Format fmt = {});

        void write(int16_t d, Format fmt = {});
        void write(int32_t d, Format fmt = {});
        void write(int64_t d, Format fmt = {});
        void write(uint16_t d, Format fmt = {});
        void write(uint32_t d, Format fmt = {});
        void write(uint64_t d, Format fmt = {});
        void write(size_t d, Format fmt = {});
        
        void write(float f, Format fmt = {});
        void write(double f, Format fmt = {});
        
        void write(void* p, Format fmt = {});

        void flush();

        void print(const char* fmt, Args args);
        void println(const char* fmt, Args args);

        template<typename... Ts>
        void print(const char* fmt, const Ts&... args) {
            if constexpr (sizeof...(Ts) == 0) {
                write(fmt);
            } else {
                auto packed = Args {
                    sizeof...(Ts),
                    new Arg[sizeof...(Ts)]{ { reinterpret_cast<Printer>(Formatter<Ts>::format), &args }... }
                };

                print(fmt, packed);

                delete[] packed.args;
            }
        }

        template<typename... Ts>
        void println(const char* fmt, const Ts&... args) {
            if constexpr (sizeof...(Ts) == 0) {
                write(fmt);
                write('\n');
            } else {
                auto packed = Args {
                    sizeof...(Ts),
                    new Arg[sizeof...(Ts)]{ { reinterpret_cast<Printer>(Formatter<Ts>::format), &args }... }
                };

                println(fmt, packed);

                delete[] packed.args;
            }
        }

    private:
        std::ostream& stream;
    };
}
