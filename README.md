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
 
***Power supply***

The whole VCO section is powered with a dual voltage -8V/+8V. Swing is then reduced at the final outputs to the standard preamp signal of 2Vpp.
The digital control section which includes the mC and all the SPIs is instead powered with +5V/0V.
An EMC/EMI differential-mode (DM) filter is used on the mains power line and no switching technology is used.

ICs used in VCO & Mixer :

**ICL8038** Precision Waveform Generator/Voltage Controlled Oscillator<BR>
An problem with this generators is strong distortion on sine wave output pin 2, so most of the solutions based on this chip has a limited frequency.
Another is that the square wave output from pin 9 is an open collector that needs to be pulled up to the power supply. In some way the quality of other waveforms is dependent on the load on this pin. I excluded the 15M potentiometer indicated in the datasheet on page 7, squeezes the top of the upper half of the signal.
As mentioned, square output pin 9 with open collector, normally would never be able to give a good square wave at these frequencies. Rising edge depends only on the pull-up resistor and its growing very slowly. If we give too strong pull-up resistor, in turn, the trailing edge will be weak because the internal transistor is too heavily loaded. 
Here, i fixed the square wave with a comparator so that the slope is pretty steep, steep as applied comparator can give. Shown in the schematic LM339 has 1.3μs response time but it would be good to use even faster model of comparator.
The amplitude of the signal, unfortunately, is not the same for each function, tests have shown that trying to match it with the usual R/R signal dividers will give very distorted waveforms as rounded square and triangle, so i resigned from such divisors.

Sine output on pin 2 as ratio 0.22~ * Vcc<BR>
Triangle output on pin 3 as ratio 0.33~ * Vcc<BR>
Square output on pin 9 as ratio 0.9~ * Vcc<BR>

This however was not a problem since I use the Quad OpAmps TL084 as a mixer anyway. What I cannot avoid at this point is the use of trimmers for signal calibration at 2Vpp.

The physical potentiometers for frequency sweep and duty cycle are respectfully replaced, by the 10KΩ MCP42010 and the 5KΩ MCP4251.

For each VCO both potentiometers of the MCP42010 are used. So there's a MCP42010 for VCO. One is used as the main one and the other is in series for fine tuning.
Only a single one MCP4251 potentiometer for duty is used. Half for VCO.

***Frequency ranges***

The frequency ranges are still raw and are related to the values of the capacitors used in the VCO applied to pin 10 of the ICL8038.

- **HVCO** (*1.6KHz to 26KHz used capacity 1uF*)
- **VCO** (*238Hz to 4.1KHz used capacity 100nF*)
- **LFO** (*11Hz to 194Hz used capacity 22nF*)
- **VLFO** (*3Hz to 67Hz used capacity 2nF*)

The selection of the frequency range is set using the micro via the I/O Expander MCP23S17 and the Quad Bilateral Switch CD4066B.
Only one of the four bilateral switches is active defining the frequency range.

***Frequency Modulation and Sweeping***

The frequency of the waveform generator is a direct function of the DC voltage at Terminal 8 (measured from V+). By altering this voltage, frequency modulation is performed. For small deviations (e.g. ±10%) the modulating signal can be applied directly to pin 8, merely providing DC decoupling with a capacitor.
An external resistor between pins 7 and 8 is not necessary, but it can be used to increase input impedance from about 8kΩ (pins 7 and 8 connected together), to about (R + 8kΩ).
For larger FM deviations or for frequency sweeping, the modulating signal is applied between the positive supply voltage and pin 8.

The potential on Pin 8 may be swept down from V+ by (1/3 VSUPPLY - 2V). Then for ALFONSo from +8V (Low Freq) to +3.33V (High Freq).

**TL084** High-speed JFET input, quad operational amplifiers<BR>
The TL084 is high speed J–FET input quad operational amplifiers. The devices feature high slew rates, low input bias and offset currents, and low offset voltage temperature coefficient.
The TL084 is used to make the harmonics mixer. For each harmonic there is the relative gain adjustment trimmer which allows it to be brought into line with 2vpp.

**LM339** Quad Comparators<BR>
This quad comparator is used extensively to make CD4066B control lines compatible. The CD4066Bs are used to switch the frequency range, to enable individual harmonics and enable the singles VCO.
The CD4066 must have a dual power supply to fully support the signals produced, and in this mode enabling and disabling of the bilateral switches is done with the +8V/-8V control signals.
Then the +5V/0V MCP23S17 I/O Expander outputs are converted to dual levels using the Quad comparators provided by the LM339.
Currently each VCO needs 8 control GPIOs. For a total of two LM339 per VCO dedicated to this purpose.
The LM339 is also used to purify the square wave output which is suboptimal due to the value of the pull-up resistor. In this case one is used for VCO.

**LM393** Dual Comparators<BR>
The LM393 is a dual comparator used primarily to produce a +5V/0 signal, derived from the square wave, compatible with the CCP input of the controller.
This allows the controller to calculate the current frequency of the selected VCO.

**CD4066B** CMOS Quad Bilateral Switch<BR>
The CD4066B is a quad bilateral switch intended for the transmission or multiplexing of analog or digital signals.
The CD4066B consists of four bilateral switches, each with independent controls. Both the p and the n devices in a given switch are biased on or off simultaneously by the control signal. The well of the n-channel device on each switch is tied to either the input (when the switch is on) or to VSS (when the switch 
is off). This configuration eliminates the variation of the switch-transistor threshold voltage with input signal and, thus, keeps the on-state resistance low over the full operating-signal range.

***SPI Devices***

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

![Front Panel](https://user-images.githubusercontent.com/122873753/226573256-fed9c808-4e0c-47b5-81cf-c3ab95d98092.png)
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
