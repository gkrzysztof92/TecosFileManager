
#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#include <iostream>
#include "arch.h"

namespace TECOS
{
    enum class OUTPUT_TYPE
    {
        UART

    };

    class OUTPUT_BUFFER_UART : public std::streambuf
    {

        protected:
            virtual int_type overflow(int_type _Character = traits_type::eof())
            {
                Output.PutChar(_Character);

                return _Character;
            }
        private:
            UART Output;
    };



    template <typename charT, typename traits>
    std::basic_ostream<charT, traits>& endl(std::basic_ostream<charT,traits>& os)
    {
        os.put('\r');
        os.put('\n');

        return os.flush();
    }


    void SetOutput(const OUTPUT_TYPE& _Output_type);
}

#endif // __OUTPUT_H__
