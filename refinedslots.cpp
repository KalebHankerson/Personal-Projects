//Program that emulates a slot machine at a casino
//Kaleb Hankerson
//04-14-2025

#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <cstdlib>
#include <ctime>


//Function to generate a random symbol
//Selects a random item from a vector of symbols
char spin()
{
    std::vector <char> symbols = {'A', 'B', 'C', 'D'};
    return symbols[rand() % symbols.size()];
}
//Displays the results of the spin in a neat, easy to read format. The function has nine parameters, which are the nine symbols generated 
void display(char s1, char s2, char s3, char s4, char s5, char s6, char s7, char s8, char s9)
{
    std::cout << "-----------------" << '\n';
    std::cout << "| " << s1 << " | " << s2 << " | " << s3 << " |" << '\n';
    std::cout << "-----------------" << '\n';
    std::cout << "| " << s4 << " | " << s5 << " | " << s6 << " |" << '\n';
    std::cout << "-----------------" << '\n';
    std::cout << "| " << s7 << " | " << s8 << " | " << s9 << " |" << '\n';
    std::cout << "-----------------" << std::endl;
}

//Using a struct to hold the boolean value used to check if a pattern matched, the multiplier that is applied based on how many matches there are, and the message sent to the user based on their win.
struct WinResult {
    bool win;
    int multiplier;
    std::string description;
};

//This function has 9 parameters that match the display function, the nine characters are the randomly generated symbols from the spin() function.
WinResult checkWin(char s1, char s2, char s3, char s4, char s5, char s6, char s7, char s8, char s9) {
    WinResult result = {false, 0, ""};

    if (s1 == s2 && s2 == s3 && s3 == s4 && s4 == s5 && s5 == s6 && s6 == s7 && s7 == s8 && s8 == s9) {
        result.win = true;
        result.multiplier = 100;
        result.description = "YOU GOT THE MAX WIN!! WELL DONE!!";
        return result;
    }

  /*Creating boolean arrays to hold the checks for if there is a match. The row and column arrays have 3 elements because up to 3 rows/columns can match. The diagonals can only match 2 times.
  They are initialized to false, but each element is assigned to be true should a row, column, or diagonal pattern match. */
  bool rowMatches[3] = {false, false, false};
  bool colMatches[3] = {false, false, false};
  bool diagMatches[2] = {false, false};
  
  //Each index represents a row, column, or diagonal. Hence why there are 3 row elements, 3 column elements, and 2 diagonal elements.
  // Checking rows. s1 == s2 && s2 == s3 is essentially saying, symbol 1 is equal symbol 2, which is also equal to symbol 3. This continues for all the checks with 1-9 representing each symbol in a row from left to right.
  rowMatches[0] = (s1 == s2 && s2 == s3);
  rowMatches[1] = (s4 == s5 && s5 == s6);
  rowMatches[2] = (s7 == s8 && s8 == s9);
  
  // Checking columns
  colMatches[0] = (s1 == s4 && s4 == s7);
  colMatches[1] = (s2 == s5 && s5 == s8);
  colMatches[2] = (s3 == s6 && s6 == s9);
  
  // Checking diagonals
  diagMatches[0] = (s1 == s5 && s5 == s9);
  diagMatches[1] = (s3 == s5 && s5 == s7);

  /* Counting the matches by initializing 3 ints to hold the values that are added by the given conditonal operators.
  Each conditional operator evaluates to 1 or 0 based on given condition. They are then added up to each other with a max of 3 for the row and column ints,
  and a max of 2 for diagonals.
  */
  int rowCount = (rowMatches[0] ? 1 : 0) + (rowMatches[1] ? 1 : 0) + (rowMatches[2] ? 1 : 0);
  int colCount = (colMatches[0] ? 1 : 0) + (colMatches[1] ? 1 : 0) + (colMatches[2] ? 1 : 0);
  int diagCount = (diagMatches[0] ? 1 : 0) + (diagMatches[1] ? 1 : 0);
  
  // This int is the sum of all the match counts.
  int totalMatches = rowCount + colCount + diagCount;

   //Switch statement is used to check all of the win conditions by passing totalMatches to it. This means that if totalMatches == 1 , then case 1 will trigger
   //and if it equals 2 then case 2 will trigger, etc.
  switch(totalMatches)
  {
    case 1:
        result.multiplier = 2;
        result.description = "You matched one pattern!";
        break;
    case 2:
        result.multiplier = 5;
        result.description = "You matched 2 patterns. Nice one!";
        break;
    case 3:
        result.multiplier = 10;
        result.description = "You matched 3 patterns! Nice job!";
        break;
    case 4:
        result.multiplier = 15;
        result.description = "You matched 4 patterns! Well played!";
        break;
    case 5:
        result.multiplier = 25;
        result.description = "You matched 5 patterns! Well done!!";
        break;
  }
  //This if statement exists because switch statements support constant values for case labels. So since I want to account for 6 or more matches,
  // I use an if statement.
  if (totalMatches >= 6)
  {
    result.multiplier = 50;
    result.description = "INSANE!! You matched 6 or more patterns!";
  }
  //this is the first element of the struct, the boolean win, and it is set to true if the totalMatches is over 0.
  result.win = (totalMatches > 0);
  return result;
}  


//Main function
int main()
{
    //Seed for the random number generator
    srand(time(0));
    //initializing all of the symbols that will be passed to the functions, after they are assigned their char value.
    char symbol1, symbol2, symbol3, symbol4, symbol5, symbol6, symbol7, symbol8, symbol9;
    int balance;
    int bet;
    std::cout << "Enter your balance: " << std::endl;
    //Input validation loop- asks for balance until user enters a number that is greater than 0
    while(!(std::cin >> balance) || balance <= 0)
    {
        std::cout << "Invalid input, please enter a number greater than zero. " << '\n';
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    std::cout << "Your balance is $" << balance << '\n';
    //This is the main loop for the slots and it runs while the user's balance is above 0, or if they bet 0.
    while (balance > 0) {
        std::cout << "Enter the amount you would like to bet: (Or enter 0 to quit)" << '\n';
        std::cin >> bet;
        //Input validation
        if (std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Error, please enter an integer." << '\n';
            continue;
        }
        //This is the user's quit option
        else if (bet == 0) {
            break; //Break if user enters 0 as their bet
        }
        //Check for bets greater than the balance
        else if (bet > balance) {
            std::cout << "Error. You cannot bet an amount greater than your current balance." << '\n';
            continue; //Reset loop
        }
        //Check for negative bets
        else if (bet < 0) {
            std::cout << "Error, your bet must be greater than 0." << std::endl;
            continue;
        }
        //Whenever the user bets, the balance is deducted.
        balance -= bet;
        
        //Spin the slot machine by calling spin function and assigning results to each symbol variable
        symbol1 = spin();
        symbol2 = spin();
        symbol3 = spin();
        symbol4 = spin();
        symbol5 = spin();
        symbol6 = spin();            
        symbol7 = spin();
        symbol8 = spin();
        symbol9 = spin();
        
        //Using the newly assigned symbols, we pass them to the display function to show the slots to the user
        display(symbol1, symbol2, symbol3, symbol4, symbol5, symbol6, symbol7, symbol8, symbol9);
        
        //The struct is used to creat a variable capable of holding a bool, int, and string so it can be set to equal the checkWin function.
        //The function returns the result.win bool, the result.multiplier int, and the result.description string.
        WinResult result = checkWin(symbol1, symbol2, symbol3, symbol4, symbol5, symbol6, symbol7, symbol8, symbol9);
        
        //This if else statement checks if result.win is true, if so then the winnings are calculated and displayed to the user, along with
        //a message of congratulations. After the execution, the loop restarts while the balance > 0.
        if (result.win) {
            int winnings = bet * result.multiplier;
            std::cout << result.description << '\n';
            std::cout << "Congratulations, you won $" << winnings << " dollars!" <<'\n';
            balance += winnings;
        } 
        //If result.win is false this else statement executes and the loop restarts while the balance > 0.
        else 
        {
            std::cout << "Try again!" << '\n';
        }
        //Shows the user their balance at the end of each roll.
        std::cout << "Current balance: $" << balance << std::endl;
    }
    return 0;
}
