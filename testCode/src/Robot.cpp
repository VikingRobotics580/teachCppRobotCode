//2017 RoboCode v3.0.0 Source Code
//PROJECT: testCode
#include <WPILib.h> // Worchester Polytechnic Institute (WPI) Library for Robot classes, AKA: ALL the robot shit
#include <cmath>    //Cuz math is fun!


/*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *
 *                         ROBOT LOAD ORDER                                    *
 * The Robot Load Order (RLO for short), is how the robot switches from one    *
 * mode to another (E.X: Autonomous -> Teleop).                                *
 *                                                                             *
 * The RLO (after Calling START_ROBOT_CLASS) is as follows:                    *
 *                                                                             *
 * Constructor -> RobotInit -> DisabledInit -> DisabledPeriodic                *
 *                                                                             *
 *                                                                             *
 * When the robot wants to change modes, here is how it does it:               *
 *                                                                             *
 * CurrentMode(Periodic) -> NextMode(Init) -> NextMode(Periodic)               *
 *                                                                             *
 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  */

//the code really starts about here

class Robot : public IterativeRobot { //This is our robot...in code form...just roll with me
    public:
    Robot():
            IterativeRobot(), //constructor
            //These constructions are given the number of the PWM or DIO port on the roboRio
            //*****Variables/objects are defined at the bottom, in the PRIVATE modifier.****
			//PWM Ports:
     /*1*/  frontLeft(0),   //port 0
     /*2*/  backLeft(1),    //port 1
     /*3*/  frontRight(2),  //port 2
     /*4*/  backRight(3),   //port 3
     /*5*/  clock(),
	               //DIO Ports:
     /*6*/  inputA(0),     //port 0
     /*7*/  inputB(1),     //port 1
     /*8*/  inputC(2),     //port 2
     /*9*/  lights(3)
        {
            // You should only initialize value here. Try not to have any other
            //  executable code here.
    	        // Logan's Translation: Put shit here that needs a "new" keyword!
            joy = new Joystick(0);  //Drive Joystick
            drive = NULL;           //We don't want our robot moving YET
        }
        void RobotInit() {
            // Initialize the Robot and all functions that need to be called.
        	    // Logan Translation: Robot needs to wake the fuck up!
            drive = new RobotDrive(frontLeft, backLeft, frontRight, backRight); //So...we can't use this anymore....fuck me
            drive->SetSafetyEnabled(false); // This is dangerous, but our robot
                                            //  has some problems and needs
                                            //  this. (He's been seeing a psychiatrist for years, poor thing!)
        }
        void AutonomousInit() {
            // Here is where you would initialize all of your autonomous code
            clock.Reset(); //Resets time before starting from 0s
            clock.Start(); //Starts the timer from 0s
        }
        void AutonomousPeriodic() {
            /*Here is where you would put all of your autonomous code.
            ***It is important to note that all code here will run as though
             autonomous mode is endless, so you have to carefully time how
             long your code will run for***
            */

        }
        void TeleopInit() {
            clock.Reset(); //This is so we can reset Autonomous mode through TeleOp for testing
        }
        void TeleopPeriodic() {
            /*Drive Train Code*/

           // ***During Teleop we want to pass Mecanum Drive the joystick axes.
        	   // Logan's Translation: We wanna use our joysticks now!

            drive->MecanumDrive_Cartesian(joy->GetX(), joy->GetY(),
                                          joy->GetTwist(), 0.0f); //BUT THIS STILL WORKS!!!...I hope

            /*Component*/
            //Insert code here

            /*Component 2*/
            //Insert code here

            //etc; make as many components as you want!

            /*Debug for switch control; just hook up a light!*/
            if(inputA.Get()){
                if(inputB.Get()){
                    lights.Set(1);
                } else {
                    lights.Set(0);
                }
            } else if (inputB.Get()){
                    lights.Set(0.5);
            } else {
                lights.Set(-1.0);
            }
        }
        void DisabledInit() {
            // Anything you need to initialize in disabled mode
        }
        void DisabledPeriodic() {
            // This method runs periodically during disabled mode. However, you
            //  cannot do any sort of movement code in here legally, so it is
            //  only here for some basic error and logging utility. (or LIGHTS!!!!! :DDDDD )
            // Also, during this mode the motors are completely disabled during
            //  this mode anyway, so don't bother (Stupid FRC!)
        }
    private:
        //Logan's important note: The order you declare these privates MATTERS. Make sure you declare them in same same order as Public!
        Joystick* joy;       //Drive Joystick
        RobotDrive* drive;   //Drive Train
 /*1*/  Talon frontLeft;     //Front-left Mecanum wheel
 /*2*/  Talon backLeft;      //Back-left Mecanum wheel
 /*3*/  Talon frontRight;    //Front-right Mecanum wheel
 /*4*/  Talon backRight;     //Back-right Mecanum wheel
 /*5*/  Timer clock;         //Creates the clock object used for getting time
 /*6*/  DigitalInput inputA; //Input for DIO port 0 from a switch
 /*7*/  DigitalInput inputB; //Input for DIO port 1 from a switch
 /*8*/  DigitalInput inputC; //Input for DIO port 2 from a switch
 /*9*/  Talon lights;        //So, we're controlling our lights using a "motor"...just roll with it
};
START_ROBOT_CLASS(Robot); //Logan's Translation: Hey, robot! This was actually all a dream! now,
                         //remember everything we told you, and for reals this time, WAKE THE FUCK UP! GO! GO! GO!
