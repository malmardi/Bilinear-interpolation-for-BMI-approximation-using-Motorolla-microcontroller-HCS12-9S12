# Bilinear-interpolation-for-BMI-approximation-using-Motorolla-microcontroller-HCS12-9S12
**Description:**
This project was implemented in the advanced embedded systems course in Spring/2012 at the American University of Sharjah (AUS).
The idea of the project is to use approximation functions to calculate BMI without knowing the exact formula. That said, we used the 
**Bilinear interpolation** to approximate the BMI value, given the values of the weight and height points.

**System Requirements:**

 - Motorola Microcontroller (HCS12/9S12).
 - Weight cell sensor with a resolution of 2.5 mV/0.1 kg, measuring a
   maximum weight of 200 kg.
 - Height cell sensor with resolution 20 mV/1 cm, measuring a maximum height of 250 cm.
 - Weight Cell sensor is connected to ATD-CH0.
 - Height cell sensor is connected to ATD-CH1.

**Language used:** Matlab & C

**Repository Structure:**

 - Report: includes a description of the problem, requirements and results.
 - Motorolla code.c: used to collect the weight and height values from the sensors, then calculate the BMI.
 - points.xlsx: excel file including all the weight/height points.
 - matlab code.m: an implementation of the Bilinear interpolation using matlab.
 


