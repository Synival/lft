# lft
Logarithmic Fourier Transform library, designed for music performers

# How to build
As of 2023-03-04, this library can only be compiled in Windows as a DLL. (As a lifelong Linux user, this is unacceptable and must be remedied!)

For Windows:

1. Fetch [MSYS2 MinGW](https://packages.msys2.org/base/mingw-w64-gcc) for your architecture.
2. Fetch [make](https://packages.msys2.org/package/make)
3. Build by typing 'make' in your command prompt of choice.

# What is this?
The "LFT" (Logarithmic Fourier Transform) is a not-so-fast variation on the "FFT" (Fast Fourier Transform) whose aim is to provide output data for logarithmic frequencies rather than linear frequencies. This is specially designed for musical analysis rather than accoustic or signal analysis. The results aren't reversible so it's not useful to modify or filter audio. This library was designed by a musician and programmer - *not a mathematician* - so it's probably not as beautiful or elegant as it could be.

# What's the problem with using an FFT?
I've attempted making a note visualizer using the FFT algorithm multiple times and could never solve these problems:

- For the lower range of sound, the sample size was often too small, producing many false positives.
- For the lower range of sound, the frequency resolution was far too low, so bass notes would never be accurately detected.
- For higher frequencies, the sample size was often much too large, so short high notes would not register quickly.
- For higher frequencies, the frequency resolution was excessively high, so many values produced were completely unnecessary.
- The linear distribution of frequencies (420Hz, 440Hz, 460Hz, 480Hz, etc.) doesn't correspond to the notes I want for musical analysis (415.3Hz, 440Hz, 466.16Hz, 493.88Hz, etc)

# How did the LFT solve this?
Overall differences:
- Notes are distributed logarithmically; each octave has the same number of frequency subdivisions.

For each individual note:
- For a good balance between accuracy and precise timing, the sample size analyzed is multiple of the note's wavelength. In other words, extreme low frequencies use a huge sample size (a lot of time), and extreme high frequencies use a very small sample size (very little time).
- For mid to low frequencies, many data points are skipped when doing calculations to save on processing time without impacting accuracy.

# License?
GPL 3.
