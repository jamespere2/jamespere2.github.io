// Jeremy Mendez, James Perez, Usman Khan
// Project Driver File
#include <iostream>  // Provides cout
#include <cstdlib>   // Provides EXIT_SUCCESS
#include <iomanip>
#include <queue>     // Provides queue
#include "Washing.h" // Provides averager, bool_source, washer
#include "LQueue.h"  // Provides the usage of queue based on linked nodes
using namespace std;

// Non Member function prototype
void car_wash_simulate(unsigned int wash_time, double arrival_prob, unsigned int total_time);
// Precondition: 0 <= arrival_prob <= 1.
// Postcondition: The function has simulated a car wash where wash_time is the
// number of seconds needed to wash one car, arrival_prob is the probability
// of a customer arriving in any second, and total_time is the total number
// of seconds for the simulation. Before the simulation, the function has
// written its three parameters to cout. After the simulation, the function
// has written two pieces of information to cout:
// (1) The number of cars washed, and
// (2) The average waiting time of a customer.
// Begin Main
int main()
{
    int washTime, totalTime;
    double aProbability;

    cout << "This program simulates a car wash.\n"
        << "Which will provide the number of customers serviced in a simulated time.\n"
        << "In addition to giving the average time a customer\n" 
        << "spent waiting for their car to be washed in this simulation.\n";

    cout << "\nEnter time for one wash cycle (must be less than or equal to 600 seconds/10 minutes): ";
    cin >> washTime;

    if (washTime < 60 || washTime > 600)
    {
        cerr << "\nERROR--**Invalid wash cycle time**\n"
            << "**The automated car-wash machinery can only wash a car in 1 to 10 minutes (60 to 600 seconds)**\n" 
            << "**Input the wash cycle time in seconds**" << endl;
        return 0;
    }

    cout << "\nEnter probability of customer arrival (0 <= p <= 1): ";
    cin >> aProbability;

    cout << "\nEnter the total time of car wash simulation: ";
    cin >> totalTime;
    cout << endl << endl;

    car_wash_simulate(washTime, aProbability, totalTime);

    cout << "\nThank you for using this simulation.\n"
        << "Have a nice day!\n";
    
    
    return 0;
}
// Non Member function prototype
void car_wash_simulate(unsigned int wash_time, double arrival_prob, unsigned int total_time)
{
    if (arrival_prob < 0 && arrival_prob > 1)
    {
        cout << "**Invalid input for arrival probability**";
        return;
    }
    double minutes = wash_time / 60;
    cout << "The time it takes to wash on car is " << wash_time
        << " seconds (" << minutes << " minutes)\n";
    
    cout << "The probabilty that a customer arrives is " << arrival_prob << endl;
    minutes = total_time / 60;
    cout << "The total time the car wash will be open is " << total_time
        << " seconds (" << minutes << " minutes)\n";

    washer W = wash_time;
    bool_source A = arrival_prob;
    averager averageTime;

    Que<int> line;

    int carsToService = total_time / wash_time;
   
    int totalArrivalTime = 0;
    int totalWaitTime = 0;
    int endTime = 0;
    int i;
    int counter = 0;
    
    for (i = 0; i < carsToService; i++)
    {
        line.addQ(i);
    }

    while (!line.empty() && total_time >= wash_time)
    {
        counter++;
        
        int arrivalTime = 1;
        cout << "\nCar number " << counter << " has arrived.\n" << endl;

        while (A.query() == false && arrivalTime > 0 && arrivalTime < 3)
        {
            arrivalTime++;
        }
       
        totalArrivalTime += arrivalTime;

        if (counter == 1)
        {
            totalWaitTime = wash_time;
            endTime = wash_time + arrivalTime;
            total_time = total_time - endTime;
        }
        else
        {
            totalWaitTime += wash_time;
            totalWaitTime = totalWaitTime - arrivalTime;
            endTime += wash_time;
            total_time = total_time - wash_time;
        }
        averageTime.next_number(totalWaitTime);

        cout << "This car arrived at " << totalArrivalTime << " seconds.\n";
        cout << "The customer wait time is " << totalWaitTime << " seconds.\n";

        W.start_washing();
        while (W.is_busy())
        {
            W.one_second();
        }
       

        cout << "The time at which this car is done being washed is "
            << endTime << " seconds.\n" << endl;

        line.removeQ();
       

    }
    cout << "There is not enough time left to wash another car.\n"
        << "The car wash will close for today.\n";

    cout << endl << counter << " cars were serviced in total allotted simulation time.\n";


    cout << "The average customer waiting time was " << averageTime.average() << " seconds " 
        << "(approximately " << setprecision(2) << fixed << averageTime.average()/60 << " minutes)"  << endl;

}