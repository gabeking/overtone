#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <iostream>
using namespace std;

#include "texture.h"
#include "sdlTools.h"
#include "note.h"
#include "sprite.h"
#include "player.h"

//Game Difficulty (1: "easy", 2: "medium", or 3: "hard")
int DIFFICULTY = 3;

string SONGNAME = "one";	//Name of song that user wishes to use
							//will be one, two, or three

// screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool loadMedia();

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

SDL_Rect gSpriteClips[4];
std::vector<texture> gSpriteSheetTextures;

bool loadMedia();   // loads files for sprite textures


int main( int argc, char* args[] )
{
	
	srand (time(NULL));

	/*
	* Create .txt files for note class
	* This python program will output
	* two .txt files, notes.txt
	* and times.txt.
	*/
	
	
	
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
	string timefilename = "../songfiles/" + SONGNAME + "time.txt";
	ifstream timefile(timefilename);
    while (std::getline(timefile, input_string))
    {
        time_vec.push_back(stod(input_string));
    }
    
    //Takes the numbers from the notes.txt and
    //inputs them into a vector
    string freqfilename = "../songfiles/" + SONGNAME + "note.txt";
	ifstream freqfile(freqfilename);
    while (std::getline(freqfile, input_string))
    {
        freq_vec.push_back(stod(input_string));

    }
    
    //Pushes the times and frequencies into a vector of note classes.
    for (unsigned int counter = 0; counter < freq_vec.size() && counter < time_vec.size(); ++counter){
		note new_note(freq_vec[counter], time_vec[counter]);
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
            //Initialize player
            player Player(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 
            &gSpriteSheetTextures[1]);
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;
            
            //While application is running
            while( !quit )
            {
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
                gSpriteSheetTextures[0].render( 0, 0, &gSpriteClips[ 0 ] );

                //Render top right sprite
                gSpriteSheetTextures[0].render( SCREEN_WIDTH - gSpriteClips[ 1 ].w, 0, &gSpriteClips[ 1 ] );

                //Render bottom left sprite
                gSpriteSheetTextures[0].render( 0, SCREEN_HEIGHT - gSpriteClips[ 2 ].h, &gSpriteClips[ 2 ] );

                //Render bottom right sprite
                gSpriteSheetTextures[0].render( SCREEN_WIDTH - gSpriteClips[ 3 ].w, SCREEN_HEIGHT - gSpriteClips[ 3 ].h, &gSpriteClips[ 3 ] );

                //Update screen
                SDL_RenderPresent( gRenderer );
            }
        }
    }
	
	// Free resources and close SDL
    close(gWindow, gRenderer, gSpriteSheetTextures);
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
        gSpriteClips[ 0 ].x =   0;
        gSpriteClips[ 0 ].y =   0;
        gSpriteClips[ 0 ].w = 100;
        gSpriteClips[ 0 ].h = 100;

        //Set top right sprite
        gSpriteClips[ 1 ].x = 100;
        gSpriteClips[ 1 ].y =   0;
        gSpriteClips[ 1 ].w = 100;
        gSpriteClips[ 1 ].h = 100;
 
        //Set bottom left sprite
        gSpriteClips[ 2 ].x =   0;
        gSpriteClips[ 2 ].y = 100;
        gSpriteClips[ 2 ].w = 100;
        gSpriteClips[ 2 ].h = 100;

        //Set bottom right sprite
        gSpriteClips[ 3 ].x = 100;
        gSpriteClips[ 3 ].y = 100;
        gSpriteClips[ 3 ].w = 100;
        gSpriteClips[ 3 ].h = 100;
    }
    
    // Load second test object
    if( !gSpriteSheetTextures[1].loadFromFile( "./dot_test.png" ) )
    {
        printf( "Failed to load sprite sheet texture!\n" );
        success = false;
    }

    return success;
}
