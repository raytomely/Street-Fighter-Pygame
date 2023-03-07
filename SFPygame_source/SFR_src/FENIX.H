#include <sys/farptr.h>
#include <go32.h>
//#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
//#include <unistd.h>
#include <math.h>
#include <io.h>
#include <time.h>
#include <allegro.h>
//#include <bios.h>
#include <dos.h>
//#include "vesa.h"

//These 2 addresses are used when referencing/using the vsync.
#define VGA_INPUT_STATUS_1  0x3DA
#define VGA_VSYNC_MASK  0x08

//These define the somewhat confusing hexidecimal numbers for video modes to neat words.
#define VGA             0x013 //320 x 200
#define TEXT            0x03 //Standard text mode

//These are palette registers necessary for setting colors to memory
#define PALETTE_MASK        0x3c6
#define PALETTE_WR          0x3c8
#define PALETTE_DATA        0x3c9


#define REPEAT 0xC0

// for keyboard
#define MAKE_1                2
#define MAKE_2                3
#define MAKE_3                4
#define MAKE_4                5
#define MAKE_5                6
#define MAKE_6                7
#define MAKE_7                8
#define MAKE_8                9
#define MAKE_9                10
#define MAKE_0                11
#define MAKE_MINUS            12
#define MAKE_EQUALS           13
#define MAKE_BKSP             14
#define MAKE_Q                16
#define MAKE_W                17
#define MAKE_E                18
#define MAKE_R                19
#define MAKE_T                20
#define MAKE_Y                21
#define MAKE_U                22
#define MAKE_I                23
#define MAKE_O                24
#define MAKE_P                25
#define MAKE_LFT_BRACKET      26
#define MAKE_RGT_BRACKET      27
#define MAKE_A                30
#define MAKE_S                31
#define MAKE_D                32
#define MAKE_F                33
#define MAKE_G                34
#define MAKE_H                35
#define MAKE_J                36
#define MAKE_K                37
#define MAKE_L                38
#define MAKE_SEMI             39
#define MAKE_APOS             40
#define MAKE_TILDE            41
#define MAKE_LEFT_SHIFT       42
#define MAKE_BACK_SLASH       43
#define MAKE_Z                44
#define MAKE_X                45
#define MAKE_C                46
#define MAKE_V                47
#define MAKE_B                48
#define MAKE_N                49
#define MAKE_M                50
#define MAKE_COMMA            51
#define MAKE_PERIOD           52
#define MAKE_FOWARD_SLASH     53
#define MAKE_RIGHT_SHIFT      54
#define MAKE_PRT_SCRN         55
#define MAKE_CAPS_LOCK        58
#define MAKE_F1               59
#define MAKE_F2               60
#define MAKE_F3               61
#define MAKE_F4               62
#define MAKE_F5               63
#define MAKE_F6               64
#define MAKE_F7               65
#define MAKE_F8               66
#define MAKE_F9               67
#define MAKE_F10              68
#define MAKE_F11              87
#define MAKE_F12              88
#define MAKE_NUM_LOCK         69
#define MAKE_SCROLL_LOCK      70
#define MAKE_HOME             71
#define MAKE_PGUP             73
#define MAKE_KEYPAD_MINUS     74
#define MAKE_CENTER           76
#define MAKE_KEYPAD_PLUS      78
#define MAKE_END              79
#define MAKE_PGDWN            81
#define MAKE_INS              82
#define MAKE_DEL              83
#define MAKE_RIGHT      77
#define MAKE_LEFT       75
#define MAKE_UP         72
#define MAKE_DOWN       80
#define MAKE_ENTER      28
#define MAKE_TAB        15
#define MAKE_SPACE      57
#define MAKE_CTRL       29
#define MAKE_ALT        56
#define MAKE_ESC        1
#define BREAK_1                (2 +128)
#define BREAK_2                (3 +128)
#define BREAK_3                (4 +128)
#define BREAK_4                (5 +128)
#define BREAK_5                (6 +128)
#define BREAK_6                (7 +128)
#define BREAK_7                (8 +128)
#define BREAK_8                (9 +128)
#define BREAK_9                (10+128)
#define BREAK_0                (11+128)
#define BREAK_MINUS            (12+128)
#define BREAK_EQUALS           (13+128)
#define BREAK_BKSP             (14+128)
#define BREAK_Q                (16+128)
#define BREAK_W                (17+128)
#define BREAK_E                (18+128)
#define BREAK_R                (19+128)
#define BREAK_T                (20+128)
#define BREAK_Y                (21+128)
#define BREAK_U                (22+128)
#define BREAK_I                (23+128)
#define BREAK_O                (24+128)
#define BREAK_P                (25+128)
#define BREAK_LFT_BRACKET      (26+128)
#define BREAK_RGT_BRACKET      (27+128)
#define BREAK_A                (30+128)
#define BREAK_S                (31+128)
#define BREAK_D                (32+128)
#define BREAK_F                (33+128)
#define BREAK_G                (34+128)
#define BREAK_H                (35+128)
#define BREAK_J                (36+128)
#define BREAK_K                (37+128)
#define BREAK_L                (38+128)
#define BREAK_SEMI             (39+128)
#define BREAK_APOS             (40+128)
#define BREAK_TILDE            (41+128)
#define BREAK_LEFT_SHIFT       (42+128)
#define BREAK_BACK_SLASH       (43+128)
#define BREAK_Z                (44+128)
#define BREAK_X                (45+128)
#define BREAK_C                (46+128)
#define BREAK_V                (47+128)
#define BREAK_B                (48+128)
#define BREAK_N                (49+128)
#define BREAK_M                (50+128)
#define BREAK_COMMA            (51+128)
#define BREAK_PERIOD           (52+128)
#define BREAK_FOWARD_SLASH     (53+128)
#define BREAK_RIGHT_SHIFT      (54+128)
#define BREAK_PRT_SCRN         (55+128)
#define BREAK_CAPS_LOCK        (58+128)
#define BREAK_F1               (59+128)
#define BREAK_F2               (60+128)
#define BREAK_F3               (61+128)
#define BREAK_F4               (62+128)
#define BREAK_F5               (63+128)
#define BREAK_F6               (64+128)
#define BREAK_F7               (65+128)
#define BREAK_F8               (66+128)
#define BREAK_F9               (67+128)
#define BREAK_F10              (68+128)
#define BREAK_F11              (87+128)
#define BREAK_F12              (88+128)
#define BREAK_NUM_LOCK         (69+128)
#define BREAK_SCROLL_LOCK      (70+128)
#define BREAK_HOME             (71+128)
#define BREAK_PGUP             (73+128)
#define BREAK_KEYPAD_MINUS     (74+128)
#define BREAK_CENTER           (76+128)
#define BREAK_KEYPAD_PLUS      (78+128)
#define BREAK_END              (79+128)
#define BREAK_PGDWN            (81+128)
#define BREAK_INS              (82+128)
#define BREAK_DEL              (83+128)
#define BREAK_RIGHT     205
#define BREAK_LEFT      203
#define BREAK_UP        200
#define BREAK_DOWN      208
#define BREAK_ENTER     156
#define BREAK_TAB       143
#define BREAK_SPACE     185
#define BREAK_CTRL      157
#define BREAK_ALT       184
#define BREAK_ESC       129

void alert_error(char *msg)
{
  printf("%s\n",msg);
  delay(2000);
  gotoxy(1,1);
}

//STRUCTURES AND STUFF!

//This is a color.
typedef struct rgb_color_type {
	unsigned char red; //degreee of red
	unsigned char green; //degree of green
	unsigned char blue; //degree of blue
} rgb;

//This is a palette of 256 colors.
typedef struct pal_256 {
  rgb colors[256];
  } palette;

//This is a  box
typedef struct box {
  int p[4];  // Four points, 2 for upper left, 2 for bottom right
  int active;  //Wether it's active or not.
  int hit;  //Wether it has been hit or not.
  } *box_ptr;


int check_collision(box_ptr off , box_ptr def) {
  if((off->active) && (def->active)) {
    if((off->p[0] > def->p[2]) || (off->p[2] < def->p[0]) || (off->p[1] > def->p[3]) || (off->p[3] < def->p[1])) return 0;
//    if(off->p[0] > def->p[2]) return 0;
//    if(off->p[2] < def->p[0]) return 0;
//    if(off->p[1] > def->p[3]) return 0;
//    if(off->p[3] < def->p[1]) return 0;
    else {
      //printf(" FOUND!\n");
      return 1;
      }
    }
  else return 0;    
  }

typedef struct pcxheader
{
  unsigned char maker;
  unsigned char ver_info;
  unsigned char encoding;
  unsigned char bits_per_pxl;
  short xmin,ymin,xmax,ymax;
  short Hres,Vres;
  unsigned char vgapalette[48];   /*This is where a 16 color palette gets put*/
  unsigned char byte_resd;
  unsigned char numcolorplanes;
  short bytes_per_line;             /*Always even; number of bytes per line*/
  short palette_flag;
  char padding[54];               /*Garbage to pad out the 256 byte header*/
  short hsize;
  short vsize;
};

typedef struct pcx {
  int height;
  int width;
  int memsize;
  pcxheader header;
  char *image_data;
  palette pal;
  char filename[25];
  } *pcx_ptr;

typedef struct tru {
  int height;
  int width;
  char *image_data;
  } *tru_ptr;

//VIDEO FUNCTIONS & DECLARATIONS!

//This function sets video modes.
void set_video_mode(int mode)
{
	union REGS regs;
	regs.x.ax = mode;
	int86(0x10, &regs, &regs);
}

//Declaration of the video buffer, where the drawing actually happens.
char *video_buffer = (char *)0xa0000;

//Declaration of the double buffer, a buffer used to speed frame rates. Not implemented yet.
char *double_buffer = NULL;

void init_double_buffer()
{
 double_buffer = (char *)malloc(640*400);
 memset(double_buffer, 0, 640*400);
// double_buffer = (char *)malloc(520*240);
// memset(double_buffer, 0, 520*240);
}

void kill_double_buffer() {
  free(double_buffer);
  }

/*
void show_double_buffer() {
  memcpy(video_buffer, double_buffer, sizeof(double_buffer));
  memset(double_buffer,0,320*200+1);
  }
*/

//This function waits until the Monitor refreshes before allowing the program to continue.
void wait4vsync(void)
{
 while(inp(VGA_INPUT_STATUS_1) & VGA_VSYNC_MASK) {}
 while(!(inp(VGA_INPUT_STATUS_1) & VGA_VSYNC_MASK)) {}
}

//PALETTE CRAP!
//Blast a color into the given palete register.
void set_color(unsigned char index, rgb *color)
{
	outportb(PALETTE_MASK,0xff);
	outportb(PALETTE_WR,index);
	outportb(PALETTE_DATA,color->red);
	outportb(PALETTE_DATA,color->green);
	outportb(PALETTE_DATA,color->blue);
}

//Blast an entire 256 palette into all 256 registers.
void set_pal(palette pal) {
  int ctr;
  for(ctr=0;ctr<256;ctr++) {
    set_color(ctr,(rgb *)&pal.colors[ctr]);
    }
  }

//Cycle the given colors in the palette.  I'm proud of this one.
palette pal_cycle(palette pal,int start, int end) {
  int ctr;
  rgb temp;
  temp = pal.colors[end];

  //Go through the colors given and shift their position 1 down.
  for(ctr=end-1;ctr>=start;ctr--) {
    pal.colors[ctr+1] = pal.colors[ctr];
    }

  pal.colors[start] = temp;
  set_pal(pal);
  return pal;
  }

//This function is used to grab a palette out of a 256 color pcx, or from a 256 palete file.
palette pal_import(char filename[25], int pcx) {
  FILE *fp;
  palette pal;
  int ctr;
  int c = 12;

  //open the file.
  fp = fopen(filename,"rb");

  //If its a pcx, go all the way to the end, where the palette is kept.
  if(pcx) {
    fseek(fp, -((256 * 3) + 1), SEEK_END);
    c = fgetc(fp);
    }

  //grab the colors.
  if(c == 12) {
    for(ctr=0;ctr<256;ctr++) {
      pal.colors[ctr].red   = fgetc(fp);
      pal.colors[ctr].green = fgetc(fp);
      pal.colors[ctr].blue  = fgetc(fp);
      }
    if(pcx) {
      for(ctr=0;ctr<256;ctr++) {
	pal.colors[ctr].red   /= 4;
	pal.colors[ctr].green /= 4;
	pal.colors[ctr].blue  /= 4;
	}
      }
    }
  else {
    //but if its only a 16 color pcx, only set the first 16 color register.
    for(ctr=0;ctr<15;ctr++) {
      pal.colors[ctr].red   = fgetc(fp);
      pal.colors[ctr].green = fgetc(fp);
      pal.colors[ctr].blue  = fgetc(fp);
      }
    //And set the last of them to black.
    for(ctr=16;ctr<256;ctr++) {
      pal.colors[ctr].red   = 0;
      pal.colors[ctr].green = 0;
      pal.colors[ctr].blue  = 0;
      }
    }

  fclose(fp);

  return pal;
  }

//Save the current palette into a neat little 768 byte palette file.
void save_pal(palette pal,char filename[25]) {
  int ctr;
  FILE *fp;

  fp = fopen(filename,"wb");
  for(ctr=0;ctr<256;ctr++) {
    fputc(pal.colors[ctr].red,fp);
    fputc(pal.colors[ctr].green,fp);
    fputc(pal.colors[ctr].blue,fp);
    }

  fclose(fp);
  }

//Set the current palette to all black.
palette clear_pal()
  {
   palette pal;
   int index;
   for(index = 0; index < 256; index++)
  {
   pal.colors[index].red = 0;
   pal.colors[index].green = 0;
   pal.colors[index].blue = 0;
  }
  return pal;
 }

//DRAWING FUNCTIONS!
//FInally! Put a pixel!
void put_pixel(int x, int y, char color)
{
 //Make sure its not outside of the screen.
 if((x >= 0) && (x < 320) && (y > 0) && (y < 200))
 {
   _farpokeb(_dos_ds,video_buffer + (y << 8) + (y << 6) + x, color);
 }
}

//void show_double_buffer(int offset) {
void show_double_buffer(int xoffset,int yoffset,int clear) {
  int ctr;
  int ctr2=0;
  //memcpy(video_buffer, double_buffer, sizeof(320*200));
  /*for(ctr=0;ctr<200;ctr++) {
    memcpy(video_buffer,double_buffer,320*200);
    }*/
  /*for(ctr=0;ctr<200;ctr++) {
    for(ctr2=0;ctr2<320;ctr2++) {
      put_pixel(ctr2,ctr,double_buffer[520*ctr+ctr2+offset]);
      }
    }*/

  for(ctr=yoffset;ctr<yoffset+200;ctr++) {
    asm volatile (
    "pushl %%es\r\n
     movw %w0,%%es\r\n
     rep; movsl\r\n
     popl %%es\r\n":
     :"rm" (_dos_ds),"c" (640/4),"S" (&double_buffer[640*ctr+xoffset]),
     "D" (0xA0000+(ctr2*320))
     :"%ecx","%esi","%edi");
    ctr2++;
    }

  /*for(ctr=0;ctr<200;ctr++) {
    asm volatile (
    "pushl %%es\r\n
     movw %w0,%%es\r\n
     rep; movsl\r\n
     popl %%es\r\n":
     :"rm" (_dos_ds),"c" (520/4),"S" (&double_buffer[520*ctr+offset]),
     "D" (0xA0000+(ctr*320))
     :"%ecx","%esi","%edi");
    }*/
// Note: sizeof(double_buffer) would be sizeof(char *)...
// not quite what you wanted...?

//Copy the screen. <you said I was a thief ;>
  /*asm volatile (
  "pushl %%es\r\n
   movl %0,%%es\r\n
   rep; movsl\r\n
   popl %%es\r\n":
   :"m" (_dos_ds),"a" (0),"c" (320*200/4),"S" (double_buffer),"D" (0xA0000):
   "%ecx","%esi","%edi");*/


  //memset(double_buffer,0,520*240);
  if(clear)
  {
    asm volatile (
     "pushl %%es\r\n
      pushl %%ds\r\n
      popl %%es\r\n
      rep; stosl\r\n
      popl %%es\r\n":
      :"a" (0),"c" (640*400/4),"D" (double_buffer):
      "%ecx","%edi","memory");
  }

  /*asm volatile (
   "pushl %%es\r\n
    pushl %%ds\r\n
    popl %%es\r\n
    rep; stosl\r\n
    popl %%es\r\n":
    :"a" (0),"c" (520*240/4),"D" (double_buffer):
    "%ecx","%edi","memory");*/

  // memset(double_buffer,0,640*400);
  // I do dislike memset... hehe
 /* asm volatile (
  "pushl %%es\r\n
   pushl %%ds\r\n
   popl %es\r\n
   rep; stosl\r\n
   popl %%es\r\n":
   :"a" (0),"c" (320*200/4),"D" (double_buffer):
   "%ecx","%edi","memory");*/
  }

void put_pixel_b(short int x, short int y, char color) {
  if((0 <= x ) && (x< 640) && (0<=y) && (y<400)) {
    if(color!=0) double_buffer[y*640+x] = color;
    }
  /*if((0 <= x ) && (x< 520) && (0<=y) && (y<240)) {
    if(color!=0) double_buffer[y*520+x] = color;
    }*/
  }


//Draw a line, any direction.
void line(int x1, int y1, int x2, int y2,int col) {
  float p[2];
  int ctr;
  float xdist = 0.0;
  float ydist = 0.0;
  float xoff = 0.0;
  float yoff = 0.0;

  xdist = abs(x2 - x1);
  ydist = abs(y2 - y1);

  xoff = xdist / ydist;
  yoff = ydist / xdist;

  p[0] = x1;
  p[1] = y1;

  if(ydist > xdist) {
    for(ctr=0;ctr<ydist;ctr++) {
      put_pixel((int)p[0],(int)p[1],col);

      if(p[0] < x2) p[0] += xoff;
      else if(p[0] > x2) p[0] -= xoff;

      if(p[1] < y2) p[1]++;
      else if(p[1] > y2) p[1]--;
      }
    }
  else if(xdist > ydist) {
    for(ctr=0;ctr<xdist;ctr++) {
      put_pixel((int)p[0],(int)p[1],col);
      if(p[0] < x2) p[0]++;
      else if(p[0] > x2) p[0]--;

      if(p[1] < y2) p[1] += yoff;
      else if(p[1] > y2) p[1] -= yoff;
      }
    }
  else {
    for(ctr=0;ctr<xdist;ctr++) {
      put_pixel((int)p[0],(int)p[1],col);
      if(p[0] < x2) p[0] += xoff;
      else if(p[0] > x2) p[0] -= xoff;

      if(p[1] < y2) p[1] += yoff;
      else if(p[1] > y2) p[1] -= yoff;
      }
    }
  }

//Draw a rectangle
void rect(int x,int y,int height,int width,int color) {
  int ctr;
  int ctr2;
  for(ctr=y;ctr<y+height;ctr++) {
    for(ctr2=x;ctr2<x+width;ctr2++) {
      put_pixel(ctr2,ctr,color);
      }
    }
  }

//Lightning Bolt
void lit(int x1, int x2, int y, int intensity, int arcs,int col) {
  int tense;
  int pos;
  int off;
  int ctr;
  int oldp[2];

  off = (x2 - x1) / arcs;
  pos = x1;
  tense = (rand() % intensity) - (intensity / 2);

  for(ctr=0;ctr<=arcs;ctr++) {
    if(ctr > 0) line(oldp[0],oldp[1],pos,y+tense,col);
    put_pixel(pos,y+tense,col);
    oldp[0] = pos;
    oldp[1] = y + tense;
    pos += off;
    tense = (rand() % intensity) - (intensity / 2);
    }
  }

// set the color 'color' in register 'index' ('color' is rgb type)

void clear_screen() {
  asm volatile (
  "pushl %%es\r\n
   movl %0,%%es\r\n
   rep; stosl\r\n
   popl %%es\r\n":
   :"m" (_dos_ds),"a" (0),"c" (320*200/4),"D" (0xA0000):
   "%ecx","%edi");
  }

//Clear the screen.
/*void clear_screen() {
  int xctr;
  int yctr;

  //memset(video_buffer,3,320*200+1);

  for(yctr=0;yctr<200;yctr++) {
    for(xctr=0;xctr<320;xctr++) {
      put_pixel(xctr,yctr,0);
      }
    }
  }*/

void litnin() {
  int arcctr = 1;
  do {
    lit(0,300,100,30,10,11);
    lit(0,300,100,30,10,56);
    lit(0,300,100,30,10,90);
    lit(0,300,100,30,10,151);
    lit(0,300,100,30,10,rand() % 255);
    if(arcctr > 20) arcctr = 1;
    else arcctr++;
    clear_screen();
    } while(!kbhit());
  }

void circle(int x, int y,int col,int rad)
{
 float deg = 0;
 int X = 0;
 int Y = 0;
 do {
   X = (int)(rad * cos(deg)); // 20 is the radius<BR>
   Y = (int)(rad * sin(deg));
   put_pixel (X+x, Y+y, col);
   deg += 0.005;
  } while (deg <= 6.4);
}

void circle_b(int x, int y,int col,int rad)
{
 float deg = 0;
 int X = 0;
 int Y = 0;
 do {
   X = (int)(rad * cos(deg)); // 20 is the radius<BR>
   Y = (int)(rad * sin(deg));
   put_pixel_b(X+x, Y+y, col);
   deg += 0.005;
  } while (deg <= 6.4);
}

void get_pcx(pcx_ptr file) {
  int bytesgotten;
  int cnt;
  FILE *fp;
  char filename[25];

  printf("Give me pcx to import.\n");
  scanf("%s",file->filename);

  if((fp = fopen(file->filename,"rb")) == NULL) {
    printf("file %s doesn't exist, 00ps\n",filename);
    return;
    }

  fseek(fp, 8, SEEK_SET);

  file->width = fgetc(fp);
  file->width = ((fgetc(fp) << 8) | file->width) + 1;
  file->height = fgetc(fp);
  file->height = ((fgetc(fp) << 8) | file->height) + 1;

  printf("%d",file->width);
  printf(" x %d\n",file->height);

  file->memsize = file->width*file->height;


  file->image_data = (char *)malloc(file->memsize);

  /*for(bytesgotten=0;bytesgotten<file->memsize;bytesgotten++) {
    file->image_data[bytesgotten] = fgetc(fp);
    }*/
  fseek(fp, 128, SEEK_SET);

  //int totwritten,filechar,writecount,i;
  //totwritten = 0;
  //while(totwritten<file->memsize)  {
  //  filechar=fgetc(fp);
  //  if(0xC0==(filechar & REPEAT)) {  /* If there's a repeat flag (top 2 bits set)*/
  //    writecount=filechar & 0x3F;        /* Writecount = lower 6 bits */
  //    filechar=fgetc(fp);           /* and pixel = next byte. */
  //    }
  //  else writecount=1;
  //  for(i=0;i<writecount;i++)  {
  //    *file->image_data++=filechar;
  //    totwritten++;
  //    }
  //  }
  fread(file->image_data, 1, file->memsize, fp);

  printf("got %d bytes\n",/*totwritten*/file->memsize);
  file->pal = pal_import(filename,1);
  printf("got palette\n");
  fclose(fp);
  };

void kill_pcx(pcx_ptr file) {
  free(&file->image_data);
  }

void pcx_to_tru(pcx_ptr pcxfile) {
  FILE *fp;
  int ctr;
  char filename[25];

  printf("Name of .TRU to be saved.\n");
  scanf("%s",filename);

  fp = fopen(filename,"wb");

  fprintf(fp,"%d %d",pcxfile->width,pcxfile->height);

  for(ctr=0;ctr<pcxfile->memsize;ctr++) {
    fputc(pcxfile->image_data[ctr],fp);
    }

  printf("%s saved. . .\n",filename);
  fclose(fp);
  }

void get_tru(char filename[25],tru_ptr trufile) {
  FILE *fp;
  int ctr;

  if((fp = fopen(filename,"rb")) == NULL) {
    printf("file %s doesn't exist, 00ps\n",filename);
    return;
    }

  fscanf(fp,"%d %d",&trufile->width,&trufile->height);
  printf("got %d x %d\n",trufile->width,trufile->height);

  trufile->image_data = (char *)malloc(trufile->width*trufile->height);

  for(ctr=0;ctr<trufile->width*trufile->height;ctr++) {
    trufile->image_data[ctr] = fgetc(fp);
    }

  fclose(fp);
  }

void kill_tru(tru_ptr trufile) {
  free(&trufile->image_data);
  }

void draw_tru(int x, int y, tru trufile) {
  int ctr;
  int ctr2;
  int buffset = 0;

  /*for(ctr=y;ctr<y+trufile.height;ctr++) {
    for(ctr2=x;ctr2<x+trufile.width;ctr2++) {
      put_pixel(ctr2,ctr,trufile.image_data[buffset]);
      buffset++;
      }
    }*/

  char Temp1, Temp2;
  int X = 0, Y = 0;


  while((Y < trufile.height) && ((X * Y) < (trufile.width*trufile.height)))
  {
    Temp1 = *trufile.image_data;
    trufile.image_data++;

    if((Temp1 & 192) == 192)       // Check if the top two bits of the byte
    {                              // are set.
      Temp2 = *trufile.image_data;
      trufile.image_data++;

      for(int i = 0; i < (Temp1 & 63); i++)
      {
	put_pixel(X+x, Y+y, Temp2);
	X++;
	if(X == trufile.width)  {Y++; X = 0; }
      }
    }

    else                              // If they are not set, just plot it
    {                                 // to the screen.
      put_pixel(X+x, Y+y, Temp1);
      X++;
      if(X == trufile.width) {Y++; X = 0; }
    }
  }
}

struct letter {
  int height;
  int width;
  char let;
  char *buffer;
  };

struct number {
  int height;
  int width;
  int number;
  char *buffer;
  };

typedef struct ffnt {
  int letwidth;
  int letheight;
  letter letters[26];
  int numwidth;
  int numheight;
  number numbers[10];
  } *font_ptr;

void make_font(char filename[25],char fontname[25]) {
  FILE *fp;
  FILE *fp2;
  FILE *tp;
  int ctr=0;
  int cnt;
  int height;
  int width;
  int filenum;
  int filechar;
  char let;
  char iname[25];
  char getex;
  char ext[4];
  unsigned char byte;
  char *buf;

  int i=0;
  if((fp = fopen(filename,"rb")) == NULL) {
    printf("Can't open file. . .\n");
    exit(-1);
    }
  if((fp2 = fopen(fontname,"wb")) == NULL) {
    printf("Couldn't create FONT!\n");
    exit(-1);
    }

  while(!feof(fp)) {
    i=0;
    getex = 'n';
    fscanf(fp,"%s",&iname);
    printf("%s : ",iname);
    while(getex != '.'){ getex=iname[i++]; }
    ext[0]=iname[i++];
    ext[1]=iname[i++];
    ext[2]=iname[i++];
    ext[3]=NULL;
    width=atoi(ext);
    printf("%d x ",width);
    if((tp = fopen(iname,"rb")) == NULL) {
      printf("Can't get this letta: %s\n",iname);
      exit(-1);
      }
    filenum = fileno(tp);
    height = filelength(filenum) / width;
    printf("%d\n",height);
    fprintf(fp2,"%d %d",width,height);
    for(cnt=0;cnt<height*width;cnt++) {
      filechar=fgetc(tp);
      byte=filechar;
      fputc(byte,fp2);
      }
    fclose(tp);
    }
  fclose(fp);
  fclose(fp2);
  }

void get_font(font_ptr font,char filename[25]) {
  int ctr;
  int cnt;
  FILE *fp;
  if((fp = fopen(filename,"rb"))==NULL) {
    printf("Couldn't open %s\n",filename);
    exit(-1);
    }
  font->letwidth = 0;
  font->letheight = 0;
  font->numwidth = 0;
  font->letheight = 0;

  for(ctr=0;ctr<26;ctr++) {
    font->letters[ctr].height = 0;
    font->letters[ctr].width = 0;
    }
  for(ctr=0;ctr<10;ctr++) {
    font->numbers[ctr].width = 0;
    font->numbers[ctr].height = 0;
    }

  for(ctr=0;ctr<10;ctr++) {
    fscanf(fp,"%d %d",&font->numbers[ctr].width,&font->numbers[ctr].height);
    if(font->numbers[ctr].width>font->numwidth) font->numwidth = font->numbers[ctr].width;
    if(font->numbers[ctr].height>font->numheight) font->numheight = font->numbers[ctr].height;
    if((font->numbers[ctr].buffer = (char *)malloc(font->numbers[ctr].height*font->numbers[ctr].width)) == NULL) {
      printf("No memory for font, abort!\n");
      exit(-1);
      }

    for(cnt=0;cnt<font->numbers[ctr].height*font->numbers[ctr].width;cnt++) {
      font->numbers[ctr].buffer[cnt] = fgetc(fp);
      }
    }

  for(ctr=0;ctr<26;ctr++) {
    fscanf(fp,"%d %d",&font->letters[ctr].width,&font->letters[ctr].height);
    if(font->letters[ctr].width>font->letwidth) font->letwidth = font->letters[ctr].width;
    if(font->letters[ctr].height>font->letheight) font->letheight = font->letters[ctr].height;
    if((font->letters[ctr].buffer = (char *)malloc(font->letters[ctr].height*font->letters[ctr].width)) == NULL) {
      printf("No memory for font, abort!\n");
      exit(-1);
      }

    for(cnt=0;cnt<font->letters[ctr].height*font->letters[ctr].width;cnt++) {
      font->letters[ctr].buffer[cnt] = fgetc(fp);
      }
    }
  fclose(fp);
  }

int lettoint(char let) {
  switch(let) {
    case 'a':
    case 'A': return 0;
              break;
    case 'b':
    case 'B': return 1;
              break;
    case 'c':
    case 'C': return 2;
              break;
    case 'd':
    case 'D': return 3;
              break;
    case 'e':
    case 'E': return 4;
              break;
    case 'f':
    case 'F': return 5;
              break;
    case 'g':
    case 'G': return 6;
              break;
    case 'h':
    case 'H': return 7;
              break;
    case 'i':
    case 'I': return 8;
              break;
    case 'j':
    case 'J': return 9;
              break;
    case 'k':
    case 'K': return 10;
              break;
    case 'l':
    case 'L': return 11;
              break;
    case 'm':
    case 'M': return 12;
              break;
    case 'n':
    case 'N': return 13;
              break;
    case 'o':
    case 'O': return 14;
              break;
    case 'p':
    case 'P': return 15;
              break;
    case 'q':
    case 'Q': return 16;
              break;
    case 'r':
    case 'R': return 17;
              break;
    case 's':
    case 'S': return 18;
              break;
    case 't':
    case 'T': return 19;
              break;
    case 'u':
    case 'U': return 20;
              break;
    case 'v':
    case 'V': return 21;
              break;
    case 'w':
    case 'W': return 22;
              break;
    case 'x':
    case 'X': return 23;
              break;
    case 'y':
    case 'Y': return 24;
              break;
    case 'z':
    case 'Z': return 25;
              break;
    case '0': return 27;
              break;
    case '1': return 28;
              break;
    case '2': return 29;
              break;
    case '3': return 30;
              break;
    case '4': return 31;
              break;
    case '5': return 32;
              break;
    case '6': return 33;
              break;
    case '7': return 34;
              break;
    case '8': return 35;
              break;
    case '9': return 36;
              break;
    default : return 26;
              break;

    }
  }


void draw_character(int x,int y,font_ptr font,int which,int b)
{
  int type;
  int memsize;
  int cnt=0;
  int cnt2=0;

  if(which <= 26) type = 1;
  else type = 0;

  if(type)
  {
    memsize = font->letters[which].height*font->letters[which].width;
    if(which != 26)
    {
      for(cnt=0;cnt<memsize;cnt++)
      {
        if(b) put_pixel_b(x+cnt2,y,font->letters[which].buffer[cnt]);
        else put_pixel(x+cnt2,y,font->letters[which].buffer[cnt]);
        cnt2++;
        if(cnt2 >= font->letters[which].width)
        {
          cnt2 = 0;
          y++;
        }
      }
    }
  }
  else
  {
    which-=27;
    memsize = font->numbers[which].height*font->numbers[which].width;
    if(which<10)
    {
      for(cnt=0;cnt<memsize;cnt++)
      {
        if(b) put_pixel_b(x+cnt2,y,font->numbers[which].buffer[cnt]);
        else put_pixel(x+cnt2,y,font->numbers[which].buffer[cnt]);
        cnt2++;
        if(cnt2 >= font->numbers[which].width)
        {
          cnt2 = 0;
          y++;
        }
      }
    }
  }
}

void draw_letter(int x,int y,font_ptr font,int which,int b) {
  int ctr;
  int cnt=0;
  int cnt2 = 0;
  int done=0;
  int memsize = font->letters[which].height*font->letters[which].width;
  if(which!=26) {
    for(cnt=0;cnt<memsize;cnt++) {
      if(b) put_pixel_b(x+cnt2,y,font->letters[which].buffer[cnt]);
      else put_pixel(x+cnt2,y,font->letters[which].buffer[cnt]);
      cnt2++;
      if(cnt2 >= font->letters[which].width) {
        cnt2 = 0;
        y++;
        }
      }
    }
  }

void draw_number(int x,int y,font_ptr font,int which,int b) {
  int ctr;
  int cnt;
  int cnt2 = 0;
  if(which<10) {
    for(cnt=0;cnt<font->numbers[which].height*font->numbers[which].width;cnt++) {
      if(b) put_pixel_b(x+cnt2,y,font->numbers[which].buffer[cnt]);
      else put_pixel(x+cnt2,y,font->numbers[which].buffer[cnt]);
      cnt2++;
      if(cnt2 >= font->numbers[which].width) {
        cnt2 = 0;
        y++;
        }
      }
    }
  }

void draw_string(int x,int y,font_ptr font,char string[99],char justify,int b) {
  int total = strlen(string);
  int ctr;
  int which;

  if(justify=='l')
  {
    /*for(ctr=0;ctr<total;ctr++) {
      draw_letter(x+ctr*font->letwidth,y,font,lettoint(string[ctr]),b);
      }*/
//    draw_letter(x,y,font,lettoint(string[0]),b);
    for(ctr=0;ctr<total;ctr++)
    {
      which = lettoint(string[ctr]);
      draw_character(x,y,font,which,b);
      if(which <= 26) x += font->letters[which].width;
      else x += font->numbers[which-27].width;
    }
  }
  else if(justify=='c')
  {
    x = x-((total*font->letwidth)/2);
    for(ctr=0;ctr<total;ctr++)
    {
      which = lettoint(string[ctr]);
      draw_character(x,y,font,which,b);
      if(which <= 26) x += font->letters[which].width;
      else x += font->numbers[which-27].width;
    }
  }
  else if(justify=='r') {
    /*for(ctr=total-1;ctr>=0;ctr--) {
      draw_letter(x-(total-ctr)*font->letwidth,y,font,lettoint(string[ctr]),b);
      }*/

    for(ctr=total-1;ctr>=0;ctr--) {
      which = lettoint(string[ctr]);
      if(which <= 26) x -= font->letters[which].width;
      else x -= font->numbers[which-27].width;
//      draw_letter(x,y,font,lettoint(string[ctr]),b);
      draw_character(x,y,font,which,b);
      }
    }
  }

void draw_num(int x,int y,font_ptr font,int total,char justify,int b) {
  if(justify=='l') {
    if(total>9) {
      draw_number(x,y,font,total/10,b);
      draw_number(x+font->numwidth,y,font,(int)(fmod(total,10)),b);
      }
    else draw_number(x,y,font,total,b);
    }
  else if(justify=='c')
  {
    if(total>9)
    {
      draw_number(x,y,font,(int)(fmod(total,10)),b);
      draw_number(x-font->numwidth,y,font,total/10,b);
    }
  }
  else if(justify=='r') {
    if(total>9) {
      draw_number(x-font->numwidth,y,font,(int)(fmod(total,10)),b);
      draw_number(x-font->numwidth*2,y,font,total/10,b);
      }
    else draw_number(x-font->numwidth,y,font,total,b);
    }
  }


void kill_font(font_ptr font) {
  int ctr;
  for(ctr=0;ctr<10;ctr++) {
    free(font->numbers[ctr].buffer);
    }
  for(ctr=0;ctr<26;ctr++) {
    free(font->letters[ctr].buffer);
    }
  }

unsigned char raw_key, key_table[128];
int keys_active=0;

_go32_dpmi_seginfo old_key_handler,new_key_handler;


void key_handler(void)
{
 unsigned char al, ah;

 asm("cli; pusha");

 raw_key = inportb(0x60);

 al = inportb(0x61);
 al |= 0x82;
 outportb(0x61, al);
 al &= 0x7f;

 outportb(0x61, al);

 /* you have the option of putting this outside */

 if(raw_key < 128) {
   if(!key_table[raw_key]) {
     key_table[raw_key] = 1;
     keys_active++;
     }
   }
 else {
   if(key_table[raw_key-128]) {
     key_table[raw_key-128] = 0;
     keys_active--;
     }
   }
 outportb(0x20, 0x20);

 asm("popa; sti");
}


void key_init(void) /* function to swap state */
{
 int index;

 new_key_handler.pm_offset   = (int)key_handler;

 new_key_handler.pm_selector = _go32_my_cs();

 _go32_dpmi_get_protected_mode_interrupt_vector(0x9, &old_key_handler);

 _go32_dpmi_allocate_iret_wrapper(&new_key_handler);

 _go32_dpmi_set_protected_mode_interrupt_vector(0x9,&new_key_handler);

 for(index=0;index<128;index++) key_table[index] = 0;
}

void key_delete(void)
{
 _go32_dpmi_set_protected_mode_interrupt_vector(0x9,&old_key_handler);
}

