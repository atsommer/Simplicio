#pragma once
#include "Driver.h"
using namespace WINX32Lib;
namespace forms2{
	ref class WinXDriver : Driver
	{
	public:
		WinXDriver(void);
		virtual int initCamera() override;
		virtual int openCameraDialog() override;
		virtual void lockCameraDialog(bool lock) override;
		virtual void closeCamera() override;
		virtual void expose() override;
		virtual void stop() override;
		virtual int getImageStatus() override;
		virtual int getImageWidth() override;
		virtual int getImageHeight() override;
		virtual void readImage(UInt16 *buffer) override;
		virtual String^ getDriverName() override {return gcnew String("Princeton Instruments (WinView)");}
		virtual int armCamera() override;

		//settings
		virtual int getRows() override;
		virtual int getCols() override;
		virtual bool isDouble() override;
		virtual void update() override;
	protected:
		Winx32App^ objApp;	//WinView application
		ExpSetupClass^ objExp;//controls experiment parameters and data acquisition
		DocWindowsClass^ objWins;
        ROIRect^ ROIRect;
		IDocFile^ objDoc1;
        IDocFile^ objDoc2;
        IDocFile^ objDoc3;
		int prevRows;
		int prevCols;
		int prevHbin;
		int prevVbin;
		virtual void getSettings() override;
	};
}
