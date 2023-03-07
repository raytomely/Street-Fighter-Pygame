#include "fenix.h"
//#include "jason.h"

struct image {
  int height;
  int width;
  int memsize;
  char filename[25];
  unsigned char *idata;
  };

struct sprite {
  int x_off[2];
  int y_off[2];
  int imag_num[2];
  int last_image;
  int op[4];
  int dp[4];
  };

typedef struct frameset {
  image images[500];
  int lastimage;
  sprite sprites[500];
  int lastsprite;
  char refilename[25];
  } *fs_ptr;

void init_fs(fs_ptr set) {
  int ctr;
  int ctr2;
  for(ctr=0;ctr<500;ctr++) {
    set->images[ctr].height = 0;
    set->images[ctr].width = 0;
    set->images[ctr].memsize = 0;
    for(ctr2=0;ctr2<2;ctr2++) {
      set->sprites[ctr].x_off[ctr2] = 0;
      set->sprites[ctr].y_off[ctr2] = 0;
      set->sprites[ctr].imag_num[ctr2] = 0;
      }
    set->sprites[ctr].last_image=0;
    set->sprites[ctr].op[0] = 0;
    set->sprites[ctr].op[1] = 0;
    set->sprites[ctr].op[2] = 0;
    set->sprites[ctr].op[3] = 0;
    set->sprites[ctr].dp[0] = 0;
    set->sprites[ctr].dp[1] = 0;
    set->sprites[ctr].dp[2] = 0;
    set->sprites[ctr].dp[3] = 0;
    }
  }


struct frame
{
  int fram_num;  //Which animation frame it is.
  int xmov;
  int ymov;
  char type; // The type of frame.
  char power; // The damage of the move
  char reaction; // The reaction number the move causes
  char orient; // Frame orientation
  char cancel; // Cancellation
  char range;
  char invincibility;
  char element;
  int active;
};

struct sequence
{
//  ursentry uentries[200];
  int moves[150];
  int used;
  int nextseq;
  int active;
};

typedef struct moveset
{
  sequence sequences[900];
  frame frames[900];
  int lastframe;
} *ms_ptr;

void init_ms(ms_ptr set)
{
  int ctr;
  int ctr2;
  for(ctr=0;ctr<900;ctr++)
  {
    set->sequences[ctr].active=0;
    set->sequences[ctr].used=0;
    set->sequences[ctr].nextseq = 0;
  }
  for(ctr=0;ctr<900;ctr++)
  {
    set->frames[ctr].fram_num = 0;
    set->frames[ctr].xmov = 0;
    set->frames[ctr].ymov = 0;
  }
}

struct special
{
  char input[10];
  int total;
  int seq_num;
  char type;
  int mod;
  char vocfile[15];
  int chains[3];
  char ide[15];
  char seq[15];
  char cmd[15];
};

struct cspecial
{
  char input[5];
  int total;
  int seq_num;
  char type;
  int mod;
  int chains[3];
};

struct super
{
  char input[99];
  int total;
  int seq_num;
  char type;
  int cost;
  char ide[15];
  char seq[15];
  char cmd[15];
  char name[99];
};

struct desperation
{
  char input[10];
  int total;
  int seq_num;
  char type;
  int cost;
  int life;
  char ide[15];
  char seq[15];
  char cmd[15];
};

struct grab
{
  char damage;
  char type;
  char input[3];
  int int1;
  int int2;
  int action;
  int reaction;
  int direction;
  char vocfile[20];
};

struct soundfx
{
  int seq;
  int framenum;
  int which;
};

typedef struct keyset
{
  int range;
  special attacks[50];
  int total;
  cspecial cspecials[50];
  super supers[20];
  int suptotal;
  grab grabs[50];
  int grabtotal;
  char sounds[30][25];
  soundfx fx[50];
  int lastsound;
  char quotes[10][50];
  int lastquote;
  desperation desperations[20];
  int lastdesperation;
  char name[20];
} *ks_ptr;

struct projectile {
  int p[2];
  int active;
  int seq;
  int curr_frame;
  int direction;
  char flip;
  };

typedef struct portrait {
  int height;
  int width;
  char *buf;
  } *port_ptr;

struct character
{
  portrait port;
  char idname1[99];
  char idname2[99];
  int alt;
  char hidname[99];
  int hid;
  int hidactive;
};

typedef struct info {
  int p[2];
  int life;
  int wins;
  box obox;
  box dbox;
  box pboxes[20];
  frame cf;
  frame pframes[20];
  sprite curr_sprite;
  grab curr_grab;
  int second;
  int throwing;
  int alive;
  int super;
  int combo;
  int blocking;
  int lowblock;
  int curr_seq;
  int curr_frame;
  int mid_seq;
  int status;
  int tag;
  int falling;
  int control;
  int frost;
  int frostctr;
  int countering;
  int stun;
  int super_subset;
  int curr_mode;
  int super_kill;

  int tagattack;
  int tagsuper;

  int taginseq;
  int tagoutseq;
  int tauntseq;
  int tagsuperseq;
  int tagspecialseq;

  char super_name[99];
  char curr_input;

  char name[25];
  portrait smallpict;
  portrait bigpict;
  char ibuffer[10];
  char cbuffer[10];
  } *info_ptr;

int get_portrait(port_ptr port,char filename[25]) {
  int i=0;
  int filenum;
  char getex;
  char ext[4];
  int ctr=0;
  unsigned long length;
  FILE *fp;
  if((fp = fopen(filename,"rb")) == NULL)
  {
    printf("Can't open portrait %s, aborting.\n",filename);
    return 0;
  }

  while(getex != '.'){ getex=filename[i++]; }
  ext[0]=filename[i++];
  ext[1]=filename[i++];
  ext[2]=filename[i++];
  ext[3]=NULL;
  port->width=atoi(ext);
//  printf("%d\n",port->width);
//  delay(2000);

  filenum = fileno(fp);
  length = filelength(filenum);//fileno(fp));

//  printf("Length:  %ld\n",length);
//  delay(2000);

  //port->height = length / port->width;
  port->height = (int)(length / port->width);

  if((port->buf = (char *)malloc(length)) == NULL)
  {
    printf("Can't allocate BG buffer, aborting.\n");
    return 0;
  }

  //fread(port->buf,1,length,fp);
  while(!feof(fp)) {
    port->buf[ctr] = fgetc(fp);
    ctr++;
    }

  fclose(fp);
//  delay(10000);


  return 1;
  }

void kill_portrait(port_ptr port) {
//  free(port->buf);
  }

void draw_portrait(int x,int y, port_ptr port,int flip) {
  int ctr;
  int ctr2;
  int cnt=0;
  for(ctr=y;ctr<y+port->height;ctr++) {
    if(!flip) {
      for(ctr2=x;ctr2<x+port->width;ctr2++) put_pixel_b(ctr2,ctr,port->buf[cnt++]);
      }
    else {
      for(ctr2=x+port->width;ctr2>x;ctr2--) put_pixel_b(ctr2,ctr,port->buf[cnt++]);
      }
    }
  }

/*struct faction
{
  character characters[20];
  int last_character;
  portrait bigpic;
  MIDI *bgtune;
  int rows,cols;
};*/

typedef struct character_set
{
  character characters[200];
  int last_character;
  int last_faction;
  portrait bigpic;
  MIDI *bgtune;
  int rows,cols;
} *cs_ptr;

void init_cs(cs_ptr set)
{
  set->last_character = -1;
  set->rows = -1;
  set->cols = -1;
  for(int ctr=0;ctr<200;ctr++)
  {
    set->characters[ctr].alt = 0;
    set->characters[ctr].hid = 0;
    set->characters[ctr].hidactive = 0;
  }
}

int check_hidchars(char filename[25])
{
  FILE *fp;
  char trash[25];

  if((fp = fopen("hid.den","rb")) == NULL) return 0;
  while(!feof(fp))
  {
    fscanf(fp,"%s",&trash);
    if(!strcmp(filename,trash)) return 1;
  }

  return 0;

}


int get_cs(cs_ptr set,char filename[25])
{
  init_cs(set);
  FILE *fp;
  FILE *fp2;
  char bgpicture[25];
  char bgmusic[25];
  char p1name[25];
  char port[25];
  int type;

  int ctr=0;
  int ctr2=0;

  if((fp = fopen(filename,"rb")) == NULL)
  {
    printf("Could not open config file %s\n",filename);
    return 0;
  }

  fscanf(fp,"%s",&bgpicture);
  get_portrait((port_ptr)&set->bigpic,bgpicture);

  fscanf(fp,"%s",&bgmusic);

  set->bgtune = load_midi(bgmusic);

  fscanf(fp,"%d %d",&set->rows,&set->cols);

  fscanf(fp,"%s",&set->characters[ctr].idname1);

  while(strcmp(set->characters[ctr].idname1,"end"))
  {
    if(set->characters[ctr].idname1[0] == '&')
    {
      for(ctr2=1;ctr2<strlen(set->characters[ctr].idname1);ctr2++)
      {
        set->characters[ctr-1].idname2[ctr2-1] = set->characters[ctr].idname1[ctr2];
        set->characters[ctr-1].alt = 1;
      }
      fscanf(fp,"%s",&set->characters[ctr].idname1);
    }

    if(set->characters[ctr].idname1[0] == '!')
    {
      for(ctr2=1;ctr2<strlen(set->characters[ctr].idname1);ctr2++)
      {
        set->characters[ctr-1].hidname[ctr2-1] = set->characters[ctr].idname1[ctr2];
        set->characters[ctr-1].hid = 1;
      }

      if(check_hidchars(set->characters[ctr-1].hidname)) set->characters[ctr-1].hidactive = 1;
      fscanf(fp,"%s",&set->characters[ctr].idname1);
    }

    if(strcmp(set->characters[ctr].idname1,"end"))
    {
      printf("Character %d : %s\n",ctr,set->characters[ctr].idname1);

      if((fp2 = fopen(set->characters[ctr].idname1,"rb")) == NULL)
      {
        printf("Couldn't open %s\n",set->characters[ctr].idname1);
        return 0;
      }
      fscanf(fp2,"%s",&p1name);
      fscanf(fp2,"%d",&type);
      fscanf(fp2,"%s",&port);
      get_portrait((port_ptr)&set->characters[ctr].port,port);
      fclose(fp2);
      ctr++;
      fscanf(fp,"%s",&set->characters[ctr].idname1);
    }
  }

  set->last_character = ctr;
  fclose(fp);
  return 1;
}



void init_ks(ks_ptr set)
{
  set->total = 0;
  set->suptotal = 0;
  set->grabtotal = 0;
  set->lastsound = 0;
  set->lastquote = 0;
  set->lastdesperation = 0;
  for(int ctr=0;ctr<50;ctr++)
  {
    strcpy(set->supers[ctr].name,"NONAME");
  }
}

int get_ide(fs_ptr set,char filename[25]) {
  FILE *fp;
  char trash[25];
  int ctr = 0;
  int ctr2=0;
  int garb;

  init_fs(set);

  if((fp = fopen(filename,"rb")) == NULL) {
    printf("Could not open file: %s\n",filename);
    delay(2000);
    return 0;
    }

  fscanf(fp,"%s",&trash);
  fscanf(fp,"%s",set->refilename);
  fscanf(fp,"%s",set->images[ctr].filename);

  while(strcmp((char *)set->images[ctr].filename,"_the_end")) {
    fscanf(fp,"%d%d%d",&set->images[ctr].memsize,&set->images[ctr].width,&set->images[ctr].height);
//    printf("%s %d %d %d\n",set->images[ctr].filename,set->images[ctr].memsize,set->images[ctr].width,set->images[ctr].height);
    ++ctr;
    fscanf(fp,"%s",&set->images[ctr].filename);
    }

  set->lastimage = ctr;
  //printf("Total IDE Frames: %d\n",set->lastimage);
  //getch();
  ctr = 0;


  fscanf(fp,"%s",&trash);
  fscanf(fp,"%s",&trash);
  if(feof(fp)) goto END;
  while(strcmp((char *)trash,"_the_end")) {
    fscanf(fp,"%d%d%d%d",&set->sprites[ctr].imag_num[0],&set->sprites[ctr].x_off[0],&set->sprites[ctr].y_off[0],&garb);
    set->sprites[ctr].last_image = 0;
    if(garb!=-1) {
      set->sprites[ctr].imag_num[1] = garb;
      fscanf(fp,"%d%d%d",&set->sprites[ctr].x_off[1],&set->sprites[ctr].y_off[1],&garb);
      set->sprites[ctr].last_image = 1;
      }
//    printf("%s %d %d %d\n",trash,set->sprites[ctr].imag_num,set->sprites[ctr].x_off,set->sprites[ctr].y_off,garb);
    ++ctr;
    fscanf(fp,"%s",&trash);
    }

  set->lastsprite = ctr - 1;
//  printf("Total Sprites: %d\n",set->lastsprite);
  //getch();

  fscanf(fp,"%s",trash);
  if(feof(fp)) goto END;
  for(ctr=0;ctr<=set->lastsprite;ctr++) {
    fscanf(fp,"%d%d%d%d",&set->sprites[ctr].op[0],&set->sprites[ctr].op[1],&set->sprites[ctr].op[2],&set->sprites[ctr].op[3]);
//    printf("Collision #%d\n",ctr);
//    printf("%d %d %d %d\n",set->sprites[ctr].op[0],set->sprites[ctr].op[1],set->sprites[ctr].op[2],set->sprites[ctr].op[3]);
    }

  for(ctr=0;ctr<=set->lastsprite;ctr++) {
    set->sprites[ctr].dp[0] = 0;
    set->sprites[ctr].dp[1] = 0;
    set->sprites[ctr].dp[2] = 0;
    set->sprites[ctr].dp[3] = 0;
    }

  END:
  fclose(fp);
  }

void get_re(fs_ptr set) {
  FILE *fp;
  int ctr;

  fp = fopen(set->refilename,"rb");

  for(ctr=0;ctr<set->lastimage;ctr++) {
    if((set->images[ctr].idata = (unsigned char *)malloc(set->images[ctr].memsize)) == NULL) {
      printf("Could not allocate memory. . .\n");
      exit(-1);
      }
    fread(set->images[ctr].idata,set->images[ctr].memsize,1,fp);
    }

  fclose(fp);
  }

void kill_frames(fs_ptr set) {
  int ctr;
  for(ctr=0;ctr<set->lastimage;ctr++) {
    free(set->images[ctr].idata);
    }
  }

void get_seq(ms_ptr set, char filename[25]) {
  FILE *fp;
  int num;
  int ctr = 0;
  int cnt;

  init_ms(set);

  if((fp = fopen(filename,"rb")) == NULL) {
    printf("Unable to open %s",filename);
    return;
    }

  fscanf(fp,"%d",&num);

  while(num != -1) {
    //printf("%d ",num);
    set->sequences[num].active = 1;
    fscanf(fp,"%d",&set->sequences[num].moves[ctr]);
    //printf("%d ",set->sequences[num].moves[ctr]);

    while(set->sequences[num].moves[ctr] != -1) {
      ctr++;
      fscanf(fp,"%d",&set->sequences[num].moves[ctr]);
      //printf("%d ",set->sequences[num].moves[ctr]);
      }


    set->sequences[num].nextseq = set->sequences[num].moves[ctr - 1];
    set->sequences[num].used = ctr - 2;
    ctr=0;
    //printf("%d: %d\n",num,set->sequences[num].used);
    //getch();
    fscanf(fp,"%d",&num);
    }

  while(fscanf(fp,"%d",&num) != EOF) {
    //printf("%d ",num);
    fscanf(fp,"%d%d%d %c%c%c%c%c%c%c",&set->frames[num].fram_num,
                                     &set->frames[num].xmov,
                                     &set->frames[num].ymov,
                                     &set->frames[num].type,
                                     &set->frames[num].power,
                                     &set->frames[num].reaction,
                                     &set->frames[num].orient,
                                     &set->frames[num].cancel,
                                     &set->frames[num].range,
                                     &set->frames[num].invincibility);
    /*printf("%d %d %d %c%c%c%c%c%c%c\n",set->frames[num].fram_num,
                                     set->frames[num].xmov,
                                     set->frames[num].ymov,
                                     set->frames[num].type,
                                     set->frames[num].power,
                                     set->frames[num].reaction,
                                     set->frames[num].orient,
                                     set->frames[num].cancel,
                                     set->frames[num].range,
                                     set->frames[num].invincibility);*/
    //getch();
    }

  set->lastframe = num;
 // printf("Total SEQ Frames: %d\n",set->lastframe);

  fclose(fp);
  }

void get_key(ks_ptr set,char filename[25]) {
  FILE *fp;
  int ctr;
  int done = 0;

  init_ks(set);
  if((fp = fopen(filename,"rt")) == NULL) {
    printf("Unable to open the file : %s\n",filename);
    exit(-1);
    }

  strcpy(set->name,"SF2IBM");
  fscanf(fp,"%d",&set->range);

  for(ctr=0;ctr<50;ctr++) {
    if(!done) {
      fscanf(fp,"%s %d %s",&set->attacks[ctr].input,&set->attacks[ctr].seq_num,&set->attacks[ctr].vocfile);
      //printf("%s %d %s\n",set->attacks[ctr].input,set->attacks[ctr].seq_num,set->attacks[ctr].vocfile);
      set->attacks[ctr].total = strlen(set->attacks[ctr].input);
      set->attacks[ctr].type = 'N';
      if(set->attacks[ctr].seq_num == -1) {
        set->total = ctr;
        done = 1;
        }
      }
    }

  done = 0;

  for(ctr=0;ctr<50;ctr++) {
    if(!done) {
      fscanf(fp,"%d %d %d %d %d %s",&set->grabs[ctr].int1,
                                        &set->grabs[ctr].int2,
                                        &set->grabs[ctr].action,
                                        &set->grabs[ctr].reaction,
                                        &set->grabs[ctr].direction,
                                        &set->grabs[ctr].vocfile);

      set->grabs[ctr].type = 1;
      set->grabs[ctr].damage = 1;

      switch((set->grabs[ctr].int1/10)) {
        case 1: set->grabs[ctr].damage = '1';
                break;
        case 2: set->grabs[ctr].damage = '2';
                break;
        case 3: set->grabs[ctr].damage = '3';
                break;
        case 4: set->grabs[ctr].damage = '4';
                break;
        case 5: set->grabs[ctr].damage = '5';
                break;
        case 6: set->grabs[ctr].damage = '6';
                break;
        }

      switch((int)(fmod(set->grabs[ctr].int1,10))) {
        case 0: set->grabs[ctr].type = '0';
                break;
        case 1: set->grabs[ctr].type = '1';
                break;
        case 2: set->grabs[ctr].type = '2';
                break;
        }

      switch((set->grabs[ctr].int2/10)) {
        case 7:
        case 8:
        case 6:  set->grabs[ctr].input[1] = 'b';
                 break;
        case 4:
        case 3:
        case 5:  set->grabs[ctr].input[1] = 'f';
                 break;
        case 1:  set->grabs[ctr].input[1] = 'u';
                 break;
        case 2:  set->grabs[ctr].input[1] = 'd';
                 break;
        case 0:  set->grabs[ctr].input[1] = 'n';
                 break;
        }

      switch((int)(fmod(set->grabs[ctr].int2,10))) {
        case 1: set->grabs[ctr].input[0] = '4';
                break;
        case 2: set->grabs[ctr].input[0] = '5';
                break;
        case 3: set->grabs[ctr].input[0] = '6';
                break;
        case 4: set->grabs[ctr].input[0] = '1';
                break;
        case 5: set->grabs[ctr].input[0] = '2';
                break;
        case 6: set->grabs[ctr].input[0] = '3';
                break;
        }

      if(set->grabs[ctr].int1 == 255) {
        set->grabtotal = ctr;
        done = 1;
        }
//      getch();
      }
    }
  fclose(fp);
  }

void get_spr(fs_ptr set,char filename[25]) {
  FILE *fp;
  char trash[25];
  int ctr = 0;
  int garb;

  init_fs(set);
  if((fp = fopen(filename,"rb")) == NULL) {
    printf("Could not open file: %s\n",filename);
    return;
    }

  fscanf(fp,"%s",&trash);
  fscanf(fp,"%s",set->refilename);
  fscanf(fp,"%s",set->images[ctr].filename);

  while(strcmp((char *)set->images[ctr].filename,"_the_end")) {
    fscanf(fp,"%d%d%d",&set->images[ctr].memsize,&set->images[ctr].width,&set->images[ctr].height);
//    printf("%s %d %d %d\n",set->images[ctr].filename,set->images[ctr].memsize,set->images[ctr].width,set->images[ctr].height);
    ++ctr;
    fscanf(fp,"%s",&set->images[ctr].filename);
    }

  set->lastimage = ctr;
//  printf("Total IDE Frames: %d\n",set->lastimage);
  //getch();
  ctr = 0;

  fscanf(fp,"%s",&trash);
  fscanf(fp,"%s",&trash);
  while(strcmp((char *)trash,"_the_end")) {
    fscanf(fp,"%d%d%d%d",&set->sprites[ctr].imag_num,&set->sprites[ctr].x_off,&set->sprites[ctr].y_off,&garb);
    set->sprites[ctr].last_image = 0;
    if(garb!=-1) {
      set->sprites[ctr].imag_num[1] = garb;
      fscanf(fp,"%d%d%d",&set->sprites[ctr].x_off[1],&set->sprites[ctr].y_off[1],&garb);
      set->sprites[ctr].last_image = 1;
      }
//    printf("%s %d %d %d\n",trash,set->sprites[ctr].imag_num,set->sprites[ctr].x_off,set->sprites[ctr].y_off,garb);
    ++ctr;
    fscanf(fp,"%s",&trash);
    }

  set->lastsprite = ctr - 1;
//  printf("Total Sprites: %d\n",set->lastsprite);
  //getch();

  fscanf(fp,"%s",trash);
  for(ctr=0;ctr<=set->lastsprite;ctr++) {
    fscanf(fp,"%d%d%d%d",&set->sprites[ctr].op[0],&set->sprites[ctr].op[1],&set->sprites[ctr].op[2],&set->sprites[ctr].op[3]);
//    printf("Collision #%d\n",ctr);
//    printf("%d %d %d %d\n",set->sprites[ctr].op[0],set->sprites[ctr].op[1],set->sprites[ctr].op[2],set->sprites[ctr].op[3]);
    }

  for(ctr=0;ctr<=set->lastsprite;ctr++) {
    fscanf(fp,"%d%d%d%d",&set->sprites[ctr].dp[0],&set->sprites[ctr].dp[1],&set->sprites[ctr].dp[2],&set->sprites[ctr].dp[3]);
    }

  fclose(fp);
  }

int get_cmd(ks_ptr set,char filename[25]) {
  FILE *fp;
  int ctr;
  int done = 0;
  char trash[25];
  int cnt;

  init_ks(set);
  if((fp = fopen(filename,"rt")) == NULL) {
    printf("Unable to open the file : %s\n",filename);
    return 0;
    }

  fscanf(fp,"%s",&set->name);
  fscanf(fp,"%d",&set->range);
  fscanf(fp,"%s",&trash);

  if(!strcmp(trash,"=sound=")) {
    for(ctr=0;ctr<30;ctr++)
    {
      if(!done)
      {
        fscanf(fp,"%s",&set->sounds[ctr]);
       // printf("%s\n",&set->sounds[ctr]);
        if(!strcmp(set->sounds[ctr],"end"))
        {
          done = 1;
        }
      }
    }
    done = 0;
    for(ctr=0;ctr<50;ctr++)
    {
      if(!done)
      {
        fscanf(fp,"%d %d %d",&set->fx[ctr].seq,&set->fx[ctr].framenum,&set->fx[ctr].which);
//        printf("%d %d %d\n",set->fx[ctr].seq,set->fx[ctr].framenum,set->fx[ctr].which);
        if(set->fx[ctr].seq == -1)
        {
          done = 1;
          set->lastsound = ctr;
        }
      }
    }
    fscanf(fp,"%s",&trash);
    }

  done = 0;
  //getch();

  if(!strcmp(trash,"=quote=")) {
    fscanf(fp,"%d",&set->lastquote);
    for(ctr=0;ctr<set->lastquote;ctr++) {
      fscanf(fp,"%s",&set->quotes[ctr]);
      }
    fscanf(fp,"%s",&trash);
    }

  done = 0;
  //getch();

  if(!strcmp(trash,"=special=")) {
    for(ctr=0;ctr<50;ctr++) {
      if(!done) {
        fscanf(fp,"%s %d %c %d",&set->attacks[ctr].input,&set->attacks[ctr].seq_num,&set->attacks[ctr].type,&set->attacks[ctr].mod);
//        printf("%s %d %c %d\n",set->attacks[ctr].input,set->attacks[ctr].seq_num,set->attacks[ctr].type,set->attacks[ctr].mod);

        if(set->attacks[ctr].type == 'M'|| set->attacks[ctr].type == 'm') {
          fscanf(fp,"%s %s %s",&set->attacks[ctr].ide,&set->attacks[ctr].seq,&set->attacks[ctr].cmd);
          }
        else if(set->attacks[ctr].type == 'C') {
          for(cnt=0;cnt<set->attacks[ctr].mod;cnt++) {
            fscanf(fp,"%d",&set->attacks[ctr].chains[cnt]);
           //printf("%d ",set->attacks[ctr].chains[cnt]);
            }
        //printf("\n");
          }
        set->attacks[ctr].total = strlen(set->attacks[ctr].input);
        if(set->attacks[ctr].seq_num == -1) {
          set->total = ctr;
          done = 1;
          }
        }
      }
    fscanf(fp,"%s",&trash);
    }

  done = 0;
  //getch();

  if(!strcmp(trash,"=cspecial=")) {
    for(ctr=0;ctr<50;ctr++) {
      if(!done) {
        fscanf(fp,"%s %d %c %d",&set->cspecials[ctr].input,&set->cspecials[ctr].seq_num,&set->cspecials[ctr].type,&set->cspecials[ctr].mod);
//        printf("%s %d %c %d\n",set->cspecials[ctr].input,set->cspecials[ctr].seq_num,set->cspecials[ctr].type,set->cspecials[ctr].mod);
        if(set->cspecials[ctr].type == 'C') {
          for(cnt=0;cnt<set->cspecials[ctr].mod;cnt++) {
            fscanf(fp,"%d",&set->cspecials[ctr].chains[cnt]);
           // printf("%d ",set->cspecials[ctr].chains[cnt]);
            }
          //printf("\n");
          }
        set->cspecials[ctr].total = strlen(set->cspecials[ctr].input);
        if(set->cspecials[ctr].seq_num == -1) {
          done = 1;
          }
        }
      }
    fscanf(fp,"%s",&trash);
    }

  done = 0;
  //getch();


  if(!strcmp(trash,"=super=")) {
    for(ctr=0;ctr<50;ctr++) {
      if(!done) {
//        fscanf(fp,"%s %d %c %d",&set->supers[ctr].input,&set->supers[ctr].seq_num,&set->supers[ctr].type,&set->supers[ctr].cost);
        fscanf(fp,"%s",&set->supers[ctr].input);
        if(set->supers[ctr].input[0] == '|')
        {
          set->supers[ctr-1].name = set->supers[ctr].input;
          fscanf(fp,"%s",&set->supers[ctr].input);
        }
        fscanf(fp,"%d %c %d",&set->supers[ctr].seq_num,&set->supers[ctr].type,&set->supers[ctr].cost);
//        printf("%s %d %c %d\n",set->supers[ctr].input,set->supers[ctr].seq_num,set->supers[ctr].type,set->supers[ctr].cost);
        if(set->supers[ctr].type == 'M' || set->supers[ctr].type == 'm') {
          fscanf(fp,"%s %s %s",&set->supers[ctr].ide,&set->supers[ctr].seq,&set->supers[ctr].cmd);
          }

        set->supers[ctr].total = strlen(set->supers[ctr].input);
        if(set->supers[ctr].seq_num == -1) {
          set->suptotal = ctr;
          if(set->suptotal < 0) set->suptotal = 0;
          done = 1;
          }
        }
      }
    fscanf(fp,"%s",&trash);
    }

  done = 0;

  if(!strcmp(trash,"=desperation=")) {
    for(ctr=0;ctr<50;ctr++) {
      if(!done) {
        fscanf(fp,"%s %d %c %d",&set->desperations[ctr].input,&set->desperations[ctr].seq_num,&set->desperations[ctr].type,&set->desperations[ctr].life);
        set->desperations[ctr].cost = 0;
        if(set->desperations[ctr].type == 'S') fscanf(fp,"%d",&set->desperations[ctr].cost);

        if(set->desperations[ctr].type == 'M') {
          fscanf(fp,"%s %s %s",&set->desperations[ctr].ide,&set->desperations[ctr].seq,&set->desperations[ctr].cmd);
          }

        set->desperations[ctr].total = strlen(set->desperations[ctr].input);
        if(set->supers[ctr].seq_num == -1) {
          set->lastdesperation = ctr;
          if(set->lastdesperation < 0) set->lastdesperation = 0;
          done = 1;
          }
        }
      }
    fscanf(fp,"%s",&trash);
    }

  done = 0;


  ctr =0;
  //getch();

  fscanf(fp,"%d %d %d %d %s",&set->grabs[ctr].int2,
                                        &set->grabs[ctr].action,
                                        &set->grabs[ctr].reaction,
                                        &set->grabs[ctr].direction,
                                        &set->grabs[ctr].vocfile);

  set->grabs[ctr].type = 1;
  set->grabs[ctr].damage = 1;
  set->grabs[ctr].type = trash[0];
  set->grabs[ctr].damage = trash[1];

  switch((set->grabs[ctr].int2/10)) {
        case 7:
        case 8:
        case 6:  set->grabs[ctr].input[1] = 'b';
                 break;
        case 4:
        case 3:
        case 5:  set->grabs[ctr].input[1] = 'f';
                 break;
        case 1:  set->grabs[ctr].input[1] = 'u';
                 break;
        case 2:  set->grabs[ctr].input[1] = 'd';
                 break;
        case 0:  set->grabs[ctr].input[1] = 'n';
                 break;
        }

      switch((int)(fmod(set->grabs[ctr].int2,10))) {
        case 1: set->grabs[ctr].input[0] = '4';
                break;
        case 2: set->grabs[ctr].input[0] = '5';
                break;
        case 3: set->grabs[ctr].input[0] = '6';
                break;
        case 4: set->grabs[ctr].input[0] = '1';
                break;
        case 5: set->grabs[ctr].input[0] = '2';
                break;
        case 6: set->grabs[ctr].input[0] = '3';
                break;
        }

//      printf("%d\n",(int)(fmod(set->grabs[ctr].int2,10)));
//      printf("%c\n",set->grabs[ctr].input[1]);

      if(!strcmp(trash,"255")) {
        set->grabtotal = ctr;
        done = 1;
        }


  for(ctr=1;ctr<50;ctr++) {
    if(!done) {
      fscanf(fp,"%d %d %d %d %d %s",&set->grabs[ctr].int1,
                                        &set->grabs[ctr].int2,
                                        &set->grabs[ctr].action,
                                        &set->grabs[ctr].reaction,
                                        &set->grabs[ctr].direction,
                                        &set->grabs[ctr].vocfile);
//      fscanf(fp,"%s",&set->grabs[ctr].vocfile);
/*      printf("%d %d %d %d %d\n",set->grabs[ctr].int1,
                                        set->grabs[ctr].int2,
                                        set->grabs[ctr].action,
                                        set->grabs[ctr].reaction,
                                        set->grabs[ctr].direction,
                                        set->grabs[ctr].vocfile);*/

      set->grabs[ctr].type = 1;
      set->grabs[ctr].damage = 1;

      switch((set->grabs[ctr].int1/10)) {
        case 1: set->grabs[ctr].damage = '1';
                break;
        case 2: set->grabs[ctr].damage = '2';
                break;
        case 3: set->grabs[ctr].damage = '3';
                break;
        case 4: set->grabs[ctr].damage = '4';
                break;
        case 5: set->grabs[ctr].damage = '5';
                break;
        case 6: set->grabs[ctr].damage = '6';
                break;
        }

      switch((int)(fmod(set->grabs[ctr].int1,10))) {
        case 0: set->grabs[ctr].type = '0';
                break;
        case 1: set->grabs[ctr].type = '1';
                break;
        case 2: set->grabs[ctr].type = '2';
                break;
        }

      switch((set->grabs[ctr].int2/10)) {
        case 7:
        case 8:
        case 6:  set->grabs[ctr].input[1] = 'b';
                 break;
        case 4:
        case 3:
        case 5:  set->grabs[ctr].input[1] = 'f';
                 break;
        case 1:  set->grabs[ctr].input[1] = 'u';
                 break;
        case 2:  set->grabs[ctr].input[1] = 'd';
                 break;
        case 0:  set->grabs[ctr].input[1] = 'n';
                 break;
        }

      switch((int)(fmod(set->grabs[ctr].int2,10))) {
        case 1: set->grabs[ctr].input[0] = '4';
                break;
        case 2: set->grabs[ctr].input[0] = '5';
                break;
        case 3: set->grabs[ctr].input[0] = '6';
                break;
        case 4: set->grabs[ctr].input[0] = '1';
                break;
        case 5: set->grabs[ctr].input[0] = '2';
                break;
        case 6: set->grabs[ctr].input[0] = '3';
                break;
        }

//      printf("%d\n",(int)(fmod(set->grabs[ctr].int2,10)));
//      printf("%c\n",set->grabs[ctr].input[1]);

      if(set->grabs[ctr].int1 == 255) {
        set->grabtotal = ctr;
        done = 1;
        }
//      getch();
      }
    }
  fclose(fp);
  }

void show_image(int h,int v,image i) {
  int b_cnt=0;
  int c_cnt=0;
  int cflag=0;
  int x=0;
  int y=0;
  int szcnt=0;
  int cnt=0;
  int t;

  while((szcnt<i.memsize) && (y<i.height)) {
    b_cnt = i.idata[cnt++];
    c_cnt = i.idata[cnt++];
    cflag = i.idata[cnt++];
    if(cflag) {
      c_cnt += 256;
      b_cnt = 1;
      }
    szcnt += (3+c_cnt);

    for(t=0;t<b_cnt;t++) {
      if(x>=i.width) {
        y++;
        x = 0;
        }
      x++;
      }
    for(t=0;t<c_cnt;t++) {
      if(x>=i.width) {
        y++;
        x = 0;
        }
      put_pixel(h+x,v+y,i.idata[cnt]);
      x++;
      cnt++;
      }
    }
  }

void show_sprite(int h,int v,sprite s,image i,int which) {
  int b_cnt=0;
  int c_cnt=0;
  int cflag=0;
  int x=0;
  int y=0;
  int szcnt=0;
  int cnt=0;
  int t;

  while((szcnt<i.memsize) && (y<i.height)) {
    b_cnt = i.idata[cnt++];
    c_cnt = i.idata[cnt++];
    cflag = i.idata[cnt++];
    if(cflag) {
      c_cnt += 256;
      b_cnt = 1;
      }
    szcnt += (3+c_cnt);

    for(t=0;t<b_cnt;t++) {
      if(x>=i.width) {
        y++;
        x = 0;
        }
      //put_pixel(h+x+xoffset,v+y+yoffset,0);
      x++;
      }
    for(t=0;t<c_cnt;t++) {
      if(x>=i.width) {
        y++;
        x = 0;
        }
      put_pixel(h+x+s.x_off[which],v+y+s.y_off[which],i.idata[cnt]);
      x++;
      cnt++;
      }
    }
  put_pixel(h,v,255);
  put_pixel(h+s.x_off[which]+s.op[0],v+s.y_off[which]+s.op[1],128);
  put_pixel(h+s.x_off[which]+s.op[0],v+s.y_off[which]+s.op[3],128);
  put_pixel(h+s.x_off[which]+s.op[2],v+s.y_off[which]+s.op[1],128);
  put_pixel(h+s.x_off[which]+s.op[2],v+s.y_off[which]+s.op[3],128);
  }

void show_seq(fs_ptr fset, ms_ptr mset, int which, int x, int y) {
  int ctr;
  int p[2];

  int proj = 0;
  int projp[2];
  int projseq = 0;
  int projctr = 0;

  p[0] = x;
  p[1] = y;
  if(mset->sequences[which].active) {
    for(ctr=0;ctr<=mset->sequences[which].used;ctr++) {
      clear_screen();
      p[0] += mset->frames[mset->sequences[which].moves[ctr]].xmov;
      p[1] += mset->frames[mset->sequences[which].moves[ctr]].ymov;
//      show_sprite(p[0],p[1],fset->sprites[mset->frames[mset->sequences[which].moves[ctr]].fram_num],fset->images[fset->sprites[mset->frames[mset->sequences[which].moves[ctr]].fram_num].imag_num[0]]);
      if(mset->frames[mset->sequences[which].moves[ctr]].type == 'F') {
        proj = 1;
        projseq = mset->sequences[which].moves[++ctr];
        projctr = 0;
        projp[0] = p[0];
        projp[1] = p[1];
        }

      if(proj) {
        projp[0] += mset->frames[mset->sequences[projseq].moves[projctr]].xmov;
        projp[1] += mset->frames[mset->sequences[projseq].moves[projctr]].ymov;
//        show_sprite(projp[0],projp[1],fset->sprites[mset->frames[mset->sequences[projseq].moves[projctr]].fram_num],fset->images[fset->sprites[mset->frames[mset->sequences[projseq].moves[projctr]].fram_num].imag_num[0]]);
        projctr++;
        if(projctr>=mset->sequences[projseq].used) {
          projctr = 0;
          proj = 0;
          projseq = 0;
          }
        }
      }
    }
  }






