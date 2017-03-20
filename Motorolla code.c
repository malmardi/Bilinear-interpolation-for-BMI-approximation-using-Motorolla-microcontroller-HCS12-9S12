#include <D12_LCD.h>
void delay_halfsec(void)
{
 int i;
 for(i=0; i<50000; i++)delay_10usec();
}
void delay_100usec(void)
{
 int i;
 for(i=0; i<10; i++)delay_10usec();
} 
void initialize_ADC(void)
{
 ATD0CTL2 = 0xC0; // power up ADC, disable interrupts
 delay_100usec(); // wait for ADC to warm up
 ATD0CTL3 = 0x08; // select active background mode 1 conv
 ATD0CTL4 = 0x2B; // sample time 2 ADC clock, prescale of 11, 10-bit
}
float ADC_CONVERT_W(void)
{
 char *Voutbuf;
 int *status;
 float weight;
 clr_disp();
 while((PTH&0X04) != 0X04){
 	lcd_print_txt("Weight (Kg)= ", LINE1);
    ATD0CTL5 = (0x86); // channel no. and justification
    while(!(ATD0STAT0 & 0x80)); // wait for conversion to finish
	weight = ATD0DR0*0.2;
	if(weight>200){
		weight = 200;
	}
	else if(weight<=0){
		weight = 10;
	}
    Voutbuf = ftoa(weight, status);
 	lcd_print_txt(Voutbuf, LINE2);
	put_char (' ');
	put_char ('K');
	put_char ('g');
	delay_halfsec();
	clr_disp();
	lcd_print_txt("Are you ready?", LINE1);
	lcd_print_txt("Put DP3 to high", LINE2);
	delay_halfsec();
	clr_disp();
 }
 return(weight); // get and return the value to the caller
}

float ADC_CONVERT_H(void)
{
 char *Voutbuf;
 int *status;
 float height;
 clr_disp();
 while((PTH&0X02) != 0X02){
 	lcd_print_txt("Height (M)= ", LINE1);
    ATD0CTL5 = (0x87); // channel no. and justification
    while(!(ATD0STAT0 & 0x80)); // wait for conversion to finish
	height = ATD0DR0*0.0025;
	if(height > 2.5){
		height = 2.5;
	}
	else if(height <= 0){
		height = 0.1;
	}
    Voutbuf = ftoa(height, status);
 	lcd_print_txt(Voutbuf, LINE2);
	put_char (' ');
	put_char ('M');
	delay_halfsec();
	clr_disp();
	lcd_print_txt("Are you ready?", LINE1);
	lcd_print_txt("Put DP2 to high", LINE2);
	delay_halfsec();
	clr_disp();
 }
 return(height); // get and return the value to the caller 
}
void welcome_screen(void){
	 clr_disp();
	 lcd_print_txt("Welcome to the", LINE1);
	 lcd_print_txt("BMI calculator", LINE2);
	 delay_halfsec();
	 clr_disp();
	 lcd_print_txt("Ready to start ?", LINE1);
	 lcd_print_txt("Put DP1 to high", LINE2);
	 while((PTH&0X01) != 0X01);
}
void BMI_CHECK_DISP(float BMI, float weight, float height){
 	 char *Voutbuf;
 	 int *status; 	 
	 clr_disp();
	 
	 while((PTH&0X08) != 0X08){
	 Voutbuf = ftoa(weight, status);
		 lcd_print_txt(Voutbuf, LINE2);
	 delay_halfsec();
	 clr_disp();
	 Voutbuf = ftoa(height, status);
		 lcd_print_txt(Voutbuf, LINE2);
	 delay_halfsec();
	 clr_disp();
 	 Voutbuf = ftoa(BMI, status);
		 lcd_print_txt(Voutbuf, LINE2);
	 delay_halfsec();
	 clr_disp();
	 if(BMI<=16.5){
        
		PORTB = 0x01;
	 }
	 else if(BMI>16.5 && BMI<=18.5){
	
	PORTB = 0x02;
	 }
	 else if(BMI>18.5 && BMI<=25.0){
	
	PORTB = 0x04;
	 }
	 else if(BMI>25.0 && BMI<=30.0){
	
	PORTB = 0x08;
	 }
	 else if(BMI>30.0 && BMI<=35.0){
	
	PORTB = 0x10;
	 }
	 else if(BMI>35.0 && BMI<=40.0){
	
	PORTB = 0x20;
	 }
	 else if(BMI>40){
	
	PORTB = 0x40;
	 }
	 delay_halfsec();
	 clr_disp();
	
delay_halfsec();
	 clr_disp();
	 }
	 PORTB = 0x00;
}

float BMI_CALCULATE(float height, float weight){
	  float BMI_value;
	  BMI_value = weight/(height*height);
	  return (BMI_value);
}
void init_ports(void){
DDRB = 0XFF;
DDRJ = 0XFF;
DDRP = 0XFF;
DDRH = 0X00;
PTJ = 0X00;
PTP = 0XFF;
}
 void main()
{
float height;
float weight;
float bmi_value;
init_ports();
init_lcd();
initialize_ADC();
  
 while(1)
 {
  		welcome_screen(); 
  		height = ADC_CONVERT_H(); 
		weight = ADC_CONVERT_W();
  	    bmi_value = BMI_CALCULATE(height, weight);
		BMI_CHECK_DISP(bmi_value, weight, height);
  
 }
}
