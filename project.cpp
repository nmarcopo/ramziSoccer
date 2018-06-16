// Nicholas Marcopoli
// Sung Hyun Shin
// Fundamentals of Computing Lab - Section 01
// 12-12-2017
// Final Project - Ramzi's (Insert Soccer Joke Here)

#include "gfxnew.h"
#include <unistd.h>
#include <cmath>
#include <stdlib.h>
using namespace std;

void menu_waiting();
void draw_menu(int, int);
void disp_instructions();
void play_level1();
void play_level2(int);
void play_level3(int);
void level4_animation(int,int, int, int, int, double, int, int, int, int, int, int, int, double);
void play_level4(int);
void updates(double, double, double &, double &, int &, int &, int &, double, double &);
void after_shot(double &,double &,int,int,int,int,bool &,double,int,double);
void after_shot2(double &,double &,int,int,int,int,bool &,double,int,double);
void draw_game(int,double,int,int,int,int,int,int,int);
void draw_game2(int,double,int,int,int,int,int,int,int);
void left_arrow(double &);
void right_arrow(double &);
void up_arrow(int &);
void down_arrow(int &);
void draw_lives(int);
void draw_goal();
void draw_goalkeeper(int, int);
void draw_biggoalkeeper(int, int);
void draw_eyecandy();
void draw_arrow(int,double,int,int);
void wait_quit(char []);

int main(){
	
	const int x_window = 600, y_window = 600;
	
	gfx_open(x_window, y_window, "Ramzi's Soccer Shooter");
	menu_waiting();
	
	return 0;
}

void menu_waiting(){
	
	// choice is 0 for no action, 1 for play, and 2 for instructions
	bool exit = false;
	while(!exit){
		draw_menu(gfx_windowwidth(), gfx_windowheight());
		// wait for keypress
		if(gfx_event_waiting()!=0){
			switch(gfx_wait()){
				case 'p':
                    play_level1();
					break;
				case 'i':
					disp_instructions();
					break;
                case 'x':
                    return;
				default:
					break;
			}
		}
	}

	return;
	
}

void disp_instructions(){
	gfx_clear();
	char font[] = "8x16";
    // different y separations for new line and continuing line on next line
	int text_pos = 10, newline = 30, sameline = 15;
	
	gfx_changefont(font);
	
	gfx_text(10,text_pos+=newline,"Welcome to Ramzi's Soccer Shooter!");
	gfx_text(10,text_pos+=newline,"In this game, you play as a the famous futbol star, Ramzi Bulalalalan,");
	gfx_text(10,text_pos+=sameline,"trying to score on Madrid.");
	gfx_text(10,text_pos+=newline,"Press the left and right arrow keys to change the direction of your kick.");
	gfx_text(10,text_pos+=newline,"Press the up and down arrow keys to change the power of your shot.");
	gfx_text(10,text_pos+=newline,"Finally, press the spacebar to shoot!");
	gfx_text(10,text_pos+=newline,"You have six tries to score on Real Madrid. Each time you score,");
	gfx_text(10,text_pos+=sameline,"the game gets harder!");
	gfx_text(10,text_pos+=newline,"There are four levels total. On the last level, get ready for a surprise!");
	gfx_text(10,text_pos+=newline,"Have fun, and good luck!");
	gfx_text(10,text_pos+=newline,"Also - don't change the window size please!");
	gfx_text(10,text_pos+=newline,"-- Nick and Andy");
	
    char text[] = "Press 'q' to quit";
	wait_quit(text);
	gfx_clear();
	return;
}

void draw_menu(int x, int y){
	
	char titlefont[] = "12x24";
	char title[] = "Ramzi's Soccer Shooter";
	
	gfx_changefont(titlefont);
	
	// Place title in center of screen
	int text_x = (gfx_windowwidth() / 2) - (gfx_textpixelwidth(title, titlefont) / 2);
	int text_y = (gfx_windowheight() / 2) + (gfx_textpixelheight(title, titlefont) / 2);
	gfx_text(text_x, text_y, title);
	
	// Place Subtitle
	char subtitlefont[] = "6x12";
	char subtitle[] = "Created by Sung Hyun Shin and Nicholas Marcopoli"; 
	
	gfx_changefont(subtitlefont);
	text_x = (gfx_windowwidth() / 2) - (gfx_textpixelwidth(subtitle, subtitlefont) / 2);
	text_y = (gfx_windowheight() / 1.9) + (gfx_textpixelheight(subtitle, subtitlefont) / 2);
	gfx_text(text_x, text_y, subtitle);

	// Place Options text
	char optionsfont[] = "6x12";
	char play[] = "Press 'p' to play!", instructions[] = "Press 'i' for instructions!";
	char quit[] = "Press 'x' to quit!";
	
	// place play
	gfx_changefont(optionsfont);
	text_x = (gfx_windowwidth() / 2) - (gfx_textpixelwidth(play, optionsfont) / 2);
	text_y = (gfx_windowheight() / 1.5) + (gfx_textpixelheight(play, optionsfont) / 2);
	gfx_text(text_x, text_y, play);
	
	// place instructions
	text_x = (gfx_windowwidth() / 2) - (gfx_textpixelwidth(instructions, optionsfont) / 2);
	text_y = (gfx_windowheight() / 1.45) + (gfx_textpixelheight(instructions, optionsfont) / 2);
	gfx_text(text_x, text_y, instructions);
	
	// place quit
	text_x = (gfx_windowwidth() / 2) - (gfx_textpixelwidth(quit, optionsfont) / 2);
	text_y = (gfx_windowheight() / 1.41) + (gfx_textpixelheight(quit, optionsfont) / 2);
	gfx_text(text_x, text_y, quit);
	
    gfx_flush();
    
}

void play_level1(){
    int goalkx, goalky;
    int ballShootRad, ballx, bally;
    int lives = 6;
    double ballShootAng;
    bool scored = false;
    double gkdx;
    char c;
    bool shot = false;
    bool ballyGoal, ballxGoal;
    double balldx, balldy;
    double ballxTemp, ballyTemp;
    double goalkxTemp;
    int ballxInit, ballyInit;
    bool missed = false;
    bool stopped = false;
    gkdx = 1;
    balldx = 0;
    balldy = 0;
    goalkxTemp = 300;
    ballx = 300;
    ballxInit = ballx;
    bally = 500;
    ballyInit = bally;
    ballxTemp = ballx;
    ballyTemp = bally;
    goalkx = 300;
    goalky = 110;
    ballShootRad = 50;
    ballShootAng = M_PI/2;

    // Functionality while in game
    while(lives>=1 && !scored){
        gfx_clear();
        draw_game(ballShootRad,ballShootAng,goalkx,goalky,ballx,bally,lives,ballxInit,ballyInit);
        gfx_flush();
        usleep(10000);
        
        if(gfx_event_waiting()&&!shot){
            c = gfx_wait();
            
            if(c == 32){ //space
                shot = true;   
                balldx = 1.3*(ballShootRad+25)/50*cos(-1*ballShootAng+M_PI);
            }
            
            if(c == 81){ //left arrow
                left_arrow(ballShootAng);
            }
            
            else if(c == 83){ //right arrow
                right_arrow(ballShootAng);
            }
            
            else if(c == 82){ //up arrow
                up_arrow(ballShootRad);
            }
            
            else if(c == 84){ //down arrow
                down_arrow(ballShootRad);
            }
        }
        
        // After ball is shot, call this function to check if shot was good or not
        if(shot == true){
            after_shot(balldx,balldy,bally,ballx,goalky,goalkx,stopped,gkdx,ballShootRad,ballShootAng);
        }
       
        // Switch goalkeeper velocity when reaches the edge
        if(goalkx <= 230){
            gkdx = -1*gkdx;
        }
        
        if(goalkx >= 370){
            gkdx = -1*gkdx;
        }
        
        // display updated screen after calculations
        updates(balldx,balldy,ballxTemp,ballyTemp,ballx,bally,goalkx,gkdx,goalkxTemp);
        
        // conditions of scoring
        ballyGoal = (bally+22 <=100);
        ballxGoal = (ballx >=210 && ballx <= 390);
        
        if(ballyGoal&&ballxGoal){
            scored = true;
        }   
        
        // conditions of missing
        missed = (ballx<=55 && bally>=105)||(ballx>=545 && bally>=105)||(bally<=105 && ballx<=200)||(bally<=105 && ballx>=400);

        if((missed||stopped)&&!((bally<=100)&&(ballx>=210)&&(ballx<=390))){
            // reset all values and lose a life
            lives -=1;
            ballx = 300;
            bally = 500;
            ballxTemp = 300;
            ballyTemp = 500;
            balldx = 0;
            balldy = 0;
            shot = false;
            ballShootRad = 50;
            ballShootAng = M_PI/2;
            if(lives > 0){
                char text[] = "Press 'q' to try again";
                wait_quit(text);
                stopped = false;
            }
        }
    }

    // If the shot was good, display a message and allow player to advance to next level
    if(scored&&lives>=1){
        char text[] = "Press 'q' to go to next level";
        wait_quit(text);
        gfx_clear();
        play_level2(lives);
    }

    // If player lost all lives, return to the menu
    if(lives == 0){
        char text1[] = "Game Over! Press 'q' to go back to the menu";
        wait_quit(text1);
        gfx_clear();
    }
}

void play_level2(int lives){
    int goalkx, goalky;
    int ballShootRad, ballx, bally;
    double ballShootAng;
    bool scored = false;
    double gkdx;
    char c;
    bool shot = false;
    bool ballyGoal, ballxGoal;
    double balldx, balldy;
    double ballxTemp, ballyTemp;
    int ballxInit, ballyInit;
    double goalkxTemp;
    bool missed = false;
    bool stopped = false;
    gkdx = 2;
    balldx = 0;
    balldy = 0;
    goalkxTemp = 300;
    ballx = 300;
    ballxInit = ballx;
    bally = 500;
    ballyInit = bally;
    ballxTemp = ballx;
    ballyTemp = bally;
    goalkx = 300;
    goalky = 110;
    ballShootRad = 50;
    ballShootAng = M_PI/2;

    // In game functionality
    while(lives>=1 && !scored){
        gfx_clear();
        draw_game(ballShootRad,ballShootAng,goalkx,goalky,ballx,bally,lives,ballxInit,ballyInit);
        gfx_flush();
        usleep(10000);
        
        if(gfx_event_waiting()&&!shot){
            c = gfx_wait();
            
            if(c == 32){ //space
                shot = true;   
                balldx = 1.3*(ballShootRad+25)/50*cos(-1*ballShootAng+M_PI);
            }
            
            if(c == 81){ //left arrow
                left_arrow(ballShootAng);
            }
            
            else if(c == 83){ //right arrow
                right_arrow(ballShootAng);
            }
            
            else if(c == 82){ //up arrow
                up_arrow(ballShootRad);
            }
            
            else if(c == 84){ //down arrow
                down_arrow(ballShootRad);
            }
        }
        
        // Checks positions of all objects and calculates new positions
        if(shot == true){
            after_shot(balldx,balldy,bally,ballx,goalky,goalkx,stopped,gkdx,ballShootRad,ballShootAng);
        }
        
        // Moves backwards if hit the edge
        if(goalkx <= 230){
            gkdx = -1*gkdx;
        }
        
        if(goalkx >= 370){
            gkdx = -1*gkdx;
        }
        
        // Draws new game positions
        updates(balldx,balldy,ballxTemp,ballyTemp,ballx,bally,goalkx,gkdx,goalkxTemp);
        
        // conditions of scoring
        ballyGoal = (bally+22 <=100);
        ballxGoal = (ballx >=210 && ballx <= 390);
        
        if(ballyGoal&&ballxGoal){
            scored = true;
        }   
        
        // conditions of missing
        missed = (ballx<=55 && bally>=105)||(ballx>=545 && bally>=105)||(bally<=105 && ballx<=200)||(bally<=105 && ballx>=400);

        if((missed||stopped)&&!((bally<=100)&&(ballx>=210)&&(ballx<=390))){
            // reset all values and lose a life
            lives -=1;
            ballx = 300;
            bally = 500;
            ballxTemp = 300;
            ballyTemp = 500;
            balldx = 0;
            balldy = 0;
            shot = false;
            ballShootRad = 50;
            ballShootAng = M_PI/2;
            if(lives > 0){
                char text[] = "Press 'q' to try again";
                wait_quit(text);
                stopped = false;
            }
        }
    }

    // If the ball goes in, prompts user to advance to next level
    if(scored&&lives>=1){
        char text[] = "Press 'q' to go to next level";
        wait_quit(text);
        gfx_clear();
        play_level3(lives);
    }

    // If the user is out of lives, returns them to the menu
    if(lives == 0){
        char text1[] = "Game Over! Press 'q' to go back to the menu";
        wait_quit(text1);
        gfx_clear();
    }
}

void play_level3(int lives){
    int goalkx, goalky;
    int goalkx2, goalky2;
    int goalkx3, goalky3;
    int ballShootRad, ballx, bally;
    double ballShootAng;
    bool scored = false;
    double gkdx;
    double gkdx2;
    char c;
    bool shot = false;
    bool ballyGoal, ballxGoal;
    double balldx, balldy;
    double ballxTemp, ballyTemp;
    double goalkxTemp;
    double goalkxTemp2;
    double goalkxTemp3;
    int ballxInit, ballyInit;
    bool missed = false;
    bool stopped = false;
    gkdx = 1;
    gkdx2 = 2;
    balldx = 0;
    balldy = 0;
    goalkxTemp = 300;
    goalkxTemp2 = 175;
    goalkxTemp3 = 425;
    ballx = 500;
    ballxInit = ballx;
    bally = 500;
    ballyInit = bally;
    ballxTemp = ballx;
    ballyTemp = bally;
    goalkx = 300;
    goalky = 110;
    goalkx2 = 175;
    goalky2 = 150;
    goalkx3 = 425;
    goalky3 = 150;
    ballShootRad = 50;
    ballShootAng = M_PI/2;
    
    // In game functionality
    while(lives>=1 && !scored){
        gfx_clear();
        draw_game(ballShootRad,ballShootAng,goalkx,goalky,ballx,bally,lives,ballxInit,ballyInit);
        draw_goalkeeper(goalkx2,goalky2);
        draw_goalkeeper(goalkx3,goalky3);
        gfx_flush();
        usleep(10000);
        
        if(gfx_event_waiting()&&!shot){
            c = gfx_wait();
            
            if(c == 32){ //space
                shot = true;   
                balldx = 1.3*(ballShootRad+25)/50*cos(-1*ballShootAng+M_PI);
            }
            
            if(c == 81){ //left arrow
                left_arrow(ballShootAng);
            }
            
            else if(c == 83){ //right arrow
                right_arrow(ballShootAng);
            }
            
            else if(c == 82){ //up arrow
                up_arrow(ballShootRad);
            }
            
            else if(c == 84){ //down arrow
                down_arrow(ballShootRad);
            }
        }
        
        // Checks shot
        if(shot == true){
            after_shot(balldx,balldy,bally,ballx,goalky,goalkx,stopped,gkdx,ballShootRad,ballShootAng);
            after_shot(balldx,balldy,bally,ballx,goalky2,goalkx2,stopped,gkdx2,ballShootRad,ballShootAng);
            after_shot(balldx,balldy,bally,ballx,goalky3,goalkx3,stopped,-1*gkdx2,ballShootRad,ballShootAng);
        }
        
        if(goalkx <= 230){
            gkdx = -1*gkdx;
        }
        
        if(goalkx >= 370){
            gkdx = -1*gkdx;
        }
        
        if(goalkx2 <= 175){
            gkdx2 = abs(gkdx2);
        }
        
        if(goalkx2 >= 280){
            gkdx2 = -1*abs(gkdx2);
        }
        
        // updates position of objects on the field
        updates(balldx,balldy,ballxTemp,ballyTemp,ballx,bally,goalkx,gkdx,goalkxTemp);
        
        goalkxTemp2 += gkdx2;
        goalkx2 = goalkxTemp2;
        goalkxTemp3 -= gkdx2;
        goalkx3 = goalkxTemp3;

        // conditions of scoring
        ballyGoal = (bally+22 <=100);
        ballxGoal = (ballx >=210 && ballx <= 390);
        
        if(ballyGoal&&ballxGoal){
            scored = true;
        }   
        
        // conditions of missing
        missed = (ballx<=55 && bally>=105)||(ballx>=545 && bally>=105)||(bally<=105 && ballx<=200)||(bally<=105 && ballx>=400);

        if((missed||stopped)&&!((bally<=100)&&(ballx>=210)&&(ballx<=390))){
            // reset all values and lose a life
            lives -=1;
            ballx = 500;
            bally = 500;
            ballxTemp = 500;
            ballyTemp = 500;
            balldx = 0;
            balldy = 0;
            shot = false;
            ballShootRad = 50;
            ballShootAng = M_PI/2;
            if(lives > 0){
                char text[] = "Press 'q' to try again";
                wait_quit(text);
                stopped = false;
            }
        }
    }

    // Prompts user to advance to last level after scoring
    if(scored&&lives>=1){
        char text[] = "Press 'q' to go to the last level";
        wait_quit(text);
        gfx_clear();
        level4_animation(lives,goalkx,goalky,goalkx2,goalky2,goalkxTemp,goalkx3,goalky3,ballShootRad,ballx,bally,ballxInit,ballyInit,ballShootAng);
    }

    // Allows user to return to menu if they lost all lives
    if(lives == 0){
        char text1[] = "Game Over! Press 'q' to go back to the menu";
        wait_quit(text1);
        gfx_clear();
    }
}

// Draws animation between second last and last level
void level4_animation(int lives,int goalkx, int goalky, int goalkx2, int goalky2, double goalkxTemp, int goalkx3, int goalky3, int ballShootRad, int ballx, int bally, int ballxInit, int ballyInit, double ballShootAng){
    int gkdx;
    bool playing = true;  
    
    gkdx = -2;
    
    while(playing){
        gfx_clear();
        draw_game(ballShootRad,ballShootAng,goalkx,goalky,ballx,bally,lives,ballxInit,ballyInit);
        draw_goalkeeper(goalkx2,goalky2);
        draw_goalkeeper(goalkx3,goalky3);
        gfx_flush();
        usleep(10000);
        goalkxTemp += gkdx;
        goalkx = goalkxTemp;
        goalkx2 += gkdx;
        goalkx3 += gkdx;
        if(goalkx3 <= -1* 100)
          playing = false;
    }

    goalkxTemp = 800;
    goalkx = 800;
    gkdx = -1;
    playing = true;

    while(playing){
        gfx_clear();
        draw_game2(ballShootRad,ballShootAng,goalkx,goalky,ballx,bally,lives,ballxInit,ballyInit);
        gfx_flush();
        usleep(10000);
        goalkxTemp += gkdx;
        goalkx = goalkxTemp;
        if(goalkx == 300)
          playing = false;
    }

    playing = true;
    goalkx2 = -200;
    goalky2 = 175;
    goalkx3 = 800; 
    goalky3 = 175;

    while(playing){
        gfx_clear();
        draw_game2(ballShootRad,ballShootAng,goalkx,goalky,ballx,bally,lives,ballxInit,ballyInit);
        draw_goalkeeper(goalkx2,goalky2);
        draw_goalkeeper(goalkx3,goalky3);
        gfx_flush();
        usleep(10000);
        if( goalkx2 != 175 ){
            goalkx2 += 1;
        }
        if(goalkx3 != 425){
            goalkx3 -= 1;
        }
        if(goalkx2 == 175 && goalkx3 == 425)
          playing = false;
    }
    
    play_level4(lives);
}

void play_level4(int lives){
    int goalkx, goalky;
    int goalkx2, goalky2;
    int goalkx3, goalky3;
    int ballShootRad, ballx, bally;
    double ballShootAng;
    bool scored = false;
    double gkdx;
    double gkdx2;
    char c;
    bool shot = false;
    bool ballyGoal, ballxGoal;
    double balldx, balldy;
    double ballxTemp, ballyTemp;
    double goalkxTemp;
    double goalkxTemp2;
    double goalkxTemp3;
    int ballxInit, ballyInit;
    bool missed = false;
    bool stopped = false;
    gkdx = 1.5;
    gkdx2 = 2;
    balldx = 0;
    balldy = 0;
    goalkxTemp = 300;
    goalkxTemp2 = 175;
    goalkxTemp3 = 425;
    ballx = 300;
    ballxInit = ballx;
    bally = 500;
    ballyInit = bally;
    ballxTemp = ballx;
    ballyTemp = bally;
    goalkx = 300;
    goalky = 110;
    goalkx2 = 175;
    goalky2 = 175;
    goalkx3 = 425;
    goalky3 = 175;
    ballShootRad = 50;
    ballShootAng = M_PI/2;
    
    // In game functionality
    while(lives>=1 && !scored){
        gfx_clear();
        draw_game2(ballShootRad,ballShootAng,goalkx,goalky,ballx,bally,lives,ballxInit,ballyInit);
        draw_goalkeeper(goalkx2,goalky2);
        draw_goalkeeper(goalkx3,goalky3);
        gfx_flush();
        usleep(10000);
        
        if(gfx_event_waiting()&&!shot){
            c = gfx_wait();
            
            if(c == 32){ //space
                shot = true;   
                balldx = 1.3*(ballShootRad+25)/50*cos(-1*ballShootAng+M_PI);
            }
            
            if(c == 81){ //left arrow
                left_arrow(ballShootAng);
            }
            
            else if(c == 83){ //right arrow
                right_arrow(ballShootAng);
            }
            
            else if(c == 82){ //up arrow
                up_arrow(ballShootRad);
            }
            
            else if(c == 84){ //down arrow
                down_arrow(ballShootRad);
            }
        }
        
        // After shot calculations
        if(shot == true){
            after_shot2(balldx,balldy,bally,ballx,goalky,goalkx,stopped,gkdx,ballShootRad,ballShootAng);
            after_shot(balldx,balldy,bally,ballx,goalky2,goalkx2,stopped,gkdx2,ballShootRad,ballShootAng);
            after_shot(balldx,balldy,bally,ballx,goalky3,goalkx3,stopped,-1*gkdx2,ballShootRad,ballShootAng);
        }
        
        if(goalkx <= 170){
            gkdx = -1*gkdx;
        }
        
        if(goalkx >= 430){
            gkdx = -1*gkdx;
        }
        
        if(goalkx2 <= 165){
            gkdx2 = abs(gkdx2);
        }
        
        if(goalkx2 >= 275){
            gkdx2 = -1*abs(gkdx2);
        }
        
        // Updates positions of each object
        updates(balldx,balldy,ballxTemp,ballyTemp,ballx,bally,goalkx,gkdx,goalkxTemp);
        
        goalkxTemp2 += gkdx2;
        goalkx2 = goalkxTemp2;
        goalkxTemp3 -= gkdx2;
        goalkx3 = goalkxTemp3;

        // conditions of scoring
        ballyGoal = (bally+22 <=100);
        ballxGoal = (ballx >=210 && ballx <= 390);
        
        if(ballyGoal&&ballxGoal){
            scored = true;
        }   
        
        // conditions of missing
        missed = (ballx<=55 && bally>=105)||(ballx>=545 && bally>=105)||(bally<=105 && ballx<=200)||(bally<=105 && ballx>=400);

        if((missed||stopped)&&!((bally<=100)&&(ballx>=210)&&(ballx<=390))){
            // reset all values and lose a life
            lives -=1;
            ballx = 300;
            bally = 500;
            ballxTemp = 300;
            ballyTemp = 500;
            balldx = 0;
            balldy = 0;
            shot = false;
            ballShootRad = 50;
            ballShootAng = M_PI/2;
            if(lives > 0){
                char text[] = "Press 'q' to try again";
                wait_quit(text);
                stopped = false;
            }
        }
    }

    // Congratulates the user on winning the game and returns them to the menu
    if(scored&&lives>=1){
        char text[] = "Congratulations! You won! Press 'q' to go back to the menu";
        wait_quit(text);
        gfx_clear();
    }

    // Returns user to menu after they've lost all lives
    if(lives == 0){
        char text1[] = "Game Over! Press 'q' to go back to the menu";
        wait_quit(text1);
        gfx_clear();
    }
}

// Calculates new posititons of obejcts on the screen
void updates(double balldx, double balldy, double &ballxTemp, double &ballyTemp, int &ballx, int &bally, int &goalkx, double gkdx,double &goalkxTemp){
      ballxTemp += balldx;
      ballyTemp += balldy;
      ballx = ballxTemp;
      bally = ballyTemp;
      goalkxTemp += gkdx;
      goalkx = goalkxTemp;
}

// After shot calculations
void after_shot(double &balldx, double &balldy, int bally, int ballx, int goalky, int goalkx, bool &stopped, double gkdx,int ballShootRad, double ballShootAng){
    bool collisiony;
    balldy = 1.3*(ballShootRad+30)/50*sin(-1*ballShootAng);
    collisiony = (bally-10<=goalky+13)&&(bally-10>=goalky+10)&&(ballx >= goalkx-20)&&(ballx <= goalkx+20);
    if(collisiony){
        balldy = 0;
        stopped = true;
    }
    
    if((ballx+10>=goalkx-20)&&(ballx+10<=goalkx-17)&&(bally >= goalky-10)&&(bally <= goalky+10)){
        if((balldx <= 1)&&(gkdx<=0)){
           balldx = gkdx;
        }
        else{
          balldx = -1*balldx;
        }
    }

    if((ballx-10<=goalkx+20)&&(ballx-10>=goalkx+17)&&(bally >= goalky-10)&&(bally <= goalky+10)){
        if((balldx <= 1)&&(gkdx>=0)){
            balldx = gkdx;
        }
        else{
          balldx = -1*balldx;
        }
    }
}

// Account for big goalkeeper from last level in collision detection
void after_shot2(double &balldx, double &balldy, int bally, int ballx, int goalky, int goalkx, bool &stopped, double gkdx,int ballShootRad, double ballShootAng){
    bool collisiony;
    balldy = 1.3*(ballShootRad+25)/50*sin(-1*ballShootAng);
    collisiony = (bally-10<=goalky+30)&&(bally-10>=goalky+25)&&(ballx >= goalkx-40)&&(ballx <= goalkx+40);
    if(collisiony){
        balldy = 0;
        stopped = true;
    }
    
    if((ballx+10>=goalkx-40)&&(ballx+10<=goalkx-35)&&(bally >= goalky-20)&&(bally <= goalky+20)){
        if((balldx <= 1)&&(gkdx<=0)){
           balldx = gkdx;
        }
        else{
          balldx = -1*balldx;
        }
    }

    if((ballx-10<=goalkx+40)&&(ballx-10>=goalkx+35)&&(bally >= goalky-20)&&(bally <= goalky+20)){
        if((balldx <= 1)&&(gkdx>=0)){
            balldx = gkdx;
        }
        else{
          balldx = -1*balldx;
        }
    }
}

// Changes direction of the arrow behind the ball
void left_arrow(double &ballShootAng){
    if(ballShootAng >=0){
        ballShootAng -= M_PI/64;
    }
}

void right_arrow(double &ballShootAng){
    if(ballShootAng <= M_PI){
        ballShootAng += M_PI/64;
    }
}

void up_arrow(int &ballShootRad){
    if(ballShootRad <= 75){
           ballShootRad += 1;
    }
}

void down_arrow(int &ballShootRad){
    if(ballShootRad >= 25){
        ballShootRad -= 1;
    }
}

// Draw the game itself
void draw_game(int radius, double angle, int goalkx, int goalky, int ballx, int bally, int lives, int ballxInit, int ballyInit){
	// call drawing funcs
    draw_goal();
    draw_goalkeeper(goalkx,goalky);
    gfx_fill_circle(ballx,bally,10); // ball
    draw_arrow(radius, angle, ballxInit, ballyInit);
    draw_eyecandy();
    draw_lives(lives);
}

// Draw game with big goalkeeper
void draw_game2(int radius, double angle, int goalkx, int goalky, int ballx, int bally, int lives, int ballxInit, int ballyInit){
	// call drawing funcs
    draw_goal();
    draw_biggoalkeeper(goalkx,goalky);
    gfx_fill_circle(ballx,bally,10); // ball
    draw_arrow(radius, angle, ballxInit, ballyInit);
    draw_eyecandy();
    draw_lives(lives);
}

// Draw remaining lives in the top left corner
void draw_lives(int lives){
	char font[] = "6x12";
	char text[] = "Balls left: ";
	gfx_changefont(font);
	gfx_text(5,10,text);
    for(int i = 0; i < lives - 1; i++){
        gfx_fill_circle(80+i*10,7,4);
    }
}

// Draw the goal
void draw_goal(){
	
	const int goal_size = 200;
    gfx_fill_rectangle(200,50,goal_size,10); //top
    gfx_fill_rectangle(200,50,10,50); //left
    gfx_fill_rectangle(390,50,10,50); //right
}

// draws small goalkeeper
void draw_goalkeeper(int x, int y){
    gfx_fill_rectangle(x-20, y-10, 40, 20); // body
    gfx_fill_circle(x,y+5,8); // head
    gfx_fill_circle(x-14,y+14,4); // left arm
    gfx_fill_circle(x+14,y+14,4); // right arm
}

// Draws the big goalkeeper
void draw_biggoalkeeper(int x, int y){
	y+=10;
    gfx_fill_rectangle(x-40, y-20, 80, 40); // body
    gfx_fill_circle(x,y+10,16); // head
    gfx_fill_circle(x-28,y+28,8); // left arm
    gfx_fill_circle(x+28,y+28,8); // right arm
}

// Draws decorations, extra lines might make it slower
void draw_eyecandy(){
	
	// draw borders
	gfx_fill_rectangle(50,100,5,600); // left
	gfx_fill_rectangle(50,100,500,5); // top
	gfx_fill_rectangle(545,100,5,600); // right
	
	// draw goalline
	gfx_fill_rectangle(150,225,300,5); // bottom 
	gfx_fill_rectangle(150,100,5,125); // left
	gfx_fill_rectangle(445,100,5,125); // right
	
	// draw goal net
	for(int i = 200; i < 325; i+=25) gfx_line(i,100,i+100,50);
	for(int i = 300; i < 425; i+=25) gfx_line(i,100,i-100,50);
	// extra lines
	gfx_line(325, 100, 400, 60);
	gfx_line(350, 100, 400, 70);
	gfx_line(200, 80, 275, 50);
	gfx_line(200, 60, 275, 100);
	gfx_line(200, 75, 250, 100);
	gfx_line(350, 50, 400, 75);
	gfx_line(325, 50, 400, 90);
	
	// draw team names
	char font[] = "12x24";
	char text[] = "Real Madrid";
	gfx_changefont(font);
	gfx_text(235,40,text);
	
	char text1[] = "Barcelona";
	gfx_text(250,575,text1);
	
}

// Draws the arrow behind the ball
void draw_arrow(int radius, double angle, int x0, int y0){
    x0 = x0 + (1.3)*10*cos(angle);
    y0 = y0 + (1.3)*10*sin(angle);
    gfx_line(x0+radius*cos(angle),y0+radius*sin(angle),x0,y0);
    gfx_line(x0,y0,x0+7*cos(angle+M_PI/8),y0+7*sin(angle+M_PI/8));
    gfx_line(x0,y0,x0+7*cos(angle-M_PI/8),y0+7*sin(angle-M_PI/8));
}

// Waits for user to press q, then returns. Takes custom text to display
void wait_quit(char text[]){
	bool exit = false;
	char font[] = "6x12";
    gfx_changefont(font);
    int xpos = gfx_windowwidth()/2 - gfx_textpixelwidth(text,font)/2;
	while(!exit){
		gfx_text(xpos,590,text);
		if(gfx_event_waiting() != 0){
			if(gfx_wait() == 'q') exit = true;
		}
	}
	return;
}
