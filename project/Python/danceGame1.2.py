#  DANCE GAME                               #
#  danceGame.py                             #
#  Author: Matthew D'Alonzo                 #
#  This is a Key-Pressing, Music Making,    #
#  rhythm game that is sweeping the nation. #


# Library Imports #                 
import pygame
import random
import numpy
import scipy
import sys
from scipy.io import wavfile
from tkinter.filedialog import askopenfilename
from tkinter import *
import pydub
from pydub import AudioSegment
pydub.AudioSegment.ffmpeg = "/absolute/path/to/ffmpeg"
AudioSegment.converter = "C:/ffmpeg-20160731-04da20e-win64-static/bin/ffmpeg.exe"

## STATIC VARIABLES ##
size=[640,480] # Size of pygame screen. I want to be able to adjust this!
streak1=10 # Value of first streak level
streak2=20 # Value of second streak level
streak3=30 # Value of max streak level
partitions=10000 # Incrementation at which program will check for a max
difficulty='easy'
make_random_song=False # This is if you want to make a random song
title_screen=True

## COLORS ##
backgroundcolor=(13,27,30) # Sets background color
score_color=(18,78,120) # Sets score color
landing_color=(146,20,12) # Sets landing color
dark_landing_color=(116,10,5)
arrow_color=(240,240,201) # Sets Arrow Color
streak_color=(244,255,82) # Sets Streak Color

## INCREMENTAL VARIABLES ##
score=0 # Keeps track of user score
streak=0 # Keeps track of consecutive hits
counter=0 # Keeps track of times run through program
multiplier=1 # Keeps of track of score multiplier
done=False # Checks if program should end
pressedtoolong=[0,0,0,0] # Keeps the user from holding the button too long
streak_cmp=[0,0] # Keeps streak values
score_cmp=[0,0] # Keeps score values

## INITIALIZATIONS ##
pygame.init() # Initializes PyGame Module
screen=pygame.display.set_mode(size) # Sets screen to screen size
icon=pygame.image.load("icon.png")
pygame.display.set_icon(icon)
pygame.display.set_caption("Dance Game- Matthew D'Alonzo")
myfont=pygame.font.Font("6809.ttf",40) # Initializes font for score
multiplierfont=pygame.font.Font("6809.ttf",25) # Sets font for multiplier
hitmissfont=pygame.font.Font("6809.ttf",30) # Sets font for hitmiss
hitmiss=hitmissfont.render("",1,(255,255,255)) # Initializes hitmiss so it's blank at the start
score_string="" # String for score
clock = pygame.time.Clock() # Initializes clock module
title_label=myfont.render("Matthew D.'s Dance Game!",1,(score_color))
score_thing=pygame.image.load("scoreborder1.png")

## LISTS ##
new_data=[] # This holds the averaged song data
new_list=[]	# This holds a transferred list later on
index_list={} # This holds the max values and indices during partitioning
song_index_two=[] # Final song index
randy_songindex=[] # This is for if you want to use the random song




##  CLASSES  ##
##    AND    ##
## FUNCITONS ##

def song_maker():
	## SONG LOADER ##
	filename = askopenfilename()
	print(filename)
	AudioSegment.from_file(filename).export("sound.wav",format="wav")
	Tk().quit()
	# print("sound is")
	# print(sound)
	screen.fill(backgroundcolor)
	title_label=myfont.render("Loading Song! (1/5)",1,(score_color))
	screen.blit(title_label,(30,100))
	pygame.display.flip()
	song=pygame.mixer.music.load("sound.wav") # Loads the song into pygame.
	fs,data=wavfile.read("sound.wav") # Loads song data into scipy


	## AVERAGING FILTER ##
	# This averages the values of the stereo channel into one set of data
	# screen.fill(backgroundcolor)
	# title_label=myfont.render("Averaging the Data! (2/5)",1,(score_color))
	# screen.blit(title_label,(30,100))
	# pygame.display.flip()
	# for i in range((len(data))):
	# 	new_data.append((data[i][0]+data[i][1])/2)
	# 	if i%50000==0:
	# 		pygame.draw.rect(screen,backgroundcolor,(0,200,640,340))
	# 		pygame.draw.rect(screen,landing_color,(90,290,460,95))
	# 		pygame.draw.rect(screen,score_color,(100,300,440*(i/len(data)),75))
	# 		pygame.draw.rect(screen,dark_landing_color,(260,180,120,90))
	# 		pygame.draw.rect(screen,landing_color,(270,190,100,70))
	# 		percent_t=str(int(i/len(data)*100))+"%"
	# 		percent_label=myfont.render(percent_t,1,(score_color))
	# 		screen.blit(percent_label,(280,200))
	# 		pygame.display.flip()
	# total_things=len(new_data)
	new_data= [item[0] for item in data]

	## MAX FINDER IN PARTITIONS ##
	# This finds the max of each decided set of partitions of the song
	screen.fill(backgroundcolor)
	title_label=myfont.render("Finding the Max! (3/5)",1,(score_color))
	screen.blit(title_label,(40,100))
	pygame.display.flip()
	for i in range(len(new_data)):
		if i is not 0:
			if int(i%partitions)==0:
				max_value=new_data[i-partitions]
				for j in range(i-partitions,i):
					if new_data[j]>max_value:
						max_value=i
						max_index=j
				index_list[i]=j
			if int(i%(partitions*10))==0:
				pygame.draw.rect(screen,backgroundcolor,(0,200,640,340))
				pygame.draw.rect(screen,landing_color,(90,290,460,95))
				pygame.draw.rect(screen,score_color,(100,300,440*(i/len(data)),75))
				pygame.draw.rect(screen,dark_landing_color,(260,180,120,90))
				pygame.draw.rect(screen,landing_color,(270,190,100,70))
				percent_t=str(int(i/len(data)*100))+"%"
				percent_label=myfont.render(percent_t,1,(score_color))
				screen.blit(percent_label,(280,200))
				pygame.display.flip()


	## CLEARER ##
	# This deletes values in the list of indices that have values
	# that are a certain percentage lower than the max.
	# I need to figure out a better way to do this!
	screen.fill(backgroundcolor)
	title_label=myfont.render("Removing Noise! (4/5)",1,(score_color))
	screen.blit(title_label,(30,100))
	pygame.display.flip()
	range_values=int(max(index_list.keys()))
	keythings=list(index_list.keys())
	for i in keythings:
		if i<range_values*0.02:
			del index_list[i]



	## LIST MOVER ##
	# This moves the values in the dictionary 
	# over into a normal list.
	screen.fill(backgroundcolor)
	title_label=myfont.render("Adjusting things! (5/5)",1,(score_color))
	screen.blit(title_label,(30,100))
	pygame.display.flip()
	new_new_list=[]
	for i in index_list.values():
		new_new_list.append(int(i))	
	print(len(new_new_list))
	if difficulty=='easy':
		for i in range(len(new_new_list)):
			if i%2==0:
				new_list.append(new_new_list[i])
	elif difficulty=='medium':
		for i in range(len(new_new_list)):
			if i%4==0:
				new_list.append(new_new_list[i])
	else:
		for i in range(len(new_new_list)):
			new_list.append(new_new_list[i])
	print(len(new_list))
	return fs,new_list

class arrows(pygame.sprite.Sprite):
	def __init__(self,angle,xloc):
		super(arrows,self).__init__()
		self.xloc=xloc
		self.angle=angle
		self.image=pygame.image.load("arrows1.1.png")
		self.rect=pygame.Rect(self.xloc,450,30,30)
		self.image=pygame.transform.rotate(self.image,self.angle)
	def movearrowup(self):
		self.rect.y-=1
	def drawarrow(self):
		screen.blit(self.image,self.rect)

class landingarrows(pygame.sprite.Sprite):
	def __init__(self,angle,xloc,typething):
		super(landingarrows,self).__init__()
		self.typething=typething
		self.xloc=xloc
		self.angle=angle
		self.image=pygame.image.load("landingarrows1.1.png")
		self.rect=pygame.Rect(self.xloc,50,30,30)
		self.image=pygame.transform.rotate(self.image,self.angle)
	def decideFill(self):
		if pressedtoolong[self.typething]>0 and pressedtoolong[self.typething]<240:
			self.image=pygame.image.load("arrows1.1.png")
			self.image=pygame.transform.rotate(self.image,self.angle)
		else:
			self.image=pygame.image.load("landingarrows1.1.png")
			self.rect=pygame.Rect(self.xloc,50,30,30)
			self.image=pygame.transform.rotate(self.image,self.angle)
	def drawlanding(self):
		screen.blit(self.image,self.rect)

class streakmeter(pygame.sprite.Sprite):
	def __init__(self,streak):
		super(streakmeter,self).__init__()
		self.rect1=pygame.Rect(550,450,40,0)
		self.rect2=pygame.Rect(550,250,40,200)
		self.rect3=pygame.Rect(550,250,40,100)
		self.streak=streak
		
		yheight=200-6.6667*self.streak
		self.rect2=pygame.Rect(550,250,40,yheight)
	def fillheight(self):
		self.rect1=pygame.Rect(550,450-200*self.streak/30,40,200*self.streak/30)
	def drawstreakmeter(self):
		if self.streak==0:
			pygame.draw.rect(screen,streak_color,(0,0,0,0))	
		else:
			pygame.draw.rect(screen,streak_color,(550,450-200*self.streak/30,40,200*self.streak/30))
		# pygame.draw.rect(screen,backgroundcolor,self.rect2)


def addArrows():
	if 0 in song_index_two[-1]:
		leftArrows.add(arrows(90,50))
	if 1 in song_index_two[-1]:
		upArrows.add(arrows(0,120))
	if 2 in song_index_two[-1]:
		downArrows.add(arrows(180,190))
	if 3 in song_index_two[-1]:
		rightArrows.add(arrows(270,260))

def arrowMover(streak,hitmiss):
	for i in upArrows:
		if counter%2==0:
			i.movearrowup()
		i.drawarrow()
		if i.rect.y<0:
			hitmiss=hitmissfont.render("Miss!",1,score_color)
			screen.blit(score_thing,(410,0))
			score_writer()
			screen.blit(hitmiss,(480,60))
			if streak>0:
				streak-=1
			upArrows.remove(i)
	for i in leftArrows:
		if counter%2==0:
			i.movearrowup()
		i.drawarrow()
		if i.rect.y<0:
			hitmiss=hitmissfont.render("Miss!",1,score_color)
			screen.blit(score_thing,(410,0))
			score_writer()
			screen.blit(hitmiss,(480,60))
			if streak>0:
				streak-=1
			leftArrows.remove(i)
	for i in rightArrows:
		if counter%2==0:
			i.movearrowup()
		i.drawarrow()
		if i.rect.y<0:
			hitmiss=hitmissfont.render("Miss!",1,score_color)
			screen.blit(score_thing,(410,0))
			score_writer()
			screen.blit(hitmiss,(480,60))
			if streak>0:
				streak-=1
			rightArrows.remove(i)
	for i in downArrows:
		if counter%2==0:
			i.movearrowup()
		i.drawarrow()
		if i.rect.y<0:
			hitmiss=hitmissfont.render("Miss!",1,score_color)
			screen.blit(score_thing,(410,0))
			score_writer()
			screen.blit(hitmiss,(480,60))
			if streak>0:
				streak-=1
			downArrows.remove(i)
	return streak,hitmiss

def keyReader(score,multiplier,streak,hitmiss):
	if pygame.key.get_pressed()[pygame.K_LEFT] and pressedtoolong[1]<10 and pressedtoolong[1] is not -1:
		pressedtoolong[1]+=1
		collidelist=pygame.sprite.spritecollide(leftLanding,leftArrows,True)
		for i in collidelist:
			if i.rect.y <55 and i.rect.y>45:
				score+=5*multiplier
				hitmiss=hitmissfont.render("Perfect!",1,score_color)
			elif i.rect.y <30 or i.rect.y >70:
				score+=1*multiplier
				hitmiss=hitmissfont.render("Poor!",1,score_color)
			else:
				score+=3*multiplier
				hitmiss=hitmissfont.render("Okay!",1,score_color)
			if streak<30:
				streak+=1
	elif not pygame.key.get_pressed()[pygame.K_LEFT]:
		pressedtoolong[1]=0
	else:
		pressedtoolong[1]=-1

	if pygame.key.get_pressed()[pygame.K_UP] and pressedtoolong[0]<10 and pressedtoolong[0] is not -1:
		pressedtoolong[0]+=1
		collidelist=pygame.sprite.spritecollide(upLanding,upArrows,True)
		for i in collidelist:
			if i.rect.y <55 and i.rect.y>45:
				score+=5*multiplier
				hitmiss=hitmissfont.render("Perfect!",1,score_color)
			elif i.rect.y <30 or i.rect.y >70:
				score+=1*multiplier
				hitmiss=hitmissfont.render("Poor!",1,score_color)
			else:
				score+=3*multiplier
				hitmiss=hitmissfont.render("Okay!",1,score_color)
			if streak<30:
				streak+=1
	elif not pygame.key.get_pressed()[pygame.K_UP]:
		pressedtoolong[0]=0
	else:
		pressedtoolong[0]=-1
	if pygame.key.get_pressed()[pygame.K_DOWN] and pressedtoolong[3]<10 and pressedtoolong[3] is not -1:
		pressedtoolong[3]+=1
		collidelist=pygame.sprite.spritecollide(downLanding,downArrows,True)
		for i in collidelist:
			if i.rect.y <55 and i.rect.y>45:
				score+=5*multiplier
				hitmiss=hitmissfont.render("Perfect!",1,score_color)
			elif i.rect.y <30 or i.rect.y >70:
				score+=1*multiplier
				hitmiss=hitmissfont.render("Poor!",1,score_color)
			else:
				score+=3*multiplier
				hitmiss=hitmissfont.render("Okay!",1,score_color)
			if streak<30:
				streak+=1
	elif not pygame.key.get_pressed()[pygame.K_DOWN]:
		pressedtoolong[3]=0
	else:
		pressedtoolong[3]=-1
	if pygame.key.get_pressed()[pygame.K_RIGHT] and pressedtoolong[2]<10 and pressedtoolong[2] is not -1:
		pressedtoolong[2]+=1
		collidelist=pygame.sprite.spritecollide(rightLanding,rightArrows,True)
		for i in collidelist:
			if i.rect.y <55 and i.rect.y>45:
				score+=5*multiplier
				hitmiss=hitmissfont.render("Perfect!",1,score_color)
			elif i.rect.y <30 or i.rect.y >70:
				score+=1*multiplier
				hitmiss=hitmissfont.render("Poor!",1,score_color)
			else:
				score+=3*multiplier
				hitmiss=hitmissfont.render("Okay!",1,score_color)
			if streak<30:
				streak+=1
	elif not pygame.key.get_pressed()[pygame.K_RIGHT]:
		pressedtoolong[2]=0
	else:
		pressedtoolong[2]=-1
	return score,multiplier,streak,hitmiss

def randsong():
	for i in range(20000):
		songindex.append([])
		if i%200==0:
			randchoice=random.randint(0,5)
			if randchoice==0:
				randy_songindex[i].append(0)
			if randchoice==1:
				randy_songindex[i].append(1)
			if randchoice==2:
				randy_songindex[i].append(2)
			if randchoice==3:
				randy_songindex[i].append(3)
			if randchoice==4:
				randy_songindex[i].append(1)
				randy_songindex[i].append(2)
			if randchoice==5:
				randy_songindex[i].append(0)
				randy_songindex[i].append(3)

def score_writer():
	score_string=str(score)
	while len(score_string)<7:
		score_string="0"+score_string
	if len(score_string)==7:
		score1_label=myfont.render(score_string[6],1,score_color)
		score10_label=myfont.render(score_string[5],1,score_color)
		score100_label=myfont.render(score_string[4],1,score_color)
		score1000_label=myfont.render(score_string[3],1,score_color)
		score10000_label=myfont.render(score_string[2],1,score_color)
		score100000_label=myfont.render(score_string[1],1,score_color)
		score1000000_label=myfont.render(score_string[0],1,score_color)
	screen.blit(score1_label,(610,0))
	screen.blit(score10_label,(580,0))
	screen.blit(score100_label,(550,0))
	screen.blit(score1000_label,(520,0))
	screen.blit(score10000_label,(490,0))
	screen.blit(score100000_label,(460,0))
	screen.blit(score1000000_label,(430,0))

# Group Maker #
upArrows=pygame.sprite.Group()
downArrows=pygame.sprite.Group()
leftArrows=pygame.sprite.Group()
rightArrows=pygame.sprite.Group()

# Group Initialization 
leftLanding=landingarrows(90,50,1)
upLanding=landingarrows(0,120,0)
downLanding=landingarrows(180,190,3)
rightLanding=landingarrows(270,260,2)













## GAME ##
## CODE ##

## START SCREEN ##
screen.fill(backgroundcolor)
pygame.draw.rect(screen,streak_color,(200,300,240,100))
start_label=myfont.render("START!",1,score_color)
screen.blit(title_label,(40,100))
screen.blit(start_label,(250,325))
pygame.display.flip()
while title_screen:
	for event in pygame.event.get():
		if event.type == pygame.MOUSEBUTTONDOWN:
				# Set the x, y postions of the mouse click
				x, y = event.pos
				if x>200 and x<440 and y>300 and y<400:
					title_screen=False
		if event.type == pygame.QUIT:
			done = True
			title_screen=False



if not done:
	fs,new_list=song_maker() # Song Maker Function

	# Runs the Random Song Function if the user wants a random song
	if make_random_song==True:
		randsong()

start_time=pygame.time.get_ticks() # Checks the time at this point in the code for later use
screen.fill(backgroundcolor) #Fills background obviously.
while not done:
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
					done = True

	## MUSIC STARTER ##
	# Begins to play the music after the while loop has run 
	# 430 times. This is because it takes loops for the arrows
	# to reach the landing arrows.
	if counter==430:
		pygame.mixer.music.play(0)

	streak_cmp[0]=streak
	score_cmp[0]=score
	

	## ELAPSED TIME CHECKER ##
	elapsed_time=pygame.time.get_ticks()-start_time # Checks the elapsed time and uses this to spawn stuff
	sample_position=fs*elapsed_time/1000 # Finds the position in the index based on the time of the song

	## BUTTON ADDER ##
	song_index_two.append([]) # Adds blank list
	if new_list:
		if sample_position>min(new_list): # Fills list if the program has passed an index
			new_list.remove(min(new_list)) # Removes the value it's adding too
			randchoice=random.randint(0,5)
			if randchoice==0:
				song_index_two[-1].append(0)
			if randchoice==1:
				song_index_two[-1].append(1)
			if randchoice==2:
				song_index_two[-1].append(2)
			if randchoice==3:
				song_index_two[-1].append(3)
			if randchoice==4:
				song_index_two[-1].append(1)
				song_index_two[-1].append(2)
			if randchoice==5:
				song_index_two[-1].append(0)
				song_index_two[-1].append(3)


	pygame.draw.rect(screen,backgroundcolor,(0,0,330,480))
	addArrows()
	streak,hitmiss=arrowMover(streak,hitmiss)
	#pygame.draw.rect(screen,backgroundcolor,(320,50,320,50))
	score,multiplier,streak,hitmiss=keyReader(score,multiplier,streak,hitmiss)	
	upLanding.decideFill()
	downLanding.decideFill()
	leftLanding.decideFill()
	rightLanding.decideFill()
	upLanding.drawlanding()
	downLanding.drawlanding()
	leftLanding.drawlanding()
	rightLanding.drawlanding()

	streak_cmp[1]=streak
	score_cmp[1]=score

	if score_cmp[0]!=score_cmp[1]:
		#pygame.draw.rect(screen,backgroundcolor,(320,0,320,50))
		screen.blit(score_thing,(410,0))
		score_writer()
		screen.blit(hitmiss,(480,60))

	if streak_cmp[0]!=streak_cmp[1]:
		pygame.draw.rect(screen,backgroundcolor,(320,240,320,240))
		streakmeter(streak).fillheight()
		streakmeter(streak).drawstreakmeter()
	# screen.blit(score_thing,(410,0))
	

	counter+=1
	pygame.draw.rect(screen,backgroundcolor,(410,200,240,100))
	pos="(" + str(pygame.mouse.get_pos()[0])+","+str(pygame.mouse.get_pos()[1])+")"
	pos_label=myfont.render(pos,1,score_color)
	screen.blit(pos_label,(400,200))

	if streak<=streak1:
		multiplier=1
		multiplier_label=multiplierfont.render("x1",1,score_color)
		screen.blit(multiplier_label,(550,450))
	elif streak<=streak2:
		multiplier=2
		multiplier_label=multiplierfont.render("x2",1,score_color)
		screen.blit(multiplier_label,(550,450))
	else:
		multiplier=3
		multiplier_label=multiplierfont.render("x3",1,score_color)
		screen.blit(multiplier_label,(550,450))

	pygame.display.flip()
	#clock.tick(60)
	(clock.tick(480))



