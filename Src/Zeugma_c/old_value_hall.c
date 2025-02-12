
#include "old_value_hall.h"
#include "main.h"
#include "usbd_cdc_if.h"
#include "usb_device.h"

uint8_t counter = 0;
uint8_t sender_flag = 0;

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
            flagg = 1;
        }
        else if ((hall_A && !hall_B && !hall_C) &&
                 ((oldValue[0] && oldValue[1] && !oldValue[2]) || flagg)) // 100'den 110'a geçiş
        {
            step = 5;
            oldValue[0] = 1;
            oldValue[1] = 0;
            oldValue[2] = 0;
            flagg = 1;
        }
        else if ((hall_A && hall_B && !hall_C) &&
                 ((!oldValue[0] && oldValue[1] && !oldValue[2]) || flagg)) // 110'dan 010'a geçiş
        {
            step = 6;
            oldValue[0] = 1;
            oldValue[1] = 1;
            oldValue[2] = 0;
            flagg = 1;
        }
        else if ((!hall_A && hall_B && !hall_C) &&
                 ((!oldValue[0] && oldValue[1] && oldValue[2]) || flagg)) // 010'dan 011'e geçiş
        {
            step = 1;
            oldValue[0] = 0;
            oldValue[1] = 1;
            oldValue[2] = 0;
            flagg = 1;
        }
        else if ((!hall_A && hall_B && hall_C) &&
                 ((!oldValue[0] && !oldValue[1] && oldValue[2]) || flagg)) // 011'den 001'e geçiş
        {
            step = 2;
            oldValue[0] = 0;
            oldValue[1] = 1;
            oldValue[2] = 1;
            flagg = 1;
        }
        else if ((!hall_A && !hall_B && hall_C) &&
                 ((oldValue[0] && !oldValue[1] && oldValue[2]) || flagg)) // 001'den 101'e geçiş
        {
            step = 3;
            oldValue[0] = 0;
            oldValue[1] = 0;
            oldValue[2] = 1;
            flagg = 1;
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
            flagg = 1;
        }
        if ((hall_A && !hall_B && !hall_C) && ((oldValue[0] && !oldValue[1] && oldValue[2]) || flagg))
        { // 011
            step = 2;
            oldValue[0] = 1;
            oldValue[1] = 0;
            oldValue[2] = 0;
            flagg = 1;
        }
        if ((hall_A && hall_B && !hall_C) && ((oldValue[0] && !oldValue[1] && !oldValue[2]) || flagg))
        { // 001
            step = 3;
            oldValue[0] = 1;
            oldValue[1] = 1;
            oldValue[2] = 0;
            flagg = 1;
        }
        if ((!hall_A && hall_B && !hall_C) && ((oldValue[0] && oldValue[1] && !oldValue[2]) || flagg))
        { // 101
            step = 4;
            oldValue[0] = 0;
            oldValue[1] = 1;
            oldValue[2] = 0;
            flagg = 1;
        }
        if ((!hall_A && hall_B && hall_C) && ((!oldValue[0] && oldValue[1] && !oldValue[2]) || flagg))
        { // 100
            step = 5;
            oldValue[0] = 0;
            oldValue[1] = 1;
            oldValue[2] = 1;
            flagg = 1;
        }
        if ((!hall_A && !hall_B && hall_C) && ((!oldValue[0] && oldValue[1] && oldValue[2]) || flagg))
        { // 110
            step = 6;
            oldValue[0] = 0;
            oldValue[1] = 0;
            oldValue[2] = 1;
            flagg = 1;
        }
    }

    // for (uint8_t i = 0; i < 160; i++)
    // {
    //     if (i == rpm / 10 && counter < 160 && rpm > 99)
    //     {
    //         analyze_data_1[i] = (uint16_t)phase_A;
    //         analyze_data_1[i + 160] = (uint16_t)phase_B;
    //         analyze_data_1[i + 320] = (uint16_t)phase_C;
    //         counter++;

    //         if (counter == 159) // Buffer tamamlandığında veri gönder
    //         {
    //             sender_flag = 1;
    //         }
    //     }
    // }
}



// Deactive
void sample_phase_data(uint16_t rpm, uint16_t phase_A, uint16_t phase_B, uint16_t phase_C)
{
    if (rpm > 99 && counter < 160)
    {
        analyze_data_1[counter] = phase_A;
        analyze_data_1[counter + 160] = phase_B;
        analyze_data_1[counter + (160 * 2)] = phase_C;

        counter++;

        if (counter == 160)
        {
            sender_flag = 1; // 160 örnek tamamlandığında veri gönderimi işaretle
        }
    }
}