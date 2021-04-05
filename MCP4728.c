/*
 * mcp4728-test.c
 * https://www.microchip.com/wwwproducts/en/MCP4728
 * Created: 4/2/2021 10:39:14 AM  UNTESTED!
 SEE PROJECTS FOR WORKING CODE....THIS LIBRARY IS DERIVED FROM THAT.
 * Author : clamm
 UNTESTED AS OF 4-5-21
 */ 

#include <avr/io.h>
#include <stdint.h>
#define ADDR 0xC0  // addr of IC IS x60; shift << 1
#include "I2C.h"





uint16_t data[4]; // array to hold values for "multi channel write"
uint16_t chdata; // holds data for single ch write
uint16_t mybytes = 0;

//TEST
//FastWrite4728(4000,7000,4000,7000); // test fastwrite feature.  
// SingleChanSelect4728(4000,1);


 

 void FastWrite4728(uint16_t chA, uint16_t chB, uint16_t chC, uint16_t chD)
{
	 
	 I2C_Init();

	 I2C_Start();
	 	
	 I2C_Write(ADDR);
		 
	 //write these values to memory
	 data[0] = chA;
	 data[1] = chB;
	 data[2] = chC;
	 data[3] = chD;
	 
	 uint8_t x = 0;
	 uint8_t MSB = 0;
	 uint8_t LSB = 0;
	 
	 if (x >= 4)
	   {
		   x = 0;
	   }

	 while (x < 4)
	 {
		    
	 //isolate MSB and write
    
	 MSB = (data[x] >> 8) ;
         
		 /*if data at input greater than 4096 
		 IT will cause output errorS unless we do this.
	 	 */
		  if (data[x] > 4096)
	 	 {
		 	 MSB = 0x0F;
	 	 }	 
	 
	 // write USING I2C
	 I2C_Write(MSB);
	 
	 //isolate LSB AND WRITE
	 LSB = data[x] & 0x00FF;
	 
	 //write USING I2C
	 I2C_Write(LSB);
	 
	 //
	   x++;
     }
}


 void SingleChanSelect4728(uint16_t chdata, uint8_t channel) 
     {
		  /* this paradigm allows you to write to single channels with enhanced settings.
		  right now it's hard coded to send a 12 bit value (chdata) to a channel (channel) 
		  and shut other 3 channels off
		  
		  But more coding could be done to change that pretty easily.
		  
		  EG: for MSB you can change more stuff by messing w/ MSB bits 15-12.
		  bit 15--ref VDD=0 or 2.3V=1
		  bit 14,13--power saving mode data
		  bit 12--gain 0=x1  1=x2
		  
          I don't have any immediate use for this so for now I am just leaving this as is
		  
		  You can also get different behavior on the 4728 by taking LDA pin high (it's usually set low)		  
          But that would consume another AVR pin.....
		  
		  For example: with LDA pin set high you can issue a single "turn on channel and write" to just one channel
		  other channels are not impacted.....
          */
		  void SingleChanWrite4728(uint16_t chdata);
		
		   uint8_t MSB1 = 0;
		   uint8_t LSB1 = 0;
		   mybytes = chdata;		   
           if (chdata > 4096)
          		  {
	          		  MSB1 = 0x0F;
          		  }
             
	     		
			 if (channel == 1)
				{
				I2C_Write(0b01000010); // turn on chan1 & write
				
				MSB1 = (chdata >> 8) ;
                I2C_Write(MSB1);
                LSB1 = chdata & 0x00FF;
	            I2C_Write(LSB1);   
				I2C_Write(0b01000101); // write to chan2
				I2C_Write(0);
				I2C_Write(0);
				I2C_Write(0b01000111); // write to chan3
                I2C_Write(0);
                I2C_Write(0);								
				I2C_Write(0b01000001); // write to chan0
				I2C_Write(0);
				I2C_Write(0);				
				}
			
            if (channel == 2)
            	{
	            I2C_Write(0b01000100); // turn on Chan2 & write
				MSB1 = (chdata >> 8) ;
				I2C_Write(MSB1);
				LSB1 = chdata & 0x00FF;
				I2C_Write(LSB1);                
				I2C_Write(0b01000111); // write to chan3
				I2C_Write(0);
				I2C_Write(0);                
                I2C_Write(0b01000001); // write to chan0
                I2C_Write(0);
                I2C_Write(0);
			    I2C_Write(0b01000011); // write to chan1	
				I2C_Write(0);
				I2C_Write(0);				
				}		

            if (channel == 3)
                {
	            I2C_Write(0b01000110); // turn on and write to ch3
				MSB1 = (chdata >> 8) ;
				I2C_Write(MSB1);
				LSB1 = chdata & 0x00FF;
				I2C_Write(LSB1);				
		        I2C_Write(0b01000001); // write to chan0
				I2C_Write(0);
				I2C_Write(0);			    
				I2C_Write(0b01000011); // write to chan1
				I2C_Write(0);
				I2C_Write(0);				
			    I2C_Write(0b01000101); // write to chan2
				I2C_Write(0);
				I2C_Write(0);				
                }
			if (channel == 0)
			   {
				I2C_Write(0b01000000)  ; 
                MSB1 = (chdata >> 8) ;
                I2C_Write(MSB1);
                LSB1 = chdata & 0x00FF;
				I2C_Write(LSB1);
                I2C_Write(0b01000011); // no write to chan1
		        I2C_Write(0);
		        I2C_Write(0);
			    I2C_Write(0b01000101); // no write to chan2
			    I2C_Write(0);
				I2C_Write(0);
                I2C_Write(0b01000111); // no write to chan3
                I2C_Write(0);
                I2C_Write(0);
			   }
           
       
        

}

