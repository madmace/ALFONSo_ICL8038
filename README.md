# A.L.F.O.N.S.o based on ICL8038

ALFONSo stands for :

<p align="right">
    <img align="right" width="300px"src="https://user-images.githubusercontent.com/122873753/222533968-67c840fd-441d-4f12-a997-181fa5d1333d.png">
</p>

**A**nalog
**L**ow 
**F**requency 
**O**scillator 
**N**olinear 
**S**equencer

In this implementation MK-ICL8038.

- [Meta](#meta)
- [Basics](Basics.md)
- [Power Supply](Power.md)
- [ICs used in VCO & Mixer](ICs.md)
- [Early implementation](#early-implementation)
- [Upcoming implementations](#upcoming-implementations)

## Meta

Scope:

- The project from my passion of analog synthesizers and the love of the patterns, rhythms and mats that colored the majority of the 70s and 80s classics. In particular the analog sequencers and LFOs.
- The use of analog IC monolith signal generators operated in BF in the 1Hz band up to 25KHz. Can be used as VCO/LFO. This first research *intentionally* uses the older, now obsolete, but *well known* **Intersil ICL8038**.
- The digital control interface via USB is based on an *old and well-known* Microchip **18-series** microcontroller. The **PIC18F4550** is a widely used mC and there is a large amount of example code and tutorials available on the web.
  However, I personally always suggest having its datasheet handy and dedicating the time to understand its correct functioning.
- Alfonso uses the USB 2.0 peripheral contained in the 18F4550 microcontroller. The firmware exposes the USB port as a CDC (USB communications device class). This allows it to be recognized by all OSes as an RS232 serial port.
  I originally intended to use the USB port as a Human Interface Device (HID) but due to its limitations I decided to implement it as a CDC and build a proprietary protocol on it.

## Early implementation

This first implementation is oriented to develop and test all the HW functionalities of the VCOs/LFOs and the core SW libraries for their command.
For this, a first mixer with the basic functions was developed.

[Front Panel](images/FrontPanel.png)
![Mixer Panel](https://user-images.githubusercontent.com/122873753/226573380-3f527885-a70a-4488-9e40-b10083d6392b.png)

Both the control logic section and the analog section with the VCO and the mixers are still being prototyped via breadboard.
Once the functionality is stabilized, I will create a welded version for better signal quality. Obviously the air links are not optimal.
    
![AlfonsoPrev1](https://user-images.githubusercontent.com/122873753/227480448-d9f88da3-b6e7-4724-b1cf-c95f1440d193.jpg)
![AlfonsoPrev2](https://user-images.githubusercontent.com/122873753/227480695-c834970d-64e1-446c-83c7-bf464703e895.jpg)
![AlfonsoPrev3](https://user-images.githubusercontent.com/122873753/227881345-979ef7f8-7705-488d-afa9-8d4fd5c0fcca.jpg)
![AlfonsoPrev4](https://user-images.githubusercontent.com/122873753/227881365-9eacd5d9-6c7d-4a65-a6d9-9520cd45d24c.jpg)


## Upcoming implementations

- It is my intention, once the project based on the **Intersil ICL8038** is completed and stabilized, to re-adapt it for use with the **EXAR XR-2206** Monolithic Function Generator.
  IC is more modern and seems to compensate for certain problems of the *ICL8038*. It is also still supported and in production.
- The impact on the Firmware of the transition of the current mC **PIC18F4450** towards the new version, currently supported by the *MCC of MPLABX*, mC **PIC18F45K50** is minimal.
  So as soon as the current version stabilizes, I'll switch to this mC.
