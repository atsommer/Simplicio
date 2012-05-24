#pragma once
#include "Driver.h"

namespace forms2{
	ref class TestDriver : Driver
	{
	public:
		TestDriver(void);
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
		virtual String^ getDriverName() override {return gcnew String("No Camera");}
		virtual int armCamera() override;

		//settings
		virtual int getRows() override;
		virtual int getCols() override;
		virtual bool isDouble() override;
		virtual void update() override;
	protected: 
		virtual void getSettings() override;
	};
}
