# SMPLComp - Simple Compressor
An audio compressor plugin created with [JUCE](https://juce.com/) and forked from (here)[https://github.com/p-hlp/SMPLComp]. 
A feature was added where the compressor is wrapped between an unpinking (-3db/octave hp) and a pinking (-3db/octave lp) filter.

<img src="https://github.com/p-hlp/SMPLComp/blob/master/SMPLComp_Snip.png"  width="60%" height="60%">

## Introduction
This is a simplified version of the [CTAGDRC](https://github.com/p-hlp/CTAGDRC) plugin, which was then modified to add the "pinking" filters.

## Features
- Input Gain
- Threshold/Ratio/Knee
- Attack/Release
- Makeup
- Mix
- Gainreduction/Input/Output Metering

## Added by QuentinFaidide
- Cmake build capabilities
- Pinking and unpinking filters around the compressor processor.

## Notes
- Filtering coefficients for pinking filter are from [here](https://ccrma.stanford.edu/%7Ejos/sasp/Example_Synthesis_1_F_Noise.html).
- The root `CMakelists.txt` was inspired by [this project's cmake]() by Anthony Alfimov. 
- The library used to make plugins is JUCE, and this software leverages the GPL compatibility of the license.