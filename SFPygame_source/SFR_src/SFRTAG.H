void warrior::tag_update(int control,int cpu, info_ptr opponent1,info_ptr opponent2,info_ptr opponent3,int target,int who)
{
  int value;

  value = 320;

  DECIDE:
  if(opponent1->alive)
  {
    if(value > abs(opponent1->p[0] - data.p[0]))
    {
      value = abs(opponent1->p[0] - data.p[0]);
      opnt = opponent1;
      goto DECIDE;
    }
  }

  if(opponent2->alive)
  {
    if(value > abs(opponent2->p[0] - data.p[0]))
    {
      value = abs(opponent2->p[0] - data.p[0]);
      opnt = opponent2;
      goto DECIDE;
    }
  }

  if(opponent3->alive)
  {
    if(value > abs(opponent3->p[0] - data.p[0]))
    {
      value = abs(opponent3->p[0] - data.p[0]);
      opnt = opponent3;
      goto DECIDE;
    }
  }

  if(target)
  {
    switch(who)
    {
      case 0:  opnt = opponent1;
               break;
      case 1:  opnt = opponent2;
               break;
      case 2:  opnt = opponent3;
               break;
    }
  }

  if(data.tagattack)
  {
    ai_special_handler();
    data.tagattack = 0;
  }

  if(data.tagsuper)
  {
    data.super = 120;
    ai_super_handler();
    data.tagsuper = 0;
  }

  if(opnt->alive)
  {
    if(data.curr_seq == 41 || data.curr_seq == 42)
    {
      data.curr_seq = 0;
      data.curr_frame = -1;
    }
  }

  update(control,cpu,opnt);
}

void interface::kof_update(info p1,info p2,info p3,info p4,info p5,info p6,int p1who,int p2who)
{
  int ctr;
  int ctr2;
  main_update(p1,p2);
  if(p1who < 2) draw_string(xoffset,yoffset+10+p1.smallpict.height+fnt.letheight,(font_ptr)&fnt,p3.name,'l',1);
  if(p1who < 1) draw_string(xoffset,yoffset+10+p1.smallpict.height+fnt.letheight*2,(font_ptr)&fnt,p5.name,'l',1);
  if(p2who < 2) draw_string(xoffset+320,yoffset+10+p2.smallpict.height+fnt.letheight,(font_ptr)&fnt,p4.name,'r',1);
  if(p2who < 1) draw_string(xoffset+320,yoffset+10+p2.smallpict.height+fnt.letheight*2,(font_ptr)&fnt,p6.name,'r',1);
}

void interface::cap_update(info p1,info p2,info p3,info p4,info p5,info p6,int p1who,int p2who)
{
  int ctr;
  int ctr2;
  info current1;
  info current2;

  if(p1who == 0)
  {
    current1 = p1;
    draw_string(xoffset,yoffset+10+p1.smallpict.height+fnt.letheight,(font_ptr)&fnt,p3.name,'l',1);
    for(ctr=0;ctr<p3.life;ctr++)
    {
      for(ctr2=0;ctr2<2;ctr2++)
      {
        put_pixel_b(xoffset+ctr,ctr2+yoffset+10+p1.smallpict.height+fnt.letheight*2,128);
      }
    }
  }
  else if(p1who == 1)
  {
    current1 = p3;
    draw_string(xoffset,yoffset+10+p3.smallpict.height+fnt.letheight,(font_ptr)&fnt,p1.name,'l',1);
    for(ctr=0;ctr<p1.life;ctr++)
    {
      for(ctr2=0;ctr2<2;ctr2++)
      {
        put_pixel_b(xoffset+ctr,ctr2+yoffset+10+p3.smallpict.height+fnt.letheight*2,128);
      }
    }
  }

  if(p2who == 0)
  {
    current2 = p2;
    draw_string(xoffset+320,yoffset+10+p2.smallpict.height+fnt.letheight,(font_ptr)&fnt,p4.name,'r',1);
    for(ctr=0;ctr<p4.life;ctr++)
    {
      for(ctr2=0;ctr2<2;ctr2++)
      {
        put_pixel_b(xoffset+320-ctr,ctr2+yoffset+10+p2.smallpict.height+fnt.letheight*2,128);
      }
    }
  }
  else if(p2who == 1)
  {
    current2 = p4;
    draw_string(xoffset+320,yoffset+10+p4.smallpict.height+fnt.letheight,(font_ptr)&fnt,p2.name,'r',1);
    for(ctr=0;ctr<p2.life;ctr++)
    {
      for(ctr2=0;ctr2<2;ctr2++)
      {
        put_pixel_b(xoffset+320-ctr,ctr2+yoffset+10+p4.smallpict.height+fnt.letheight*2,128);
      }
    }
  }
  main_update(current1,current2);

  /*
  draw_string(xoffset,yoffset+10+p1.smallpict.height+fnt.letheight,(font_ptr)&fnt,p3.name,'l',1);
  for(ctr=0;ctr<p3.life;ctr++)
  {
    for(ctr2=0;ctr2<2;ctr2++)
    {
      put_pixel_b(xoffset+ctr,ctr2+yoffset+10+p1.smallpict.height+fnt.letheight*2,128);
    }
  }


  draw_string(xoffset,yoffset+10+p1.smallpict.height+fnt.letheight*2+2,(font_ptr)&fnt,p5.name,'l',1);

  draw_string(xoffset+320,yoffset+10+p2.smallpict.height+fnt.letheight,(font_ptr)&fnt,p4.name,'r',1);
  for(ctr=0;ctr<p4.life;ctr++)
  {
    for(ctr2=0;ctr2<2;ctr2++)
    {
      put_pixel_b(xoffset+320-ctr,ctr2+yoffset+10+p2.smallpict.height+fnt.letheight*2,128);
    }
  }

  draw_string(xoffset+320,yoffset+10+p2.smallpict.height+fnt.letheight*2+2,(font_ptr)&fnt,p6.name,'r',1);*/
/*    if(type)
    {
      for(ctr=0;ctr<p6->life;ctr++)
      {
        for(ctr2=0;ctr2<2;ctr2++)
        {
          put_pixel_b(xoffset+320-ctr,ctr2+yoffset+10+p2->smallpict.height+fnt.letheight*2+2+fnt.letheight+2,128);
        }
      }
    }*/
}

int tagging_handler(info_ptr p1,info_ptr p2, int whoactive)
{
  int returnval;
  if(whoactive==0)
  {
    if((p2->alive) && (p2->p[0] <= 0 || p2->p[0] >= width))
    {
      p2->p[0] = p1->p[0];
      p2->curr_seq = 299;
      p2->curr_frame = -1;
      p2->curr_input = 'n';
      p2->second = p1->second;
      p2->super = p1->super;
      returnval = 1;
    }
  }
  else if(whoactive==1)
  {
    if((p1->alive) && (p1->p[0] <= 0 || p1->p[0] >= width))
    {
      p1->p[0] = p2->p[0];
      p1->curr_seq = 299;
      p1->curr_frame = -1;
      p1->curr_input = 'n';
      p1->second = p2->second;
      p1->super = p2->super;
      returnval = 0;
    }
  }
  return returnval;
}

void third_strike_handler(info_ptr p1,info_ptr p2,info_ptr p3,int whoactive)
{
  if((p3->p[0] <= 0 || p3->p[0] >= width) && (p3->alive))
  {
    p3->tagattack = 1;
    if(whoactive == 0)
    {
      if(!p1->second)
      {
        p3->p[0] = xoffset+40;
        p3->second = 0;
      }
      else
      {
        p3->p[0] = xoffset+280;
        p3->second = 1;
      }
    }
    else if(whoactive == 1)
    {
      if(!p2->second)
      {
        p3->p[0] = xoffset+40;
        p3->second = 0;
      }
      else
      {
        p3->p[0] = xoffset+280;
        p3->second = 1;
      }
    }
  }
}


void third_super_handler(info_ptr p1,info_ptr p2)
{
  if((p2->p[0] <= 0 || p2->p[0] >= width) && (p2->alive) && (p1->super >= 40))
  {
    p1->super -= 40;
    p2->tagsuper = 1;
    p2->second = p1->second;
    if(!p2->second) p2->p[0] = xoffset+40;
    else p2->p[0] = xoffset+280;
  }
}

int capcom_match(char idname1[25],char idname2[25],char idname3[25],char idname4[25],char idname5[25],char idname6[25],int active)
{
  static warrior leftfighters[3];
  static warrior rightfighters[3];
  info ldatas[3];
  info rdatas[3];
  int ctr;
  for(ctr=0;ctr<3;ctr++)
  {
    leftfighters[ctr].setup();
    leftfighters[ctr].import_controls("p1.key");
    rightfighters[ctr].setup();
    rightfighters[ctr].import_controls("p2.key");
  }

  leftfighters[0].get2(idname1);
  leftfighters[1].get2(idname2);
  leftfighters[2].get2(idname3);
  rightfighters[0].get2(idname4);
  rightfighters[1].get2(idname5);
  rightfighters[2].get2(idname6);

  background bg;
//  if(rand() % 100 > 50) bg.get(leftfighters[0].bgname);
//  else bg.get(rightfighters[0].bgname);
  int rightactive = 0;
  int leftactive = 0;

  int textpos = width/2 + 200;
  int copy = 0;
  int vgoff;
  int loop;
  int slowctr;
  int ai = 1;
  int returnval=0;
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
  int p1=0,p2=0;
  int whofirst=0;
  char name[25];
  int type;
  char p[25];
  char bigp[25];

  MIDI *bgmusic;
  SAMPLE *bgsamp;
  FILE *fp;

  int temp=0;
  char *sdk;
  int pause;
  int ctr2=0;

//  bgmusic = load_midi(sdk);
//  play_midi(bgmusic,1);
  if(active==0)
  {
    p1 = 1;
    p2 = 1;
    if(rand() % 100 > 50)
    {
      bg.get(leftfighters[0].bgname);
      bgmusic = load_midi(leftfighters[0].music);
    }
    else
    {
      bg.get(rightfighters[0].bgname);
      bgmusic = load_midi(rightfighters[0].music);
    }
  }
  else if(active==1)
  {
    p2 = 1;
    bg.get(rightfighters[0].bgname);
    bgmusic = load_midi(rightfighters[0].music);
  }
  else if(active==2)
  {
    p1 = 1;
    bg.get(leftfighters[0].bgname);
    bgmusic = load_midi(leftfighters[0].music);
  }
  else if(active==3)
  {
    if(rand() % 100 > 50)
    {
      bg.get(leftfighters[0].bgname);
      bgmusic = load_midi(leftfighters[0].music);
    }
    else
    {
      bg.get(rightfighters[0].bgname);
      bgmusic = load_midi(rightfighters[0].music);
    }
  }


  clear_screen();
  yoffset = height - 200;
  for(ctr=0;ctr<3;ctr++)
  {
    leftfighters[ctr].init(0,height-10,width/2 - (ctr+1)*50,0);
    rightfighters[ctr].init(1,height-10,width/2 + (ctr+1)*50,copy);
  }

  xoffset = (width / 2) - 160;

  loop=0;
  if(rand() % 100 < 50)
  {
    yoffset = 0;
    do
    {
      bg.update((info_ptr)&leftfighters[0].data,(info_ptr)&rightfighters[0].data,0);
      for(slowctr=0;slowctr<speed;slowctr++) wait4vsync();
      show_double_buffer(xoffset,yoffset,1);
      yoffset++;
      if(key_table[MAKE_ESC])
      {
        yoffset = height - 200;
      }
    } while(yoffset < height - 200);
  }

  yoffset = height - 200;
  for(ctr=0;ctr<3;ctr++)
  {
    leftfighters[ctr].data.p[0] = width/2 - (ctr+1)*50;
    rightfighters[ctr].data.p[0] = width/2 + (ctr+1)*50;
  }

  do
  {
    bg.update((info_ptr)&leftfighters[0].data,(info_ptr)&rightfighters[0].data,0);
    for(ctr=0;ctr<3;ctr++)
    {
      leftfighters[ctr].update(0,0,(info_ptr)&rightfighters[ctr].data);
      rightfighters[ctr].update(0,0,(info_ptr)&leftfighters[ctr].data);
    }
    for(slowctr=0;slowctr<speed;slowctr++) wait4vsync();
    show_double_buffer(xoffset,yoffset,1);
  } while(leftfighters[0].data.curr_seq != 0 || leftfighters[1].data.curr_seq != 0 || leftfighters[2].data.curr_seq != 0 || rightfighters[0].data.curr_seq != 0 || rightfighters[1].data.curr_seq != 0 || rightfighters[2].data.curr_seq != 0);


  for(ctr=1;ctr<3;ctr++)
  {
    leftfighters[ctr].data.curr_seq = 3;
    rightfighters[ctr].data.curr_seq = 3;
  }

  do
  {
    bg.update((info_ptr)&leftfighters[0].data,(info_ptr)&rightfighters[0].data,0);
    for(ctr=0;ctr<3;ctr++)
    {
      leftfighters[ctr].tag_update(0,0,(info_ptr)&rightfighters[0].data,(info_ptr)&rightfighters[1].data,(info_ptr)&rightfighters[2].data,0,0);
      rightfighters[ctr].tag_update(0,0,(info_ptr)&leftfighters[0].data,(info_ptr)&leftfighters[1].data,(info_ptr)&leftfighters[2].data,0,0);
    }
    for(slowctr=0;slowctr<speed;slowctr++) wait4vsync();
    show_double_buffer(xoffset,yoffset,1);
  } while(leftfighters[1].data.p[0] > 0 || leftfighters[2].data.p[0] > 0 || rightfighters[1].data.p[0] < width || rightfighters[2].data.p[0] < width && (!key_table[MAKE_ESC]));

  leftfighters[1].data.p[0] = 0;
  leftfighters[2].data.p[0] = 0;
  rightfighters[1].data.p[0] = width;
  rightfighters[2].data.p[0] = width;

  MATCH:

  do {
    bg.update((info_ptr)&leftfighters[leftactive].data,(info_ptr)&rightfighters[rightactive].data,0);
    for(ctr=0;ctr<3;ctr++)
    {
      leftfighters[ctr].tag_update(0,0,(info_ptr)&rightfighters[0].data,(info_ptr)&rightfighters[1].data,(info_ptr)&rightfighters[2].data,0,0);
      rightfighters[ctr].tag_update(0,0,(info_ptr)&leftfighters[0].data,(info_ptr)&leftfighters[1].data,(info_ptr)&leftfighters[2].data,0,0);
    }
//      face.update((info_ptr)&leftfighters[leftactive].data,(info_ptr)&rightfighters[rightactive].data);
//    face.kof_update(leftfighters[leftactive].data,rightfighters[rightactive].data,leftfighters[leftactive+1].data,rightfighters[rightactive+1].data,leftfighters[leftactive+2].data,rightfighters[rightactive+2].data,leftactive,rightactive);
    if(centext) draw_string(xoffset+160,yoffset+100,(font_ptr)&bgfnt,"READY",'c',1);
    else draw_string(textpos,yoffset+100,(font_ptr)&bgfnt,"READY",'l',1);
    for(slowctr=0;slowctr<speed;slowctr++) wait4vsync();
    show_double_buffer(xoffset,yoffset,1);
    textpos-=20;
    } while(textpos>xoffset-100);

  do {
    bg.update((info_ptr)&leftfighters[leftactive].data,(info_ptr)&rightfighters[rightactive].data,0);
    for(ctr=0;ctr<3;ctr++)
    {
      leftfighters[ctr].tag_update(0,0,(info_ptr)&rightfighters[0].data,(info_ptr)&rightfighters[1].data,(info_ptr)&rightfighters[2].data,0,0);
      rightfighters[ctr].tag_update(0,0,(info_ptr)&leftfighters[0].data,(info_ptr)&leftfighters[1].data,(info_ptr)&leftfighters[2].data,0,0);
    }
//      face.tag_update((info_ptr)&leftfighters[leftactive].data,(info_ptr)&rightfighters[rightactive].data);
//    face.kof_update(leftfighters[leftactive].data,rightfighters[rightactive].data,leftfighters[leftactive+1].data,rightfighters[rightactive+1].data,leftfighters[leftactive+2].data,rightfighters[rightactive+2].data,leftactive,rightactive);
    if(centext) draw_string(xoffset+160,yoffset+100,(font_ptr)&bgfnt,"FIGHT",'l',1);
    else draw_string(textpos,yoffset+100,(font_ptr)&bgfnt,"FIGHT",'l',1);
    for(slowctr=0;slowctr<speed;slowctr++) wait4vsync();
    show_double_buffer(xoffset,yoffset,1);
    textpos+=20;
    } while(textpos<xoffset+320);

  do
  {
    bg.update((info_ptr)&leftfighters[leftactive].data,(info_ptr)&rightfighters[rightactive].data,0);
    if(!leftfighters[0].data.alive) leftactive = 1;
    if(!leftfighters[1].data.alive) leftactive = 0;
    if(!rightfighters[0].data.alive) rightactive = 1;
    if(!rightfighters[1].data.alive) rightactive = 0;

    for(ctr=0;ctr<3;ctr++)
    {

      if(ctr==leftactive)
      {
        leftfighters[ctr].tag_update(1,p1,(info_ptr)&rightfighters[0].data,(info_ptr)&rightfighters[1].data,(info_ptr)&rightfighters[2].data,1,rightactive);
        if(leftfighters[ctr].data.curr_input == 'h') leftactive = tagging_handler((info_ptr)&leftfighters[0].data,(info_ptr)&leftfighters[1].data,ctr);
        else if(leftfighters[ctr].data.curr_input == 'm') third_strike_handler((info_ptr)&leftfighters[0].data,(info_ptr)&leftfighters[1].data,(info_ptr)&leftfighters[2].data,ctr);
        else if(leftfighters[ctr].data.curr_input == 'w') third_super_handler((info_ptr)&leftfighters[leftactive].data,(info_ptr)&leftfighters[2].data);
      }
      else
      {
        leftfighters[ctr].tag_update(0,p1,(info_ptr)&rightfighters[0].data,(info_ptr)&rightfighters[1].data,(info_ptr)&rightfighters[2].data,1,rightactive);
        if(leftfighters[ctr].data.alive)
        {
          if(leftfighters[ctr].data.curr_seq == 0) leftfighters[ctr].data.curr_seq = 3;
          leftfighters[ctr].data.curr_input = 'n';
        }
      }

      if(ctr==rightactive)
      {
        rightfighters[ctr].tag_update(1,p2,(info_ptr)&leftfighters[0].data,(info_ptr)&leftfighters[1].data,(info_ptr)&leftfighters[2].data,1,leftactive);
        if(rightfighters[ctr].data.curr_input == 'h') rightactive = tagging_handler((info_ptr)&rightfighters[0].data,(info_ptr)&rightfighters[1].data,ctr);
        else if(rightfighters[ctr].data.curr_input == 'm') third_strike_handler((info_ptr)&rightfighters[0].data,(info_ptr)&rightfighters[1].data,(info_ptr)&rightfighters[2].data,ctr);
        else if(rightfighters[ctr].data.curr_input == 'w') third_super_handler((info_ptr)&rightfighters[rightactive].data,(info_ptr)&rightfighters[2].data);
      }
      else
      {
        rightfighters[ctr].tag_update(0,p1,(info_ptr)&leftfighters[0].data,(info_ptr)&leftfighters[1].data,(info_ptr)&leftfighters[2].data,1,rightactive);
        if(rightfighters[ctr].data.alive)
        {
          if(rightfighters[ctr].data.curr_seq == 0) rightfighters[ctr].data.curr_seq = 3;
          rightfighters[ctr].data.curr_input = 'n';
        }
      }
    }
    face.cap_update(leftfighters[0].data,rightfighters[0].data,leftfighters[1].data,rightfighters[1].data,leftfighters[2].data,rightfighters[2].data,leftactive,rightactive);
    for(slowctr=0;slowctr<speed;slowctr++) wait4vsync();
    show_double_buffer(xoffset,yoffset,1);

    if(key_table[MAKE_ESC])
    {
//      destroy_midi(bgmusic);
      return 0;
    }
  } while(leftfighters[leftactive].data.alive && rightfighters[rightactive].data.alive);

  if(!leftfighters[leftactive].data.alive)
  {
    rightfighters[rightactive].data.curr_seq = 0;
    rightfighters[rightactive].data.curr_frame = -1;
    if(leftactive == 0) leftactive = 1;
    else if(leftactive == 1) leftactive = 0;
    if(!leftfighters[leftactive].data.alive)
    {
      returnval = 2;
      goto END;
    }
    leftfighters[leftactive].data.p[0] = xoffset + 40;
    leftfighters[leftactive].data.second = 0;
    rightfighters[rightactive].data.second = 1;
    leftfighters[leftactive].data.curr_seq = 299;
    leftfighters[leftactive].data.curr_frame = -1;
  }

  if(!rightfighters[rightactive].data.alive)
  {
    leftfighters[leftactive].data.curr_seq = 0;
    leftfighters[leftactive].data.curr_frame = -1;

    if(rightactive == 0) rightactive = 1;
    else if(rightactive == 1) rightactive = 0;
    if(!rightfighters[rightactive].data.alive)
    {
      returnval = 1;
      goto END;
    }
    rightfighters[rightactive].data.p[0] = xoffset + 280;
    rightfighters[rightactive].data.second = 1;
    leftfighters[leftactive].data.second = 0;
    rightfighters[rightactive].data.curr_seq = 299;
    rightfighters[rightactive].data.curr_frame = -1;
  }

  do
  {
    bg.update((info_ptr)&leftfighters[leftactive].data,(info_ptr)&rightfighters[rightactive].data,0);
    for(ctr=0;ctr<3;ctr++)
    {
      leftfighters[ctr].tag_update(0,0,(info_ptr)&rightfighters[0].data,(info_ptr)&rightfighters[1].data,(info_ptr)&rightfighters[2].data,0,0);
      rightfighters[ctr].tag_update(0,0,(info_ptr)&leftfighters[0].data,(info_ptr)&leftfighters[1].data,(info_ptr)&leftfighters[2].data,0,0);
    }
    for(slowctr=0;slowctr<speed;slowctr++) wait4vsync();
    show_double_buffer(xoffset,yoffset,1);
    if(key_table[MAKE_ESC])
    {
//      destroy_midi(bgmusic);
      return 0;
    }
  } while(leftfighters[leftactive].data.curr_seq != 0 || rightfighters[rightactive].data.curr_seq != 0);

  goto MATCH;

  //data.p[0] > 0 || leftfighters[2].data.p[0] > 0 || rightfighters[1].data.p[0] < width || rightfighters[2].data.p[0] < width && (!key_table[MAKE_ESC]));

  //(leftfighters[0].data.alive || leftfighters[1].data.alive) && (rightfighters[0].data.alive || rightfighters[1].data.alive));

  END:
  loop = 0;
  do
  {
    bg.update((info_ptr)&leftfighters[leftactive].data,(info_ptr)&rightfighters[rightactive].data,0);
    for(ctr=0;ctr<3;ctr++)
    {
      leftfighters[ctr].tag_update(0,0,(info_ptr)&rightfighters[0].data,(info_ptr)&rightfighters[1].data,(info_ptr)&rightfighters[2].data,0,0);
      rightfighters[ctr].tag_update(0,0,(info_ptr)&leftfighters[0].data,(info_ptr)&leftfighters[1].data,(info_ptr)&leftfighters[2].data,0,0);
    }
    for(slowctr=0;slowctr<speed;slowctr++) wait4vsync();
    show_double_buffer(xoffset,yoffset,1);
    if(key_table[MAKE_ESC])
    {
//      destroy_midi(bgmusic);
      return 0;
    }
    loop++;
  } while(loop < maxloops);
//  destroy_midi(bgmusic);
  return returnval;
}
/*
int tag_match(char idname1[25],char idname2[25],char idname3[25],char idname4[25],char idname5[25],char idname6[25],int active)
{
  static warrior leftfighters[3];
  static warrior rightfighters[3];
  int ctr;
  int p1=0,p2=0;
  for(ctr=0;ctr<3;ctr++)
  {
    leftfighters[ctr].setup();
    leftfighters[ctr].import_controls("p1.key");
    rightfighters[ctr].setup();
    rightfighters[ctr].import_controls("p2.key");
  }

  leftfighters[0].get2(idname1);
  leftfighters[1].get2(idname2);
  leftfighters[2].get2(idname3);
  rightfighters[0].get2(idname4);
  rightfighters[1].get2(idname5);
  rightfighters[2].get2(idname6);

  background bg;

  MIDI *bgmusic;

  if(active==0)
  {
    p1 = 1;
    p2 = 1;
    if(rand() % 100 > 50)
    {
      bg.get(leftfighters[0].bgname);
      bgmusic = load_midi(leftfighters[0].music);
    }
    else
    {
      bg.get(rightfighters[0].bgname);
      bgmusic = load_midi(rightfighters[0].music);
    }
  }
  else if(active==1)
  {
    p2 = 1;
    bg.get(rightfighters[0].bgname);
    bgmusic = load_midi(rightfighters[0].music);
  }
  else if(active==2)
  {
    p1 = 1;
    bg.get(leftfighters[0].bgname);
    bgmusic = load_midi(leftfighters[0].music);
  }
  else if(active==3)
  {
    if(rand() % 100 > 50)
    {
      bg.get(leftfighters[0].bgname);
      bgmusic = load_midi(leftfighters[0].music);
    }
    else
    {
      bg.get(rightfighters[0].bgname);
      bgmusic = load_midi(rightfighters[0].music);
    }
  }

  int rightactive = 0;
  int leftactive = 0;

  int textpos = width/2 + 200;
  int copy = 0;
  int vgoff;
  int loop;
  int slowctr;
  int ai = 1;
  int returnval=0;
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
  int whofirst=0;
  char name[25];
  int type;
  char p[25];
  char bigp[25];

  //MIDI *bgmusic;
  //SAMPLE *bgsamp;
  FILE *fp;

  int temp=0;
  char *sdk;
  int pause;

//  bgmusic = load_midi(sdk);
//  play_midi(bgmusic,1);

  clear_screen();
  yoffset = height - 200;
  for(ctr=0;ctr<3;ctr++)
  {
    leftfighters[ctr].init(0,height-10,width/2 - (ctr+1)*50,0);
    rightfighters[ctr].init(1,height-10,width/2 + (ctr+1)*50,copy);
  }

  leftfighters[1].data.p[0] = 0;
  leftfighters[2].data.p[0] = 0;
  rightfighters[1].data.p[0] = width;
  rightfighters[2].data.p[0] = width;

  xoffset = (width / 2) - 160;

  loop=0;

  yoffset = height - 200;

  do
  {
    bg.update((info_ptr)&leftfighters[leftactive].data,(info_ptr)&rightfighters[rightactive].data,0);
    leftfighters[leftactive].tag_update(0,p1,(info_ptr)&rightfighters[0].data,(info_ptr)&rightfighters[1].data,(info_ptr)&rightfighters[2].data,0,0);
    rightfighters[rightactive].tag_update(0,p2,(info_ptr)&leftfighters[0].data,(info_ptr)&leftfighters[1].data,(info_ptr)&leftfighters[2].data,0,0);
    for(slowctr=0;slowctr<speed;slowctr++) wait4vsync();
    show_double_buffer(xoffset,yoffset,1);
  } while(leftfighters[leftactive].data.curr_seq != 0 || rightfighters[rightactive].data.curr_seq != 0);

  do
  {
    bg.update((info_ptr)&leftfighters[0].data,(info_ptr)&rightfighters[0].data,0);
    for(ctr=0;ctr<3;ctr++)
    {
      if(ctr==leftactive)
      {
        leftfighters[ctr].tag_update(1,0,(info_ptr)&rightfighters[0].data,(info_ptr)&rightfighters[1].data,(info_ptr)&rightfighters[2].data,0);
        if(leftfighters[ctr].data.curr_input == 'w')
        {
          if(leftactive==0)
          {
            leftfighters[1].data.curr_seq = 45;
            leftfighters[1].data.curr_frame = -1;
            leftfighters[1].data.p[0] = leftfighters[0].data.p[0];
          }
          else
          {
            leftactive = 0;
          }
        }
        if(leftfighters[ctr].data.curr_input == 'm')
        {
          if(leftactive==1)
          {
            leftfighters[2].data.curr_seq = 45;
            leftfighters[2].data.curr_frame = -1;
            leftfighters[2].data.p[0] = leftfighters[1].data.p[0];
          }
          else
          {
            leftactive = 1;
          }
        }
        if(leftfighters[ctr].data.curr_input == 'h')
        {
          if(leftactive==2)
          {
            leftfighters[0].data.curr_seq = 45;
            leftfighters[0].data.curr_frame = -1;
            leftfighters[0].data.p[0] = leftfighters[2].data.p[0];
          }
          else
          {
            leftactive = 2;
          }
        }
        if(leftactive==0)
        {
          if(!leftfighters[ctr].data.alive) leftactive = 1;
        }
        else if(leftactive == 1)
        {
          if(!leftfighters[ctr].data.alive) leftactive = 2;
        }
        else if(leftactive == 2)
        {
          if(!leftfighters[ctr].data.alive) leftactive = 0;
        }
      }
      else
      {
        if(leftfighters[ctr].data.second) leftfighters[ctr].data.p[0]++;
        else leftfighters[ctr].data.p[0]--;
        leftfighters[ctr].tag_update(0,1,(info_ptr)&rightfighters[0].data,(info_ptr)&rightfighters[1].data,(info_ptr)&rightfighters[2].data,0);
      }
      if(ctr==rightactive)
      {
        rightfighters[ctr].tag_update(1,0,(info_ptr)&leftfighters[0].data,(info_ptr)&leftfighters[1].data,(info_ptr)&leftfighters[2].data,0);
        if(rightfighters[ctr].data.curr_input == 'w')
        {
          if(rightactive==0)
          {
            rightfighters[1].data.curr_seq = 45;
            rightfighters[1].data.curr_frame = -1;
            rightfighters[1].data.p[0] = rightfighters[0].data.p[0];
          }
          else
          {
            rightactive = 0;
          }
        }
        if(rightfighters[ctr].data.curr_input == 'm')
        {
          if(rightactive==1)
          {
            rightfighters[2].data.curr_seq = 45;
            rightfighters[2].data.curr_frame = -1;
            rightfighters[2].data.p[0] = rightfighters[1].data.p[0];
          }
          else
          {
            rightactive = 1;
          }
        }
        if(rightfighters[ctr].data.curr_input == 'h')
        {
          if(rightactive==2)
          {
            rightfighters[0].data.curr_seq = 45;
            rightfighters[0].data.curr_frame = -1;
            rightfighters[0].data.p[0] = rightfighters[2].data.p[0];
          }
          else
          {
            rightactive = 2;
          }
        }
        if(rightactive==0)
        {
          if(!rightfighters[ctr].data.alive) rightactive = 1;
        }
        else if(rightactive == 1)
        {
          if(!rightfighters[ctr].data.alive) rightactive = 2;
        }
        else if(rightactive == 2)
        {
          if(!rightfighters[ctr].data.alive) rightactive = 0;
        }
      }
      else
      {
        if(rightfighters[ctr].data.second) rightfighters[ctr].data.p[0]++;
        else rightfighters[ctr].data.p[0]--;
        rightfighters[ctr].tag_update(0,1,(info_ptr)&leftfighters[0].data,(info_ptr)&leftfighters[1].data,(info_ptr)&leftfighters[2].data,0);
      }
    }
    //face.update((info_ptr)&player1.data,(info_ptr)&player2.data);
    for(slowctr=0;slowctr<speed;slowctr++) wait4vsync();
    show_double_buffer(xoffset,yoffset,1);

    if(key_table[MAKE_ESC])
    {
//      destroy_midi(bgmusic);
      return 0;
    }
  } while((leftfighters[0].data.alive || leftfighters[1].data.alive || leftfighters[2].data.alive) && (rightfighters[0].data.alive || rightfighters[1].data.alive || rightfighters[2].data.alive));


//  destroy_midi(bgmusic);
  return returnval;
} */

int kof_match(char idname1[25],char idname2[25],char idname3[25],char idname4[25],char idname5[25],char idname6[25],int active)
{
  static warrior leftfighters[3];
  static warrior rightfighters[3];
  int ctr;
  for(ctr=0;ctr<3;ctr++)
  {
    leftfighters[ctr].setup();
    leftfighters[ctr].import_controls("p1.key");
    rightfighters[ctr].setup();
    rightfighters[ctr].import_controls("p2.key");
  }

  leftfighters[0].get2(idname1);
  leftfighters[1].get2(idname2);
  leftfighters[2].get2(idname3);
  rightfighters[0].get2(idname4);
  rightfighters[1].get2(idname5);
  rightfighters[2].get2(idname6);

  background bg;

  int rightactive = 0;
  int leftactive = 0;

  int textpos = width/2 + 200;
  int copy = 0;
  int vgoff;
  int loop;
  int slowctr;
  int ai = 1;
  int returnval=1;

  int maxloops=100;
  //if(!strcmp(idname1,idname2)) copy = 1;
  int round=1;
  int cpu = 0;//stuff;
  char name[25];
  int type;
  char p[25];
  char bigp[25];
  int p1=0,p2=0;
  int whofirst=0;
  int super_killed=0,p1kill=0,p2kill=0;

  MIDI *bgmusic;
  SAMPLE *bgsamp;

  if(active==0)
  {
    p1 = 1;
    p2 = 1;
    if(rand() % 100 > 50)
    {
      bg.get(leftfighters[0].bgname);
      bgmusic = load_midi(leftfighters[0].music);
    }
    else
    {
      bg.get(rightfighters[0].bgname);
      bgmusic = load_midi(rightfighters[0].music);
    }
  }
  else if(active==1)
  {
    p2 = 1;
    bg.get(rightfighters[0].bgname);
    bgmusic = load_midi(rightfighters[0].music);
  }
  else if(active==2)
  {
    p1 = 1;
    bg.get(leftfighters[0].bgname);
    bgmusic = load_midi(leftfighters[0].music);
  }
  else if(active==3)
  {
    if(rand() % 100 > 50)
    {
      bg.get(leftfighters[0].bgname);
      bgmusic = load_midi(leftfighters[0].music);
    }
    else
    {
      bg.get(rightfighters[0].bgname);
      bgmusic = load_midi(rightfighters[0].music);
    }
  }

  int temp=0;
  char *sdk;
  int pause;


  int leftx;
  int rightx;
  int lefty;
  int righty;

  portrait lefts[3],rights[3];
  FILE *fp;

  fp = fopen(idname1,"rb");
  fscanf(fp,"%s",&name);
  fscanf(fp,"%d",&type);
  fscanf(fp,"%s %s",&p,&bigp);
  fclose(fp);
  get_portrait((port_ptr)&lefts[0],bigp);

  fp = fopen(idname2,"rb");
  fscanf(fp,"%s",&name);
  fscanf(fp,"%d",&type);
  fscanf(fp,"%s %s",&p,&bigp);
  fclose(fp);
  get_portrait((port_ptr)&lefts[1],bigp);

  fp = fopen(idname3,"rb");
  fscanf(fp,"%s",&name);
  fscanf(fp,"%d",&type);
  fscanf(fp,"%s %s",&p,&bigp);
  fclose(fp);
  get_portrait((port_ptr)&lefts[2],bigp);

  fp = fopen(idname4,"rb");
  fscanf(fp,"%s",&name);
  fscanf(fp,"%d",&type);
  fscanf(fp,"%s %s",&p,&bigp);
  fclose(fp);
  get_portrait((port_ptr)&rights[0],bigp);

  fp = fopen(idname5,"rb");
  fscanf(fp,"%s",&name);
  fscanf(fp,"%d",&type);
  fscanf(fp,"%s %s",&p,&bigp);
  fclose(fp);
  get_portrait((port_ptr)&rights[1],bigp);

  fp = fopen(idname6,"rb");
  fscanf(fp,"%s",&name);
  fscanf(fp,"%d",&type);
  fscanf(fp,"%s %s",&p,&bigp);
  fclose(fp);
  get_portrait((port_ptr)&rights[2],bigp);

  static interface face;

  do
  {
  //  copy = 0;
    clear_screen();
    play_midi(bgmusic,1);
    yoffset = height - 200;

    leftfighters[leftactive].init(0,height-10,width/2 - 75,0);
    rightfighters[rightactive].init(1,height-10,width/2 + 75,copy);

    xoffset = (width / 2) - 160;
    textpos = xoffset+420;

    leftx = xoffset - lefts[leftactive].width;
    rightx = xoffset + 320;
    lefty = yoffset + 100 - (lefts[leftactive].height/2);
    righty = yoffset + 100 - (rights[rightactive].height/2);

    loop=0;
    if(round == 1)
    {
      yoffset = 0;
      do
      {
        bg.update((info_ptr)&leftfighters[leftactive].data,(info_ptr)&rightfighters[rightactive].data,0);
        for(slowctr=0;slowctr<speed;slowctr++) wait4vsync();
        show_double_buffer(xoffset,yoffset,1);
        yoffset++;
        if(key_table[MAKE_ESC])
        {
          yoffset = height - 200;
        }
      } while(yoffset < height - 200);
    }

    yoffset = height - 200;

    do
    {
      bg.update((info_ptr)&leftfighters[leftactive].data,(info_ptr)&rightfighters[rightactive].data,0);
      draw_portrait(leftx,yoffset,(port_ptr)&lefts[leftactive],0);
      draw_portrait(rightx,yoffset+200-rights[rightactive].height-bgfnt.letheight,(port_ptr)&rights[rightactive],1);
      draw_string(xoffset+160,yoffset+100,(font_ptr)&bgfnt,"VS",'c',1);
      for(slowctr=0;slowctr<speed;slowctr++) wait4vsync();
      show_double_buffer(xoffset,yoffset,1);
      if(leftx < xoffset) leftx += 10;
      if(rightx > xoffset+320-rights[rightactive].width) rightx -= 10;
      if(key_table[MAKE_ESC])
      {
          leftx = xoffset;
          rightx = xoffset+320-rights[rightactive].width;
      }
    } while((leftx < xoffset) || (rightx > xoffset+320-rights[rightactive].width));

    do
    {
      bg.update((info_ptr)&leftfighters[leftactive].data,(info_ptr)&rightfighters[rightactive].data,0);
      draw_portrait(leftx,yoffset,(port_ptr)&lefts[leftactive],0);
      draw_portrait(rightx,yoffset+200-rights[rightactive].height-bgfnt.letheight,(port_ptr)&rights[rightactive],1);
      draw_string(xoffset+160,yoffset+100,(font_ptr)&bgfnt,"VS",'c',1);
      draw_string(xoffset,yoffset+lefts[leftactive].height,(font_ptr)&bgfnt,leftfighters[leftactive].data.name,'l',1);
      draw_string(xoffset+320,yoffset+200-bgfnt.letheight,(font_ptr)&bgfnt,rightfighters[rightactive].data.name,'r',1);

      for(slowctr=0;slowctr<speed;slowctr++) wait4vsync();
      show_double_buffer(xoffset,yoffset,1);
      if(leftx < xoffset) leftx += 2;
      if(rightx > xoffset+320-rights[rightactive].width) rightx -= 2;
      loop++;
      if(key_table[MAKE_ESC])
      {
          loop = maxloops;
      }
    } while(loop < maxloops / 2);

    do
    {
      bg.update((info_ptr)&leftfighters[leftactive].data,(info_ptr)&rightfighters[rightactive].data,0);
      leftfighters[leftactive].update(0,p1,(info_ptr)&rightfighters[rightactive].data);
      rightfighters[rightactive].update(0,p2,(info_ptr)&leftfighters[leftactive].data);

      for(slowctr=0;slowctr<speed;slowctr++) wait4vsync();
      show_double_buffer(xoffset,yoffset,1);
    } while(leftfighters[leftactive].data.curr_seq != 0 || rightfighters[rightactive].data.curr_seq != 0);

    do {
      bg.update((info_ptr)&leftfighters[leftactive].data,(info_ptr)&rightfighters[rightactive].data,0);
      leftfighters[leftactive].update(0,p1,(info_ptr)&rightfighters[rightactive].data);
      rightfighters[rightactive].update(0,p2,(info_ptr)&leftfighters[leftactive].data);
//      face.update((info_ptr)&leftfighters[leftactive].data,(info_ptr)&rightfighters[rightactive].data);
      face.kof_update(leftfighters[leftactive].data,rightfighters[rightactive].data,leftfighters[leftactive+1].data,rightfighters[rightactive+1].data,leftfighters[leftactive+2].data,rightfighters[rightactive+2].data,leftactive,rightactive);
      if(centext) draw_string(xoffset+160,yoffset+100,(font_ptr)&bgfnt,"ROUND",'c',1);
      else draw_string(textpos,yoffset+100,(font_ptr)&bgfnt,"ROUND",'l',1);
      if(centext) draw_num(xoffset+160,yoffset+100+bgfnt.letheight,(font_ptr)&bgfnt,round,'c',1);
      draw_num(textpos+6*bgfnt.letwidth,yoffset+100,(font_ptr)&bgfnt,round,'l',1);
      for(slowctr=0;slowctr<speed;slowctr++) wait4vsync();
      show_double_buffer(xoffset,yoffset,1);
      textpos-=20;
      } while(textpos>xoffset-100);

    do {
      bg.update((info_ptr)&leftfighters[leftactive].data,(info_ptr)&rightfighters[rightactive].data,0);
      leftfighters[leftactive].update(0,p1,(info_ptr)&rightfighters[rightactive].data);
      rightfighters[rightactive].update(0,p2,(info_ptr)&leftfighters[leftactive].data);
//      face.tag_update((info_ptr)&leftfighters[leftactive].data,(info_ptr)&rightfighters[rightactive].data);
      face.kof_update(leftfighters[leftactive].data,rightfighters[rightactive].data,leftfighters[leftactive+1].data,rightfighters[rightactive+1].data,leftfighters[leftactive+2].data,rightfighters[rightactive+2].data,leftactive,rightactive);
      if(centext) draw_string(xoffset+160,yoffset+100,(font_ptr)&bgfnt,"FIGHT",'l',1);
      else draw_string(textpos,yoffset+100,(font_ptr)&bgfnt,"FIGHT",'l',1);
      for(slowctr=0;slowctr<speed;slowctr++) wait4vsync();
      show_double_buffer(xoffset,yoffset,1);
      textpos+=20;
      } while(textpos<xoffset+320);



    do
    {
      if(leftfighters[leftactive].data.obox.active) whofirst = 0;
      if(rightfighters[rightactive].data.obox.active) whofirst = 1;
      bg.update((info_ptr)&leftfighters[leftactive].data,(info_ptr)&rightfighters[rightactive].data,0);
      if(whofirst)
      {
        leftfighters[leftactive].update(1,p1,(info_ptr)&rightfighters[rightactive].data);
        rightfighters[rightactive].update(1,p2,(info_ptr)&leftfighters[leftactive].data);
      }
      else
      {
        rightfighters[rightactive].update(1,p2,(info_ptr)&leftfighters[leftactive].data);
        leftfighters[leftactive].update(1,p1,(info_ptr)&rightfighters[rightactive].data);
      }


      face.kof_update(leftfighters[leftactive].data,rightfighters[rightactive].data,leftfighters[leftactive+1].data,rightfighters[rightactive+1].data,leftfighters[leftactive+2].data,rightfighters[rightactive+2].data,leftactive,rightactive);
//      face.update((info_ptr)&leftfighters[leftactive].data,(info_ptr)&rightfighters[rightactive].data);
      for(slowctr=0;slowctr<speed;slowctr++) wait4vsync();
      show_double_buffer(xoffset,yoffset,1);

      if(key_table[MAKE_ESC])
      {
        destroy_midi(bgmusic);
        return 0;
      }
    } while(leftfighters[leftactive].data.alive && rightfighters[rightactive].data.alive);

    super_killed = 0;

    if(leftfighters[leftactive].data.super_kill || rightfighters[rightactive].data.super_kill)
    {
      super_killed=1;
      if(leftfighters[leftactive].data.super_kill) p1kill=1;
      else p1kill = 0;
      if(rightfighters[rightactive].data.super_kill) p2kill=1;
      else p2kill = 0;
      textpos = xoffset+320;
      do
      {
        bg.update((info_ptr)&leftfighters[leftactive].data,(info_ptr)&rightfighters[rightactive].data,1);
        if(whofirst)
        {
          leftfighters[leftactive].update(0,p1,(info_ptr)&rightfighters[rightactive].data);
          rightfighters[rightactive].update(0,p2,(info_ptr)&leftfighters[leftactive].data);
        }
        else
        {
          rightfighters[rightactive].update(0,p2,(info_ptr)&leftfighters[leftactive].data);
          leftfighters[leftactive].update(0,p1,(info_ptr)&rightfighters[rightactive].data);
        }
        if(super_killed)
        {
          if(p1kill)
          {
            if(strcmp(leftfighters[leftactive].data.super_name,"NONAME"))
            {
              draw_string(xoffset+textpos,50+yoffset,(font_ptr)&hugefnt,leftfighters[leftactive].data.super_name,'l',1);
              draw_string(xoffset+textpos,50+yoffset+hugefnt.letheight,(font_ptr)&hugefnt,leftfighters[leftactive].data.super_name,'l',1);
              draw_string(xoffset+textpos,50+yoffset+hugefnt.letheight*2,(font_ptr)&hugefnt,leftfighters[leftactive].data.super_name,'l',1);
            }
          }
          if(p2kill)
          {
            if(strcmp(rightfighters[rightactive].data.super_name,"NONAME"))
            {
              draw_string(xoffset+textpos,50+yoffset,(font_ptr)&hugefnt,rightfighters[rightactive].data.super_name,'l',1);
              draw_string(xoffset+textpos,50+yoffset+hugefnt.letheight,(font_ptr)&hugefnt,rightfighters[rightactive].data.super_name,'l',1);
              draw_string(xoffset+textpos,50+yoffset+hugefnt.letheight*2,(font_ptr)&hugefnt,rightfighters[rightactive].data.super_name,'l',1);
            }
          }
        }
        for(slowctr=0;slowctr<speed*2;slowctr++) wait4vsync();
        show_double_buffer(xoffset,yoffset,0);
        textpos-=20;
        if(key_table[MAKE_ESC])
        {
          destroy_midi(bgmusic);
          leftfighters[leftactive].data.super_kill = 0;
          rightfighters[rightactive].data.super_kill = 0;
        }
      } while((leftfighters[leftactive].data.curr_seq != 43 && rightfighters[rightactive].data.curr_seq != 43) || (leftfighters[leftactive].data.super_kill && rightfighters[rightactive].data.super_kill));
    }

    loop = 0;

//    play_sample(systemsounds[1],sfxvolume,125,1000,0);
    do {
      bg.update((info_ptr)&leftfighters[leftactive].data,(info_ptr)&rightfighters[rightactive].data,0);
      if(whofirst)
      {
        leftfighters[leftactive].update(1,p1,(info_ptr)&rightfighters[rightactive].data);
        rightfighters[rightactive].update(1,p2,(info_ptr)&leftfighters[leftactive].data);
      }
      else
      {
        rightfighters[rightactive].update(1,p2,(info_ptr)&leftfighters[leftactive].data);
        leftfighters[leftactive].update(1,p1,(info_ptr)&rightfighters[rightactive].data);
      }
      face.kof_update(leftfighters[leftactive].data,rightfighters[rightactive].data,leftfighters[leftactive+1].data,rightfighters[rightactive+1].data,leftfighters[leftactive+2].data,rightfighters[rightactive+2].data,leftactive,rightactive);
      if(leftfighters[leftactive].data.curr_seq == 43) {
        draw_string(xoffset+130,yoffset+50,(font_ptr)&bgfnt,rightfighters[rightactive].data.name,'l',1);
        }
      else if(rightfighters[rightactive].data.curr_seq == 43) {
        draw_string(xoffset+130,yoffset+50,(font_ptr)&bgfnt,leftfighters[leftactive].data.name,'l',1);
        }
      else if(leftfighters[leftactive].data.curr_seq == 43 && rightfighters[rightactive].data.curr_seq == 43) draw_string(xoffset+130,yoffset+50,(font_ptr)&bgfnt,"NO",'l',1);
      if(leftfighters[leftactive].data.curr_seq == 43 || rightfighters[rightactive].data.curr_seq == 43) draw_string(xoffset+130,yoffset+75,(font_ptr)&bgfnt,"WINS",'l',1);
      if(super_killed)
      {
        if(p1kill)
        {
          if(strcmp(leftfighters[leftactive].data.super_name,"NONAME"))
          {
            draw_string(xoffset+textpos,50+yoffset,(font_ptr)&hugefnt,leftfighters[leftactive].data.super_name,'l',1);
            draw_string(xoffset+textpos,50+yoffset+hugefnt.letheight,(font_ptr)&hugefnt,leftfighters[leftactive].data.super_name,'l',1);
            draw_string(xoffset+textpos,50+yoffset+hugefnt.letheight*2,(font_ptr)&hugefnt,leftfighters[leftactive].data.super_name,'l',1);
          }
        }
        if(p2kill)
        {
          if(strcmp(rightfighters[rightactive].data.super_name,"NONAME"))
          {
            draw_string(xoffset+textpos,50+yoffset,(font_ptr)&hugefnt,rightfighters[rightactive].data.super_name,'l',1);
            draw_string(xoffset+textpos,50+yoffset+hugefnt.letheight,(font_ptr)&hugefnt,rightfighters[rightactive].data.super_name,'l',1);
            draw_string(xoffset+textpos,50+yoffset+hugefnt.letheight*2,(font_ptr)&hugefnt,rightfighters[rightactive].data.super_name,'l',1);
          }
        }
      }
      for(slowctr=0;slowctr<speed;slowctr++) wait4vsync();
      show_double_buffer(xoffset,yoffset,1);
      loop++;
      textpos-=20;

      } while(loop < maxloops);

    round++;
    if(!leftfighters[leftactive].data.alive)
    {
      leftactive++;
      bgmusic = load_midi(leftfighters[leftactive].music);
    }
    if(!rightfighters[rightactive].data.alive)
    {
      rightactive++;
      bgmusic = load_midi(rightfighters[rightactive].music);
    }
  } while((rightactive != 3) && (leftactive != 3));

  loop = 0;

  do
  {
    bg.update((info_ptr)&leftfighters[leftactive].data,(info_ptr)&rightfighters[rightactive].data,1);
    if(rightactive == 3)
    {
      if(leftactive == 0)
      {
        draw_portrait(xoffset+160-(lefts[leftactive].width/2)-lefts[1].width,yoffset+100-(lefts[1].height/2),(port_ptr)&lefts[1],0);
        draw_portrait(xoffset+160+(lefts[leftactive].width/2),yoffset+100-(lefts[2].height/2),(port_ptr)&lefts[2],0);
      }
      else if(leftactive == 1)
      {
        draw_portrait(xoffset+160-(lefts[leftactive].width/2)-lefts[0].width,yoffset+100-(lefts[0].height/2),(port_ptr)&lefts[0],0);
        draw_portrait(xoffset+160+(lefts[leftactive].width/2),yoffset+100-(lefts[2].height/2),(port_ptr)&lefts[2],0);
      }
      else if(leftactive == 2)
      {
        draw_portrait(xoffset+160-(lefts[leftactive].width/2)-lefts[0].width,yoffset+100-(lefts[0].height/2),(port_ptr)&lefts[0],0);
        draw_portrait(xoffset+160+(lefts[leftactive].width/2),yoffset+100-(lefts[1].height/2),(port_ptr)&lefts[1],0);
      }
      draw_portrait(xoffset+160-(lefts[leftactive].width/2),yoffset+100-(lefts[leftactive].height/2),(port_ptr)&lefts[leftactive],0);
      draw_string(xoffset+160,yoffset+200-(bgfnt.letheight*2),(font_ptr)&bgfnt,leftfighters[leftactive].data.name,'c',1);
      returnval = 1;
    }
    if(leftactive == 3)
    {
      if(rightactive == 0)
      {
        draw_portrait(xoffset+160-(rights[rightactive].width/2)-rights[1].width,yoffset+100-(rights[1].height/2),(port_ptr)&rights[1],0);
        draw_portrait(xoffset+160+(rights[rightactive].width/2),yoffset+100-(rights[2].height/2),(port_ptr)&rights[2],0);
      }
      else if(rightactive == 1)
      {
        draw_portrait(xoffset+160-(rights[rightactive].width/2)-rights[0].width,yoffset+100-(rights[0].height/2),(port_ptr)&rights[0],0);
        draw_portrait(xoffset+160+(rights[rightactive].width/2),yoffset+100-(rights[2].height/2),(port_ptr)&rights[2],0);
      }
      else if(rightactive == 2)
      {
        draw_portrait(xoffset+160-(rights[rightactive].width/2)-rights[0].width,yoffset+100-(rights[0].height/2),(port_ptr)&rights[0],0);
        draw_portrait(xoffset+160+(rights[rightactive].width/2),yoffset+100-(rights[1].height/2),(port_ptr)&rights[1],0);
      }
      draw_portrait(xoffset+160-(rights[rightactive].width/2),yoffset+100-(rights[rightactive].height/2),(port_ptr)&rights[rightactive],0);
      draw_string(xoffset+160,yoffset+200-(bgfnt.letheight*2),(font_ptr)&bgfnt,rightfighters[rightactive].data.name,'c',1);
      returnval = 2;
    }
    draw_string(xoffset+160,yoffset+200-bgfnt.letheight,(font_ptr)&bgfnt,"Team Wins",'c',1);
    for(slowctr=0;slowctr<speed;slowctr++) wait4vsync();
    show_double_buffer(xoffset,yoffset,1);
    loop++;
    if(key_table[MAKE_ESC])
    {
        loop = maxloops;
    }
  } while(loop < maxloops);

  destroy_midi(bgmusic);
  return returnval;
}

int tag_player_select(char *p1, char *p2, char *p3, char *p4, char *p5, char *p6) {
  int st1, up1, dn1, lf1, rt1, jb1, sg1, fc1, sh1, fw1, rh1;
  int st2, up2, dn2, lf2, rt2, jb2, sg2, fc2, sh2, fw2, rh2;
  portrait left, right;
  char bigp[25];
  portrait pix[120];
  int leftids[3], rightids[3];
  int leftctrs[3], rightctrs[3];
  leftctrs[0] = 0;
  leftctrs[1] = 0;
  leftctrs[2] = 0;
  rightctrs[0] = 0;
  rightctrs[1] = 0;
  rightctrs[2] = 0;
  int p1id=0, p2id=0;
  int p1on=0, p2on=0;
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
  static frameset leftfsets[3],rightfsets[3];
  static moveset leftmsets[3],rightmsets[3];
  int leftactive=0,rightactive=0;


  y = 100 - (cs.bigpic.height/2);

  for(ctr=0;ctr<cs.last_character;ctr++)
  {
    if((fp = fopen(cs.characters[ctr].idname1,"rb")) == NULL)
    {
      printf("Couldn't open %s\n",cs.characters[ctr].idname1);
      return 0;
    }
    fscanf(fp,"%s",&p1name);
    fscanf(fp,"%d",&type);
    fscanf(fp,"%s",&port);
    get_portrait((port_ptr)&pix[ctr],port);
    fclose(fp);
    if(width<pix[ctr].width) width = pix[ctr].width;
    if(height<pix[ctr].height) height = pix[ctr].height;
  }

  for(ctr=0;ctr<3;ctr++)
  {
    leftids[ctr] = rand() % cs.last_character;
    rightids[ctr] = rand() % cs.last_character;
  }

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
  do
  {
    curr_port = screen_num*(cs.rows*cs.cols);
    draw_portrait(0,y,(port_ptr)&cs.bigpic,0);

    if(p1on)
    {
      draw_portrait(0,0,(port_ptr)&left,0);
      for(ctr=0;ctr<3;ctr++)
      {
        if(ctr <= leftactive) draw_warrior(20+50*ctr,165,leftfsets[ctr].sprites[leftmsets[ctr].frames[leftmsets[ctr].sequences[0].moves[leftctrs[ctr]]].fram_num],leftfsets[ctr].images[leftfsets[ctr].sprites[leftmsets[ctr].frames[leftmsets[ctr].sequences[0].moves[leftctrs[ctr]]].fram_num].imag_num[0]],'n',0,0,'n');
      }

      draw_string(0,170,(font_ptr)&bgfnt,p1name,'l',1);
      if(!p1done)
      {
        for(ctr=0;ctr<3;ctr++)
        {
          leftctrs[ctr]++;
          if(leftctrs[ctr] > leftmsets[ctr].sequences[0].used) leftctrs[ctr] = 0;
        }
      }
    }


    if(p2on)
    {
      draw_portrait(320-right.width,0,(port_ptr)&right,1);
      for(ctr=0;ctr<3;ctr++)
      {
        if(ctr <= rightactive) draw_warrior(300-(50*ctr),165,rightfsets[ctr].sprites[rightmsets[ctr].frames[rightmsets[ctr].sequences[0].moves[rightctrs[ctr]]].fram_num],rightfsets[ctr].images[rightfsets[ctr].sprites[rightmsets[ctr].frames[rightmsets[ctr].sequences[0].moves[rightctrs[ctr]]].fram_num].imag_num[0]],'h',0,0,'n');
      }

      draw_string(320,170,(font_ptr)&bgfnt,p2name,'r',1);
      if(!p2done)
      {
        for(ctr=0;ctr<3;ctr++)
        {
          rightctrs[ctr]++;
          if(rightctrs[ctr] > rightmsets[ctr].sequences[0].used) rightctrs[ctr] = 0;
        }
      }
    }
      /*draw_warrior(270,165,fset2.sprites[mset2.frames[mset2.sequences[0].moves[p2ctr]].fram_num],fset2.images[fset2.sprites[mset2.frames[mset2.sequences[0].moves[p2ctr]].fram_num].imag_num[0]],'h',0,0);
      if(fset2.sprites[mset2.frames[mset2.sequences[0].moves[p2ctr]].fram_num].last_image) {
        draw_warrior(270,165,fset2.sprites[mset2.frames[mset2.sequences[0].moves[p2ctr]].fram_num],fset2.images[fset2.sprites[mset2.frames[mset2.sequences[0].moves[p2ctr]].fram_num].imag_num[1]],'h',1,0);
        }
      draw_string(320,170,(font_ptr)&bgfnt,p2name,'r',1);
      if(!p2done) p2ctr++;
      if(p2ctr > mset2.sequences[0].used) p2ctr = 0;*/
//      }

    for(ctr=0;ctr<cs.rows;ctr++)
    {
      for(ctr2=0;ctr2<cs.cols;ctr2++)
      {
        if(curr_port <= cs.last_character)
        {
          draw_portrait(x+(ctr2*width),0+ctr*height,(port_ptr)&pix[curr_port],0);
          curr_port++;
        }
      }
    }

    show_double_buffer(0,0,1);
    } while(!keys_active);

  if(key_table[MAKE_TAB])
  {
    screen_num++;
    if(screen_num > cs.last_character / (cs.rows*cs.cols)) screen_num = 0;
    if(!p1done)
    {
      p1id = screen_num * (cs.rows * cs.cols);
      fp = fopen(cs.characters[p1id].idname1,"rb");
      fscanf(fp,"%s",&p1name);
      fscanf(fp,"%d",&type);
      fscanf(fp,"%s %s %s %s",&port,&bigp,&i,&s);
      kill_portrait((port_ptr)&left);
      kill_frames((fs_ptr)&leftfsets[leftactive]);
      get_portrait((port_ptr)&left,bigp);
      get_ide((fs_ptr)&leftfsets[leftactive],i);
      get_re((fs_ptr)&leftfsets[leftactive]);
      get_seq((ms_ptr)&leftmsets[leftactive],s);
      fclose(fp);
    }

    if(!p2done)
    {
      p2id = screen_num * (cs.rows * cs.cols);
      fp = fopen(cs.characters[p2id].idname1,"rb");
      fscanf(fp,"%s",&p2name);
      fscanf(fp,"%d",&type);
      fscanf(fp,"%s %s %s %s",&port,&bigp,&i,&s);
      kill_portrait((port_ptr)&right);
      kill_frames((fs_ptr)&rightfsets[rightactive]);
      get_portrait((port_ptr)&right,bigp);
      get_ide((fs_ptr)&rightfsets[rightactive],i);
      get_re((fs_ptr)&rightfsets[rightactive]);
      get_seq((ms_ptr)&rightmsets[rightactive],s);
      fclose(fp);
    }
  }


  if(!p1on) {
    p1done = 0;
    if(key_table[st1]) {
      p1on = 1;
      p1id = 0;
      p1last = 0;
      fp = fopen(cs.characters[p1id].idname1,"rb");
      fscanf(fp,"%s",&p1name);
      fscanf(fp,"%d",&type);
      fscanf(fp,"%s %s %s %s",&port,&bigp,&i,&s);
      get_portrait((port_ptr)&left,bigp);
      get_ide((fs_ptr)&leftfsets[leftactive],i);
      get_re((fs_ptr)&leftfsets[leftactive]);
      get_seq((ms_ptr)&leftmsets[leftactive],s);
      fclose(fp);
      }
    }
  else {
    if(!p1done) {
      p1last = p1id;
      if(key_table[st1])
      {
        leftids[leftactive] = p1id;
        if(leftactive<2)
        {
          leftactive++;
        }
        else
        {
          p1done = 1;
//        play_sample(systemsounds[0],sfxvolume,125,1000,0);
          if(p2done == p2on) goto DONE;
        }
      }
      else if(key_table[rt1]) {
//        play_sample(systemsounds[3],sfxvolume,125,1000,0);
        if(p1id < cs.last_character) p1id++;
        else p1id = 0;
        }
      else if(key_table[lf1]) {
//        play_sample(systemsounds[3],sfxvolume,125,1000,0);
        if(p1id > 0) p1id--;
        else p1id = cs.last_character;
        }
      else if(key_table[dn1]) {
//        play_sample(systemsounds[3],sfxvolume,125,1000,0);
        if(p1id < cs.last_character) p1id += cs.cols;
        if(p1id > cs.last_character) p1id = cs.last_character;
        }
      else if(key_table[up1]) {
//        play_sample(systemsounds[3],sfxvolume,125,1000,0);
        if(p1id > 0) p1id -= cs.cols;
        if(p1id < 0) p1id = 0;
        }
      }
    if(p1last != p1id) {
      fp = fopen(cs.characters[p1id].idname1,"rb");
      fscanf(fp,"%s",&p1name);
      fscanf(fp,"%d",&type);
      fscanf(fp,"%s %s %s %s",&port,&bigp,&i,&s);
      kill_portrait((port_ptr)&left);
      kill_frames((fs_ptr)&leftfsets[leftactive]);
      get_portrait((port_ptr)&left,bigp);
      get_ide((fs_ptr)&leftfsets[leftactive],i);
      get_re((fs_ptr)&leftfsets[leftactive]);
      get_seq((ms_ptr)&leftmsets[leftactive],s);
      fclose(fp);
      }
    }


  if(!p2on) {
    p2done = 0;
    if(key_table[st2]) {
      p2on = 1;
      p2id = 0;
      fp = fopen(cs.characters[p2id].idname1,"rb");
      fscanf(fp,"%s",&p2name);
      fscanf(fp,"%d",&type);
      fscanf(fp,"%s %s %s %s",&port,&bigp,&i,&s);
      get_portrait((port_ptr)&right,bigp);
      get_ide((fs_ptr)&rightfsets[rightactive],i);
      get_re((fs_ptr)&rightfsets[rightactive]);
      get_seq((ms_ptr)&rightmsets[rightactive],s);
      fclose(fp);
      }
    }
  else {
    if(!p2done) {
      p2last = p2id;
      if(key_table[st2])
      {
        rightids[rightactive] = p2id;
        if(rightactive<2)
        {
          rightactive++;
        }
        else
        {
          p2done = 1;
//        play_sample(systemsounds[0],sfxvolume,125,1000,0);
          if(p1done == p1on) goto DONE;
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
      if(p2last != p2id) {
        fp = fopen(cs.characters[p2id].idname1,"rb");
        fscanf(fp,"%s",&p2name);
        fscanf(fp,"%d",&type);
        fscanf(fp,"%s %s %s %s",&port,&bigp,&i,&s);
        kill_portrait((port_ptr)&right);
        kill_frames((fs_ptr)&rightfsets[rightactive]);
        get_portrait((port_ptr)&right,bigp);
        get_ide((fs_ptr)&rightfsets[rightactive],i);
        get_re((fs_ptr)&rightfsets[rightactive]);
        get_seq((ms_ptr)&rightmsets[rightactive],s);
        fclose(fp);
        }
      }
    }
  goto LOOP;

  DONE:
//  destroy_midi(bgtune);
  //destroy_sample(bgsamp);
  for(ctr=0;ctr<=cs.last_character;ctr++) kill_portrait((port_ptr)&pix[ctr]);
//  kill_portrait((port_ptr)&bigpic);
  kill_portrait((port_ptr)&left);
  kill_portrait((port_ptr)&right);
  strcpy(p1,cs.characters[leftids[0]].idname1);
  strcpy(p2,cs.characters[leftids[1]].idname1);
  strcpy(p3,cs.characters[leftids[2]].idname1);
  strcpy(p4,cs.characters[rightids[0]].idname1);
  strcpy(p5,cs.characters[rightids[1]].idname1);
  strcpy(p6,cs.characters[rightids[2]].idname1);

  returnval = 0;
  if(p1on) returnval = 1;
  if(p2on) returnval = 2;
  if(p1on && p2on) returnval = 3;
  return returnval;
  }

void tag_mode() {
  int temp = 0;
  int winner = 0;
  char p1[25],p2[25],p3[25],p4[25],p5[25],p6[25];

  temp = tag_player_select(p1,p2,p3,p4,p5,p6);
  winner = capcom_match(p1,p2,p3,p4,p5,p6,temp);
  }

void new_demo_mode(char *config)
{
  int temp;
  int curr_id = 0;
  int last_id;
  char ids[120][20];
  char name[25];
  int rows,cols;
  int winner;
  FILE *fp;
  int type;
  int fighttype=0;
  char p[25];
  char i[25];
  char s[25];
  char k[25];
  char b[25];
  char bigp[25];
  char backname[25];
  char bgmusic[25];
  portrait port[2];
  char idname1[25];
  char idname2[25];

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
  int lastfight = 0;


  do
  {
    lastfight = fighttype;
    RAND:
    fighttype = rand() % 3;
    if(lastfight == fighttype) goto RAND;

    if(fighttype==0)
    {
      winner = single_match(ids[rand() % last_id],ids[rand() % last_id],0);
    }
    else if(fighttype==1)
    {
      winner = kof_match(ids[rand() % last_id],ids[rand() % last_id],ids[rand() % last_id],ids[rand() % last_id],ids[rand() % last_id],ids[rand() % last_id],0);
    }
    else if(fighttype==2)
    {
      winner = capcom_match(ids[rand() % last_id],ids[rand() % last_id],ids[rand() % last_id],ids[rand() % last_id],ids[rand() % last_id],ids[rand() % last_id],0);
    }
  } while(winner != 0);
}


