#define OFF 0
#define ON 1

#define STUN 6
#define DEFAULT 7

struct super_meter {
  char full_meter_text[20];
  int sprite_num;
  int sprite_x;
  int sprite_y;
  int color;
  int fill_x;
  int fill_y;
  int max_length;
  int levels;
  int height;
};

struct dizzy_meter {
  char dizzied_text[10];
  int max_length;
  int height;
  int color;
  int fill_x;
  int fill_y;
};

struct super_sys {
  super_meter spmeter;
  dizzy_meter dzmeter;
  int animation_seq;
  bool vism;
};


typedef struct superset {
  char ide_file[20];
  int total;
  super_sys supersets[6];
} *superset_ptr;


void init_supersets (superset_ptr set)
{
  set->total = 0;

  for (int ctr = 0; ctr < 6; ctr++) {
  strcpy(set->supersets[ctr].spmeter.full_meter_text, "none");
  set->supersets[ctr].spmeter.sprite_num = 0;
  set->supersets[ctr].spmeter.sprite_x = 0;
  set->supersets[ctr].spmeter.sprite_y = 0;
  set->supersets[ctr].spmeter.fill_x = 0;
  set->supersets[ctr].spmeter.fill_y = 0;
  set->supersets[ctr].spmeter.max_length = 0;
  set->supersets[ctr].spmeter.levels = 0;
  set->supersets[ctr].spmeter.height = 0;
  }

  for (int ctr = 0; ctr < 6; ctr++) {
  strcpy(set->supersets[ctr].dzmeter.dizzied_text,"none");
  set->supersets[ctr].dzmeter.max_length = 0;
  set->supersets[ctr].dzmeter.height = 0;
  set->supersets[ctr].dzmeter.color = 0;
  set->supersets[ctr].dzmeter.fill_x = 0;
  set->supersets[ctr].dzmeter.fill_y = 0;
  set->supersets[ctr].animation_seq = 0;
  set->supersets[ctr].vism = OFF;
  }

};

/*
void get_supermeter_cfg (superset_ptr set, char filename[20]) {
  FILE *fp;
  char trash[20];

  if((fp = fopen(filename,"rb")) == NULL) {
    exit(-1);
    printf("Could not open file: %s. Aborting... \n", filename);
    }

  init_supersets(set);


  fscanf(fp,"%s", &set->id_file);
  fscanf(fp,"%d", &set->supersets.total);

  for (int ctr = 0; ctr < set->supersets.total; ctr++) {
    fscanf(fp,"%s", &trash);
    fscanf(fp,"%s", &set->supersets[ctr].spmeter.full_meter_text);

    }

  END:
  fclose(fp);

}
*/


struct mode {
  char ide_file[20];
  char seq_file[20];
  char cmd_file[20];
  char mode_name[15];
  int super_subset;  // super combo system
  int chaincombo; // which chain combo system, none, set to N
  float odamage;  // offenise damage
  float ddamage;  // defensive damage
  float super_rate; // super meter charging rate
  int air_block; // on or off
  bool limb_control; // on or off
  bool juggle; // can character be juggle? on/off
  bool air_recovery; // air recovery from SFA3 on/off
  bool alpha_counter; // if disabled, skip the sequence that goes with it
  int alpha_counter_seq; // alpha counter sequence
  bool fdash; // dashing on/off
  int fdash_seq;
  bool bdash; // dashing on/off
  int bdash_seq;
  bool oguard; // offensive guard on/off
  int oguard_seq;
};


typedef struct modeset {
  mode modes[6];
  int total;
} *modes_ptr;


void init_modes (modes_ptr set)
{
  set->total = 0;

  for (int ctr = 0; ctr < 6; ctr++) {

    strcpy(set->modes[ctr].mode_name,"none");
    set->modes[ctr].super_subset = 0;
    set->modes[ctr].chaincombo = 0;
    set->modes[ctr].odamage = 0;
    set->modes[ctr].ddamage = 0;
    set->modes[ctr].super_rate = 0;
    set->modes[ctr].air_block = OFF;
    set->modes[ctr].limb_control = OFF;
    set->modes[ctr].juggle = OFF;
    set->modes[ctr].air_recovery = OFF;
    set->modes[ctr].alpha_counter = OFF;
    set->modes[ctr].alpha_counter_seq = 0;
    set->modes[ctr].fdash = OFF;
    set->modes[ctr].fdash_seq = 0;
    set->modes[ctr].bdash = OFF;
    set->modes[ctr].bdash_seq = 0;
    set->modes[ctr].oguard = OFF;
    set->modes[ctr].oguard_seq = 0;
  }
}

void load_modes_for_select (modes_ptr mdset, char idname[25]) {
        fscanf(fp,"%s %s",&p,&bp);
      //get_portrait((port_ptr)&data.smallpict,p);
      fscanf(fp,"%s%s",&bgname,&music);

      fscanf(fp, "%d", &mdset.total);

      if (mdset1.total > 6) {
        exit(-1);
        printf("%s has too many modes... exiting game", &filename);
        }

      for (int i = 0; i < mdset1.total; i++) {
        fscanf(fp,"%s", &trash);

        fscanf(fp,"%s%s%s",&mdset1.modes[i].ide_file,
                           &mdset1.modes[i].seq_file,
                           &mdset1.modes[i].cmd_file);

        fscanf(fp,"%s", &mdset1.modes[i].mode_name);
        fscanf(fp,"%s", &mdset1.modes[i].super_subset);
        fscanf(fp,"%s", &mdset1.modes[i].chaincombo);
        fscanf(fp,"%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",&mdset1.modes[i].odamage,
                                                     &mdset1.modes[i].ddamage,
                                                     &mdset1.modes[i].super_rate,
                                                     &mdset1.modes[i].air_block,
                                                     &mdset1.modes[i].limb_control,
                                                     &mdset1.modes[i].juggle,
                                                     &mdset1.modes[i].air_recovery,
                                                     &mdset1.modes[i].alpha_counter,
                                                     &mdset1.modes[i].alpha_counter_seq,
                                                     &mdset1.modes[i].fdash,
                                                     &mdset1.modes[i].fdash_seq,
                                                     &mdset1.modes[i].bdash,
                                                     &mdset1.modes[i].bdash_seq,
                                                     &mdset1.modes[i].oguard,
                                                     &mdset1.modes[i].oguard_seq);
         } // end for loop
        fclose(fp);
        } // end type 2 checking
}


void mode_select (char idname1[25], char idname2[25], int &player1mode, int &player2mode, int active) {

  FILE *fp;
  modeset mdset1;
  modeset mdset2;
  int who;

  if (active == 1) {
    if((fp = fopen(idname1,"rb")) == NULL) {
      exit(-1);
      printf("The file %s could not be opened. Exiting Program.",idname1);
      }

    fscanf(fp,"%s", &name);
    strcpy(data.name,name);

    fscanf(fp,"%d", &type);

    if (type == 0 || type == 1) {
      player1mode = DEFAULT;
      fclose(fp);
      }

    if (type == 2) {
      init_modes((modes_ptr)&mdset1);
  } // end active == 1


  if (active == 2) {
    if((fp = fopen(idname2,"rb")) == NULL) {
      exit(-1);
      printf("The file %s could not be opened.",idname2);
      }
    get_mode (mdset1, mdset2, idname2, active);
  }

  if (active == 3) {
    player1.get(idname1);
    player2.get(idname2);
  }


} // end mode_select


/*
void reference_mode_select (char idname1[25], char idname2[25], char config[25]) {

  static warrior player1;
  static warrior player2;

  char bigp[25];
  portrait pix[120];
  int p1on=0, p2on=0;
  int p1last=0, p2last=0;
  int p1done=0, p2done=0;

  char bgpicture[25];
  portrait bigpic;
  char bgmusic[25];
  MIDI *bgtune;
//  SAMPLE *bgsamp;
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
  static frameset fset1,fset2;
  static moveset mset1,mset2;

  if((fp = fopen(config,"rb")) == NULL) {
    printf("Could not open config file %s",config);
    }


  fscanf(fp,"%s",&bgpicture);
  get_portrait((port_ptr)&bigpic,bgpicture);
  y = 100 - (bigpic.height/2);

  fscanf(fp,"%s",&bgmusic);

  bgtune = load_midi(bgmusic);

  fscanf(fp,"%d %d",&rows,&cols);

  fscanf(fp,"%s",&ids[ctr]);

  while(strcmp(ids[ctr],"end")) {
    if((fp2 = fopen(ids[ctr],"rb")) == NULL) {
      printf("Couldn't open %s",ids[ctr]);
      exit(-1);
      }
    fscanf(fp2,"%s",&p1name);
    fscanf(fp2,"%d",&type);
    fscanf(fp2,"%s",&port);
    get_portrait((port_ptr)&pix[ctr],port);
    fclose(fp2);
    if(width<pix[ctr].width) width = pix[ctr].width;
    if(height<pix[ctr].height) height = pix[ctr].height;

    ctr++;
    fscanf(fp,"%s",&ids[ctr]);
    }

  last_id = ctr-1;
  fclose(fp);

  p1id = rand() % last_id;
  p2id = rand() % last_id;

  fp = fopen("p1.key","rb");
  fscanf(fp,"%d %d %d %d %d",&st1,&up1,&dn1,&lf1,&rt1);
  fclose(fp);

  fp = fopen("p2.key","rb");
  fscanf(fp,"%d %d %d %d %d",&st2,&up2,&dn2,&lf2,&rt2);
  fclose(fp);

  x = 160 - ((cols/2)*width);


  play_midi(bgtune,1);

  LOOP:
  delay(250);
  do {
    draw_portrait(0,y,(port_ptr)&bigpic,0);


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
        if(ctr*cols+ctr2 <= last_id) {
          draw_portrait(x+(ctr2*width),0+ctr*height,(port_ptr)&pix[ctr*cols+ctr2],0);
          }
        }
      }

    show_double_buffer(0,0);
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
  //destroy_sample(bgsamp);
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
}

*/