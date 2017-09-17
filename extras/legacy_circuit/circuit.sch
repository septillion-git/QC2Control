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
LIBS:circuit-cache
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
L GND #PWR?
U 1 1 5989BD3E
P 5750 4500
F 0 "#PWR?" H 5750 4250 50  0001 C CNN
F 1 "GND" H 5750 4350 50  0000 C CNN
F 2 "" H 5750 4500 50  0001 C CNN
F 3 "" H 5750 4500 50  0001 C CNN
	1    5750 4500
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5989BD57
P 5150 3550
F 0 "R1" V 5230 3550 50  0000 C CNN
F 1 "10k" V 5150 3550 50  0000 C CNN
F 2 "" V 5080 3550 50  0001 C CNN
F 3 "" H 5150 3550 50  0001 C CNN
	1    5150 3550
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 5989BDBC
P 5150 4050
F 0 "R2" V 5230 4050 50  0000 C CNN
F 1 "1k5" V 5150 4050 50  0000 C CNN
F 2 "" V 5080 4050 50  0001 C CNN
F 3 "" H 5150 4050 50  0001 C CNN
	1    5150 4050
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 5989BE45
P 6350 3550
F 0 "R3" V 6430 3550 50  0000 C CNN
F 1 "10k" V 6350 3550 50  0000 C CNN
F 2 "" V 6280 3550 50  0001 C CNN
F 3 "" H 6350 3550 50  0001 C CNN
	1    6350 3550
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 5989BE9E
P 6350 4050
F 0 "R4" V 6430 4050 50  0000 C CNN
F 1 "1k5" V 6350 4050 50  0000 C CNN
F 2 "" V 6280 4050 50  0001 C CNN
F 3 "" H 6350 4050 50  0001 C CNN
	1    6350 4050
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 5989BEBD
P 5400 3800
F 0 "R5" V 5480 3800 50  0000 C CNN
F 1 "470R" V 5400 3800 50  0000 C CNN
F 2 "" V 5330 3800 50  0001 C CNN
F 3 "" H 5400 3800 50  0001 C CNN
	1    5400 3800
	0    -1   1    0   
$EndComp
Text Label 4800 3800 0    60   ~ 0
Data+
Text Label 6000 3800 0    60   ~ 0
Data-
Text Label 6500 3350 0    60   ~ 0
Arduino_DmPin
Text Label 4800 4450 0    60   ~ 0
GND
Text Label 6350 4300 0    60   ~ 0
Arduino_DmGndPin
Text Label 6500 3200 0    60   ~ 0
Arduino_DpPin
Text Label 6600 3050 0    60   ~ 0
Arduino_Vcc
$Comp
L D D1
U 1 1 5989CAAB
P 5650 2800
F 0 "D1" H 5650 2900 50  0000 C CNN
F 1 "1N4148" H 5650 2700 50  0000 C CNN
F 2 "" H 5650 2800 50  0001 C CNN
F 3 "" H 5650 2800 50  0001 C CNN
	1    5650 2800
	-1   0    0    1   
$EndComp
$Comp
L D D2
U 1 1 5989CBB6
P 6050 2800
F 0 "D2" H 6050 2900 50  0000 C CNN
F 1 "1N4148" H 6050 2700 50  0000 C CNN
F 2 "" H 6050 2800 50  0001 C CNN
F 3 "" H 6050 2800 50  0001 C CNN
	1    6050 2800
	-1   0    0    1   
$EndComp
Text Label 4800 2800 0    60   ~ 0
Vbus
Text Label 6400 2800 0    60   ~ 0
Arduino_RAW/Vin
Text Notes 5450 2600 0    51   ~ 0
Optional. See notes
Wire Wire Line
	5150 3700 5150 3900
Connection ~ 5150 3800
Wire Wire Line
	4800 3800 5250 3800
Wire Wire Line
	6350 3700 6350 3900
Connection ~ 6350 3800
Wire Wire Line
	6000 3800 6350 3800
Wire Wire Line
	6350 3400 6350 3350
Wire Wire Line
	6350 3350 7150 3350
Wire Wire Line
	5750 4450 5750 4500
Wire Wire Line
	4800 4450 7150 4450
Wire Wire Line
	5150 4200 5150 4450
Connection ~ 5150 4450
Wire Wire Line
	6350 4200 6350 4300
Wire Wire Line
	6350 4300 7150 4300
Wire Wire Line
	5550 3800 5800 3800
Wire Wire Line
	5800 3800 5800 3200
Wire Wire Line
	5800 3200 7150 3200
Wire Wire Line
	5150 3050 5150 3400
Wire Wire Line
	5150 3050 7150 3050
Wire Wire Line
	4800 2800 5500 2800
Wire Wire Line
	5800 2800 5900 2800
Wire Wire Line
	6200 2800 7150 2800
Wire Notes Line
	5450 2600 5450 2950
Wire Notes Line
	5450 2950 6250 2950
Wire Notes Line
	6250 2950 6250 2600
Wire Notes Line
	6250 2600 5450 2600
Connection ~ 5750 4450
Text Label 6600 4450 0    60   ~ 0
Arduino_GND
$EndSCHEMATC
