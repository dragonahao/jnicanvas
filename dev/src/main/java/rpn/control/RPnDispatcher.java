/*
 * Instituto de Matematica Pura e Aplicada - IMPA
 * Departamento de Dinamica dos Fluidos
 *
 * @brief represents the core component for command
 * 	  scheduling , batching and running.
 */

package rpn.core.control;

import rpn.jni.JNIBridge;



public interface RPnDispatcher extends Runnable {

	void prerun();
	void run();
	void postrun();
}


public class LocalDispatcher implements RPnDispatcher {


	private XML commandString_;
	private XML returnString_;


	public LocalDispatcher(XML commandString) {

		commandString_ = commandString.toString();

	}

	public void prerun() {

		RPnApplicationModule.evaluateState(new ReadyState(commandString_));
	}

	public void run() {

		RPnApplicationModule.evaluateState(new StartState(commandString_));
		returnString_ = JNIBridge.dispatchNative(commandString_);
	}

	public void postrun() {

		RPnApplicationModule.evaluateState(new FinishedState(commandString_,returnString_));

	}
}


public class ThreadedLocalDispatcher implements RPnDispatcher {


	private LocalDispatcher local_;
	private	RPnThread localThread_;


	public ThreadedLocalDispatcher(LocalDispatcher local) {

		local_ = local;
	}

	public void prerun() {

		local_.prerun();
	}

	public void run() {

		localThread_ = new RPnThread(local_);
		localThread_.start();
		RPnApplicationModule.evaluateState(new ScheduledState(commandString_));
	}

	public void postrun() {

		localThread_.join();
		local_.postrun();
	}
}

public class BatchDispatcher implements RPnDispatcher {


	public BatchDispatcher(XML commandString) {}

	// TODO
}

#endif control_RPN_DISPATCHER

