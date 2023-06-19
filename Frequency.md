## Frequency Counter

The purpose of this module is to communicate the current frequencies of the VCOs to the PC.

***Implementation via CCP module (Capture / Compare/ PWM) as "Initial choice"***

My intention was to use the Capture mode of the two available CCPs,
in particular the CCP2 combined with the Timer3 to calculate the frequency of the 5V/0 square conditioned signal made compatible with the digital input.

I didn't want to use other external components, thus subtracting other GPIOs from the uC.<BR>
My choice was to directly use the FOsc of 48Mhz / TOsc of 12Mhz on the Timer3.

The four operating ranges of the VCOs would have been managed with different samplings of the CCP.

- **HVCO** Capture mode: every 16th rising edge
- **VCO** Capture mode: every 4th rising edge
- **LFO** Capture mode: every rising edge
- **VLFO** Capture mode: every rising edge

With the 16-bit Timer3 and associated to the uC clock oscillator :

12Mhz/64K = 183 Timer3 Overflows per second.
With : 1/183 = 5.4644~ ms for each Overflow.

In the case of management with a single Overflow, this is the maximum time available to the CCP2.<BR>
So the minimum frequencies with respect to the three sampling ratios :

- 1:1 every rising edge 183 Hz
- 1:4 every 4th rising edge 732 Hz
- 1:16 every 16th rising edge 2.928 KHz

In VLFO mode the minimum frequency is ~3Hz, so we're not there.

The problem is Timer3 is the reference frequency which is very high.

***Reference 16bit Timer with managed Overflows***

To solve the problem I thought if it was possible to use a management with the managed Overflow of the same Timer3.

- With double Overflow management, the maximum period would be : 10.9289 ms for a minimum frequency of 91.5 Hz
- With triple Overflow management, the maximum period would be : 16.3932 ms for a minimum frequency of 61 Hz
- With a management of ten Overflows the maximum period would be : 54.644 ms for a minimum frequency of 18.3 Hz

This added to the fact that the Timer3 has the possibility to be managed via Prescaler 1:2, 1:4, 1:8 I could have achieved the goal,
but at the cost of a high computational complexity in the uC and a high imprecision given by the decimals.

So I decided to abandon the solution via CCP.

***Timer1 with external quartz 32.765Hz as RTC***

The Timer1 of the micro has the possibility of advancing with the system clock but also with an external quartz.
In this case I used the classic 32.768Khz RTC quartz. This technique is extensively described in the PIC18F4550 datasheet on page 131, paragraph 12.3.

By setting the Timer1 register with an initial prescaler of 0x8000 (32768) we obtain that each Timer1 overflow corresponds exactly to one second.
This is why it is called RTC crystal.

In addition to Timer1, Timer0 configured at 8 bit is used to take the clock from pin T0CKI as input.
This input clock is actually the appropriate 0/5V square rectified output for the VCO's frequency counter.

The overflows of Timer0 in the period of one second are counted, then in the overflow of Timer1.

The final frequency will simply be:

- FreqHz = <Number Overflows Timer0> * 256 + Timer0;

This is because the calculation is done at the timer1 overflow which is one second.

[Return to index.](README.md)




