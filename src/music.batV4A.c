/*Music.bat*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//#define DEBUG

#define STARTABLE 1							/*these three macros are for getformat*/
#define CUSTOM 2
#define BADFORMAT 0

#define MUSICBAT_VER "test ver. 4a (1)"			/*needed for printing ver. no.*/

void die ( char * );			/*prints a message and closes the program*/
int get_format ( char * );		/*returns 1 or 2 depending on the method used to open link or 0 if wrong format*/
void play_music ( char *, int );/*plays the music*/
bool check_custom ( char * );	/*checks if the string is a custom name defined by user*/		

int main ( int argc, char * argv[] ) {
	
	#ifndef DEBUG
		system ("@echo off");
	#endif
	
	int delay = 0, type;/*delay is delay before playing song in minutes*/
						/*type is type of link, using the 3 macros at the top*/
	printf ( "Music.bat version <" MUSICBAT_VER ">\n" );
	
	switch ( argc ) {
		case 1:			/*no command line arguments*/
				
				printf ("ui to be implemented...\n");
				return 0;/*to be implemented...*/
				
		default :		/*has command line arguments, no mode selection. only playing music after delay.*/
			if ( ! ( type = get_format ( argv[1] ) ) )
				die ( "wrong link format. music.bat only accepts mp3 files, youtube"
					  " links or custom names for youtube links you have set." );
			
			delay = atoi ( argv[2] );
			
			play_music ( argv [1], delay );
	}
}

/*determines how to open the link/file in the string*/
int get_format ( char * subject ) {
	if ( strstr ( subject, "mp3" ) || strstr (subject, "youtube.com/w" ) )
		return STARTABLE;
	else if ( check_custom ( subject ) )
		return CUSTOM;
	return BADFORMAT;	
}

/*Plays the music after a set delay*/
void play_music ( char *link, int delay ) {
	char ixy_[24] = "\0";	/*  length for ixy_ is 10+4+9+1, 10 for "timeout /t ", 4  for the delay,      */
	char ity[59] = "\0"; 	/*  9 for " /nobreak" and 1 for '\0' . legth for ity is 6+52, 6 for "start "  */
							/*  and 52, which is the length of a youtube link, the longest thing accepted.*/
	
	if ( strlen ( link ) > 52 )
		die ( "link is too long. max link length is 52 characters." );
	if ( strlen (link ) < 2 )
		die ( "Link is too smalley");
	if ( delay > 1440 || delay < 0 )
		die ( "invalid delay. delay can be between 0 and 1440 minutes." );
	
	snprintf ( ixy_, 23, "timeout /T %d /nobreak", delay*60 );
	snprintf ( ity, 58, "start %s", link );
	system (ixy_);
	
	system ( ity );
	exit ( 0 );	
}

/*checks if the string is a custom name*/
bool check_custom ( char * subject ) { /*to be implemented...*/
	return false;
}

/*prints a message and closes the program*/
void die ( char * str ) {
	fprintf ( stderr, str );
	exit ( 0 );
}
