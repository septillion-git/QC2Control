EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L R R1
U 1 1 592EC466
P 2650 2250
F 0 "R1" V 2730 2250 50  0000 C CNN
F 1 "2k2" V 2650 2250 50  0000 C CNN
F 2 "" V 2580 2250 50  0001 C CNN
F 3 "" H 2650 2250 50  0001 C CNN
	1    2650 2250
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 592EC5AA
P 2650 2750
F 0 "R2" V 2730 2750 50  0000 C CNN
F 1 "1k" V 2650 2750 50  0000 C CNN
F 2 "" V 2580 2750 50  0001 C CNN
F 3 "" H 2650 2750 50  0001 C CNN
	1    2650 2750
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 592EC5D2
P 3950 2250
F 0 "R3" V 4030 2250 50  0000 C CNN
F 1 "2k2" V 3950 2250 50  0000 C CNN
F 2 "" V 3880 2250 50  0001 C CNN
F 3 "" H 3950 2250 50  0001 C CNN
	1    3950 2250
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 592EC601
P 3950 2750
F 0 "R4" V 4030 2750 50  0000 C CNN
F 1 "1k" V 3950 2750 50  0000 C CNN
F 2 "" V 3880 2750 50  0001 C CNN
F 3 "" H 3950 2750 50  0001 C CNN
	1    3950 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 2100 2650 1750
Wire Wire Line
	2650 1750 4600 1750
Text Label 4600 1750 2    60   ~ 0
Arduino_Vcc
Text Label 4600 2050 2    60   ~ 0
Arduino_DmPin
Wire Wire Line
	3950 2100 3950 2050
Wire Wire Line
	3950 2050 4600 2050
Text Label 4600 1900 2    60   ~ 0
Arduino_DpPin
Wire Wire Line
	2650 2400 2650 2500
Wire Wire Line
	2650 2500 2650 2600
Connection ~ 2650 2500
Wire Wire Line
	2650 2900 2650 3000
Wire Wire Line
	2300 3000 2650 3000
Wire Wire Line
	2650 3000 3300 3000
Wire Wire Line
	3300 3000 3950 3000
Wire Wire Line
	3950 3000 4600 3000
Wire Wire Line
	3950 3000 3950 2900
$Comp
L GND #PWR1
U 1 1 592EC6F3
P 3300 3050
F 0 "#PWR1" H 3300 2800 50  0001 C CNN
F 1 "GND" H 3300 2900 50  0000 C CNN
F 2 "" H 3300 3050 50  0001 C CNN
F 3 "" H 3300 3050 50  0001 C CNN
	1    3300 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 3000 3300 3050
Connection ~ 3300 3000
Text Label 2300 2500 0    60   ~ 0
Data+
Wire Wire Line
	3950 2400 3950 2500
Wire Wire Line
	3950 2500 3950 2600
Text Label 3600 2500 0    60   ~ 0
Data-
Wire Wire Line
	3600 2500 3950 2500
Connection ~ 3950 2500
Text Label 2300 3000 0    60   ~ 0
GND
Text Label 4600 3000 2    60   ~ 0
Arduino_GND
Text Label 2300 1500 0    60   ~ 0
Vbus
Wire Wire Line
	2300 1500 3050 1500
Wire Wire Line
	3350 1500 3450 1500
Wire Wire Line
	3750 1500 4600 1500
Text Label 4600 1500 2    60   ~ 0
Arduino_RAW/Vin
$Comp
L D D1
U 1 1 592ECD42
P 3200 1500
F 0 "D1" H 3200 1600 50  0000 C CNN
F 1 "1N4148" H 3200 1400 50  0000 C CNN
F 2 "" H 3200 1500 50  0001 C CNN
F 3 "" H 3200 1500 50  0001 C CNN
	1    3200 1500
	-1   0    0    1   
$EndComp
$Comp
L D D2
U 1 1 592ECDA8
P 3600 1500
F 0 "D2" H 3600 1600 50  0000 C CNN
F 1 "1N4148" H 3600 1400 50  0000 C CNN
F 2 "" H 3600 1500 50  0001 C CNN
F 3 "" H 3600 1500 50  0001 C CNN
	1    3600 1500
	-1   0    0    1   
$EndComp
Wire Notes Line
	3000 1650 3800 1650
Wire Notes Line
	3800 1650 3800 1300
Wire Notes Line
	3800 1300 3000 1300
Wire Notes Line
	3000 1300 3000 1650
Text Notes 3000 1300 0    50   ~ 0
Extra protection
$Comp
L R R5
U 1 1 592F13A9
P 2900 2500
F 0 "R5" V 2980 2500 50  0000 C CNN
F 1 "680R" V 2900 2500 50  0000 C CNN
F 2 "" V 2830 2500 50  0001 C CNN
F 3 "" H 2900 2500 50  0001 C CNN
	1    2900 2500
	0    1    1    0   
$EndComp
Wire Wire Line
	2300 2500 2650 2500
Wire Wire Line
	2650 2500 2750 2500
Wire Wire Line
	3050 2500 3350 2500
Wire Wire Line
	3350 2500 3350 1900
Wire Wire Line
	3350 1900 4600 1900
Connection ~ 3950 3000
Connection ~ 2650 3000
$EndSCHEMATC
