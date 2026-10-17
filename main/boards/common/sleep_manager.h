#ifndef SLEEP_MANAGER_H
#define SLEEP_MANAGER_H

#include <cstdint>

// 睡眠源标记（用于精细防休眠，当前为桩实现，实际休眠由 PowerSaveTimer 控制）
enum class SleepBusySrc {
    Display,
    Audio,
    Network,
    Other,
};

inline void sm_kick(uint32_t kick_ms, const char* reason) {
    (void)kick_ms;
    (void)reason;
}

inline void sm_set_busy(SleepBusySrc src, bool busy) {
    (void)src;
    (void)busy;
}

#endif  // SLEEP_MANAGER_H
