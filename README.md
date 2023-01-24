# A.L.F.O.N.S.o based on ICL8038

ALFONSo stands for :

**A**nalog
**L**ow 
**F**requency 
**O**scillator 
**N**olinear 
**S**equencer 

In this implementation MK-ICL8038.

- [Meta](#meta)
- [Basics](#basics)
- [Early implementation](#early-implementation)
- [Upcoming implementations](#upcoming-implementations)

## Meta

Scope:

- The project from my passion of analog synthesizers and the love of the patterns, rhythms and mats that colored the majority of the 70s and 80s classics. In particular the analog sequencers and LFOs.
- The use of analog IC monolith signal generators operated in BF in the 1Hz band up to 25KHz. Can be used as VCO/LFO. This first research *intentionally* uses the older, now obsolete, but well known **Intersil ICL8038**.
- The digital control interface via USB is based on an *old and well-known* Microchip **18-series** microcontroller. The **PIC18F4550** is a widely used mC and there is a large amount of example code and tutorials available on the web.
  However, I personally always suggest having its datasheet handy and dedicating the time to understand its correct functioning.
  
## Basics

## Early implementation

This first implementation is oriented to develop and test all the HW functionalities of the VCOs/LFOs and the core SW libraries for their command.
For this, a first mixer with the basic functions was developed.

![MixPanel1](https://user-images.githubusercontent.com/122873753/214284695-f959e45d-0ba2-4988-ba2b-588b65fec1ae.png)

Both the control logic section and the analog section with the VCO and the mixers are still being prototyped via breadboard.
Once the functionality is stabilized, I will create a welded version for better signal quality. Obviously the air links are not optimal.

![AlfonsoPrev1](https://user-images.githubusercontent.com/122873753/214313627-f87d06cf-55e3-4104-a56d-350e2fd5c412.jpg)
![AlfonsoPrev2](https://user-images.githubusercontent.com/122873753/214313670-8de575b0-895b-4a02-b9fe-d2fca62c175e.jpg)

## Upcoming implementations

- It is my intention, once the project based on the **Intersil ICL8038** is completed and stabilized, to re-adapt it for use with the **EXAR XR-2206** Monolithic Function Generator.
  IC is more modern and seems to compensate for certain problems of the *ICL8038*. It is also still supported and in production.
- The impact on the Firmware of the transition of the current mC **PIC18F4450** towards the new version, currently supported by the *MCC of MPLABX*, mC **PIC18F45K50** is minimal.
  So as soon as the current version stabilizes, I'll switch to this mC.
