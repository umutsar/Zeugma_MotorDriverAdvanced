
#include "old_value_hall.h"

void set_old_value()
{

    if (!geri_vites)
    { // İLERİ YÖN ADIMLARI

        if ((hall_A && !hall_B && hall_C) &&
            ((oldValue[0] && !oldValue[1] && !oldValue[2]) || flagg))
        // 101'den 100'e geçiş
        {
            step = 4;
            oldValue[0] = 1;
            oldValue[1] = 0;
            oldValue[2] = 1;
            flagg = 0;
        }
        else if ((hall_A && !hall_B && !hall_C) &&
                 ((oldValue[0] && oldValue[1] && !oldValue[2]) || flagg)) // 100'den 110'a geçiş
        {
            step = 5;
            oldValue[0] = 1;
            oldValue[1] = 0;
            oldValue[2] = 0;
            flagg = 0;
        }
        else if ((hall_A && hall_B && !hall_C) &&
                 ((!oldValue[0] && oldValue[1] && !oldValue[2]) || flagg)) // 110'dan 010'a geçiş
        {
            step = 6;
            oldValue[0] = 1;
            oldValue[1] = 1;
            oldValue[2] = 0;
            flagg = 0;
        }
        else if ((!hall_A && hall_B && !hall_C) &&
                 ((!oldValue[0] && oldValue[1] && oldValue[2]) || flagg)) // 010'dan 011'e geçiş
        {
            step = 1;
            oldValue[0] = 0;
            oldValue[1] = 1;
            oldValue[2] = 0;
            flagg = 0;
        }
        else if ((!hall_A && hall_B && hall_C) &&
                 ((!oldValue[0] && !oldValue[1] && oldValue[2]) || flagg)) // 011'den 001'e geçiş
        {
            step = 2;
            oldValue[0] = 0;
            oldValue[1] = 1;
            oldValue[2] = 1;
            flagg = 0;
        }
        else if ((!hall_A && !hall_B && hall_C) &&
                 ((oldValue[0] && !oldValue[1] && oldValue[2]) || flagg)) // 001'den 101'e geçiş
        {
            step = 3;
            oldValue[0] = 0;
            oldValue[1] = 0;
            oldValue[2] = 1;
            flagg = 0;
        }
    }

    else // Geri yon
    {
        if ((hall_A && !hall_B && hall_C) && ((!oldValue[0] && !oldValue[1] && oldValue[2]) || flagg))
        { // 010
            step = 1;
            oldValue[0] = 1;
            oldValue[1] = 0;
            oldValue[2] = 1;
            flagg = 0;
        }
        if ((hall_A && !hall_B && !hall_C) && ((oldValue[0] && !oldValue[1] && oldValue[2]) || flagg))
        { // 011
            step = 2;
            oldValue[0] = 1;
            oldValue[1] = 0;
            oldValue[2] = 0;
            flagg = 0;
        }
        if ((hall_A && hall_B && !hall_C) && ((oldValue[0] && !oldValue[1] && !oldValue[2]) || flagg))
        { // 001
            step = 3;
            oldValue[0] = 1;
            oldValue[1] = 1;
            oldValue[2] = 0;
            flagg = 0;
        }
        if ((!hall_A && hall_B && !hall_C) && ((oldValue[0] && oldValue[1] && !oldValue[2]) || flagg))
        { // 101
            step = 4;
            oldValue[0] = 0;
            oldValue[1] = 1;
            oldValue[2] = 0;
            flagg = 0;
        }
        if ((!hall_A && hall_B && hall_C) && ((!oldValue[0] && oldValue[1] && !oldValue[2]) || flagg))
        { // 100
            step = 5;
            oldValue[0] = 0;
            oldValue[1] = 1;
            oldValue[2] = 1;
            flagg = 0;
        }
        if ((!hall_A && !hall_B && hall_C) && ((!oldValue[0] && oldValue[1] && oldValue[2]) || flagg))
        { // 110
            step = 6;
            oldValue[0] = 0;
            oldValue[1] = 0;
            oldValue[2] = 1;
            flagg = 0;
        }
    }
}

