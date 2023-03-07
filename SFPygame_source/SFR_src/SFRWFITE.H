#include "sfrwbase.h"

static ffnt fnt;
static ffnt bgfnt;
static ffnt hugefnt;
int speed;
int juggling;
int drama;
int sfxvolume;
int midvolume;
int centext;
int width;
int height;
int xoffset;
int yoffset;
int noleg;
int shadcnt;
int maxrounds;
int shadowdelay;
SAMPLE *systemsounds[30];
character_set cs;

//sound 0 = move option
//sound 1 = you win
//sound 2 = pause
//sound 3 = perfect
//sound 4 = select ding
//sound 5 = versus screen
//sound 6 = victory

int get_systemsounds(char *filename)
{
  FILE *fp;
  char trash[25];
  if((fp = fopen(filename,"rb")) == NULL) return FALSE;
  for(int ctr=0;ctr<6;ctr++)
  {
    fscanf(fp,"%s",&trash);
    systemsounds[ctr] = load_sample(trash);
  }
  fclose(fp);

  return TRUE;
}

//play_sample(systemsounds[0],sfxvolume,125,1000,0);

#define STAND 0
#define JUMP  1
#define DUCK  2
#define LEAP  3
#define SJUMP 4
#define RECOIL 5

unsigned char coltemp;
unsigned char reds[4];
unsigned char blues[4];

void draw_warrior(int h,int v,sprite s,image i,char flip,int which,int copy,char element)
{
  int b_cnt=0;
  int c_cnt=0;
  int cflag=0;
  int x=0;
  int y=0;
  int szcnt=0;
  int cnt=0;
  int t;
  char blit;

  coltemp = reds[0];
  reds[0] = reds[1];
  reds[1] = reds[2];
  reds[2] = reds[3];
  reds[3] = coltemp;

  x = 0;
  if(flip == 'v' || flip == 'b')
  {
    y = i.height;
    while((szcnt<i.memsize) && (y>0))
    {
      b_cnt = i.idata[cnt++];
      c_cnt = i.idata[cnt++];
      cflag = i.idata[cnt++];
      if(cflag)
      {
        c_cnt += 256;
        b_cnt = 1;
      }
      szcnt += (3+c_cnt);

      for(t=0;t<b_cnt;t++)
      {
        if(flip == 'b')
        {
          if(x<=(-1*i.width))
          {
            y--;
            x = 0;
          }
          x--;
        }
        else
        {
          if(x>=i.width)
          {
            y--;
            x = 0;
          }
          x++;
        }
      }
      for(t=0;t<c_cnt;t++)
      {
        if(i.idata[cnt] <= 63)
        {
          blit = reds[0];
        }
        else if(i.idata[cnt] <= 127)
        {
          blit = reds[1];
        }
        else if(i.idata[cnt] <= 191)
        {
          blit = reds[2];
        }
        else if(i.idata[cnt] <= 255)
        {
          blit = reds[3];
        }

        if(flip == 'b')
        {
          if(x<=(-1*i.width))
          {
            y--;
            x = 0;
          }
          if(!copy) put_pixel_b(h+x-s.x_off[which],v+y+s.y_off[which],i.idata[cnt]);
          else put_pixel_b(h+x-s.x_off[which],v+y+s.y_off[which],255-i.idata[cnt]);
          x--;
          cnt++;
        }
        else
        {
          if(x>=i.width)
          {
            y--;
            x = 0;
          }
          if(!copy) put_pixel_b(h+x+s.x_off[which],v+y+s.y_off[which],i.idata[cnt]);
          else put_pixel_b(h+x+s.x_off[which],v+y+s.y_off[which],255-i.idata[cnt]);
          x++;
          cnt++;
        }
      }
    }
  }
  else
  {
    y = 0;
    while((szcnt<i.memsize) && (y<i.height))
    {
      b_cnt = i.idata[cnt++];
      c_cnt = i.idata[cnt++];
      cflag = i.idata[cnt++];
      if(cflag)
      {
        c_cnt += 256;
        b_cnt = 1;
      }
      szcnt += (3+c_cnt);

      for(t=0;t<b_cnt;t++)
      {
        if(flip == 'h')
        {
          if(x<=(-1*i.width))
          {
            y++;
            x = 0;
          }
          x--;
        }
        else
        {
          if(x>=i.width)
          {
            y++;
            x = 0;
          }
          x++;
        }
      }
      for(t=0;t<c_cnt;t++)
      {
        if(i.idata[cnt] <= 63)
        {
          blit = reds[0];
        }
        else if(i.idata[cnt] <= 127)
        {
          blit = reds[1];
        }
        else if(i.idata[cnt] <= 191)
        {
          blit = reds[2];
        }
        else if(i.idata[cnt] <= 255)
        {
          blit = reds[3];
        }

        if(flip == 'h')
        {
          if(x<=(-1*i.width))
          {
            y++;
            x = 0;
          }
          if(!copy) put_pixel_b(h+x-s.x_off[which],v+y+s.y_off[which],i.idata[cnt]);
          else put_pixel_b(h+x-s.x_off[which],v+y+s.y_off[which],255-i.idata[cnt]);
          x--;
          cnt++;
        }
        else
        {
          if(x>=i.width)
          {
            y++;
            x = 0;
          }
          if(!copy) put_pixel_b(h+x+s.x_off[which],v+y+s.y_off[which],i.idata[cnt]);
          else put_pixel_b(h+x+s.x_off[which],v+y+s.y_off[which],255-i.idata[cnt]);
          x++;
          cnt++;
        }
      }
    }
  }
}

void draw_shadow(int h,int v,sprite s,image i,char flip,int color,int cycle)
{
  int b_cnt=0;
  int c_cnt=0;
  int cflag=0;
  int x=0;
  int y=0;
  int szcnt=0;
  int cnt=0;
  int t;
  char blit;
  int shade;
  if(color>3) shade = color + 16;
  else shade = color;


  x = 0;
  if(flip == 'v' || flip == 'b')
  {
    y = i.height;
    while((szcnt<i.memsize) && (y>0))
    {
      b_cnt = i.idata[cnt++];
      c_cnt = i.idata[cnt++];
      cflag = i.idata[cnt++];
      if(cflag)
      {
        c_cnt += 256;
        b_cnt = 1;
      }
      szcnt += (3+c_cnt);

      for(t=0;t<b_cnt;t++)
      {
        if(flip == 'b')
        {
          if(x<=(-1*i.width))
          {
            y--;
            x = 0;
          }
          x--;
        }
        else
        {
          if(x>=i.width)
          {
            y--;
            x = 0;
          }
          x++;
        }
      }
      for(t=0;t<c_cnt;t++)
      {
        if(i.idata[cnt] <= 31) blit = 1;
        else if(i.idata[cnt] <= 63) blit = 32;
        else if(i.idata[cnt] <= 95) blit = 64;
        else if(i.idata[cnt] <= 127) blit = 96;
        else if(i.idata[cnt] <= 159) blit = 128;
        else if(i.idata[cnt] <= 191) blit = 160;
        else if(i.idata[cnt] <= 223) blit = 192;
        else if(i.idata[cnt] <= 255) blit = 224;

        {
          blit = 96;
        }


        if(flip == 'b')
        {
          if(x<=(-1*i.width))
          {
            y--;
            x = 0;
          }
          put_pixel_b(h+x-s.x_off[0],v+y+s.y_off[0],blit + shade + (cycle * 4));
          x--;
          cnt++;
        }
        else
        {
          if(x>=i.width)
          {
            y--;
            x = 0;
          }
          put_pixel_b(h+x+s.x_off[0],v+y+s.y_off[0],blit + shade + (cycle * 4));
          x++;
          cnt++;
        }
      }
    }
  }
  else
  {
    y = 0;
    while((szcnt<i.memsize) && (y<i.height))
    {
      b_cnt = i.idata[cnt++];
      c_cnt = i.idata[cnt++];
      cflag = i.idata[cnt++];
      if(cflag)
      {
        c_cnt += 256;
        b_cnt = 1;
      }
      szcnt += (3+c_cnt);

      for(t=0;t<b_cnt;t++)
      {
        if(flip == 'h')
        {
          if(x<=(-1*i.width))
          {
            y++;
            x = 0;
          }
          x--;
        }
        else
        {
          if(x>=i.width)
          {
            y++;
            x = 0;
          }
          x++;
        }
      }
      for(t=0;t<c_cnt;t++)
      {
        if(i.idata[cnt] <= 31) blit = 1;
        else if(i.idata[cnt] <= 63) blit = 32;
        else if(i.idata[cnt] <= 95) blit = 64;
        else if(i.idata[cnt] <= 127) blit = 96;
        else if(i.idata[cnt] <= 159) blit = 128;
        else if(i.idata[cnt] <= 191) blit = 160;
        else if(i.idata[cnt] <= 223) blit = 192;
        else if(i.idata[cnt] <= 255) blit = 224;

        if(flip == 'h')
        {
          if(x<=(-1*i.width))
          {
            y++;
            x = 0;
          }
          put_pixel_b(h+x-s.x_off[0],v+y+s.y_off[0],blit + shade + (cycle * 4));
          x--;
          cnt++;
        }
        else
        {
          if(x>=i.width)
          {
            y++;
            x = 0;
          }
          put_pixel_b(h+x+s.x_off[0],v+y+s.y_off[0],blit + shade + (cycle * 4));
          x++;
          cnt++;
        }
      }
    }
  }
}

class interface
{
  public:
  int time;
  int ctr;
  int ctr2;
  float p1life;
  float p2life;
  int p1super;
  int p2super;
  int p1stun;
  int p2stun;
  int rad;
  int cycle;
  int rumble;
  int p1rumble;
  int p2rumble;


  interface()
  {
    time = 0;
    p1life = 0.0;
    p2life = 0.0;
    p1super = 120;
    p2super = 200;
    p1stun = 0;
    p2stun = 0;
    cycle = 0;
    rumble = 0;
    p1rumble = 0;
    p2rumble = 0;
  }

  //~interface();

  void main_update(info p1, info p2)
  {
    cycle++;
    if(cycle>3) cycle = 0;

    char blit;
    if(p1.life > p1life) p1life = p1.life;
    else if(p1.life < p1life) p1life -= 0.50;

    if(p2.life > p2life) p2life = p2.life;
    else if(p2.life < p2life) p2life -= 0.50;


    for(ctr=(int)(p1life*1.3*-1);ctr<0;ctr++)
    {
      for(ctr2=0;ctr2<8;ctr2++)
      {
        if(p1life > p1.life) put_pixel_b(ctr+130+xoffset,yoffset+ctr2,128 + (cycle * 32));
      }
    }

    for(ctr=(int)(p1.life*1.3*-1);ctr<0;ctr++)
    {
      if(p1.life <= 20) blit = 236; //28;
      else if(p1.life <= 30) blit = 252; //60;
      else if(p1.life <= 40) blit = 220; //92;
      else if(p1.life <= 50) blit = 188; //124;
      else if(p1.life <= 60) blit = 156;
      else if(p1.life <= 70) blit = 124;
      else if(p1.life <= 80) blit = 92;
      else if(p1.life <= 90) blit = 60;
      else if(p1.life <= 100) blit = 28;

//      blit = ctr * 2.55;
      for(ctr2=0;ctr2<8;ctr2++)
      {
        put_pixel_b(ctr+130+xoffset,yoffset+ctr2,blit - (cycle * 4));
      }
    }

    for(ctr=(int)(p2life*1.3)+190;ctr>190;ctr--)
    {
      for(ctr2=0;ctr2<8;ctr2++)
      {
        if(p2life > p2.life) put_pixel_b(ctr+xoffset,yoffset+ctr2,128 + (cycle * 32));
      }
    }

    for(ctr=(int)(p2.life*1.3)+190;ctr>190;ctr--)
    {
      if(p2.life <= 20) blit = 236; //28;
      else if(p2.life <= 30) blit = 252; //60;
      else if(p2.life <= 40) blit = 220; //92;
      else if(p2.life <= 50) blit = 188; //124;
      else if(p2.life <= 60) blit = 156;
      else if(p2.life <= 70) blit = 124;
      else if(p2.life <= 80) blit = 92;
      else if(p2.life <= 90) blit = 60;
      else if(p2.life <= 100) blit = 28;

      for(ctr2=0;ctr2<8;ctr2++)
      {
        put_pixel_b(ctr+xoffset,yoffset+ctr2,blit - (cycle * 4));
      }
    }

    p1super--;
    if(p1super < 120-p1.super) p1super = 120;
    p2super++;
    if(p2super > 200+p2.super) p2super = 200;

    draw_num(xoffset+122,yoffset+200-fnt.letheight,(font_ptr)&fnt,p1.super / 40,'l',1);

    for(ctr=120;ctr>120-p1.super;ctr--)
    {
      if(p1.super < 40) blit = 3;
      else if(p1.super < 80) blit = 4;
      else if(p1.super < 120) blit = 28;
      else blit = 31;

      if(ctr >= p1super)
      {
        for(ctr2=200;ctr2>195;ctr2--) put_pixel_b(ctr+xoffset,yoffset+ctr2,blit + ( ( (120 - p1super) / 8) * 32) );
      }
      else
      {
        for(ctr2=200;ctr2>195;ctr2--) put_pixel_b(ctr+xoffset,yoffset+ctr2,blit);
      }
    }

    draw_num(xoffset+198,yoffset+200-fnt.letheight,(font_ptr)&fnt,p2.super / 40,'r',1);

    for(ctr=p2.super+200;ctr>200;ctr--)
    {
      if(p2.super < 40) blit = 3;
      else if(p2.super < 80) blit = 4;
      else if(p2.super < 120) blit = 28;
      else blit = 31;

      if(ctr <= p2super)
      {
        for(ctr2=200;ctr2>195;ctr2--) put_pixel_b(ctr+xoffset,yoffset+ctr2,blit + ( ( (p2super - 200) / 8) * 32) );
      }
      else
      {
        for(ctr2=200;ctr2>195;ctr2--) put_pixel_b(ctr+xoffset,yoffset+ctr2,blit);
      }
    }

    if(rumble)
    {
      rumble = 0;
      if(p1life > p1.life)
      {
        p1rumble = (p1life - p1.life) * -1;
        if(p1rumble < -10) p1rumble = -10;
      }
      else p1rumble = 0;
      if(p2life > p2.life)
      {
        p2rumble = (p2life - p2.life) * -1;
        if(p2rumble < -10) p2rumble = -10;
      }
      else p2rumble = 0;
    }
    else
    {
      rumble = 1;
      if(p1life > p1.life)
      {
        p1rumble = (p1life - p1.life);
        if(p1rumble > 10) p1rumble = 10;
      }
      else p1rumble = 0;
      if(p2life > p2.life)
      {
        p2rumble = (p2life - p2.life);
        if(p2rumble > 10) p2rumble = 10;
      }
      else p2rumble = 0;
    }

    draw_string(p1.smallpict.width+xoffset,yoffset+10,(font_ptr)&fnt,p1.name,'l',1);

    if(p2.combo>1)
    {
      draw_num(0+xoffset,yoffset+10+p1.smallpict.height,(font_ptr)&fnt,p2.combo,'l',1);
      draw_string(20+xoffset,yoffset+10+p1.smallpict.height,(font_ptr)&fnt,"HITS",'l',1);
    }

    if(p1.alive) draw_portrait(0+xoffset,yoffset+10+p1rumble,(port_ptr)&p1.smallpict,0);


    draw_string(285+xoffset,yoffset+10,(font_ptr)&fnt,p2.name,'r',1);

    if(p1.combo>1)
    {
      draw_num(260+xoffset,yoffset+10+p2.smallpict.height,(font_ptr)&fnt,p1.combo,'r',1);
      draw_string(320+xoffset,yoffset+10+p2.smallpict.height,(font_ptr)&fnt,"HITS",'r',1);
    }

    if(p2.alive) draw_portrait(320-p2.smallpict.width+xoffset,yoffset+10+p2rumble,(port_ptr)&p2.smallpict,1);
  }

  void kof_update(info p1,info p2,info p3,info p4,info p5,info p6,int p1who,int p2who);
  void cap_update(info p1,info p2,info p3,info p4,info p5,info p6,int p1who,int p2who);

  void update(info p1,info p2)
  {
    main_update(p1,p2);
    if(rad<5) rad++;
    else rad = 0;

    for(ctr=0;ctr<p1.wins;ctr++)
    {
      circle_b(p1.smallpict.width+xoffset+10+(15*ctr),yoffset+30,255,rad);
    }

    for(ctr=0;ctr<p2.wins;ctr++)
    {
      circle_b(320-p2.smallpict.width+xoffset-10-(20*ctr),yoffset+30,255,rad);
    }
  }
};

struct shadow {
  int x,y;
  frame shad;
  int sequence;
  char flip;
  int flicker;
  int color;
  int cycle;
  };

class warrior {
  public:
  int super_start;

  int curr_proj;
  int curr_special;
  int curr_cspecial;
  int curr_super;
  int shadowframe;
  int shadowseq;

  int air_seq;
  int air_frame;
  int air_done;
  int shade;
  int shadowed;

  int buffctr;
  int guarding;
  int lowguard;
  int blocking;
  int lowblock;
  int blockctr;
  int projctr;
  int frozen;
  int ground;
  int rising;
  int grav;
  int maxheight;
  int velo;
  int chainin;
  int close;
  int sfr;
  int grav2;
  int posing;
  int clone;
  int morphctr;
  int fire;
  int throwing;
  int side;

  char flip;

  char music[99];
  char bgname[25];
  int pstartctr;
  int walking;
  int dizzied;
  info_ptr opnt;
//  portrait bigpict;
  char name[25];
  char idname[25];
  char p[25];
  char i[25];
  char s[25];
  char k[25];
  char b[25];
  char bp[25];
  int type;
  int shadow_color;
  int shadow_cycle;

  //modeset mdset;

  info data;
  frameset fset;
  moveset mset;
  keyset kset;

  projectile proj[20];

  SAMPLE *samples[30];
  shadow shadows[99];

  int strt,up,dn,lf,rt,jb,st,fc,sh,fw,rh,p3,k3;

  void shadow_init()
  {
//    for(int ctr=0;ctr<99;ctr++)
//    {
      shadows[0].shad.fram_num = -1;
      shadows[0].sequence = -1;
      shadows[0].flicker = 0;
//    }
  }

  void shadow_handler()
  {
    for(int ctr=(shadcnt-1);ctr>0;ctr--)
    {
      shadows[ctr] = shadows[ctr-1];
    }
    if(shadowed)
    {
      if(data.status == JUMP || data.status == LEAP)
      {
        shadows[0].shad = mset.frames[mset.sequences[air_seq].moves[air_frame]];
        shadows[0].sequence = air_seq;
      }
      else
      {
        shadows[0].shad = mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]];
        shadows[0].sequence = data.curr_seq;
      }
      shadows[0].x = data.p[0];
      shadows[0].y = data.p[1];
      shadows[0].flip = flip;
      shadows[0].color = shadow_color;
      shadows[0].cycle = 0;
      if(shadows[1].flicker) shadows[0].flicker = 0;
      else if(!shadows[1].flicker) shadows[0].flicker = 1;
    }
  }

  void shadow_draw()
  {
    for(int ctr=shadcnt-1;ctr>=0;ctr--)
    {
      if(shadows[ctr].shad.fram_num != -1)
      {
        if(shadows[ctr].flicker >= shadowdelay)
        {
          draw_shadow(shadows[ctr].x,shadows[ctr].y,fset.sprites[shadows[ctr].shad.fram_num],fset.images[fset.sprites[shadows[ctr].shad.fram_num].imag_num[0]],shadows[ctr].flip,shadows[ctr].color,shadows[ctr].cycle);
          shadows[ctr].flicker = 0;
        }
        else shadows[ctr].flicker++;
      }
    }
  }


  void setup() {
    data.super = 0;
    data.wins = 0;
    data.curr_seq = 299;
    data.stun = 0;
    data.life = 100;
    morphctr = 101;
    }

  void get(char filename[25]) {

    char trash[20];
    FILE *fp;

    if((fp = fopen(filename,"rb")) == NULL) {
      exit(-1);
      printf("Could not find the file %s, aborting.\n",filename);
      }

    fscanf(fp,"%s", &name);
    strcpy(data.name,name);

    fscanf(fp,"%d", &type);

    if (type == 0) {
      fscanf(fp,"%s %s %s %s %s %s %s",&p,&bp,&i,&s,&k,&bgname,&music);
      get_ide((fs_ptr)&fset,i);
      get_key((ks_ptr)&kset,k);
      get_re((fs_ptr)&fset);
      get_seq((ms_ptr)&mset,s);
      get_portrait((port_ptr)&data.smallpict,p);
      sfr = type;
      fclose(fp);
      }
    else if (type == 1) {
      fscanf(fp,"%s %s %s %s %s %s %s",&p,&bp,&i,&s,&k,&bgname,&music);
      get_spr((fs_ptr)&fset,i);
      get_re((fs_ptr)&fset);
      get_cmd((ks_ptr)&kset,k);
      get_seq((ms_ptr)&mset,s);
      get_portrait((port_ptr)&data.smallpict,p);
      sfr = type;
      fclose(fp);
      }




/*    if (type == 2) {
      init_modes((modes_ptr)&mdset);
      fscanf(fp,"%s %s",&p,&bp);
      get_portrait((port_ptr)&data.smallpict,p);
      fscanf(fp,"%s%s",&bgname,&music);

      fscanf(fp, "%d", &mdset.total);

      if (mdset.total > 6) {
        exit(-1);
        printf("%s has too many modes... exiting game", &filename);
        }

      for (int i = 0; i < mdset.total; i++) {
        fscanf(fp,"%s", &trash);

        fscanf(fp,"%s%s%s",&mdset.modes[i].ide_file,
                           &mdset.modes[i].seq_file,
                           &mdset.modes[i].cmd_file);

        fscanf(fp,"%s", &mdset.modes[i].mode_name);
        fscanf(fp,"%s", &mdset.modes[i].super_subset);
        fscanf(fp,"%s", &mdset.modes[i].chaincombo);
        fscanf(fp,"%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",&mdset.modes[i].odamage,
                                                     &mdset.modes[i].ddamage,
                                                     &mdset.modes[i].super_rate,
                                                     &mdset.modes[i].air_block,
                                                     &mdset.modes[i].limb_control,
                                                     &mdset.modes[i].juggle,
                                                     &mdset.modes[i].air_recovery,
                                                     &mdset.modes[i].alpha_counter,
                                                     &mdset.modes[i].alpha_counter_seq,
                                                     &mdset.modes[i].fdash,
                                                     &mdset.modes[i].fdash_seq,
                                                     &mdset.modes[i].bdash,
                                                     &mdset.modes[i].bdash_seq,
                                                     &mdset.modes[i].oguard,
                                                     &mdset.modes[i].oguard_seq);
                                                     }
        sfr = type;
        fclose(fp);
        } // end type 2 checking
      }  // end get();*/
    }

  void get2(char id[25])
  {
    FILE *fp;
    char *trash;
    if((fp = fopen(id,"rb")) == NULL)
    {
      printf("%s\n",id);
      alert_error("Could not find this char");
    }
    fscanf(fp,"%s",&name);
    strcpy(data.name,name);
    fscanf(fp,"%d",&type);
    fscanf(fp,"%s %s %s %s %s %s %s",&p,&bp,&i,&s,&k,&bgname,&music);

    if(type)
    {
      get_spr((fs_ptr)&fset,i);
      get_cmd((ks_ptr)&kset,k);
      for(int ctr=0;ctr<30;ctr++)
      {
         samples[ctr] = load_sample(kset.sounds[ctr]);
      }

    }
    else
    {
      get_ide((fs_ptr)&fset,i);
      get_key((ks_ptr)&kset,k);
    }
    get_re((fs_ptr)&fset);
    get_seq((ms_ptr)&mset,s);
    get_portrait((port_ptr)&data.smallpict,p);
    sfr = type;
    //fscanf(fp,"%s",&trash);

    /*if(!strcmp(trash,"flags"))
    {
      fscanf(fp,"%s",&trash);
    } */

    fclose(fp);
  }

  void import_controls(char filename[25]) {
    FILE *fp;
    if((fp = fopen(filename,"rb")) == NULL)
    {
      printf("unable to open key config file %s, go to options!",filename);
      delay(2000);
      exit(-1);
    }
    fscanf(fp,"%d %d %d %d %d %d %d %d %d %d %d %d %d",
              &strt,&up,&dn,&lf,&rt,&jb,&st,&fc,&sh,&fw,&rh,&p3,&k3);
    fclose(fp);
    }


  ~warrior() {
    kill_frames((fs_ptr)&fset);
    kill_portrait((port_ptr)&data.smallpict);
    }

  void init(int who,int floor,int x,int copy) {
//    opnt = (info_ptr)&data;

//    opnt->p[0] = data.p[0];
//    opnt->p[1] = data.p[1];

    data.p[0] = x;
    data.p[1] = floor;
    ground = floor;
    data.second = who;
    data.curr_frame = -1;
    if(data.curr_seq != 299) data.curr_seq = 0;
    for(buffctr=0;buffctr<10;buffctr++)
    {
      data.ibuffer[buffctr] = 'n';
      data.cbuffer[buffctr] = 'n';
    }
    air_frame = 0;
    air_seq = 0;
    air_done = 0;
    data.status = STAND;
    for(projctr=0;projctr<20;projctr++) {
      proj[projctr].active = 0;
      data.pboxes[projctr].active = 0;
      }
    data.dbox.active = 0;
    data.obox.active = 0;
    curr_proj = 0;
    frozen = 0;
    rising = 0;
    data.falling = 0;
    velo = 0;
    curr_special = -1;
    curr_cspecial = -1;
    chainin = 0;
    close = 0;
    data.mid_seq = 0;

    data.alive = 1;
    super_start = 0;
    data.combo = 0;
    posing = 0;
    clone = copy;
    data.status = STAND;
    guarding = 0;
    fire = 0;
    blocking = 0;
    guarding = 0;
    data.frost = 0;
    walking = 0;
    shadow_init();
    data.tagattack = 0;
    data.tagsuper = 0;
    }

  void input_handler() {
    data.ibuffer[0] = 'n';

    if(keys_active) {
      if(key_table[up]) {
        data.ibuffer[0] = 'u';
        }
      if(key_table[dn]) {
        data.ibuffer[0] = 'd';
        }
      if(data.second)
      {
        if(key_table[rt]) {
          data.ibuffer[0] = 'b';
          if(key_table[up]) data.ibuffer[0] = 'L';
          if(key_table[dn]) data.ibuffer[0] = 'S';
          }
        if(key_table[lf])
        {
          data.ibuffer[0] = 'f';
          if(key_table[up]) data.ibuffer[0] = 'l';
          if(key_table[dn]) data.ibuffer[0] = 's';
        }
      }
      else {
        if(key_table[rt])
        {
          data.ibuffer[0] = 'f';
          if(key_table[up]) data.ibuffer[0] = 'l';
          if(key_table[dn]) data.ibuffer[0] = 's';
        }
        if(key_table[lf]) {
          data.ibuffer[0] = 'b';
          if(key_table[up]) data.ibuffer[0] = 'L';
          if(key_table[dn]) data.ibuffer[0] = 'S';
          }
        }
      if(key_table[jb]) {
        data.ibuffer[0] = '1';
//        if(data.ibuffer[1] == 'f' && data.ibuffer[2] == 'f') data.ibuffer[0] = '&';
        if(key_table[dn]) data.ibuffer[0] = '!';
        if(key_table[sh]) data.ibuffer[0] = 'w';
        if(key_table[st] || key_table[fc]) data.ibuffer[0] = 'p';

        }
      if(key_table[st]) {
        data.ibuffer[0] = '2';
//        if(data.ibuffer[1] == 'f' && data.ibuffer[2] == 'f') data.ibuffer[0] = '*';
        if(key_table[dn]) data.ibuffer[0] = '@';
        if(key_table[fw]) data.ibuffer[0] = 'm';
        if(key_table[fc] || key_table[jb]) data.ibuffer[0] = 'p';
        }
      if(key_table[fc]) {
        data.ibuffer[0] = '3';
//        if(data.ibuffer[1] == 'f' && data.ibuffer[2] == 'f') data.ibuffer[0] = '(';
        if(key_table[dn]) data.ibuffer[0] = '#';
        if(key_table[rh]) data.ibuffer[0] = 'h';
        if(key_table[st] || key_table[jb]) data.ibuffer[0] = 'p';
        }
      if(key_table[sh]) {
        data.ibuffer[0] = '4';
//        if(data.ibuffer[1] == 'f' && data.ibuffer[2] == 'f') data.ibuffer[0] = ')';
        if(key_table[dn]) data.ibuffer[0] = '$';
        if(key_table[jb]) data.ibuffer[0] = 'w';
        if(key_table[fw] || key_table[rh]) data.ibuffer[0] = 'k';
        }
      if(key_table[fw]) {
        data.ibuffer[0] = '5';
//        if(data.ibuffer[1] == 'f' && data.ibuffer[2] == 'f') data.ibuffer[0] = '_';
        if(key_table[dn]) data.ibuffer[0] = '%';
        if(key_table[st]) data.ibuffer[0] = 'm';
        if(key_table[sh] || key_table[rh]) data.ibuffer[0] = 'k';
        }
      if(key_table[rh]) {
        data.ibuffer[0] = '6';
//        if(data.ibuffer[1] == 'f' && data.ibuffer[2] == 'f') data.ibuffer[0] = '+';
        if(key_table[dn]) data.ibuffer[0] = '^';
        if(key_table[fc]) data.ibuffer[0] = 'h';
        if(key_table[sh] || key_table[fw]) data.ibuffer[0] = 'k';
        }
      }
    }

  void convert_input() {
    guarding = 0;
    lowguard = 0;
    data.cbuffer[0] = data.ibuffer[0];
    switch(data.cbuffer[0]) {
      case 'b': guarding = 1;
                break;
      case 'S': lowguard = 1;
                break;

      }
    }

  void ai_movement_handler();

  void movement_handler() {
    switch(data.cbuffer[0]) {
      case 'F':
      case 'f':  if(data.cbuffer[1] != 'f' || data.curr_seq != 6) {
                   data.curr_seq = 6;
                   data.curr_frame = -1;
                   data.status = STAND;
                   }
                 break;
      case 'B':
      case 'b':  if(data.cbuffer[1] != 'b' || data.curr_seq != 3) {
                   data.curr_seq = 3;
                   data.curr_frame = -1;
                   data.status = STAND;
                   }
                 break;
      case 'D':
      case 'd':  data.curr_seq = 2;
                 data.curr_frame = -1;
                 data.status = DUCK;
                 break;
      case 'U':
      case 'u':  data.curr_seq = 1;
                 air_seq = 1;
                 data.curr_frame = -1;
                 air_frame = -1;
                 data.status = JUMP;
                 break;
      case 'n':  data.curr_seq = 0;
                 if(data.cbuffer[1] != 'n') {
                   data.curr_frame = -1;
                   data.status = STAND;
                   }
                 data.status = STAND;
                 break;
      case 'l':  data.curr_seq = 7;
                 air_seq = 7;
                 data.curr_frame = -1;
                 air_frame = -1;
                 data.status = LEAP;
                 break;
      case 'L':  data.curr_seq = 4;
                 air_seq = 4;
                 data.curr_frame = -1;
                 air_frame = -1;
                 data.status = LEAP;
                 break;
      case 's':  data.curr_seq = 8;
                 data.curr_frame = -1;
                 data.status = DUCK;
                 break;
      case 'S':  data.curr_seq = 5;
                 data.curr_frame = -1;
                 data.status = DUCK;
                 break;
      }
    }

  void ai_attack_handler(int offset);

  void attack_handler(int offset) {
    switch(data.ibuffer[0]) {
      case '&':
      case '1':  if(close) data.curr_seq = 20;
                 else data.curr_seq = 14;
                 data.curr_frame = -1;
                 break;
      case '!':  data.curr_seq = 38;
                 data.curr_frame = -1;
                 break;
      case '*':
      case '2':  if(close) data.curr_seq = 21;
                 else data.curr_seq = 15;
                 data.curr_frame = -1;
                 data.super+=2;
                 break;
      case '@':  data.curr_seq = 39;
                 data.curr_frame = -1;
                 data.super+=2;
                 break;
      case '(':
      case '3':  if(close) data.curr_seq = 22;
                 else data.curr_seq = 16;
                 data.curr_frame = -1;
                 data.super+=3;
                 break;
      case '#':  data.curr_seq = 40;
                 data.curr_frame = -1;
                 data.super+=3;
                 break;
      case ')':
      case '4':  if(close) data.curr_seq = 17;
                 else data.curr_seq = 11;
                 data.curr_frame = -1;
                 break;
      case '$':  data.curr_seq = 35;
                 data.curr_frame = -1;
                 break;
      case '_':
      case '5':  if(close) data.curr_seq = 18;
                 else data.curr_seq = 12;
                 data.curr_frame = -1;
                 data.super+=2;
                 break;
      case '%':  data.curr_seq = 36;
                 data.curr_frame = -1;
                 data.super+=2;
                 break;
      case '+':
      case '6':  if(close) data.curr_seq = 19;
                 else data.curr_seq = 13;
                 data.curr_frame = -1;
                 data.super+=3;
                 break;
      case '^':  data.curr_seq = 37;
                 data.curr_frame = -1;
                 data.super+=3;
                 break;
      }
    }

  int ai_special_handler();

  void special_handler() {
    int ctr;
    int ctr2;
    int done = 0;
    for(ctr=0;ctr<kset.total;ctr++) {
      if(!done) {
        if(kset.attacks[ctr].input[0] == data.ibuffer[0] || kset.attacks[ctr].input[0] == data.cbuffer[0]) {
          buffctr = 0;
          ctr2 = 0;
          while(buffctr < 10) {
            if(data.ibuffer[buffctr] == kset.attacks[ctr].input[ctr2] || data.cbuffer[buffctr] == kset.attacks[ctr].input[ctr2]) {
              ctr2++;
              if(ctr2 == kset.attacks[ctr].total) {
                if(curr_super == -1) {
                  if(kset.attacks[ctr].type != 'A') {
                    data.curr_seq = kset.attacks[ctr].seq_num;
                    data.curr_frame = -1;
                    curr_special = ctr;
                    data.curr_grab = kset.grabs[kset.grabtotal+1];
                    if(kset.attacks[ctr].type == 'm') {
                      kill_frames((fs_ptr)&fset);
                      get_ide((fs_ptr)&fset,kset.attacks[ctr].ide);
                      get_re((fs_ptr)&fset);
                      get_seq((ms_ptr)&mset,kset.attacks[ctr].seq);
                      get_cmd((ks_ptr)&kset,kset.attacks[ctr].cmd);
                      for(int cnt=0;cnt<30;cnt++) {
                        samples[cnt] = load_sample(kset.sounds[cnt]);
                        }
                      morphctr = 0;
                      }
                    else if(kset.attacks[ctr].type == 'M') {
                      kill_frames((fs_ptr)&fset);
                      get_ide((fs_ptr)&fset,kset.attacks[ctr].ide);
                      get_re((fs_ptr)&fset);
                      get_seq((ms_ptr)&mset,kset.attacks[ctr].seq);
                      get_cmd((ks_ptr)&kset,kset.attacks[ctr].cmd);
                      for(int cnt=0;cnt<30;cnt++) {
                        samples[cnt] = load_sample(kset.sounds[cnt]);
                        }
                      morphctr = 101;
                      }
                    else if(kset.attacks[ctr].type == 'S') shade = 1;
                    for(buffctr=0;buffctr<10;buffctr++) {
                      data.ibuffer[buffctr] = 'n';
                      data.cbuffer[buffctr] = 'n';
                      }
                    buffctr = 10;
                    done = 1;
                    data.super += 5;

                    }
                  }
                }
              }
            buffctr++;
            }
          }
        }
      }
    }

  void cspecial_handler() {
    int ctr;
    int ctr2;
    int done = 0;
    if(curr_cspecial == -1) {
      for(ctr=0;ctr<kset.attacks[curr_special].mod;ctr++) {
        if(!done) {
          if(kset.cspecials[kset.attacks[curr_special].chains[ctr]].input[0] == data.ibuffer[0]  || kset.cspecials[kset.attacks[curr_special].chains[ctr]].input[0] == data.cbuffer[0]) {
            buffctr = 0;
            ctr2 = 0;
            while(buffctr < 10) {
              if(data.ibuffer[buffctr] == kset.cspecials[kset.attacks[curr_special].chains[ctr]].input[ctr2] || data.cbuffer[buffctr] == kset.cspecials[kset.attacks[curr_special].chains[ctr]].input[ctr2]) {
                ctr2++;
                if(ctr2 == kset.cspecials[kset.attacks[curr_special].chains[ctr]].total) {
                  if(kset.cspecials[kset.attacks[curr_special].chains[ctr]].type != 'A') {
                    data.curr_seq = kset.cspecials[kset.attacks[curr_special].chains[ctr]].seq_num;
                    data.curr_frame = -1;
                    curr_cspecial = ctr;
                    data.curr_grab = kset.grabs[kset.grabtotal+1];
                    for(buffctr=0;buffctr<10;buffctr++) {
                      data.ibuffer[buffctr] = 'n';
                      data.cbuffer[buffctr] = 'n';
                      }
                    buffctr = 10;
                    done = 1;
                    data.super+=5;
                    }
                  }
                }
              buffctr++;
              }
            }
          }
        }
      }
    else {
      for(ctr=0;ctr<kset.cspecials[curr_cspecial].mod;ctr++) {
        if(!done) {
          if(kset.cspecials[kset.cspecials[curr_cspecial].chains[ctr]].input[0] == data.ibuffer[0] || kset.cspecials[kset.cspecials[curr_cspecial].chains[ctr]].input[0] == data.cbuffer[0]) {
            buffctr = 0;
            ctr2 = 0;
            while(buffctr < 10) {
              if(data.ibuffer[buffctr] == kset.cspecials[kset.cspecials[curr_cspecial].chains[ctr]].input[ctr2] || data.cbuffer[buffctr] == kset.cspecials[kset.cspecials[curr_cspecial].chains[ctr]].input[ctr2]) {
                ctr2++;
                if(ctr2 == kset.cspecials[kset.cspecials[curr_cspecial].chains[ctr]].total) {
                  if(kset.cspecials[kset.cspecials[curr_cspecial].chains[ctr]].type != 'A') {
                    data.curr_seq = kset.cspecials[kset.cspecials[curr_cspecial].chains[ctr]].seq_num;
                    data.curr_frame = -1;
                    curr_special = -1;
                    curr_cspecial = -1;
                    data.curr_grab = kset.grabs[kset.grabtotal+1];
                    for(buffctr=0;buffctr<10;buffctr++) {
                      data.ibuffer[buffctr] = 'n';
                      data.cbuffer[buffctr] = 'n';
                      }
                    buffctr = 10;
                    done = 1;
                    data.super+=5;
                    }
                  }
                }
              buffctr++;
              }
            }
          }
        }
      }
    }

  int ai_super_handler();

  void super_handler() {
    int ctr;
    int ctr2;
    int done = 0;
    for(ctr=0;ctr<kset.suptotal;ctr++) {
      if(!done) {
        if(kset.supers[ctr].input[0] == data.ibuffer[0] || kset.supers[ctr].input[0] == data.cbuffer[0]) {
          buffctr = 0;
          ctr2 = 0;
          while(buffctr < 10) {
            if(data.ibuffer[buffctr] == kset.supers[ctr].input[ctr2] || data.cbuffer[buffctr] == kset.supers[ctr].input[ctr2]) {
              ctr2++;
              if(ctr2 == kset.supers[ctr].total) {
                if(curr_special == -1) {
                  if(kset.supers[ctr].type != 'A') {
                    if(data.super >= kset.supers[ctr].cost * 40) {
                      data.super -= kset.supers[ctr].cost * 40;
                      data.curr_seq = kset.supers[ctr].seq_num;
                      data.curr_frame = -1;
                      data.curr_grab = kset.grabs[kset.grabtotal+1];
                      curr_super = ctr;
                      super_start = 1;
                      if(kset.supers[ctr].type == 'm') {
                        kill_frames((fs_ptr)&fset);
                        get_ide((fs_ptr)&fset,kset.supers[ctr].ide);
                        get_re((fs_ptr)&fset);
                        get_seq((ms_ptr)&mset,kset.supers[ctr].seq);
                        get_cmd((ks_ptr)&kset,kset.supers[ctr].cmd);
                        for(int cnt=0;cnt<30;cnt++) {
                          samples[cnt] = load_sample(kset.sounds[cnt]);
                          }
                        morphctr = 0;
                        }
                      else if(kset.supers[ctr].type == 'M') {
                        kill_frames((fs_ptr)&fset);
                        get_ide((fs_ptr)&fset,kset.supers[ctr].ide);
                        get_re((fs_ptr)&fset);
                        get_seq((ms_ptr)&mset,kset.supers[ctr].seq);
                        get_cmd((ks_ptr)&kset,kset.supers[ctr].cmd);
                        for(int cnt=0;cnt<30;cnt++) {
                          samples[cnt] = load_sample(kset.sounds[cnt]);
                          }
                        morphctr = 101;
                        }
                      for(buffctr=0;buffctr<10;buffctr++) {
                        data.ibuffer[buffctr] = 'n';
                        data.cbuffer[buffctr] = 'n';
                        }
                      buffctr = 10;
                      done = 1;
                      data.super_kill = 1;
                      strcpy(data.super_name,kset.supers[ctr].name);
                      }
                    }
                  }
                }
              }
            buffctr++;
            }
          }
        }
      }
    }

void desperation_handler() {
    int ctr;
    int ctr2;
    int done = 0;
    for(ctr=0;ctr<kset.lastdesperation;ctr++) {
      if(!done) {
        if(kset.desperations[ctr].input[0] == data.ibuffer[0] || kset.desperations[ctr].input[0] == data.cbuffer[0]) {
          buffctr = 0;
          ctr2 = 0;
          while(buffctr < 10) {
            if(data.ibuffer[buffctr] == kset.desperations[ctr].input[ctr2] || data.cbuffer[buffctr] == kset.desperations[ctr].input[ctr2]) {
              ctr2++;
              if(ctr2 == kset.desperations[ctr].total) {
                if(curr_special == -1) {
                  if(kset.desperations[ctr].type != 'A') {
                    if(data.super >= kset.desperations[ctr].cost * 40) {
                      data.super -= kset.desperations[ctr].cost * 40;
                      if(data.life <= kset.desperations[ctr].life) {
                        data.curr_seq = kset.desperations[ctr].seq_num;
                        data.curr_frame = -1;
                        super_start = 1;
                        if(kset.desperations[ctr].type == 'm') {
                          kill_frames((fs_ptr)&fset);
                          get_ide((fs_ptr)&fset,kset.desperations[ctr].ide);
                          get_re((fs_ptr)&fset);
                          get_seq((ms_ptr)&mset,kset.desperations[ctr].seq);
                          get_cmd((ks_ptr)&kset,kset.desperations[ctr].cmd);
                          for(int cnt=0;cnt<30;cnt++) {
                            samples[cnt] = load_sample(kset.sounds[cnt]);
                            }
                          morphctr = 0;
                          }
                        else if(kset.desperations[ctr].type == 'M') {
                          kill_frames((fs_ptr)&fset);
                          get_ide((fs_ptr)&fset,kset.desperations[ctr].ide);
                          get_re((fs_ptr)&fset);
                          get_seq((ms_ptr)&mset,kset.desperations[ctr].seq);
                          get_cmd((ks_ptr)&kset,kset.desperations[ctr].cmd);
                          for(int cnt=0;cnt<30;cnt++) {
                            samples[cnt] = load_sample(kset.sounds[cnt]);
                            }
                          }
                        for(buffctr=0;buffctr<10;buffctr++) {
                          data.ibuffer[buffctr] = 'n';
                          data.cbuffer[buffctr] = 'n';
                          }
                        buffctr = 10;
                        done = 1;
                        data.super_kill = 1;
                        strcpy(data.super_name,kset.supers[ctr].name);
                        }
                      }
                    }
                  }
                }
              }
            buffctr++;
            }
          }
        }
      }
    }

  void ai_throw_handler(info_ptr opponent);

  void throw_handler(info_ptr opponent) {
    int ctr;
    int ctr2;
    int done = 0;
    for(ctr=0;ctr<=kset.grabtotal;ctr++) {
      if(!done) {
        if(kset.grabs[ctr].input[0] == data.ibuffer[0]) {
          if(data.ibuffer[1] == kset.grabs[ctr].input[1]) {
            if((opponent->dbox.active) && (opponent->p[1] == ground)) {
              if(data.second) {
                if(kset.grabs[ctr].direction == 1) {
                  data.second = 0;
                  opponent->second = 1;
                  data.p[0] -= abs(opponent->curr_sprite.x_off[0]) * 2;
                  }
                else if(kset.grabs[ctr].direction == 2) {
                  data.second = 1;
                  opponent->second = 0;
                  }
                }
              else {
                if(kset.grabs[ctr].direction == 1) {
                  data.second = 1;
                  opponent->second = 0;
                  data.p[0] += abs(opponent->curr_sprite.x_off[0]) * 2;
                  }
                else if(kset.grabs[ctr].direction == 2) {
                  data.second = 0;
                  opponent->second = 1;
                  }
                }
              switch(kset.grabs[ctr].damage) {
                case '0':  opponent->life -= 2;
                           break;
                case '1':  opponent->life -= 4;
                           break;
                case '2':  opponent->life -= 6;
                           break;
                case '3':  opponent->life -= 8;
                           break;
                case '4':  opponent->life -= 10;
                           break;
                case '5':  opponent->life -= 12;
                           break;
                case '6':  opponent->life -= 14;
                           break;
                case '7':  opponent->life -= 16;
                           break;
                case '8':  opponent->life -= 18;
                           break;
                case '9':  opponent->life -= 20;
                           break;
                }
              if(opponent->life <= 0) {
                opponent->alive = 0;
                ++data.wins;
                }
              data.curr_seq = kset.grabs[ctr].action;
              data.curr_frame = -1;
              opponent->curr_seq = kset.grabs[ctr].reaction;              
              opponent->curr_frame = -1;
              opponent->status = RECOIL;
              done = 1;
              data.super+=4;
              }
            }
          }
        }
      }
    }

  void air_movement_handler() {
    switch(data.ibuffer[0]) {
      case 'f':  if(data.second) {
                   if(velo > -5) velo--;
                   }
                 else {
                   if(velo < 5) velo++;
                   }
                 break;
      case 'b':  if(data.second) {
                   if(velo < 5) velo++;
                   }
                 else {
                   if(velo > -5) velo--;
                   }
                 break;
      }
    }

  void ai_air_attack_handler();

  void air_attack_handler() {
    switch(data.ibuffer[0]) {
      case '!':
      case '1':  switch(data.status) {
                   case JUMP :  air_seq = 26;
                                break;
                   case SJUMP:
                   case LEAP :  air_seq = 32;
                                break;
                   }
                 air_frame = -1;
                 air_done = 1;
                 break;
      case '@':
      case '2':  switch(data.status) {
                   case JUMP :  air_seq = 27;
                                break;
                   case SJUMP:
                   case LEAP :  air_seq = 33;
                                break;
                   }
                 air_frame = -1;
                 air_done = 1;
                 data.super+=2;
                 break;
      case '#':
      case '3':  switch(data.status) {
                   case JUMP :  air_seq = 28;
                                break;
                   case SJUMP:
                   case LEAP :  air_seq = 34;
                                break;
                   }
                 air_frame = -1;
                 air_done = 1;
                 data.super+=3;
                 break;
      case '$':
      case '4':  switch(data.status) {
                   case JUMP :  air_seq = 23;
                                break;
                   case SJUMP:
                   case LEAP :  air_seq = 29;
                                break;
                   }
                 air_frame = -1;
                 air_done = 1;
                 break;
      case '%':
      case '5':  switch(data.status) {
                   case JUMP :  air_seq = 24;
                                break;
                   case SJUMP:
                   case LEAP :  air_seq = 30;
                                break;
                   }
                 air_frame = -1;
                 air_done = 1;
                 data.super+=2;
                 break;
      case '^':
      case '6':  switch(data.status) {
                   case JUMP :  air_seq = 25;
                                break;
                   case SJUMP:
                   case LEAP :  air_seq = 31;
                                break;
                   }
                 air_frame = -1;
                 air_done = 1;
                 data.super+=3;
                 break;
      }
    }

  void ai_air_special_handler();
  void tag_update(int control,int cpu,info_ptr opponent1,info_ptr opponent2,info_ptr opponent3,int target,int who);

  void air_special_handler() {
    int ctr;
    int ctr2;
    int done = 0;
    for(ctr=0;ctr<kset.total;ctr++) {
      if(!done) {
        if(kset.attacks[ctr].input[0] == data.ibuffer[0] || kset.attacks[ctr].input[0] == data.cbuffer[0]) {
          buffctr = 0;
          ctr2 = 0;
          while(buffctr < 10) {
            if(data.ibuffer[buffctr] == kset.attacks[ctr].input[ctr2] || data.cbuffer[buffctr] == kset.attacks[ctr].input[ctr2]) {
              ctr2++;
              if(ctr2 == kset.attacks[ctr].total) {
                if(kset.attacks[ctr].type == 'A') {
                  air_seq = kset.attacks[ctr].seq_num;
                  if(kset.attacks[ctr].mod) frozen = 1;
                  air_frame = -1;
                  for(buffctr=0;buffctr<10;buffctr++) {
                    data.ibuffer[buffctr] = 'n';
                    data.cbuffer[buffctr] = 'n';
                    }
                  buffctr = 10;
                  done = 1;
                  data.super+=5;
                  }
                }
              }
            buffctr++;
            }
          }
        }
      }
    }

  void ai_air_super_handler();

  void air_super_handler() {
    int ctr;
    int ctr2;
    int done = 0;
    for(ctr=0;ctr<kset.suptotal;ctr++) {
      if(!done) {
        if(kset.supers[ctr].input[0] == data.ibuffer[0] || kset.supers[ctr].input[0] == data.cbuffer[0]) {
          buffctr = 0;
          ctr2 = 0;
          while(buffctr < 10) {
            if(data.ibuffer[buffctr] == kset.supers[ctr].input[ctr2] || data.cbuffer[buffctr] == kset.supers[ctr].input[ctr2]) {
              ctr2++;
              if(ctr2 == kset.supers[ctr].total) {
                if(curr_special == -1) {
                  if(data.super >= kset.supers[ctr].cost * 40) {
                    if(kset.supers[ctr].type == 'A') {
                      data.super -= kset.supers[ctr].cost * 40;
                      air_seq = kset.supers[ctr].seq_num;
                      air_frame = -1;
                      frozen = 1;
                      data.curr_grab = kset.grabs[kset.grabtotal+1];
                      curr_super = ctr;
                      super_start = 1;
                      for(buffctr=0;buffctr<10;buffctr++) {
                        data.ibuffer[buffctr] = 'n';
                        data.cbuffer[buffctr] = 'n';
                        }
                      buffctr = 10;
                      done = 1;
                      data.super_kill = 1;
                      strcpy(data.super_name,kset.supers[ctr].name);
                      }
                    }
                  }
                }
              }
            buffctr++;
            }
          }
        }
      }
    }

  void box_update() {
    if(data.status == JUMP || data.status == SJUMP || data.status == LEAP) {
      data.obox.p[1] = data.p[1] + fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num].y_off[0] + fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num].op[1];
      data.obox.p[3] = data.p[1] + fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num].y_off[0] + fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num].op[3];
      data.dbox.p[1] = data.p[1] + fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num].y_off[0];
      data.dbox.p[3] = data.p[1] + fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num].y_off[0] + fset.images[fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num].imag_num[0]].height;
      if(flip == 'b' || flip == 'h') {
        data.obox.p[0] = data.p[0] - fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num].x_off[0] - fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num].op[2];
        data.obox.p[2] = data.p[0] - fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num].x_off[0] - fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num].op[0];
        data.dbox.p[0] = data.p[0] + (-1*fset.images[fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num].imag_num[0]].width) - fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num].x_off[0];
        data.dbox.p[2] = data.p[0] + 0 - fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num].x_off[0];
        /*if(flip == 'b') {
          if(x<=(-1*i.width)) {
            y--;
            x = 0;
            }
          if(!copy) put_pixel_b(h+x-s.x_off[which],v+y+s.y_off[which],i.idata[cnt]);
          else put_pixel_b(h+x-s.x_off[which],v+y+s.y_off[which],255-i.idata[cnt]);
          x--;
          cnt++;
          }
        else {
          if(x>=i.width) {
            y--;
            x = 0;
            }
          if(!copy) put_pixel_b(h+x+s.x_off[which],v+y+s.y_off[which],i.idata[cnt]);
          else put_pixel_b(h+x+s.x_off[which],v+y+s.y_off[which],255-i.idata[cnt]);
          x++;
          cnt++;
          }*/
        }
      else {
        data.obox.p[0] = data.p[0] + fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num].x_off[0] + fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num].op[0];
        data.obox.p[2] = data.p[0] + fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num].x_off[0] + fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num].op[2];
        data.dbox.p[0] = data.p[0] + fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num].x_off[0];
        data.dbox.p[2] = data.p[0] + fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num].x_off[0] + fset.images[fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num].imag_num[0]].width;
        }

      if(fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num].op[3] == 0) {
        data.obox.p[1] = data.p[1] + fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num].y_off[0];
        data.obox.p[3] = data.p[1] + fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num].y_off[0] + fset.images[fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num].imag_num[0]].height;
        }
      if(fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num].op[2] == 0) {
        data.obox.p[0] = data.p[0] + fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num].x_off[0];
        data.obox.p[2] = data.p[0] + fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num].x_off[0] + fset.images[fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num].imag_num[0]].width;
        }

      if(mset.frames[mset.sequences[air_seq].moves[air_frame]].invincibility == 'A') data.dbox.active = 0;
      else data.dbox.active = 1;

      //if(mset.frames[mset.sequences[air_seq].moves[air_frame]].type == 'A') {
      if(mset.frames[mset.sequences[air_seq].moves[air_frame]].range != 'x') data.obox.active = 1;
      else data.obox.active = 0;
      //else obox.active = 0;
      }
    else {
      data.obox.p[1] = data.p[1] + fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].y_off[0] + fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].op[1];
      data.obox.p[3] = data.p[1] + fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].y_off[0] + fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].op[3];
      data.dbox.p[1] = data.p[1] + fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].y_off[0];
      data.dbox.p[3] = data.p[1] + fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].y_off[0] + fset.images[fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].imag_num[0]].height;
      if(flip == 'b' || flip == 'h') {
        data.obox.p[0] = data.p[0] - fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].x_off[0] - fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].op[2];
        data.obox.p[2] = data.p[0] - fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].x_off[0] - fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].op[0];
        data.dbox.p[0] = data.p[0] - fset.images[fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].imag_num[0]].width - fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].x_off[0];
        data.dbox.p[2] = data.p[0] - fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].x_off[0];
        }
      else {
        data.obox.p[0] = data.p[0] + fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].x_off[0] + fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].op[0];
        data.obox.p[2] = data.p[0] + fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].x_off[0] + fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].op[2];
        data.dbox.p[0] = data.p[0] + fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].x_off[0];
        data.dbox.p[2] = data.p[0] + fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].x_off[0] + fset.images[fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].imag_num[0]].width;
        }


      if(fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].op[3] == 0) {
        data.obox.p[1] = data.p[1] + fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].y_off[0];
        data.obox.p[3] = data.p[1] + fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].y_off[0] + fset.images[fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].imag_num[0]].height;
        }
      if(fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].op[2] == 0) {
        if(!data.second) {
          data.obox.p[0] = data.p[0] + fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].x_off[0];
          data.obox.p[2] = data.p[0] + fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].x_off[0] + fset.images[fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].imag_num[0]].width;
          }
        else {
          data.obox.p[0] = data.p[0] - fset.images[fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].imag_num[0]].width - fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].x_off[0];
          data.obox.p[2] = data.p[0] - fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].x_off[0];
          }
        }

      if(mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].invincibility == 'A') data.dbox.active = 0;
      else data.dbox.active = 1;

      //if(mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].type == 'A') {
      if(mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].range != 'x') data.obox.active = 1;
      else data.obox.active = 0;
      //  }
      //else obox.active = 0;
      }
    }

  void pbox_update() {
    for(projctr=0;projctr<20;projctr++) {
      if(proj[projctr].active) {
        data.pboxes[projctr].p[1] = proj[projctr].p[1] + fset.sprites[mset.frames[mset.sequences[proj[projctr].seq].moves[proj[projctr].curr_frame]].fram_num].y_off[0];
        data.pboxes[projctr].p[3] = proj[projctr].p[1] + fset.sprites[mset.frames[mset.sequences[proj[projctr].seq].moves[proj[projctr].curr_frame]].fram_num].y_off[0] + fset.images[fset.sprites[mset.frames[mset.sequences[proj[projctr].seq].moves[proj[projctr].curr_frame]].fram_num].imag_num[0]].height;
        if(proj[projctr].flip == 'b' || proj[projctr].flip == 'h') {
          data.pboxes[projctr].p[0] = proj[projctr].p[0] - fset.images[fset.sprites[mset.frames[mset.sequences[proj[projctr].seq].moves[proj[projctr].curr_frame]].fram_num].imag_num[0]].width - fset.sprites[mset.frames[mset.sequences[proj[projctr].seq].moves[proj[projctr].curr_frame]].fram_num].x_off[0];
          data.pboxes[projctr].p[2] = proj[projctr].p[0] - fset.sprites[mset.frames[mset.sequences[proj[projctr].seq].moves[proj[projctr].curr_frame]].fram_num].x_off[0];
          }
        else {
          data.pboxes[projctr].p[0] = proj[projctr].p[0] + fset.sprites[mset.frames[mset.sequences[proj[projctr].seq].moves[proj[projctr].curr_frame]].fram_num].x_off[0];
          data.pboxes[projctr].p[2] = proj[projctr].p[0] + fset.sprites[mset.frames[mset.sequences[proj[projctr].seq].moves[proj[projctr].curr_frame]].fram_num].x_off[0] + fset.images[fset.sprites[mset.frames[mset.sequences[proj[projctr].seq].moves[proj[projctr].curr_frame]].fram_num].imag_num[0]].width;
          }

        if(mset.frames[mset.sequences[proj[projctr].seq].moves[proj[projctr].curr_frame]].type == 'A') data.pboxes[projctr].active = 1;
        else data.pboxes[projctr].active = 0;
        }
      }
    }

  void block_handler(info_ptr opponent) {
    if(opponent->blocking) {
      opponent->curr_seq = 67;
      opponent->curr_frame = -1;
      }
    if(opponent->lowblock) {
      opponent->curr_seq = 68;
      opponent->curr_frame = -1;
      }
    //opponent->status = RECOIL;
    }

  void collision_handler(info_ptr opponent)
  {
    int ctr;
    int the_frame;
    int the_seq;
    opponent->super_kill = 0;
    if(data.status == LEAP || data.status == JUMP)
    {
      the_frame = air_frame;
      the_seq = air_seq;
    }
    else
    {
      the_frame = data.curr_frame;
      the_seq = data.curr_seq;
    }

    if(!opponent->blocking && !opponent->lowblock)
    {
      if(opponent->cf.type == 'I')
      {
        opponent->countering = 1;
      }
      else
      {
        if(mset.frames[mset.sequences[the_seq].moves[the_frame]].reaction != 'f')
        {
          if(opponent->frost)
          {
            opponent->frost = 0;
            opponent->frostctr = 0;
          }
        }
        switch(mset.frames[mset.sequences[the_seq].moves[the_frame]].reaction)
        {
          case '0':  opponent->curr_seq = 71;
                     break;
          case '1':  opponent->curr_seq = 72;
                     break;
          case '2':  opponent->curr_seq = 73;
                     break;
          case '3':  opponent->curr_seq = 74;
                     break;
          case '4':  opponent->curr_seq = 75;
                     break;
          case '5':  opponent->curr_seq = 76;
                     break;
          case '6':  opponent->curr_seq = 77;
                     break;
          case '7':  opponent->curr_seq = 78;
                     break;
          case '8':  opponent->curr_seq = 79;
                     break;
          case '9':  opponent->curr_seq = 71;
                     break;
          case 'A':  opponent->curr_seq = 83;
                     break;
          case 'B':  opponent->curr_seq = 84;
                     break;
          case 'C':  opponent->curr_seq = 85;
                     break;
          case 'D':  opponent->curr_seq = 86;
                     break;
          case 'E':  opponent->curr_seq = 87;
                     break;
          case 'f':  if(!opponent->frost)
                     {
                       opponent->frost = 1;
                       opponent->frostctr = 100;
                     }
                     else
                     {
                       opponent->frost = 0;
                       opponent->frostctr = 0;
                       data.frost = 1;
                       data.frostctr = 100;
                     }
                     break;
          case 'F':  opponent->curr_seq = 88;
                     break;
          case 'G':  opponent->curr_seq = 89;
                     break;
          case 'H':  opponent->curr_seq = 90;
                     break;
          case 'I':  opponent->curr_seq = 91;
                     break;
          case 'J':  opponent->curr_seq = 92;
                     break;
          case 'K':  opponent->curr_seq = 93;
                     break;
          case 'L':  opponent->curr_seq = 94;
                     break;
          case 'M':  opponent->curr_seq = 95;
                     break;
          case 'N':  opponent->curr_seq = 96;
                     break;
          case 'O':  opponent->curr_seq = 97;
                     break;
          case 'P':  opponent->curr_seq = 98;
                     break;
          case 'Q':  opponent->curr_seq = 99;
                     break;
        }
      }

      if(opponent->life > 0)
      {
        switch(mset.frames[mset.sequences[the_seq].moves[the_frame]].power)
        {
          case '0':  opponent->life -= 2;
                     data.super += 1;
                     break;
          case '1':  opponent->life -= 4;
                     data.super += 1;
                     break;
          case '2':  opponent->life -= 6;
                     data.super += 2;
                     break;
          case '3':  opponent->life -= 8;
                     data.super += 2;
                     break;
          case '4':  opponent->life -= 10;
                     data.super += 3;
                     break;
          case '5':  opponent->life -= 12;
                     data.super += 3;
                     break;
          case '6':  opponent->life -= 14;
                     data.super += 4;
                     break;
          case '7':  opponent->life -= 16;
                     data.super += 4;
                     break;
          case '8':  opponent->life -= 18;
                     data.super += 5;
                     break;
          case '9':  opponent->life -= 20;
                     data.super += 5;
                     break;
        }

        if(opponent->p[0] <= 20) data.p[0]+=15;
        else if(opponent->p[0] >= 500) data.p[0] -= 15;
      }
    }
    else block_handler(opponent);

    if(!juggling)
    {
      if(opponent->p[1] < ground) opponent->curr_seq = 76;
    }

    opponent->curr_frame = -1;
    ++opponent->combo;
    if(opponent->combo > 1)
    {
      if(data.second) opponent->second = 0;
      if(!data.second) opponent->second = 1;
    }
    if(drama)
    {
      for(ctr=0;ctr<opponent->combo;ctr++) delay(10);
    }

    opponent->status = RECOIL;
    opponent->super += opponent->combo/2;
    opponent->falling = 0;

    switch(mset.frames[mset.sequences[the_seq].moves[the_frame]].type)
    {
      case 'C':  the_seq = mset.sequences[the_seq].moves[++the_frame];
                 the_frame = -1;
                 if(data.status == LEAP || data.status == JUMP) frozen = 1;
                 break;
      case 'B':  if(opponent->blocking)
                 {
                   the_seq = mset.sequences[the_seq].moves[++the_frame];
                   the_frame = -1;
                   if(data.status == LEAP || data.status == JUMP) frozen = 1;
                 }
                 else the_frame++;
                 break;
      case 'H':  if(!opponent->blocking && !opponent->lowblock)
                 {
                   the_seq = mset.sequences[the_seq].moves[++the_frame];
                   the_frame = -1;
                   if(data.status == LEAP || data.status == JUMP) frozen = 1;
                 }
                 else the_frame++;
                 break;
      case 'V':  if(!opponent->blocking && !opponent->lowblock)
                 {
                   the_seq = mset.sequences[the_seq].moves[++the_frame];
                   the_frame = -1;
                 }
                 else if(opponent->blocking || opponent->lowblock)
                 {
                   the_seq = mset.sequences[the_seq].moves[the_frame+=2];
                   the_frame = -1;
                 }
                 if(data.status == LEAP || data.status == JUMP) frozen = 1;
                 break;
    }

    if(data.status == LEAP || data.status == JUMP)
    {
      air_frame = the_frame;
      air_seq = the_seq;

    }
    else
    {
      data.curr_frame = the_frame;
      data.curr_seq = the_seq;
    }

    if(opponent->life <= 0)
    {
      opponent->alive = 0;
//      if((opponent->curr_seq >= 71) && (opponent->curr_seq <= 78))  opponent->curr_seq = 79;
      if(opponent->life != -255)
      {
        ++data.wins;
        opponent->life = -255;
      }
    }
    else opponent->alive = 1;
  }

  void pcollision_handler(info_ptr opponent,int which) {
    int ctr;
    //opponent->frost = 0;
    if(mset.frames[mset.sequences[proj[which].seq].moves[proj[which].curr_frame]].reaction != 'f') {
      if(opponent->frost) {
        opponent->frost = 0;
        opponent->frostctr = 0;
        }
      }
    if(!opponent->blocking && !opponent->lowblock) {
      switch(mset.frames[mset.sequences[proj[which].seq].moves[proj[which].curr_frame]].reaction) {
        case '0':  opponent->curr_seq = 71;
                   break;
        case '1':  opponent->curr_seq = 72;
                   break;
        case '2':  opponent->curr_seq = 73;
                   break;
        case '3':  opponent->curr_seq = 74;
                   break;
        case '4':  opponent->curr_seq = 75;
                   break;
        case '5':  opponent->curr_seq = 76;
                   break;
        case '6':  opponent->curr_seq = 77;
                   break;
        case '7':  opponent->curr_seq = 78;
                   break;
        case '8':  opponent->curr_seq = 79;
                   break;
        case '9':  opponent->curr_seq = 71;
                   break;
        case 'A':  opponent->curr_seq = 83;
                   break;
        case 'B':  opponent->curr_seq = 84;
                   break;
        case 'C':  opponent->curr_seq = 85;
                   break;
        case 'D':  opponent->curr_seq = 86;
                   break;
        case 'E':  opponent->curr_seq = 87;
                   break;
        case 'F':  opponent->curr_seq = 88;
                   break;
        case 'f':  if(!opponent->frost) {
                     opponent->frost = 1;
                     opponent->frostctr = 100;
                     }
                   else {
                     opponent->frost = 0;
                     opponent->frostctr = 0;
                     data.frost = 1;
                     data.frostctr = 100;
                     }
                   break;
        case 'G':  opponent->curr_seq = 89;
                   break;
        case 'H':  opponent->curr_seq = 90;
                   break;
        case 'I':  opponent->curr_seq = 91;
                   break;
        case 'J':  opponent->curr_seq = 92;
                   break;
        case 'K':  opponent->curr_seq = 93;
                   break;
        case 'L':  opponent->curr_seq = 94;
                   break;
        case 'M':  opponent->curr_seq = 95;
                   break;
        case 'N':  opponent->curr_seq = 96;
                   break;
        case 'O':  opponent->curr_seq = 97;
                   break;
        case 'P':  opponent->curr_seq = 98;
                   break;
        case 'Q':  opponent->curr_seq = 99;
                   break;
        }

      switch(mset.frames[mset.sequences[proj[which].seq].moves[proj[which].curr_frame]].power) {
        case '0':  opponent->life -= 2;
                   data.super += 1;
                   break;
        case '1':  opponent->life -= 4;
                   data.super += 1;
                   break;
        case '2':  opponent->life -= 6;
                   data.super += 2;
                   break;
        case '3':  opponent->life -= 8;
                   data.super += 2;
                   break;
        case '4':  opponent->life -= 10;
                   data.super += 3;
                   break;
        case '5':  opponent->life -= 12;
                   data.super += 3;
                   break;
        case '6':  opponent->life -= 14;
                   data.super += 4;
                   break;
        case '7':  opponent->life -= 16;
                   data.super += 4;
                   break;
        case '8':  opponent->life -= 18;
                   data.super += 5;
                   break;
        case '9':  opponent->life -= 20;
                   data.super += 5;
                   break;
        }
      }
    else block_handler(opponent);

    if(!juggling)
    {
      if(opponent->p[1] < ground) opponent->curr_seq = 76;
        }
      opponent->curr_frame = -1;
      ++opponent->combo;
      if(opponent->combo > 2)
      {
        if(data.second) opponent->second = 0;
        if(!data.second) opponent->second = 1;
      }
      if(drama) {
        for(ctr=0;ctr<opponent->combo;ctr++) delay(10);
        }
      opponent->status = RECOIL;
      opponent->super += opponent->combo;
      opponent->falling = 0;

    if(opponent->life <= 0)
    {
      opponent->alive = 0;
//      if(opponent->curr_seq >= 71 && opponent->curr_seq <= 78)  opponent->curr_seq = 79;
      if(opponent->life != -255)
      {
        ++data.wins;
        opponent->life = -255;
      }
    }
    else opponent->alive = 1;
    }



  void super_startup(int x,int y,int o) {
    int spot;
    for(spot=50;spot>0;spot-=2) {
      circle(x-o,y,4,50-spot);
      put_pixel(x+spot-o,y,255);
      put_pixel(x-spot-o,y,255);
      put_pixel(x-o,y+spot,255);
      put_pixel(x-o,y-spot,255);
      put_pixel(x+spot-o,y+spot,255);
      put_pixel(x-spot-o,y-spot,255);
      put_pixel(x+spot-o,y-spot,255);
      put_pixel(x-spot-o,y+spot,255);
      delay(5);
      }
    shadowed = 1;
    shadow_color = rand() % 8;
//    shadow_cycle = rand() % 4;
    super_start = 0;
    }

  void guard_handler(info_ptr opponent) {
    for(projctr=0;projctr<20;projctr++) {
      if(opponent->pboxes[projctr].active) {
        if(guarding) {
          if(blocking == 0) data.curr_frame = -1;
          data.curr_seq = 9;
          blocking = 1;
          }
        if(lowguard) {
          if(lowblock == 0) data.curr_frame = -1;
          data.curr_seq = 10;
          lowblock = 1;
          }
        }
      }
    if(opponent->cf.type == 'A' || opponent->cf.type == 'C' || opponent->cf.type == 'H' || opponent->cf.type == 'B' || opponent->cf.type == 'V') {
      if(guarding) {
        if(blocking == 0) data.curr_frame = -1;
        data.curr_seq = 9;
        blocking = 1;
        }
      if(lowguard) {
        if(lowblock == 0) data.curr_frame = -1;
        data.curr_seq = 10;
        lowblock = 1;
        }
      }
    }

  void cpu_handler(info_ptr opponent,int offset);

  void event_handler(info_ptr opponent,int offset) {
    for(buffctr=9;buffctr>0;buffctr--) {
      data.ibuffer[buffctr] = data.ibuffer[buffctr-1];
      data.cbuffer[buffctr] = data.cbuffer[buffctr-1];
      }

    input_handler();
    convert_input();

    if(data.status == JUMP || data.status == LEAP) {
      if(!air_done) {
        switch(mset.frames[mset.sequences[air_seq].moves[air_frame]].cancel) {
          case '0':  break;
          case '1':  air_super_handler();
                     air_special_handler();
                     break;
          case '2':  air_attack_handler();
                     air_super_handler();
                     air_special_handler();
                     break;
          case '3':  air_attack_handler();
                     air_super_handler();
                     air_special_handler();
                     break;
          case '4':  break;
          case '5':  air_super_handler();
                     air_special_handler();
                     break;
          case '6':  air_attack_handler();
                     air_super_handler();
                     air_special_handler();
                     break;
          case '7':  air_attack_handler();
                     air_super_handler();
                     air_special_handler();
                     break;
          }
        }
      }
    else if(data.status != RECOIL) {
      switch(mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].cancel) {
        case '0':  break;
        case '1':  desperation_handler();
                   super_handler();
                   special_handler();
                   break;
        case '2':  attack_handler(offset);
                   if(close) throw_handler(opponent);
                   break;
        case '3':  attack_handler(offset);
                   desperation_handler();
                   super_handler();
                   special_handler();
                   if(close) throw_handler(opponent);
                   break;
        case '4':  movement_handler();
                   if(guarding || lowguard) guard_handler(opponent);
                   else {
                     blocking = 0;
                     lowblock = 0;
                     }
                   break;
        case '5':  movement_handler();
                   if(guarding || lowguard) guard_handler(opponent);
                   else {
                     blocking = 0;
                     lowblock = 0;
                     }
                   desperation_handler();
                   super_handler();
                   special_handler();
                   break;
        case '6':  movement_handler();
                   if(guarding || lowguard) guard_handler(opponent);
                   else {
                     blocking = 0;
                     lowblock = 0;
                     }
                   attack_handler(offset);
                   if(close) throw_handler(opponent);
                   break;
        case '7':  movement_handler();
                   if(guarding || lowguard) guard_handler(opponent);
                   else {
                     blocking = 0;
                     lowblock = 0;
                     }
                   attack_handler(offset);
                   desperation_handler();
                   super_handler();
                   special_handler();
                   if(close) throw_handler(opponent);
                   data.curr_input = data.ibuffer[0];
                   break;
        }
      }

    if(curr_special != -1) {
      if(kset.attacks[curr_special].type == 'C') cspecial_handler();
      }
    if(mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].type == 'J') {
      opponent->dbox.active = 1;
      }
    }


  void sound_handler() {
    int ctr=0;
    for(ctr=0;ctr<kset.lastsound;ctr++) {
      if(data.status == JUMP || data.status == LEAP) {
        if(air_seq == kset.fx[ctr].seq) {
          if(air_frame == kset.fx[ctr].framenum) {
            play_sample(samples[kset.fx[ctr].which],sfxvolume,125,1000,0);
            }
          }
        }
      else {
        if(data.curr_seq == kset.fx[ctr].seq) {
          if(data.curr_frame == kset.fx[ctr].framenum) {
            play_sample(samples[kset.fx[ctr].which],sfxvolume,125,1000,0);
            }
          }
        }
      }
    }

  void frame_handler(info_ptr opponent) {
    if(data.status == JUMP || data.status == LEAP) {
      switch(mset.frames[mset.sequences[air_seq].moves[air_frame]].type) {
        case 'I':  if(data.countering) {
                     air_seq = mset.sequences[air_seq].moves[++air_frame];
                     air_frame = -1;
                     }
                   else ++air_frame;
                   break;
        case 'C':
        case 'B':
        case 'H':  ++air_frame;
                   break;
        case 'V':  air_frame+=2;
                   break;
        }
      }
    else {
      switch(mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].type) {
        case 'I':  if(data.countering) {
                     data.curr_seq = mset.sequences[data.curr_seq].moves[++data.curr_frame];
                     data.curr_frame = -1;
                     }
                   else ++data.curr_frame;
                   break;
        case 'C':
        case 'B':
        case 'H':  ++data.curr_frame;
                   break;
        case 'V':  ++data.curr_frame;
                   ++data.curr_frame;
                   break;
        }
      }
    data.countering = 0;
    }

  void unknown_handler()
  {
    if(data.status == JUMP || data.status == LEAP)
    {
      switch(mset.frames[mset.sequences[air_seq].moves[air_frame]].type)
      {
        case 'I':  if(data.countering)
                   {
                     air_seq = mset.sequences[air_seq].moves[++air_frame];
                     air_frame = -1;
                   }
                   else ++air_frame;
                   break;
        case 'R':  if(rand() % 100 > 50) air_seq = mset.frames[mset.sequences[air_seq].moves[air_frame]].xmov;
                   else air_seq = mset.frames[mset.sequences[air_seq].moves[air_frame]].ymov;
                   air_frame = 0;
                   break;
      }
    }
    else
    {
      switch(mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].type)
      {
        case 'I':  if(data.countering)
                   {
                     data.curr_seq = mset.sequences[data.curr_seq].moves[++data.curr_frame];
                     data.curr_frame = -1;
                   }
                   else ++data.curr_frame;
                   break;
        case 'R':  if(rand() % 100 > 50) data.curr_seq = mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].xmov;
                   else data.curr_seq = mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].ymov;
                   data.curr_frame = 0;
                   break;
      }
    }
  }

  void update(int control,int cpu,info_ptr opponent) {
    if(sfr) {
      if(data.super>120) data.super = 120;
      }
    else data.super = 0;

    if(morphctr<100) morphctr++;

    if(data.frost) {
      if(data.frostctr>0) data.frostctr--;
      else data.frost = 0;
      }

    int pctr;
    data.control = control;
    if(data.dbox.active) {
      if(opponent->p[1] - abs(opponent->curr_sprite.y_off[0]) + 10 <= data.p[1] && data.p[1] <= opponent->p[1]) {
        if(opponent->p[0] > data.p[0]) {
          if(data.p[0] > opponent->p[0] - abs(opponent->curr_sprite.x_off[0])) {
            data.p[0] = opponent->p[0] - abs(opponent->curr_sprite.x_off[0]) - 1;
            }
          }
        else if(opponent->p[0] < data.p[0]) {
          if(data.p[0] < opponent->p[0] + abs(opponent->curr_sprite.x_off[0])) {
            data.p[0] = opponent->p[0] + abs(opponent->curr_sprite.x_off[0]) + 1;
            }
          }
        else {
          if(data.second) data.p[0]--;
          else data.p[0]++;
          }
        }
      }

    if(data.alive) {
      if(control) {
        if(data.status != RECOIL) {
          if(!data.frost) {
            if(opponent->alive) {
              if(!fire) {
                if(!cpu) event_handler(opponent,xoffset);
                else cpu_handler(opponent,xoffset);
                }
              else fire = 0;
              }
            }
          }
        }                
      //  }
      }

    if(check_collision((box_ptr)&data.obox,(box_ptr)&opponent->dbox))
    {
      if(!data.countering)
      {
        if(data.alive) collision_handler(opponent);
      }
    }
    else frame_handler(opponent);

    unknown_handler();

    for(projctr=0;projctr<20;projctr++)
    {
      if(data.pboxes[projctr].active)
      {
        if(check_collision((box_ptr)&data.pboxes[projctr],(box_ptr)&opponent->dbox))
        {
          if(opponent->alive) pcollision_handler(opponent,projctr);
          data.pboxes[projctr].active = 0;
        }
        for(pctr=0;pctr<20;pctr++)
        {
          if(check_collision((box_ptr)&data.pboxes[projctr],(box_ptr)&opponent->pboxes[pctr]))
          {
            opponent->pboxes[pctr].active = 0;
            data.pboxes[projctr].active = 0;
          }
        }
      }
    }

    if(!opponent->alive)
    {
      if(!posing)
      {
        if(!data.mid_seq)
        {
          if(opponent->curr_seq == 43)
          {
            if(rand() % 200 > 100) data.curr_seq = 41;
            else data.curr_seq = 42;
            data.curr_frame = -1;
            posing = 1;
          }
        }
      }
    }

    if(abs(opponent->p[0] - data.p[0]) <= kset.range) close = 1;
    else close = 0;

    if(data.curr_seq != 0) data.mid_seq = 1;
    else data.mid_seq = 0;

    if(!data.mid_seq) {
      if(data.p[0] > opponent->p[0]) data.second = 0;
      else data.second = 1;
      }

    //frame_handler(opponent);
    if(!data.frost)
    {
      data.curr_frame++;
      shadow_handler();
      sound_handler();
    }

    if(data.curr_frame > mset.sequences[data.curr_seq].used)
    {
      if(data.p[1] != ground)
      {
        data.falling = 1;
      }
      else
      {
        if(data.alive) data.curr_seq = mset.sequences[data.curr_seq].nextseq;
        else
        {
          if(mset.sequences[data.curr_seq].nextseq == 0) data.curr_seq = 79;
          else if(mset.sequences[data.curr_seq].nextseq == 108) data.curr_seq = data.curr_seq = 43;
          else data.curr_seq = mset.sequences[data.curr_seq].nextseq;
        }
        data.curr_frame = 0;
        data.status = STAND;
        air_done = 0;
        curr_special = -1;
        curr_cspecial = -1;
        curr_super = -1;
        if(mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].cancel != '0')  data.mid_seq = 0;
        data.combo = 0;
        frozen = 0;
        shadowed = 0;
        throwing = 0;
        walking = 0;
        shade = 0;
        if(morphctr==100)
        {
          if(data.curr_seq == 0)
          {
            kill_frames((fs_ptr)&fset);
            get_ide((fs_ptr)&fset,i);
            get_re((fs_ptr)&fset);
            get_seq((ms_ptr)&mset,s);
            get_cmd((ks_ptr)&kset,k);
          }
          morphctr++;
        }
      }
      shadow_init();
      data.super_kill = 0;
    }



    shadow_draw();

/*    if(shade) {
      if(data.status==JUMP || data.status == LEAP) {
        draw_warrior(data.p[0],data.p[1],fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame-fire]].fram_num],fset.images[fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame-fire]].fram_num].imag_num[0]],flip,0,0);
        if(fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame-fire]].fram_num].last_image) {
          draw_warrior(data.p[0],data.p[1],fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame-fire]].fram_num],fset.images[fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame-fire]].fram_num].imag_num[1]],flip,1,0);
          }
        }
      else {
        draw_warrior(data.p[0],data.p[1],fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame-fire]].fram_num],fset.images[fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame-fire]].fram_num].imag_num[0]],flip,0,0);
        if(fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame-fire]].fram_num].last_image) {
          draw_warrior(data.p[0],data.p[1],fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame-fire]].fram_num],fset.images[fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame-fire]].fram_num].imag_num[1]],flip,1,0);
          }
        }
      }*/

    if(!data.frost) {
      if(data.falling) {
        if(data.p[1] < ground) {
          if(data.curr_frame > 0)  data.curr_frame--;
          data.p[1] += grav2;
          grav2++;
          }
        else {
          data.falling = 0;
          grav2 = 0;
          }
        }

      if(data.alive) {
        if(!data.mid_seq) {
          if(opponent->p[0] > data.p[0]) data.second = 0;
          else if(opponent->p[0] < data.p[0]) data.second = 1;
          }
        }

      if(data.status == JUMP || data.status == LEAP) {
        air_frame++;
        if(air_frame >= mset.sequences[air_seq].used) {
          air_seq = data.curr_seq;
//          data.curr_frame = mset.sequences[data.curr_seq].used - 1;
          air_frame = mset.sequences[data.curr_seq].used - 1;
          if(frozen) {
            data.curr_frame = mset.sequences[data.curr_seq].used - 1;
            air_frame = data.curr_frame;
            frozen = 0;
            }
           //data.curr_frame;
        /*if(frozen) {
          falling = 1;
          }*/
//        frozen = 0;
          }
        }
      }

    if(data.status == STAND && data.curr_seq == 0) {
      if(data.p[1] < ground) data.p[1] = ground;
      }

    for(projctr=0;projctr<20;projctr++) {
      if(!data.pboxes[projctr].active) {
        if(mset.frames[mset.sequences[proj[projctr].seq].moves[proj[projctr].curr_frame]].range != 'x') {
          if(mset.sequences[mset.sequences[proj[projctr].seq].nextseq].active) {
            if(mset.sequences[proj[projctr].seq].nextseq != 253) {
              if(sfr) proj[projctr].seq = mset.sequences[proj[projctr].seq].nextseq;
              else proj[projctr].seq = 66;
              }
            else {
              proj[projctr].active = 0;
              }
            }
          else proj[projctr].active = 0;
          proj[projctr].curr_frame = 0;
          }
        }

      if(proj[projctr].active) {
        proj[projctr].curr_frame++;
        if(proj[projctr].curr_frame > mset.sequences[proj[projctr].seq].used) {
          //
          if(sfr) proj[projctr].active = 0;
          else {
            if(mset.sequences[proj[projctr].seq].nextseq != 253 && mset.sequences[proj[projctr].seq].nextseq != 0) {
              proj[projctr].curr_frame = 0;
              proj[projctr].seq = mset.sequences[proj[projctr].seq].nextseq;
              }
            else proj[projctr].active = 0;
            }
          }
        }
      else data.pboxes[projctr].active = 0;
      }

    if(!data.frost)
    {
      if(frozen)
      {
        if(data.status == RECOIL) frozen = 0;
        data.curr_frame--;
        if(data.status != SJUMP) {
          if(data.second) {
            data.p[0] -= mset.frames[mset.sequences[air_seq].moves[air_frame]].xmov;
            }
          else {
            data.p[0] += mset.frames[mset.sequences[air_seq].moves[air_frame]].xmov;
            }
          data.p[1] += mset.frames[mset.sequences[air_seq].moves[air_frame]].ymov;
          }
        }
      else
      {
        if(mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].type != 'R')
        {
          if(data.second)
          {
            data.p[0] -= mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].xmov;
          }
          else
          {
            data.p[0] += mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].xmov;
          }
          data.p[1] += mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].ymov;
        }
      }
    }

    if(data.alive && control) {
      if(data.p[0] > xoffset+300) data.p[0] = xoffset+300;
      if(data.p[0] < xoffset+20) data.p[0] = xoffset+20;
      }

    if(data.p[1] > ground) {
      data.p[1] = ground;
      if(frozen) {
        data.curr_seq = mset.sequences[data.curr_seq].nextseq;
        data.curr_frame = 0;
        frozen = 0;
        }
      grav = maxheight;
      data.status = STAND;
      }

    if(!data.second) {
      draw_warrior(data.p[0],ground,fset.sprites[0],fset.images[0],flip,0,0,'n');
      if(data.status == JUMP || data.status == LEAP || data.status == SJUMP) {
        switch(mset.frames[mset.sequences[air_seq].moves[air_frame]].orient) {
          case 'N': flip = 'n';
                    break;
          case 'R': flip = 'b';
                    break;
          case 'F': flip = 'h';
                    break;
          case 'U': flip = 'v';
                    break;
          }
        draw_warrior(data.p[0],data.p[1],fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num],fset.images[fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num].imag_num[0]],flip,0,clone,'r');
        if(fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num].last_image) {
          draw_warrior(data.p[0],data.p[1],fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num],fset.images[fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num].imag_num[1]],flip,1,clone,'r');
          }
        }
      else {
        switch(mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].orient) {
          case 'N': flip = 'n';
                    break;
          case 'R': flip = 'b';
                    break;
          case 'F': flip = 'h';
                    break;
          case 'U': flip = 'v';
                    break;
          }
        draw_warrior(data.p[0],data.p[1],fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num],fset.images[fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].imag_num[0]],flip,0,clone,'r');
        if(fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].last_image) {
          draw_warrior(data.p[0],data.p[1],fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num],fset.images[fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].imag_num[1]],flip,1,clone,'r');
          }
        }
      }
    else {
      draw_warrior(data.p[0],ground,fset.sprites[0],fset.images[0],flip,0,0,'n');
      if(data.status == JUMP || data.status == LEAP || data.status == SJUMP) {
        switch(mset.frames[mset.sequences[air_seq].moves[air_frame]].orient) {
          case 'N': flip = 'h';
                    break;
          case 'R': flip = 'v';
                    break;
          case 'F': flip = 'n';
                    break;
          case 'U': flip = 'b';
                    break;
          }
        draw_warrior(data.p[0],data.p[1],fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num],fset.images[fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num].imag_num[0]],flip,0,clone,'r');
        if(fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num].last_image) {
          draw_warrior(data.p[0],data.p[1],fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num],fset.images[fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num].imag_num[1]],flip,1,clone,'r');
          }
        }
      else {
        switch(mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].orient) {
          case 'N': flip = 'h';
                    break;
          case 'R': flip = 'v';
                    break;
          case 'F': flip = 'n';
                    break;
          case 'U': flip = 'b';
                    break;
          }
        draw_warrior(data.p[0],data.p[1],fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num],fset.images[fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].imag_num[0]],flip,0,clone,'r');
        if(fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].last_image) {
          draw_warrior(data.p[0],data.p[1],fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num],fset.images[fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num].imag_num[1]],flip,1,clone,'r');
          }
        }
      }


    if(super_start) {
      ++super_start;
      if(super_start == 3) super_startup(data.obox.p[0] + ((data.obox.p[2] - data.obox.p[0]) / 2),data.obox.p[1] + ((data.obox.p[3] - data.obox.p[1])/ 2),xoffset);
      }
    box_update();
    data.blocking = blocking;
    data.lowblock = lowblock;
    if(data.status == JUMP || data.status == LEAP || data.status == SJUMP) {
      data.cf = mset.frames[mset.sequences[air_seq].moves[air_frame]];
      data.curr_sprite = fset.sprites[mset.frames[mset.sequences[air_seq].moves[air_frame]].fram_num];
      }
    else {
      data.cf = mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]];
      data.curr_sprite = fset.sprites[mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].fram_num];
      }


    if(data.status == JUMP || data.status == LEAP || data.status == SJUMP) {
      if(mset.frames[mset.sequences[air_seq].moves[air_frame]].type == 'F') {
        fire = 1;
        if(sfr) {
          switch(mset.frames[mset.sequences[air_seq].moves[air_frame]].power) {
            case '1':  pstartctr = 1;
                       break;
            case '2':  pstartctr = 2;
                       break;
            case '3':  pstartctr = 3;
                       break;
            case '4':  pstartctr = 4;
                       break;
            case '5':  pstartctr = 5;
                       break;
            case '6':  pstartctr = 6;
                       break;
            case '7':  pstartctr = 7;
                       break;
            case '8':  pstartctr = 8;
                       break;
            case '9':  pstartctr = 9;
                       break;
            case 'A':  pstartctr = 10;
                       break;
            case 'B':  pstartctr = 11;
                       break;
            case 'C':  pstartctr = 12;
                       break;
            case 'D':  pstartctr = 13;
                       break;
            case 'E':  pstartctr = 14;
                       break;
            case 'F':  pstartctr = 15;
                       break;
            }
          }
        else {
          if(mset.frames[mset.sequences[air_seq].moves[air_frame]].power == '4') pstartctr = 1;
          }
        for(projctr=0;projctr<pstartctr;projctr++) {
          proj[curr_proj].active = 1;
          proj[curr_proj].seq = mset.sequences[air_seq].moves[++air_frame];
          proj[curr_proj].p[0] = data.p[0];
          proj[curr_proj].p[1] = data.p[1];
          proj[curr_proj].curr_frame = 0;
          if(data.second) proj[curr_proj].direction = 1;
          else proj[curr_proj].direction = 0;
          curr_proj++;
          if(curr_proj >= 20) {
            curr_proj = 0;
            }
          }
        }
      }
    else {
      if(mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].type == 'F') {
        fire = 1;
        if(sfr) {
          switch(mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].power) {
            case '1':  pstartctr = 1;
                       break;
            case '2':  pstartctr = 2;
                       break;
            case '3':  pstartctr = 3;
                       break;
            case '4':  pstartctr = 4;
                       break;
            case '5':  pstartctr = 5;
                       break;
            case '6':  pstartctr = 6;
                       break;
            case '7':  pstartctr = 7;
                       break;
            case '8':  pstartctr = 8;
                       break;
            case '9':  pstartctr = 9;
                       break;
            case 'A':  pstartctr = 10;
                       break;
            case 'B':  pstartctr = 11;
                       break;
            case 'C':  pstartctr = 12;
                       break;
            case 'D':  pstartctr = 13;
                       break;
            case 'E':  pstartctr = 14;
                       break;
            case 'F':  pstartctr = 15;
                       break;
            }
          }
        else {
          if(mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].power == '4') pstartctr = 1;
          }

        for(projctr=0;projctr<pstartctr;projctr++) {
          proj[curr_proj].active = 1;
          proj[curr_proj].seq = mset.sequences[data.curr_seq].moves[++data.curr_frame];
          proj[curr_proj].p[0] = data.p[0];
          proj[curr_proj].p[1] = data.p[1];
          proj[curr_proj].curr_frame = 0;
          if(data.second) proj[curr_proj].direction = 1;
          else proj[curr_proj].direction = 0;
          curr_proj++;
          if(curr_proj >= 20) {
            curr_proj = 0;
            }
          }
        }
      }

    pstartctr = 0;
    for(projctr=19;projctr>=0;projctr--) {
      if(proj[projctr].active) {
        if(proj[projctr].direction) {
          proj[projctr].p[0] -= mset.frames[mset.sequences[proj[projctr].seq].moves[proj[projctr].curr_frame]].xmov;
          proj[projctr].p[1] += mset.frames[mset.sequences[proj[projctr].seq].moves[proj[projctr].curr_frame]].ymov;
          switch(mset.frames[mset.sequences[proj[projctr].seq].moves[proj[projctr].curr_frame]].orient) {
            case 'N': proj[projctr].flip = 'h';
                      break;
            case 'R': proj[projctr].flip = 'v';
                      break;
            case 'F': proj[projctr].flip = 'n';
                      break;
            case 'U': proj[projctr].flip = 'b';
                      break;
            }
          draw_warrior(proj[projctr].p[0],proj[projctr].p[1],fset.sprites[mset.frames[mset.sequences[proj[projctr].seq].moves[proj[projctr].curr_frame]].fram_num],fset.images[fset.sprites[mset.frames[mset.sequences[proj[projctr].seq].moves[proj[projctr].curr_frame]].fram_num].imag_num[0]],proj[projctr].flip,0,0,'n');
          }
        else {
          proj[projctr].p[0] += mset.frames[mset.sequences[proj[projctr].seq].moves[proj[projctr].curr_frame]].xmov;
          proj[projctr].p[1] += mset.frames[mset.sequences[proj[projctr].seq].moves[proj[projctr].curr_frame]].ymov;
          switch(mset.frames[mset.sequences[proj[projctr].seq].moves[proj[projctr].curr_frame]].orient) {
            case 'N': proj[projctr].flip = 'n';
                      break;
            case 'R': proj[projctr].flip = 'b';
                      break;
            case 'F': proj[projctr].flip = 'h';
                      break;
            case 'U': proj[projctr].flip = 'v';
                      break;
            }
          draw_warrior(proj[projctr].p[0],proj[projctr].p[1],fset.sprites[mset.frames[mset.sequences[proj[projctr].seq].moves[proj[projctr].curr_frame]].fram_num],fset.images[fset.sprites[mset.frames[mset.sequences[proj[projctr].seq].moves[proj[projctr].curr_frame]].fram_num].imag_num[0]],proj[projctr].flip,0,0,'n');
          }
        }
      }
    pbox_update();
    for(projctr=0;projctr<20;projctr++) {
      data.pframes[projctr] = mset.frames[mset.sequences[proj[projctr].seq].moves[proj[projctr].curr_frame]];
      }
    }
  };

class background {
  public:
  char *buf;
  int memsize;
  //int height;
  int yoff;
  int color;


  int get(char filename[25])
  {
    int i=0;
    int filenum;
    char getex;
    char ext[4];
    int ctr=0;
    char backgrounds[25][25];
    int numbacks = 0;
    FILE *fp;

    while(getex != '.'){ getex=filename[i++]; }
    ext[0]=filename[i++];
    ext[1]=filename[i++];
    ext[2]=filename[i++];
    ext[3]=NULL;

    if(!strcmp(ext,"lst"))
    {
      if((fp = fopen(filename,"rb")) == NULL)
      {
        printf("Couldn't open %s, aborting\n");
        return 0;
      }

      fscanf(fp,"%d",&numbacks);
      for(ctr=0;ctr<numbacks;ctr++)
      {
        fscanf(fp,"%s",&backgrounds[ctr]);
      }

      fclose(fp);

      strcpy(filename,backgrounds[rand() % numbacks]);

      i = 0;
      getex = 'n';

      while(getex != '.'){ getex=filename[i++]; }
      ext[0]=filename[i++];
      ext[1]=filename[i++];
      ext[2]=filename[i++];
      ext[3]=NULL;
    }


    if((fp = fopen(filename,"rb")) == NULL)
    {
      printf("%s",&filename);
      alert_error("Unable to get background.");
      return 0;
    }

    width=atoi(ext);
    filenum = fileno(fp);
    height = filelength(filenum) / width;
    if((buf = (char *)malloc(width*height)) == NULL)
    {
      printf("Can't allocate BG buffer, aborting.\n");
      return 0;
    }

//    while((buf[ctr] = fgetc(fp))!=EOF) ctr++;
//    memsize = ctr;
//    memsize = fread(buf,520*240,1,fp);
    while(!feof(fp))
    {
      buf[ctr] = fgetc(fp);
      ctr++;
    }
    memsize = ctr;
//    printf("%d background bytes\n",memsize);
//    getch();
    fclose(fp);
    color = rand() % 255;
    return 1;
  }

  ~background()
  {
    free(buf);
  }

  void update(info_ptr p1,info_ptr p2,int drama) {
    int ctr=0;
    int x = 0;
    int y = 0;

    if(p1->alive && p1->control) {
      if(p1->p[0] < xoffset+30) {
        if(p2->p[0] < xoffset+290) {
          if(xoffset>0) {
            xoffset -= xoffset+30-p1->p[0];
            p2->p[0] += xoffset+30-p1->p[0];
            p1->p[0] = xoffset+30+1;
            if(xoffset<0) xoffset=0;
            }
          }
        }
      }

    if(p2->alive && p2->control) {
      if(p2->p[0] < xoffset+30) {
        if(p1->p[0] < xoffset+290) {
          if(xoffset>0) {
            xoffset -= xoffset+30-p2->p[0];
            p1->p[0] += xoffset+30-p2->p[0];
            p2->p[0] = xoffset+30+1;
            if(xoffset<0) xoffset=0;
            }
          }
        }
      }

    if(p1->alive && p1->control) {
      if(p1->p[0] > xoffset+290) {
        if(p2->p[0] > xoffset+30) {
          if(xoffset<width-320) {
            xoffset += p1->p[0] - (xoffset+290);
            p2->p[0] -= p1->p[0] - (xoffset+290);
            p1->p[0] = xoffset+290-1;
            if(xoffset>width-320) xoffset=width-320;
            }
          }
        }
      }

    if(p2->alive && p2->control) {
      if(p2->p[0] > xoffset+290) {
        if(p1->p[0] > xoffset+30) {
          if(xoffset<width-320) {
            xoffset += p2->p[0] - (xoffset+290);
            p1->p[0] -= p2->p[0] - (xoffset+290);
            p2->p[0] = xoffset+290-1;
            if(xoffset>width-320) xoffset=width-320;
            }
          }
        }
      }

    if(xoffset<0) xoffset = 0;
    if(xoffset>width-320) xoffset=width-320;


   // if(p1->p[1] < 100) yoffset++;
   // else yoffset--;

   // if(p2->p[1] < 100) yoffset++;
   // else yoffset--;

    //if((p1->p[1] > (yoffset+100)) && (p2->p[1] > (yoffset+100))) yoffset++;
    if((p1->p[1] > yoffset+180) && (p2->p[1] > yoffset+180))
    {
      if(p1->p[1] < p2->p[1]) yoffset = p1->p[1] - 180;
      else yoffset = p2->p[1] - 180;
    }
    yoffset++;

    if(p1->p[1] < (yoffset+100)) yoffset-= ((yoffset+100) - p1->p[1]) / 2;
    if(p2->p[1] < (yoffset+100)) yoffset-= ((yoffset+100) - p2->p[1]) / 2;


    if(yoffset<0) yoffset = 0;
    if(yoffset>height-200) yoffset=height-200;



    //memcpy(double_buffer,buf,width*height);
//    for(ctr=200-height;ctr<height;ctr++) {
    if(!drama)
    {
      for(ctr=0;ctr<height;ctr++)
      {
        memcpy(double_buffer+ctr*640,buf+ctr*width,width);
      }
    }
    else
    {
      memset(double_buffer,color,640*400);
    }
    color+=4;
    if(color>255) color = color-255;
    /* asm volatile (
      "pushl %%es\n
      pushl %%ds\n
      popl %%es\n
      rep; movsl\n
      popl %%es\n":
      :"c" (320/4),"S" (&buf[520*ctr+offset]),
      "D" (&double_buffer[520*ctr+offset])
      :"%ecx","%esi","%edi","memory");
      }*/
//    return offset;
    }
  };



