#ifndef SENCAM_H
#define SENCAM_H

typedef unsigned char  byte;     /* 8-bit  */
typedef unsigned short word;    /* 16-bit */
typedef unsigned long  dword;    /* 32-bit */


#if !defined IDC_UPDATE
 #define IDC_UPDATE    1000
#endif

#if !defined IDC_UPDATEBW
 #define IDC_UPDATEBW  1001
#endif

#if !defined IDC_UPDATECOL
 #define IDC_UPDATECOL 1002
#endif



#ifdef __cplusplus
extern "C" {            //  Assume C declarations for C++
#endif  //C++

//camop functions Sensicam
//Win95/98 sen95cam.dll Version 3.21 
//WinNT4.0/Win2000 senntcam.dll Version 1.11 

int  SET_BOARD(int boardnr);
//set the current board to work with
//after selecting a board the first time, call SET_INIT(1..2) to initialize it
//boardnr: 0..9 selects PCI-Board set

int  GET_BOARD(int *boardnr);
//get the current board to work with


int  SET_INIT(int mode);
//resets or initialize the PCI-Board, the camera and all global values of the dll
//mode=0 : reset
//         frees memory
//         close dialog boxes
//         SET_INIT(0) should be called before you close your program

//mode=1 : init default
//mode=2 : init with values of registry (HKEY_CURRENT_USER\\software\\PCO\\Camera Settings

int  GET_STATUS(int *camtype, int *eletemp, int *ccdtemp);
//reads out the connected camera LONG or FAST
//and the electronic and CCD temperature in 캜
//version>3.21
//if camera with analog gain switch (*camtyp>>16)&0x0F == 0x01  


int  GET_IMAGE_SIZE(int *width, int *height);
//reads out the actual size of the picture, which is send from the camera

int  GET_IMAGE_STATUS(int *status);
//reads out the status of the PCI-Buffer process
// *status Bit0 = 0 : no read image process is running
//                1 : read image process is running
//         Bit1 = 0 : 1 or 2 pictures are in PCI-Buffer
//                1 : no picture is in PCI-BUFFER
//         Bit2 = 0 : camera is idle, no exposure is running
//                1 : camera is busy, exposure is running or a picture
//                    is send from the camera to the PCI-Buffer

int  SET_COC( int mode,    int trig,
                    int roixmin, int roixmax,
                    int roiymin, int roiymax,
                    int hbin,    int vbin,
                    char *timevalues);
// build an COC and load it into the camera
// mode = (typ&0xFFFF)+subtyp<<16
//version>3.21 and valid camera connected
// mode = (typ&0xFFFFFF)+subtyp<<16+gain<<8

// typ=0    : set LONG EXPOSURE camera (if camtyp=FAST return error WRONGVAL)
// subtyp=0 : sequential mode, busy out
// subtyp=1 : simultaneous mode, busy out
// subtyp=2 : sequential mode, busy out, exposure out
// subtyp=3 : simultaneous mode, exposure out

// typ=1    : set FAST SHUTTER camera  (if camtyp=LONG return error WRONGVAL)
// subtyp=0 : standard fast
// subtyp=1 : double fast, only for doubleshutter cameras, else returns WRONGVAL
// subtyp=2 : double long, only for doubleshutter cameras, else returns WRONGVAL
// subtyp=5 : fast shutter cycle mode

// gain=0   : normal analog gain
// gain=1   : extended analog gain

// trig=0 : continuos software triggering
// trig=1 : external trigger raising edge
// trig=2 : external trigger falling edge

// roi... : values for area of interest, 32x32pixel quadrants
//    x   : range 1 to 40 (20)
//    y   : range 1 to 32 (15)

// hbin   : horizontal binning (1,2,4,8)
// vbin   : vertical binning (1,2,4,8,16,32)

// timevalues : Null terminated ASCII string
//              delay0,exposure0,delay0,exposur1 ... -1,-1
//              The pair -1,-1 must be last of the table
//              The LONG camera expects only one pair of timevalues
//              DOUBLE and DOUBLE LONG have no timevalues
//              FAST can have up to 100 pairs of timevalues
//              see SDK-manual for exact description
// changing the values of roi..., hbin and vbin changes also the size
// of the picture, which is send from the camera

int  GET_SETTINGS(int *mode,int *trig,
                        int *roixmin, int *roixmax,
                        int *roiymin, int *roiymax,
                        int *hbin, int *vbin,
                        char *(*tab));
// get values, which are in use now
// !!! The pointer to the string table is mistakenly defined as char**.
// The actual behaviour is as it was defined as char*.
// In order to keep compatible to older versions of the SDK this mistake
// is not corrected.
// Use new function GET_COC_SETTING


int  LOAD_USER_COC(word *codetable);
// load or own COC = codetable into the camera (see LAYER2 commands description)
// none of the SET_COC parameters is in use,
// GET_IMAGE_SIZE reads out wrong values

int  RUN_COC(int mode);
// starts camera grabing pictures
// mode=0 continuos runninng
// mode=4 start single exposure
//        don't use other values

int  STOP_COC(int mode);
// stops camera grabing pictures
// mode=0 stops, make PCI-BUFFER empty
//        and wait for CCD-Chip get cleared if camera is running
//        don't use other values

int  LOAD_OUTPUT_LUT(byte *lut);
// loads the convert LUT for black&white pictures
// converting is actual done only by software
// in the new PCI-BUFFER Board also by hardware
// lut : table with 4096 8-Bit values

int  CONVERT_BUFFER_12TO8(int mode, int width,int height,
                                word *b12, byte *b8);
// converts an 12Bit image to an 8Bit image using LUT
// mode=0 : normal converting TOP 12Bit = TOP 8Bit
// mode=Bit0 set: flips image  TOP 12Bit = BOTTOM 8Bit  (BMP-Format)
// mode=Bit3 set: mirror image  first row 12Bit = last row 8Bit  (BMP-Format)
//          don't use other values
// width  : number of pixel in each line in the image
// height : number of lines in the image
// b12    : pointer to PC memory area, from which to read the 12BIT image
// b8     : pointer to PC memory area, to write the 8Bit image in

int  READ_IMAGE_8BIT(int mode,int width,int height, byte *b8);
// transfers and converts one picture from PCI-Buffer to PC memory area
// mode=0 : normal transfer and converting TOP camera = TOP 8Bit
// mode=Bit0 set: flips image  TOP camera = BOTTOM 8Bit  (BMP-Format)
// mode=Bit3 set: mirror image  first row 12Bit = last row 8Bit  (BMP-Format)
//          don't use other values
// width  : number of pixel in each line in the image
// height : number of lines in the image
// b8     : pointer to PC memory area, to write the 8Bit image in

int  READ_IMAGE_12BIT(int mode,int width,int height, word *b12);
// transfers and converts one picture from PCI-Buffer to PC memory area
// mode=0 : normal transferand converting TOP camera = TOP 12Bit
// mode=Bit0 set: flips image  TOP camera = BOTTOM 12Bit  
// mode=Bit3 set: mirror image  first row camera = last row 12Bit
//          don't use other values
// width  : number of pixel in each line in the image
// height : number of lines in the image
// b12    : pointer to PC memory area, to write the 12Bit image in

int  READ_IMAGE_12BIT_EXT(int mode,int width,int height,int x, word *b12);
// transfers and converts one picture from PCI-Buffer to PC memory area
// mode=0 : normal transferand converting TOP camera = TOP 12Bit
// mode=Bit0 set: flips image  TOP camera = BOTTOM 12Bit  
// mode=Bit3 set: mirror image  first row camera = last row 12Bit
//          don't use other values
// width  : number of pixel in each line in the image
// height : number of lines in the image
// x      : image number within the PC memory area, start with 0!
// b12    : pointer to begin of PC memory area, to write the 12Bit image in


// Color camera functions
int  LOAD_COLOR_LUT(byte *redlut,byte *greenlut,byte *bluelut);
// loads the convert COLOR LUT's for color pictures
// converting is always done by software
// redlut : table with 4096 8-Bit values for red color
// greenlut : table with 4096 8-Bit values for green color
// bluelut : table with 4096 8-Bit values for blue color

int  LOAD_PSEUDO_COLOR_LUT(byte *redlut,byte *greenlut,byte *bluelut);
// loads the convert PSEUDO-COLOR LUT's for bw pictures
// converting is always done by software
// redlut : table with 256 8-Bit values for red color
// greenlut : table with 256 8-Bit values for green color
// bluelut : table with 256 8-Bit values for blue color

int  CONVERT_BUFFER_12TOCOL(int mode, int width, int height,
                               word *b12, byte *gb8);
// converts an 12Bit color image to an 32Bit (24Bit) image using COLOR LUT's
// mode=0       : converting 12Bit to 24Bit
// mode=Bit0 set: flips image  TOP 12Bit = BOTTOM 32/24Bit  (BMP-Format)
// mode=Bit1 set: converting 12Bit to 32Bit
// mode=Bit3 set: mirror image  first row 12Bit = last row 32/24Bit
// mode=Bit4 set: convert via pseudo LUT's
// mode=Bit5 set: low average convert
//          don't use other values
// width  : number of pixel in each line in the image
// height : number of lines in the image
// b12    : pointer to PC memory area, from which to read the 12BIT image
// b8     : pointer to PC memory area, to write the 8Bit image in

int  READ_IMAGE_COL(int mode,int width,int height, byte *b8);
// transfers and converts one picture from PCI-Buffer to PC memory area
// mode=0       : converting 12Bit to 24Bit
// mode=Bit0 set: flips image  TOP 12Bit = BOTTOM 32/24Bit  (BMP-Format)
// mode=Bit1 set: converting 12Bit to 32Bit
// mode=Bit3 set: mirror image  first row 12Bit = last row 32/24Bit
// mode=Bit4 set: convert via pseudo LUT's
// mode=Bit5 set: low average convert
//          don't use other values
// width  : number of pixel in each line in the image
// height : number of lines in the image
// b8     : pointer to PC memory area, to write the 8Bit image in



// Dialog functions:
// every Dialog store his exit values in the registry and load's it when starting
int  OPEN_DIALOG_CAM(HWND hWnd, int mode, char *title);
// create an thread, which controls an dialog box, where you can input
// all values for SET_COC. If one value is changed SET_COC is send.
// hWnd   : your main window handle
// mode=0 : dialogbox, no message is send to hWnd
// mode=1 : dialogbox, message is send to hWnd
//long exposure Sensicam
// mode=2 : short dialogbox, only time values, no message 
// mode=3 : short dialogbox, only time values, message 
// mode=4 : great dialogbox, does not return before 'ok', no message 
// mode=5 : great dialogbox, does not return before 'ok', message 
//          message=(PostMessage(hwnd,WM_COMMAND,updmsg,0);
//          (updmsg is IDC_UPDATE or read out from the registry)
// title  : Null terminated ASCII string
//          title of the window
//          if NULL default title is used

int  LOCK_DIALOG_CAM(int mode);
// inhibits user input to dialogbox
// mode=0 : user can change values
// mode=1 : user cannot change values

int  CLOSE_DIALOG_CAM(void);
// closes the dialog box

int  SET_DIALOG_CAM(int mode, int trig,
                        int roixmin, int roixmax,
                        int roiymin, int roiymax,
                        int hbin, int vbin,
                        char *timevalues);
// set values in the dialogbox

int  GET_DIALOG_CAM(int *mode,int *trig,
                          int *roixmin, int *roixmax,
                          int *roiymin, int *roiymax,
                          int *hbin, int *vbin,
                          char *(*tab));
// get values from the dialogbox

int  STATUS_DIALOG_CAM(int *hwnd,int *status);
// hwnd   : window handle of Dialogbox
//          NULL if Dialogbox is closed
// status : 0 no user input, since last call
//          1 any user input, since last call

int  OPEN_DIALOG_BW(HWND hwnd, int mode, char *title);
// create an thread, which controls an dialog box, where you can input
// the black&white LUT. If one value is changed LOAD_OUTPUT_LUT is send.
// hWnd   : your main window handle
// mode=0 : no message is send to hWnd
// mode=1 : message is send to hWnd
//          (PostMessage(hwnd,WM_COMMAND,updmsg,0);
//          (updmsg is IDC_UPDATEBW or read out from the registry)
// title  : Null terminated ASCII string
//          title of the window
//          if NULL default title is used

int  LOCK_DIALOG_BW(int mode);
// inhibits user input to dialogbox
// mode=0 : user can change values
// mode=1 : user cannot change values

int  SET_DIALOG_BW(int bwmin, int bwmax, int bwlinlog);
// create an new lut with the values
// bwmin : 0..4094 lower offset all below will cxovert to black
// bwmax : 1..4095 upper offset all above will convert to white
// bwlinlo=0 : linear curve between bwmin and bwmax
//        =1 : logarithmic curve between bwmin and bwmax

int  STATUS_DIALOG_BW(int *hwnd,int *status);
// hwnd   : window handle of Dialogbox
//          NULL if Dialogbox is closed
// status : 0 no user input, since last call
//          1 any user input, since last call

int  GET_DIALOG_BW(int *lutmin,int *lutmax,int *lutlinlog);

int  CLOSE_DIALOG_BW(void);
// closes the dialog box

// the same as BW-Dialog only for COLOR-LUT
int  OPEN_DIALOG_COL(HWND hwnd, int mode, char *title);
int  LOCK_DIALOG_COL(int mode);
int  SET_DIALOG_COL(int redmin, int redmax,
                          int greenmin, int greenmax,
                          int bluemin, int bluemax,
                          int linlog);
int  GET_DIALOG_COL(int *redmin, int *redmax,
                          int *greenmin, int *greenmax,
                          int *bluemin, int *bluemax,
                          int *linlog);
int  STATUS_DIALOG_COL(int *hwnd,int *status);
int  CLOSE_DIALOG_COL(void);



//*****************************************************************
// the following functions are for the MULTI-BUFFER Option
//

int  GET_CCDSIZE(int *ccdsize);
int  GET_CCD_SIZE(int *ccdsize);
// returns ccdsize in pixel of connected camera

int  ALLOC_RECORDER(int *bufanz, int ccdsize);
// allocates *bufanz buffer's with Pixelsize ccdsize
// if *bufanz=0 allocates as much as possible
// returns count of buffers in *bufanz

int  FREE_RECORDER(void);
// free allocated buffers

int  GET_RECORDER_ADDR(int buf, int *linadr);
// get address of allocated buffer
// buf: number of buffer
// *linadr 32bit address

int  SET_BUFFER_SIZE(int *numbers, int width,int height);
// creates an queue of buffer adresses for buffers with size width*height
// *numbers: count of buffers
//           returns possible buffers
// width:    width  of  pictures in Pixels
// height:   height of  pictures in Pixels

int  GET_BUFFER_ADDR(int picnr,int *linadr,int *picwidth,int *picheight);
// gets linadr and width,height of picture Nr picnr

int  GET_DMA_STATUS(int *count);
// returns buffer, in which the dma transfers now

int  RUN_DMA(int pics,int pice, int mode);
//starts dma
//pics:   number of buffer to start
//pice:   number of buffer to end
//mode:  0=writing from start to end and return from routine
//       1=wraping continuous
//       in both modes the windows message queue is called, while
//       waiting for pictures come in and waiting for DMA is done
//       call DMA_STOP() to return from function

int  STOP_DMA(void);
//stops dma at the next possible time, an running DMA is completed

int  DMA_START_SINGLE(int pics);
//starts one single dma, call DMA_DONE to see if done

int  DMA_DONE(int *pic);
//pic : 0 dma done
//      else buffernr called in Dma_Start_Single

int  RUN_DMA_AVG(int pics, int pice, int mode,int avgmode);
//start averanging
//pics:  number of buffer to start
//pice:  number of buffer to end
//mode:  0=writing from start to end and return from routine
//       1=wraping continuous
//avgmode: count of pictures to average
//       in both modes the windows message queue is called, while
//       waiting for pictures come in and waiting for DMA is done
//       call DMA_STOP() to return from function


void  GET_PALETTE(HPALETTE *ghpal);
//returns the Palette used for dialogs

int   AUTO_MINMAX(int mode, int *min, int *max, int width,int height,word *frame);
//calculate min and max values in the picture in frame
//mode   : 0 return
//         1 set actual LUT and return
//*min	 : minimal value in picture
//*max	 : maximal value in picture
//width  : number of pixel in each line in the image
//height : number of lines in the image
//frame  : pointer to begin of PC memory area to calculate or
//         NULL, allocate a buffer,read in a single picture and calculate

int   AUTO_MINMAX_OFF(int mode, int *min, int *max,int lowoff, int hioff, int width,int height,word *frame);
//calculate min and max values excluding all pixel
//below lowoff percent and above hioff percent
//mode   : 0 return
//         1 set actual LUT and return
//*min	 : minimal value in picture
//*max	 : maximal value in picture
//width  : number of pixel in each line in the image
//height : number of lines in the image
//frame  : pointer to begin of PC memory area to calculate or
//         NULL, allocate a buffer,read in a single picture and calculate

int  AUTO_COLOR(int width,int height,word *frame);
//set the actual BW-LUT so, that it is between lowoff percent
//and hioff percent of values in the picture in frame
//if frame==NULL, allocate a buffer and read in a single picture

int  AUTO_RANGE(int mode, int *time, int off,int width,int height,word *frame);
//try to get nearest possible exposure time between 1-2000ms
//loop readimage, calculate until time is found or error occured
//return : 0   = ok
//         101 = picture to dark
//         102 = picture to bright
//mode   : 0 return without changing actual settings
//         1 call SET_COC, if no error and return
//*time	 : found exposure time
//off	 : range to fit in, in percent below 100%
//width  : number of pixel in each line in the image
//height : number of lines in the image
//frame  : pointer to begin of PC memory area to read picture in
//         NULL, allocate a buffer for pictures
//

int  READ_REGISTRY_VALUES(void);
// reads values from registry to current data set
int  WRITE_REGISTRY_VALUES(void);
// write values from current data set to registry


float  GET_COCTIME(void);
//returns readout time in 탎
float  GET_BELTIME(void);
//returns exposure+delay time in 탎
float  GET_EXPTIME(void);
//returns exposure time in 탎
float  GET_DELTIME(void);
//returns delay time in 탎

//version > 3.18(win95) or 3.08(winnt)
void SET_TIMEOUT(int timeout1,int timeout2);
void GET_TIMEOUT(int *timeout1,int *timeout2);
//@ver3.21
void  SETTIMEOUT(int timeout1,int timeout2);
void  GETTIMEOUT(int *timeout1,int *timeout2);
//Set or get the actual timeoutvalues
//timeout1 is the timeout in ms for all PCI-board interaction
//timeout2 is the syncronisation-timeout in ms between the
//SDK-function, which need PCI-board interaction

void ENABLE_ERROR_MESSAGES(BOOL m);
//enables (m=TRUE) or disables (m=FALSE)
//errormessages of the driver


//version > 3.19(win95) or 3.09(winnt)
int TEST_COC(int *mode, int *trig,
             int *roixmin, int *roixmax,
             int *roiymin, int *roiymax,
             int *hbin, int *vbin,
             char *tab,int *tablength);
//@ver3.21
int  TESTCOC(int *mode, int *trig,
             int *roixmin, int *roixmax,
             int *roiymin, int *roiymax,
             int *hbin, int *vbin,
             char *tab,int *tablength);
//test values and change it if wrong ones are given
//values like in SET_COC 
//return  : 0   = all ok
//          103 = one or more values changed
//          104 = buffer for builded string too short
//
//*tablength  in length of allocated buffer for tab (not strlen(tab));
//            out strlen needed for new build string
//

//version > 3.20(win95) or 3.10(winnt)
int  SET_POWERDOWN(int pdtime, int pdwakeup);
// time values are in ms
// pdtime is the time after which pd is invoked in the COC
// pdwakeup is the time the chip needs to come back from powerdown


//version > 3.21(win95) or 3.11(winnt)
int  DMA_IMAGE_START(int board,int width, int height,unsigned short *frame,HANDLE picevent);
//this function is only avaiable for WINDOWS NT
//WIN95/98 returns with error -13
//start a DMA transfer of one image from board buffer to
//PC memory location 'frame'. If transfer is done
//the event picevent is set.
//board    : number of board  
//width    : number of pixel in each line in the image
//height   : number of lines in the image
//frame    : pointer to begin of PC memory area 
//picevent : HANDLE of event (created with CreateEvent(...) or similar) 

int  CLEAR_BOARD_BUFFER(int board);
//clears one picture from board buffer in specified board
//board    : number of board  

int  ENABLE_MESSAGE_LOG(int m,char *name);
//if m>0 open file 'name' and write error messages to it 
//if m==0 close file

//version > 3.22(win95) or 3.12(winnt)
int  LOAD_USER_AOI(int aoixmin,int aoixmax);
//set the horizontal AOI, must be called after SET_USER_COC()
//must not be called after a call to SET_COC()
//aoixmin   : start of horizontal AOI 
//aoixmax   : end of horizontal AOI 
//aoixmax must be greater than aoixmin
//maximum value is ccdxsize, the five low order Bits are masked so
//minimum step size is 32

int  SET_DICAM_WAIT(int time);
//Set waiting time for DICAM. The camera must wait a specific
//time until HV-Modul and Pulser are ready for the next exposure.
//Waiting is done in the SDK, with this function one can set the time
//to wait in ms. The value cannot be smaller than 200. 


int  GET_CAMERA_ID(int board,int *id);
//Get the Camera-ID of selected board, if camera supports this   
//in:
//board    : number of board  0..9
//           -1 = get board selected with last SET_BOARD call
//out
//*id      : camera-id (0...3)

int  GET_CAMERA_CCD(int board,int *ccdtyp);
//Get the Camera-CCD-typ of selected board  
//in:
//board    : number of board  0..9
//           -1 = get board selected with last SET_BOARD call
//out
//*ccdtyp  : camera-CCD-typ (CCD74,CCD85,...)


int  GET_CAMERA_TYP(int board,int *camtyp);
//Get the Camera-typ of selected board  
//in:
//board    : number of board  0..9
//           -1 = get board selected with last SET_BOARD call
//out
//*camtyp  : camera-typ (FAST,LONG,DICAM,...)


int  GET_CAMERA_STAT(int board,int select,int *stat);
//Get the status of selected board  
//in:
//board    : number of board  0..9
//           -1 = get board selected with last SET_BOARD call
//select   : 1 = typ_info
//         : 2 = ccdtemp 
//         : 3 = eletemp 
//         : 4 = channel status info (special systems only)
//         : 5 = system status info  (special systems only)
//         : 6 = board typ 
//         : 7 = board revision
  
//out
//*stat    : selected status information

int  SET_CAMERA_VAL(int board,int select,int val);
//Set port of selected board to value   
//in:
//board    : number of board  0..9
//           -1 = get board selected with last SET_BOARD call
//select   : 1 = register 1  
//           2 = register 2  

int  BEGIN_WAIT_IMAGE(int boardnr,HANDLE event);
//this function is only avaiable for WINDOWS NT
//WIN95/98 returns with error -13
//enables board function to create events, when
//a picture is avaiable in the board buffer 
//the function returns immediately,
//the event is set, when a picture is in one of the board 
//buffer

//in:
//board    : number of board  0..9
//picevent : HANDLE of event (created with CreateEvent(...) or similar) 
//out

int  END_WAIT_IMAGE(int boardnr);
//this function is only avaiable for WINDOWS NT
//WIN95/98 returns with error -13
//disables board function to create events, when


int  GET_COC_SETTING(int *mode, int *trig,
                           int *roixmin, int *roixmax,
                           int *roiymin, int *roiymax,
                           int *hbin, int *vbin,
                           char *tab,int len);
// get values, which are in use now
// corrected version of GET_SETTINGS
//in:
//len    : size of tab (number of bytes allocated)


int  CHECK_BOARD_MEMORY(int board, int len);
//this function is only avaiable for PCI525 boards
//if called on PCI520 board return with error NOFUNCTION (-13)
//memory test for on board buffers
//write status in logfile, if logging is enabled (INFO_M,ERROR_M)   

//in:
//board    : number of board  0..9
//           -1 = get board selected with last SET_BOARD call
//len      : count of memory words to check
//           maximal value is 4*1024*1024 (8Mbyte) 
//out
//         


#ifdef __cplusplus
}            // Assume C declarations for C++
#endif  //C++

#endif //SENCAM_H 