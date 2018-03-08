#Nixie-Tube-Clock-Project
DIY a single nixie tube clock by using a IN-18 tube and an Arduino uno dev board(Atmega328P-AU)

A Clock using IN-18 nixie tube, which just has one tube. In my design, the clock has following parts:
	1: IN -18 Nixie Tube
	2: DC-DC Coverter(lift 5V to 170V)
	3: Motherboard for the tube 
	4: Arduino uno dev board and DS3231
	5: Tapsensor
	6: Auxiliary button (Reset MCU once it goes crazy)
	7: A container and removable bottom (glass fiber , 3D print)
DS3231 connect to arduino by I2C, once tapsensor gives a "HIGH", arduino read time data from DS3231 and split received string into single digital and set corresponding pin to HIGH for 1000ms (D2~D11 mapping 0~9).
#For instance
	if arduino received 12:34, D2, D3, D4, D5 will be set to HIGH one by one. 
Those channels control 10 transistors, voltage cross the character and anode will up to approx 170v. DONE~ 
