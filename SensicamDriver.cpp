#include "StdAfx.h"
#include "SensicamDriver.h"
#include "sencam.h"
#include "cam_types.h"

namespace forms2{
	using namespace System;
	using namespace System::Windows::Forms;

	SensicamDriver::SensicamDriver(void){
		mode = NULL_SETTING;
		trig = NULL_SETTING;
		roix1 = NULL_SETTING;
		roix2 = NULL_SETTING;
		roiy1 = NULL_SETTING;
		roiy2 = NULL_SETTING;
		hbin = NULL_SETTING;
		vbin = NULL_SETTING;
	}

	int SensicamDriver::initCamera(){
		SET_BOARD(0);//selects the 0-th PCI board
		//initialize the camera using stored parameters
		int err = SET_INIT(1);
		if (err){
			//initialization returned an error
			MessageBox::Show( String::Concat("Error initializing camera. Error Code: ",err),"Box",MessageBoxButtons::OK);
			return 1;
		}
		err = STOP_COC(0);//prevents unintended acquisition
		if (err){
			MessageBox::Show( String::Concat("Error stopping camera operating code. Error Code: ",err),"Box",MessageBoxButtons::OK);
			return 1;
		}
		if (openCameraDialog()) return 1;	
		return 0;
	}
		
	int SensicamDriver::openCameraDialog(){
		CLOSE_DIALOG_CAM();
		if(OPEN_DIALOG_CAM(NULL,0,NULL)){
			MessageBox::Show("Error opening camera settings dialogue box.","Box",MessageBoxButtons::OK);
			return 1;
		}
		return 0;
	}

	void SensicamDriver::closeCamera(){
		STOP_COC(0);
		LOCK_DIALOG_CAM(0);//neccessary?
		CLOSE_DIALOG_CAM();
		SET_INIT(0);
	}

	void SensicamDriver::lockCameraDialog(bool lock){
		if (lock)
			LOCK_DIALOG_CAM(1);
		else
			LOCK_DIALOG_CAM(0);
	}

	int SensicamDriver::getCols()
	{
		getSettings();
		return 32*(roix2-roix1+1)/hbin;
	}
	
	int SensicamDriver::getRows()
	{ 
		getSettings();
		int rows = 	32*(roiy2-roiy1+1);
		if (roiy2==33)
			rows-=16;
		return rows/vbin;
	}
	bool SensicamDriver::isDouble(){
		getSettings();
		//const int typ = mode & 0x00FF;//byte 0
		const int submode = (mode & 0xFF0000)>>16;//byte 2
		//int dbl = (submode==QE_DOUBLE)? 2:1;
		return (submode==QE_DOUBLE);
	}
	
	void SensicamDriver::getSettings(){
		//char table[300];
		//char* tab = (char *)malloc(300);
		//char** table = &tab;
		//UInt16 *buf = (UInt16 *)malloc(2*dbl*cols*rows*layers);
//		GET_SETTINGS( &mode, &trig, &roix1, &roix2, &roiy1, &roiy2, &hbin, &vbin, table);
	}
}


