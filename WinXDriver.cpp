#include "StdAfx.h"
#include "WinXDriver.h"

using namespace System::Runtime::InteropServices;
using namespace WINX32Lib;
using namespace KINETICSTOFRAMESLib;
using namespace System::Windows::Forms;
using namespace System;


namespace forms2{
	WinXDriver::WinXDriver(void)
	{
			objApp=gcnew Winx32AppClass();
			objWins=gcnew DocWindowsClass();	

			objExp = gcnew ExpSetupClass();
			ROIRect = (ROIRectClass^) objExp->GetROI(1);
	}
	int WinXDriver::initCamera()
	{
		/*
		if (objApp->CountOpenDocs()>0)
        {
			short pcDocs = 1;
			objApp->CloseOpenDocs(pcDocs);
			//closes all opened windows
		}
		*/
		int err=0;
		try{
			objExp->Start(objDoc1);
			objExp->Stop();
		}catch (System::Runtime::InteropServices::COMException ^e){
			err = 1;		
		}
		if (!err){
			//Store current parameters to detect changes later
			prevRows = getRows();
			prevCols = getCols();
			prevVbin = vbin;
			prevHbin = hbin;
		}
		return err;
	}

	int WinXDriver::openCameraDialog()
	{
		return 0;
	}
	void WinXDriver::lockCameraDialog(bool lock)
	{
	}
	void WinXDriver::closeCamera()
	{
		if (objDoc1 != nullptr)
		try{
			objDoc1->Close();
		}catch (System::Runtime::InteropServices::COMException ^){;}
	}
	void WinXDriver::expose()
	{
		objExp->Start(objDoc1);
	}
	void WinXDriver::stop()
	{
		objExp->Stop();
	}
	int WinXDriver::getImageStatus()
	{
		short status =0; 
		int running = (int) objExp->GetParam(WINX32Lib::EXP_CMD::EXP_RUNNING, status);
		if (status !=0)
			return IMAGE_ERROR;
		if (running)
			return CAMERA_BUSY;
		else{
			
			return CAMERA_IDLE;		
		}
	}
	int WinXDriver::getImageWidth()
	{//assumes there is a DocFile open
		short stat;
		int width = (int) objDoc1->GetParam(WINX32Lib::DM_CMD::DM_XDIM,stat);
		return width;
	}
	int WinXDriver::getImageHeight()
	{
		short stat;
		int height = (int) objDoc1->GetParam(WINX32Lib::DM_CMD::DM_YDIM,stat);
		return height;
	}
	void WinXDriver::readImage(UInt16 *buffer)
	{
		Object^ obFrame;//object to hold the array of data
		objDoc1->GetFrame(1,obFrame);
		Array^ arFrame = (Array^) obFrame;

		//Copy the Array arFrame to the buffer
		Int16^ pix;
		int rows = getRows();
		int cols = getCols();
		for (int x=0;x<cols;x++)
			for (int y=0;y<rows;y++)
			{
				//pix = (Double^)objDoc1->GetPixel(1,i+1,j+1);<--super slow!
				pix = (Int16^) arFrame->GetValue(x,y);
				buffer[x + y*cols]=*pix;
			}
	}
	int WinXDriver::armCamera()
	{
		//Check if the ROI was changed
		int rows = getRows();
		int cols = getCols();
		if (rows != prevRows || cols != prevCols || hbin != prevHbin || vbin != prevVbin)
		{
			//objDoc1 = (IDocFile^) gcnew DocFile();
			objDoc1->Close();
			prevRows = rows;
			prevCols = cols;
			prevVbin = vbin;
			prevHbin = hbin;
		}
		return 0;
	}
	int WinXDriver::getRows()
	{
	//this function determines the number of rows of data to be taken
		getSettings();
		int rows = (roiy2 - roiy1+1)/vbin;
		//Int32^ r32 = rows;
		//MessageBox::Show(r32->ToString(),"rows",MessageBoxButtons::OK);
		return rows;
	}
	int WinXDriver::getCols()
	{
		getSettings();
		int cols = (roix2 - roix1+1)/hbin;
		//Int32^ c32 = cols;
		//MessageBox::Show(c32->ToString(),"cols",MessageBoxButtons::OK);
		return cols;
	}

	bool WinXDriver::isDouble()
	{
		return false;
	}
	void WinXDriver::update(){}
	void WinXDriver::getSettings()
	{
		short stat;
		int useROI = (int) objExp->GetParam(WINX32Lib::EXP_CMD::EXP_USEROI,stat);
		if (useROI)
		{
			ROIRect = objExp->GetROI(1);
			double top, left, bottom, right;
			int xg,yg;		
			ROIRect->Get(top,left,bottom,right,xg,yg);
			roix1 = (int) top;
			roiy1 = (int) left;
			roix2 = (int) right;
			roiy2 = (int) bottom;
			hbin = xg;
			vbin = yg;
			//Int32^ w32 = hbin;
			//MessageBox::Show(w32->ToString(),"hbin",MessageBoxButtons::OK);
		}
		else
		{
			roix1 = 1;
			roiy1 = 1;
			roix2 = (int) objExp->GetParam(WINX32Lib::EXP_CMD::EXP_XDIM,stat);
			roiy2 = (int) objExp->GetParam(WINX32Lib::EXP_CMD::EXP_YDIM,stat);
			//roix2 = (int) objDoc1->GetParam(WINX32Lib::DM_CMD::DM_XDIM,stat);
			//roiy2 = (int) objDoc1->GetParam(WINX32Lib::DM_CMD::DM_YDIM,stat);
			hbin = 1;
			vbin = 1;
		}
			
	}
}
