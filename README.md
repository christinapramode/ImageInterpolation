# Image Interpolation in C

This project involves developing an algorithm to carry out image interpolation in C, and running the code in a DSP Processor simulator using Texas Instruments' Code Composer Studio.

![Picture1](https://user-images.githubusercontent.com/59883696/124708529-06ba1680-df18-11eb-8919-465f4121bf26.png)

## Step 1 - Developing the C code

### Problem Statement:

Given a grayscale image of size WxH, interpolate into an image of size 2WxH. i.e., for an input image of size 256x256, the output image size would be 512x256. 
The code should fill in the extra output pixels by interpolating using the formula - (a+b+1)/2
  
For more information regarding the basics of images & image processing -
https://visualresources.princeton.edu/making-images/digital-image-basics/ 
  
For more information regarding image interpolation -
https://www.cambridgeincolour.com/tutorials/image-interpolation.htm


#### The code involves the following steps - 
1. Creating/opening the input ("Image1_256x256.raw") and output files ("Image1_512x256.raw").
2. Reading from the input file (row by row), and storing the pixel data in a pointer array "rev".
3. A function "interpImg", which carries out the interpolation and stores the result in another pointer array "revout".
4. Writing to the output file (row by row).
5. Close all files.

#### Refer to "ImageInterp.txt" for the full code.

Codes for reading raw images -
- https://stackoverflow.com/questions/29760779/reproduce-raw-image-c 
- https://stackoverflow.com/questions/26416702/how-can-i-read-a-raw-image-in-c-without-special-libreries


## Step 2 - Running the Code on Ti CCS

