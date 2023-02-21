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
- Alfonso uses the USB 2.0 peripheral contained in the 18F4550 microcontroller. The firmware exposes the USB port as a CDC (USB communications device class). This allows it to be recognized by all OSes as an RS232 serial port. I originally intended to use the USB port as a Human Interface Device (HID) but due to its limitations I decided to implement it as a CDC and build a proprietary protocol on it.
  
## Basics

The ICL8038 waveform generator is a monolithic integrated circuit capable of producing high accuracy sine, square, triangular, sawtooth and pulse waveforms. The frequency (or repetition rate) can be selected externally from 0.001Hz to more than 300kHz.
In used configuration, the frequency has been fixed in the audio frequency range 1Hz to 20KHz. Integrators via comparators create the primary triangle which is then flip-flopped to obtain the square and a smoothing network based on multiple transistors stages.
The sweep is modulated via a dc voltage to pin 8. The relative frequency range depends on the capacitor applied to pin 10.
4 different meshes with different values are needed to get good linearity. This especially applies to operation as an LFO. 4 different selectable operating modes have been selected.

- **HVCO**
- **VCO**
- **LFO**
- **VLFO**

## Early implementation

This first implementation is oriented to develop and test all the HW functionalities of the VCOs/LFOs and the core SW libraries for their command.
For this, a first mixer with the basic functions was developed.

![FrontPanel2](https://user-images.githubusercontent.com/122873753/219691139-56ebe908-0478-47ee-9727-a8250ba0d4af.png)
![MixPanel2](https://user-images.githubusercontent.com/122873753/219691177-673d9b65-abc1-4e9c-ae17-913530f8a1f3.png)

Both the control logic section and the analog section with the VCO and the mixers are still being prototyped via breadboard.
Once the functionality is stabilized, I will create a welded version for better signal quality. Obviously the air links are not optimal.

![AlfonsoPrev1](https://user-images.githubusercontent.com/122873753/214313627-f87d06cf-55e3-4104-a56d-350e2fd5c412.jpg)
![AlfonsoPrev2](https://user-images.githubusercontent.com/122873753/214313670-8de575b0-895b-4a02-b9fe-d2fca62c175e.jpg)

## Upcoming implementations

- It is my intention, once the project based on the **Intersil ICL8038** is completed and stabilized, to re-adapt it for use with the **EXAR XR-2206** Monolithic Function Generator.
  IC is more modern and seems to compensate for certain problems of the *ICL8038*. It is also still supported and in production.
- The impact on the Firmware of the transition of the current mC **PIC18F4450** towards the new version, currently supported by the *MCC of MPLABX*, mC **PIC18F45K50** is minimal.
  So as soon as the current version stabilizes, I'll switch to this mC.
