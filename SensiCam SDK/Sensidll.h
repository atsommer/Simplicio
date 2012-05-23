//==========================================================================;
//  Copyright (C) 1998 PCO - Computer Optics GmbH.  All Rights Reserved.
//
//--------------------------------------------------------------------------;
/////////////////////////////////////////////////////////////////////////////
// sendll.h.cpp sendcpp demo application 
// by Franz Reitner, created with Visual C++ 6.0
/////////////////////////////////////////////////////////////////////////////
#ifndef SENSIDLL_H
#define SENSIDLL_H


int (__stdcall *SETINIT)(int);
int (__stdcall *SETBOARD)(int);
int (__stdcall *RUNCOC)(int);
int (__stdcall *STOPCOC)(int);
int (__stdcall *SETCOC)( int, int, int, int, int, int, int, int, char*);
int (__stdcall *GETSETTINGS)( int*, int*, int*, int*, int*, int*, int*, int*, char*);
float (__stdcall *GETBELTIME)();
float (__stdcall *GETCOCTIME)();
int (__stdcall *LOADOUTPUTLUT)(byte*);
int (__stdcall *LOADPSEUDOCOLORLUT)(byte*,byte*,byte*);
int (__stdcall *LOADCOLORLUT)(byte*,byte*,byte*);
int (__stdcall *GETSTATUS)(int*, int*, int*);
int (__stdcall *GETIMAGESTATUS)(int*);
int (__stdcall *GETIMAGESIZE)(int*, int*);
int (__stdcall *GETCCDSIZE)(int*);
int (__stdcall *LOADCOC)(word*);
int (__stdcall *READIMAGE12BIT)(int,int,int, word*);
int (__stdcall *READIMAGE8BIT)(int,int,int, byte*);
int (__stdcall *CONVERTBUFFER12TO8)(int, int,int, word*, byte*);
int (__stdcall *CONVERTBUFFER12TOCOL)(int, int,int, word*, byte*);
int (__stdcall *OPENDIALOGCAM)(HWND, int, char*);
int (__stdcall *CLOSEDIALOGCAM)(void);
int (__stdcall *STATUSDIALOGCAM)(int*,int*);
int (__stdcall *SETDIALOGCAM)( int, int, int, int, int, int, int, int, char*);
int (__stdcall *LOCKDIALOGCAM)(int);
int (__stdcall *OPENDIALOGBW)(HWND, int, char*);
int (__stdcall *STATUSDIALOGBW)(int*, int*);
int (__stdcall *SETDIALOGBW)(int, int, int);
int (__stdcall *GETDIALOGBW)(int*, int*, int*);
int (__stdcall *CLOSEDIALOGBW)(void);
int (__stdcall *OPENDIALOGCOL)(HWND, int, char*);
int (__stdcall *STATUSDIALOGCOL)(int*, int*);
int (__stdcall *SETDIALOGCOL)(int, int, int, int, int, int, int);
int (__stdcall *GETDIALOGCOL)(int*, int*, int*, int*, int*, int*, int*);
int (__stdcall *CLOSEDIALOGCOL)(void);

#endif