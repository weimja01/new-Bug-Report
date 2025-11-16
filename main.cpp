/* Program name: bugreport.cpp
* Author: Jeff Weimer
* Date last updated: 11/15/2025
* Purpose: Bug Report Priority Que demo
*/

#include <iostream>
#include <string>
#include <regex>
#include "BugReport.h"
#include "priorityQueue.h"
#include "unorderedLinkedList.h"

using namespace std;

// Function to validate date format using regex (yyyy-mm-dd)
bool isValidDate(const string& date)
{
    // Regex pattern for yyyy-mm-dd format
    regex datePattern(R"(^\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01])$)");
    return regex_match(date, datePattern);
}

// Function to get bug report input from user
BugReport getBugReportFromUser(int& nextId)
{
    string description, reporter, date;
    int priority;
    
    // Validate date with regex
    do
    {
        cout << "Enter the date of the report (yyyy-mm-dd): ";
        getline(cin, date);
        
        if (!isValidDate(date))
        {
            cout << "The date entered is not valid. Please check that the date entered is in the correct format.\n";
        }
    } while (!isValidDate(date));
    
    cout << "Enter the name of the reporter: ";
    getline(cin, reporter);
    
    cout << "Describe the bug: ";
    getline(cin, description);
    
    cout << "What is the priority 1 - 10 (1 is low, 10 is high): ";
    cin >> priority;
    cin.ignore(); // Clear newline from buffer
    
    return BugReport(nextId++, description, reporter, "In Progress", priority, date);
}

int main()
{
    priorityQueueType<BugReport> bugQueue;
    unorderedLinkedList<BugReport> completedBugs;
    int nextId = 1;
    int choice;
    
    do
    {
        cout << "Please choose from the following menu: \n";
        cout << "1. Enter Bug Report\n";
        cout << "2. Distribute Bug Report\n";
        cout << "3. Quit\n\n";
        cin >> choice;
        cin.ignore(); // Clear newline from buffer
        
        switch (choice)
        {
            case 1:
            {
                // Enter bug report
                BugReport newBug = getBugReportFromUser(nextId);
                bugQueue.enqueue(newBug);
                break;
            }
            
            case 2:
            {
                // Distribute bug report
                if (bugQueue.isEmptyQueue())
                {
                    cout << "No bug reports in queue.\n\n";
                }
                else
                {
                    BugReport bug = bugQueue.dequeue();
                    // Display with current status (In Progress)
                    cout << "Bug Report:\n";
                    cout << bug << "\n";
                    // NOW change to Finished before storing
                    bug.setStatus("Finished");
                    completedBugs.insert(bug);
                }
                break;
            }
            
            case 3:
            {
                // Quit display
                cout << "Quitting: \n\n";
                
                cout << "List of Finished Bug Reports: \n\n";
                if (!completedBugs.isEmptyList())
                {
                    //Print()
                    completedBugs.print(cout, "\n");
                }
                
                cout << "List of Unfinished Bug Reports: \n\n";
                if (!bugQueue.isEmptyQueue())
                {
                    while (!bugQueue.isEmptyQueue())
                    {
                        BugReport bug = bugQueue.dequeue();
                        bug.setStatus("new");
                        cout << bug << "\n\n";
                    }
                }
                break;
            }
            
            default:
                cout << "Invalid choice. Please try again.\n\n";
                break;
        }
        
    } while (choice != 3);
    
    return 0;
}