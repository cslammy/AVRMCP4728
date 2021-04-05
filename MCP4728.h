/*
 * 
 *
 * Created: 4/5/2021 12:55:43 PM
 *  Author: clamm
 */ 


#ifndef MCP4728_H_
#define MCP4728_H_

void SingleChanWrite4728(uint16_t chdata);

void FastWrite4728(uint16_t chA, uint16_t chB, uint16_t chC, uint16_t chD);

void SingleChanSelect4728(uint16_t chdata, uint8_t channel);




#endif /* MCP4728_H_ */