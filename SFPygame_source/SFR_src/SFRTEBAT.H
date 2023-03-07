#include <sfrwfite.h>

struct hidden {
  char who[25];
  char him[25];
  int xpos;
  int ypos;
  int active;
  portrait pic;
  };

int story_select(char *p1, char *p2, char *bg, char config[25]) {
  int st1, up1, dn1, lf1, rt1;
  int st2, up2, dn2, lf2, rt2;
  portrait left, right;
  char bigp[25];
  char ids[99][25];
  portrait pix[99];
  int last_id, p1id=0, p2id=0;
  int p1on=0, p2on=0;
  int p1last=0, p2last=0;
  int p1done=0, p2done=0;
  char p1name[25],p2name[25];

  char bgpicture[25];
  portrait bigpic;
  char bgmusic[25];
  MIDI *bgtune;
  int rows,cols;
  int ctr=0,ctr2=0;
  FILE *fp;
  FILE *fp2;
  int height=0,width=0;
  int x,y;
  int bgy;
  char port[25];
  int type;
  char i[25];
  char s[25];
  char k[25];
  char b[25];
  int returnval;
  int p1ctr=0,p2ctr=0;
  static frameset fset1,fset2;
  static moveset mset1,mset2;
  hidden hiddens[20];
  int hidctr = 0;
  for(ctr=0;ctr<20;ctr++) {
    hiddens[ctr].active = 0;
    }
  char temp[25];


  if((fp = fopen("te.cfg","rb")) == NULL) {
    printf("No te.cfg\nRun te.exe\n");
    return 0;
    }

  last_id = fgetc(fp);

  //last_id -= 1;


  fclose(fp);

  if((fp = fopen(config,"rb")) == NULL) {
    printf("Could not open config file:\n%s",config);
    return 0;
    }

  fscanf(fp,"%s",&bgpicture);
  get_portrait((port_ptr)&bigpic,bgpicture);
  bgy = 100 - (bigpic.height/2);

  fscanf(fp,"%s",&bgmusic);
  bgtune = load_midi(bgmusic);

  fscanf(fp,"%d %d",&x,&y);
  fscanf(fp,"%d %d",&rows,&cols);

  for(ctr=0;ctr<last_id;ctr++) {
    fscanf(fp,"%s",&ids[ctr]);
    if((fp2 = fopen(ids[ctr],"rb")) == NULL) {
      printf("Couldn't open %s",ids[ctr]);
      return 0;
      }
    fscanf(fp2,"%s",&p1name);
    fscanf(fp2,"%d",&type);
    fscanf(fp2,"%s",&port);
    get_portrait((port_ptr)&pix[ctr],port);
    fclose(fp2);

    if(width<pix[ctr].width) width = pix[ctr].width;
    if(height<pix[ctr].height) height = pix[ctr].height;
    }


  fscanf(fp,"%s",&temp);
  while(strcmp(temp,"end")) {
    strcpy(hiddens[hidctr].him,temp);
    fp2 = fopen("hid.den","rb");
    while(!feof(fp2)) {
      fscanf(fp2,"%s",&temp);
      if(!strcmp(temp,hiddens[hidctr].him)) hiddens[hidctr].active = 1;
      }
    fclose(fp2);
    fscanf(fp,"%s",&hiddens[hidctr].who);
    if((fp2 = fopen(hiddens[hidctr].who,"rb")) == NULL) {
      printf("Couldn't open %s",hiddens[hidctr].who);
      return 0;
      }
    fscanf(fp2,"%s",&p1name);
    fscanf(fp2,"%d",&type);
    fscanf(fp2,"%s",&port);
    get_portrait((port_ptr)&hiddens[hidctr].pic,port);
    fclose(fp2);
    fscanf(fp,"%d %d",&hiddens[hidctr].xpos,&hiddens[hidctr].ypos);
    hidctr++;
    fscanf(fp,"%s",&temp);
    }

  fclose(fp);

  p1id = rand() % last_id;
  p2id = rand() % last_id;

  if((fp = fopen("p1.key","rb")) == NULL) {
    printf("Couldn't open p1.key\n");
    return 0;
    }
  fscanf(fp,"%d %d %d %d %d",&st1,&up1,&dn1,&lf1,&rt1);
  fclose(fp);

  if((fp = fopen("p2.key","rb")) == NULL) {
    printf("Couldn't open p2.key\n");
    return 0;
    }
  fscanf(fp,"%d %d %d %d %d",&st2,&up2,&dn2,&lf2,&rt2);
  fclose(fp);

  play_midi(bgtune,1);

  LOOP:
  delay(250);
  do {
    draw_portrait(0,bgy,(port_ptr)&bigpic,0);

    if(p1on) {
      draw_portrait(0,0,(port_ptr)&left,0);
      draw_warrior(50,165,fset1.sprites[mset1.frames[mset1.sequences[0].moves[p1ctr]].fram_num],fset1.images[fset1.sprites[mset1.frames[mset1.sequences[0].moves[p1ctr]].fram_num].imag_num[0]],'n',0,0);
      if(fset1.sprites[mset1.frames[mset1.sequences[0].moves[p1ctr]].fram_num].last_image) {
        draw_warrior(50,165,fset1.sprites[mset1.frames[mset1.sequences[0].moves[p1ctr]].fram_num],fset1.images[fset1.sprites[mset1.frames[mset1.sequences[0].moves[p1ctr]].fram_num].imag_num[1]],'n',1,0);
        }
      draw_string(0,170,(font_ptr)&bgfnt,p1name,'l',1);
      if(!p1done) p1ctr++;
      if(p1ctr > mset1.sequences[0].used) p1ctr = 0;
      }

    if(p2on) {
      draw_portrait(320-right.width,0,(port_ptr)&right,1);
      draw_warrior(270,165,fset2.sprites[mset2.frames[mset2.sequences[0].moves[p2ctr]].fram_num],fset2.images[fset2.sprites[mset2.frames[mset2.sequences[0].moves[p2ctr]].fram_num].imag_num[0]],'h',0,0);
      if(fset2.sprites[mset2.frames[mset2.sequences[0].moves[p2ctr]].fram_num].last_image) {
        draw_warrior(270,165,fset2.sprites[mset2.frames[mset2.sequences[0].moves[p2ctr]].fram_num],fset2.images[fset2.sprites[mset2.frames[mset2.sequences[0].moves[p2ctr]].fram_num].imag_num[1]],'h',1,0);
        }
      draw_string(320,170,(font_ptr)&bgfnt,p2name,'r',1);
      if(!p2done) p2ctr++;
      if(p2ctr > mset2.sequences[0].used) p2ctr = 0;
      }

    for(ctr=0;ctr<rows;ctr++) {
      for(ctr2=0;ctr2<cols;ctr2++) {
        if(ctr*cols+ctr2 < last_id) {
          draw_portrait(x+(ctr2*width),y+ctr*height,(port_ptr)&pix[ctr*cols+ctr2],0);
          }
        }
      }
    for(ctr=0;ctr<hidctr;ctr++) {
      if(hiddens[ctr].active) {
        draw_portrait(x+(hiddens[ctr].xpos*width),y+(hiddens[ctr].ypos*height),(port_ptr)&hiddens[ctr].pic,0);
        }
      }

    show_double_buffer(0);
    } while(!keys_active);

  if(!p1on) {
    p1done = 0;
    if(key_table[st1]) {
      p1on = 1;
      p1id = 0;
      p1last = 0;
      fp = fopen(ids[p1id],"rb");
      fscanf(fp,"%s",&p1name);
      fscanf(fp,"%d",&type);
      fscanf(fp,"%s %s %s %s",&port,&bigp,&i,&s);
      get_portrait((port_ptr)&left,bigp);
      get_ide((fs_ptr)&fset1,i);
      get_re((fs_ptr)&fset1);
      get_seq((ms_ptr)&mset1,s);
      fclose(fp);
      }
    }
  else {
    if(!p1done) {
      p1last = p1id;
      if(key_table[st1]) {
        p1done = 1;
        if(p2done == p2on) goto DONE;
        }
      else if(key_table[rt1]) {
        if(p1id < last_id) p1id++;
        else p1id = 0;
        }
      else if(key_table[lf1]) {
        if(p1id > 0) p1id--;
        else p1id = last_id;
        }
      else if(key_table[dn1]) {
        if(p1id < last_id) p1id += cols;
        if(p1id > last_id) p1id = last_id;
        }
      else if(key_table[up1]) {
        if(p1id > 0) p1id -= cols;
        if(p1id < 0) p1id = 0;
        }
      }
    if(p1last != p1id) {
      fp = fopen(ids[p1id],"rb");
      fscanf(fp,"%s",&p1name);
      fscanf(fp,"%d",&type);
      fscanf(fp,"%s %s %s %s",&port,&bigp,&i,&s);
      kill_portrait(left);
      kill_frames((fs_ptr)&fset1);
      get_portrait((port_ptr)&left,bigp);
      get_ide((fs_ptr)&fset1,i);
      get_re((fs_ptr)&fset1);
      get_seq((ms_ptr)&mset1,s);
      fclose(fp);
      }
    }


  if(!p2on) {
    p2done = 0;
    if(key_table[st2]) {
      p2on = 1;
      p2id = 0;
      fp = fopen(ids[p2id],"rb");
      fscanf(fp,"%s",&p2name);
      fscanf(fp,"%d",&type);
      fscanf(fp,"%s %s %s %s",&port,&bigp,&i,&s);
      get_portrait((port_ptr)&right,bigp);
      get_ide((fs_ptr)&fset2,i);
      get_re((fs_ptr)&fset2);
      get_seq((ms_ptr)&mset2,s);
      fclose(fp);
      }
    }
  else {
    if(!p2done) {
      p2last = p2id;
      if(key_table[st2]) {
        p2done = 1;
        if(p1done == p1on) goto DONE;
        }
      else if(key_table[rt2]) {
        if(p2id < last_id) p2id++;
        else p2id = 0;
        }
      else if(key_table[lf2]) {
        if(p2id > 0) p2id--;
        else p2id = last_id;
        }
      else if(key_table[dn2]) {
        if(p2id < last_id) p2id += cols;
        if(p2id > last_id) p2id = last_id;
        }
      else if(key_table[up2]) {
        if(p2id > 0) p2id -= cols;
        if(p2id < 0) p2id = 0;
        }
      if(p2last != p2id) {
        fp = fopen(ids[p2id],"rb");
        fscanf(fp,"%s",&p2name);
        fscanf(fp,"%d",&type);
        fscanf(fp,"%s %s %s %s",&port,&bigp,&i,&s);
        kill_portrait(right);
        kill_frames((fs_ptr)&fset2);
        get_portrait((port_ptr)&right,bigp);
        get_ide((fs_ptr)&fset2,i);
        get_re((fs_ptr)&fset2);
        get_seq((ms_ptr)&mset2,s);
        fclose(fp);
        }
      }
    }
  goto LOOP;

  DONE:
  destroy_midi(bgtune);
  for(ctr=0;ctr<=last_id;ctr++) kill_portrait(pix[ctr]);
  kill_portrait(bigpic);
  kill_portrait(left);
  kill_portrait(right);
  strcpy(p1,ids[p1id]);
  strcpy(p2,ids[p2id]);
  returnval = 0;
  if(p1on) returnval = 1;
  if(p2on) returnval = 2;
  if(p1on && p2on) returnval = 3;
  return returnval;
  }

int single_match(char idname1[25],char idname2[25],int active) {
  static warrior player1;
  player1.setup();
  player1.get(idname1);
  player1.import_controls("p1.key");
  static warrior player2;
  player2.setup();
  player2.get(idname2);
  player2.import_controls("p2.key");

  background bg;

  int textpos = bg.width/2 + 200;
  int copy = 0;
  int bgoff;
  int loop;
  int slowctr;
  int ai = 1;
  int returnval=0;
  char winquote1[25];
  char winquote2[25];

  strcpy(winquote1,"NOQUOTE");
  strcpy(winquote2,"NOQUOTE");

  int maxloops=100;
  if(!strcmp(idname1,idname2)) copy = 1;
  int round=1;
  int cpu = 0;//stuff;

  static portrait left,right;
  static interface face;
  int p1=0,p2=0;
  int whofirst=0;
  char name[25];
  int type;
  char p[25];
  char bigp[25];

  MIDI *bgmusic;
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



  WHO:

  if(active == 1) {
    bgmusic = load_midi(player2.music);
    bg.get(player2.bgname);
    p2 = 1;
    }
  else if(active == 2) {
    bgmusic = load_midi(player1.music);
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
      bgmusic = load_midi(player2.music);
      bg.get(player2.bgname);
      }
    else {
      bgmusic = load_midi(player1.music);
      bg.get(player1.bgname);
      }
    }



  //static portrait left;


  //printf("%s\n",player1.bigp);
  //printf("%s\n",player2.bigp);
  //delay(2000);

  //get_portrait((port_ptr)&left,player1.bigp);

  //get_portrait((port_ptr)&right,player2.bigp);

  play_midi(bgmusic,1);

  do {
    clear_screen();
    player1.init(0,190,bg.width/2 - 50,0);
    player2.init(1,190,bg.width/2 + 50,copy);
    bgoff = 100;
    loop=0;
    if(round == 1) {
      do {
        bgoff = bg.update((info_ptr)&player1.data,(info_ptr)&player2.data,bgoff);
        player1.update(0,p1,(info_ptr)&player2.data,bgoff);
        player2.update(0,p2,(info_ptr)&player1.data,bgoff);
        for(slowctr=0;slowctr<speed;slowctr++) wait4vsync();
        show_double_buffer(bgoff);
        } while(player1.data.curr_seq != 0 || player2.data.curr_seq != 0);
      }

    do {
      bgoff = bg.update((info_ptr)&player1.data,(info_ptr)&player2.data,bgoff);
      player1.update(0,p1,(info_ptr)&player2.data,bgoff);
      player2.update(0,p2,(info_ptr)&player1.data,bgoff);
      face.update((info_ptr)&player1.data,(info_ptr)&player2.data,bgoff);
      draw_string(textpos,100,(font_ptr)&bgfnt,"ROUND",'l',1);
      draw_num(textpos+6*bgfnt.letwidth,100,(font_ptr)&bgfnt,round,'l',1);
      for(slowctr=0;slowctr<speed;slowctr++) wait4vsync();
      show_double_buffer(bgoff);
      textpos-=20;
      } while(textpos>bg.width/2 - 275);

    do {
      bgoff = bg.update((info_ptr)&player1.data,(info_ptr)&player2.data,bgoff);
      player1.update(0,p1,(info_ptr)&player2.data,bgoff);
      player2.update(0,p2,(info_ptr)&player1.data,bgoff);
      face.update((info_ptr)&player1.data,(info_ptr)&player2.data,bgoff);
      draw_string(textpos,100,(font_ptr)&bgfnt,"FIGHT",'l',1);
      for(slowctr=0;slowctr<speed;slowctr++) wait4vsync();
      show_double_buffer(bgoff);
      textpos+=20;
      } while(textpos<bg.width/2 + 200);

    do {
      if(player1.data.obox.active) whofirst = 0;
      if(player2.data.obox.active) whofirst = 1;
      bgoff = bg.update((info_ptr)&player1.data,(info_ptr)&player2.data,bgoff);
      if(whofirst) {
        player1.update(1,p1,(info_ptr)&player2.data,bgoff);
        player2.update(1,p2,(info_ptr)&player1.data,bgoff);
        }
      else {
        player2.update(1,p2,(info_ptr)&player1.data,bgoff);
        player1.update(1,p1,(info_ptr)&player2.data,bgoff);
        }
      face.update((info_ptr)&player1.data,(info_ptr)&player2.data,bgoff);
      for(slowctr=0;slowctr<speed;slowctr++) wait4vsync();
      show_double_buffer(bgoff);
      if(key_table[MAKE_ESC]) {
        destroy_midi(bgmusic);
        return 0;
        }
      } while(player1.data.alive && player2.data.alive);

    do {
      bgoff = bg.update((info_ptr)&player1.data,(info_ptr)&player2.data,bgoff);
      player1.update(1,p1,(info_ptr)&player2.data,bgoff);
      player2.update(1,p2,(info_ptr)&player1.data,bgoff);
      face.update((info_ptr)&player1.data,(info_ptr)&player2.data,bgoff);
      if(player1.data.curr_seq == 43) {
        draw_string(bgoff+130,50,(font_ptr)&bgfnt,player2.data.name,'l',1);
        }
      else if(player2.data.curr_seq == 43) {
        draw_string(bgoff+130,50,(font_ptr)&bgfnt,player1.data.name,'l',1);
        }
      else if(player1.data.curr_seq == 43 && player2.data.curr_seq == 43) draw_string(bgoff+130,50,(font_ptr)&bgfnt,"NO",'l',1);
      if(player1.data.curr_seq == 43 || player2.data.curr_seq == 43) draw_string(bgoff+130,75,(font_ptr)&bgfnt,"WIN",'l',1);
      for(slowctr=0;slowctr<speed;slowctr++) wait4vsync();
      show_double_buffer(bgoff);
      loop++;
      } while(loop < maxloops);

    round++;
    } while(player1.data.wins<2 && player2.data.wins<2);

  loop = 0;

  if(player1.kset.lastquote > 0) strcpy(winquote1,player1.kset.quotes[rand() % player1.kset.lastquote]);
  if(player2.kset.lastquote > 0) strcpy(winquote2,player2.kset.quotes[rand() % player2.kset.lastquote]);

  do {
    bgoff = bg.update((info_ptr)&player1.data,(info_ptr)&player2.data,bgoff);
    if(player1.data.wins == 2) {
      player1.update(1,p1,(info_ptr)&player2.data,bgoff);
      draw_portrait(bgoff,100-(left.height/2),(port_ptr)&left,0);
      draw_string(bgoff+130,50,(font_ptr)&bgfnt,player1.data.name,'l',1);
      draw_string(bgoff+130,75,(font_ptr)&bgfnt,"WIN",'l',1);
      draw_string(bgoff,0,(font_ptr)&fnt,winquote1,'l',1);
      if((player1.data.p[0] - bgoff) > 160) {
        if(bgoff < 200) bgoff++;
        }
      else if((player1.data.p[0] - bgoff) < 160) {
        if(bgoff > 0) bgoff--;
        }
      }
    if(player2.data.wins == 2) {
      player2.update(1,p2,(info_ptr)&player1.data,bgoff);
      draw_portrait(bgoff+(320-right.width),100-(right.height/2),(port_ptr)&right,1);
      draw_string(bgoff+130,50,(font_ptr)&bgfnt,player2.data.name,'l',1);
      draw_string(bgoff+130,75,(font_ptr)&bgfnt,"WIN",'l',1);
      draw_string(bgoff,0,(font_ptr)&fnt,winquote2,'l',1);
      if((player2.data.p[0] - bgoff) > 160) {
        if(bgoff < 200) bgoff++;
        }
      else if((player2.data.p[0] - bgoff) < 160) {
        if(bgoff > 0) bgoff--;
        }
      }
    if(key_table[MAKE_ESC]) {
      loop = 300;
      }
    show_double_buffer(bgoff);
    loop++;
    } while(loop < 300);

  destroy_midi(bgmusic);
  if(player1.data.wins == 2) returnval = 1;
  if(player2.data.wins == 2) returnval = 2;
  if(player1.data.wins == 2 && player2.data.wins == 2) returnval = 3;
  return returnval;
  }

int tag_match(char idname1[25],char idname2[25],char idname3[25],char idname4[25],int active) {
  static warrior player1;
  player1.setup();
  player1.get(idname1);
  player1.import_controls("p1.key");
  static warrior player2;
  player2.setup();
  player2.get(idname2);
  player2.import_controls("p1.key");
  static warrior player3;
  player3.setup();
  player3.get(idname3);
  player3.import_controls("p2.key");
  static warrior player4;
  player4.setup();
  player4.get(idname4);
  player4.import_controls("p2.key");

  background bg;

  int textpos = bg.width/2 + 200;
  int copy = 0;
  int bgoff;
  int loop;
  int slowctr;
  int ai = 1;
  int returnval=0;
  int active1=0;
  int active2=0;
  char winquote1[25];
  char winquote2[25];

  strcpy(winquote1,"NOQUOTE");
  strcpy(winquote2,"NOQUOTE");

  int maxloops=100;
  //if(!strcmp(idname1,idname2)) copy = 1;
  int round=1;
  int cpu = 0;//stuff;

  static portrait left,right;
  static interface face;
  int p1=0,p2=0,p3=0,p4=0;
  int p1control=0,p2control=0,p3control=0,p4control=0;
  int whofirst=0;
  char name[25];
  int type;
  char p[25];
  char bigp[25];

  MIDI *bgmusic;
  FILE *fp;

/*  fp = fopen(idname1,"rb");
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
  fclose(fp);                         */
  int temp=0;



  WHO:

  if(active == 1) {
    temp = rand() % 2;

    if(temp) {
      bgmusic = load_midi(player3.music);
      bg.get(player3.bgname);
      }
    else {
      bgmusic = load_midi(player4.music);
      bg.get(player4.bgname);
      }

    p3 = 1;
    p4 = 1;
    }
  else if(active == 2) {
    temp = rand() % 2;

    if(temp) {
      bgmusic = load_midi(player2.music);
      bg.get(player2.bgname);
      }
    else {
      bgmusic = load_midi(player1.music);
      bg.get(player1.bgname);
      }
    p1 = 1;
    p2 = 1;
    }
  else if(active == 0) {
    p1 = 1;
    p2 = 1;
    p3 = 1;
    p4 = 1;
    active = rand() % 2+1;
    goto WHO;
    }
  else if(active == 3) {
    temp = rand() % 4;

    if(temp==0) {
      bgmusic = load_midi(player2.music);
      bg.get(player2.bgname);
      }
    else if(temp==1) {
      bgmusic = load_midi(player1.music);
      bg.get(player1.bgname);
      }
    else if(temp==2) {
      bgmusic = load_midi(player3.music);
      bg.get(player3.bgname);
      }
    else if(temp==3) {
      bgmusic = load_midi(player4.music);
      bg.get(player4.bgname);
      }
    }



  //static portrait left;


  //printf("%s\n",player1.bigp);
  //printf("%s\n",player2.bigp);
  //delay(2000);

  //get_portrait((port_ptr)&left,player1.bigp);

  //get_portrait((port_ptr)&right,player2.bigp);

  play_midi(bgmusic,1);

//  do {
    clear_screen();
    player1.init(0,190,bg.width/2 - 100,0);
    player2.init(0,190,bg.width/2 - 50,0);
    player1.side = 0;
    player2.side = 0;
    player3.init(1,190,bg.width/2 + 100,copy);
    player4.init(1,190,bg.width/2 + 50,copy);
    player3.side = 1;
    player4.side = 1;

    bgoff = 100;
    loop=0;
//    if(round == 1) {
      do {
        //bgoff = bg.update((info_ptr)&player1.data,(info_ptr)&player2.data,bgoff);
        bgoff = bg.update((info_ptr)&player2.data,(info_ptr)&player4.data,bgoff);
        player1.update(0,p1,(info_ptr)&player3.data,bgoff);
        player2.update(0,p2,(info_ptr)&player4.data,bgoff);
        player3.update(0,p3,(info_ptr)&player1.data,bgoff);
        player4.update(0,p4,(info_ptr)&player2.data,bgoff);
        for(slowctr=0;slowctr<speed;slowctr++) wait4vsync();
        show_double_buffer(bgoff);
        } while(player1.data.curr_seq != 0 || player2.data.curr_seq != 0 || player3.data.curr_seq != 0 || player4.data.curr_seq != 0);

  /*  do {
      //bgoff = bg.update((info_ptr)&player1.data,(info_ptr)&player2.data,bgoff);
      player1.update(0,p1,(info_ptr)&player2.data,bgoff);
      player2.update(0,p2,(info_ptr)&player1.data,bgoff);
      face.update((info_ptr)&player1.data,(info_ptr)&player2.data,bgoff);
      draw_string(textpos,100,(font_ptr)&bgfnt,"ROUND",'l',1);
      draw_num(textpos+6*bgfnt.letwidth,100,(font_ptr)&bgfnt,round,'l',1);
      for(slowctr=0;slowctr<speed;slowctr++) wait4vsync();
      show_double_buffer(bgoff);
      textpos-=20;
      } while(textpos>bg.width/2 - 275);

    do {
      //bgoff = bg.update((info_ptr)&player1.data,(info_ptr)&player2.data,bgoff);
      player1.update(0,p1,(info_ptr)&player2.data,bgoff);
      player2.update(0,p2,(info_ptr)&player1.data,bgoff);
      face.update((info_ptr)&player1.data,(info_ptr)&player2.data,bgoff);
      draw_string(textpos,100,(font_ptr)&bgfnt,"FIGHT",'l',1);
      for(slowctr=0;slowctr<speed;slowctr++) wait4vsync();
      show_double_buffer(bgoff);
      textpos+=20;
      } while(textpos<bg.width/2 + 200);*/

    do {
      if(player1.data.obox.active || player2.data.obox.active) whofirst = 0;
      if(player3.data.obox.active || player4.data.obox.active) whofirst = 1;

      if(active1) {
        if(active2) {
          bgoff = bg.update((info_ptr)&player1.data,(info_ptr)&player3.data,bgoff);
          face.update((info_ptr)&player1.data,(info_ptr)&player3.data,bgoff);
          }
        else {
          bgoff = bg.update((info_ptr)&player1.data,(info_ptr)&player4.data,bgoff);
          face.update((info_ptr)&player1.data,(info_ptr)&player4.data,bgoff);
          }
        }
      else {
        if(active2) {
          bgoff = bg.update((info_ptr)&player2.data,(info_ptr)&player3.data,bgoff);
          face.update((info_ptr)&player2.data,(info_ptr)&player3.data,bgoff);
          }
        else {
          bgoff = bg.update((info_ptr)&player2.data,(info_ptr)&player4.data,bgoff);
          face.update((info_ptr)&player2.data,(info_ptr)&player4.data,bgoff);
          }
        }

      if(!player1.data.alive) {
        if(active1 == 1) {
          active1 = 0;
          player2.data.p[0] = bgoff - 50;
          player2.data.curr_seq = 7;
          player2.data.curr_frame = -1;
          }
        }
      if(!player2.data.alive) {
        if(active1 == 0) {
          active1 = 1;
          player1.data.p[0] = bgoff - 50;
          player1.data.curr_seq = 7;
          player1.data.curr_frame = -1;
          }
        }
      if(!player3.data.alive) {
        if(active2 == 1) {
          active2 = 0;
          player4.data.p[0] = bgoff + 370;
          player4.data.curr_seq = 7;
          player4.data.curr_frame = -1;
          }
        }
      if(!player4.data.alive) {
        if(active2 == 0) {
          active2 = 1;
          player3.data.p[0] = bgoff + 370;
          player3.data.curr_seq = 6;
          player3.data.curr_frame = -1;
          }
        }

      if(whofirst) {
        if(active1) {
          if(player2.data.p[0] > 0) {
            if(!player2.data.mid_seq && player2.data.alive) {
              player2.data.second = 0;
              player2.data.curr_seq = 4;
              }
            p2control = 0;
            }
          if(player1.data.p[0] < bgoff-49) {
            player1.data.second = 0;
            player1.data.curr_seq = 7;
            p1control = 0;
            }
          else {
            if(player1.data.p[0] > bgoff-10) p1control = 1;
            }

          if(active2) {
            player1.update(p1control,p1,(info_ptr)&player3.data,bgoff);
            player2.update(p2control,p2,(info_ptr)&player3.data,bgoff);
            }
          else {
            player1.update(p1control,p1,(info_ptr)&player4.data,bgoff);
            player2.update(p2control,p2,(info_ptr)&player4.data,bgoff);
            }


          if(player1.data.tag) {
            if(player2.data.alive && player2.data.p[0] < 0) {
              player2.data.p[0] = bgoff - 50;
              player2.data.curr_frame = -1;
              player1.data.tag = 0;
              active1 = 0;
              }
            }
          }
        else {
          if(player1.data.p[0] > 0) {
            if(!player1.data.mid_seq && player1.data.alive) {
              player1.data.second = 0;
              player1.data.curr_seq = 4;
              }
            p1control = 0;
            }
          if(player2.data.p[0] < bgoff-49) {
            player2.data.second = 0;
            player2.data.curr_seq = 7;
            p2control = 0;
            }
          else {
            if(player2.data.p[0] > bgoff-10) p2control = 1;
            }


          if(active2) {
            player1.update(p1control,p1,(info_ptr)&player3.data,bgoff);
            player2.update(p2control,p2,(info_ptr)&player3.data,bgoff);
            }
          else {
            player1.update(p1control,p1,(info_ptr)&player4.data,bgoff);
            player2.update(p2control,p2,(info_ptr)&player4.data,bgoff);
            }

          if(player2.data.tag) {
            if(player1.data.alive  && player1.data.p[0] < 0) {
              player1.data.status = LEAP;
              player1.air_seq = 7;
              player1.air_frame = -1;
              player1.data.p[0] = bgoff - 50;
              player1.data.curr_frame = -1;
              player2.data.tag = 0;
              active1 = 1;
              }
            }
          }

        if(active2) {
          if(player4.data.p[0] < 520) {
            if(!player4.data.mid_seq && player4.data.alive) {
              player4.data.second = 1;
              player4.data.curr_seq = 4;
              }
            p4control = 0;
            }
          if(player3.data.p[0] > bgoff+369) {
            player3.data.second = 1;
            player3.data.curr_seq = 7;
            p3control = 0;
            }
          else {
            if(player3.data.p[0] < bgoff+330) p3control = 1;
            }

          if(active1) {
            player3.update(p3control,p3,(info_ptr)&player1.data,bgoff);
            player4.update(p4control,p4,(info_ptr)&player1.data,bgoff);
            }
          else {
            player3.update(p3control,p3,(info_ptr)&player2.data,bgoff);
            player4.update(p4control,p4,(info_ptr)&player2.data,bgoff);
            }


          if(player3.data.tag) {
            if(player4.data.alive  && player4.data.p[0] > 520) {
              player4.data.status = LEAP;
              player4.air_seq = 7;
              player4.air_frame = -1;
              player4.data.p[0] = bgoff + 370;
              player4.data.curr_frame = -1;
              player3.data.tag = 0;
              active2 = 0;
              }
            }
          }
        else {
          if(player3.data.p[0] < 520) {
            if(!player3.data.mid_seq && player3.data.alive) {
              player3.data.second = 1;
              player3.data.curr_seq = 4;
              }
            p3control = 0;
            }
          if(player4.data.p[0] > bgoff+369) {
            player4.data.second = 1;
            player4.data.curr_seq = 7;
            p4control = 0;
            }
          else {
            if(player4.data.p[0] < bgoff+330) p4control = 1;
            }

          if(active1) {
            player3.update(p3control,p3,(info_ptr)&player1.data,bgoff);
            player4.update(p4control,p4,(info_ptr)&player1.data,bgoff);
            }
          else {
            player3.update(p3control,p3,(info_ptr)&player2.data,bgoff);
            player4.update(p4control,p4,(info_ptr)&player2.data,bgoff);
            }

          if(player4.data.tag) {
            if(player3.data.alive && player3.data.p[0] > 520) {
              player3.data.status = LEAP;
              player3.air_seq = 7;
              player3.air_frame = -1;
              player3.data.p[0] = bgoff + 370;
              player3.data.curr_frame = -1;
              player4.data.tag = 0;
              active2 = 1;
              }
            }
          }
        }
      else {
        if(active2) {
          if(player4.data.p[0] < 520) {
            if(!player4.data.mid_seq && player4.data.alive) {
              player4.data.second = 1;
              player4.data.curr_seq = 4;
              }
            p4control = 0;
            }
          if(player3.data.p[0] > bgoff+369) {
            player3.data.second = 1;
            player3.data.curr_seq = 7;
            p3control = 0;
            }
          else {
            if(player3.data.p[0] < bgoff+330) p3control = 1;
            }

          if(active1) {
            player3.update(p3control,p3,(info_ptr)&player1.data,bgoff);
            player4.update(p4control,p4,(info_ptr)&player1.data,bgoff);
            }
          else {
            player3.update(p3control,p3,(info_ptr)&player2.data,bgoff);
            player4.update(p4control,p4,(info_ptr)&player2.data,bgoff);
            }

          if(player3.data.tag) {
            if(player4.data.alive  && player4.data.p[0] > 520) {
              player4.data.status = LEAP;
              player4.air_seq = 7;
              player4.air_frame = -1;
              player4.data.p[0] = bgoff + 370;
              player4.data.curr_frame = -1;
              player3.data.tag = 0;
              active2 = 0;
              }
            }
          }
        else {
          if(player3.data.p[0] < 520) {
            if(!player3.data.mid_seq && player3.data.alive) {
              player3.data.second = 1;
              player3.data.curr_seq = 4;
              }
            p3control = 0;
            }
          if(player4.data.p[0] > bgoff+369) {
            player4.data.second = 1;
            player4.data.curr_seq = 7;
            p4control = 0;
            }
          else {
            if(player4.data.p[0] < bgoff+330) p4control = 1;
            }

          if(active1) {
            player3.update(p3control,p3,(info_ptr)&player1.data,bgoff);
            player4.update(p4control,p4,(info_ptr)&player1.data,bgoff);
            }
          else {
            player3.update(p3control,p3,(info_ptr)&player2.data,bgoff);
            player4.update(p4control,p4,(info_ptr)&player2.data,bgoff);
            }

          if(player4.data.tag) {
            if(player3.data.alive && player3.data.p[0] > 520) {
              player3.data.status = LEAP;
              player3.air_seq = 7;
              player3.air_frame = -1;
              player3.data.p[0] = bgoff + 370;
              player3.data.curr_frame = -1;
              player4.data.tag = 0;
              active2 = 1;
              }
            }
          }

        if(active1) {
          if(player2.data.p[0] > 0) {
            if(!player2.data.mid_seq) {
              player2.data.second = 0;
              player2.data.curr_seq = 4;
              }
            p2control = 0;
            }
          if(player1.data.p[0] < bgoff-49) {
            player1.data.second = 0;
            player1.data.curr_seq = 7;
            p1control = 0;
            }
          else {
            if(player1.data.p[0] > bgoff-10) p1control = 1;
            }

          if(active2) {
            player1.update(p1control,p1,(info_ptr)&player3.data,bgoff);
            player2.update(p2control,p2,(info_ptr)&player3.data,bgoff);
            }
          else {
            player1.update(p1control,p1,(info_ptr)&player4.data,bgoff);
            player2.update(p2control,p2,(info_ptr)&player4.data,bgoff);
            }

          if(player1.data.tag) {
            if(player2.data.alive && player2.data.p[0] < 0) {
              player2.data.status = LEAP;
              player2.air_seq = 7;
              player2.air_frame = -1;
              player2.data.p[0] = bgoff - 50;
              player2.data.curr_frame = -1;
              player1.data.tag = 0;
              active1 = 0;
              }
            }
          }
        else {
          if(player1.data.p[0] > 0) {
            if(!player1.data.mid_seq && player1.data.alive) {
              player1.data.second = 0;
              player1.data.curr_seq = 4;
              }
            p1control = 0;
            }
          if(player2.data.p[0] < bgoff-49) {
            player2.data.second = 0;
            player2.data.curr_seq = 7;
            p2control = 0;
            }
          else {
            if(player2.data.p[0] > bgoff-10) p2control = 1;
            }

          if(active2) {
            player1.update(p1control,p1,(info_ptr)&player3.data,bgoff);
            player2.update(p2control,p2,(info_ptr)&player3.data,bgoff);
            }
          else {
            player1.update(p1control,p1,(info_ptr)&player4.data,bgoff);
            player2.update(p2control,p2,(info_ptr)&player4.data,bgoff);
            }

          if(player2.data.tag) {
            if(player1.data.alive && player1.data.p[0] < 0) {
              player1.data.status = LEAP;
              player1.air_seq = 7;
              player1.air_frame = -1;
              player1.data.p[0] = bgoff - 50;
              player1.data.curr_frame = -1;
              player2.data.tag = 0;
              active1 = 1;
              }
            }
          }
        }
 //     face.update((info_ptr)&player1.data,(info_ptr)&player2.data,bgoff);
      for(slowctr=0;slowctr<speed;slowctr++) wait4vsync();
      show_double_buffer(bgoff);
      if(key_table[MAKE_ESC]) {
        destroy_midi(bgmusic);
        return 0;
        }
      } while((player1.data.alive || player2.data.alive) && (player3.data.alive || player4.data.alive));


    do {
//      bgoff = bg.update((info_ptr)&player1.data,(info_ptr)&player2.data,bgoff);
      if(active1) {
        if(active2) {
          bgoff = bg.update((info_ptr)&player1.data,(info_ptr)&player3.data,bgoff);
          face.update((info_ptr)&player1.data,(info_ptr)&player3.data,bgoff);
          }
        else {
          bgoff = bg.update((info_ptr)&player1.data,(info_ptr)&player4.data,bgoff);
          face.update((info_ptr)&player1.data,(info_ptr)&player4.data,bgoff);
          }
        }
      else {
        if(active2) {
          bgoff = bg.update((info_ptr)&player2.data,(info_ptr)&player3.data,bgoff);
          face.update((info_ptr)&player2.data,(info_ptr)&player3.data,bgoff);
          }
        else {
          bgoff = bg.update((info_ptr)&player2.data,(info_ptr)&player4.data,bgoff);
          face.update((info_ptr)&player2.data,(info_ptr)&player4.data,bgoff);
          }
        }
      player1.update(0,p1,(info_ptr)&player3.data,bgoff);
      player2.update(0,p2,(info_ptr)&player4.data,bgoff);
      player3.update(0,p3,(info_ptr)&player1.data,bgoff);
      player4.update(0,p4,(info_ptr)&player2.data,bgoff);
      for(slowctr=0;slowctr<speed;slowctr++) wait4vsync();
      show_double_buffer(bgoff);
 //     player1.update(0,p1,(info_ptr)&player2.data,bgoff);
  //    player2.update(0,p2,(info_ptr)&player1.data,bgoff);
   //   face.update((info_ptr)&player1.data,(info_ptr)&player2.data,bgoff);
    //  if(player1.data.curr_seq == 43) {
//        draw_string(bgoff+130,50,(font_ptr)&bgfnt,player2.data.name,'l',1);
 //       }
  //    else if(player2.data.curr_seq == 43) {
   //     draw_string(bgoff+130,50,(font_ptr)&bgfnt,player1.data.name,'l',1);
    //    }
     // else if(player1.data.curr_seq == 43 && player2.data.curr_seq == 43) draw_string(bgoff+130,50,(font_ptr)&bgfnt,"NO",'l',1);
//      if(player1.data.curr_seq == 43 || player2.data.curr_seq == 43) draw_string(bgoff+130,75,(font_ptr)&bgfnt,"WIN",'l',1);
 //     for(slowctr=0;slowctr<speed;slowctr++) wait4vsync();
  //    show_double_buffer(bgoff);
      loop++;
      } while(loop < maxloops);

    return 0;
/*    round++;
    } while(player1.data.wins<2 && player2.data.wins<2);

  loop = 0;

  if(player1.kset.lastquote > 0) strcpy(winquote1,player1.kset.quotes[rand() % player1.kset.lastquote]);
  if(player2.kset.lastquote > 0) strcpy(winquote2,player2.kset.quotes[rand() % player2.kset.lastquote]);

  do {
    bgoff = bg.update((info_ptr)&player1.data,(info_ptr)&player2.data,bgoff);
    if(player1.data.wins == 2) {
      player1.update(0,p1,(info_ptr)&player2.data,bgoff);
      draw_portrait(bgoff,100-(left.height/2),(port_ptr)&left,0);
      draw_string(bgoff+130,50,(font_ptr)&bgfnt,player1.data.name,'l',1);
      draw_string(bgoff+130,75,(font_ptr)&bgfnt,"WIN",'l',1);
      draw_string(bgoff,0,(font_ptr)&fnt,winquote1,'l',1);
      if((player1.data.p[0] - bgoff) > 160) {
        if(bgoff < 200) bgoff++;
        }
      else if((player1.data.p[0] - bgoff) < 160) {
        if(bgoff > 0) bgoff--;
        }
      }
    if(player2.data.wins == 2) {
      player2.update(0,p2,(info_ptr)&player1.data,bgoff);
      draw_portrait(bgoff+(320-right.width),100-(right.height/2),(port_ptr)&right,1);
      draw_string(bgoff+130,50,(font_ptr)&bgfnt,player2.data.name,'l',1);
      draw_string(bgoff+130,75,(font_ptr)&bgfnt,"WIN",'l',1);
      draw_string(bgoff,0,(font_ptr)&fnt,winquote2,'l',1);
      if((player2.data.p[0] - bgoff) > 160) {
        if(bgoff < 200) bgoff++;
        }
      else if((player2.data.p[0] - bgoff) < 160) {
        if(bgoff > 0) bgoff--;
        }
      }
    if(key_table[MAKE_ESC]) {
      loop = 300;
      }
    show_double_buffer(bgoff);
    loop++;
    } while(loop < 300);

  destroy_midi(bgmusic);
  if(player1.data.wins == 2) returnval = 1;
  if(player2.data.wins == 2) returnval = 2;
  if(player1.data.wins == 2 && player2.data.wins == 2) returnval = 3;
  return returnval;*/
  }

//This function returns the scan code of the active key.
int return_scancode() {
  int ctr=1;  //Generic counter.
  int val=0;

  //a for loop that checks every possible key to see if it is pressed.
  while(val == 0) {
    if(ctr<128) ctr++;
    else ctr = 1;
    if(key_table[ctr]) val = ctr;
    }


  delay(1000);
  printf("%d\n",val);

  do {
    }while(!keys_active);


/*  for(ctr=1;ctr<128;ctr++) {
    if(key_table[ctr]) val = ctr;
    //return ctr;  //if the key has been pressed, return its value.
    }*/
  return val;  //if no key was found, return 0.
  }


/*This function is used to 'map' the keypresses for each control.  int player refers to which character's controls are to be mapped.*/

void map_controls(int player) {
  int strt=0, up=0, dn=0, lf=0, rt=0, jb=0, st=0, fc=0, sh=0, fw=0, rh=0, p3=0, k3=0;
  char filename[25];
  //Integer values for the scancode of each button.  start, up, down, left, right, jab, strong, fierce, short, forward, r. house, all 3 punches, all 3 kicks*/

  if(player==1) strcpy(filename,"p1.key");
  else strcpy(filename,"p2.key");

  FILE *fp;  //A file pointer, for file access.
  if((fp = fopen(filename,"wb")) == NULL) {
    printf("Unable to Create %s",filename);
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
    show_double_buffer(0);  //Copies all image data to the actual video buffer (screen).
    strt = return_scancode();

    fprintf(fp,"%d ",strt);

    do{
      }while(keys_active);

    draw_string(0,0,(font_ptr)&fnt,"Press key for up",'l',1);
    show_double_buffer(0);  //Copies all image data to the actual video buffer (screen).
    up = return_scancode();  //Key has been pressed, get it's scan code, and store it in up.

    fprintf(fp,"%d ",up);

        do{
      }while(keys_active);

    draw_string(0,0,(font_ptr)&fnt,"Press key for down",'l',1);
    show_double_buffer(0);  //Copies all image data to the actual video buffer (screen).
    dn = return_scancode();  //Key has been pressed, get it's scan code, and store it in up.

    fprintf(fp,"%d ",dn);

        do{
      }while(keys_active);

    draw_string(0,0,(font_ptr)&fnt,"Press key for left",'l',1);
    show_double_buffer(0);  //Copies all image data to the actual video buffer (screen).
    lf = return_scancode();  //Key has been pressed, get it's scan code, and store it in up.

    fprintf(fp,"%d ",lf);

        do{
      }while(keys_active);

    draw_string(0,0,(font_ptr)&fnt,"Press key for right",'l',1);
    show_double_buffer(0);  //Copies all image data to the actual video buffer (screen).
    rt = return_scancode();  //Key has been pressed, get it's scan code, and store it in up.

    fprintf(fp,"%d ",rt);

        do{
      }while(keys_active);

    draw_string(0,0,(font_ptr)&fnt,"Press key for jab",'l',1);
    show_double_buffer(0);  //Copies all image data to the actual video buffer (screen).
    jb = return_scancode();  //Key has been pressed, get it's scan code, and store it in up.

    fprintf(fp,"%d ",jb);

        do{
      }while(keys_active);

    draw_string(0,0,(font_ptr)&fnt,"Press key for strong",'l',1);
    show_double_buffer(0);  //Copies all image data to the actual video buffer (screen).
    st = return_scancode();  //Key has been pressed, get it's scan code, and store it in up.

    fprintf(fp,"%d ",st);

        do{
      }while(keys_active);

    draw_string(0,0,(font_ptr)&fnt,"Press key for fierce",'l',1);
    show_double_buffer(0);  //Copies all image data to the actual video buffer (screen).
    fc = return_scancode();  //Key has been pressed, get it's scan code, and store it in up.

    fprintf(fp,"%d ",fc);

        do{
      }while(keys_active);

    draw_string(0,0,(font_ptr)&fnt,"Press key for short",'l',1);
    show_double_buffer(0);  //Copies all image data to the actual video buffer (screen).
    sh = return_scancode();  //Key has been pressed, get it's scan code, and store it in up.

    fprintf(fp,"%d ",sh);

        do{
      }while(keys_active);

    draw_string(0,0,(font_ptr)&fnt,"Press key for forward",'l',1);
    show_double_buffer(0);  //Copies all image data to the actual video buffer (screen).
    fw = return_scancode();  //Key has been pressed, get it's scan code, and store it in up.

    fprintf(fp,"%d ",fw);

        do{
      }while(keys_active);

    draw_string(0,0,(font_ptr)&fnt,"Press key for roundhouse",'l',1);
    show_double_buffer(0);  //Copies all image data to the actual video buffer (screen).
    rh = return_scancode();  //Key has been pressed, get it's scan code, and store it in up.

    fprintf(fp,"%d ",rh);

        do{
      }while(keys_active);

    draw_string(0,0,(font_ptr)&fnt,"Press key for all punch",'l',1);
    show_double_buffer(0);  //Copies all image data to the actual video buffer (screen).
    p3 = return_scancode();  //Key has been pressed, get it's scan code, and store it in up.

    fprintf(fp,"%d ",p3);

        do{
      }while(keys_active);

    draw_string(0,0,(font_ptr)&fnt,"Press key for all kick",'l',1);
    show_double_buffer(0);  //Copies all image data to the actual video buffer (screen).
    k3 = return_scancode();  //Key has been pressed, get it's scan code, and store it in up.

    fprintf(fp,"%d ",k3);

        do{
      }while(keys_active);
/*  if(player == 1) if((fp = fopen("p1.key","wb")) == NULL) { //Create player one control file or. .
    printf("unable to create p1.key");
    exit(-1);
    }
  else if(player == 2) if((fp = fopen("p2.key","wb")) == NULL) {   //Create player two control file.
    printf("unable to create p2.key");
    exit(-1);
    }

//  fprintf(fp,"%d %d %d %d %d %d %d %d %d %d %d %d %d",
//              strt,up,dn,lf,rt,jb,st,fc,sh,fw,rh,p3,k3);

  //Write all the scancodes to the file.*/

  fclose(fp);  //close the file pointer.
  }

void options_menu(char config[25]) {
  char strings[7][25];
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
  strcpy(strings[5],"Map left player");
  strcpy(strings[6],"Map right player");

  LOOP:
  do {
    draw_string(0,0,(font_ptr)&fnt,"OPTIONS MENU",'l',1);
    draw_string(0,fnt.letheight,(font_ptr)&fnt,"USE PLUS OR MINUS",'l',1);
    draw_string(0,200-fnt.letheight,(font_ptr)&fnt,"PRESS ESC TO EXIT",'l',1);
    for(menuctr=0;menuctr<7;menuctr++) {
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
    if(rad<5) rad++;
    else rad = 0;
    circle_b(5,80+val*fnt.letheight,255,rad);
    show_double_buffer(0);
    set_volume(sfxvolume,midvolume);
    } while(!keys_active);

  if(key_table[MAKE_UP]) {
    do {
      } while(keys_active);
    if(val > 0) val--;
    }
  else if(key_table[MAKE_DOWN]) {
    do {
      } while(keys_active);
    if(val < 6) val++;
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
      case 5:  map_controls(1);
               goto LOOP;
               break;
      case 6:  map_controls(2);
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
      }
    }
  else if(key_table[MAKE_ESC]) goto EXIT;
  goto LOOP;



  EXIT:
  FILE *fp = fopen("options.opt","wb");
  fprintf(fp,"%d %d %d %d %d",speed,sfxvolume,midvolume,juggling,drama);
  fclose(fp);
  }

void demo_mode(char *config) {
  int temp;
  int curr_id = 0;
  int last_id;
  char ids[99][20];
  char name[25];
  int rows,cols;
  int winner;
  FILE *fp;
  int type;
  char p[25];
  char i[25];
  char s[25];
  char k[25];
  char b[25];
  char bigp[25];
  char backname[25];
  char bgmusic[25];

  if((fp = fopen(config,"rb")) == NULL) {
    printf("No config file?  No game for you!\n");
    exit(-1);
    }

  fscanf(fp,"%s",&backname);
  fscanf(fp,"%s",&bgmusic);
  fscanf(fp,"%d%d",&cols,&rows);
  fscanf(fp,"%s",&ids[curr_id]);
  while(strcmp(ids[curr_id],"end")) {
    curr_id++;
    fscanf(fp,"%s",&ids[curr_id]);
    }
  fclose(fp);

  last_id = curr_id;
  curr_id = 0;

  fp = fopen(ids[rand() % last_id],"rb");
  fscanf(fp,"%s",&name);
  fscanf(fp,"%d",&type);

  fscanf(fp,"%s %s %s %s %s %s",&p,&bigp,&i,&s,&k,&b);
  fclose(fp);

  do {
    winner = single_match(ids[rand() % last_id],ids[rand() % last_id],0);
    temp = tag_match(ids[rand() % last_id],ids[rand() % last_id],ids[rand() % last_id],ids[rand() % last_id],0);
    } while(winner != 0);
  }

int countdown(char idname[25]) {
  FILE *fp;
  }

int story_mode(char *config) {
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
  char all[75][25];
  int curr_all=0;
  int last_all=0;
  char trash[25];
  int winner=1;
  int type;
  int fightcount=0;
  int who;
  char bgpicture[25];
  char bgmusic[25];
  int rows,cols;
  int x,y;
  int ctr;

  if((fp = fopen("te.cfg","rb")) == NULL) {
    printf("No te.cfg\nRun te.exe\n");
    return 0;
    }

  last_all = fgetc(fp);

  fclose(fp);

  if((fp = fopen(config,"rb")) == NULL) {
    printf("Could not open config file:\n%s",config);
    return 0;
    }

  fscanf(fp,"%s",&bgpicture);
  fscanf(fp,"%s",&bgmusic);
  fscanf(fp,"%d %d",&x,&y);
  fscanf(fp,"%d %d",&rows,&cols);

  for(curr_all=0;curr_all<last_all;curr_all++) {
    fscanf(fp,"%s",&all[curr_all]);
    }

  fclose(fp);

  who = story_select(idname1,idname2,b,config);

  WHO:

  if(who == 1) strcpy(guy,idname1);
  else if(who == 2) strcpy(guy,idname2);
  else if(who == 3) {
    who = single_match(idname1,idname2,3);
    goto WHO;
    }

  printf("%s",guy);
  delay(2000);
  if((fp = fopen(guy,"rb")) == NULL) {
    printf("I'm afraid %s doesn't exist. . .",guy);
    return 0;
    }

  fscanf(fp,"%s",&yourname);

  fscanf(fp,"%d",&type);

  fscanf(fp,"%s %s %s %s %s %s %s",&p,&bigp,&i,&s,&k,&b,&m);

  get_portrait((port_ptr)&port[0],bigp);

  fscanf(fp,"%s",&victim[last_opponent]);
  while(strcmp(victim[last_opponent],"ending")) {
    ++last_opponent;
    fscanf(fp,"%s",victim[last_opponent]);
    }

  fclose(fp);

  //fscanf(fp,"%s",&victim);

  while(strcmp(victim[curr_opponent],"ending")) {
    if(!strcmp(victim[curr_opponent],"%rand%")) {
      CHECK:
      if(winner==who) strcpy(him,all[rand() % last_all]);
      for(ctr=0;ctr<last_opponent;ctr++) {
        if(!strcmp(victim[ctr],him)) goto CHECK;
        }
      }
    else strcpy(him,victim[curr_opponent]);
    clear_screen();
//    kill_portrait(port[1]);


    fp = fopen(him,"rb");
    fscanf(fp,"%s",&name);
    fscanf(fp,"%d",&type);
    fscanf(fp,"%s %s %s %s %s %s",&p,&bigp,&i,&s,&k,&b);
    fclose(fp);

//    get_portrait((port_ptr)&port[1],bigp);


    if(who == 1) {
      draw_portrait(0,100-(port[0].height/2),(port_ptr)&port[0],0);
//      draw_portrait(320-port[1].width,100-(port[1].height/2),(port_ptr)&port[1],1);
      draw_string(0,150,(font_ptr)&bgfnt,yourname,'l',1);
      draw_string(140,150,(font_ptr)&bgfnt,"VS",'l',1);
      draw_string(320,150,(font_ptr)&bgfnt,name,'r',1);
      }
    else if(who == 2) {
//      draw_portrait(0,100-(port[1].height/2),(port_ptr)&port[1],0);
      draw_portrait(320-port[0].width,100-(port[0].height/2),(port_ptr)&port[0],1);
      draw_string(0,150,(font_ptr)&bgfnt,name,'l',1);
      draw_string(140,150,(font_ptr)&bgfnt,"VS",'l',1);
      draw_string(320,150,(font_ptr)&bgfnt,yourname,'r',1);
      }

    show_double_buffer(0);

    delay(1000);

    if(who == 1) {
      winner = single_match(guy,him,who);
      }
    else if(who == 2) {
      winner = single_match(him,guy,who);
      }

    if(winner == 0) return 0;
    if(winner==who) ++curr_opponent;
    }

  if((fp = fopen("hid.den","rb+")) == NULL) {
    printf("unable to check hidden file.");
    return 0;
    }

  int done = 0;

  fscanf(fp,"%s",&trash);
  while(!feof(fp)) {
    if(!strcmp(trash,guy)) done = 1;
    if(done) goto END;
    fscanf(fp,"%s",trash);
    }

  fprintf(fp,"%s\n",guy);
  fclose(fp);

  END:


  kill_portrait(port[0]);
  kill_portrait(port[1]);
  }
