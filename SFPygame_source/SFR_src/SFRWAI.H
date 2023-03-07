
void warrior::ai_movement_handler() {
  int randnum;
  randnum = rand() % 13;
  guarding = 0;
  blocking = 0;

  switch(randnum) {
    case 0:
    case 1:
    case 2:  data.curr_seq = 6;
             data.curr_frame = -1;
             data.status = STAND;
             walking = 1;//data.mid_seq = 1;
             if((rand() % 100) > 10) guarding=1;
             break;
    case 3:  data.curr_seq = 3;
             data.curr_frame = -1;
             data.status = STAND;
             walking = 1;//data.mid_seq = 1;
             if((rand() % 100) > 10) guarding=1;
             break;
    case 4:
    case 5:
    case 6:  data.curr_seq = 7;
             air_seq = 7;
             data.curr_frame = -1;
             air_frame = -1;
             data.status = LEAP;
             break;
    case 7:  data.curr_seq = 4;
             air_seq = 4;
             data.curr_frame = -1;
             air_frame = -1;
             data.status = LEAP;
             break;
    case 8:
    case 9:  data.curr_seq = 0;
             data.curr_frame = -1;
             data.status = STAND;
             walking = 1;
             guarding = 1;
             break;
    case 10: data.ibuffer[0] = 'w';
             break;
    case 11: data.ibuffer[0] = 'm';
             break;
    case 12: data.ibuffer[0] = 'h';
             break;
    }
  }

void warrior::ai_attack_handler(int offset) {
  int randnum;
  randnum = rand() % 12;
  guarding = 0;
  blocking = 0;

  switch(randnum) {
    case 0:  if(close) data.curr_seq = 20;
             else data.curr_seq = 14;
             data.curr_frame = -1;
             break;
    case 1:  data.curr_seq = 38;
             data.curr_frame = -1;
             break;
    case 2:  if(close) data.curr_seq = 21;
             else data.curr_seq = 15;
             data.curr_frame = -1;
             data.super+=2;
             break;
    case 3:  data.curr_seq = 39;
             data.curr_frame = -1;
             data.super+=2;
             break;
    case 4:  if(close) data.curr_seq = 22;
             else data.curr_seq = 16;
             data.curr_frame = -1;
             data.super+=3;
             break;
    case 5:  data.curr_seq = 40;
             data.curr_frame = -1;
             data.super+=3;
             break;
    case 6:  if(close) data.curr_seq = 17;
             else data.curr_seq = 11;
             data.curr_frame = -1;
             break;
    case 7:  data.curr_seq = 35;
             data.curr_frame = -1;
             break;
    case 8:  data.curr_seq = 36;
             if(close) data.curr_seq = 18;
             else data.curr_seq = 12;
             data.curr_frame = -1;
             data.super+=2;
             break;
    case 9:  data.curr_seq = 36;
             data.curr_frame = -1;
             data.super+=2;
             break;
    case 10: if(close) data.curr_seq = 19;
             else data.curr_seq = 13;
             data.curr_frame = -1;
             data.super+=3;
             break;
    case 11: data.curr_seq = 37;
             data.curr_frame = -1;
             data.super+=3;
             break;
    }
  }

int warrior::ai_special_handler() {
  int randnum;
  guarding = 0;
  blocking = 0;
  if(kset.total > 0) {
    randnum = rand() % kset.total;
    if(kset.attacks[randnum].type != 'A') {
      data.curr_seq = kset.attacks[randnum].seq_num;
      data.curr_frame = -1;
      data.super += 5;
      if(kset.attacks[randnum].type == 'm') {
        kill_frames((fs_ptr)&fset);
        get_ide((fs_ptr)&fset,kset.attacks[randnum].ide);
        get_re((fs_ptr)&fset);
        get_seq((ms_ptr)&mset,kset.attacks[randnum].seq);
        get_cmd((ks_ptr)&kset,kset.attacks[randnum].cmd);
        for(int cnt=0;cnt<30;cnt++) {
          samples[cnt] = load_sample(kset.sounds[cnt]);
          }
        morphctr=0;
        }
      else if(kset.attacks[randnum].type == 'M') {
        kill_frames((fs_ptr)&fset);
        get_ide((fs_ptr)&fset,kset.attacks[randnum].ide);
        get_re((fs_ptr)&fset);
        get_seq((ms_ptr)&mset,kset.attacks[randnum].seq);
        get_cmd((ks_ptr)&kset,kset.attacks[randnum].cmd);
        for(int cnt=0;cnt<30;cnt++) {
          samples[cnt] = load_sample(kset.sounds[cnt]);
          }
        morphctr=101;
        }
      else if(kset.attacks[randnum].type == 'S') shade = 1;
      }
    }
  return 1;
  }

int warrior::ai_super_handler() {
  int randnum;
  guarding = 0;
  blocking = 0;

  if(kset.suptotal > 0) {
    randnum = rand() % (kset.suptotal);
    if(data.super >= kset.supers[randnum].cost * 40) {
      if(kset.supers[randnum].type != 'A') {
        data.super -= kset.supers[randnum].cost * 40;
        data.curr_seq = kset.supers[randnum].seq_num;
        data.curr_frame = -1;
        super_start = 1;
        if(kset.supers[randnum].type == 'm') {
          kill_frames((fs_ptr)&fset);
          get_ide((fs_ptr)&fset,kset.supers[randnum].ide);
          get_re((fs_ptr)&fset);
          get_seq((ms_ptr)&mset,kset.supers[randnum].seq);
          get_cmd((ks_ptr)&kset,kset.supers[randnum].cmd);
          for(int cnt=0;cnt<30;cnt++) {
            samples[cnt] = load_sample(kset.sounds[cnt]);
            }
          morphctr = 0;
          }
        else if(kset.supers[randnum].type == 'M') {
          kill_frames((fs_ptr)&fset);
          get_ide((fs_ptr)&fset,kset.supers[randnum].ide);
          get_re((fs_ptr)&fset);
          get_seq((ms_ptr)&mset,kset.supers[randnum].seq);
          get_cmd((ks_ptr)&kset,kset.supers[randnum].cmd);
          for(int cnt=0;cnt<30;cnt++) {
            samples[cnt] = load_sample(kset.sounds[cnt]);
            }
          morphctr = 101;
          }
        }
      data.super_kill = 1;
      strcpy(data.super_name,kset.supers[randnum].name);
      }
    }
  return 1;
  }

void warrior::ai_air_attack_handler() {
  int randnum;
  guarding = 0;
  blocking = 0;
  randnum = rand() % 6;
  if(close) {
    switch(data.status) {
      case JUMP:  air_seq = 23 + randnum;
                  break;
      case LEAP:  air_seq = 29 + randnum;
                  break;
      }
    air_frame = -1;
    air_done = 1;
    data.super += 1 * (randnum + 1);
    }
  }

void warrior::ai_air_special_handler() {
  int randnum;
  guarding = 0;
  blocking = 0;
  if(kset.total > 0) {
    randnum = rand() % kset.total;
    if(kset.attacks[randnum].type == 'A') {
      air_seq = kset.attacks[randnum].seq_num;
      if(kset.attacks[randnum].mod) frozen = 1;
      air_frame = -1;
      data.super += 5;
      air_done = 1;
      }
    }
  }

void warrior::ai_air_super_handler() {
  int randnum;
  guarding = 0;
  blocking = 0;
  if(kset.suptotal > 0) {
    randnum = rand() % kset.suptotal;
    if(data.super >= kset.supers[randnum].cost * 40) {
      if(kset.supers[randnum].type == 'A') {
        data.super -= kset.supers[randnum].cost * 40;
        air_seq = kset.supers[randnum].seq_num;
        air_frame = -1;
        air_done = 1;
        super_start = 1;
        frozen = 1;
        }
      data.super_kill = 1;
      strcpy(data.super_name,kset.supers[randnum].name);
      }
    }
  }

void warrior::ai_throw_handler(info_ptr opponent) {
  int randnum;
  guarding = 0;
  blocking = 0;
  if(kset.grabtotal > 0) {
    randnum = rand() % kset.grabtotal;
    if((opponent->dbox.active) && (opponent->p[1] == ground) && (rand() % 100 > 50)) {
      if(data.second) {
        if(kset.grabs[randnum].direction == 1) {
          data.second = 0;
          opponent->second = 1;
          data.p[0] -= abs(opponent->curr_sprite.x_off[0]) * 2;
          }
        else if(kset.grabs[randnum].direction == 2) {
          data.second = 1;
          opponent->second = 0;
          }
        }
      else {
        if(kset.grabs[randnum].direction == 1) {
          data.second = 1;
          opponent->second = 0;
          data.p[0] += abs(opponent->curr_sprite.x_off[0]) * 2;
          }
        else if(kset.grabs[randnum].direction == 2) {
          data.second = 0;
          opponent->second = 1;
          }
        }

      switch(kset.grabs[randnum].damage) {
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

      data.curr_seq = kset.grabs[randnum].action;
      data.curr_frame = -1;
      opponent->curr_seq = kset.grabs[randnum].reaction;
      opponent->curr_frame = -1;
      opponent->status = RECOIL;
      data.super+=4;
      }
    }
  }

void warrior::cpu_handler(info_ptr opponent,int offset) {
  int randnum;
  data.ibuffer[0] = 'n';
  randnum = rand() % 1000;
  if(!guarding) {
    guarding = 0;
    lowguard = 0;
    }

  if(data.status == JUMP || data.status == LEAP) {
    if(!air_done) {
      switch(mset.frames[mset.sequences[air_seq].moves[air_frame]].cancel) {
        case '0':  break;
        case '1':  if(randnum > 200 && randnum < 400) ai_air_super_handler();
                   if(randnum > 400) ai_air_special_handler();
                   break;
        case '2':  if(randnum < 200) ai_air_attack_handler();
                   if(randnum > 200 && randnum < 400) ai_air_super_handler();
                   if(randnum > 400) ai_air_special_handler();
                   break;
        case '3':  if(randnum < 200) ai_air_attack_handler();
                   if(randnum > 200 && randnum < 400) ai_air_super_handler();
                   if(randnum > 400) ai_air_special_handler();
                   break;
        case '4':  break;
        case '5':  if(randnum > 200 && randnum < 400) ai_air_super_handler();
                   if(randnum > 400) ai_air_special_handler();
                   break;
        case '6':  if(randnum < 200) ai_air_attack_handler();
                   if(randnum > 200 && randnum < 400) ai_air_super_handler();
                   if(randnum > 400) ai_air_special_handler();
                   break;
        case '7':  if(randnum < 200) ai_air_attack_handler();
                   if(randnum > 200 && randnum < 400) ai_air_super_handler();
                   if(randnum > 400) ai_air_special_handler();
                   break;
        }
      }
    }
  else if(data.status != RECOIL) {
    if(!walking) {
      switch(mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].cancel) {
        case '0':  break;
        case '1':  if(randnum > 600 && randnum < 700) ai_super_handler();
                   if(randnum > 700 && randnum < 1000) ai_special_handler();
                   break;
        case '2':  if(randnum > 300 && randnum < 600) ai_attack_handler(offset);
  //                 if(close) ai_throw_handler(opponent);
                   break;
        case '3':  if(randnum > 300 && randnum < 600) ai_attack_handler(offset);
                   if(randnum > 600 && randnum < 700) ai_super_handler();
                   if(randnum > 700 && randnum < 1000) ai_special_handler();
//                   if(close) ai_throw_handler(opponent);
                   break;
        case '4':  if(randnum < 300) ai_movement_handler();
                   if(guarding || lowguard) guard_handler(opponent);
                   else {
                     blocking = 0;
                     lowblock = 0;
                     }
                   break;
        case '5':  if(randnum < 300) ai_movement_handler();
                   if(guarding || lowguard) guard_handler(opponent);
                   else {
                     blocking = 0;
                     lowblock = 0;
                     }
                   if(randnum > 600 && randnum < 700) ai_super_handler();
                   if(randnum > 700 && randnum < 1000) ai_special_handler();
                   break;
        case '6':  if(randnum < 300) ai_movement_handler();
                   if(guarding || lowguard) guard_handler(opponent);
                   else {
                     blocking = 0;
                     lowblock = 0;
                     }
                   if(randnum > 300 && randnum < 600) ai_attack_handler(offset);
//                   if(close) ai_throw_handler(opponent);
                   break;
        case '7':  if(randnum < 300) ai_movement_handler();
                   if(guarding || lowguard) guard_handler(opponent);
                   else {
                     blocking = 0;
                     lowblock = 0;
                     }
                   if(randnum > 300 && randnum < 600) ai_attack_handler(offset);
                   if(randnum > 600 && randnum < 700) ai_super_handler();
                   if(randnum > 700 && randnum < 1000) ai_special_handler();
                   data.curr_input = data.ibuffer[0];
//                   if(close) ai_throw_handler(opponent);
                   break;
        }
      }
    else {
      switch(mset.frames[mset.sequences[data.curr_seq].moves[data.curr_frame]].cancel) {
        case '2':
        case '3':
        case '6':
        case '7':  if(close) ai_throw_handler(opponent);
                   break;
        }
      }
    }
  }

