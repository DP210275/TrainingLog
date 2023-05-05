Welcome to the Triathlon Training Log!

Here are some things to get you started with how the program works and how to use it!

Getting Started:
    - After unzipping the files into a directory on your Linux machine, navigate to that directory and check that you have all these 
    files by using the "ls" command:
        > EventT.h
        > EventT.cpp
        > trainingLogMERGE.cpp
        > userListT.h
        > userListT.cpp
        > userT.h
        > userT.cpp
        > Makefile
    - Once you've verified these files are in the directory, type the command: "make"
        (This will compile the program into an executable file named "trainingLogMERGE")

Running the Program
    - Make sure the executable has been compiled by typing "ls" to see if the "trainingLogMERGE" executable is there
    - To run the program, simply type "./trainingLogMERGE" on the command line and hit Enter

Logging In
    - Upon starting the program, you will be prompted for your username
    - If you have not used the program before, just enter any username that you will remember: the program will remember you 
    for next time!
    - If the username is new, the program will ask if you would like to create an account. Simply type "Y" or "y" for yes, 
    and "n" or "N" for no. 
        (If you misspelled your username, type "n" and reenter your username)
    
Navigating the Menu
    - When using this program, you will have to navigate different menu options to get to the different features of the program!
    - To select an option, simply type the corresponding number and hit the "Enter" key
    - All menus in this program work like this, so keep this in mind!

Logging an Event
    - On the main menu, type "1" for the Training Log, and hit the "Enter" key
    - To log the different types of events, do the following:
        > For a swim, type "1" and hit Enter
        > For a bike, type "2" and hit Enter
        > For a run, type "3" and hit Enter
    - To return to the Main Menu, type "4" and hit Enter
    - Upon selecting an event to log, enter the following:
        > Type "exit" and hit Enter at any time during the logging process to return to the Training Log menu
        
        > The program will prompt if you would like to use the current date for the date of the event   
            ~ If yes, type "y" and hit Enter
            ~ If no, type "n" and hit Enter 
                * You will then be prompted to enter the month of the event (1 = January, 2 = February, and so on), 
                so do that and hit Enter
                * You will then be prompted to enter the day of the event. Do that, and hit Enter

        > The program will ask for the training week number the event should be associated with
            ~ This is for analysis purposes, however you will have to keep track of what training week you are on
            ~ This can be any number, if this is your first time, start with "1", and hit Enter

        > The program will ask for the workout duration in minutes
            ~ Simply type the minutes of the training, and hit Enter

        > The program will then ask for the distance in miles of the workout
            ~ Simply type this distance, to 2 decimal places if needed (e.g., "1.25" or "1.5" or "1" are all valid), and hit Enter

        > The program will then ask for your average heart rate during the event
            ~ Simply type a number between 100 and 200, and hit Enter
        
        > The program will then ask for any notes you want to log for the event
            ~ Simply type whatever you want here, such as "First event of training week 1", and when you are finished, hit Enter
            ~ You also have the choice to leave this section empty. If so, simply hit Enter

Analyzing Data
    - *** Before attempting to analyze your training events, make sure you have entered at least one event in the Training Log. 
    The Data Analysis will not work without events logged. ***

    - To get to the Data Analysis menu, type "2" and hit Enter on the Main menu
    - To get the average duration, speed, distance, and heart rate for different events, type "1" on the Data Analysis menu, 
    and hit enter.
        > The program will then prompt you for some information before giving you the average
        > Type "exit" at any point to return to the Data Analysis menu
        
        > The program will first prompt you if you'd like the average of all events for all weeks.
            ~ Simply type "y" or "n" depending on what you want to do
        > If no, the program will then prompt for the training week number for analysis
            ~ Simply type a number, and hit Enter
            ~ If no week with that number is present, the program will report it to you and ask for a valid number
        > The program will ask if you want to enter another week for analysis
            ~ Simply type "y" or "n", depending on what you want to do, and then hit Enter
            ~ If you only have 1 week in your log, then it will not let you enter another training week, even if you enter "y"
            ~ If you have multiple weeks and want to enter another one, simply type another valid training week and hit Enter
        > The program will then prompt for the type of event you'd like to analyze
            ~ Simply type "s" for swim, "b" for bike, "r" for run, or "a" for all events, and then hit Enter
        > The program will then output your average heart rate, distance, time, and speed for that week(s)

    - To get the max distance and speed, type "2" on the data analysis menu and hit enter
        > The program will first prompt you to enter a valid training week
            ~ Like the average analysis, type a valid number and hit enter
            ~ If you enter an invalid number, the program will tell you and reprompt for a valid number
        > Then you will be asked if you want to enter another week or not
            ~ Simply type "y" or "n", depending on if you want to or not, and hit enter
            ~ If you do not have any other training weeks logged, the program will let you know and continue with the process
        > Then you will enter the type of event you want to get the max distance and speed of
            ~ Type "s" for swim, "b" for bike, "r" for run, or "a" for all events, and hit Enter
        > The program will then output your max distance and speed for those week(s)!

Checking Your Progress
    - To get to the Check Your Progress feature, type "3" on the main menu, and hit Enter
    - You will then be prompted to enter your swim event speed in MPH
        ~ This will be a number, which can be a decimal, and then hit enter
    - Then you will be prompted to enter your bike event speed in MPH
        ~ This is the same thing as the swim, so a number or a decimal, and hit enter
    - Then you will be prompted to enter your run event speed in MPH
        ~ Do the same thing as the other two events
    - The program will then ask for the comparison goal you would like to compare against
        ~ Type "a" for Beginner, "b" for Intermediate, "c" for Expert, and "d" for a custom goal
            > Beginner targets:
                + Swim: 1mph
                + Bike: 6mph
                + Run: 12mph
            > Intermediate targets:
                + Swim: 2mph
                + Bike: 8mph
                + Run: 16mph
            > Expert targets:
                + Swim: 2.5mph
                + Bike: 20mph
                + Run: 10mph
        ~ If you select "Custom", the following will happen:
            > You will be prompted to enter the swim target you would like 
                + This can be a number or a decimal, and hit enter
            > Then you will be prompted for the bike target
                + Again, can be a number or a decimal, and hit enter
            > Finally, you'll be prompted for a run target
                + Once again, enter a number or a decimal, and hit enter
    - Then the program will output a progress bar, showing how close you are to your selected target!
        ~ You will have to scroll up a little bit to see it, though

Exiting the program
    - You can exit the program in 2 ways:
        ~ Navigate to the main menu, and type "4" to exit, and hit enter
        ~ Simply hit Ctrl+C at any point, and the program will force exit
            > If you have logged any new events, the program will save these events to your account's data file, and then exit.

Other things to note:
    - To check your data file, type "ls" in the program directory
    - To look at your data file, simply type something like "more [your file name]" and hit enter
        ~ Your data file will be your username with "REPO.txt" on the end
            > Ex: haydenREPO.txt
    - The data file will have the following information in the following format on one line:
        ~ [Type of event] ; [Month of event] ; [Day of event] ; [Training week number] ; [Time in minutes] ; 
        [Distance in miles] ; [Speed in mph] ; [Average heart rate] ; [Notes] ;
 