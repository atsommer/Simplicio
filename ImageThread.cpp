#include "stdafx.h"
//#include "CameraThread.h"
#include "form1.h"
//#include "CameraSettings.h"
//#include "sencam.h"
#include "ImageData.h"
#include "ImageThread.h"

namespace forms2{
	using namespace System;
	using namespace System::Threading;
	using namespace System::Drawing::Imaging;
	void ImageThread::init(Form1^ f){
		mainForm = f;
		processing=false;
		imageData = nullptr;
		buffers = nullptr;
		saveFile=true;
		singleFrame = f->isSingleFrame();
		addBuffersMainForm = gcnew DelegateBuffersIntImg(f,&Form1::addBuffers);
	}
	bool ImageThread::processImage(ImageData^ img, bool savefile,int binsize,int pixelsize){
		if (processing || img==nullptr) return true;
		imageData = img;
		saveFile = savefile;
		binSize=binsize;
		pixelSize=pixelsize;
		Thread^ imageThread = gcnew Thread(gcnew ThreadStart(this,&ImageThread::processNewImage));
		imageThread->Start();
		return false;
	}
	int max(int x,int y){return x>y?x:y;}
	int min(int x,int y){return x<y?x:y;}
	void ImageThread::processNewImage(){
		//creates new buffers and calculates values
		//report to Form1: buffers, numBuffers, [imageData--or write calculations to buffers]
		if (imageData==nullptr) return;
		processing = true;
		
		//allocate new buffers
		int layers = imageData->getLayers();
		bool makePreview=(layers==3 || singleFrame);
		numBuffers = layers;
		if (makePreview)
			numBuffers++;//create an extra buffer
		/*
		if (singleFrame)
			numBuffers = 2;
		*/
		buffers=mainForm->getEmptyBuffers(numBuffers);

		//get image size
		int cols = imageData->getCols();//min(img->getCols(),pictureBox->Width);
		int rows = imageData->getRows()*imageData->getDoubler();//min((img->getRows())*(img->getDoubler()),pictureBox->Height);
		
		//create bitmaps, lock bits
		Rectangle rect = Rectangle(0,0,cols,rows);
		array<Bitmap^>^ bitmaps = gcnew array<Bitmap^>(numBuffers);
		array<BitmapData^>^ bmpData = gcnew array<BitmapData^>(numBuffers);
		for(int i(0);i<numBuffers;i++){
			bitmaps[i]=gcnew Bitmap(cols,rows,PixelFormat::Format32bppArgb);
			bmpData[i] = bitmaps[i]->LockBits(rect,Imaging::ImageLockMode::ReadWrite,bitmaps[i]->PixelFormat);
		}

		//create value arrays
		int bytesPerPixel = 4;  
		int stride=bmpData[0]->Stride;//bytes per row
		int bytes = stride * rows;//bytes per layer
		array<array<Byte>^>^ bmpValues = gcnew array<array<Byte>^>(numBuffers);
		for (int i=0;i<numBuffers;i++){
			bmpValues[i] = gcnew array<Byte>(bytes);
		}
		
		//find maximum values in each layer for normalization
		array<UInt16>^ maxVals = gcnew array<UInt16>(layers);
		for (int lay=0;lay<layers;lay++)
			maxVals[lay] = max(imageData->getMaxValue(lay),1);
		
		//draw the new data onto the new buffers
		int bufLay;
		int value,x,y;
		SolidBrush^ brush = gcnew SolidBrush(Color::FromArgb(155,0,0));
		array<UInt32>^ counts = gcnew array<UInt32>(layers);//holds the pixel data from each layer
		UInt32 PWA, PWOA, DF;
		
		UInt32 paddedNumerator, denominator, ratio;
		double floatRatio=1, pixelNcount=0;
		double Ncount=0;
		for (int r(0);r<rows;r+=binSize){
			for(int c(0);c<cols;c+=binSize){	
				//for each pixel:
				//read each layer and draw
				for (int lay(0);lay<layers;lay++){
					counts[lay] = imageData->getValue(r,c,lay,0);
					ratio = (255*counts[lay])/maxVals[lay];
					value = (int)ratio;
					if (value>255){ MessageBox::Show("Color value  > 255","Box",MessageBoxButtons::OK); value=255;}
					//brush->Color = Color::FromArgb(value,value,value);
					bufLay = lay;
					//if (layers==3 || singleFrame) bufLay++;//make space for preview layer
					if (makePreview) bufLay++;//make space for preview layer
					x = pixelSize*c/binSize;
					y = pixelSize*r/binSize;
					for (int rgb=0;rgb<4;rgb++)
						bmpValues[bufLay][y*stride+bytesPerPixel*x+rgb] = (rgb==3)? 255:value;
					//bitmaps[bufLay]->SetPixel(pixelSize*c/binSize,pixelSize*r/binSize,Color::FromArgb(value,value,value));
					//buffers[bufLay]->Graphics->FillRectangle(brush,Rectangle(pixelSize*c/binSize,pixelSize*r/binSize,pixelSize,pixelSize));
				}
				
				if (singleFrame)//define preview layer for single frame kinetics imaging
				{
					PWA=counts[1];
					PWOA=counts[2];
					DF=counts[3];
				}
				else if (layers==3)
				{
					PWA=counts[0];
					PWOA=counts[1];
					DF=counts[2];
				}
				
				if (makePreview)//define preview layer for three frame imaging
				{	
					//if ((counts[0] > counts[2])&&(counts[1]>counts[2])){
					if ((PWA > DF)&&(PWOA>DF)){
						//draw transmission image	
						paddedNumerator = (PWA-DF)<<16;
						denominator = PWOA-DF;
						ratio =paddedNumerator/denominator;
						//floatRatio =(double)ratio;
						//floatRatio/= 2^16;						
						//prevent ratio from exceeding 2*padding i.e. pwa twice as bright as pwoa
						if (ratio >= (2<<16))
							ratio = (2<<16) - 1;
						ratio = ratio>>9;//bring ratio into the range [0,255]
						value = (int)ratio;
						x = pixelSize*c/binSize;
						y = pixelSize*r/binSize;
						for (int rgb=0;rgb<4;rgb++)
							bmpValues[0][y*stride+bytesPerPixel*x+rgb] =(rgb==3)? 255:value;
						//bitmaps[0]->SetPixel(pixelSize*c/binSize,pixelSize*r/binSize,Color::FromArgb(value,value,value));
						//brush->Color = Color::FromArgb(value,value,value);
						//buffers[0]->Graphics->FillRectangle(brush,Rectangle(pixelSize*c/binSize,pixelSize*r/binSize,pixelSize,pixelSize));
						//floatRatio = ((double)(counts[0]-counts[2]))/(counts[1]-counts[2]);
						floatRatio = ((double)(PWA-DF))/(PWOA-DF);
					}
					else if (PWOA>DF) //no light in PWA
						floatRatio = MIN_T;
					else if (PWA>DF) //no light in PWOA
						floatRatio = 1;
					if (floatRatio < MIN_T) 
						floatRatio = MIN_T;
					//if (floatRatio > 1) floatRatio =1;
					//add to Ncount
					Ncount += -Math::Log(floatRatio) * binSize * binSize;		
				}//end of layers==3
			}//end for loop on c
		}//end for loop on r

		//copy bits into bitmaps
		//unlock bits
		//draw bitmaps to buffers
		for (int i=0;i<numBuffers;i++){
			System::Runtime::InteropServices::Marshal::Copy( bmpValues[i], 0, bmpData[i]->Scan0, bytes );
			bitmaps[i]->UnlockBits(bmpData[i]);
			buffers[i]->Graphics->DrawImage(bitmaps[i],0,0);
		}

		//draw time, max value, and list-driven variables on each image:
		System::Drawing::Font^ font = gcnew System::Drawing::Font("Arial",12);
		LinkedList<String^>^ strList = gcnew LinkedList<String^>();//holds the strings to draw
		//define white box behind text
		int bw(200),bh(20);
		x = pixelSize*cols/binSize-bw;
		y = pixelSize*rows/binSize;
		//loop over buffers and draw text
		brush->Color = Color::White;
		for (int bufLay(0); bufLay<numBuffers;bufLay++){
			if (!makePreview || bufLay!=0)//not a transmission image 
			{
				int lay = bufLay;//image data layer for max value
				if (makePreview) lay--;
				strList->AddLast(String::Format("Maximum Value: {0}",maxVals[lay]));
			}else 
			{//transmission image
				strList->AddLast(String::Format("Ncount: {0}",(int)Ncount));
				for each(Variable^ var in imageData->getSeqVars())
					strList->AddLast(String::Format("{0} = {1}", var->VariableName, var->VariableValue));
			}
			strList->AddFirst(imageData->getDateTimeString());
			buffers[bufLay]->Graphics->FillRectangle(brush,Rectangle(x,y,bw,bh*strList->Count));
			int strInd(0);
			for each(String^ str in strList){
				buffers[bufLay]->Graphics->DrawString(str,font,Brushes::Black, Point(x+15,y+bh*strInd) );
				strInd++;
			}
			strList->Clear();
		}
		
		//save to file
		//if (saveFile)
		//	imageData->saveFile();
		//send buffers to main window
		//if(callBack)
		
		array<Object^>^ parameters = gcnew array<Object^>(3);
		parameters[0] = buffers;
		parameters[1] = numBuffers;
		parameters[2] = imageData;
		mainForm->BeginInvoke(addBuffersMainForm, parameters);
		processing=false;
	}

}