/*********************************
 **	  Snow Ball Fight RPG		**
 **	Created By Charles Davis	**
 **	CPSC 246-01 Dr. Valentine	**
 ********************************/

// The extra white space at the end of each getType function's returned string
// was added to make the printStatus function look better.  The output is best
// viewed by piping it to a text file. 
//		SnowBallFight.exe > output.txt
// this produces a nice out put of each round.


#include <string>
#include <iostream>
#include <time.h>
using namespace std;


/***************************** Person Class **********************************/
class Person
{
	// private attributes of a person object

	private:
		int ballsInBucket,	// number of snowballs landed in the players bucket
			numInBag,		// number of snowballs in bag to be thrown
			percentAccuracy, // accuracy value
			damageThisRound; // calculated damage this round

	// public functions
	public:
		const static int MAX_HEALTH = 100;

		// default constructor
		Person()
		{
			ballsInBucket = 0;
			numInBag = 10;
			percentAccuracy = 5;
			damageThisRound = 0;
		}
		

		// constructor using health and strength inputs
		Person(int h, int s, int a)
		{
			setNumBallsInBucket(h);
			setNumInBag(s);
			setAccuracy(a);
			damageThisRound = 0;
		}


		// set the health of the person making sure health is valid
		void setNumBallsInBucket(int numBalls)
		{
			if(numBalls < 0)
			{
				numBalls = 0;	// if invalid, health is zero
			}
			else if(numBalls >= 100)
			{
				numBalls = 100;
			}
			else{}
			
			ballsInBucket = numBalls;		// set health to h
		}



		// set the strength of the person making sure strength is valid
		void setNumInBag(int bagNum)
		{
			if(bagNum < 0)
			{
				bagNum = 0;	// if invalid, strength is zero 
			}
			else if(bagNum >= 50)
			{
				bagNum = 50;
			}
			else{}

			numInBag = bagNum;	// set strength to s
		}




		// set the accuracy of this Person
		void setAccuracy(int a)
		{
			if(a < 0)
				a = 0;	// if invalid, set accuracy to 0

			percentAccuracy = a;
		}



		void setDamageThisRound(int damage)
		{
			if(damage >= 0)		// if the damage isn't negative
				damageThisRound = damage;	// set it to given value
		}
		


		// attack function based on ballsInBucket and accuracy
		virtual int attack()
		{	
			double tempAccuracy;	// temp accuracy
			int damage;				// temp damage

			// get random numbers for numInBag and Accuracy
			setNumInBag(getRandomNumberBetween(10,50));
			setAccuracy(getRandomNumberBetween(5,95));

			// turn the accuracy into a percent
			tempAccuracy = percentAccuracy/100.0;

			// the damage is the numInBag time the percentAccuracy rounded up
			damage = int(0.5 + numInBag * tempAccuracy);

			// set damageThisRound to calculated damage
			damageThisRound = damage;	

			return damage;	// also return damage
		}



		// Updates the balls in bucket value based on given damage value
		void receiveDamage(int damage)
		{
			setNumBallsInBucket(ballsInBucket+damage);
		}


 /********************************** getters *********************************/
		int getHealth(){ return ballsInBucket; }
		
		int getStrength(){ return numInBag; }

		int getAccuracy(){ return percentAccuracy; } 

		int getDamageThisRound() { return damageThisRound; }

		// getType is a pure virtual function. Person is an abstract class
		virtual string getType() = 0;

		int getRandomNumberBetween(int low, int high)
		{
			return (rand() % (high-low)) + low;
		}
		
};	// end Person




/***************************** Faculty Class **********************************/
class Faculty : public Person
{
	public:

		// Default constructor calling parent class default
		Faculty() : Person() { /* left blank intentionally */ }
		

		// Argumented constructor calling parent class argumented constructor
		Faculty(int h, int s, int a) : 
			Person (h, s, a){ /*left blank intentionally*/ }


		// getType returns the type of this class that's calling it.
		// it's virtual to allow for polymorphism.  We're interested in the
		// child's type not the parent
		virtual string getType() { return "Faculty           "; }


		// Child's attack function.  It's virtual to all the child to call its
		// own function and not the parent's attack function
		virtual int attack() 
		{
			int damage = Person::attack();  // call parent's attack function
			
			if((rand() % 100) < 50)		// 50% of the time 
				damage = int(.5 + (damage * 1.5));	// damage is 50% extra

			setDamageThisRound(damage);		// set the current damage

			return damage;		// return the calculated damage
		}

}; // end Faculty




/***************************** Student Class **********************************/
class Student : public Person
{
	public:

		// Default constructor calling parent class default
		Student() : Person() { /* left blank intentionally */ }


		// Argumented constructor calling parent class argumented constructor
		Student(int h, int s, int a) : 
			Person(h, s, a){ /*left blank intentionally*/}


		// getType returns the type of this class that's calling it.
		// it's virtual to allow for polymorphism.  We're interested in the
		// child's type not the parent

		// The extra white space in this getType and all subsequent functions
		// was added to make the printStatus function in main look better
		virtual string getType(){ return "Student           "; }


		// Child's attack function.  It's virtual to all the child to call its
		// own function and not the parent's attack function
		virtual int attack() 
		{ 
			// sometimes students party all night or sleep in and are weakened 
			// by 25%

			int damage = Person::attack(); // call the parent's attack function
			
			if((rand() % 100) < 20)		// 20% of the time
				damage = int(.5 + (damage * .75));	// damage is 25% less

			setDamageThisRound(damage);	// set the current damage to calculated
										// damage and the return it
			return damage;
		}

}; // end Student




/*********************** Chemistry Faculty Class *****************************/
class ChemistryFaculty : public Faculty
{
	public:
		
		// Default constructor calling parent class default
		ChemistryFaculty() : Faculty(){/*left blank intentionally*/}
		

		// Argumented constructor calling parent class argumented constructor
		ChemistryFaculty(int h, int s, int a) : 
			Faculty(h, s, a){/*blank intentionally*/}


		// getType returns the type of this class that's calling it.
		// it's virtual to allow for polymorphism.  We're interested in the
		// child's type not the parent
		virtual string getType(){ return "Chemistry Faculty "; }


		// special defense move evaporate snow ball.  reduce damage to zero.
		// Evaporate Snow Ball

		// special attack move called trial and error.  Chemistry Faculty
		// tests the attack value 10 times and returns the biggest -40%

		virtual int attack()
		{
			int damage[10];		// create an integer array of size 10
			int temp;			// temp array for comparing

			for(int i = 0; i < 10; i++)		// fill the array with attacks
				damage[i] = Faculty::attack(); // call the parent's attack 
				
			temp = damage[0];	// temp is the first value in the array

			for(int i = 1; i < 10; i++) // for each
			{
				if(damage[i] > temp)	// if the next damage is bigger
					temp = damage[i];	// make temp this damage
			}

			temp = int(temp * 0.6);		// subtract 40% from the biggest value

			setDamageThisRound(temp);	// set damage this round to temp

			return temp;			// return calculated value

		}

}; // end ChemistryFaculty




/*********************** Chemistry Student Class *****************************/
class ChemistryStudent : public Student
{
	public:

		// Default constructor calling parent class default
		ChemistryStudent() : Student(){ /*left blank intentionally*/}
		

		// Argumented constructor calling parent class argumented constructor
		ChemistryStudent(int h, int s, int a) : 
			Student(h, s, a){/*blank intentionally*/}


		// getType returns the type of this class that's calling it.
		// it's virtual to allow for polymorphism.  We're interested in the
		// child's type not the parent
		virtual string getType(){ return "Chemistry Student "; }
		

		// special attack move informally called phase change. The snowball
		// is hardened and the damage is increase by 50%-100%.  This happens
		// 25% of the time

		virtual int attack()
		{
			int damage = Student::attack();	// call parent's damage function
			double offset =		// calculate random offset between 50-100%
				1.0 + (Person::getRandomNumberBetween(50, 100)/100.0);

			if(rand() % 100 < 25)	// 25% of the time it does 50-100% extra								 
				damage = int(damage * offset);

			setDamageThisRound(damage);	 // set damage this round to damage

			return damage;		// return calculated damage

		}

}; // end ChemistryStudent




/*********************** Psychology Faculty Class *****************************/
class PsychologyFaculty : public Faculty
{
	public:

		// Default constructor calling parent class default
		PsychologyFaculty() : Faculty(){/*left blank intentionally*/}
		

		// Argumented constructor calling parent class argumented constructor
		PsychologyFaculty(int h, int s, int a) : 
			Faculty(h, s, a){/*blank intentionally*/}


		// getType returns the type of this class that's calling it.
		// it's virtual to allow for polymorphism.  We're interested in the
		// child's type not the parent
		virtual string getType(){ return "Psychology Faculty"; }


		
		// Special attack function Called Super Ego.  Psychology Faculty can 
		// control snow with their superior id impulse control.  35% of the
		// Time their accuracy is improve by 60%.  Resisting the urge to 
		// throw snowballs willy nilly they through their bag with great
		// precision and restraint.

		virtual int attack()
		{ 
			int damage = Faculty::attack();	// call parent's attack value

			if((rand() % 100) < 35)		// 35% of the time
				damage = int(damage * 1.6);	// add 60% more damage

			setDamageThisRound(damage);	// set damage this round with damage

			return damage;		// return calculated damage
		}

}; // end PsychologyFaculty




/*********************** Psychology Student Class *****************************/
class PsychologyStudent : public Student
{
	public:
		
		// Default constructor calling parent class default
		PsychologyStudent() : Student(){/*left blank intentionally*/}


		// Argumented constructor calling parent class argumented constructor
		PsychologyStudent(int h, int s, int a) : 
			Student(h, s, a){/*intentionally blank*/}


		// getType returns the type of this class that's calling it.
		// it's virtual to allow for polymorphism.  We're interested in the
		// child's type not the parent
		virtual string getType(){ return "Psychology Student"; }


		// special Rorschach attack.  What does this snow ball splatter look
		// like to you?  Increase the accuracy of attack by throwing 3 balls
		// and averaging their results

		virtual int attack()
		{	
			int damage;
			
			damage = Student::attack();		// attack 1

			damage += Student::attack();	// attack 2
			
			damage += Student::attack();	// attack 3

			damage = int(damage / 3);		// average all three


			setDamageThisRound(damage);  // set damage this round with damage

			return damage;		// return result of average

		}

}; // end PsychologyStudent




/************************* Music Faculty Class *******************************/
class MusicFaculty : public Faculty
{
	public:

		// Default constructor calling parent class default
		MusicFaculty() : Faculty(){/*left blank intentionally*/}
		

		// Argumented constructor calling parent class argumented constructor
		MusicFaculty(int h, int s, int a) : 
			Faculty(h, s, a){/*blank intentionally*/}


		// getType returns the type of this class that's calling it.
		// it's virtual to allow for polymorphism.  We're interested in the
		// child's type not the parent
		virtual string getType(){ return "Music Faculty     "; }

		// increases the attack by creating a wall of sound and sending
		// sending snowballs with the wall to the opponent increasing damage
		// by 100%

		virtual int attack()
		{
			int damage = Faculty::attack(); // call parent's attack function

			if((rand() % 100) < 20)		// 20% of the time
				damage = damage * 2;	// double the damage

			setDamageThisRound(damage);	// set damage this round with damage

			return damage;			// return the calculated damage
		}

}; // end MusicFaculty




/************************* Music Student Class *******************************/
class MusicStudent : public Student
{
	public:

		// Default constructor calling parent class default
		MusicStudent() : Student(){/*left blank intentionally*/}
		

		// Argumented constructor calling parent class argumented constructor
		MusicStudent(int h, int s, int a) : 
			Student(h, s, a){/*blank intentionally*/}


		// getType returns the type of this class that's calling it.
		// it's virtual to allow for polymorphism.  We're interested in the
		// child's type not the parent
		virtual string getType(){ return "Music Student     "; }

		// special attack sonic fury.
		// Student fills his instrument with multiple snowballs and fires
		// them all by playing the instrument.
		virtual int attack()
		{
			int damage = 0;

			// add together 10 snowballs at 20% power
			for(int i = 0; i < 10; i++)	
				damage += int(Student::attack() * .20);

			setDamageThisRound(damage);	// set damage this round with damage

			return damage;	// return calculated damage
		}

}; // end Music Student




/********************************* Team **************************************/
class Team
{
	private: 
		Person** teamArray;		// Pointer to Person pointers for team array
		int numPlayers, currentPlayer;	// number of players and current player

	public:

	Team()		// default constructor that makes a simple two person team of
	{			// one faculty and one student
		setSize(2);
		setCurrentPlayerIndex(0);

		teamArray = new Person*[numPlayers];
		teamArray[0] = new Faculty();
		teamArray[1] = new Student();
	}




	// argumented constructor taking an int size of the team
	Team(int num)
	{
		if(num > 0)	// if the size is at least 1
		{	
			setSize(num);	// set the size
			setCurrentPlayerIndex(0);	// set current player to 0

			teamArray = new Person*[numPlayers]; // allocate new chunk of mem
			initTeam();			// initialize the team with random players
			
		}
		else { cerr << "Invalid team size"; }

	}



	// makeCopy function
	Person* makeCopy(Person* other)
	{
		// Make copy solves the slicing problem when dealing with our derived
		// derived classes and dynamic memory.  When we call the Copy
		// constructor and the assignment operator overload functions we need
		// to make sure we're actually making copies of the arrays and not just
		// having two pointers to the same data.  So we made this function that
		// solves that problem by making copies of the Persons inside the array

		Person* ptr;		// temporary pointer to a generic Person
		string person = other->getType();	// type name of Person passed in


		// huge list of different types of Persons to create space in the 
		// memory for a specific type of Person

		if(person == "Student           ")	
		{
			ptr = new Student();	// new keyword returns a pointer to Object
		}
		else if(person == "Faculty           ")
		{
			ptr = new Faculty();
		}
		else if(person == "Psychology Student")
		{
			ptr = new PsychologyStudent();
		}
		else if(person == "Chemistry Student ")
		{
			ptr = new ChemistryStudent();
		}
		else if(person == "Music Student     ")
		{
			ptr = new MusicStudent();
		}
		else if(person == "Psychology Faculty")
		{
			ptr = new PsychologyFaculty();
		}
		else if(person == "Chemistry Faculty ")
		{
			ptr = new ChemistryFaculty();
		}
		else if(person == "Music Faculty     ")
		{
			ptr = new MusicFaculty();
		}
		else
		{
			ptr = nullptr;	// if it doesn't match any of these make it null
		}

		*ptr = *other;	// now that we have made room for the specific Person
						// dereference ptr and send other's contents to it
						// thus copying the Person object
		return ptr;		// return the copy
		
	}




	// Copy constructor 
	Team(const Team &otherTeam)
	{
		//copy automatic data
		numPlayers = otherTeam.numPlayers;
		currentPlayer = otherTeam.currentPlayer;

		// make a new array of Person pointers of size other.numplayers
		teamArray = new Person*[otherTeam.numPlayers];

		// makeCopy each otherTeam Person into the new array
		for(int i = 0; i < otherTeam.numPlayers; i++)
		{
			teamArray[i] = makeCopy(otherTeam.teamArray[i]);
		}
	}



	// Destructor
	~Team()
	{
		for(int i = 0; i < numPlayers; i++)	// delete each Pointer in teamArray
		{
			delete teamArray[i];			
		}

		delete [] teamArray;	// delete the reference to head of the array
	}



	
	// assignment operator overload the last of the big three
	Team& operator=(const Team& other)
	{
		// if caller isn't trying to assign itself to itself
		if(this != &other)
		{
			// assign automatic variables from other obj to this obj
			numPlayers = other.numPlayers;
			currentPlayer = other.currentPlayer;
				
			// delete the current dynamic stuff
			for(int i = 0; i < numPlayers; i++)
			{
				delete teamArray[i];
			}

			delete [] teamArray;

			// create a new array of Person pointers
			teamArray = new Person*[other.numPlayers];

			// copy other Pointers into this teamArray
			for(int i = 0; i < other.numPlayers; i++)
			{
				teamArray[i] = makeCopy(other.teamArray[i]);
			}
		}
		
		// return the reference of this 
		return *this;
	}



	// Init Team
	void initTeam()
	{
		// Init Team sets up each team with a random set of different types
		// of Persons

		// Consts to make the switch statement more readable
		const int GENERAL_STUDENT = 0;
		const int CHEMISTRY_STUDENT = 1;
		const int PSYCHOLOGY_STUDENT = 2;
		const int MUSIC_STUDENT = 3;
		const int GENERAL_FACULTY = 4;
		const int CHEMISTRY_FACULTY = 5;
		const int PSYCHOLOGY_FACULTY = 6;
		const int MUSIC_FACULTY = 7;

		int playerType;	// player type to switch on

		for(int player = 0; player < numPlayers; player++)
		{
			playerType = rand() % 8;	// random number from 0 to 7

			switch(playerType)	// create a pointer to a specific Person
			{					// and assign it to the teamArray
				case GENERAL_STUDENT:
					teamArray[player] = new Student();
				break;

				case CHEMISTRY_STUDENT:
					teamArray[player] =  new ChemistryStudent();
				break;

				case PSYCHOLOGY_STUDENT:
					teamArray[player] =  new PsychologyStudent();
				break;

				case MUSIC_STUDENT:
					teamArray[player] = new MusicStudent();
				break;

				case GENERAL_FACULTY:
					teamArray[player] = new Faculty();
					break;

				case CHEMISTRY_FACULTY:
					teamArray[player] = new ChemistryFaculty();
					break;

				case PSYCHOLOGY_FACULTY:
					teamArray[player] = new PsychologyFaculty();
					break;

				case MUSIC_FACULTY:
					teamArray[player] = new MusicFaculty();
					break;

				default: break;
			}
		}
	}




	// returns the size of the team
	int size(){ return numPlayers; }



	// set the size of the team if it is not zero
	void setSize(int size)
	{
		if(size > 0)
			numPlayers = size;
		else
			numPlayers = 1;
	}	



	// set the current player index keeping it within range
	void setCurrentPlayerIndex(int index)
	{
		if(index >= 0 && index < numPlayers)
			currentPlayer = index;
		else
			currentPlayer = 0;
	}



	// get next player 
	Person* getNextPlayer()
	{
		// Returns a person pointer to the next player that isn't dead
		// it returns a nullptr if there are no healthy players

		int temp;	// temporary variable for the index of the player to return

			// for the number of players on a team
			for(int i = 0; i < numPlayers; i++)
			{
				// if the current player's health is maxed out
				if(teamArray[currentPlayer]->getHealth() == Person::MAX_HEALTH)
				{
					// move to the next player one the team.  If the the add
					// goes over the number of total players circle back to the
					// beginning of the team
					currentPlayer = (currentPlayer + 1) % numPlayers;
				}
				else
				{	
					// assign temp to the currentplayer. update currentplayer
					temp = currentPlayer;
					setCurrentPlayerIndex(currentPlayer+1);
					return teamArray[temp];  // return player temp in the array
				}
			}

			return nullptr;  // if there are no healthy players return null
	}
	



	// test to see if there is another player left
	bool hasNextPlayer()
	{
		// for every player on the team
		for(int i = 0; i < numPlayers; i++)
		{
			// if they aren't dead return true
			if(teamArray[i]->getHealth() != Person::MAX_HEALTH)
			{
				return true;
			}
		}

		// all players are dead return false
		return false;
	}




	// Returns the player in the array at the given index
	Person* getPlayer(int index)
	{
		return teamArray[index];
	}

};



const static int NUM_PLAYERS = 50;	// num players per team
static int roundCounter = 0;	// I found a use for a static variable!
								// this is used by the printStatus function to
							// keep track of how many times it has been called
int main();
void init();
void printStatus(Team* one, Team* two);
void battle(Person* p1, Person* p2);
bool isGameOver(Person* p1, Person* p2);
	

/*********************************** main ************************************/
int main()
{
	// The main function seed the random number generator for team init and
	// attacking values.  It then sets up the two teams and sends them into
	// battle until at least one of the teams has no healthy players meaning
    // all players on 1 or both teams have 100 snowballs in their bucket.
	// It prints out the status of the game after every round and finally 
	// the winner and final status.


	//Variable dictionary for main

	// seed the random number generator
	srand((unsigned) time(0));

	bool gameOver = false;			// bool testing to see if the game is over

	Team teamOne = Team(NUM_PLAYERS);	// 2 Team objects of size NUM_PLAYERS
	Team teamTwo = Team(NUM_PLAYERS);

	Person* nextPlayerOne = nullptr;	// 2 Person pointers for point to next
	Person* nextPlayerTwo = nullptr;	// player to battle

	int battleCounter = 0;				// number of total battles

	// print out initialization stuff
	init();

	// run game while there are elligible players
	while(!gameOver)
	{
		// 1.0  Input
		nextPlayerOne = teamOne.getNextPlayer();	// getNextPlayer from team1
		nextPlayerTwo = teamTwo.getNextPlayer();	// getNextPlayer from team2


		// 2.0 Process
		gameOver = isGameOver(nextPlayerOne, nextPlayerTwo); //test 4 game over

		if(!gameOver)		// if the game isn't over run battles
		{
			if(battleCounter % NUM_PLAYERS == 0)	// if the number of battles 
			{										// is equal to one round 
				printStatus(&teamOne, &teamTwo);	//print status
			}

			// send a player from each team into battle
			battle(nextPlayerOne, nextPlayerTwo);
			battleCounter++;	// increase the battle count
		}

	}		
		// 3.0 Output
		printStatus(&teamOne, &teamTwo);

		cerr << "<<<<Normal Termination>>>>" << endl;

	return 0;
}



/*********************************** Init ************************************/
void init()
{
	cout << "\n\n\n";
	cout << "\n\n====================================================" << endl;
	cout << "    Charles Davis - CPSC 246.01 - Fall 2014   " << endl;
 	cout << "Snow Ball Fight Role Playing Game Using Polymorphism" << endl;
	cout << "====================================================\n\n" << endl;
}




/******************************** Print Status *******************************/
void printStatus(Team* one, Team* two)
{
	// Prints out a nice chart of each team and its statistics.
	// It then neutralizes dead players by setting their damage to 0

	Person* tempOne;	// 2 temp person pointers
	Person* tempTwo;

	cout << "\n\n\t  R O U N D   #   " << roundCounter << "\n\n";

	cout << "\n*******************************************";
	cout <<   "********************************************";
	cout << "\n||Team One||    ||HitsOnOpp||NumInBucket||";
	cout << "   ||Team Two||    ||HitsOnOpp||NumInBucket||\n";
	cout << "\n*******************************************";
	cout <<   "********************************************";
	cout << "\n\n";

	for(int i = 0; i < NUM_PLAYERS; i++)	// for each player
	{
		tempOne = one->getPlayer(i);	// get that player at pos i
		tempTwo = two->getPlayer(i);	// from each team

		cout << tempOne->getType() << "    ";	// print out type
		cout << tempOne->getDamageThisRound() << " \t";	 // snowballs landed
		cout << tempOne->getHealth() << "\t     ";	// current ball in bucket
		
		cout << tempTwo->getType() << "\t   ";	// repeat for team 2
		cout << tempTwo->getDamageThisRound() << " \t     ";
		cout << tempTwo->getHealth() << "\n ";

		cout << "\n\n\n";

		// if either player died this turn neutralize his damage stat
		if(tempOne->getHealth() == Person::MAX_HEALTH)
			tempOne->setDamageThisRound(0);

		if(tempTwo->getHealth() == Person::MAX_HEALTH)
			tempTwo->setDamageThisRound(0);
	}

	roundCounter++;	 // update the round number
}



/*********************************** Battle **********************************/
void battle(Person* p1, Person* p2)
{
	// the battle function takes to Persons and pits them against each other
	// due to dynamic binding these can be any unique child of the person class

	int damage1 = p1->attack();	//get p1's damage by calling its attack
	int	damage2 = p2->attack();	//get p2's damage by calling its attack

	p1->receiveDamage(damage2); //send damage2 to player 1
	p2->receiveDamage(damage1); //send damage1 to player 2
}



/********************************* isGameOver ********************************/
bool isGameOver(Person* p1, Person* p2)
{
	// This function tests to see if the game is over by testing the value of
	// the person pointers sent to it.  We are treating nullptr as a sentinel
	// value to tell us if the getNextPlayer function has anymore players.
	// It then prints out the winning team to the console or in the event of
	// a tie it prints out it's a tie.  If neither person is a nullptr the
	// game is not over and we return false.


	if(p1 == nullptr && p2 == nullptr)	// if they're both null it is a tie
	{
		cout << "\n\n\n\n\n IT'S A TIE!!!!! \n\n\n\n\n";
		return true;
	}
	else if(p1 == nullptr)	// if p1 is null team 2 wins
	{
		cout << "\n\n\n\n\n TEAM TWO WINS!!!!! \n\n\n\n\n";
		return true;
	}
	else if(p2 == nullptr)	// if p2 is null team 1 wins
	{
		cout << "\n\n\n\n\n TEAM ONE WINS!!!!! \n\n\n\n\n";
		return true;
	}
	else { return false; }	// otherwise the game isn't over

}