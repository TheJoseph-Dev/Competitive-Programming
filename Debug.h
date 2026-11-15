#ifdef DEBUG_H
    #include <iostream>
    #include <cstring>
    #define dbgf(fmt, x) printf("| " #x " = " fmt "\n", (x))

    #define p_vi(v) do { printf("[ "); for(ll e : v) printf("%lld ", e); puts("]"); } while(0)
    #define dbgvi(v) do { printf(#v " = "); p_vi(v); } while(0)
    #define dbgmi(mtx, rows) do { puts("[" #mtx "] ="); for(int i = 0; i < rows; ++i) p_vi(mtx[i]); } while(0)

    #define p_v(v) do { printf("[ "); for(auto e : v) std::cout << e << " "; puts("]"); } while(0)
    #define dbgv(v) do { printf(#v " = "); p_v(v); } while(0)
    #define dbgm(m) do { puts("[" #m "] ="); for(auto r : m) p_v(r); } while(0)
    #define dbg(...) do { __f(#__VA_ARGS__, __VA_ARGS__); } while(0)
    template <typename Arg1>
    void __f(const char *name, Arg1 &&arg1) { std::cout << name << ": " << arg1 << std::endl; }
    template <typename Arg1, typename... Args>
    void __f(const char *names, Arg1 &&arg1, Args &&... args) {
        const char *comma = strchr(names + 1, ',');
        std::cout.write(names, comma - names) << ": " << arg1 << " |";
        __f(comma + 1, args...);
    }

    #define dbg2(...) __f2(#__VA_ARGS__, __VA_ARGS__)
    template<typename... Args>
    void __f2(const char* names, Args&&... args) {
        std::cout << "[ " << names << " ] = [ ";
        ((std::cout << args << " "), ... );  // C++17 fold expression
        std::cout << "]\n";
    }

    #define dbgbin(n) do { printf(#n " = "); for(int i = 31 - __builtin_clz(n); i >= 0; i--) putchar(((n>>i)&1)+'0'); putchar('\n'); } while(0)
#else
    #define dbgf(fmt, x)
    #define p_vi(v)
    #define dbgvi(v)
    #define dbgmi(mtx, rows)
    #define p_v(v)
    #define dbgv(v)
    #define dbgm(m)
    #define dbg(...)
    #define dbg2(...)
    #define dbgbin(n)
#endif