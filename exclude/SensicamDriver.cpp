#include "StdAfx.h"
#include "SensicamDriver.h"
#include "sencam.h"

SensicamDriver::SensicamDriver(void)
{
}

void SensicamDriver::initCamera()
{
	SET_BOARD(0);
}

bool SensicamDriver::openCameraDialog(){
	return true;
}

void SensicamDriver::lockCameraDialog(bool lock){

}

void SensicamDriver::expose(){

}

void SensicamDriver::stop(){
}

int SensicamDriver::getImageStatus(){
	return 0;
}

int SensicamDriver::getImageWidth(){
	return 0;
}

int SensicamDriver::getImageHeight(){
	return 0;
}
void SensicamDriver::readImage(UInt16 *buffer){

}
