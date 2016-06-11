//Project 1

//File: project1.c

/*Program description: This program simulates a game of craps.
The player is given an initial bank roll of $100.00. The player is
given a choice to place a bet or no bet ($5.00 minimum.) After
placing the bet, the player decides whether he/she will bet for
or against themselves. Then the player rolls the dice and depending
on the total dice roll and whether they bet for or against themselves
the player wins or loses the amount of the bet. The player is also
given a choice to double their bet, in which case they must roll
the seven (bet against) or the point (bet for) to win. After the game
is completed the player can decide to continue playing or quit. If the
player runs out of money the game exits automatically. Player statistics
are listed after each game and then saved to a text file.
*/


//preprocessor directives and constants
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define INITIAL_BET_BILL 100 //players initial bank roll


//function prototypes
int rolling(int dice_1, int dice_2);
int playing(double *bank_rollp, int *wonp, int *lostp, int *bet_forp, int *bet_againstp);
int ending(double *end_bank_rollp, int *end_wonp, int *end_lostp, int *end_bet_forp, int *end_bet_againstp);
int beginning(double *begin_bank_rollp, int *begin_wonp, int *begin_lostp, int *begin_bet_forp, int *begin_bet_againstp);


//main function
int
main(void)
{

    //main variables for playing function
    double current_bank_roll;
    int times_won = 0;
    int times_lost = 0;
    int times_bet_for = 0;
    int times_bet_against = 0;
    int play_time;
    char P_or_Q;     //play or quit the game
    int condition;   //value for while loop


    current_bank_roll = INITIAL_BET_BILL; //player starts with $100

    printf("Welcome to the GMU craps table!\n"); //introduction message

    //notify the player how much money is initially in their bank roll
    printf("All players start with $%.2f in their bank roll.\n", current_bank_roll);



    beginning(&current_bank_roll, &times_won, &times_lost, &times_bet_for, &times_bet_against);



    //call playing function to play the game
    play_time = playing(&current_bank_roll, &times_won, &times_lost, &times_bet_for, &times_bet_against);

    //call ending function to display results to player
    ending(&current_bank_roll, &times_won, &times_lost, &times_bet_for, &times_bet_against);


    //check if the player ran out of money (there is a $5.00 minimum bet)
    //The player cannot continue playing if he/she has less than $5.00
    if (current_bank_roll < 5)
    {
        //exit the game because player has no money left
        printf("You ran out of money! Come back another time.\n");
        exit(0);
    }


    //check if the player played the game at least once
    condition = 1;
    while ((times_won >= 1 || times_lost >= 1) && condition == 1)
    {
        //ask player if they would like to continue or quit
        printf("Would like to continue playing (P) or quit (Q)? ");
        scanf(" %c", &P_or_Q);

        switch(P_or_Q)
        {
            case 'P':
            case 'p':
                    //call playing function to play the game
                    play_time = playing(&current_bank_roll, &times_won, &times_lost, &times_bet_for, &times_bet_against);

                    //call ending function to display results to user
                    ending(&current_bank_roll, &times_won, &times_lost, &times_bet_for, &times_bet_against);

                    //check if the player ran out of money
                    if (current_bank_roll < 5)
                    {
                        //exit game because player has no money left
                        printf("You ran out of money! Come back another time.\n");
                        exit(0);
                    }
                    break;

            case 'Q':
            case 'q':
                    //if player chooses to quit, exit the game
                    printf("Thank you for playing! Hope to see you soon!\n");
                    condition = 0;   //set sentinel value to 0 to exit while loop
                    break;

        }
    }


    //main function returns value of 0
    return (0);

}





//rolling the dice function
int
rolling(int dice_1, int dice_2)
{
    //initialize dice variables
    int x_dice = 0;
    int y_dice = 0;
    int sum_of_die;

    //get random number for x-dice
    srand((int)(time(NULL)));

    //convert random number to a number in the range 1 to 6
    x_dice = (rand()%6)+1;

    //convert random number to a number in the range 1 to 6
    y_dice = (rand()%6)+1;

    //display dice roll results to the player
    printf("The first dice roll is: %d\n", x_dice);
    printf("The second dice roll is: %d\n", y_dice);

    //calculate the sum of the dice roll
    sum_of_die = x_dice + y_dice;

    //return the sum of both dice
    return sum_of_die;


}


//playing the game function
int
playing(double *bank_rollp, int *wonp, int *lostp, int *bet_forp, int *bet_againstp)
{
    char Y_or_N;  //yes or no
    char F_or_A;  //for or against
    char key_press; //interactive input for dice roll
    int play_die1, play_die2; //variables for calling the rolling function
    int total_die_value;      //initialize the total dice value
    double amount_of_bet; //place dollar bet
    int players_point;
    int inner_condition;  //value for while loop
    int money_condition;  //value to check if player bets valid amount of money
    double doubled_bet;      //variable for storing the players doubled bet
    int doubling_condition; //value for checking if the player is allowed to double their bet

    //ask player if they want to bet
    printf("Would you like to place a bet (Y or N)? ");
    scanf(" %c", &Y_or_N);

    //check if they entered Yes (Y) or No (N)
    switch (Y_or_N)
    {

        case 'Y':
        case 'y':

            //check if a valid bet is entered
            money_condition = 1;
            while (money_condition == 1)
            {
                //ask player to place a bet
                printf("Please enter the amount of the bet ($5.00 minimum): $");
                scanf("%lf", &amount_of_bet);

                //check if the bet they placed is more than their bank roll
                if (amount_of_bet > *bank_rollp)
                {
                    printf("Insufficient funds. You only have $%.2f in your bank roll.\n", *bank_rollp);
                }

                //check if they entered at least $5.00 bet
                else if (amount_of_bet < 5)
                {
                    printf("Minimum bet must be $5.00!\n");
                }

                //if they entered a valid bet reset the sentinel value and exit this loop
                else
                {
                    money_condition = 0;
                }

            }

            //ask if the player would like to bet for or against themselves
            printf("Would you like to bet for or against yourself (F or A)? ");
            scanf(" %c", &F_or_A);

            switch (F_or_A)
            {
                //if player bets for themselves
                case 'F':
                case 'f':
                        //increase the "bet for" counter by 1
                        *bet_forp = *bet_forp + 1;

                        //interactive input for rolling the dice
                        key_press = getchar();

                        //keep looping while the player presses enter
                        inner_condition = 1;
                        while (key_press == '\n' && inner_condition == 1)
                        {
                            //player presses enter to roll the dice
                            printf("Press enter to roll the dice!\n");
                            key_press = getchar();

                            //call the rolling function and store the sum of dice value
                            total_die_value = rolling(play_die1, play_die2);
                            //display the total value of the roll to the player
                            printf("The total value of the roll is: %d\n", total_die_value);

                            //check if the player rolled a 7 or 11
                            if (total_die_value == 7 || total_die_value == 11)
                            {
                                //notify the player won the amount that they bet
                                printf("You won $%.2f!\n", amount_of_bet);
                                //increase the bank roll by the amount they bet
                                *bank_rollp = *bank_rollp + amount_of_bet;
                                //increase the win counter by 1
                                *wonp = *wonp + 1;

                                break;  //go back to the main function


                            }

                            //check if the player rolled a 2 or 3 or 12
                            else if (total_die_value == 2 || total_die_value == 3 || total_die_value == 12)
                            {
                                //notify the player that they lost the amount they bet
                                printf("You lost $%.2f...\n", amount_of_bet);
                                //decrease the bank roll by the amount they bet
                                *bank_rollp = *bank_rollp - amount_of_bet;
                                //increase the lost counter by 1
                                *lostp = *lostp + 1;

                                break;   //go back to the main function
                            }


                            //check if the player rolled something other than 2, 3, 7, 11, or 12
                            else if (total_die_value != 2 || total_die_value != 3 || total_die_value != 7 || total_die_value != 11 || total_die_value != 12)
                            {
                                //initialize the players point
                                players_point = total_die_value;
                                //ask player if they would like to double their bet
                                printf("Would you like to double the amount of your bet (Y or N)? ");
                                scanf("%c", &Y_or_N);

                                switch (Y_or_N)
                                {
                                    //if player chooses to double their bet
                                    case 'Y':
                                    case 'y':



                                            //double their bet
                                            doubled_bet = amount_of_bet*2;

                                            //check if the player is allowed to double their bet
                                            if (doubled_bet > *bank_rollp)
                                            {
                                                //notify the player that they cannot double
                                                printf("Insufficient funds. You cannot double your bet!\n");
                                                amount_of_bet = amount_of_bet;   //initialize the bet back to the original value
                                                doubling_condition = 0;     //set the sentinel value for later use
                                                //this sentinel value is used to check whether the player doubled or not
                                            }

                                            else
                                            {
                                                doubling_condition = 1;    //set the sentinel value

                                            }


                                            //get interactive input from player
                                            key_press = getchar();
                                            //continue looping while the player presses enter
                                            while (key_press == '\n')
                                            {
                                                //player must press enter to roll the dice
                                                printf("Press enter to roll the dice!\n");
                                                key_press = getchar();

                                                //call the rolling function and get the total value of the dice
                                                total_die_value = rolling(play_die1, play_die2);
                                                printf("The total value of the roll is: %d\n", total_die_value);

                                                //check if the players point equals the total value rolled
                                                if (players_point == total_die_value)
                                                {
                                                    if (doubling_condition == 0)
                                                    {
                                                        //player wins the bet if they rolled the the point
                                                        printf("You won $%.2f!\n", amount_of_bet);


                                                        //increase the players bank roll
                                                        *bank_rollp = *bank_rollp + amount_of_bet;
                                                    }

                                                    else if (doubling_condition == 1)
                                                    {
                                                        //player wins double the bet if they rolled the the point
                                                        printf("You won $%.2f!\n", doubled_bet);


                                                        //increase the players bank roll
                                                        *bank_rollp = *bank_rollp + doubled_bet;
                                                    }


                                                    //increase the players win counter
                                                    *wonp = *wonp + 1;
                                                    //break out of inner while loop
                                                    inner_condition = 0;
                                                    break;

                                                }

                                                //check if player rolled a 7
                                                else if (total_die_value == 7)
                                                {
                                                    if (doubling_condition == 0)
                                                    {
                                                        //player loses the bet because they rolled a 7
                                                        printf("You sevened out. You lost $%.2f...\n", amount_of_bet);
                                                        //decrease the players bank roll
                                                        *bank_rollp = *bank_rollp - amount_of_bet;

                                                    }

                                                    else if (doubling_condition == 1)
                                                    {
                                                        //player loses the double bet because they rolled a 7
                                                        printf("You sevened out. You lost $%.2f...\n", doubled_bet);
                                                        //decrease the players bank roll
                                                        *bank_rollp = *bank_rollp - doubled_bet;

                                                    }

                                                    //increase the lose counter
                                                    *lostp = *lostp + 1;
                                                    //break out of inner while loop
                                                    inner_condition = 0;
                                                    break;

                                                }

                                            }
                                                break; //break yes case for doubling the bet



                                        //if player does not want to double their bet
                                        case 'N':
                                        case 'n':
                                                //Do not double the players bet
                                                //keep rolling the dice
                                                key_press = getchar();

                                                while (key_press == '\n')
                                                {
                                                    //player must press enter to roll the dice
                                                    printf("Press enter to roll the dice!\n");
                                                    key_press = getchar();

                                                    //call the rolling function and get the total value of the dice
                                                    total_die_value = rolling(play_die1, play_die2);
                                                    printf("The total value of the roll is: %d\n", total_die_value);

                                                    //check if the players point equals the total value rolled
                                                    if (players_point == total_die_value)
                                                    {
                                                        //player wins the double bet if they rolled the the point
                                                        printf("You won $%.2f!\n", amount_of_bet);
                                                        //increase the players bank roll
                                                        *bank_rollp = *bank_rollp + amount_of_bet;
                                                        //increase the players win counter
                                                        *wonp = *wonp + 1;
                                                        //break out of inner while loop
                                                        inner_condition = 0;
                                                        break;

                                                    }

                                                    //check if player rolled a 7
                                                    else if (total_die_value == 7)
                                                    {
                                                        //player loses the double bet because they rolled a 7
                                                        printf("You sevened out. You lost $%.2f...\n", amount_of_bet);
                                                        //decrease the players bank roll
                                                        *bank_rollp = *bank_rollp - amount_of_bet;
                                                        //increase the lose counter
                                                        *lostp = *lostp + 1;
                                                        //break out of inner while loop
                                                        inner_condition = 0;
                                                        break;

                                                    }


                                                }

                                                        break; //break the "No" case




                                }





                            }




                        }



                                        break; //break for case





                    //if player bets against themselves
                    case 'A':
                    case 'a':
                            //increase the "bet against" counter by 1
                            *bet_againstp = *bet_againstp + 1;
                            //interactive input for dice roll
                            key_press = getchar();

                            //keep looping while the player presses enter
                            inner_condition = 1;
                            while (key_press == '\n' && inner_condition == 1)
                            {
                                //player must press enter to roll the dice
                                printf("Press enter to roll the dice!\n");
                                key_press = getchar();

                                //store the total value of the dice roll and display total to player
                                total_die_value = rolling(play_die1, play_die2);
                                printf("The total value of the roll is: %d\n", total_die_value);

                                //check if total dice roll is 7 or 11
                                if (total_die_value == 7 || total_die_value == 11)
                                {
                                    //notify user they lost the amount they bet
                                    printf("You lost $%.2f...\n", amount_of_bet);
                                    //decrease the players bank roll
                                    *bank_rollp = *bank_rollp - amount_of_bet;
                                    //increase the players lose counter
                                    *lostp = *lostp + 1;

                                    break;  //go back to main function


                                }

                                //check if the player rolled a 2, 11, or 12
                                else if (total_die_value == 2 || total_die_value == 3 || total_die_value == 12)
                                {
                                    //notify player that they won the amount of the bet
                                    printf("You won $%.2f!\n", amount_of_bet);
                                    //increase the players bank roll
                                    *bank_rollp = *bank_rollp + amount_of_bet;
                                    //increase the players win counter
                                    *wonp = *wonp + 1;

                                    break;   //go back to the main function
                                }

                                // check if the player rolled a number other than 2, 3, 7, 11, or 12
                                else if (total_die_value != 2 || total_die_value != 3 || total_die_value != 7 || total_die_value != 11 || total_die_value != 12)
                                {
                                    //initialize the players point and ask if they want to double their bet
                                    players_point = total_die_value;
                                    printf("Would you like to double the amount of your bet (Y or N)? ");
                                    scanf("%c", &Y_or_N);

                                    switch (Y_or_N)
                                    {
                                        //if the player chooses to double
                                        case 'Y':
                                        case 'y':

                                                //double the amount of their bet
                                                doubled_bet = amount_of_bet*2;

                                                //check if the player is allowed to double their bet
                                                if (doubled_bet > *bank_rollp)
                                                {
                                                    //notify the player that they cannot double
                                                    printf("Insufficient funds. You cannot double your bet!\n");
                                                    amount_of_bet = amount_of_bet;   //initialize the bet back to the original value
                                                    doubling_condition = 0;     //set the sentinel value for later use
                                                    //this sentinel value is used to check whether the player doubled or not
                                                }

                                                else
                                                {
                                                    doubling_condition = 1;    //set the sentinel value

                                                }



                                                //interactive input for dice roll
                                                key_press = getchar();

                                                //keep looping while player presses enter
                                                while (key_press == '\n')
                                                {
                                                    //player must press enter to roll
                                                    printf("Press enter to roll the dice!\n");
                                                    key_press = getchar();

                                                    //call the rolling function and store the total dice value and display the total
                                                    total_die_value = rolling(play_die1, play_die2);
                                                    printf("The total value of the roll is: %d\n", total_die_value);

                                                    //check if the player rolled a 7
                                                    if (total_die_value == 7)
                                                    {
                                                        if (doubling_condition == 0)
                                                        {
                                                            //notify the player they won the amount of the bet
                                                            printf("You won $%.2f!\n", amount_of_bet);
                                                            //increase the players bank roll
                                                            *bank_rollp = *bank_rollp + amount_of_bet;

                                                        }

                                                        else if (doubling_condition == 1)
                                                        {
                                                            //notify the player they won the amount of the bet
                                                            printf("You won $%.2f!\n", doubled_bet);
                                                            //increase the players bank roll
                                                            *bank_rollp = *bank_rollp + doubled_bet;


                                                        }

                                                        //increase the win counter
                                                        *wonp = *wonp + 1;
                                                        //break out of the inner while loop
                                                        inner_condition = 0;
                                                        break;

                                                    }

                                                    //check if the player rolled the point
                                                    else if (players_point == total_die_value)
                                                    {
                                                        if (doubling_condition == 0)
                                                        {
                                                            //notify the player that they lost the bet
                                                            printf("You rolled the point. You lost $%.2f...\n", amount_of_bet);
                                                            //decrease the bank roll
                                                            *bank_rollp = *bank_rollp - amount_of_bet;

                                                        }

                                                        else if (doubling_condition == 1)
                                                        {
                                                            //notify the player that they lost the bet
                                                            printf("You rolled the point. You lost $%.2f...\n", doubled_bet);
                                                            //decrease the bank roll
                                                            *bank_rollp = *bank_rollp - doubled_bet;

                                                        }

                                                        //increase the lose counter
                                                        *lostp = *lostp + 1;
                                                        //break out of the inner while loop
                                                        inner_condition = 0;
                                                        break;

                                                    }

                                                }
                                                    break; //break yes case for doubling the bet


                                            //if player chooses not to double
                                            case 'N':
                                            case 'n':
                                                    //Do not double the players bet
                                                    //keep rolling the dice
                                                    key_press = getchar();

                                                    while (key_press == '\n')
                                                    {
                                                        //player must press enter to roll
                                                        printf("Press enter to roll the dice!\n");
                                                        key_press = getchar();

                                                        //call the rolling function and store the total dice value and display the total
                                                        total_die_value = rolling(play_die1, play_die2);
                                                        printf("The total value of the roll is: %d\n", total_die_value);

                                                        //check if the player rolled a 7
                                                        if (total_die_value == 7)
                                                        {
                                                            //notify the player they won the amount of the bet
                                                            printf("You won $%.2f!\n", amount_of_bet);
                                                            //increase the players bank roll
                                                            *bank_rollp = *bank_rollp + amount_of_bet;
                                                            //increase the win counter
                                                            *wonp = *wonp + 1;
                                                            //break out of the inner while loop
                                                            inner_condition = 0;
                                                            break;

                                                        }

                                                        //check if the player rolled the point
                                                        else if (players_point == total_die_value)
                                                        {
                                                            //notify the player that they lost the bet
                                                            printf("You rolled the point. You lost $%.2f...\n", amount_of_bet);
                                                            //decrease the bank roll
                                                            *bank_rollp = *bank_rollp - amount_of_bet;
                                                            //increase the lose counter
                                                            *lostp = *lostp + 1;
                                                            //break out of the inner while loop
                                                            inner_condition = 0;
                                                            break;

                                                        }


                                                    }


                                                    break; //break "No" case



                                    }





                                }




                            }



                                            break; //break against case




                }





                    break; //break yes case for placing the bet






            //if the player does not want to place a bet exit the game
            case 'N':
            case 'n':
                    printf("Thank you for playing! Hope to see you soon.\n");
                    exit(0);


    }




}




//ending function displays the players results
int
ending(double *end_bank_rollp, int *end_wonp, int *end_lostp, int *end_bet_forp, int *end_bet_againstp)
{

    //declare file pointer
    FILE *myfilep;

    //display results to the player if a roll ends the game
    printf("These are your results:\n");

    printf("-----Total Bank Roll: $%.2f\n",*end_bank_rollp);

    printf("-----Wins: %d\n", *end_wonp);

    printf("-----Losses: %d\n", *end_lostp);

    printf("-----Times Bet For: %d\n", *end_bet_forp);

    printf("-----Times Bet Against: %d\n", *end_bet_againstp);


    //open the file for writing, save the players results to a text file
    myfilep = fopen("results.txt", "w");

    //write the results to the text file
    fprintf(myfilep, "These are the players results:\n");

    fprintf(myfilep, "1.) Total bank roll: $%.2f\n", *end_bank_rollp);

    fprintf(myfilep, "2.) Wins: %d\n", *end_wonp);

    fprintf(myfilep, "3.) Losses: %d\n", *end_lostp);

    fprintf(myfilep, "4.) Times Bet For: %d\n", *end_bet_forp);

    fprintf(myfilep, "5.) Times Bet Against: %d\n", *end_bet_againstp);






    //close the file
    fclose(myfilep);



}


int
beginning(double *begin_bank_rollp, int *begin_wonp, int *begin_lostp, int *begin_bet_forp, int *begin_bet_againstp)
{
    FILE *finp;



    if (finp = fopen("results.txt", "r"))
    {
        ending(begin_bank_rollp, begin_wonp, begin_lostp, begin_bet_forp, begin_bet_againstp);

        printf("this is the beginning bank roll: $%.2f\n", &begin_bank_rollp);

    }


    else
    {

        printf("File does not exist. Starting new game.\n");
    }




    fclose(finp);

}

























