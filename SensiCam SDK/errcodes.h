/*=============================================================

	ERRCODES.H

	Header file with errorcodes for SENCAM DLL
	Author MB

	Compiler: MS VISUAL C++ 6.0
==================================================================*/
#ifndef ERRCODES_H
#define ERRCODES_H

#define NOERR        0

#define NOTINIT      -1    // Initialization failed; no camera connected
#define TIMEOUT      -2	   // Timeout in any function
#define WRONGVAL     -3    // Function-call with wrong parameter
#define NOPCIDEV     -4	   // Cannot locate PCI card
#define WRONGOS      -5
#define NODRIVER     -6
#define IOFAILURE    -7 

#define INVMODE      -9    // Invalid Camera mode
#define NOPCIBIOS    -10   // no PCI Bios found

#define DEVICEBUSY   -11    // device is hold by an other process
#define DATAERROR    -12    // Error in reading or writing data to board
#define NOFUNCTION   -13    //
#define NODMABUF     -14    // cannot allocate DMA buffer
#define NORBT        -15    // Online.rbt File not found or load error
#define POLLERR      -16    // DMA Timeout
#define EVENTERR     -17    // creating Event failed


//-13 ... -20 reserved

#define CAMERABUSY   -20   // LOAD_COC error (Camera runs Program-Memory)
#define OUTRAM       -21   // to many values in COC
#define WRONGTEMP    -22   // Camera Temperatur is out of Normal-Range wrong WINDOWS-Version
#define NOMEM        -23   // Buffer de/allocate error
#define READOUTRUN   -24   // Readout is running
#define NOBUFFLAG    -25   // Set/reset Buffer Flags failed
#define BUFINUSE     -26   // buffer is used  
#define SYSERR       -27   // a call to a windows-function fails
#define DMARUN       -28   // try to disturb dma running
#define NOFILE       -29   // cannot open file
#define REGERR       -30   // error in reading/writing to registry
#define NODIALOG     -31   // no open dialog
#define WRONGVERS    -32   // need newer called vxd or dll 
#define WRONGEXTSTAT -33   // one of extended status bits shows an error 
#define BOARDMEMERR  -34   // board memory has an error 
#define WRONGCCD     -35   // function not allowed with this ccdtyp 
#define DMAERROR     -36   // error in DMA from board to memory  
#define FILE_READ_ERR     -37   // error while reading from file 
#define FILE_WRITE_ERR    -38   // error while writing to file 
//-40...-50 reserved for DIPRO

//Warnings
#define NOPIC        100   // picture-buffer empty
#define UNDERPIC     101   // picture to dark 
#define OVERPIC      102   // picture to bright 
#define VALCHANGE    103   // values changed in TEST_COC
#define STR_SHORT    104   // tab buffer to short in TEST_COC

#define TESTSOFT     120   // Lattice Testsoftware is loaded

#endif