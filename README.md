<h1>Nixie-Tube-Clock-Project</h1>
<p>DIY a single nixie tube clock by using a IN-18 tube and an Arduino uno dev board(Atmega328P-AU)</p>
<p>A Clock using IN-18 nixie tube, which just has one tube. In my design, the clock has following parts:
	<h4>1: IN -18 Nixie Tube
	<h4>2: DC-DC Coverter(lift 5V to 170V)
	<h4>3: Control board for the tube 
	<h4>4: Arduino uno dev board and DS3231
	<h4>5: Tapsensor
	<h4>6: Auxiliary button (Reset MCU once it goes crazy)
	<h4>7: A container and removable bottom (glass fiber , 3D print)</p>		

<p> DS3231 is connect to arduino by I2C, once tapsensor gives a &quot;HIGH&quot;, processor get time data from ds3231 process raw data and divide into individual digits. Then ignite nixie tube</p>

<p>Those channels control 10 transistors, voltage cross the character and anode will up to approx 170v. DONE~ </p>
