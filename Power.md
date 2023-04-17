## Power supply

***Initial choice***
As an initial choice I thought that the dual power supply for the linear/analog section should be greater than the positive voltage used by the digital section.
I thought this thing would bring me more room for work. 
For this the whole VCO section was powered with a dual voltage -8V/+8V and digital control section which includes the mC and all the SPIs is instead powered with +5V/0V.

However, this has brought me problems with digital potentiometers that cannot withstand voltages higher than the supply voltage on the R2R ladder.

As visible in the previous version of the diagram, a level voltage shifter based on the LM358 has been used, to bring the variation per divider of the MCP42010 (0 to 5V) to the compatible values for the ICL8038 powered at +8/-8V (3.3V to 8V).
Same problem occurred with the MCP4251 used to manage the duty cycle.
To solve these problems and not further increase the circuit complexity I decided to use the +5/-5V power supply for the VCO section.

***Summing up***

The whole VCO section is powered with a dual voltage -5V/+5V. Swing is then reduced at the final outputs to the standard preamp signal of 2Vpp.
The digital control section which includes the mC and all the SPIs is instead powered with +5V/0V.
An EMC/EMI differential-mode (DM) filter is used on the mains power line and no switching technology is used.

[Return to index.](README.md)
