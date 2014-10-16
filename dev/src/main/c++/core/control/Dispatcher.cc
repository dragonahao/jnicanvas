#include <Dispatcher.h>
#include <Command.h>


bool Dispatcher :: instanceFlag = false;

Dispatcher* Dispatcher :: dispatcher = NULL;


Dispatcher* Dispatcher :: instance()
{
	if(! instanceFlag)
	{
		dispatcher = new Dispatcher();
		instanceFlag = true;
		return dispatcher;
	}
	else
	{
		return dispatcher;
	}
}


int Dispatcher :: submit(Command * command)
{
	command->execute();

	cmdQueue.push_back(command);
	cmdHistory.push_back(command);

	return cmdHistory.size();
}


string Dispatcher :: listHistory(void)
{
	string result = "";
	for (int i=0; i<cmdHistory.size(); i++)
		result += cmdHistory[i]->toXML();

	return result;
}


/*  Static function to submit commands*/

int submit(Command * command_)
{
        Dispatcher *dispatcher;
        dispatcher = Dispatcher :: instance();
        return dispatcher->submit(command_) -1;
}


