#ifndef __VESA_H
#define __VESA_h
//#include <iostream.h>
#include <dos.h>
#include <alloc.h>


#define SVGA800x600x256 0x103
#define SVGA640x480x256 0x101
#define SVGA320x240x24  0x10F

unsigned char *video_buffer = (char *)0xA0000000;
unsigned char *double_buffer = (char *)farmalloc(2048*480*3);


// Globals are faster
int z,multi;
short xres3;
int current_bank,bankswitch;

// Vesa mode information struct
struct VBEModeInfo {
  short   ModeAttributes;         /* Mode attributes                  */
  char    WinAAttributes;         /* Window A attributes              */
  char    WinBAttributes;         /* Window B attributes              */
  short   WinGranularity;         /* Window granularity in k          */
  short   WinSize;                /* Window size in k                 */
  short   WinASegment;            /* Window A segment                 */
  short   WinBSegment;            /* Window B segment                 */
  void    *WinFuncPtr;            /* Pointer to window function       */
  short   BytesPerScanLine;       /* Bytes per scanline               */
  short   XResolution;            /* Horizontal resolution            */
  short   YResolution;            /* Vertical resolution              */
  char    XCharSize;              /* Character cell width             */
  char    YCharSize;              /* Character cell height            */
  char    NumberOfPlanes;         /* Number of memory planes          */
  char    BitsPerPixel;           /* Bits per pixel                   */
  char    NumberOfBanks;          /* Number of CGA style banks        */
  char    MemoryModel;            /* Memory model type                */
  char    BankSize;               /* Size of CGA style banks          */
  char    NumberOfImagePages;     /* Number of images pages           */
  char    res1;                   /* Reserved                         */
  char    RedMaskSize;            /* Size of direct color red mask    */
  char    RedFieldPosition;       /* Bit posn of lsb of red mask      */
  char    GreenMaskSize;          /* Size of direct color green mask  */
  char    GreenFieldPosition;     /* Bit posn of lsb of green mask    */
  char    BlueMaskSize;           /* Size of direct color blue mask   */
  char    BlueFieldPosition;      /* Bit posn of lsb of blue mask     */
  char    RsvdMaskSize;           /* Size of direct color res mask    */
  char    RsvdFieldPosition;      /* Bit posn of lsb of res mask      */
  char    DirectColorModeInfo;    /* Direct color mode attributes     */


  /* VESA 2.0 variables */
  /* flat frame buffer not supported on most vid cards */
  unsigned long    PhysBasePtr;         /* physical address for flat frame buffer */
  unsigned long    OffScreenMemOffset;  /* pointer to start of off screen memory */
  short   OffScreenMemSize;             /* amount of off screen memory in 1k units */
  char    res2[206];                    /* Pad to 256 byte block size       */
} modeinfo;

void getinfo(int mode)
{
int off,segment;
off = FP_OFF(&modeinfo);
segment = FP_SEG(&modeinfo);

   asm {
       mov ax,0x4F01
       mov cx,mode
       mov dx,segment
       mov es,dx
       mov bx,off
       mov di,bx
       int 0x10
       }
       xres3=modeinfo.XResolution*3;
}


int set_bank(int bank)
{
int axreturn;
//char alreturn,ahreturn;
bank = bank << multi;
if(current_bank == bank) return 0;
   _asm {
	mov ax,0x4f05
	mov bh,0x00
	mov bl,0x00
	mov dx,bank
	int 0x10
	mov axreturn,ax
	}

   if(axreturn==0x4f) current_bank = bank;

   return axreturn;
}

void set_bank24(int bank)
{

if(current_bank == bank) return;
   _asm {
	mov ax,0x4f05
	mov bh,0x00
	mov bl,0x00
	mov dx,bank
	int 0x10

	}

current_bank = bank;
}

void setmode(unsigned char mode)
{
   asm {
      mov AH,0          //clear ah
      mov AL,mode       //put vid mode into al
      int 0x10           //call the set video mode intterupt

    }

}

int SetVesaMode(int mode)
{
    getinfo(mode);
    int axreturn;
    asm {
	mov ax,0x4f02
	mov bx,mode
	int 0x10
	mov axreturn,ax
	}

    switch(modeinfo.WinGranularity){
	  case 1: multi = 6; break;
	  case 2: multi = 5; break;
	  case 4: multi = 4; break;
	  case 8: multi = 3;  break;
	  case 16: multi = 2; break;
	  case 32: multi = 1; break;
	  case 64: multi = 0; break;
	  default: multi = 0; break;
	  }

    switch(modeinfo.BytesPerScanLine){
	  case 1024: bankswitch = 10; break;
	  case 2048: bankswitch = 11; break;
	  }
    return axreturn; // 0 if successful otherwise fail
}

void putpixel24d(unsigned long x,unsigned long y,char r, char g, char b)
{
    y*=(xres3);
    x*=3;
    x+=y;
    double_buffer[x++]=b;
    double_buffer[x++]=g;
    double_buffer[x]=r;
}

void commitbuf()
{
  long yxres3,dbloff,vidoff;
  int x,y,bank=0;
  set_bank24(bank);
  for (y=0; y<modeinfo.YResolution;y++)
  {

    yxres3=y*xres3;

    for(x=0; x<xres3; x++)
    {
     dbloff=(x*3)+yxres3;
     vidoff=(y<<bankswitch)+(x*3);

     video_buffer[vidoff++]=double_buffer[dbloff++];
     video_buffer[vidoff++]=double_buffer[dbloff++];
     video_buffer[vidoff]=double_buffer[dbloff];
    }
    if (y%32 == 0)
	set_bank24(++bank);
  }
}


void putpixel24(unsigned long x,unsigned long y,char r, char g, char b)
{
    y=y<<bankswitch;

    x*=3;

    x+=y;
    set_bank24(x>>16);
    video_buffer[x++]=b;
    video_buffer[x++]=g;
    video_buffer[x]=r;

}


void putpixel(int x, int y, char color)
{
    // I know multiplication is slow, didnt want to take time
    // to figure out the faster way

    long offset = (unsigned long)y*modeinfo.XResolution+(unsigned long)x;


    set_bank(offset>>16);

    video_buffer[offset] = color;

}

#endif
