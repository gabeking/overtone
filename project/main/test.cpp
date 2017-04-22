//Necessary Includes
#include <SDL2/SDL.h>			//Main SDL header
#include <SDL2/SDL_image.h>		//SDL image loading/moving
#include <SDL2/SDL_ttf.h>		//SDL text placement
#include <SDL2/SDL_mixer.h>		//SDL Music Player
#include <stdio.h>				//standard input/output / filestreams
#include <string>				//C++ string library
#include <vector>				//C++ vector library
#include <fstream>				//File i/o
#include <stdlib.h>				//C general utilities (rand, atoi, etc.)
#include <iostream>				//cin, cout, etc
using namespace std;			//STL namespace

#include "texture.h"			//Sets textures to objects
#include "sdlTools.h"			//SDL utilities
#include "note.h"				//Holds note class for enemy spawning
#include "sprite.h"				//For general movement, spawning, etc
#include "player.h"				//Player specific object code

//Function prototypes
vector<note> set_up_music_adt();		//Takes txt files and converts them
										//to note class

//Global Variables
string PROGRAM_NAME;	//Holds program name, for usage

int SCORE = 0;

int DIFFICULTY = 2; 		//Game Difficulty (1: "easy", 2: "medium", or 3: "hard")

string SONGNAME = "one";	//Name of song that user wishes to use
							//will be one, two, or three

void usage(int status) {	//Prints if '-h' argument is used
	cout << "Usage: ./" << PROGRAM_NAME << "DIFFICULTY SONGFILE" << endl;
	cout << "DIFFICULTY can be 1, 2, or 3" << endl;
	cout << "SONGFILE can be one, two, or three" << endl;
    exit(status);
}




// screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Necessary implementation variables for SDL
bool loadMedia();

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

TTF_Font *gFont = NULL;

texture gTextTexture;

Mix_Music *gMusic = NULL;

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

SDL_Rect playerSpriteClips[1];
SDL_Rect gSpriteClip[4];
std::vector<SDL_Rect*> gSpriteClips;
std::vector<texture> gSpriteSheetTextures;

bool loadMedia();   // loads files for sprite textures

//Main function
int main( int argc, char* argv[] )
{
	//Command line argument parsing
	int argind = 1;
    PROGRAM_NAME = argv[0];
    while (argind < argc) {
        char* arg = argv[argind++];
		if (strcmp(arg, "-h")==0){
			usage(0);
		}
    	if (argind == 2){	//Checks user-inputted DIFFICULTY
			if (strcmp(arg, "1")==0 || strcmp(arg, "2")==0 || strcmp(arg, "3")==0){
				DIFFICULTY = atoi(arg);
			}else{
				cout << "DIFFICULTY input not understood, defaulting to medium." << endl;
			}
		}
		if (argind == 3){	//Checks user-inputted SONGNAME
			if (strcmp(arg, "one")==0 || strcmp(arg, "two")==0 || strcmp(arg, "three")==0){
				SONGNAME = arg;
			}else{
				cout << "SONGNAME input not understood, defaulting to one." << endl;
			}
		}
    }
	cout << "DIFFICULTY is: " << DIFFICULTY << endl;
	cout << "SONGNAME is: " << SONGNAME << endl;	

	srand (time(NULL));		//Seeds random number generator

	
	vector<note> song_notes = set_up_music_adt();		//Calls adt generation
	
	
    //Start up SDL and create window
    if( !init(gWindow, gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT) )
    {   
        printf( "Failed to initialize!\n" );
    }
    else
    {   
        texture texture0;

        gSpriteSheetTextures.push_back(texture0);
        gSpriteSheetTextures.push_back(texture0);

        //Load media
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            // Initialize fps cap timer
            SDLTimer capTimer;

            //Initialize player
            player Player(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 
            SCREEN_WIDTH, SCREEN_HEIGHT, &gSpriteSheetTextures[0]);
            Player.setClips(gSpriteClips);
            
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

			

            
            //While application is running
            while( !quit )
            {
                /* TODO: Make animation counter */
                
                // start cap timer
                capTimer.start();

                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 ) 
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                }

                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );

                // Handle player sprite
                Player.update();
                Player.render();

                //Render top left sprite
                //gSpriteSheetTextures[0].render( 0, 0, &gSpriteClips[ 0 ] );

                //Render top right sprite
                //gSpriteSheetTextures[0].render( SCREEN_WIDTH - gSpriteClips[ 1 ].w, 0, &gSpriteClips[ 1 ] );

                //Render bottom left sprite
                //gSpriteSheetTextures[0].render( 0, SCREEN_HEIGHT - gSpriteClips[ 2 ].h, &gSpriteClips[ 2 ] );

                //Render bottom right sprite
                //gSpriteSheetTextures[0].render( SCREEN_WIDTH - gSpriteClips[ 3 ].w, SCREEN_HEIGHT - gSpriteClips[ 3 ].h, &gSpriteClips[ 3 ] );
				if( Mix_PlayingMusic() == 0 ) { 
					Mix_PlayMusic( gMusic, -1 ); 
				}	

				gTextTexture.render( 20, 20);				

                //Update screen
                SDL_RenderPresent( gRenderer );

                // if frame finished early
                Uint32 frameTicks = capTimer.getTicks();
                if (frameTicks < SCREEN_TICKS_PER_FRAME) {
                    // wait remaining time
                    SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks);
                }
            }
        }
    }
	
	// Free resources and close SDL
    close(gMusic, gFont, gWindow, gRenderer, gSpriteSheetTextures);
	Mix_HaltMusic();
    return 0;
}

bool loadMedia()
	{
    //Loading success flag
    bool success = true;

    //Load sprite sheet texture
    if( !gSpriteSheetTextures[0].loadFromFile( "./dots.png" ) )
    {
        printf( "Failed to load sprite sheet texture!\n" );
        success = false;
    }
    else
    {
        //Set top left sprite
        gSpriteClip[0].x =   0;
        gSpriteClip[0].y =   0;
        gSpriteClip[0].w = 100;
        gSpriteClip[0].h = 100;
        gSpriteClips.push_back(&gSpriteClip[0]);

        //Set top right sprite
        gSpriteClip[1].x = 100;
        gSpriteClip[1].y =   0;
        gSpriteClip[1].w = 100;
        gSpriteClip[1].h = 100;
        //gSpriteClips.push_back(&gSpriteClip[1]);
 
        //Set bottom left sprite
        gSpriteClip[2].x =   0;
        gSpriteClip[2].y = 100;
        gSpriteClip[2].w = 100;
        gSpriteClip[2].h = 100;
        //gSpriteClips.push_back(&gSpriteClip[2]);

        //Set bottom right sprite
        gSpriteClip[3].x = 100;
        gSpriteClip[3].y = 100;
        gSpriteClip[3].w = 100;
        gSpriteClip[3].h = 100;
        //gSpriteClips.push_back(&gSpriteClip[3]);
    }
    
    // Load second test object
    if( !gSpriteSheetTextures[1].loadFromFile( "./dot_test.png" ) )
    {
        printf( "Failed to load sprite sheet texture!\n" );
        success = false;
    }

	//Open the font 
	gFont = TTF_OpenFont( "fonts/zekton.ttf", 28 ); 
	if( gFont == NULL ) { 
		printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() ); 
		success = false; 
	} else { //Render text SDL_Color 
		SDL_Color textColor = { 0, 0, 0 }; 
		if( !gTextTexture.loadFromRenderedText(gFont, "0010", textColor ) ) { 
			printf( "Failed to render text texture!\n" ); 
			success = false; 
		} 
	}
	
	//Load music 
	SONGNAME = "./songfiles/" + SONGNAME;
	gMusic = Mix_LoadMUS( SONGNAME.c_str() ); 
	if( gMusic == NULL ) { 
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() ); 
		success = false; 
	}

    return success;
}


vector<note> set_up_music_adt(){
	
	/*
	 * This will intitialize the note class as a vector of class notes
	 */
	vector<note> total_notes;
	vector<note> song_notes;
	vector<double> time_vec;
	vector<double> freq_vec;
	string input_string; 
	
	//Takes the numbers from the times.txt and 
	//inputs them into a vector
	string timefilename = "./songfiles/" + SONGNAME + "time.txt";
	ifstream timefile(timefilename);
    while (std::getline(timefile, input_string))
    {
        time_vec.push_back(stod(input_string));
    }
    
    //Takes the numbers from the notes.txt and
    //inputs them into a vector
    string freqfilename = "./songfiles/" + SONGNAME + "note.txt";
	ifstream freqfile(freqfilename);
    while (std::getline(freqfile, input_string))
    {
        freq_vec.push_back(stod(input_string));

    }
    
    //Pushes the times and frequencies into a vector of note classes.
    for (unsigned int counter = 0; counter < freq_vec.size() && counter < time_vec.size(); ++counter){
		note new_note(SCREEN_HEIGHT, freq_vec[counter], time_vec[counter]);
		total_notes.push_back(new_note);
	}
	//second and second_increment are used to 
	//take out a certain amount of notes from the total_notes vector
	double second;
	double second_increment;
	double songLength = total_notes.back().getOnset();
	
	//This changes that amount of enemies that will be spawned
	//based on the difficulty
	switch (DIFFICULTY) {
		case 1:
			second = 3;
			second_increment = 3;
			break;
		case 2:
			second = 2;
			second_increment = 2;
			break;
		case 3:
			second = 1;
			second_increment = 1;
			break;
		default:
			second = 3;
			second_increment = 3;
			break;
	}

	//lower_size and upper_size will keep the range from which
	//the note will be drawn
	int lower_size = 0;
	int upper_size = 0;
	int note_to_choose = 0;
	
	//This for loop takes one note, at random, in every 1, 2, or 3 
	//second range
	for (unsigned int counter = 0; counter < total_notes.size(); ++counter){
		if (total_notes[counter].getOnset() > second){
			int modulo = upper_size-lower_size;
			note_to_choose = rand() % modulo + lower_size - 1;
			song_notes.push_back(total_notes[note_to_choose]);
			second+=second_increment;
			lower_size=upper_size;
		}
		upper_size++;
	}

	return song_notes;
}
