# SMPLComp - Simple Compressor
An audio compressor plugin created with [JUCE](https://juce.com/) and forked from [here](https://github.com/p-hlp/SMPLComp). 
A feature was added after fork where the compressor is wrapped between an unpinking (-3db/octave hp) and a pinking (-3db/octave lp) filter.
I'd like to remind that this plugins is 99.999999% Phillip Lamp's amazing own work and that this fork has only seen minor changes to 
play with the pinking idea and change the build system. So please, consider Phillip the sole author and give him all the credit,
and if you're curious I invite you to see his [CTAGDRC repo](https://github.com/p-hlp/CTAGDRC) where the DSP is detailed.

## Introduction
This is a simplified version of the [CTAGDRC](https://github.com/p-hlp/CTAGDRC) plugin, which was then modified to be wrapped between "pinking" filters.

## Purpose of the fork
Most music frequency response approximately follow a 3 dB/octave slope down from DC to Nyquist (the shape of pink noise),
and most Compressors/Limiters directly treat this signal where frequencies are not equally represented. This has the consequence that for example, a kick in electronic music might be responsible for most of the gain reduction, and higher frequencies in a sane mix are less likely to participate.
This is where the pinking idea comes in, where we compress the signal after this 3dB/octave slope was removed,
in order to give all frequencies of a normal sounding music the same chance to participate in the gain reduction of the master bus compressor.
This "unpinking" is then reversed after the gain reduction of the compressor was applied to restore the frequency response back to normal.
This process does not pretend to replace vanilla compressors, but covers a use case I personnally find interesting. 

## Features
- Input Gain
- Threshold/Ratio/Knee
- Attack/Release
- Makeup
- Mix
- Gainreduction/Input/Output Metering

## Added by Quentin Faidide
- Cmake build capabilities
- Pinking and unpinking filters around the compressor processor.

## Notes
- Filtering coefficients for pinking filter are from [here](https://ccrma.stanford.edu/%7Ejos/sasp/Example_Synthesis_1_F_Noise.html).
- The root `CMakelists.txt` was inspired by [this project's cmake]() by Anthony Alfimov. 
- The library used to make plugins is JUCE, and this software leverages the GPL compatibility of the license.