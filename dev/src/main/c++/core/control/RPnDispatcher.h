/*
 * Instituto de Matematica Pura e Aplicada - IMPA
 * Departamento de Dinamica dos Fluidos
 *
 * @brief represents the native component for 
 *  	  local dispatching of commands
 */

#ifndef control_RPN_DISPATCHER
#define control_RPN_DISPATCHER

namespace core {
	namespace control {


class RPnDispatcher {

	public :

	
		RPnDispatcher(XML commandString);
		virtual ~RPnDispatcher();

		void prerun();
		void run();
		void postrun();
		
	private :

		RPnCommand command_;
		XML commandString_;
		XML resultString_;
	
	public :

	RPnDispatcher(XML commandString) : 
		commandString_(commandString) {

	}
	
	void RPnDispatcher::prerun() {

		RPnVisualizationModule::evaluateState(new ReadyState(commandString_));
		RPnControlModule::evaluateState(new ReadyState(commandString_));

		command_ = RPnCommand.parseCommand(commandString_);
	}

	void RPnDispatcher::run() {

		RPnVisualizationModule::evaluateState(new StartState(commandString_));
		RPnControlModule::evaluateState(new StartState(commandString_));

		resultString_ = command_.run();
	}

	void RPnDispatcher::postrun() {

		RPnVisualizationModule::evaluateState(new FinishedState(commandString_,returnString));
		RPnControlModule::evaluateState(new FinishedState(commandString_,returnString));
	}
}

	} // core

} // control









