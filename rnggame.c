#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>
#include <string.h>

//declaration
void autoguesser(unsigned int answer);
void wait();

//idiot proofing
static void fail( char const *message ) {
    fprintf( stderr, "%s\n", message );
	wait();
    exit(1);
}

int main(int argc, char **argv)
{
    //will the computer solve it
    bool automatic = false;

    //guess the user is lazy then
    //if(argc == 2 && strcmp(argv[1], "auto") == 0) automatic = true;
    
    //set the rng seed to a random time stamp
    srand(time(NULL));
    //user input
    printf("Select your dificulty level.\n");
	printf("0. Tutorial (automatic)\n");
    printf("1. Baby Mode (100 guesses)\n");
    printf("2. Easy (50 guesses)\n");
    printf("3. Medium (20 guesses)\n");
    printf("4. Hard (10 guesses)\n");
    printf("5. Impossible (5 guesses)\n");
    int option;
    if(scanf("%d", &option) != 1){
        fail("choice must be a number");
    }
    //check for moronic input
    if(option < 0 || option > 5) fail("Invalid choice");
    //generate the random number
    printf("Generating guessing number\n");
    printf("The number is always positive\n");
    printf("The absolute maximum number is %d\n", INT_MAX);
    printf("Enter a non number if you need to exit\n");
    unsigned int answer = rand();
    //printf("%d\n", guess); //strictly debugging purposes
    //number of chances user has left
    int chances;
    //set the difficulty level
    switch(option){
		case 0:
		automatic = true;
		break;
        case 1:
        chances = 100;
        break;
        case 2:
        chances = 50;
        break;
        case 3:
        chances = 20;
        break;
        case 4:
        chances = 10;
        break;
        case 5:
        chances = 5;
        break;
        default:
        fail("sum ain't right chief");
        break;
    }
    //if the user wants to chicken out
    if(automatic) autoguesser(answer);

    //user guessed number input
    unsigned int guess;
    //number of times user has taken
    int attempts = 0;
    //main game
    while(chances){
        printf("Your guess: ");
        int input = scanf("%d", &guess);
        if(input != 1){
            printf("answer must be a number\n");
            input = 0;
            guess = 0;
            continue;
        }
        else if(guess == answer){
            printf("CONGRATULATIONS YOU FOUND THE ANSWER\n");
            printf("and it only took you %d guesses\n", attempts);
			wait();
            return EXIT_SUCCESS;
        }
        else if(guess < answer){
            printf("too low\n");
            chances--;
            attempts++;
            continue;
        }
        else if(guess > answer){
            printf("too high\n");
            chances--;
            attempts++;
            continue;
        }
    }
    //user failed lmao
    printf("oof you ran out of chances\n");
    printf("the actual number was %d\n", answer);
    printf("nice try\n");
	wait();
    return EXIT_SUCCESS;
}

void wait()
{
	printf("Press any key to continue...\n");
	getchar();
}

void autoguesser(unsigned int answer)
{
    //number of attempts by the computer
    int takes = 0;
    //low boundary
    unsigned int low = 0;
    //high boundary
    unsigned int high = INT_MAX;
    //to keep the computer running
    bool guessing = true;
    //the starting number
    unsigned int start = INT_MAX / 2;
    //the shifting guess
    unsigned int cursor = start;
    printf("the computer will do the guessing here\n");
    while(guessing){
        if(cursor == answer){
            guessing = false;
            printf("the computer found it the number is %d\n", cursor);
            printf("it only took %d tries\n", takes);
            continue;
        }
        if(cursor > answer){
            printf("%d is too high\n", cursor);
            //shift high down
            high = cursor;
            cursor = (low+high) / 2;
            takes++;
            continue;
        }
        if(cursor < answer){
            printf("%d is too low\n", cursor);
            low = cursor;
            cursor = (low+high) / 2;
            takes++;
            continue;
        }
    }
	wait();
    exit(0);
}