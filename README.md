M4T3M4T
=======

first network controlled Club Mate dispenser



Flachband von den Knöpfen
-----------------
1  LED 1
2  LED 2
3  LED 3
4  LED 4
5  LED 5
6  LED 6
7  
8  
9  
10 
11 
12 
13 Taster 1
14 Taster 2
15 Taster 3
16 Taster 4
17 Taster 5
18 Taster 6
19 
20 
21 
22 
23 Taster-GND
24 
25 
26 LED-GND
 
Netzteil
----------
 
Connector X80
 
PIN
1   Triac 3IO
2   Triac 2
3   Triac 1
4 
5   GND
6   
7   PT100 b
8   PT100 a
9   
10 
 
 
1,7K Vorwiederstand für den Triac-Treiber
 
 
Aktoren
----------
 
 
 
* 5 mal 24V~ 66W (Drehmotoren) berechnet 2,75A gemessen 5A (max 10s ???)
  *  Heidolph Typ 607 113 02770a
* 1 mal Aggregat (230V ??? bei ??? A) wird über triac geschaltet
Triac BTA12 600BW
 * Optokoppler MOC3022 133Q
  * http://www.datasheetcatalog.org/datasheet/motorola/MOC3021.pdf
 
 
mögliche Schaltung
 
µC  = 5V =>  transistor array  = 12V =>  Relais
 
* http://www.mikrocontroller.net/part/ULN2003
* http://www.mikrocontroller.net/part/ULN2803 (500mA pro Kanal)
 
Transistor Array
http://www.pollin.de/shop/dt/NjM5ODk4OTk-/Bauelemente_Bauteile/Aktive_Bauelemente/IC/ULN2803A.html
 
"Netzteil" 24V~ auf 5V
http://www.pollin.de/shop/dt/MjA4OTgxOTk-/Bausaetze_Module/Bausaetze/Bausatz_Regelbares_Netzteil.html
 
Relais
http://www.pollin.de/shop/dt/MTA1OTU2OTk-/Bauelemente_Bauteile/Mechanische_Bauelemente/Relais_Zugmagnete/Relaisfassung_Finder_F95853.html
http://www.pollin.de/shop/dt/MjA1OTU2OTk-/Bauelemente_Bauteile/Mechanische_Bauelemente/Relais_Zugmagnete/Relais_Printfassung_FINDER.html
 
http://www.pollin.de/shop/dt/NjA1OTU2OTk-/Bauelemente_Bauteile/Mechanische_Bauelemente/Relais_Zugmagnete/Relais_Finder_F40527_05.html
http://www.pollin.de/shop/dt/ODU0OTU2OTk-/Bauelemente_Bauteile/Mechanische_Bauelemente/Relais_Zugmagnete/Relais_Finder_46_52_9_012_0040.html
 
 
 
Sensoren
-------------
 
* pt 100 im kühlschrank - geht und getestet
 
pro Schacht
* Motorschalter
* Leerschalter
 
 
 
 
Stecker Molex:
------------------
http://www.molex.com/pdm_docs/sd/367570107_sd.pdf
Pin zu Pin
6mm
 
X1
 
3 mal 4 Pins
25mm
17mm
6 Belegt
 
X2
 
3 mal 5 Pins
30mm
17mm
Voll(15) Belegt
 
X5
3 Pins (Mitte leer)
 
X6
2 Pins
 
X7
2 Pins
 
Münzzähler
3 mal 3 Pins
17mm

