import sys
import pygame
from Color import Color
from ctypes import *
import numpy as np

minimax = CDLL('./minimax.so')
class GUILoop:
    pass
    EMPTY   = 0
    PLAYER  = 1
    NPC     = 2

    def __init__(self):
        self.m_Col = 3
        self.m_Row = 3

        self.m_mem =  np.zeros((self.m_Col * self.m_Row), dtype=np.int32)

        self.m_Last_Player = GUILoop.NPC

        self.m_Width = 1024
        self.m_Height = 768
        self.m_FPS = 60
        self.m_Display = None
        self.m_Clock = None
        self.m_DX = 0.0
        self.m_DY = 0.0
        self.m_Running = True
        self.m_StepbyStep = True
        self.m_ShowLattice = True
        #We should define the color palette. In this example, I wrote some color in according to site: https://erikasarti.com/html/tabela-cores/
        #Remember to define one unique color for each CA state
        self.m_Palettes = []

        self.m_Palettes.append(Color(0, 255, 0))                        #Green    # It's green, the same color of lattice color <----
        self.m_Palettes.append(Color(255, 0, 0))                        #Red
        self.m_Palettes.append(Color(0, 250, 154))                      #MediumSpringGreen
        self.m_Palettes.append(Color(0, 0, 255))                        #Blue

        self.m_Palettes.append(Color(255, 0, 255))                      #Fuchsia / Magenta
        self.m_Palettes.append(Color(255, 255, 0))                      #Yellow
        self.m_Palettes.append(Color(0, 255, 255))                      #Aqua / Cyan

        self.m_Palettes.append(Color(70, 130, 180))                     #SteelBlue
        self.m_Palettes.append(Color(221, 160, 221))                    #Plum
        self.m_Palettes.append(Color(173, 255, 47))                     #GreenYellow

        self.m_Palettes.append(Color(85, 107, 47))                      #DarkOliveGreen
        self.m_Palettes.append(Color(255, 228, 196))                    #Bisque
        self.m_Palettes.append(Color(106, 90, 205))                     #SlateBlue
        print('--------------------------------------------')
        print('Color palette size:', len(self.m_Palettes))
        print('--------------------------------------------')
        self.setMsg()
        self.help()

    def setPalette(self, p):
        self.m_Palettes = []
        self.m_Palettes = p
        print('--------------------------------------------')
        print('Color palette size:', len(self.m_Palettes))
        print('--------------------------------------------')

    def setMsg(self):
        if self.m_Last_Player == GUILoop.NPC:
            pygame.display.set_caption('Tic-Tac-Toe - [Player]')
            print('Tic-Tac-Toe - [Player]')
        else:
            pygame.display.set_caption('Tic-Tac-Toe - [NPC]')
            print('Tic-Tac-Toe - [NPC]')

    def init(self):
        pygame.init()
        self.m_Display = pygame.display.set_mode((self.m_Width, self.m_Height))

        
        
        self.m_Display.fill((0, 0, 0))
        self.m_Clock = pygame.time.Clock()
        self.m_DX = (self.m_Width / self.m_Col)
        self.m_DY = (self.m_Height / self.m_Row)

    def check(self, ymin, ymax, xmin, xmax, pos):
        if pos[1] < ymin:
            return False
        elif pos[1] > ymax:
            return False
        if pos[0] < xmin:
            return False
        elif pos[0] > xmax:
            return False
        else:
            return True


    def pos2pos(self, pos):
        print(pos)
        
        col = -1
        row = -1

        dx = self.m_Width / self.m_Col
        dy = self.m_Height  / self.m_Row
        j = 0
        found = False
        
        while j < self.m_Row and not found:
            i = 0
            ymin = j * dy
            ymax = (j+1) * dy
            
            while i < self.m_Col and not found:
                xmin = i * dx
                xmax = (i+1) * dx   
                found = self.check(ymin, ymax, xmin, xmax, pos)
                if (found):
                    print('Found in:', i, j)
                    col = i
                    row = j
                     
                i = i + 1
            j = j + 1

        if (found):
            s = self.m_mem[row * self.m_Col + col]
            if s == GUILoop.EMPTY:
            
                if self.m_Last_Player == GUILoop.NPC:
                    self.m_mem[row * self.m_Col + col] = GUILoop.PLAYER
                    self.m_Last_Player =  GUILoop.PLAYER
                     
                    
                else:
                    self.m_mem[row * self.m_Col + col] = GUILoop.NPC
                    self.m_Last_Player = GUILoop.NPC
                     
                self.update()
            else:
                print('Position occupied!')


                



    def toPNG(self):
        filename = 'snapshot.png'
        pygame.image.save(self.m_Display, filename)
        print('File: ', filename, ' saved')

    def help(self):
        print('Help...')
    #main loop
    def loop(self):
        while self.m_Running:
            self.input()
            #self.update()
            self.render()

    #input key - only for render
    def input(self):
        for e in pygame.event.get():
            if e.type == pygame.MOUSEBUTTONUP:
                    self.pos2pos(pygame.mouse.get_pos())
                    
                    
            if e.type == pygame.QUIT:                                   #close window
                self.m_Running = False
            if e.type == pygame.KEYDOWN:
                if e.key == pygame.K_ESCAPE:                               #close window
                    self.m_Running = False
                if e.key == pygame.K_e:                                 #enable step by step
                    self.m_StepbyStep = not self.m_StepbyStep
                if e.key == pygame.K_l:                                 #show lattice
                    self.m_ShowLattice = not self.m_ShowLattice
                if e.key == pygame.K_u:                                 #update steps
                    print('Update')
                if e.key == pygame.K_s:                                 #save to file - the time step is part of name
                    self.toPNG()
                if e.key == pygame.K_h:
                    self.help()

    # Update the cells state
    def update(self):
        self.setMsg()
        print('Thinking....')
        ret = minimax.checkGameOver(self.m_mem.ctypes.data_as(c_void_p))
        print('Answer: ', ret)
        if ret == -1:
            print('GAME OVER!')
        else:
            print('Winner is', ret)

    #render
    def render(self):
        
        self.m_Clock.tick(self.m_FPS)
        self.m_Display.fill((0, 0, 0))


        if self.m_ShowLattice:
            #Lines of lattice
            for j in range(1, self.m_Row):
                pygame.draw.line(self.m_Display, (0, 255, 0), (0, j * self.m_DY), (self.m_Width, j * self.m_DY))

            #columns of lattice
            for i in range(1, self.m_Col):
                pygame.draw.line(self.m_Display, (0, 255, 0), (i * self.m_DX, 0), (i * self.m_DX, self.m_Height))


        #state render only if s > 0. 0 state is black
        for j in range(0, self.m_Row):
            for i in range(0, self.m_Col):
                s = self.m_mem[j *  self.m_Col + i]

                if s > 0:
                    c = s % len (self.m_Palettes)
                    color = self.m_Palettes[c]
                    x = i * self.m_DX
                    y = j * self.m_DY
                    pygame.draw.rect(self.m_Display, (color.r, color.g, color.b), (x + 1, y + 1, self.m_DX - 2, self.m_DY - 2), 0)
        pygame.display.flip()


if __name__ == '__main__':
    gui = GUILoop()
   
    print(minimax)
    print('Hello')
    #print(minimax.power2(10))
    #print(minimax.power3(10))
    
    #minimax.checkGameOver(m_mem.ctypes.data_as(c_void_p))
    gui.init()
    gui.loop()