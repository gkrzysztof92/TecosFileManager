#include "output.h"

namespace TECOS
{

    void SetOutput(const OUTPUT_TYPE& _OutputType)
    {
        if(_OutputType == OUTPUT_TYPE::UART)
        {
            static OUTPUT_BUFFER_UART output_buffer;

            std::cout.rdbuf(&output_buffer);
        }
    }
}
