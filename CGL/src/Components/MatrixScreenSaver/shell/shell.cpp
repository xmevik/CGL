#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>

namespace
{
    int Parameters[20];

} // namespace


namespace shell
{
    void CheckForActivity()
    {
        // Loading vait time

        int _vait_time = 0;

        std::ifstream configin;
        configin.open("config.txt");

        if (configin.is_open())
        {
            std::string line;

            getline(configin, line);
            getline(configin, line);

            char value[10] = {};

            for (int i = 0; i <= line.size(); i++)
            {

                if (line[i + 1] == ':')
                    break;

                value[i] = line[i];
            }

            _vait_time = atoi(value);
        }

        configin.close();

        // Activity check itself

        int _inactive_time = 0;
        POINT _old_cursorpos, _new_cursorpos;
        GetCursorPos(&_old_cursorpos);
        while (true)
        {
            if (_inactive_time >= _vait_time) // Time before screensaver activation in seconds
                return;

            GetCursorPos(&_new_cursorpos);

            if (_old_cursorpos.x == _new_cursorpos.x && _old_cursorpos.y == _new_cursorpos.y) //Keyboard activity check doesn't work/Need to re-write
            {
                _inactive_time++;
            }
            else
            {
                _old_cursorpos = _new_cursorpos;
                _inactive_time = 0;
            }
            Sleep(1000);

        }

    }

    int* LoadConfig()
    {
        std::ifstream configin;
        configin.open("config.txt");

        if (configin.is_open())
        {
            std::string line;
            for (int i = 0; getline(configin, line); i++)
            {
                if (i == 0 || i == 1)
                    continue;

                char value[10] = {};

                for (int j = 0; j <= line.size(); j++)
                {
                    if (line[j + 1] == ':')
                        break;

                    value[j] = line[j];
                }

                Parameters[i] = atoi(value);
            }
        }
        else
        {
            Parameters[0] = -1;
        }

        configin.close();

        return Parameters;
    }


    int CheckConfigValues(int* checking)
    {

        if (checking[0] == -1) // Missing config.txt
            return -1;

        if (checking[2] != 0) // Check for video
        {
            return 2;
        }

        if (checking[3] > 255 || checking[3] < 0) // Check transparency
            return 3;

        if (checking[4] < 3) // Check chance
            return 4;

        for (int i = 5; i <= 6; i++) // Check dealys
            if (checking[i] < 0)
                return i;

        return 0;
    }

}
