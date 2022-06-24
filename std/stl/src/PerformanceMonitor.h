#pragma once
#include <chrono>

class PerfMonitor
{
private:
    using SteadyClock  = std::chrono::steady_clock;
    using HighResClock = std::chrono::high_resolution_clock;
    using TimePoint    = std::chrono::time_point<SteadyClock>;

    TimePoint start;
    TimePoint end;

public:
    PerfMonitor(): start(), end() { }
    ~PerfMonitor() { }

    void Start(){
        start = HighResClock::now();
    }
    void End(){
        end = HighResClock::now();
    }

    // get the duration - default as milliseconds
    //      you can get as a different unit by using the type parameter
    //          pm.Duration<std::micro>()
    template<class Dur = std::milli, intmax_t _Nx = Dur::num, intmax_t _Dx = Dur::den,
             std::enable_if_t< std::is_same_v<Dur, std::ratio<_Nx, _Dx>>, bool > = true>
    auto Duration() {
        return std::chrono::duration<double, Dur>(end - start).count();
    }
};