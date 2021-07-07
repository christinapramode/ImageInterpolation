# Image Interpolation in C

This project involves developing an algorithm to carry out image interpolation in C, and running the code in a DSP Processor simulator using Texas Instruments' Code Composer Studio.

# Step 1 - Developing the C code

Problem Statement:

Given a grayscale image of size WxH, interpolate into an image of size 2WxH. i.e., for an input image of size 256x256, the output image size would be 512x256. 
The code should fill in the extra output pixels by interpolating using the formula - (a+b+1)/2
  
For more information regarding the basics of images & image processing -
https://visualresources.princeton.edu/making-images/digital-image-basics/ 
  
For more information regarding image interpolation -
https://www.cambridgeincolour.com/tutorials/image-interpolation.htm


The code involves the following steps - 
1. Creating/opening the input ("Image1_256x256.raw") and output files ("Image1_512x256.raw").
2. Reading from the input file (row by row), and storing the pixel data in a pointer array "rev".
3. A function "interpImg", which carries out the interpolation and stores the result in another pointer array "revout".
4. Writing to the output file (row by row).
5. Close all files.

# Step 2 - Running the Code on Ti CCS

