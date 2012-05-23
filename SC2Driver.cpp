#include "stdafx.h"
#include "SC2Driver.h"


namespace forms2{
	using namespace System;
	using namespace System::Windows::Forms;
	SC2Driver::SC2Driver(void){
		//mode = NULL_SETTING;
		//trig = NULL_SETTING;
		roix1 = NULL_SETTING;
		roix2 = NULL_SETTING;
		roiy1 = NULL_SETTING;
		roiy2 = NULL_SETTING;
		hbin = NULL_SETTING;
		vbin = NULL_SETTING;
		
		sBufNr = -1;
		hDialog= NULL;
		strGeneral.wSize = sizeof(strGeneral);// initialize all structure size members
		strGeneral.strCamType.wSize = sizeof(strGeneral.strCamType);
		strCamType.wSize = sizeof(strCamType);
		strSensor.wSize = sizeof(strSensor);
		strSensor.strDescription.wSize = sizeof(strSensor.strDescription);
		strDescription.wSize = sizeof(strDescription);
		strTiming.wSize = sizeof(strTiming);
		strStorage.wSize = sizeof(strStorage);
		strRecording.wSize = sizeof(strRecording);
		strImage.wSize = sizeof(strImage);
		strImage.strSegment[0].wSize = sizeof(strImage.strSegment[0]);
		strImage.strSegment[1].wSize = sizeof(strImage.strSegment[0]);
		strImage.strSegment[2].wSize = sizeof(strImage.strSegment[0]);
		strImage.strSegment[3].wSize = sizeof(strImage.strSegment[0]);
	}
	
	int SC2Driver::initCamera(){
		//HANDLE hCam;
		
		hCam = NULL;
		int iRetCode = PCO_OpenCamera(&hCam, 0);// Try to open camera
		if (iRetCode != PCO_NOERROR)
		{
			disconnected();
			MessageBox::Show( String::Concat("No camera detected or other initialization error."),"Box",MessageBoxButtons::OK);
			return INIT_ERROR;
		}
		else                                 // if successfull...
		{
			iRetCode = PCO_GetGeneral(hCam, &strGeneral);// Get infos from camera
			if (iRetCode != PCO_NOERROR)
			{
			  disconnected();
			  return INIT_ERROR;
			}
			iRetCode = PCO_GetCameraType(hCam, &strCamType);
			if (iRetCode != PCO_NOERROR)
			{
			  disconnected();
			  return INIT_ERROR;
			}
			iRetCode = PCO_GetSensorStruct(hCam, &strSensor);
			if (iRetCode != PCO_NOERROR)
			{
			  disconnected();
			  return INIT_ERROR;
			}
			iRetCode = PCO_GetCameraDescription(hCam, &strDescription);
			if (iRetCode != PCO_NOERROR)
			{
			  disconnected();
			  return INIT_ERROR;
			}
			iRetCode = PCO_GetTimingStruct(hCam, &strTiming);
			if (iRetCode != PCO_NOERROR)
			{
			  disconnected();
			  return INIT_ERROR;
			}
			iRetCode = PCO_GetRecordingStruct(hCam, &strRecording);
			if (iRetCode != PCO_NOERROR)
			{
			  disconnected();
			  return INIT_ERROR;
			}
		}
		/*
		if (strCamType.wCamType == CAMERATYPE_PCO_USBPIXELFLY)
			MessageBox::Show("Pixelfly.usb detected","Box",MessageBoxButtons::OK);
		*/

		return 0;
	}
	void SC2Driver::disconnected(){
		//connection to camera was lost
	}
	int SC2Driver::openCameraDialog(){
		PCO_CloseDialogCam(hDialog);
		HWND hmain = 0;
		int err = PCO_OpenDialogCam(&hDialog, hCam, 0, 0,0, 0, 400, 300, "SC2 Camera control window");
		return err;
	}
	void SC2Driver::lockCameraDialog(bool lock){
		PCO_EnableDialogCam(hDialog, !lock);
	}
	void SC2Driver::closeCamera(){
		PCO_CloseCamera(hCam);
	}
	void SC2Driver::expose(){
		DWORD wImage=0;
		PCO_AddBuffer(hCam, wImage, wImage, sBufNr);
		
	}
	void SC2Driver::stop(){
		PCO_SetRecordingState(hCam, 0x0000);
		PCO_CancelImages(hCam);
		//PCO_FreeBuffer(hCam, sBufNr);
		
	}
	int SC2Driver::getImageStatus(){
		//return Driver::CAMERA_IDLE;
		DWORD err = WaitForSingleObject(hEvent, 2000);
		//return Driver::CAMERA_IDLE;
		DWORD statDLL, statDrv;
		err = PCO_GetBufferStatus(hCam, sBufNr, &statDLL, &statDrv);
		if (err){
			String^ layerStr;
			if (err & PCO_ERROR_FIRMWARE)		layerStr = gcnew String("Firmware");
			else if (err & PCO_ERROR_DRIVER)	layerStr = gcnew String("Driver");
			else if (err & PCO_ERROR_SDKDLL)	layerStr = gcnew String("SDK-dll");
			else if (err & PCO_ERROR_APPLICATION) layerStr= gcnew String("application");

			//MessageBox::Show(String::Concat("Layer: ",layerStr),"Box",MessageBoxButtons::OK);

			char errorText[1000];
			PCO_GetErrorText(err, errorText, 1000);
			MessageBox::Show(String::Concat(gcnew String(errorText)," sBufNr = ",(int) sBufNr),"Box",MessageBoxButtons::OK);

			return Driver::IMAGE_ERROR;
		}
		if (statDLL)// & (0x40000000 | 0x00008000))
			return Driver::CAMERA_IDLE;
		else
			return Driver::CAMERA_BUSY;
	}
	int SC2Driver::getImageWidth(){
		
		return getCols();
	}
	int SC2Driver::getImageHeight(){
		int dbl = isDouble() ? 2 : 1;
		return getRows()*dbl;
	}
	void SC2Driver::readImage(UInt16 *buffer){
		
	}
	int SC2Driver::armCamera(){
		PCO_ArmCamera(hCam);
		sBufNr = -1;//allocate a new buffer
		DWORD size = getRows()*getCols()*isDouble()*sizeof(WORD);
		//wBuf;//pointer to image data, wBuf[0...size]
		//HANDLE hEvent;
		PCO_FreeBuffer(hCam, 0);
		int err = PCO_AllocateBuffer(hCam, &sBufNr, size,&wBuf ,&hEvent);
		if (err){	
			char errorText[1000];
			PCO_GetErrorText(err, errorText, 1000);
			MessageBox::Show(String::Concat(gcnew String(errorText)," sBufNr = ",(int) sBufNr),"Box",MessageBoxButtons::OK);
		}
		//setRecordingstate, Addbuffer
		PCO_SetRecordingState(hCam, 0x0001);
		//DWORD wImage=0;
		//PCO_AddBuffer(hCam, wImage, wImage, sBufNr);
		PCO_CamLinkSetImageParameters(hCam, getImageWidth(), getImageHeight());
		PCO_SetStorageMode(hCam, 1);
		return 0;
	}
	//settings
	int SC2Driver::getRows(){
		getSettings();
		return roiy2-roiy1 + 1;
	}

	int SC2Driver::getCols(){
		getSettings();
		return roix2-roix1+1;
	}

	bool SC2Driver::isDouble(){
		WORD dbl;
		int err = PCO_GetDoubleImageMode(hCam, &dbl);
		if (dbl) return true;
		else return false;
	}
	void SC2Driver::update(){

	}
	
	void SC2Driver::getSettings(){
		WORD x1, x2, y1, y2;
		//PCO_GetROI(hCam, &roix1, &roiy1, &roix2, &roiy2);	
		PCO_GetROI(hCam, &x1, &y1, &x2, &y2);	
		roix1 = (int) x1;
		roix2 = (int) x2;
		roiy1 = (int) y1;
		roiy2 = (int) y2;
	}
}