## Possible Correction in Main::run()

___

1.  Main::run calls checkCommsCriticalFailure() for the state it is in. 
    If multiple failures occur it will fail to capture them both at the same time. **[See Image 1]**
2. If both the navigation and the comms modules have a critical failure checkCriticalFailure will return true for comms, which will stop the method from checking, and returning true for navigation. **[See Image 2]**

We, State Machines, are proposing that instead of having Main::run() check if each module has a critical failure and solving it one at a time. Instead it will highlight and aim to correct each critical failure for each module in unison.