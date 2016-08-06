#include "io.h"

namespace TECOS
{

    uint32_t IO::MailboxRead(uint8_t _Channel)
    {

        uint32_t data = 0,
                 count = 0;

        while(true)
        {
            //oczekiwanie na pojawienie sie w rejestrze statusu flagi mailbox empty

            while(Read32(IO_REGISTER::MAILBOX_STATUS) & 0x40000000)
            {
                if(count++ >= (1 << 20))
                {
                    return 0xFFFFFFFF;
                }

            }

            //synchronizacja pamieci
            Memory::Barrier();

            //odczyt danych z mailbox
            data = Read32(IO_REGISTER::MAILBOX_READ);

            //synchronizacja pamieci
            Memory::Barrier();

            //sprawdzenie czy 4 najmniej znaczace bity odpowiadaja numerowi kanalu
            if((data & 0xF) == _Channel) //jezeli tak to konczymy odczytywanie
                break;
        }

        //dane zapisane sa w pozostalych 28 bitach
        return (data & 0xFFFFFFF0);
    }

    void IO::MailboxWrite(uint8_t _Channel, uint32_t _Data)
    {
        //oczekiwanie na pojawienie sie statustu flagi mailbor full
        while(Read32(IO_REGISTER::MAILBOX_STATUS) & 0x80000000)
        {
        }

        //synchronizacja pamieci
        Memory::Barrier();

        //zapisanie danych z mailbox
        //data = Read32(IO_REGISTER::MAILBOX_WRITE, _Channel | (_Data & 0xFFFFFFF0));
        Write32(IO_REGISTER::MAILBOX_WRITE, _Channel | (_Data & 0xFFFFFFF0));

        //synchronizacja pamieci
        Memory::Barrier();

    }


}
