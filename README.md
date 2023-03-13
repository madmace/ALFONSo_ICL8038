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
- [Basics](#basics)
- [Early implementation](#early-implementation)
- [Upcoming implementations](#upcoming-implementations)

## Meta

Scope:

- The project from my passion of analog synthesizers and the love of the patterns, rhythms and mats that colored the majority of the 70s and 80s classics. In particular the analog sequencers and LFOs.
- The use of analog IC monolith signal generators operated in BF in the 1Hz band up to 25KHz. Can be used as VCO/LFO. This first research *intentionally* uses the older, now obsolete, but well known **Intersil ICL8038**.
- The digital control interface via USB is based on an *old and well-known* Microchip **18-series** microcontroller. The **PIC18F4550** is a widely used mC and there is a large amount of example code and tutorials available on the web.
  However, I personally always suggest having its datasheet handy and dedicating the time to understand its correct functioning.
- Alfonso uses the USB 2.0 peripheral contained in the 18F4550 microcontroller. The firmware exposes the USB port as a CDC (USB communications device class). This allows it to be recognized by all OSes as an RS232 serial port.
  I originally intended to use the USB port as a Human Interface Device (HID) but due to its limitations I decided to implement it as a CDC and build a proprietary protocol on it.
  
## Basics

The ICL8038 waveform generator is a monolithic integrated circuit capable of producing high accuracy sine, square, triangular, sawtooth and pulse waveforms. The frequency (or repetition rate) can be selected externally from 0.001Hz to more than 300kHz.
In used configuration, the frequency has been fixed in the audio frequency range 1Hz to 20KHz. Integrators via comparators create the primary triangle which is then flip-flopped to obtain the square and a smoothing network based on multiple transistors stages to obtain the sine.
The sweep is modulated via a DC voltage to pin 8. The relative frequency range depends on the capacitor applied to pin 10.
Four different meshes with different values are needed to get good linearity. This especially applies to operation as an LFO. Four different selectable operating modes have been selected.

The frequency ranges are still raw and are related to the values of the capacitors used in the VCO applied to pin 10 of the ICL8038.

- **HVCO** (*1.6KHz to 26KHz*)
- **VCO** (*238Hz to 4.1KHz*)
- **LFO** (*11Hz to 194Hz*)
- **VLFO** (*3Hz to 67Hz*)

The selection of the frequency range is set using the micro via the I/O Expander MCP23S17 and the Quad Bilateral Switch CD4066B.

The PIC18F4550 has only one MSSP *(Master Synchronous Serial Port)*. While it can be dynamically reset, the open-drain nature of the I2C *(Inter Integrated Circuit)* protocol makes it incompatible with SPI (Serial Peripheral Interface).
So I chose to use only SPI peripherals even with the expenditure of lines for the various CSs *(Chip Select)*.

SPI ICs used :

**MCP23S08** High-speed SPI 8-Bit I/O Expander from Microchip<BR>
A very convenient prerogative of this series of SPI I/O Expanders is that it has the possibility of setting additional hardware addresses which allow you to select the peripheral with the same CS line.
In the case of the MCP23S08 it has two address pins wired for a total of four I/O expanders per CS.
In the project it is used to drive via SPI the Hitachi HD44780-based LCD in four bit mode, the related handshake and internal LED lighting signals.
In the microcode a specific library has been developed for the coupling of the MCP23S08 and the HD44780.

**MCP23S17** High-speed SPI 16-Bit I/O Expander from Microchip<BR>
Like its minor brother MCP23S08, the MCP23S17 has the ability to set hardware addresses switching from previous two to three addresses for eight devices on the same CS line.
The MCP23S17 is used to drive the numerous analog bilateral switchs found in mixers. There is one for each two VCO module.
    
**MCP42010** Dual Digital Potentiometer SPI
The IC is a double potentiometer with 256 taps 8-bit for each potentiometer. The MCP42XXX series is with the internal register is volatile. So it doesn't keep the last setting. At the moment it is the software that imposes all the default levels on connection. The permanent model is also available in case of future considerations.
The MCP42XXX series is available with the values for 10 kΩ, 50 kΩ and 100 kΩ. There is a nominal wiper resistance of 52Ω for the 10 kΩ version, 125Ω for the 50 kΩ and 100 kΩ versions. The channel-to-channel matching variation is less than 1%. The resistance between the wiper and either of the resistor endpoints varies linearly according to the value stored in the data register. At power-up or upon habilitation the RS, all data registers will automatically be loaded with the mid-scale value (80h). The Shutdown pin SHDN, if enabled, leaves the A terminal is opened and the B and W terminals are connected for all potentiometers.
A feature of this SPI IC is the presence of SO output pin, multiple devices can be daisy-chained together.
    
**MCP4251**
The IC is a double potentiometer with 257 taps 8-bit for each potentiometer. The MCP4251 also has volatile internal register loaded with the mid-scale value (80h).
It has a nominal wiper resistance of 75Ω typical for all available values 5kΩ, 10kΩ, 50kΩ, 100 kΩ.

## Early implementation

This first implementation is oriented to develop and test all the HW functionalities of the VCOs/LFOs and the core SW libraries for their command.
For this, a first mixer with the basic functions was developed.

![Front Panel](https://user-images.githubusercontent.com/122873753/222146686-99d1909f-2db3-43aa-8f50-f5286ce944ac.png)
![Mixer Panel](https://user-images.githubusercontent.com/122873753/222147808-f85e7260-d6f0-4ed8-a101-276cef76ffd2.png)

Both the control logic section and the analog section with the VCO and the mixers are still being prototyped via breadboard.
Once the functionality is stabilized, I will create a welded version for better signal quality. Obviously the air links are not optimal.

![AlfonsoPrev1](https://user-images.githubusercontent.com/122873753/214313627-f87d06cf-55e3-4104-a56d-350e2fd5c412.jpg)
![AlfonsoPrev2](https://user-images.githubusercontent.com/122873753/214313670-8de575b0-895b-4a02-b9fe-d2fca62c175e.jpg)

## Upcoming implementations

- It is my intention, once the project based on the **Intersil ICL8038** is completed and stabilized, to re-adapt it for use with the **EXAR XR-2206** Monolithic Function Generator.
  IC is more modern and seems to compensate for certain problems of the *ICL8038*. It is also still supported and in production.
- The impact on the Firmware of the transition of the current mC **PIC18F4450** towards the new version, currently supported by the *MCC of MPLABX*, mC **PIC18F45K50** is minimal.
  So as soon as the current version stabilizes, I'll switch to this mC.
