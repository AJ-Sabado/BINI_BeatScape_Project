#pragma once

#include "SDL.h"
#include "States.h"
#include "SoundFX.h"
#include "iostream"
#include "string"
#include "LeaderboardManager.h";
#include "ScoreContainer.h"

namespace BINI
{

	//Handles events through SDL event.
	class Events
	{
	public:
		//Events constructor.
		Events();
		
		//Events deconstructor.
		~Events();
		
		//Polls all pending events.
		int pollEvents();

		//Returns event type.
		Uint32 type();

		//Returns key code from an event.
		Uint32 getKey();

		//Returns true if key is polled repeatedly.
		bool repeat();

		//Returns current application state.
		int getCurrentState();

		//Changes application state
		void setState(int state);

		//Stores user data for leaderboard export
		void setUserData( int score, int maxcombo, std::string difficulty = "", float accuracy = 0.f);

		//Stores user initials
		void setUserInitials(std::string initials);

		//Returns user score
		int getUserScore();

		//Returns user max combo
		int getUserMaxCombo();

		//Returns user accuracy
		float getUserAccuracy();

		//Reutrns user initials
		std::string getUserInitials();

		//Returns user difficulty
		std::string getUserDifficulty();

		//exports data to log
		void exportData();

		//Removes previously stored user data
		void clearUserData();

		//Returns scores in the form of a ScoreContainer list
		BINI::ScoreContainer* getScoreList();


	private:

		//SDL event
		SDL_Event e;

		//Current application state
		int currentState;

		//Current User score
		int userScore = 0;

		//Current User max combo
		int userMaxCombo = 0;

		//Current User accuracy
		float userAccuracy = 0.f;

		//Current user difficulty
		std::string userDifficulty = "";

		//Current User Initials
		std::string userInitials = "";

		//Leaderboard file location
		const std::string leadboardPath = "leaderboard/leaderboard.bBoard";

		//Leaderboard manager
		BINI::LeaderboardManager* leaderboardmanager;

		

	};
}



