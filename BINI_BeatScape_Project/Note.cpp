#include "Note.h"

namespace BINI
{
	Note::Note(int release)
	{
		noteYPos = 0;

		releaseDuration = release;

		isAlive = true;
		
	}
}