#include <time.h>
#include "threads.h"

namespace thread
{
    void GraphicsEventThread(LPVOID RawInput)
    {
        matrix::GraphicsParam* Input = reinterpret_cast<matrix::GraphicsParam*>(RawInput);

        Sleep(2000);

        matrix::StartMessageEvent(Input->hdc, Input->Horzres, Input->Vertres);

        matrix::GreenTextEvent(Input->hdc, Input->Horzres, Input->Vertres, Input->Parameters[5]);

        while (true)
        {
#pragma warning( disable : 4244 )
            srand(time(NULL));
            int chance = rand() % Input->Parameters[4];

            switch (chance)
            {
            case 1:
            {
                matrix::NeoEvent(Input->hdc, Input->Horzres, Input->Vertres, Input->Parameters[7]);

                matrix::GreenTextEvent(Input->hdc, Input->Horzres, Input->Vertres, Input->Parameters[5]);
                break;
            }
            case 2:
            {
                matrix::RandomLettersEvent(Input->hdc, Input->Horzres, Input->Vertres, Input->Parameters[6], Input->Parameters[7]);

                matrix::GreenTextEvent(Input->hdc, Input->Horzres, Input->Vertres, Input->Parameters[5]);
                break;
            }
            default:
            {
                matrix::GreenTextEvent(Input->hdc, Input->Horzres, Input->Vertres, Input->Parameters[5]);

                break;
            }
            }
        }

        ExitThread(0);
    }
}
