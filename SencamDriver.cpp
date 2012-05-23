#include "stdafx.h"
#include "SencamDriver.h"
#include "sencam.h"
#include "cam_types.h"

namespace forms2{
	using namespace System;
	using namespace System::Windows::Forms;
	SencamDriver::SencamDriver(void){
		mode = NULL_SETTING;
		trig = NULL_SETTING;
		roix1 = NULL_SETTING;
		roix2 = NULL_SETTING;
		roiy1 = NULL_SETTING;
		roiy2 = NULL_SETTING;
		hbin = NULL_SETTING;
		vbin = NULL_SETTING;
	}

	int SencamDriver::initCamera(){
		SET_BOARD(0);//selects the 0-th PCI board
		//initialize the camera using stored parameters
		int err = SET_INIT(1);
		if (err == -1){
			MessageBox::Show( String::Concat("No camera detected"),"Box",MessageBoxButtons::OK);
			return NO_CAMERA;
		}
		if (err){
			//initialization returned an error
			MessageBox::Show( String::Concat("Error initializing camera. Error Code: ",err),"Box",MessageBoxButtons::OK);
			return INIT_ERROR;
		}
		err = STOP_COC(0);//prevents unintended acquisition
		if (err){
			MessageBox::Show( String::Concat("Error stopping camera operating code. Error Code: ",err),"Box",MessageBoxButtons::OK);
			return INIT_ERROR;
		}
		if (openCameraDialog()) return INIT_ERROR;	
		return 0;
	}

	int SencamDriver::openCameraDialog(){
		CLOSE_DIALOG_CAM();
		if(OPEN_DIALOG_CAM(NULL,0,NULL)){
			MessageBox::Show("Error opening camera settings dialogue box.","Box",MessageBoxButtons::OK);
			return 1;
		}
		return 0;
	}
	void SencamDriver::lockCameraDialog(bool lock){
		if (lock)
			LOCK_DIALOG_CAM(1);
		else
			LOCK_DIALOG_CAM(0);
	}
	void SencamDriver::closeCamera(){
		STOP_COC(0);
		LOCK_DIALOG_CAM(0);//neccessary?
		CLOSE_DIALOG_CAM();
		SET_INIT(0);
	}
	int SencamDriver::armCamera(){
		int err = STOP_COC(0);	
		return (err != 0);
	}
	void SencamDriver::expose(){
		RUN_COC(4);
	}
	void SencamDriver::stop(){
		STOP_COC(0);
	}
	int SencamDriver::getImageStatus(){
		int picstat;
		int errS=GET_IMAGE_STATUS(&picstat);
		if (errS !=0)
			//error occured
			return IMAGE_ERROR;
		
		if ( (picstat&0x02) == 0)
			return CAMERA_IDLE;
		else
			return CAMERA_BUSY;
	}
	int SencamDriver::getImageWidth(){
		int width, height;
		GET_IMAGE_SIZE(&width,&height);
		return width;
	}
	int SencamDriver::getImageHeight(){
		int width, height;
		GET_IMAGE_SIZE(&width,&height);
		return height;
	}
	void SencamDriver::readImage(UInt16 *buffer){
		int width, height;
		GET_IMAGE_SIZE(&width,&height);
		READ_IMAGE_12BIT(0,width,height,buffer);
	}

	//settings
	int SencamDriver::getRows(){
		getSettings();
		int rows = 	32*(roiy2-roiy1+1);
		if (roiy2==33)
			rows-=16;
		return rows/vbin;
	}

	int SencamDriver::getCols(){
		getSettings();
		return 32*(roix2-roix1+1)/hbin;
	}

	bool SencamDriver::isDouble(){
		getSettings();
		//const int typ = mode & 0x00FF;//byte 0
		const int submode = (mode & 0xFF0000)>>16;//byte 2
		//int dbl = (submode==QE_DOUBLE)? 2:1;
		return (submode==QE_DOUBLE);
	}
	void SencamDriver::update(){

	}
	
	void SencamDriver::getSettings(){
		char table[300];
		int _mode;
		int _trig;
		int _roix1;
		int _roix2;
		int _roiy1;
		int _roiy2;
		int _hbin;
		int _vbin;
		GET_SETTINGS( &_mode, &_trig, &_roix1, &_roix2, &_roiy1, &_roiy2, &_hbin, &_vbin, (char**) table);
		mode = _mode;
		trig = _trig;
		roix1 = _roix1;
		roix2 = _roix2;
		roiy1 = _roiy1;
		roiy2 = _roiy2;
		hbin = _hbin;
		vbin = _vbin;
	}
}