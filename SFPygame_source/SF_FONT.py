import pygame,sys,math,random,os,pickle
from pygame.locals import *

pygame.init()

palette_path="SFIBM 125\\RGB.PAL"
sfibm_path="C:SFIBM 125\\"
font_path=sfibm_path+"SF2W.FNT"

#Red
_R7 = 0xe0
_R6 = 0xc0
_R5 = 0xa0
_R4 = 0x80
_R3 = 0x60
_R2 = 0x40
_R1 = 0x20
#Green
_G7 = 0x1c
_G6 = 0x18
_G5 = 0x14
_G4 = 0x10
_G3 = 0x0c
_G2 = 0x08
_G1 = 0x04
#Black
_B3 = 0x03
_B2 = 0x02
_B1 = 0x01


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


def swap_nibble(bitmap):
    bytes_list = list(bitmap)
    for i in range(len(bytes_list)):
	#print( bin(((byte<<4)&255) | (byte>>4) )
        #bytes_list[i] = ((bytes_list[i]<<4)&255) | (bytes_list[i]>>4)
        b=bytes_list[i]
        bytes_list[i] = (b<<3&136)|(b<<1&68)|(b>>1&34)|(b>>3&17)
    return bytes(bytes_list)
        
def print_bitmap(bitmap):
    for byte in bitmap:
        print(bin(byte|512))

def char_id(char):
    return (ord(char)-33)<<4

def make_char(bitmap,color=(255,0,0)):
    image=pygame.Surface((8,16)).convert()
    #image.set_colorkey((0,0,0))
    swapped_bitmap=swap_nibble(bitmap)
    y=0
    for byte in swapped_bitmap:
        b=bin(byte|256)
        x=0
        for i in range(3,11):
            if b[i] == '1':
               image.set_at((x,y),color)
            x+=1
        y+=1
    return image


def print_font(font_file):
    with open(font_file, 'rb') as file:
         _FCBITMAP=file.read(190*32)
         _MCBITMAP=file.read(84*32)
         _LCBITMAP=file.read(108*32)
         file.read(char_id('!'))    
         for i in range(100):  #94-95
             _ECBITMAP=file.read(16)
             print("\n\n\n",i,chr(i+33))
             print_bitmap(swap_nibble(_ECBITMAP))


def view_font(font_file):
    screen = pygame.display.set_mode((640, 480))
    clock=pygame.time.Clock()
    PALETTE=get_palette(palette_path)
    color=(255,0,0)#PALETTE[_R7|_G5]
    with open(font_file, 'rb') as file:
         #file.seek((190*32)+(84*32)+(108*32))
         _FCBITMAP=file.read(190*32)
         _MCBITMAP=file.read(84*32)
         _LCBITMAP=file.read(108*32)
         file.read(char_id('!'))
         #_ECBITMAP=file.read(16)#(1*1504)
         
         
         image_size=(8,16)
         screen.fill((255,255,255))
         x=0
         y=0
         for i in range(100):  #94-95
             _ECBITMAP=file.read(16)
             image=make_char(_ECBITMAP,color)
             image_scaled_size=(image_size[0]*4,image_size[1]*4)
             image=pygame.transform.scale(image,image_scaled_size).convert()
             screen.blit(image,(x*4*8,y*4*16))
             x+=1
             if x == 20:
                x=0 
                y+=1
         pygame.display.flip()

    while True:
        clock.tick(10)
        for event in pygame.event.get():
            if event.type == QUIT:
               pygame.quit()
               sys.exit()
            if event.type == KEYDOWN:
                if event.key == K_ESCAPE:
                   pygame.quit()
                   sys.exit()
                    

#print_font(font_path)
view_font(font_path)
