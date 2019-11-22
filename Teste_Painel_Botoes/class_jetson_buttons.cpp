#include "class_jetson_buttons.h"

/**
 * @brief Construct a new Class_Jetson_Buttons::Class_Jetson_Buttons object
 * 
 */
Class_Jetson_Buttons::Class_Jetson_Buttons()
{

}


/**
 * @brief Class_Jetson_Buttons::ButtonOutPut
 * @param pinName
 * @param Status
 */
Class_Jetson_Buttons::ButtonOutPut(int &pinName, int &Status)
{

    unsigned int pButtonStates[8] = {0,0,0,0,0,0,0,0};
	char pinNames[8][6] = {"pin29", "pin37", "pin31", "pin18", "pin33", "pin16", "pin32", "pin13"}; 
	unsigned int pinAddresses[8] = {pin29, pin37, pin31, pin18, pin33, pin16, pin32, pin13}; 
	



		for(int n = 0; n <= 7; n++){
			gpioGetValue(pinAddresses[n], &pButtonStates[n]) ;
			if(pButtonStates[n] == high){
				if(pButtonFlag[n] == low){
					pButtonFlag[n] = high;
					cout << pinNames[n] << " flag set to: " << pButtonStates[n] << endl;
				}
			}else{
				if(pButtonFlag[n] == high){
					pButtonFlag[n] = low;
					cout << pinNames[n] << " flag set to: " << pButtonStates[n] << endl;
				}
			}
		}

    usleep(1000); // sleep for a millisecond
}
