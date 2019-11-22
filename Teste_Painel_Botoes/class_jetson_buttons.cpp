#include "class_jetson_buttons.h"
#include <QDebug>


/**
 * @brief Construct a new Class_Jetson_Buttons::Class_Jetson_Buttons object
 * 
 */
Class_Jetson_Buttons::Class_Jetson_Buttons()
{
    InitButtons(); /*< inicializa as portas */
}


/**
 * @brief Class_Jetson_Buttons::~Class_Jetson_Buttons
 */
Class_Jetson_Buttons::~Class_Jetson_Buttons()
{

}


/**
 * @brief Class_Jetson_Buttons::InitButtons
 * Inicializa os pinos gpio e seta as direções
 */
void Class_Jetson_Buttons::InitButtons()
{

    // Definindo o gpio para cada nome de pino
     pin37 = gpio187;
     pin32 = gpio36;   // Disp1
     pin29 = gpio219;  // Disp2
     pin16 = gpio37;   // Vmod1
     pin33 = gpio63;   // Vmod2
     pin31 = gpio186;  // power_off
     pin18 = gpio184;  // save_file
     pin13 = gpio38;   // sync


    // Habilita pinos (Make the button and led available in user)
    gpioExport(pin37) ;
    gpioExport(pin32) ;
    gpioExport(pin29) ;
    gpioExport(pin16) ;
    gpioExport(pin33) ;
    gpioExport(pin31) ;
    gpioExport(pin18) ;
    gpioExport(pin13) ;


    // Seta a direção do pino
    gpioSetDirection(pin37,inputPin);
    gpioSetDirection(pin32,inputPin);
    gpioSetDirection(pin29,inputPin);
    gpioSetDirection(pin16,inputPin);
    gpioSetDirection(pin33,inputPin);
    gpioSetDirection(pin31,inputPin);
    gpioSetDirection(pin18,inputPin);
    gpioSetDirection(pin13,inputPin);
}


/**
 * @brief Class_Jetson_Buttons::ButtonCheck
 * @param pinName
 * @param Status
 */
void Class_Jetson_Buttons::ButtonCheck()//(int &pinName, int &Status)
{

    unsigned int pButtonStates[8] = {0,0,0,0,0,0,0,0};
    char pinNames[8][20] = {"pin29", "pin37", "pin31", "redLEDredLEDpin18", "pin33", "pin16", "pin32", "pin13"};
    unsigned int pinAddresses[8] = {pin29, pin37, pin31, pin18, pin33, pin16, pin32, pin13};

    unsigned int pButtonDebouncing[8] = {0,0,0,0,0,0,0,0};
    unsigned int pButtonCounter[8] = {0,0,0,0,0,0,0,0};
    unsigned int pButtonFlag[8] = {0,0,0,0,0,0,0,0};



        for(int n = 0; n <= 7; n++)
        {
            gpioGetValue(pinAddresses[n], &pButtonStates[n]);

            if(pButtonStates[n] == high)
            {
                if(pButtonFlag[n] == low)
                {
                    pButtonFlag[n] = high;
                    std::cout << pinNames[n] << " flag set to: " << pButtonStates[n] << std::endl;
                }
            }
            else
            {
                if(pButtonFlag[n] == high)
                {
                    pButtonFlag[n] = low;
                    std::cout << pinNames[n] << " flag set to: " << pButtonStates[n] << std::endl;
                }
            }
        }

        std::cout << "Degug ButtonCheck()" << std::endl;

}

