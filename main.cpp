/* Program name: bugreport.cpp
* Author: Jeff Weimer
* Date last updated: 11/15/2025
* Purpose: Bug Report Priority Que demo
*/
//cache problem
#include <iostream>
#include <limits>
#include "BugReport.h"
#include "unorderedLinkedList.h"
#include <regex>
#include "priorityQueue.h"
//

using namespace std;

BugReport getBugReportFromUser(int& nextId);
bool isValidDate(const string& date);


int main()

{
    priorityQueueType<BugReport> bugQueue;
    unorderedLinkedList<BugReport> completedBugs;
    int nextID = 1;
    int choice;

    do
    {
        cout << "Please choose from the following menu: \n";
        cout << "1. Enter Bug Report\n";
        cout << "2. Distribute Bug Report\n";
        cout << "3. Quit\n\n";
        cin >> choice;
        cin.ignore(); 

        switch (choice)
        {   //enter bug report
            case 1:
            {
                BugReport newBug = getBugReportFromUser(nextID);
                bugQueue.enqueue(newBug);
                break;
            }
            // distribute the bug report
            case 2:
            {
                if(bugQueue.isEmptyQueue())
                {
                    cout <<"No bug reports in queue.\n\n";
                }
                else
                {
                    BugReport bug = bugQueue.dequeue();
                    cout << "Bug Report:\n";
                    cout << bug << "\n";
                    //add it to completed list
                    completedBugs.insert(bug);
                }
                break;
            }
            //quit display
            case 3:
            {
                cout << "Quitting: \n\n";
                //finished bug reports
                cout << "List of Finished Bug Reports: \n\n";
                if(!completedBugs.isEmptyList())
                {
                    for (auto it = completedBugs.begin(); it != completedBugs.end(); ++it)
                    {
                        BugReport finishedBug = *it;
                        finishedBug.setStatus("Finished");
                        cout << finishedBug << "\n";
                    }
                }

                //unfinished bug reports
                cout << "List of Unfinished Bug Reports: \n\n";
                if(!bugQueue.isEmptyQueue())
                {
                    while(!bugQueue.isEmptyQueue())
                    {
                        BugReport bug = bugQueue.dequeue();
                        bug.setStatus("New");
                        cout << bug << "\n\n";
                    }
                }

                break;
            }

            default:
                cout << "Invalid Choice. Please try again. \n\n";
                break;
        } 

    } while (choice != 3);
    return 0;
}

BugReport getBugReportFromUser(int &nextId)
{
    string description, reporter, date;
    int priority;

    do
    {
       cout <<"Enter the date of the report (yyyy-mm-dd): ";
       getline(cin,date);

       if(!isValidDate(date))
       {
        cout <<"The Date entered is not valid. Please check that the date entered is in the correct formt. \n";
       }
    } while(!isValidDate(date));

    cout << "Enter the name of the reporter: ";
    getline(cin, reporter);

    cout << "Describe the bug: ";
    getline(cin, description);

    cout << "What is the priority 1 - 10 (1 is low, 10 is high): ";
    cin >> priority;
    cin.ignore();

    return BugReport(nextId++, description, reporter, "In Progress", priority, date);
    
    
}

bool isValidDate(const string &date)
{
    regex datePattern(R"(^\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01])$)");
    return regex_match(date, datePattern);
}
