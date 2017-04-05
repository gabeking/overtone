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



// screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool loadMedia();

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

SDL_Rect gSpriteClips[4];
std::vector<texture> gSpriteSheetTextures;

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

int main( int argc, char* args[] )
{
	
	/*
	* Create .txt files for note class
	* This python program will output
	* two .txt files, notes.txt
	* and times.txt.
	*/
	string SONGNAME = "allstar.mp3";	//Name of song that user wishes to use
	/* TODO: ALLOW USER TO CHOOSE SONG */
	string chmod_var = "chmod +x ../songfiles/notetimefiles.py";	
	string process_var = "python ../songfiles/notetimefiles.py ../songfiles/" + SONGNAME;	

	system(chmod_var.c_str());	//Gives program permission to run python file
	system(process_var.c_str());	//Processes python file
	
	
	/*
	 * This will intitialize the note class as a vector of class notes
	 */
	vector<note> song_notes;
	vector<double> time_vec;
	vector<double> freq_vec;
	string input_string; 
	
	//Takes the numbers from the times.txt and 
	//inputs them into a vector
	ifstream timefile("../songfiles/times.txt");
    while (std::getline(timefile, input_string))
    {
        time_vec.push_back(stod(input_string));
    }
    
    //Takes the numbers from the notes.txt and
    //inputs them into a vector
    ifstream freqfile("../songfiles/notes.txt"); 
    while (std::getline(freqfile, input_string))
    {
        freq_vec.push_back(stod(input_string));

    }
    
    //Pushes the times and frequencies into a vector of note classes.
    for (unsigned int counter = 0; counter < freq_vec.size() && counter < time_vec.size(); ++counter){
		note new_note(freq_vec[counter], time_vec[counter]);
		song_notes.push_back(new_note);
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

                // Render dot_test sprite
                gSpriteSheetTextures[1].render( SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

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
