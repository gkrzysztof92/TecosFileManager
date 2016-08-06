#include "time.h"

namespace TECOS
{
    TIMER* TIME::SYSTEM_TIMER = reinterpret_cast<TIMER*>(IO_REGISTER::TIMER_BASE);
}
