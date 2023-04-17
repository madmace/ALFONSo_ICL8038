## Basics

The **ICL8038** waveform generator is a monolithic integrated circuit capable of producing high accuracy sine, square, triangular, sawtooth and pulse waveforms.
The frequency (or repetition rate) can be selected externally from 0.001Hz to more than 300kHz.
In used configuration, the frequency has been fixed in the audio frequency range 1Hz to 20KHz.
As a quick description of how waveforms are produced, the integrators via comparators create the primary triangle which is then flip-flopped to obtain the square and a smoothing network based on multiple transistors stages to obtain the sine.
The sweep is modulated via a DC voltage. The relative frequency range depends on the capacitor applied.


Four different meshes with different values are needed to get good linearity.
This especially applies to operation as an LFO.
Four different selectable operating modes have been selected.

***Frequency ranges***

The frequency ranges are still raw and are related to the values of the capacitors used in the VCO applied to pin 10 of the ICL8038.

- **HVCO** (*1.6KHz to 26KHz used capacity 2.2uF*)
- **VCO** (*238Hz to 4.1KHz used capacity 220nF*)
- **LFO** (*11Hz to 194Hz used capacity 22nF*)
- **VLFO** (*3Hz to 67Hz used capacity 2nF*)

The selection of the frequency range is set using the micro via the I/O Expander **MCP23S17** and the Quad Bilateral Switch **CD4066B**.
Only one of the four bilateral switches is active defining the frequency range.

***Notice !***
The capacitor values and frequency range are still being refined, so the correct values will only be released upon completion of the design of the VCOs module.


Return to index. [README.md](README.md)