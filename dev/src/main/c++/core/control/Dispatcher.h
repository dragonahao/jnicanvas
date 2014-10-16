#ifndef _Dispatcher
#define _Dispatcher

#include <vector>
#include <Command.h>

using namespace std;


//
// IMPORTANT!! This implementation is NOT thread safe!
//             Google for an example of a thread safe one.
//

class Dispatcher
{
private:
	// Desired behavior : queue should be consumed as commands end (not implemented!)
	//                    history should stay for session saving
	vector <Command *> cmdQueue;
	vector <Command *> cmdHistory;
	//vector <Curve> resultQueue;
	//vector <Curve> resultHistory;

	static bool instanceFlag;
	static Dispatcher *dispatcher;
	Dispatcher() { /* private constructor */ }

public:
	static Dispatcher* instance();
	int submit(Command * command);
	string listHistory(void);

};

#endif


/*  Static function to submit commands */

int submit(Command * command_);
