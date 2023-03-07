import pygame,sys,math,random,os,pickle ,pygame.midi
from pygame.locals import *

pygame.init()


BLACK=pygame.color.THECOLORS["black"]
WHITE=pygame.color.THECOLORS["white"]
RED=pygame.color.THECOLORS["red"]
BLUE=pygame.color.THECOLORS["blue"]
YELLOW=pygame.color.THECOLORS["yellow"]
ORANGE=pygame.color.THECOLORS["orange"]
TURQUOISE=pygame.color.THECOLORS["turquoise"]
SCREEN_WIDTH=640
SCREEN_HEIGHT=480
DISPLAY_SURFACE_WIDTH=320
DISPLAY_SURFACE_HEIGHT=240
SCALE=2
FLOOR_Y_POS=180


def get_palette(palette_file):
    with open(palette_path, 'r') as file:
         palette_data=file.read()
    palette_data=palette_data.split('\n')
    del(palette_data[len(palette_data)-1])

    #palette=image.get_palette()
    palette=[[0,0,0]for i in range(256)]

    for i in range(len(palette_data)):
            palette_data[i]=palette_data[i].split(' ')
            color=palette_data[i]
            for j in range(len(color)-1,-1,-1):
                    if color[j]=='':
                            del(color[j])
                    else:
                            color[j]=int(color[j])

            palette[i][0]=color[1]*4
            palette[i][1]=color[2]*4
            palette[i][2]=color[3]*4
    return palette


def Runlength_decompression(bytes_list):
    bytes_list2=bytes_list
    bytes_list=list(bytes_list)
    step=0
    index=0
    length=len(bytes_list)-1
    while index<length:
       #loop speed limitation
       #30 frames per second is enought
       #pygame.time.Clock().tick(30)
       if bytes_list[index+2]!=0:
          bytes_list[index+1]=int.from_bytes(
          bytes([bytes_list[index+1],bytes_list[index+2]]),sys.byteorder)
       step=bytes_list[index+1]+1
       bytes_list[index]=[0]*bytes_list[index]
       del(bytes_list[index+1])
       del(bytes_list[index+1])
       length=len(bytes_list)-1
       index+=step
    for i in range(len(bytes_list)-1,-1,-1):
        if type(bytes_list[i])==list:
           bytes_list[i:i+1]=bytes_list[i][:]
    return bytes(bytes_list)


def Runlength_compression(image, alpha_color):
    image_data = b''
    alpha_color_count = 0
    other_color_count = 0
    other_color = False
    other_color_list = []
    for y in range(image.get_height()):
        for x in range(image.get_width()):
            if image.get_at((x, y)) == alpha_color:
               if other_color:
                  if other_color_count > 255:
                     image_data += bytes([alpha_color_count])
                     image_data += int.to_bytes(other_color_count, 2, sys.byteorder)
                  else:
                     image_data += bytes([alpha_color_count, other_color_count, 0])
                  image_data += bytes(other_color_list)
                  alpha_color_count = 0
                  other_color_count = 0
                  other_color = False
                  other_color_list = []                
               alpha_color_count += 1
               if alpha_color_count > 255:
                  image_data += bytes([alpha_color_count-1, 0, 0])
                  alpha_color_count = 1
            elif image.get_at((x, y)) != alpha_color:
               other_color = True
               other_color_list.append(image.get_at_mapped((x,y)))
               other_color_count += 1
    if alpha_color_count > 0 or other_color_count > 0:
       image_data += bytes([alpha_color_count])
       image_data += int.to_bytes(other_color_count, 2, sys.byteorder)
       image_data += bytes(other_color_list)
    return image_data

               
def load_RE(RE,IDE,PALETTE):
    alpha_color=PALETTE[0]
    with open(IDE, 'r') as file:
         data=file.read()
    data=data.split('_the_end')
    images=data[0]
    sprites=data[1]
    collisions=data[2]
    images=images.split('\n')
    sprites=sprites.split('\n')
    collisions=collisions.split('\n')
    for i in range(len(images)-1,-1,-1):
        images[i]=images[i].split(' ')
        for j in range(len(images[i])-1,-1,-1):
            if images[i][j]=='':
               del(images[i][j])
        if len(images[i])!=4:
           del(images[i])

    for i in range(len(sprites)-1,-1,-1):
        sprites[i]=sprites[i].split(' ')
        for j in range(len(sprites[i])-1,-1,-1):
            if sprites[i][j]=='':
               del(sprites[i][j])
        #if len(sprites[i])>5:
           #sprites[i]=sprites[i][:5]
        if len(sprites[i])<5:
           #print(sprites[i])
           del(sprites[i])

    for i in range(len(collisions)-1,-1,-1):
        collisions[i]=collisions[i].split(' ')
        for j in range(len(collisions[i])-1,-1,-1):
            if collisions[i][j]=='':
               del(collisions[i][j])
        if len(collisions[i])!=4:
           del(collisions[i])
        else:
           for j in range(len(collisions[i])):
               collisions[i][j]=int(collisions[i][j])

    #print(len(images),len(sprites),len(collisions))
    with open(RE, 'rb') as file:
         for i in range(len(images)):
             image=images[i]
             image_size=(int(image[2]),int(image[3]))
             image_data=file.read(int(image[1]))
             image_data=Runlength_decompression(image_data)
             padding=(image_size[0]*image_size[1])-len(image_data)
             if padding<0:
                image_data=image_data[:padding]
             else:
                image_data+=b'\x00'*padding
             image_data=pygame.image.fromstring(image_data,image_size,'P')
             image_data.set_palette(PALETTE)
             image_data.set_colorkey(alpha_color)
             image_data.convert()
             image[1]=image_data

    frames=[]
    len_collisions=len(collisions)
    for i in range(len(sprites)):
        sprite=sprites[i]
        image=images[int(sprite[1])][1]
        second_image=None
        collision=[0,0,0,0]
        if i < len_collisions:
           collision=collisions[i]
           if collision[2]<collision[0]:
              collision[2],collision[0]=collision[0],collision[2]
           if collision[3]<collision[1]:
              collision[3],collision[1]=collision[1],collision[3]
           collision=[collision[0],collision[1],collision[2]-collision[0],collision[3]-collision[1]]
        else:
           pass
           #print('no collision box')
        if len(sprite)>5:
           second_image=images[int(sprite[4])][1]
           second_image={'name':sprite[0],'x_axis_shift':int(sprite[5]),'y_axis_shift':int(sprite[6]),
                          'image':second_image,'collision_box':collision,
                          'image_size':second_image.get_size()}

        frame={'name':sprite[0],'x_axis_shift':int(sprite[2]),'y_axis_shift':int(sprite[3]),
               'image':image,'collision_box':collision,'second_image':second_image,
               'image_size':image.get_size()}

        if second_image:
           x_axis_shift = min(frame['x_axis_shift'], second_image['x_axis_shift'])
           y_axis_shift = min(frame['y_axis_shift'], second_image['y_axis_shift'])
           width = max(frame['x_axis_shift'] + frame['image_size'][0],
                       second_image['x_axis_shift'] + second_image['image_size'][0]) - x_axis_shift
           height = max(frame['y_axis_shift'] + frame['image_size'][1],
                        second_image['y_axis_shift'] + second_image['image_size'][1]) - y_axis_shift     
           image = pygame.Surface((width, height)).convert()
           image.set_colorkey(image.get_at((0,0)))
           image.blit(frame['image'], (frame['x_axis_shift'] - x_axis_shift,
                                       frame['y_axis_shift'] - y_axis_shift))
           image.blit(second_image['image'], (second_image['x_axis_shift'] - x_axis_shift,
                                              second_image['y_axis_shift'] - y_axis_shift))
           frame['image'] = image
           frame['image_size'] = (width, height)
           if frame['collision_box'] != [0,0,0,0]:
              frame['collision_box'][0] += frame['x_axis_shift'] - x_axis_shift
              frame['collision_box'][1] += frame['y_axis_shift'] - y_axis_shift
           frame['x_axis_shift'] = x_axis_shift
           frame['y_axis_shift'] = y_axis_shift
        frames.append(frame)
    return frames


def load_SEQ(SEQ):
    with open(SEQ, 'r') as file:
         seq_data=file.read()
    seq_data=seq_data.split('\n')
    process='sequences_frames'
    split_index=None
    sequences={}
    sequences_frames={}
    for i in range(len(seq_data)-1,-1,-1):
        seq_data[i]=seq_data[i].split(' ')
        for j in range(len(seq_data[i])-1,-1,-1):
            if seq_data[i][j]=='':
               del(seq_data[i][j])
            else:
               if process=='sequences':
                  seq_data[i][j]=int(seq_data[i][j])
        if process=='sequences':
           if seq_data[i]!=[]:
              seq_data[i][-1],seq_data[i][-2]=seq_data[i][-2],seq_data[i][-1]
              if seq_data[i][-1]==253:
                 seq_data[i].append(seq_data[i][-3])
                 if len(seq_data[i])>5:
                    del(seq_data[i][-4])
              sequences[seq_data[i][0]]=seq_data[i][1:]
        if process=='sequences_frames':
           if len(seq_data[i])==5:
              seq_data[i][0]=int(seq_data[i][0])
              seq_data[i][1]=int(seq_data[i][1])
              seq_data[i][2]=int(seq_data[i][2])
              seq_data[i][3]=int(seq_data[i][3])
              if len(seq_data[i][4])==6:
                 #seq_data[i][4]=seq_data[i][4][:3]+'N'+seq_data[i][4][3:]
                 seq_data[i][4]="D00N0xx"
              seq_data[i].append(seq_data[i][4][0])
              seq_data[i].append(int(seq_data[i][4][1]))
              seq_data[i].append(int(seq_data[i][4][2]))
              seq_data[i].append(seq_data[i][4][3])
              seq_data[i].append(int(seq_data[i][4][4]))
              seq_data[i].append(seq_data[i][4][5])
              seq_data[i].append(seq_data[i][4][6])
              del(seq_data[i][4])
              sequences_frames[seq_data[i][0]]={'Image_number':seq_data[i][1],
                 'x_movement':seq_data[i][2], 'y_movement':seq_data[i][3],
                 'frame_type':seq_data[i][4], 'hit_damage':seq_data[i][5],
                 'hit_reaction':seq_data[i][6], 'frame_orientation':seq_data[i][7],
                 'cancel_mode':seq_data[i][8], 'attack_mode':seq_data[i][9],
                 'invincible':seq_data[i][10]}
        if seq_data[i]==['-1']:
           seq_data[i][0]=int(seq_data[i][0])
           split_index=i
           process='sequences'
        elif seq_data[i]==[]:
           del(seq_data[i])
    #sequences=seq_data[:split_index]
    #sequences_frames=seq_data[split_index+1:]
    for i in range(9):
        sequences[i].append("movement_sequence")
    return (sequences, sequences_frames)


def load_KEY(KEY):
    with open(KEY, 'r') as file:
         key_data=file.read()
    key_data=key_data.split('_end    -1  _end')
    #key_data=key_data.split('_end -1 _end')
    super_moves=key_data[0]
    throws=key_data[1]
    super_moves=super_moves.split('\n')
    throws=throws.split('\n')
    for i in range(len(super_moves)-1,-1,-1):
        super_moves[i]=super_moves[i].split(' ')
        for j in range(len(super_moves[i])-1,-1,-1):
            if super_moves[i][j]=='':
               del(super_moves[i][j])
        if super_moves[i]==[]:
           del(super_moves[i])
    close_range=int(super_moves[0][0])
    del(super_moves[0])
    for i in range(len(super_moves)):
        super_moves[i][1]=int(super_moves[i][1])
        reverse_string=''
        for j in range(len(super_moves[i][0])-1,-1,-1):
            reverse_string+=super_moves[i][0][j]
        super_moves[i][0]=reverse_string
        super_move={'inputs':super_moves[i][0],
                    'sequence':super_moves[i][1],
                    'sound':super_moves[i][2],
                    'inputs_lenth':len(super_moves[i][0])}
        if super_moves[i][2] != '_no_voice':
           super_move['sound'] = pygame.mixer.Sound(sfibm_path+super_moves[i][2])
        elif super_moves[i][2] == '_no_voice':
           super_move['sound'] = pygame.mixer.Sound(bytes(0))
        super_move['sound'].set_volume(0.3)   
        super_moves[i]=super_move
    for i in range(len(throws)-1,-1,-1):
        throws[i]=throws[i].split(' ')
        for j in range(len(throws[i])-1,-1,-1):
            if throws[i][j]=='':
               del(throws[i][j])
        if throws[i]==[]:
           del(throws[i])
    del(throws[-1])
    for i in range(len(throws)):
        throw_data=throws[i]
        if len(throw_data[0]) == 1:
           throw_data[0] = '4' + throw_data[0]
        throw={'damage':int(throw_data[0][0]),'throw_height':int(throw_data[0][1]),
               'direction_held':int(throw_data[1][0]),
               'button_held':int(throw_data[1][1]),
               'character_sequence':int(throw_data[2]),
               'opponent_sequence':int(throw_data[3]),
               'slam_direction':int(throw_data[4]),'sound':throw_data[5]}
        if throw_data[5] != '_no_voice':
           throw['sound'] = pygame.mixer.Sound(sfibm_path+throw_data[5])
        elif throw_data[5] == '_no_voice':
           throw['sound'] = pygame.mixer.Sound(bytes(0))
        throw['sound'].set_volume(0.3)   
        throws[i]=throw
    return super_moves,throws,close_range


def load_R(R,ID,PALETTE):
    alpha_color=PALETTE[0]
    with open(ID, 'r') as file:
         data=file.read()
    data=data.split('_the_end')
    images=data[0]
    images=images.split('\n')
    for i in range(len(images)-1,-1,-1):
        images[i]=images[i].split(' ')
        for j in range(len(images[i])-1,-1,-1):
            if images[i][j]=='':
               del(images[i][j])
        if len(images[i])!=3:
           del(images[i])
        else:
           images[i][1]=int(images[i][1])
           images[i][2]=int(images[i][2])
    with open(R, 'rb') as file:
         for i in range(len(images)):
             image=images[i]
             image_size=(image[1],image[2])
             data_size=image[1]*image[2]
             image_data=file.read(data_size)
             image_data=pygame.image.fromstring(image_data,image_size,'P')
             image_data.set_palette(PALETTE)
             image_data.set_colorkey(alpha_color)
             image_data.convert()
             images[i]={'image':image_data,'width':image[1],'height':image[2],'name':image[0]}
    return images


def load_background(image_path,palette):
    with open(image_path, 'rb') as file:
         image_data=file.read()
    image_width=520  #int(image_path.split('.')[1])
    image_height=int(len(image_data)/image_width)
    image_size=(image_width,image_height)
    image=pygame.image.fromstring(image_data,image_size,'P')
    image.set_palette(palette)
    image.convert()
    pos=[int(160-image_width/2),200-image_height]
    pos[1]+=pos[1]%2
    background={'image':image,'width':image_width,'height':image_height,'pos':pos}
    return background


def load_character(RE, IDE, SEQ, KEY, controls, side, palette):
   sprites=load_RE(RE,IDE,palette)
   sequences,sequences_frames=load_SEQ(SEQ)
   super_moves,throws,close_range=load_KEY(KEY)
   if side == 'left':
      pos = [90, FLOOR_Y_POS]
   elif side == 'right':
      pos = [230, FLOOR_Y_POS]
   return Character(sprites,sequences,sequences_frames,controls,super_moves,throws,close_range,pos,side)


def check_character(character):
    for i in range(len(character.super_moves)-1,-1,-1):
        super_move = character.super_moves[i]
        try:
            character.sequences[super_move['sequence']]
        except KeyError:
            del(character.super_moves[i])
            print('delted super move with sequence number ',super_move['sequence'])
    for i in range(len(character.throws)-1,-1,-1):
        throw = character.throws[i]
        try:
            character.sequences[throw['character_sequence']]
        except KeyError:
            del(character.throws[i])
            print('delted throw with sequence number ',throw['character_sequence'])


def load_sounds(sfibm_path):
    sounds = []
    for i in range(10):
        if i < 8:
           sound = pygame.mixer.Sound(sfibm_path+'D'+str(i)+'.VOC')
        else:
           sound = pygame.mixer.Sound(sfibm_path+'D0.VOC')
        sound.set_volume(0.3)   
        sounds.append(sound)
    sounds.append(pygame.mixer.Sound(sfibm_path+'DEFENCE.VOC'))
    sounds[10].set_volume(0.3)
    for i in range(11,41):
        sound = pygame.mixer.Sound(sfibm_path+'A'+str(i)+'.VOC')
        sound.set_volume(0.3)
        sounds.append(sound)
    sounds.append(pygame.mixer.Sound(sfibm_path+'WAVEFX.VOC'))
    sounds[41].set_volume(0.3)
    return sounds
    

palette_path="characters\\RGB.PAL"
sfibm_path="characters\\"
IDE=sfibm_path+"HYPRYU.IDE"
RE=sfibm_path+"HYPRYU.RE"
SEQ=sfibm_path+"HYPRYU.SEQ"
KEY=sfibm_path+"HYPRYU.KEY"
IDE2=sfibm_path+"VEGETA.IDE"#sfibm_path+"HYPKEN.IDE"
RE2=sfibm_path+"VEGETA.RE"#sfibm_path+"HYPKEN.RE"
SEQ2=sfibm_path+"VEGETA.SEQ"#sfibm_path+"HYPKEN.SEQ"
KEY2=sfibm_path+"HYPKEN.KEY"
background_path=sfibm_path+"HYPKEN.BK"
R=sfibm_path+"FACEW.R"
ID=sfibm_path+"FACEW.ID"


def read_RE(RE,IDE):
    screen = pygame.display.set_mode((640, 480))#,0,8)
    clock=pygame.time.Clock()
    PALETTE=get_palette(palette_path)
    #pygame.display.set_palette(get_palette(PALETTE))
    font=pygame.font.SysFont('Arial', 20)
    frames=load_RE(RE,IDE,PALETTE)
    image=frames[0]['image']
    images_lenth=len(frames)-1
    change_image=True
    image_index=0
    image_axis_pos=[200,400]
    image_pos=[0,0]
    frame=frames[image_index]

    pygame.key.set_repeat(400, 30)

    while True:

        #loop speed limitation
        #30 frames per second is enought
        clock.tick(30)

        for event in pygame.event.get():    #wait for events
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            if event.type == KEYDOWN:
                if event.key == K_RIGHT:
                 image_index+=1
                 if image_index>images_lenth:
                    image_index=0
                 frame=frames[image_index]
                 change_image=True
                elif event.key == K_LEFT:
                 image_index-=1
                 if image_index<0:
                    image_index=images_lenth
                 frame=frames[image_index]
                 change_image=True

        if change_image:
           change_image=False
           image=frame['image']
           image_width=image.get_width()
           image_height=image.get_height()
           image_scaled_size=(image_width*SCALE,image_height*SCALE)
           image=pygame.transform.scale(image,image_scaled_size).convert()
           screen.fill((255,255,255))
           x_axis=frame['x_axis_shift']*SCALE
           y_axis=frame['y_axis_shift']*SCALE
           image_pos=[x_axis+image_axis_pos[0],y_axis+image_axis_pos[1]]
           screen.blit(image,image_pos)
           if frame['second_image']:
              old_axis=[x_axis,y_axis]
              image=frame['second_image']['image']
              image_width2=image.get_width()
              image_height2=image.get_height()
              image_scaled_size=(image_width2*SCALE,image_height2*SCALE)
              image=pygame.transform.scale(image,image_scaled_size).convert()
              x_axis=frame['second_image']['x_axis_shift']*SCALE
              y_axis=frame['second_image']['y_axis_shift']*SCALE
              image_pos2=[x_axis+image_axis_pos[0],y_axis+image_axis_pos[1]]
              screen.blit(image,image_pos2)

           temp_rect=frames[image_index]['collision_box']
           rect=[image_pos[0],image_pos[1],image_width*SCALE,image_height*SCALE]
           pygame.draw.rect(screen, (255,0,0), rect,5)
           rect=[image_pos[0]+temp_rect[0]*SCALE,image_pos[1]+temp_rect[1]*SCALE,
                 temp_rect[2]*SCALE,temp_rect[3]*SCALE]
           pygame.draw.rect(screen, (0,0,255), rect,5)
           #pygame.draw.circle(screen,(0,255,0),(image_axis_pos),10)

           pygame.draw.line(screen,(0,255,0),(image_axis_pos[0]-15,image_axis_pos[1]),
                            (image_axis_pos[0]+15,image_axis_pos[1]),5)
           pygame.draw.line(screen,(0,255,0),(image_axis_pos[0],image_axis_pos[1]-15),
                            (image_axis_pos[0],image_axis_pos[1]+15),5)
           text=font.render(str(image_index)+' '+'/'+str(images_lenth), True, (250,0,0))
           screen.blit(text,(420,320))
           text=font.render(frames[image_index]['name'], True, (250,0,0))
           screen.blit(text,(420,340))
           pygame.display.flip()

#read_RE(RE2,IDE2)


def read_SEQ(RE,IDE,SEQ):
    screen = pygame.display.set_mode((640, 480))#,0,8)
    clock=pygame.time.Clock()
    PALETTE=get_palette(palette_path)
    #pygame.display.set_palette(get_palette(PALETTE))
    font=pygame.font.SysFont('Arial', 20)
    frames=load_RE(RE,IDE,PALETTE)
    sequences, sequences_frames=load_SEQ(SEQ)
    sequences_numbers=[]
    for number in sequences:
        sequences_numbers.append(number)
    sequences_numbers_index=0
    sequences_numbers_lenth=len(sequences_numbers)-1
    sequence_number=sequences_numbers[sequences_numbers_index]
    sequence=sequences[sequence_number]
    sequence_index=0
    sequence_frame=sequences_frames[sequence[sequence_index]]
    frame=frames[sequence_frame['Image_number']]
    image=frame['image']
    anim_time=0
    max_anim_time=2
    image_axis_pos=[200,400]
    image_pos=[0,0]
    change_image=True

    #pygame.key.set_repeat(400, 30)

    while True:

        #loop speed limitation
        #30 frames per second is enought
        clock.tick(30)

        for event in pygame.event.get():    #wait for events
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            if event.type == KEYDOWN:
                if event.key == K_RIGHT:
                 sequences_numbers_index+=1
                 if sequences_numbers_index>sequences_numbers_lenth:
                    sequences_numbers_index=0
                 sequence_number=sequences_numbers[sequences_numbers_index]
                 sequence=sequences[sequence_number]
                 sequence_index=0
                 anim_time=max_anim_time
                 change_image=True
                elif event.key == K_LEFT:
                 sequences_numbers_index-=1
                 if sequences_numbers_index<0:
                    sequences_numbers_index=sequences_numbers_lenth
                 sequence_number=sequences_numbers[sequences_numbers_index]
                 sequence=sequences[sequence_number]
                 sequence_index=0
                 anim_time=max_anim_time
                 change_image=True

        anim_time+=1
        if anim_time>=max_anim_time:
           anim_time=0
           sequence_index+=1
           if sequence[sequence_index]==-1:
              #print(sequence[sequence_index+1])
              sequence=sequences[sequence[sequence_index+1]]
              sequence_index=0
           sequence_frame=sequences_frames[sequence[sequence_index]]
           frame=frames[sequence_frame['Image_number']]
           image=frame['image']
           change_image=True

        if change_image:
           change_image=False
           image_width=image.get_width()
           image_height=image.get_height()
           image_scaled_size=(image_width*SCALE,image_height*SCALE)
           scaled_image=pygame.transform.scale(image,image_scaled_size).convert()
           x_axis=frame['x_axis_shift']*SCALE
           y_axis=frame['y_axis_shift']*SCALE
           image_pos=[x_axis+image_axis_pos[0],y_axis+image_axis_pos[1]]
           screen.fill((255,255,255))
           screen.blit(scaled_image,image_pos)
           text=font.render(str(sequences_numbers_index)+' '+'/'+str(sequences_numbers_lenth), True, (250,0,0))
           screen.blit(text,(420,320))
           text=font.render(str(sequence_number)+' '+str(sequence[sequence_index]), True, (250,0,0))
           screen.blit(text,(420,340))
           text=font.render(frame['name'], True, (250,0,0))
           screen.blit(text,(420,360))
           pygame.display.flip()

#read_SEQ(RE,IDE,SEQ)


def read_R(R,ID):
    screen = pygame.display.set_mode((640, 480))#,0,8)
    clock=pygame.time.Clock()
    PALETTE=get_palette(palette_path)
    #pygame.display.set_palette(get_palette(PALETTE))
    font=pygame.font.SysFont('Arial', 20)
    images=load_R(R,ID,PALETTE)
    images_lenth=len(images)-1
    change_image=True
    image_index=0
    image=images[image_index]
    image_pos=[50,50]

    pygame.key.set_repeat(400, 30)

    while True:

        #loop speed limitation
        #30 frames per second is enought
        clock.tick(30)

        for event in pygame.event.get():    #wait for events
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            if event.type == KEYDOWN:
                if event.key == K_RIGHT:
                 image_index+=1
                 if image_index>images_lenth:
                    image_index=0
                 image=images[image_index]
                 change_image=True
                elif event.key == K_LEFT:
                 image_index-=1
                 if image_index<0:
                    image_index=images_lenth
                 image=images[image_index]
                 change_image=True

        if change_image:
           change_image=False
           image_scaled_size=(image['width']*SCALE,image['height']*SCALE)
           scaled_image=pygame.transform.scale(image['image'],image_scaled_size).convert()
           screen.fill((255,255,255))
           screen.blit(scaled_image,image_pos)

           #rect=[image_pos[0],image_pos[1],image['width']*SCALE,image['height']*SCALE]
           #pygame.draw.rect(screen, (255,0,0), rect,5)
           text=font.render(str(image_index)+' '+'/'+str(images_lenth), True, (250,0,0))
           screen.blit(text,(50,250))
           text=font.render(image['name'], True, (250,0,0))
           screen.blit(text,(50,270))
           pygame.display.flip()

#read_R(R,ID)


def get_palette_image(palette):
    palette_image = pygame.Surface((162, 162)).convert()
    for i in range(0, 162, 10):
        pygame.draw.line(palette_image, WHITE, (i, 0), (i, 162), 2)
        pygame.draw.line(palette_image, WHITE, (0, i), (162, i), 2)
    x = 2
    y = 2
    for color in palette:
        pygame.draw.rect(palette_image, color, [x, y, 8, 8], 0)
        x += 10
        if x > 152:
           x = 2
           y += 10
    return palette_image

        
def color_match_palette(color, palette):
    comparison_value = (999, 999, 999)
    chosen_color_index = None
    for i in range(1,len(palette)):
        palette_color = palette[i]
        temp_comparison_value = (abs(color[0] - palette_color[0]),
                                 abs(color[1] - palette_color[1]),
                                 abs(color[2] - palette_color[2]))
        if temp_comparison_value < comparison_value:
           comparison_value = temp_comparison_value 
           chosen_color_index = i
    return chosen_color_index


def image_change_color(image, color1_index, color2_index):
    for y in range(image.get_height()):
        for x in range(image.get_width()):
            image_color_index = image.get_at_mapped((x, y))
            if image_color_index == color1_index:
               image.set_at((x, y), color2_index)

    
def image_swap_color_index(image, color1_index, color2_index):
    palette = image.get_palette()
    color1 = palette[color1_index]
    color2 = palette[color2_index]
    image.set_palette_at(color2_index, color1)
    image.set_palette_at(color1_index, color2)
    for y in range(image.get_height()):
        for x in range(image.get_width()):
            image_color_index = image.get_at_mapped((x, y))
            if image_color_index == color1_index:
               image.set_at((x, y), color2_index)
            elif image_color_index == color2_index:
               image.set_at((x, y), color1_index)                   

    
def find_unused_palette_colors(palette, image):
    image_colors = []
    unused_colors_indexes = []
    for y in range(image.get_height()):
        for x in range(image.get_width()):
            image_color = image.get_at((x, y))
            if not (image_color in image_colors):
               image_colors.append(image_color)
    for i in range(len(palette)):
           if not palette[i] in image_colors:
              unused_colors_indexes.append(i)
    return unused_colors_indexes

def image_match_palette (image, palette):
    image_copy = image.copy()
    image_copy.set_palette(palette)
    palette = image_copy.get_palette()
    alpha_color = palette[0]
    matched_colors = []
    matched_colors_indexes = []
    chosen_color_index = None
    comparison_value = (999, 999, 999)
    for y in range(image.get_height()):
        for x in range(image.get_width()):
            image_color = image.get_at((x, y))
            if image_color == alpha_color:
               continue
            if image_color in matched_colors:
               for i in range(len(matched_colors)):
                   if matched_colors[i] == image_color:
                      image_copy.set_at((x,y), matched_colors_indexes[i])
               continue
            comparison_value = (999, 999, 999)
            for i in range(1,len(palette)):
                palette_color = palette[i]
                temp_comparison_value = (abs(image_color[0] - palette_color[0]),
                                         abs(image_color[1] - palette_color[1]),
                                         abs(image_color[2] - palette_color[2]))
                
                if temp_comparison_value < comparison_value:
                   comparison_value = temp_comparison_value
                   chosen_color_index = i
            matched_colors.append(image_color)
            matched_colors_indexes.append(chosen_color_index)
            image_copy.set_at((x, y), chosen_color_index)
    image = image_copy
    return image_copy   


def capture_sprite(rect, image):
    
    capturing_rect = Rect([0, 0, 0, 0])
    #alpha_color = image.get_at(rect.topleft)
    alpha_color = image.get_palette_at(0)
    other_color = False
    
    old_x = rect.x + rect.width
    for y in range(rect.y, rect.y + rect.height, 1):
        for x in range(rect.x, rect.x + rect.width, 1):
            if image.get_at((x,y)) != alpha_color:
               other_color = True
               if x < old_x:
                  old_x = x
                  capturing_rect.x = x
                  break
                
    if other_color:
       old_x = rect.x
       for y in range(rect.y, rect.y + rect.height, 1):
           for x in range(rect.x + rect.width, rect.x-1, -1):
               if image.get_at((x,y)) != alpha_color:
                  if x > old_x :
                     old_x = x 
                     if x > rect.x:
                        capturing_rect.width = (x+1) - capturing_rect.x
                     break
                    
       old_y = rect.y + rect.height             
       for x in range(rect.x, rect.x + rect.width, 1):
           for y in range(rect.y, rect.y + rect.height, 1):
               if image.get_at((x,y)) != alpha_color:
                  if y < old_y:
                     old_y = y
                     capturing_rect.y = y
                     break
                    
       old_y = rect.y             
       for x in range(rect.x, rect.x + rect.width, 1):
           for y in range(rect.y + rect.height, rect.y-1, -1):
               if image.get_at((x,y)) != alpha_color:
                  if y > old_y :
                     old_y = y 
                     if y > rect.y:
                        capturing_rect.height = (y+1) - capturing_rect.y
                     break
                    
       return capturing_rect


def convert_all_sprites(directory, character_name="test"):
    screen = pygame.display.set_mode((160, 120))
    font=pygame.font.SysFont('Arial', 20)
    text=font.render("CONVERTING...", True, WHITE)
    screen.blit(text,(8,45))
    pygame.display.flip()
    sfibm_palette=get_palette(palette_path)
    alpha_color = sfibm_palette[0]
    image_files = []
    compressed_images_data = b''
    try:
        with open(character_name+'.IDE', 'r') as file:
             data=file.read()
        data=data.split('_the_end')
        images_info = data[0]
        sprites_info = data[1]
        collisions_info = data[2]
        images=load_RE(character_name+'.RE',character_name+'.IDE',sfibm_palette)
        image_number = len(images)-1
    except(FileNotFoundError, IndexError):
        shadow_images = load_RE("characters\\SHADOW.RE","characters\\SHADOW.IDE",sfibm_palette)
        shadow_image = shadow_images[0]['image'].convert(8)
        with open(character_name+'.RE', 'bw') as file:
             compressed_image_data = Runlength_compression(shadow_image, shadow_image.get_palette_at(0))
             file.write(compressed_image_data)
        with open(character_name+'.IDE', 'w') as file:
             file.write("======Image=======\n{}.RE\n".format(character_name))
             file.write("1SHADOW.49    319   49    8\n")
             file.write("_the_end\n=====Sprite=======\n")
             file.write("1SHADOW.49      0  -24   -8 -1\n")
             file.write("_the_end\n==Collision_Info==\n")
             file.write("  0   0   0   0\n")
        images_info = "======Image=======\n{}.RE\n1SHADOW.49    319   49    8\n".format(character_name)
        sprites_info = "\n=====Sprite=======\n1SHADOW.49      0  -24   -8 -1\n"
        collisions_info = "\n==Collision_Info==\n  0   0   0   0\n"
        image_number = 0
    for file in os.listdir(directory):
        if file[-3:] in ('PCX','pcx','PNG','png','BMP','bmp'):
           image_files.append(file)
    image_files_length = len(image_files)       
    for image_files_index in range(len(image_files)):
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()       
        image = pygame.image.load(directory+image_files[image_files_index]).convert(8)
        rect = Rect(0, 0, image.get_width() -1 , image.get_height() - 1)
        rect = capture_sprite(rect, image)
        image = image.subsurface(rect)
        palette=image.get_palette()
        #image_swap_color_index(image, 99, 0)
        image.set_palette_at(0, alpha_color)
        image = image_match_palette(image, sfibm_palette)
        compressed_image_data = Runlength_compression(image, image.get_palette_at(0))
        compressed_images_data += compressed_image_data
        image_name = image_files[image_files_index][:-4]
        image_width = image.get_width()
        image_height = image.get_height()
        compression_lenght = len(compressed_image_data)
        image_info = "{}.{}   {}   {}   {}\n".format(image_name, image_width, compression_lenght, image_width, image_height)
        images_info += image_info
        image_number += 1
        sprite_info = "{}   {}   {}   {} -1\n".format(image_name, image_number, -int(image_width/2), -image_height)
        sprites_info += sprite_info
        collisions_info += "  0   0   0   0\n"
        pygame.draw.rect(screen, WHITE, [22, 77, 105, 15], 2)
        converting_percentage = int(image_files_index * 100 / image_files_length)+1
        pygame.draw.rect(screen, TURQUOISE, [25, 80, converting_percentage, 10], 0)
        pygame.display.flip()
    with open(character_name+'.RE', 'ba') as file:
         file.write(compressed_images_data)
    with open(character_name+'.IDE', 'w') as file:
         file.write(images_info)
         file.write("_the_end")
         file.write(sprites_info)
         file.write("_the_end")
         file.write(collisions_info)
    screen.fill(BLACK)
    text=font.render("DONE", True, WHITE)
    screen.blit(text,(50,45))
    pygame.display.flip()
    pygame.quit()
    sys.exit()

        
def view_directory_images(directory, character_name="test"):
    screen = pygame.display.set_mode((640, 480))
    clock=pygame.time.Clock()
    font=pygame.font.SysFont('Arial', 20)
    sfibm_palette=get_palette(palette_path)
    alpha_color = sfibm_palette[0]
    shadow_images = load_RE("characters\\SHADOW.RE","characters\\SHADOW.IDE",sfibm_palette)
    shadow_image = shadow_images[0]['image'].convert(8)
    try:
        with open(character_name+'.IDE', 'r') as file:
             data=file.read()
        data=data.split('_the_end')
        images_info = data[0]
        sprites_info = data[1]
        collisions_info = data[2]
        images=load_RE(character_name+'.RE',character_name+'.IDE',sfibm_palette)
        image_number = len(images)-1
        #print(image_number,images_info,sprites_info,collisions_info)
    except(FileNotFoundError, IndexError):
        with open(character_name+'.RE', 'bw') as file:
             compressed_image_data = Runlength_compression(shadow_image, shadow_image.get_palette_at(0))
             file.write(compressed_image_data)  #compressed_image_data_length:316==>319
        with open(character_name+'.IDE', 'w') as file:
             file.write("======Image=======\n{}.RE\n".format(character_name))
             file.write("1SHADOW.49    319   49    8\n")
             file.write("_the_end\n=====Sprite=======\n")
             file.write("1SHADOW.49      0  -24   -8 -1\n")
             file.write("_the_end\n==Collision_Info==\n")
             file.write("  0   0   0   0\n")
        images_info = "======Image=======\n{}.RE\n1SHADOW.49    319   49    8\n".format(character_name)
        sprites_info = "\n=====Sprite=======\n1SHADOW.49      0  -24   -8 -1\n"
        collisions_info = "\n==Collision_Info==\n  0   0   0   0\n"
        image_number = 0
    sfibm_palette_image = get_palette_image(sfibm_palette)
    sfibm_palette_image_pos = [680 - (sfibm_palette_image.get_width() + 50), 50]
    sfibm_palette_image_rect = sfibm_palette_image.get_rect()
    sfibm_palette_image_rect.move_ip(sfibm_palette_image_pos)
    sfibm_color_index = 0
    sfibm_selected_color = sfibm_palette[sfibm_color_index]
    update = True
    image_files = []
    image_files_index = 0
    pcx_length = 0
    png_length = 0
    bmp_length = 0
    message = font.render('Images Viewer', True, RED)
    message_time = 50
    
    for file in os.listdir(directory):
        if file[-3:] in ('PCX','pcx','PNG','png','BMP','bmp'):
           image_files.append(file)
           if file[-3:] in ('PCX','pcx'):
              pcx_length += 1
           elif file[-3:] in ('PNG','png'):
              png_length += 1
           elif file[-3:] in ('BMP','bmp'):
              bmp_length += 1                            
    image_files_length = len(image_files)-1
    image = pygame.image.load(directory+image_files[image_files_index]).convert(8)
    image_palette = image.get_palette()
    image_palette_image = get_palette_image(image_palette)
    image_palette_image_rect = image_palette_image.get_rect()
    image_palette_image_pos = [680 - (image_palette_image.get_width() + 50), 250]
    image_palette_image_rect.move_ip(image_palette_image_pos)
    image_color_index = 0
    image_selected_color = image_palette[image_color_index]
    
    pygame.key.set_repeat(400, 30)

    while True:

        #loop speed limitation
        #30 frames per second is enought
        clock.tick(30)
        
        for event in pygame.event.get():    #wait for events
            if event.type == QUIT:
                pygame.quit()
                sys.exit()

            if event.type == KEYDOWN:
               if event.key == K_ESCAPE:
                  pygame.quit()
                  sys.exit()
               if event.key == K_RIGHT:
                  image_files_index += 1
                  if image_files_index > image_files_length:
                     image_files_index = 0
                  image_file = image_files[image_files_index]
                  #try:
                  image = pygame.image.load(directory+image_files[image_files_index]).convert(8)
                  image_palette = image.get_palette()
                  image_palette_image = get_palette_image(image_palette)
                  #except pygame.error:pass
                  update = True   
               elif event.key == K_LEFT:
                  image_files_index -= 1
                  if image_files_index < 0:
                     image_files_index = image_files_length
                  image_file = image_files[image_files_index]
                  image = pygame.image.load(directory+image_files[image_files_index]).convert(8)
                  image_palette = image.get_palette()
                  image_palette_image = get_palette_image(image_palette)
                  update = True
               elif event.key == K_c:
                  sfibm_color_index =  color_match_palette(image_selected_color, sfibm_palette)
                  sfibm_selected_color = sfibm_palette[sfibm_color_index]
                  update = True
               elif event.key == K_v:
                  image_change_color(image, image_color_index, sfibm_color_index)
                  update = True 
               elif event.key == K_p:    
                  image_swap_color_index(image, image_color_index, 0)
                  image_palette = image.get_palette()
                  image_palette_image = get_palette_image(image_palette)                  
                  update = True                  
               elif event.key == K_t:
                  image.set_colorkey(image_selected_color) 
                  update = True
               elif event.key == K_s:
                  #image = pygame.transform.flip(image,True,False) 
                  image_scaled_size = (int(image.get_width()/SCALE),int(image.get_height()/SCALE))
                  image = pygame.transform.scale(image,image_scaled_size)
                  update = True                  
               elif event.key == K_u:
                  unused_colors_indexes = find_unused_palette_colors(image.get_palette(), image)
                  for colors_index in unused_colors_indexes:
                      image.set_palette_at(colors_index, (0, 0, 0, 255))
                  image_palette = image.get_palette()    
                  image_palette_image = get_palette_image(image_palette)    
                  update = True   
               elif event.key == K_RETURN:
                  image = image_files[image_files_index]
                  image = pygame.image.load(directory+image_files[image_files_index]).convert(8)
                  rect = Rect(0, 0, image.get_width() -1 , image.get_height() - 1)
                  rect = capture_sprite(rect, image)
                  image = image.subsurface(rect)
                  #image_swap_color_index(image, 99, 0)
                  image.set_palette_at(0, alpha_color)
                  image = image_match_palette(image, sfibm_palette)
                  image_palette = image.get_palette()
                  image_palette_image = get_palette_image(image_palette)
                  image_selected_color = image_palette[image_color_index]
                  update = True
               elif event.key == K_SPACE:
                  image.set_colorkey(alpha_color)
                  update = True
               elif event.key == K_F2:
                  try:
                      with open(character_name+'.RE', 'bx') as file:
                           compressed_image_data = Runlength_compression(shadow_image, shadow_image.get_palette_at(0))
                           file.write(compressed_image_data)
                      with open(character_name+'.IDE', 'x') as file:
                           file.write("======Image=======\n{}.RE\n".format(character_name))
                           file.write("1SHADOW.49    319   49    8\n")
                           file.write("_the_end\n=====Sprite=======\n")
                           file.write("1SHADOW.49      0  -24   -8 -1\n")
                           file.write("_the_end\n==Collision_Info==\n")
                           file.write("  0   0   0   0\n")
                      images_info = "======Image=======\n{}.RE\n1SHADOW.49    319   49    8\n".format(character_name)
                      sprites_info = "\n=====Sprite=======\n1SHADOW.49      0  -24   -8 -1\n"
                      collisions_info = "\n==Collision_Info==\n  0   0   0   0\n"
                      image_number = 0
                      message = font.render('File Write', True, RED)
                      message_time = 50
                      update = True
                  except FileExistsError:
                      message = font.render('File Exists', True, RED)
                      message_time = 50
                      update = True
               elif event.key == K_F5:
                  with open(character_name+'.RE', 'ba') as file:
                       compressed_image_data = Runlength_compression(image, image.get_palette_at(0))
                       file.write(compressed_image_data)
                  with open(character_name+'.IDE', 'w') as file:
                       image_name = image_files[image_files_index][:-4]
                       image_width = image.get_width()
                       image_height = image.get_height()
                       compression_lenght = len(compressed_image_data)
                       file.write(images_info)
                       image_info = "{}.{}   {}   {}   {}\n".format(image_name, image_width, compression_lenght, image_width, image_height)
                       file.write(image_info)
                       images_info += image_info
                       file.write("_the_end")
                       file.write(sprites_info)
                       image_number += 1       #;print(image_number)
                       sprite_info = "{}   {}   {}   {} -1\n".format(image_name, image_number, -int(image_width/2), -image_height)
                       file.write(sprite_info)
                       sprites_info += sprite_info
                       file.write("_the_end")           
                       file.write(collisions_info)
                       file.write("  0   0   0   0\n")
                       collisions_info += "  0   0   0   0\n"
                  message = font.render('File Write', True, RED)
                  message_time = 50
                  update = True
            if event.type == MOUSEBUTTONDOWN:
               if event.button==1:
                  if sfibm_palette_image_rect.collidepoint(event.pos):
                     x = int((event.pos[0] - sfibm_palette_image_rect[0]) / 10)%16
                     y = int((event.pos[1] - sfibm_palette_image_rect[1]) / 10)%16
                     sfibm_color_index =  x + (y * 16)
                     sfibm_selected_color = sfibm_palette[sfibm_color_index]
                     update = True
                  elif image_palette_image_rect.collidepoint(event.pos):
                     x = int((event.pos[0] - image_palette_image_rect[0]) / 10)%16
                     y = int((event.pos[1] - image_palette_image_rect[1]) / 10)%16
                     image_color_index =  x + (y * 16)
                     image_selected_color = image_palette[image_color_index]
                     update = True
               elif event.button==3:
                   if image.get_rect().collidepoint(event.pos):
                      image_color_index =  image.get_at_mapped(event.pos)
                      image_selected_color = image_palette[image_color_index]
                      #message = font.render(str(image_color_index), True, RED)
                      #message = font.render(str(image.get_at(event.pos)), True, RED)
                      #message_time = 50
                      update = True


        if update:
           update = False
           screen.fill(WHITE)
           screen.blit(image,(0,0))
           screen.blit(sfibm_palette_image, sfibm_palette_image_pos)
           screen.blit(image_palette_image, image_palette_image_pos)
           text=font.render(str(bmp_length)+' BMP', True, RED)
           screen.blit(text,(280,130))           
           text=font.render(str(pcx_length)+' PCX', True, RED)
           screen.blit(text,(280,160))
           text=font.render(str(png_length)+' PNG', True, RED)
           screen.blit(text,(280,190))           
           text=font.render(str(image_files_index)+' /'+str(image_files_length), True, RED)
           screen.blit(text,(280,240))
           text=font.render(image_files[image_files_index], True, RED)
           screen.blit(text,(280,260))
           text=font.render("SFIBM Palette", True, RED)
           screen.blit(text,(sfibm_palette_image_pos[0],20))
           text=font.render("Image Palette", True, RED)
           screen.blit(text,(image_palette_image_pos[0],220))
           rect = [438, 52, 20, 20]
           pygame.draw.rect(screen, sfibm_selected_color, rect, 0)
           text=font.render("RGB: {}, {}, {}".format(*sfibm_selected_color), True, RED)
           text_pos=[rect[0]-text.get_width()-12, rect[1]]
           screen.blit(text,text_pos)
           text=font.render("Index: "+str(sfibm_color_index), True, RED)
           screen.blit(text,(text_pos[0], text_pos[1]+20))           
           rect = [438, 390, 20, 20]
           pygame.draw.rect(screen, image_selected_color, rect, 0)
           text=font.render("RGB: {}, {}, {}".format(*image_selected_color), True, RED)
           text_pos=[rect[0]-text.get_width()-12, rect[1]]
           screen.blit(text,text_pos)
           text=font.render("Index: "+str(image_color_index), True, RED)
           screen.blit(text,(text_pos[0], text_pos[1]+20))           
           rect = [sfibm_palette_image_pos[0]+(sfibm_color_index * 10) % 160,
                   sfibm_palette_image_pos[1]+(sfibm_color_index) //  16 * 10, 11, 11]
           pygame.draw.rect(screen, TURQUOISE, rect, 2)
           rect = [image_palette_image_pos[0]+(image_color_index * 10) % 160,
                   image_palette_image_pos[1]+(image_color_index) //  16 * 10, 11, 11]
           pygame.draw.rect(screen, TURQUOISE, rect, 2)
           if message_time > 0:
              message_time -=1
              screen.blit(message,(280,300))
              update = True
           pygame.display.flip()

#directory = "fighting engine\\k91v12s\\sprites\\charlce\\"
#convert_all_sprites(directory,'CHARLCE')
#view_directory_images(directory,'CHARLCE')


def sprite_editor(RE,IDE):
    screen = pygame.display.set_mode((640, 480))#,0,8)
    clock=pygame.time.Clock()
    PALETTE=get_palette(palette_path)
    #pygame.display.set_palette(get_palette(PALETTE))
    font=pygame.font.SysFont('Arial', 20)
    frames=load_RE(RE,IDE,PALETTE)
    with open(IDE, 'r') as file:
         data=file.read()
    data=data.split('_the_end')
    images_info = data[0]
    image=frames[0]['image']
    image_rect = image.get_rect()
    images_lenth=len(frames)-1
    image_gripping = False
    dragging_start_pos = [0, 0]
    dragging_end_pos = [0, 0]
    gripping_start_pos = [0, 0]
    collision_rect_gripping = False
    update=True
    image_index=0
    image_axis_pos=[200,400]
    image_pos=[0,0]
    frame=frames[image_index]
    message = font.render('Sprite Editor', True, RED)
    message_time = 50    
    
    pygame.key.set_repeat(400, 30)

    while True:

        #loop speed limitation
        #30 frames per second is enought
        clock.tick(30)
        
        for event in pygame.event.get():    #wait for events
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
             
            if event.type == KEYDOWN:
               if event.key == K_RIGHT:
                  image_index+=1
                  if image_index>images_lenth:
                     image_index=0
                  frame=frames[image_index]
                  update=True
               elif event.key == K_LEFT:
                  image_index-=1
                  if image_index<0:
                     image_index=images_lenth
                  frame=frames[image_index]
                  update=True
               if event.key == K_o:
                  frame['collision_box'] = [0, 0, 0, 0]
                  update=True
               if event.key == K_c:
                  frame['x_axis_shift'] = -int(image.get_width()/2/SCALE)
                  frame['y_axis_shift'] = -int(image.get_height()/SCALE)
                  update=True    
               if event.key == K_RETURN:
                  with open(IDE, 'w') as file:
                       data = ""
                       data = images_info
                       sprites_info = ""
                       collisions_info = ""
                       for i in range(len(frames)):
                           seq_frame = frames[i]
                           sprites_info += "{}  {}  {}  {}  -1\n".format(seq_frame['name'], i,
                                            seq_frame['x_axis_shift'], seq_frame['y_axis_shift'])
                           collision =[seq_frame['collision_box'][0], seq_frame['collision_box'][1], 0, 0]
                           collision[2] = seq_frame['collision_box'][0] + seq_frame['collision_box'][2]
                           collision[3] = seq_frame['collision_box'][1] + seq_frame['collision_box'][3]
                           collisions_info += "  {}   {}   {}   {}\n".format(*collision)
                       data = ""
                       data += images_info
                       data += "_the_end\n=====Sprite=======\n"
                       data += sprites_info
                       data += "_the_end\n==Collision_Info==\n"
                       data += collisions_info
                       file.write(data)
                       message = font.render("Changes Saved", True, RED)
                       message_time = 50
                       update=True
            if event.type == MOUSEBUTTONDOWN:
               if event.button == 1: 
                  if image_rect.collidepoint(event.pos):
                     image_gripping = True
                     dragging_start_pos = event.pos
               elif event.button == 3:
                  gripping_start_pos[0] =  event.pos[0] - image_pos[0]
                  gripping_start_pos[1] =  event.pos[1] - image_pos[1]
                  frame['collision_box'][0] =  event.pos[0] - image_pos[0]
                  frame['collision_box'][1] =  event.pos[1] - image_pos[1]
                  frame['collision_box'][2] = 0
                  frame['collision_box'][3] = 0
                  collision_rect_gripping = True
            if event.type == MOUSEBUTTONUP:
               if image_gripping:
                  image_gripping = False
                  frame['x_axis_shift'] = int(frame['x_axis_shift'])
                  frame['y_axis_shift'] = int(frame['y_axis_shift'])
                  update=True
               elif collision_rect_gripping:
                  collision_rect_gripping = False
                  frame['collision_box'][0] =  gripping_start_pos[0]
                  frame['collision_box'][1] =  gripping_start_pos[1]
                  frame['collision_box'][2] = event.pos[0] - image_pos[0] - frame['collision_box'][0]
                  frame['collision_box'][3] = event.pos[1] - image_pos[1] - frame['collision_box'][1]
                  if frame['collision_box'][2] < 0:
                     frame['collision_box'][2] *= -1
                     frame['collision_box'][0] -= frame['collision_box'][2]
                  if frame['collision_box'][3] < 0:
                     frame['collision_box'][3] *= -1
                     frame['collision_box'][1] -= frame['collision_box'][3]
                  frame['collision_box'][0] = int(frame['collision_box'][0] / SCALE)
                  frame['collision_box'][1] = int(frame['collision_box'][1] / SCALE)
                  frame['collision_box'][2] = int(frame['collision_box'][2] / SCALE)
                  frame['collision_box'][3] = int(frame['collision_box'][3] / SCALE)                  
                  update=True
            if event.type == MOUSEMOTION:
               if image_gripping:
                  dragging_end_pos = event.pos
                  frame['x_axis_shift'] += (dragging_end_pos[0] - dragging_start_pos[0]) / SCALE
                  frame['y_axis_shift'] += (dragging_end_pos[1] - dragging_start_pos[1]) / SCALE
                  dragging_start_pos = event.pos
                  update=True
               elif collision_rect_gripping:
                  frame['collision_box'][0] =  gripping_start_pos[0]
                  frame['collision_box'][1] =  gripping_start_pos[1]
                  frame['collision_box'][2] = event.pos[0] - image_pos[0] - frame['collision_box'][0]
                  frame['collision_box'][3] = event.pos[1] - image_pos[1] - frame['collision_box'][1]
                  if frame['collision_box'][2] < 0:
                     frame['collision_box'][2] *= -1
                     frame['collision_box'][0] -= frame['collision_box'][2]
                  if frame['collision_box'][3] < 0:
                     frame['collision_box'][3] *= -1
                     frame['collision_box'][1] -= frame['collision_box'][3]                  
                  frame['collision_box'][0] = int(frame['collision_box'][0] / SCALE)
                  frame['collision_box'][1] = int(frame['collision_box'][1] / SCALE)
                  frame['collision_box'][2] = int(frame['collision_box'][2] / SCALE)
                  frame['collision_box'][3] = int(frame['collision_box'][3] / SCALE)                  
                  update=True

     
        if update:
           update=False
           image=frame['image']
           image_width=image.get_width()
           image_height=image.get_height()
           image_scaled_size=(image_width*SCALE,image_height*SCALE)
           image=pygame.transform.scale(image,image_scaled_size).convert()
           screen.fill((255,255,255))
           x_axis=frame['x_axis_shift']*SCALE
           y_axis=frame['y_axis_shift']*SCALE
           image_pos=[x_axis+image_axis_pos[0],y_axis+image_axis_pos[1]]
           image_rect = Rect(image_pos , image_scaled_size)
           screen.blit(image,image_pos)
           if frame['second_image']:
              old_axis=[x_axis,y_axis]
              image=frame['second_image']['image']
              image_width2=image.get_width()
              image_height2=image.get_height()
              image_scaled_size=(image_width2*SCALE,image_height2*SCALE)
              image=pygame.transform.scale(image,image_scaled_size).convert()
              x_axis=frame['second_image']['x_axis_shift']*SCALE
              y_axis=frame['second_image']['y_axis_shift']*SCALE
              image_pos2=[x_axis+image_axis_pos[0],y_axis+image_axis_pos[1]]
              screen.blit(image,image_pos2)

           temp_rect=frames[image_index]['collision_box']
           rect=[image_pos[0],image_pos[1],image_width*SCALE,image_height*SCALE]
           pygame.draw.rect(screen, (255,0,0), rect,5)
           rect=[image_pos[0]+temp_rect[0]*SCALE,image_pos[1]+temp_rect[1]*SCALE,
                 temp_rect[2]*SCALE,temp_rect[3]*SCALE]
           pygame.draw.rect(screen, (0,0,255), rect,5)
           #pygame.draw.circle(screen,(0,255,0),(image_axis_pos),10)

           pygame.draw.line(screen,(0,255,0),(image_axis_pos[0]-15,image_axis_pos[1]),
                            (image_axis_pos[0]+15,image_axis_pos[1]),5)
           pygame.draw.line(screen,(0,255,0),(image_axis_pos[0],image_axis_pos[1]-15),
                            (image_axis_pos[0],image_axis_pos[1]+15),5)
           text=font.render(str(image_index)+' '+'/'+str(images_lenth), True, (250,0,0))
           screen.blit(text,(420,320))
           text=font.render(frames[image_index]['name'], True, (250,0,0))
           screen.blit(text,(420,340))
           text=font.render("X axis shift:  "+str(int(frame['x_axis_shift'])), True, (250,0,0))
           screen.blit(text,(420,370))
           text=font.render("Y axis shift:  "+str(int(frame['y_axis_shift'])), True, (250,0,0))
           screen.blit(text,(420,390))
           text=font.render("Collision:", True, (250,0,0))
           screen.blit(text,(420,420))
           text=font.render("{}, {}, {}, {}".format(*frame['collision_box']), True, (250,0,0))
           screen.blit(text,(420,440))
           if message_time > 0:
              message_time -=1
              screen.blit(message,(420,280))
              update = True           
           pygame.display.flip()
       
#sprite_editor(RE2,IDE2)#('TOGUR0.RE','TOGUR0.IDE')


def animation_editor(RE,IDE,SEQ):
    screen = pygame.display.set_mode((640, 480))#,0,8)
    clock=pygame.time.Clock()
    PALETTE=get_palette(palette_path)
    #pygame.display.set_palette(get_palette(PALETTE))
    font=pygame.font.SysFont('Arial', 20)
    frames=load_RE(RE,IDE,PALETTE)
    with open(IDE, 'r') as file:
         data=file.read()
    data=data.split('_the_end')
    images_info = data[0]
    sequences_names = {0:"Standing Still", 1:"Jumping up", 2:"Kneeling",
                       3:"Walking back", 4:"Jumping back", 5:"Kneeling back",
                       6:"Walking forward", 7:"Jumping forward", 8:"Kneeling forward",
                       9:"High block", 10:"Low block",
                       11:"Far light kick", 12:"Far medium kick", 13:"Far hard kick",
                       14:"Far light punch", 15:"Far medium punch", 16:"Far hard punch",
                       17:"Close light kick", 18:"Close medium kick", 19:"Close hard kick",
                       20:"Close light punch", 21:"Close medium punch", 22:"Close hard punch",
                       23:"Jump up light kick", 24:"Jump up medium kick", 25:"Jump up hard kick",
                       26:"Jump up light punch", 27:"Jump up medium punch", 28:"Jump up hard punch",
                       29:"Jump towards/away light kick", 30:"Jump towards/away medium kick", 31:"Jump towards/away hard kick",
                       32:"Jump towards/away light punch", 33:"Jump towards/away medium punch", 34:"Jump towards/away hard punch",
                       35:"Ducking light kick", 36:"Ducking medium kick", 37:"Ducking hard kick",
                       38:"Ducking light punch", 39:"Ducking medium punch", 40:"Ducking hard punch",
                       41:"Victory pose 1", 42:"Victory pose 2", 43:"Knocked out", 44:"Draw game",
                       66:"Projectile dissipation", 67:"Hit while blocking high", 68:"Hit while blocking low",
                       71:"hit reaction 0", 72:"hit reaction 1", 73:"hit reaction 2", 74:"hit reaction 3",
                       75:"hit reaction 4", 76:"hit reaction 5", 77:"hit reaction 6", 78:"hit reaction 7",
                       79:"hit reaction 8", 80:"dizzy",
                       108:"Get up from a K.O.", 109:"Jumping ???"}
    sequences, sequences_frames=load_SEQ(SEQ)
    sequences_numbers=[]
    for number in sequences:
        sequences_numbers.append(number)
    sequences_numbers_index=0
    sequences_numbers_length=len(sequences_numbers)-1
    sequence_number=sequences_numbers[sequences_numbers_index]
    sequence_name = sequences_names[sequence_number]
    sequence=sequences[sequence_number]
    sequence_index=0
    sequence_frame=sequences_frames[sequence[sequence_index]]
    frame=frames[sequence_frame['Image_number']]
    image=frame['image']
    image_rect = image.get_rect()
    anim_time=0
    max_anim_time=2
    image_axis_pos=[200,400]
    image_pos=[0,0]
    image_gripping = False
    dragging_start_pos = [0, 0]
    dragging_end_pos = [0, 0]    
    play_animation = True
    update = True
    message = font.render('Animation Editor', True, RED)
    message_time = 50    

    #pygame.key.set_repeat(400, 30)

    while True:

        #loop speed limitation
        #30 frames per second is enought
        clock.tick(30)

        for event in pygame.event.get():    #wait for events
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            if event.type == KEYDOWN:
                if event.key == K_RIGHT:
                   sequences_numbers_index+=1
                   if sequences_numbers_index>sequences_numbers_length:
                      sequences_numbers_index=0
                   sequence_number=sequences_numbers[sequences_numbers_index]
                   if sequence_number in sequences_names:
                      sequence_name = sequences_names[sequence_number]
                   else:
                      sequence_name = " "
                   sequence=sequences[sequence_number]
                   sequence_index=0
                   anim_time=max_anim_time
                   update=True
                elif event.key == K_LEFT:
                   sequences_numbers_index-=1
                   if sequences_numbers_index<0:
                      sequences_numbers_index=sequences_numbers_length
                   sequence_number=sequences_numbers[sequences_numbers_index]
                   if sequence_number in sequences_names:
                      sequence_name = sequences_names[sequence_number]
                   else:
                      sequence_name = " "                   
                   sequence=sequences[sequence_number]
                   sequence_index=0
                   anim_time=max_anim_time
                   update=True
                if event.key == K_UP:
                   play_animation = False
                   sequence_index+=1
                   if sequence[sequence_index]==-1:
                      sequence_index -= 1
                   sequence_frame=sequences_frames[sequence[sequence_index]]
                   frame=frames[sequence_frame['Image_number']]
                   image=frame['image']
                   update=True
                elif event.key == K_DOWN:
                   play_animation = False
                   sequence_index-=1
                   if sequence_index < 0:
                      sequence_index = 0
                   sequence_frame=sequences_frames[sequence[sequence_index]]
                   frame=frames[sequence_frame['Image_number']]
                   image=frame['image']
                   update=True
                if event.key == K_p:
                   if not play_animation:
                      play_animation = True
                   else:
                      play_animation = False
                if event.key == K_c:
                   frame['x_axis_shift'] = -int(image.get_width()/2)
                   frame['y_axis_shift'] = -image.get_height()
                   update=True
                if event.key == K_RETURN:
                   with open(IDE, 'w') as file:
                        data = ""
                        data = images_info
                        sprites_info = ""
                        collisions_info = ""
                        for i in range(len(frames)):
                            seq_frame = frames[i]
                            sprites_info += "{}  {}  {}  {}  -1\n".format(seq_frame['name'], i,
                                             seq_frame['x_axis_shift'], seq_frame['y_axis_shift'])
                            collision =[seq_frame['collision_box'][0], seq_frame['collision_box'][1], 0, 0]
                            collision[2] = seq_frame['collision_box'][0] + seq_frame['collision_box'][2]
                            collision[3] = seq_frame['collision_box'][1] + seq_frame['collision_box'][3]
                            collisions_info += "  {}   {}   {}   {}\n".format(*collision)
                        data = ""
                        data += images_info
                        data += "_the_end\n=====Sprite=======\n"
                        data += sprites_info
                        data += "_the_end\n==Collision_Info==\n"
                        data += collisions_info
                        file.write(data)
                        message = font.render("Changes Saved", True, RED)
                        message_time = 50
                        update=True
                   
            if event.type == MOUSEBUTTONDOWN:
               if event.button == 1: 
                  if image_rect.collidepoint(event.pos):
                     image_gripping = True
                     dragging_start_pos = event.pos
                     play_animation = False
            if event.type == MOUSEBUTTONUP:
               if image_gripping:
                  image_gripping = False
                  frame['x_axis_shift'] = int(frame['x_axis_shift'])
                  frame['y_axis_shift'] = int(frame['y_axis_shift'])
                  update=True
            if event.type == MOUSEMOTION:
               if image_gripping:
                  dragging_end_pos = event.pos
                  frame['x_axis_shift'] += (dragging_end_pos[0] - dragging_start_pos[0]) / SCALE
                  frame['y_axis_shift'] += (dragging_end_pos[1] - dragging_start_pos[1]) / SCALE
                  dragging_start_pos = event.pos
                  update=True
   
        if play_animation:
           anim_time+=1
           if anim_time>=max_anim_time:
              anim_time=0
              sequence_index+=1
              if sequence[sequence_index]==-1:
                 #print(sequence[sequence_index+1])
                 #sequence=sequences[sequence[sequence_index+1]]
                 sequence_index=0
              sequence_frame=sequences_frames[sequence[sequence_index]]
              frame=frames[sequence_frame['Image_number']]
              image=frame['image']
              update=True

        if update:
           update=False
           screen.fill((255,255,255))
           image_width=image.get_width()
           image_height=image.get_height()
           image_scaled_size=(image_width*SCALE,image_height*SCALE)
           scaled_image=pygame.transform.scale(image,image_scaled_size).convert()
           x_axis=frame['x_axis_shift']*SCALE
           y_axis=frame['y_axis_shift']*SCALE
           image_pos=[x_axis+image_axis_pos[0],y_axis+image_axis_pos[1]]
           image_rect = Rect(image_pos , image_scaled_size)
           
           temp_rect=frame['collision_box']
           rect=[image_pos[0],image_pos[1],image_width*SCALE,image_height*SCALE]
           pygame.draw.rect(screen, (255,0,0), rect,5)
           rect=[image_pos[0]+temp_rect[0]*SCALE,image_pos[1]+temp_rect[1]*SCALE,
                 temp_rect[2]*SCALE,temp_rect[3]*SCALE]
           pygame.draw.rect(screen, (0,0,255), rect,5)
           pygame.draw.line(screen,(0,255,0),(image_axis_pos[0]-15,image_axis_pos[1]),
                            (image_axis_pos[0]+15,image_axis_pos[1]),5)
           pygame.draw.line(screen,(0,255,0),(image_axis_pos[0],image_axis_pos[1]-15),
                            (image_axis_pos[0],image_axis_pos[1]+15),5)
           
           screen.blit(scaled_image,image_pos)
           text=font.render(sequence_name, True, (250,0,0))
           screen.blit(text,(420,230))           
           text=font.render(str(sequences_numbers_index)+' '+'/'+str(sequences_numbers_length), True, (250,0,0))
           screen.blit(text,(420,260))
           text=font.render(str(sequence_number)+' '+str(sequence[sequence_index])+' '+str(sequence_index), True, (250,0,0))
           screen.blit(text,(420,280))
           text=font.render(frame['name'], True, (250,0,0))
           screen.blit(text,(420,300))
           text=font.render("X axis shift:  "+str(int(frame['x_axis_shift'])), True, (250,0,0))
           screen.blit(text,(420,370))
           text=font.render("Y axis shift:  "+str(int(frame['y_axis_shift'])), True, (250,0,0))
           screen.blit(text,(420,390))
           text=font.render("Collision:", True, (250,0,0))
           screen.blit(text,(420,420))
           text=font.render("{}, {}, {}, {}".format(*frame['collision_box']), True, (250,0,0))
           screen.blit(text,(420,440))
           if message_time > 0:
              message_time -=1
              screen.blit(message,(420,180))
              update = True           
           pygame.display.flip()
           
animation_editor(RE2,IDE2,SEQ2)

     
if __name__ == "__main__":
    main()
