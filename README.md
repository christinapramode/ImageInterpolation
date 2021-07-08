# Image Interpolation in C

This project involves developing an algorithm to carry out image interpolation in C, running and optimizing the code in a DSP Processor simulator using Texas Instruments' Code Composer Studio v5.5.

<img src="https://user-images.githubusercontent.com/59883696/124708529-06ba1680-df18-11eb-8919-465f4121bf26.png" width="703" height="248">

***

## Step 1 - Developing the C code

### Problem Statement:

Given a grayscale image of size WxH, interpolate into an image of size 2WxH. i.e., for an input image of size 256x256, the output image size would be 512x256. 
The code should fill in the extra output pixels by interpolating using the formula - (a+b+1)/2

#### The code involves the following steps: 
1. Creating/opening the input ("Image1_256x256.raw") and output files ("Image1_512x256.raw").
2. Reading from the input file (row by row), and storing the pixel data in a pointer array "rev".
3. A function "interpImg", which carries out the interpolation and stores the result in another pointer array "revout".
4. Writing to the output file (row by row).
5. Close all files.

#### Refer to "ImageInterp.txt" for the full code

#### References:

For more information regarding the basics of images & image processing - 
- https://visualresources.princeton.edu/making-images/digital-image-basics/ 
  
For more information regarding image interpolation - 
- https://www.cambridgeincolour.com/tutorials/image-interpolation.htm

Codes for reading raw images -
- https://stackoverflow.com/questions/29760779/reproduce-raw-image-c 
- https://stackoverflow.com/questions/26416702/how-can-i-read-a-raw-image-in-c-without-special-libreries

***

## Step 2 - Running and Optimizing the Code on Ti CCS

### Step 2.1 - Running the Code

Before running the code in CCS, ***profiling*** is added to measure the time taken for running the "interpImg" function. 
The header file "<c6x.h>" is included and the 64 bit TSC register (timer) is initialized before calling "interpImg", and ended afterwards. "sumcycles" stores the total cycles taken. 

#### Refer to "ImageInterpCCS.txt" for the full code

### Step 2.2 - Further Optimization of the Code

For further optimization, we use ***intrinsics functions*** to perform SIMD (Single Instruction Multiple Data) operations in the function definition to compute the values of the extra output pixels.

The intrinsics functions used for Image Interpolation include - 

*\_mem4, \_amem4, \_unpklu4, \_unpkhu4, \_swap4, \_shrmb, \_avgu4, \_add4*

Details on C66x intrinsics are available at Texas Instruments' TMS320C6000 Programmer's Guide - 
- https://www.ti.com/lit/ug/spru198k/spru198k.pdf

#### Refer to "ImageInterpOptimized.txt" for the full code

### Optimization Cycles:

<img src="https://user-images.githubusercontent.com/59883696/124746472-865adc00-df3e-11eb-9250-7f4a2ae95fc3.png" width="468" height="214">

#### Note: 
The values for optimization levels 0, 1, 2, 3 were obtained by changing the levels in the CCS IDE properties window. (Code used - "ImageInterpCCS.txt")

The value for optimization level 4 was obtained by selecting level 3 in the CCS IDE properties window and using the code - "ImageInterpOptimized.txt", i.e. the code using the intrinsics function.

DSP Simulator details - Device Family: "C6000" , Variant: "Generic C66xx Device", Target Configuration: "C6678 Device Cycle Approximate Simulator", "Little Endian"

***

For clarifications, contact me at <christinapramode@gmail.com>
