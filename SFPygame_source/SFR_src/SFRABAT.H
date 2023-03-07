#include "sfrwfite.h"

int return_scancode() {
  int ctr=1;  //Generic counter.
  int val=0;

  //a for loop that checks every possible key to see if it is pressed.
  while(val == 0) {
    if(ctr<128) ctr++;
    else ctr = 1;
    if(key_table[ctr]) val = ctr;
    }



/*  for(ctr=1;ctr<128;ctr++) {
    if(key_table[ctr]) val = ctr;
    //return ctr;  //if the key has been pressed, return its value.
    }*/
  return val;  //if no key was found, return 0.
  }

void map_controls(int player) {
  int strt=0, up=0, dn=0, lf=0, rt=0, jb=0, st=0, fc=0, sh=0, fw=0, rh=0, p3=0, k3=0;
  char filename[25];
  //Integer values for the scancode of each button.  start, up, down, left, right, jab, strong, fierce, short, forward, r. house, all 3 punches, all 3 kicks*/

  if(player==1) strcpy(filename,"p1.key");
  else strcpy(filename,"p2.key");

  FILE *fp;  //A file pointer, for file access.
  if((fp = fopen(filename,"wb")) == NULL) {
    printf("Unable to Create %s\n",filename);
    return;
    }

/*  if(player == 1) if((fp = fopen("p1.key","wt")) == NULL) { //Create player one control file or. .
    printf("unable to create p1.key");
    exit(-1);
    }
  else if(player == 2) if((fp = fopen("p2.key","wt")) == NULL) {   //Create player two control file.
    printf("unable to create p2.key");
    exit(-1);
    }*/

  //fprintf(fp,"%d %d %d %d %d %d %d %d %d %d %d %d %d",
//              strt,up,dn,lf,rt,jb,st,fc,sh,fw,rh,p3,k3);

  //do loop, while no key has been pressed.
//  do {
    draw_string(0,0,(font_ptr)&fnt,"Press key for start",'l',1);
    show_double_buffer(0,0,1);  //Copies all image data to the actual video buffer (screen).
    strt = return_scancode();

    fprintf(fp,"%d ",strt);

    do{
      }while(keys_active);

    draw_string(0,0,(font_ptr)&fnt,"Press key for up",'l',1);
    show_double_buffer(0,0,1);  //Copies all image data to the actual video buffer (screen).
    up = return_scancode();  //Key has been pressed, get it's scan code, and store it in up.

    fprintf(fp,"%d ",up);

        do{
      }while(keys_active);

    draw_string(0,0,(font_ptr)&fnt,"Press key for down",'l',1);
    show_double_buffer(0,0,1);  //Copies all image data to the actual video buffer (screen).
    dn = return_scancode();  //Key has been pressed, get it's scan code, and store it in up.

    fprintf(fp,"%d ",dn);

        do{
      }while(keys_active);

    draw_string(0,0,(font_ptr)&fnt,"Press key for left",'l',1);
    show_double_buffer(0,0,1);  //Copies all image data to the actual video buffer (screen).
    lf = return_scancode();  //Key has been pressed, get it's scan code, and store it in up.

    fprintf(fp,"%d ",lf);

        do{
      }while(keys_active);

    draw_string(0,0,(font_ptr)&fnt,"Press key for right",'l',1);
    show_double_buffer(0,0,1);  //Copies all image data to the actual video buffer (screen).
    rt = return_scancode();  //Key has been pressed, get it's scan code, and store it in up.

    fprintf(fp,"%d ",rt);

        do{
      }while(keys_active);

    draw_string(0,0,(font_ptr)&fnt,"Press key for jab",'l',1);
    show_double_buffer(0,0,1);  //Copies all image data to the actual video buffer (screen).
    jb = return_scancode();  //Key has been pressed, get it's scan code, and store it in up.

    fprintf(fp,"%d ",jb);

        do{
      }while(keys_active);

    draw_string(0,0,(font_ptr)&fnt,"Press key for strong",'l',1);
    show_double_buffer(0,0,1);  //Copies all image data to the actual video buffer (screen).
    st = return_scancode();  //Key has been pressed, get it's scan code, and store it in up.

    fprintf(fp,"%d ",st);

        do{
      }while(keys_active);

    draw_string(0,0,(font_ptr)&fnt,"Press key for fierce",'l',1);
    show_double_buffer(0,0,1);  //Copies all image data to the actual video buffer (screen).
    fc = return_scancode();  //Key has been pressed, get it's scan code, and store it in up.

    fprintf(fp,"%d ",fc);

        do{
      }while(keys_active);

    draw_string(0,0,(font_ptr)&fnt,"Press key for short",'l',1);
    show_double_buffer(0,0,1);  //Copies all image data to the actual video buffer (screen).
    sh = return_scancode();  //Key has been pressed, get it's scan code, and store it in up.

    fprintf(fp,"%d ",sh);

        do{
      }while(keys_active);

    draw_string(0,0,(font_ptr)&fnt,"Press key for forward",'l',1);
    show_double_buffer(0,0,1);  //Copies all image data to the actual video buffer (screen).
    fw = return_scancode();  //Key has been pressed, get it's scan code, and store it in up.

    fprintf(fp,"%d ",fw);

        do{
      }while(keys_active);

    draw_string(0,0,(font_ptr)&fnt,"Press key for roundhouse",'l',1);
    show_double_buffer(0,0,1);  //Copies all image data to the actual video buffer (screen).
    rh = return_scancode();  //Key has been pressed, get it's scan code, and store it in up.

    fprintf(fp,"%d ",rh);

        do{
      }while(keys_active);

    draw_string(0,0,(font_ptr)&fnt,"Press key for all punch",'l',1);
    show_double_buffer(0,0,1);  //Copies all image data to the actual video buffer (screen).
    p3 = return_scancode();  //Key has been pressed, get it's scan code, and store it in up.

    fprintf(fp,"%d ",p3);

        do{
      }while(keys_active);

    draw_string(0,0,(font_ptr)&fnt,"Press key for all kick",'l',1);
    show_double_buffer(0,0,1);  //Copies all image data to the actual video buffer (screen).
    k3 = return_scancode();  //Key has been pressed, get it's scan code, and store it in up.

    fprintf(fp,"%d ",k3);

        do{
      }while(keys_active);

  fclose(fp);  //close the file pointer.
  }

int gfx_player_select(char *p1, char *p2, char *bg, char config[25]) {
  int st1, up1, dn1, lf1, rt1, jb1, sg1, fc1, sh1, fw1, rh1;
  int st2, up2, dn2, lf2, rt2, jb2, sg2, fc2, sh2, fw2, rh2;
  portrait left, right;
  char bigp[25];
  int p1id=0, p2id=0;
  int p1on=0, p2on=0;
  int p1alt=0,p2alt=0;
  int p1last=0, p2last=0;
  int p1done=0, p2done=0;
  char p1name[25],p2name[25];

  int ctr=0,ctr2=0;
  FILE *fp;
  FILE *fp2;
  int height=0,width=0;
  int x,y;
  char port[25];
  int type;
  char i[25];
  char s[25];
  char k[25];
  char b[25];
  int returnval;
  int p1ctr=0,p2ctr=0;
  int curr_port=0;
  int screen_num=0;
  static frameset fset1,fset2;
  static moveset mset1,mset2;


  y = 100 - (cs.bigpic.height/2);

  for(ctr=0;ctr<cs.last_character;ctr++)
  {
    if(width<cs.characters[ctr].port.width) width = cs.characters[ctr].port.width;
    if(height<cs.characters[ctr].port.height) height = cs.characters[ctr].port.height;
  }

  p1id = rand() % cs.last_character;
  p2id = rand() % cs.last_character;

  fp = fopen("p1.key","rb");
  fscanf(fp,"%d %d %d %d %d %d %d %d %d %d %d",&st1,&up1,&dn1,&lf1,&rt1,&jb1,&sg1,&fc1,&sh1,&fw1,&rh1);
  fclose(fp);

  fp = fopen("p2.key","rb");
  fscanf(fp,"%d %d %d %d %d %d %d %d %d %d %d",&st2,&up2,&dn2,&lf2,&rt2,&jb2,&sg2,&fc2,&sh2,&fw2,&rh2);
  fclose(fp);

  x = 160 - ((cs.cols/2)*width);

  play_midi(cs.bgtune,1);

  LOOP:
  delay(250);
  do {
    curr_port = screen_num*(cs.rows*cs.cols);
    draw_portrait(0,y,(port_ptr)&cs.bigpic,0);

    if(p1on) {
      if(cs.characters[p1id].hid == cs.characters[p1id].hidactive)
      {
        draw_portrait(0,0,(port_ptr)&left,0);
        draw_warrior(50,165,fset1.sprites[mset1.frames[mset1.sequences[0].moves[p1ctr]].fram_num],fset1.images[fset1.sprites[mset1.frames[mset1.sequences[0].moves[p1ctr]].fram_num].imag_num[0]],'n',0,0,'n');
        if(fset1.sprites[mset1.frames[mset1.sequences[0].moves[p1ctr]].fram_num].last_image)
        {
          draw_warrior(50,165,fset1.sprites[mset1.frames[mset1.sequences[0].moves[p1ctr]].fram_num],fset1.images[fset1.sprites[mset1.frames[mset1.sequences[0].moves[p1ctr]].fram_num].imag_num[1]],'n',1,0,'n');
        }
      }
      draw_string(0,170,(font_ptr)&bgfnt,p1name,'l',1);
      if(!p1done) p1ctr++;
      if(p1ctr > mset1.sequences[0].used) p1ctr = 0;
      }

    if(p2on) {
      if(cs.characters[p2id].hid == cs.characters[p2id].hidactive)
      {
        draw_portrait(320-right.width,0,(port_ptr)&right,1);
        draw_warrior(270,165,fset2.sprites[mset2.frames[mset2.sequences[0].moves[p2ctr]].fram_num],fset2.images[fset2.sprites[mset2.frames[mset2.sequences[0].moves[p2ctr]].fram_num].imag_num[0]],'h',0,0,'n');
        if(fset2.sprites[mset2.frames[mset2.sequences[0].moves[p2ctr]].fram_num].last_image)
        {
          draw_warrior(270,165,fset2.sprites[mset2.frames[mset2.sequences[0].moves[p2ctr]].fram_num],fset2.images[fset2.sprites[mset2.frames[mset2.sequences[0].moves[p2ctr]].fram_num].imag_num[1]],'h',1,0,'n');
        }
      }
      draw_string(320,170,(font_ptr)&bgfnt,p2name,'r',1);
      if(!p2done) p2ctr++;
      if(p2ctr > mset2.sequences[0].used) p2ctr = 0;
      }

    for(ctr=0;ctr<cs.rows;ctr++)
    {
      for(ctr2=0;ctr2<cs.cols;ctr2++)
      {
        if(curr_port <= cs.last_character)
        {
          if(cs.characters[curr_port].hid == cs.characters[curr_port].hidactive) draw_portrait(x+(ctr2*width),0+ctr*height,(port_ptr)&cs.characters[curr_port].port,0);
          curr_port++;
        }
      }
    }

    show_double_buffer(0,0,1);
    } while(!keys_active);

  if(key_table[MAKE_ESC]) return 0;

  if(key_table[MAKE_TAB])
  {
    screen_num++;
    if(screen_num > cs.last_character / (cs.rows*cs.cols)) screen_num = 0;
    if(!p1done)
    {
      p1id = screen_num * (cs.rows * cs.cols);
      if(cs.characters[p1id].hid == cs.characters[p1id].hidactive)
      {
        fp = fopen(cs.characters[p1id].idname1,"rb");
        fscanf(fp,"%s",&p1name);
        fscanf(fp,"%d",&type);
        fscanf(fp,"%s %s %s %s",&port,&bigp,&i,&s);
        kill_portrait((port_ptr)&left);
        kill_frames((fs_ptr)&fset1);
        get_portrait((port_ptr)&left,bigp);
        get_ide((fs_ptr)&fset1,i);
        get_re((fs_ptr)&fset1);
        get_seq((ms_ptr)&mset1,s);
        fclose(fp);
      }
      else strcpy(p1name,"UNKNOWN");
    }

    if(!p2done)
    {
      p2id = screen_num * (cs.rows * cs.cols);
      if(cs.characters[p2id].hid == cs.characters[p2id].hidactive)
      {
        fp = fopen(cs.characters[p2id].idname1,"rb");
        fscanf(fp,"%s",&p2name);
        fscanf(fp,"%d",&type);
        fscanf(fp,"%s %s %s %s",&port,&bigp,&i,&s);
        kill_portrait((port_ptr)&right);
        kill_frames((fs_ptr)&fset2);
        get_portrait((port_ptr)&right,bigp);
        get_ide((fs_ptr)&fset2,i);
        get_re((fs_ptr)&fset2);
        get_seq((ms_ptr)&mset2,s);
        fclose(fp);
      }
      else strcpy(p2name,"UNKNOWN");
    }

  }


  if(!p1on)
  {
    p1done = 0;
    if(key_table[st1])
    {
      p1on = 1;
      p1id = 0;
      p1last = 0;
      if(cs.characters[p1id].hid == cs.characters[p1id].hidactive)
      {
        fp = fopen(cs.characters[p1id].idname1,"rb");
        fscanf(fp,"%s",&p1name);
        fscanf(fp,"%d",&type);
        fscanf(fp,"%s %s %s %s",&port,&bigp,&i,&s);
        get_portrait((port_ptr)&left,bigp);
        get_ide((fs_ptr)&fset1,i);
        get_re((fs_ptr)&fset1);
        get_seq((ms_ptr)&mset1,s);
        fclose(fp);
      }
      else strcpy(p1name,"UNKNOWN");
    }
  }
  else
  {
    if(!p1done)
    {
      p1last = p1id;
      if(key_table[st1])
      {
        if(cs.characters[p1id].hid != cs.characters[p1id].hidactive) goto LOOP;
        if(!cs.characters[p1id].alt)
        {
          p1done = 1;
//        play_sample(systemsounds[0],sfxvolume,125,1000,0);
          if(p2done == p2on) goto DONE;
        }
        else
        {
          if(key_table[fc1])
          {
            p1done = 1;
            p1alt = 0;
            if(p2done == p2on) goto DONE;
          }
          else if(key_table[rh1])
          {
            p1done = 1;
            p1alt = 1;
            if(p2done == p2on) goto DONE;
          }
        }
      }
      else if(key_table[rt1])
      {
//        play_sample(systemsounds[3],sfxvolume,125,1000,0);
        if(p1id < cs.last_character) p1id++;
        else p1id = 0;
      }
      else if(key_table[lf1])
      {
//        play_sample(systemsounds[3],sfxvolume,125,1000,0);
        if(p1id > 0) p1id--;
        else p1id = cs.last_character;
      }
      else if(key_table[dn1])
      {
//        play_sample(systemsounds[3],sfxvolume,125,1000,0);
        if(p1id < cs.last_character) p1id += cs.cols;
        if(p1id > cs.last_character) p1id = cs.last_character;
      }
      else if(key_table[up1])
      {
//        play_sample(systemsounds[3],sfxvolume,125,1000,0);
        if(p1id > 0) p1id -= cs.cols;
        if(p1id < 0) p1id = 0;
      }
    }
    if(p1last != p1id)
    {
      if(cs.characters[p1id].hid == cs.characters[p1id].hidactive)
      {
        fp = fopen(cs.characters[p1id].idname1,"rb");
        fscanf(fp,"%s",&p1name);
        fscanf(fp,"%d",&type);
        fscanf(fp,"%s %s %s %s",&port,&bigp,&i,&s);
        kill_portrait((port_ptr)&left);
        kill_frames((fs_ptr)&fset1);
        get_portrait((port_ptr)&left,bigp);
        get_ide((fs_ptr)&fset1,i);
        get_re((fs_ptr)&fset1);
        get_seq((ms_ptr)&mset1,s);
        fclose(fp);
      }
      else strcpy(p1name,"UNKNOWN");
    }
  }


  if(!p2on)
  {
    p2done = 0;
    if(key_table[st2])
    {
      p2on = 1;
      p2id = 0;
      if(cs.characters[p2id].hid == cs.characters[p2id].hidactive)
      {
        fp = fopen(cs.characters[p2id].idname1,"rb");
        fscanf(fp,"%s",&p2name);
        fscanf(fp,"%d",&type);
        fscanf(fp,"%s %s %s %s",&port,&bigp,&i,&s);
        get_portrait((port_ptr)&right,bigp);
        get_ide((fs_ptr)&fset2,i);
        get_re((fs_ptr)&fset2);
        get_seq((ms_ptr)&mset2,s);
        fclose(fp);
      }
      else strcpy(p2name,"UNKNOWN");
    }
  }
  else {
    if(!p2done) {
      p2last = p2id;
      if(key_table[st2])
      {
        if(cs.characters[p2id].hid != cs.characters[p2id].hidactive) goto LOOP;
        if(!cs.characters[p2id].alt)
        {
          p2done = 1;
//        play_sample(systemsounds[0],sfxvolume,125,1000,0);
          if(p1done == p1on) goto DONE;
        }
        else
        {
          if(key_table[fc2])
          {
            p2done = 1;
            p2alt = 0;
            if(p1done == p1on) goto DONE;
          }
          else if(key_table[rh2])
          {
            p2done = 1;
            p2alt = 1;
            if(p1done == p1on) goto DONE;
          }
        }
      }
      else if(key_table[rt2]) {
//        play_sample(systemsounds[3],sfxvolume,125,1000,0);
        if(p2id < cs.last_character) p2id++;
        else p2id = 0;
        }
      else if(key_table[lf2]) {
//        play_sample(systemsounds[3],sfxvolume,125,1000,0);
        if(p2id > 0) p2id--;
        else p2id = cs.last_character;
        }
      else if(key_table[dn2]) {
//        play_sample(systemsounds[3],sfxvolume,125,1000,0);
        if(p2id < cs.last_character) p2id += cs.cols;
        if(p2id > cs.last_character) p2id = cs.last_character;
        }
      else if(key_table[up2]) {
//        play_sample(systemsounds[3],sfxvolume,125,1000,0);
        if(p2id > 0) p2id -= cs.cols;
        if(p2id < 0) p2id = 0;
        }
      if(p2last != p2id)
      {
        if(cs.characters[p2id].hid == cs.characters[p2id].hidactive)
        {
          fp = fopen(cs.characters[p2id].idname1,"rb");
          fscanf(fp,"%s",&p2name);
          fscanf(fp,"%d",&type);
          fscanf(fp,"%s %s %s %s",&port,&bigp,&i,&s);
          kill_portrait((port_ptr)&right);
          kill_frames((fs_ptr)&fset2);
          get_portrait((port_ptr)&right,bigp);
          get_ide((fs_ptr)&fset2,i);
          get_re((fs_ptr)&fset2);
          get_seq((ms_ptr)&mset2,s);
          fclose(fp);
        }
        else strcpy(p2name,"UNKNOWN");
      }
    }
  }
  goto LOOP;

  DONE:
  kill_portrait((port_ptr)&left);
  kill_portrait((port_ptr)&right);

  if(p1on)
  {
    if(p1alt) strcpy(p1,cs.characters[p1id].idname2);
    else strcpy(p1,cs.characters[p1id].idname1);
  }
  else strcpy(p1,cs.characters[rand() % cs.last_character].idname1);

  if(p2on)
  {
    if(p2alt) strcpy(p2,cs.characters[p2id].idname2);
    else strcpy(p2,cs.characters[p2id].idname1);
  }
  else strcpy(p2,cs.characters[rand() % cs.last_character].idname1);

  returnval = 0;
  if(p1on) returnval = 1;
  if(p2on) returnval = 2;
  if(p1on && p2on) returnval = 3;
  return returnval;
  }

int options_menu() {
  char strings[11][25];
//  char strings[5][25];
  int val=0;
  int y;
  int ctr;
  int rad = 0;
  int menuctr;
  char sfxvol[10];
  char midvol[10];

  strcpy(strings[0],"Current Speed");
  strcpy(strings[1],"SFX Volume");
  strcpy(strings[2],"MIDI Volume");
  strcpy(strings[3],"Juggling");
  strcpy(strings[4],"Dramatic Combos");
  strcpy(strings[5],"Centered Text");
  strcpy(strings[6],"Super Shadows");
  strcpy(strings[7],"Rounds per fight");
  strcpy(strings[8],"Shadow Delay");
  strcpy(strings[9],"Map left player");
  strcpy(strings[10],"Map right player");

  LOOP:
  do {
    draw_string(0,0,(font_ptr)&fnt,"OPTIONS MENU",'l',1);
    draw_string(0,fnt.letheight,(font_ptr)&fnt,"USE PLUS OR MINUS",'l',1);
    draw_string(0,200-fnt.letheight,(font_ptr)&fnt,"PRESS ESC TO EXIT",'l',1);
    for(menuctr=0;menuctr<11;menuctr++) {
      draw_string(20,75+menuctr*fnt.letheight,(font_ptr)&fnt,strings[menuctr],'l',1);
      }
    draw_num(320,75,(font_ptr)&fnt,speed,'r',1);
    if(sfxvolume < 100) strcpy(sfxvol,"off");
    else if(sfxvolume == 100) strcpy(sfxvol,"low");
    else if(sfxvolume == 200) strcpy(sfxvol,"high");
    draw_string(320,75+fnt.letheight,(font_ptr)&fnt,sfxvol,'r',1);
    if(midvolume < 100) strcpy(midvol,"off");
    else if(midvolume == 100) strcpy(midvol,"low");
    else if(midvolume == 200) strcpy(midvol,"high");
    draw_string(320,75+2*fnt.letheight,(font_ptr)&fnt,midvol,'r',1);
    if(juggling) draw_string(320,75+3*fnt.letheight,(font_ptr)&fnt,"on",'r',1);
    else draw_string(320,75+3*fnt.letheight,(font_ptr)&fnt,"off",'r',1);
    if(drama) draw_string(320,75+4*fnt.letheight,(font_ptr)&fnt,"on",'r',1);
    else draw_string(320,75+4*fnt.letheight,(font_ptr)&fnt,"off",'r',1);
    if(centext) draw_string(320,75+5*fnt.letheight,(font_ptr)&fnt,"on",'r',1);
    else draw_string(320,75+5*fnt.letheight,(font_ptr)&fnt,"off",'r',1);
    draw_num(320,75+6*fnt.letheight,(font_ptr)&fnt,shadcnt,'r',1);
    draw_num(320,75+7*fnt.letheight,(font_ptr)&fnt,maxrounds,'r',1);
    draw_num(320,75+8*fnt.letheight,(font_ptr)&fnt,shadowdelay,'r',1);
//    if(noleg) draw_string(320,75+6*fnt.letheight,(font_ptr)&fnt,"on",'r',1);
//    else draw_string(320,75+6*fnt.letheight,(font_ptr)&fnt,"off",'r',1);

    if(rad<5) rad++;
    else rad = 0;
    circle_b(5,75+(fnt.letheight/2)+(val*fnt.letheight),255,rad);
    show_double_buffer(0,0,1);
    set_volume(sfxvolume,midvolume);
    } while(!keys_active);

  if(key_table[MAKE_UP]) {
//    play_sample(systemsounds[3],sfxvolume,125,1000,0);
    do {
      } while(keys_active);
    if(val > 0) val--;
    }
  else if(key_table[MAKE_DOWN]) {
//    play_sample(systemsounds[3],sfxvolume,125,1000,0);
    do {
      } while(keys_active);
    if(val < 10) val++;
    }
  else if(key_table[MAKE_KEYPAD_PLUS] || key_table[MAKE_EQUALS]) {
    do {
      } while(keys_active);
    switch(val) {
      case 0:  speed++;
               goto LOOP;
               break;
      case 1:  if(sfxvolume < 200) sfxvolume += 100;
               goto LOOP;
               break;
      case 2:  if(midvolume < 200) midvolume += 100;
               goto LOOP;
               break;
      case 3:  if(juggling < 1) juggling++;
               goto LOOP;
               break;
      case 4:  if(drama < 1) drama++;
               goto LOOP;
               break;
      case 5:  if(centext < 1) centext++;
               goto LOOP;
               break;
      case 6:  shadcnt++;
               if(shadcnt>99) shadcnt=1;
               goto LOOP;
               break;
      case 7:  maxrounds++;
               if(maxrounds>99) maxrounds=1;
               goto LOOP;
               break;
      case 8:  shadowdelay++;
               if(shadowdelay>shadcnt) shadowdelay=1;
               goto LOOP;
               break;
      case 9:  map_controls(1);
               goto LOOP;
               break;
      case 10: map_controls(2);
               goto LOOP;
               break;
      }
    }
  else if(key_table[MAKE_KEYPAD_MINUS] || key_table[MAKE_MINUS]) {
    do {
      } while(keys_active);
    switch(val) {
      case 0:  if(speed>0) speed--;
               goto LOOP;
               break;
      case 1:  if(sfxvolume >= 100) sfxvolume -= 100;
               goto LOOP;
               break;
      case 2:  if(midvolume >= 100) midvolume -= 100;
               goto LOOP;
               break;
      case 3:  if(juggling > 0) juggling--;
               goto LOOP;
               break;
      case 4:  if(drama > 0) drama--;
               goto LOOP;
               break;
      case 5:  if(centext > 0) centext--;
               goto LOOP;
               break;
      case 6:  shadcnt--;
               if(shadcnt<1) shadcnt=99;
               goto LOOP;
               break;
      case 7:  maxrounds--;
               if(maxrounds<1) maxrounds=99;
               goto LOOP;
               break;
      case 8:  shadowdelay--;
               if(shadowdelay<1) shadowdelay = shadcnt;
               goto LOOP;
               break;
      }
    }
  else if(key_table[MAKE_ESC]) goto EXIT;
  goto LOOP;



  EXIT:
  FILE *fp;
  if((fp = fopen("options.opt","wt")) == NULL) {
    return 0;
    }
  fprintf(fp,"%d %d %d %d %d %d %d %d %d %d",speed,sfxvolume,midvolume,juggling,drama,centext,noleg,shadcnt,maxrounds,shadowdelay);
  fclose(fp);
  return 1;

  }

int pausemenu()
{
//  play_sample(systemsounds[2],sfxvolume,125,1000,0);
  do
  {
  }while(keys_active);

  char strings[4][25];
  int val=0;
  int rad=0;

  strcpy(strings[0],"Modify Options");
  strcpy(strings[1],"Return to Fight");
  strcpy(strings[2],"Quit Fight");

  START:

  do {
    draw_string(0,0,(font_ptr)&bgfnt,"Pause Menu",'l',1);
    draw_string(0,bgfnt.letheight,(font_ptr)&bgfnt,"ESC to Return",'l',1);
/*    for(menuctr=0;menuctr<9;menuctr++) {
      draw_string(20,75+menuctr*fnt.letheight,(font_ptr)&fnt,strings[menuctr],'l',1);
      }*/
    for(int ctr=0;ctr<3;ctr++) {
      draw_string(20,75+ctr*fnt.letheight,(font_ptr)&fnt,strings[ctr],'l',1);
      //else if(abs(ctr-val) == 1) draw_string(75,100+(ctr-val)*bgfnt.letheight,(font_ptr)&fnt,strings[ctr],'l',1);
      }

    if(rad<5) rad++;
    else rad = 0;

    circle_b(5,75+(fnt.letheight/2)+(val*fnt.letheight),255,rad);
    show_double_buffer(0,0,1);

    }while(!keys_active);

  if(key_table[MAKE_UP])
  {
//    play_sample(systemsounds[3],sfxvolume,125,1000,0);
    do {
      }while(keys_active);
    if(val>0) val--;
    goto START;
  }
  else if(key_table[MAKE_DOWN])
  {
//    play_sample(systemsounds[3],sfxvolume,125,1000,0);
    do {
      }while(keys_active);
    if(val<2) val++;
    goto START;
    }
  else if(key_table[MAKE_ENTER])
  {
    do {
      }while(keys_active);
    switch(val)
    {
      case 0:  options_menu();
               goto START;
               break;
      case 1:  return 0;
      case 2:  return 1;
    }
  }
  else if(key_table[MAKE_ESC])
  {
    do {
    }while(keys_active);
    return 0;
  }
  else goto START;

  return 1;
}

int single_match(char idname1[25],char idname2[25],int active) {
  static warrior player1;
  player1.setup();
  player1.get2(idname1);
  player1.import_controls("p1.key");
  static warrior player2;
  player2.setup();
  player2.get2(idname2);
  player2.import_controls("p2.key");

  static background bg;
  static portrait left,right;
  static interface face;


  int copy = 0;
  //int bgoff;
  int vgoff;
  int loop;
  int slowctr;
  int ai = 1;
  int returnval=0;
  char winquote1[99];
  char winquote2[99];

  strcpy(winquote1,"NOQUOTE");
  strcpy(winquote2,"NOQUOTE");

  int maxloops=100;
  if(!strcmp(idname1,idname2)) copy = 1;
  int round=1;
  int cpu = 0;//stuff;



  int p1=0,p2=0;
  int whofirst=0;
  char name[25];
  int type;
  int super_killed = 0;
  int p1kill = 0;
  int p2kill = 0;
  char p[25];
  char bigp[25];

  MIDI *bgmusic;
  SAMPLE *bgsamp;
  FILE *fp;

  fp = fopen(idname1,"rb");
  fscanf(fp,"%s",&name);
  fscanf(fp,"%d",&type);
  fscanf(fp,"%s %s",&p,&bigp);
  get_portrait((port_ptr)&left,bigp);
  fclose(fp);

  fp = fopen(idname2,"rb");
  fscanf(fp,"%s",&name);
  fscanf(fp,"%d",&type);
  fscanf(fp,"%s %s",&p,&bigp);
  get_portrait((port_ptr)&right,bigp);
  fclose(fp);
  int temp=0;
  char sdk[99];
  int pause;

  WHO:

  if(active == 1) {
    strcpy(sdk,player2.music);
    bg.get(player2.bgname);
    p2 = 1;
    }
  else if(active == 2) {
    strcpy(sdk,player1.music);
    bg.get(player1.bgname);
    p1 = 1;
    }
  else if(active == 0) {
    p1 = 1;
    p2 = 1;
    active = rand() % 2+1;
    goto WHO;
    }
  else if(active == 3) {
    temp = rand() % 2;

    if(temp) {
      strcpy(sdk,player2.music);
      bg.get(player2.bgname);
      }
    else {
      strcpy(sdk,player1.music);
      bg.get(player1.bgname);
      }
    }

  bgmusic = load_midi(sdk);
  play_midi(bgmusic,1);
  int textpos = width/2 + 200;

  do {
    clear_screen();
    yoffset = height - 200;
    player1.init(0,height-10,width/2 - 50,0);
    player2.init(1,height-10,width/2 + 50,copy);
    player1.data.life = 100;
    player2.data.life = 100;
    xoffset = (width / 2) - 160;
    textpos = xoffset+420;

    loop=0;
    if(round == 1) {
      if(rand() % 100 < 50) {
        yoffset = 0;
        do {
          bg.update((info_ptr)&player1.data,(info_ptr)&player2.data,0);
          for(slowctr=0;slowctr<speed;slowctr++) wait4vsync();
          show_double_buffer(xoffset,yoffset,1);
          yoffset++;
          if(key_table[MAKE_ESC]) {
            yoffset = height - 200;
            }
          } while(yoffset < height - 200);
        }

      yoffset = height - 200;
      do {
        bg.update((info_ptr)&player1.data,(info_ptr)&player2.data,0);
        player1.update(0,p1,(info_ptr)&player2.data);
        player2.update(0,p2,(info_ptr)&player1.data);
        for(slowctr=0;slowctr<speed;slowctr++) wait4vsync();
        show_double_buffer(xoffset,yoffset,1);
        } while(player1.data.curr_seq != 0 || player2.data.curr_seq != 0);
      }

    do {
      bg.update((info_ptr)&player1.data,(info_ptr)&player2.data,0);
      player1.update(0,p1,(info_ptr)&player2.data);
      player2.update(0,p2,(info_ptr)&player1.data);
      face.update(player1.data,player2.data);
      if(centext) draw_string(xoffset+160,yoffset+100,(font_ptr)&bgfnt,"ROUND",'c',1);
      else draw_string(textpos,yoffset+100,(font_ptr)&bgfnt,"ROUND",'l',1);
      if(centext) draw_num(xoffset+160,yoffset+100+bgfnt.letheight,(font_ptr)&bgfnt,round,'c',1);
      draw_num(textpos+6*bgfnt.letwidth,yoffset+100,(font_ptr)&bgfnt,round,'l',1);
      for(slowctr=0;slowctr<speed;slowctr++) wait4vsync();
      show_double_buffer(xoffset,yoffset,1);
      textpos-=20;
      } while(textpos>xoffset-100);

    do {
      bg.update((info_ptr)&player1.data,(info_ptr)&player2.data,0);
      player1.update(0,p1,(info_ptr)&player2.data);
      player2.update(0,p2,(info_ptr)&player1.data);
      face.update(player1.data,player2.data);
      if(centext) draw_string(xoffset+160,yoffset+100,(font_ptr)&bgfnt,"FIGHT",'l',1);
      else draw_string(textpos,yoffset+100,(font_ptr)&bgfnt,"FIGHT",'l',1);
      for(slowctr=0;slowctr<speed;slowctr++) wait4vsync();
      show_double_buffer(xoffset,yoffset,1);
      textpos+=20;
      } while(textpos<xoffset+320);

    do
    {
      if(player1.data.obox.active) whofirst = 0;
      if(player2.data.obox.active) whofirst = 1;
      bg.update((info_ptr)&player1.data,(info_ptr)&player2.data,0);
      if(whofirst) {
        player1.update(1,p1,(info_ptr)&player2.data);
        player2.update(1,p2,(info_ptr)&player1.data);
        }
      else {
        player2.update(1,p2,(info_ptr)&player1.data);
        player1.update(1,p1,(info_ptr)&player2.data);
        }
      face.update(player1.data,player2.data);
      for(slowctr=0;slowctr<speed;slowctr++) wait4vsync();
      show_double_buffer(xoffset,yoffset,1);
      if(key_table[MAKE_SPACE])
      {
        do
        {
        }while(keys_active);
        do
        {
        }while(!key_table[MAKE_SPACE]);
      }

      if(key_table[MAKE_ESC])
      {
        pause = pausemenu();
        if(pause)
        {
          destroy_midi(bgmusic);
          return 0;
        }
        player1.import_controls("p1.key");
        player2.import_controls("p2.key");
      }
    } while(player1.data.alive && player2.data.alive);

    super_killed = 0;

    if(player1.data.super_kill || player2.data.super_kill)
    {
      super_killed=1;
      if(player1.data.super_kill) p1kill=1;
      else p1kill = 0;
      if(player2.data.super_kill) p2kill=1;
      else p2kill = 0;
      textpos = xoffset+320;
      do
      {
        bg.update((info_ptr)&player1.data,(info_ptr)&player2.data,1);
        if(whofirst)
        {
          player1.update(1,p1,(info_ptr)&player2.data);
          player2.update(1,p2,(info_ptr)&player1.data);
        }
        else
        {
          player2.update(1,p2,(info_ptr)&player1.data);
          player1.update(1,p1,(info_ptr)&player2.data);
        }

        if(super_killed)
        {
          if(p1kill)
          {
            if(strcmp(player1.data.super_name,"NONAME"))
            {
              draw_string(xoffset+textpos,50+yoffset,(font_ptr)&hugefnt,player1.data.super_name,'l',1);
              draw_string(xoffset+textpos,50+yoffset+hugefnt.letheight,(font_ptr)&hugefnt,player1.data.super_name,'l',1);
              draw_string(xoffset+textpos,50+yoffset+hugefnt.letheight*2,(font_ptr)&hugefnt,player1.data.super_name,'l',1);
            }
          }
          if(p2kill)
          {
            if(strcmp(player2.data.super_name,"NONAME"))
            {
              draw_string(xoffset+textpos,50+yoffset,(font_ptr)&hugefnt,player2.data.super_name,'l',1);
              draw_string(xoffset+textpos,50+yoffset+hugefnt.letheight,(font_ptr)&hugefnt,player2.data.super_name,'l',1);
              draw_string(xoffset+textpos,50+yoffset+hugefnt.letheight*2,(font_ptr)&hugefnt,player2.data.super_name,'l',1);
            }
          }
        }
        for(slowctr=0;slowctr<speed*2;slowctr++) wait4vsync();
        show_double_buffer(xoffset,yoffset,0);
        textpos-=20;
      } while(((player1.data.curr_seq != 43 && player2.data.curr_seq != 43) || (player1.data.super_kill || player2.data.super_kill)) && (!key_table[MAKE_ESC]));
    }

//    play_sample(systemsounds[1],sfxvolume,125,1000,0);

    do {
      bg.update((info_ptr)&player1.data,(info_ptr)&player2.data,0);
      if(whofirst)
      {
        player1.update(1,p1,(info_ptr)&player2.data);
        player2.update(1,p2,(info_ptr)&player1.data);
      }
      else
      {
        player2.update(1,p2,(info_ptr)&player1.data);
        player1.update(1,p1,(info_ptr)&player2.data);
      }
      face.update(player1.data,player2.data);
      if(player1.data.curr_seq == 43) {
        draw_string(xoffset+130,yoffset+50,(font_ptr)&bgfnt,player2.data.name,'l',1);
        }
      else if(player2.data.curr_seq == 43) {
        draw_string(xoffset+130,yoffset+50,(font_ptr)&bgfnt,player1.data.name,'l',1);
        }
      else if(player1.data.curr_seq == 43 && player2.data.curr_seq == 43) draw_string(xoffset+130,yoffset+50,(font_ptr)&bgfnt,"NO",'l',1);
      if(player1.data.curr_seq == 43 || player2.data.curr_seq == 43) draw_string(xoffset+130,yoffset+75,(font_ptr)&bgfnt,"WINS",'l',1);
      if(super_killed)
      {
        if(p1kill)
        {
          if(strcmp(player1.data.super_name,"NONAME"))
          {
            draw_string(xoffset+textpos,50+yoffset,(font_ptr)&hugefnt,player1.data.super_name,'l',1);
            draw_string(xoffset+textpos,50+yoffset+hugefnt.letheight,(font_ptr)&hugefnt,player1.data.super_name,'l',1);
            draw_string(xoffset+textpos,50+yoffset+hugefnt.letheight*2,(font_ptr)&hugefnt,player1.data.super_name,'l',1);
          }
        }
        if(p2kill)
        {
          if(strcmp(player2.data.super_name,"NONAME"))
          {
            draw_string(xoffset+textpos,50+yoffset,(font_ptr)&hugefnt,player2.data.super_name,'l',1);
            draw_string(xoffset+textpos,50+yoffset+hugefnt.letheight,(font_ptr)&hugefnt,player2.data.super_name,'l',1);
            draw_string(xoffset+textpos,50+yoffset+hugefnt.letheight*2,(font_ptr)&hugefnt,player2.data.super_name,'l',1);
          }
        }
      }
      for(slowctr=0;slowctr<speed;slowctr++) wait4vsync();
      show_double_buffer(xoffset,yoffset,1);
      loop++;
      textpos-=20;

      } while(loop < maxloops);

    round++;
    } while(player1.data.wins<maxrounds && player2.data.wins<maxrounds);

  loop = 0;

  if(player1.kset.lastquote > 0) strcpy(winquote1,player1.kset.quotes[rand() % player1.kset.lastquote]);
  if(player2.kset.lastquote > 0) strcpy(winquote2,player2.kset.quotes[rand() % player2.kset.lastquote]);
//  play_sample(systemsounds[5],sfxvolume,125,1000,0);

  do {
    bg.update((info_ptr)&player1.data,(info_ptr)&player2.data,0);
    if(player1.data.wins == maxrounds) {
      player1.update(1,p1,(info_ptr)&player2.data);
      draw_portrait(xoffset,yoffset+100-(left.height/2),(port_ptr)&left,0);
      draw_string(xoffset+130,yoffset+50,(font_ptr)&bgfnt,player1.data.name,'l',1);
      draw_string(xoffset+130,yoffset+75,(font_ptr)&bgfnt,"WINS",'l',1);
      draw_string(xoffset,yoffset,(font_ptr)&fnt,winquote1,'l',1);
      if((player1.data.p[0] - xoffset) > 160) {
        if(xoffset < 200) xoffset++;
        }
      else if((player1.data.p[0] - xoffset) < 160) {
        if(xoffset > 0) xoffset--;
        }
      }
    if(player2.data.wins == maxrounds) {
      player2.update(1,p2,(info_ptr)&player1.data);
      draw_portrait(xoffset+(320-right.width),yoffset+100-(right.height/2),(port_ptr)&right,1);
      draw_string(xoffset+130,yoffset+50,(font_ptr)&bgfnt,player2.data.name,'l',1);
      draw_string(xoffset+130,yoffset+75,(font_ptr)&bgfnt,"WINS",'l',1);
      draw_string(xoffset,yoffset,(font_ptr)&fnt,winquote2,'l',1);
      if((player2.data.p[0] - xoffset) > 160) {
        if(xoffset < 200) xoffset++;
        }
      else if((player2.data.p[0] - xoffset) < 160) {
        if(xoffset > 0) xoffset--;
        }
      }
    if(key_table[MAKE_ESC]) {
      loop = 300;
      }
    show_double_buffer(xoffset,yoffset,1);
    loop++;
    } while(loop < 300);

  destroy_midi(bgmusic);
//  destroy_midi(bgmusic);
  if(player1.data.wins == maxrounds) returnval = 1;
  if(player2.data.wins == maxrounds) returnval = 2;
  if(player1.data.wins == maxrounds && player2.data.wins == maxrounds) returnval = 3;
  return returnval;
  }

int countdown(char idname[25]) {
  FILE *fp;
  }

int exhibition_mode(char *config) {
  FILE *fp;
  FILE *op;
  char name[25];
  char yourname[25];
  portrait port[2];
  char idname1[25];
  char idname2[25];
  char guy[25];
  char p[25];//[2];
  char i[25];//[2];
  char s[25];//[2];
  char k[25];//[2];
  char b[25];//[2];
  char m[25];
  char bigp[25];
  int curr_opponent=0;
  int last_opponent=0;
  char victim[25][20];
  char him[25];
  char all[120][25];
  int curr_all=0;
  int last_all=0;
  char trash[25];
  int winner=1;
  int type[2];
  int fightcount=0;
  int who;
  char bgpicture[25];
  char bgmusic[25];
  int rows,cols;
  int ctr;

  WHO:
  who = gfx_player_select(idname1,idname2,b,config);

  if(who == 1) strcpy(guy,idname1);
  else if(who == 2) strcpy(guy,idname2);
  else if(who == 3)
  {
    who = single_match(idname1,idname2,3);
    if(who) goto WHO;
    else return 1;
  }

  if((fp = fopen(guy,"rb")) == NULL)
  {
    printf("%s",&guy);
    alert_error("Could not open this character.");
    return 0;
  }

//  strcpy(guy,cs.characters[rand() % cs.last_character].idname1);

  fscanf(fp,"%s",&yourname);

  fscanf(fp,"%d",&type[0]);

  fscanf(fp,"%s %s %s %s %s %s %s",&p,&bigp,&i,&s,&k,&b,&m);

  get_portrait((port_ptr)&port[0],bigp);

  while(winner != 0)
  {
    strcpy(him,cs.characters[rand() % cs.last_character].idname1);
    clear_screen();
    kill_portrait((port_ptr)&port[1]);


    op = fopen(him,"rb");
    fscanf(op,"%s",&name);
    fscanf(op,"%d",&type[1]);
    fscanf(op,"%s %s %s %s %s %s",&p,&bigp,&i,&s,&k,&b);
    fclose(op);

    get_portrait((port_ptr)&port[1],bigp);

    if(who == 1)
    {
      draw_portrait(0,100-(port[0].height/2),(port_ptr)&port[0],0);
      draw_portrait(320-port[1].width,100-(port[1].height/2),(port_ptr)&port[1],1);
      draw_string(0,150,(font_ptr)&bgfnt,yourname,'l',1);
      draw_string(140,150,(font_ptr)&bgfnt,"VS",'l',1);
      draw_string(320,150,(font_ptr)&bgfnt,name,'r',1);
      }
    else if(who == 2) {
      draw_portrait(0,100-(port[1].height/2),(port_ptr)&port[1],0);
      draw_portrait(320-port[0].width,100-(port[0].height/2),(port_ptr)&port[0],1);
      draw_string(0,150,(font_ptr)&bgfnt,name,'l',1);
      draw_string(140,150,(font_ptr)&bgfnt,"VS",'l',1);
      draw_string(320,150,(font_ptr)&bgfnt,yourname,'r',1);
      }

    show_double_buffer(0,0,1);

    delay(1000);

    if(who == 1) {
      winner = single_match(guy,him,who);
      }
    else if(who == 2) {
      winner = single_match(him,guy,who);
      }

    if(winner == 0) return 1;
    if(winner==who) ++curr_opponent;
    }

  kill_portrait((port_ptr)&port[0]);
  kill_portrait((port_ptr)&port[1]);

  return 1;
  }

int scene_handler(char *filename)
{
  FILE *fp;
  portrait scene;
  char scenename[25];
  char string[99];
  int pause;
  int numscenes;
  int numstrings;
  int ctr,ctr2;

  if((fp = fopen(filename,"rb")) == NULL) return 0;

  fscanf(fp,"%d",&pause);
  fscanf(fp,"%d",&numscenes);

  for(ctr=0;ctr<numscenes;ctr++)
  {
    fscanf(fp,"%s",&scenename);
    get_portrait((port_ptr)&scene,scenename);
    fscanf(fp,"%d",&numstrings);
    for(ctr2=0;ctr2<numstrings;ctr2++)
    {
      fscanf(fp,"%s",&string);
      draw_portrait(160 - (scene.width/2),0,(port_ptr)&scene,0
      );
      draw_string(320,scene.height + ((200 - scene.height) / 2),(font_ptr)&bgfnt,string,'r',1);
      show_double_buffer(0,0,1);
      delay(pause*10);
    }
    delay(pause*10);
    kill_portrait((port_ptr)&scene);
  }

  delay(pause*pause);

  fclose(fp);
  return 1;
}

int tournament_mode(char *config) {
  FILE *fp;
  FILE *op;
  char name[25];
  char yourname[25];
  portrait port[2];
  char idname1[25];
  char idname2[25];
  char guy[25];
  char p[25];//[2];
  char i[25];//[2];
  char s[25];//[2];
  char k[25];//[2];
  char b[25];//[2];
  char m[25];
  char bigp[25];
  int curr_opponent=0;
  int last_opponent=0;
  char victim[25][20];
  char him[25];
  char all[120][25];
  int curr_all=0;
  int last_all=0;
  char trash[25];
  int winner=1;
  int type[2];
  int fightcount=0;
  int who;
  char bgpicture[25];
  char bgmusic[25];
  int rows,cols;
  int ctr;
  char getex;
  char ext[4];
  int ir;

//  modes_select(player1, player2);

  WHO:

  who = gfx_player_select(idname1,idname2,b,config);

  if(who == 3)
  {
    who = single_match(idname1,idname2,3);
    if(who) goto WHO;
    else return 1;
  }

  strcpy(guy,cs.characters[rand() % cs.last_character].idname1);

  if((fp = fopen(guy,"rb")) == NULL)
  {
    printf("I'm afraid %s doesn't exist. . .",guy);
    return 0;
  }

  fscanf(fp,"%s",&yourname);

  fscanf(fp,"%d",&type[0]);


  fscanf(fp,"%s %s %s %s %s %s %s",&p,&bigp,&i,&s,&k,&b,&m);

  get_portrait((port_ptr)&port[0],bigp);

  fscanf(fp,"%s",&victim[last_opponent]);
  while(strcmp(victim[last_opponent],"ending")) {
    ++last_opponent;
    fscanf(fp,"%s",victim[last_opponent]);
    }

  fclose(fp);

  while(strcmp(victim[curr_opponent],"ending")) {
    clear_screen();
    if(!strcmp(victim[curr_opponent],"%rand%")) {
      CHECK:
      if(winner==who) strcpy(him,cs.characters[rand() % cs.last_character].idname1);
      for(ctr=0;ctr<last_opponent;ctr++) {
        if(!strcmp(victim[ctr],him)) goto CHECK;
        }
      }
    else
    {
      strcpy(him,victim[curr_opponent]);
      ir=0;
      getex = 'n';
      while(getex != '.')
      {
        getex=him[ir++];
      }
      ext[0]=him[ir++];
      ext[1]=him[ir++];
      ext[2]=him[ir++];
      ext[3]=NULL;

      if(!strcmp(ext,"scn"))
      {
        scene_handler(him);
        goto BOTTOM;
      }
    }

    kill_portrait((port_ptr)&port[1]);


    op = fopen(him,"rb");
    fscanf(op,"%s",&name);
    fscanf(op,"%d",&type[1]);
    fscanf(op,"%s %s %s %s %s %s",&p,&bigp,&i,&s,&k,&b);
    fclose(op);

    get_portrait((port_ptr)&port[1],bigp);
//    play_sample(systemsounds[4],sfxvolume,125,1000,0);


    if(who == 1) {
      draw_portrait(0,100-(port[0].height/2),(port_ptr)&port[0],0);
      draw_portrait(320-port[1].width,100-(port[1].height/2),(port_ptr)&port[1],1);
      draw_string(0,150,(font_ptr)&bgfnt,yourname,'l',1);
      draw_string(140,150,(font_ptr)&bgfnt,"VS",'l',1);
      draw_string(320,150,(font_ptr)&bgfnt,name,'r',1);
      }
    else if(who == 2) {
      draw_portrait(0,100-(port[1].height/2),(port_ptr)&port[1],0);
      draw_portrait(320-port[0].width,100-(port[0].height/2),(port_ptr)&port[0],1);
      draw_string(0,150,(font_ptr)&bgfnt,name,'l',1);
      draw_string(140,150,(font_ptr)&bgfnt,"VS",'l',1);
      draw_string(320,150,(font_ptr)&bgfnt,yourname,'r',1);
      }

    show_double_buffer(0,0,1);

    delay(1000);

    if(who == 1) {
      winner = single_match(guy,him,who);
      }
    else if(who == 2) {
      winner = single_match(him,guy,who);
      }

    BOTTOM:

    if(winner == 0) return 0;
    if(winner==who) ++curr_opponent;
    }

  fp = fopen("hid.den","at");
  fprintf(fp,"%s\n",guy);
  fclose(fp);


  kill_portrait((port_ptr)&port[0]);
  kill_portrait((port_ptr)&port[1]);
  return 1;
  }
