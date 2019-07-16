#ifndef __LINUXI2CINTERFACE_H  
#define __LINUXI2CINTERFACE_H  


/*
 *  This is a Linux implementation of the I2CInterface class 
 *  It's use the /dev/i2c device what is given as parameter 
 *  Most of the function are not implemented as the linux interface is very limitted 
 *  For more complex actions ( bus abort etc) it is not clear what is implemented. 
 *  But still good enough for simple devices 
 *  For the Raspberry Pi plan is  to use the bmc2835 lib but I wait a little bit with this
 *  to see what will be the best to use with the Raspberry Pi 4 
 *
 *
 *  This file make part of the PeriperalDevice package see repository  
 *  https://github.com/wimbeaumont/PeripheralDevices
 *  For more info see 	the README.md in the top of repository 
 *
 *  version 0.11  : initial version to see if it compiles at all 
 *  version 0.20  : use  LinuxI2c.h to overcome problems with read name clase 
 * (C) Wim Beaumont Universiteit Antwerpen 2019
 *
 * License see
 * https://github.com/wimbeaumont/PeripheralDevices/blob/master/LICENSE
 */

#include "I2CInterface.h"
#include "LinuxI2c.h" 
#define VERSION_LINUXI2CInterface_HDR "2.00" 

class LinuxI2CInterface :public I2CInterface {
    LinuxI2C li2c;

    public :        
    LinuxI2CInterface(char* filedescr ): // file points to the I2C device that is openend  
    getVersion( VERSION_LINUXI2CInterface_HDR,VERSION_LINUXI2CInterface_HDR, __TIME__, __DATE__),li2c( filedescr){

	devinit= !li2c.getDevStatus(); 

    };
    ~LinuxI2CInterface(void){ }	
    // next could perhaps more efficient  but not yet investigated 
virtual int 	frequency (int hz){ return setnotsupported();}		

virtual int     read (int address, char *data, int length, bool repeated=true){
			int l_length;
  			comerr=-1000;
		 	if ( repeated == true ){setnotsupported();}//sets comerr
			else {	comerr=li2c.setaddr(address);}
			if ( comerr ==0){
			   l_length= li2c.linux_read(data, length);			  
			   if(  l_length != length ){
				comerr =-101;
			   }
			}else { comerr=0; } //success 	
			return comerr ; 
		};
virtual int    read (int& data , int ack){ return setnotsupported();}		
				// Read a single byte from the I2C bus. returns the byte read not supported in linux 

virtual int    write (int address, const char *data, int length, bool repeated=false){			
			int l_length;
  			comerr=-1000;
		 	if ( repeated == true ){setnotsupported();}//sets comerr
			else {	comerr=li2c.setaddr(address);}
			if ( comerr ==0){
			   l_length= li2c.linux_write(data, length);
			   if(  l_length != length ){
				comerr =-101;
			   }
			}else { comerr=0; } //success 	
			return comerr ; 		};



virtual int    write (int data){ return setnotsupported();}
		//  Write single byte out on the I2C bus. returns  the ack status  not supported for linux

virtual int    start (void){ return setnotsupported();}
virtual int    stop (void){ return setnotsupported();}
virtual int    transfer (int address, const char *tx_buffer, int tx_length, char *rx_buffer, 
				int rx_length, void* callbackfunction,  bool repeated=false){
            		return setnotsupported();  // seems transfer not supported in Linux or not correctly 
	        };    

virtual int  abort_transfer(void) { return setnotsupported();}
// use lock and unlock from the interface 


virtual void wait_for_ms(int x)  {  usleep(1000*x); }
    
} ;  //end class 


#endif
