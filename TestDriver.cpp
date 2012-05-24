#include "StdAfx.h"
#include "TestDriver.h"

using namespace System::Windows::Forms;
using namespace System;


namespace forms2{
	TestDriver::TestDriver(void)
	{
		
	}
	int TestDriver::initCamera()
	{
		return 0;
	}

	int TestDriver::openCameraDialog()
	{
		return 0;
	}
	void TestDriver::lockCameraDialog(bool lock)
	{
	}
	void TestDriver::closeCamera()
	{

	}
	void TestDriver::expose()
	{
	}
	void TestDriver::stop()
	{
	}
	int TestDriver::getImageStatus()
	{
		return CAMERA_IDLE;		
	}
	int TestDriver::getImageWidth()
	{
		return getCols();
	}
	int TestDriver::getImageHeight()
	{
		return getRows();
	}
	void TestDriver::readImage(UInt16 *buffer)
	{
		int rows = getRows();
		int cols = getCols();
		for (int x=0;x<cols;x++)
			for (int y=0;y<rows;y++)
			{
				buffer[x + y*cols]=7;
			}
	}
	int TestDriver::armCamera()
	{
		return 0;
	}
	int TestDriver::getRows()
	{
	//this function determines the number of rows of data to be taken
		getSettings();
		int rows = (roiy2 - roiy1+1)/vbin;
		return rows;
	}
	int TestDriver::getCols()
	{
		getSettings();
		int cols = (roix2 - roix1+1)/hbin;
		return cols;
	}

	bool TestDriver::isDouble()
	{
		return false;
	}
	void TestDriver::update(){}
	void TestDriver::getSettings()
	{
		roix1 = 1;
		roiy1 = 1;
		roix2 = 512;
		roiy2 = 512;
		hbin = 1;
		vbin = 1;			
	}
}
