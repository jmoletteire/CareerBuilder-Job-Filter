#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <iterator>
#include <chrono>
#include <stack>
#include <queue>

using namespace std;
typedef chrono::steady_clock Clock;

//Rayyan Merchant
//Jack Moletteire
//Cody Sauermann

struct Filters {
    bool jobTitleActive = false;
    bool cityActive = false;
    bool stateActive = false;
    bool companyNameActive = false;
    bool postDateActive = false;
    bool salaryActive = false;
    string jobTitle;
    string city;
    string state;
    string companyName;
    string postDate;
    string salary;
    int totalFilterCount;
    Filters() {
        totalFilterCount = 0;
    }
};

string toLowerCase(string str) {
    string returnStr = "";
    for(int i = 0; i < str.size(); i++) {
        returnStr += tolower(str[i]);
    }
    return returnStr;
}

class Job //job class
{
private:
    //these correspond, respectively, to each of the constructor parameters
    string cit;
    string stat;
    //string count;
    string pos;
    string salar;
    //string postlan;
    string tie;
    string comp;

public:
    string uniq;
    void printJob();
    int calculateWeight(Job newer);
    bool checkFilters(Filters filters);
    Job();
    Job(string uniqid, string city, string state, string post, string salary, string title, string company);
};

void Job::printJob() //prints out the job
{
    cout<<"ID: " << uniq << endl;
    cout<<"State: " << stat << endl;
    //cout<<"Country: " << count << endl;
    cout<<"Salary: " << salar << endl;
    cout<<"Job Title: " << tie << endl;
    cout<<"Company: " << comp << endl;
    cout << endl;
}
int Job::calculateWeight(Job newer) //compares this to the job that has been passed in to calculate the weight
{
    int output = 1;
    if (this->cit != newer.cit)
    {
        output++;
    }
    if (this->stat != newer.stat)
    {
        output++;
    }
    if (this->pos != newer.pos)
    {
        output++;
    }
    if (this->salar != newer.salar)
    {
        output++;
    }
    if (this->tie != newer.tie)
    {
        output++;
    }
    if (this->comp != newer.comp)
    {
        output++;
    }
    return output;
}
Job::Job()
{
    uniq = "";
    cit = "";
    stat = "";
    //count = "";
    pos = "";
    salar = "";
    //postlan = "";
    tie = "";
    comp = "";
}
Job::Job(string uniqid, string city, string state, string post, string salary, string title, string company)
{
    uniq = uniqid;
    cit = city;
    stat = state;
    //count = country;
    pos = post;
    salar = salary;
    //postlan = postlang;
    tie = title;
    comp = company;
}
bool Job::checkFilters(Filters filters) {
    int tempCount = 0;
    if(filters.jobTitleActive) {
        string tempTie = toLowerCase(tie);
        if (tempTie.find(filters.jobTitle) != string::npos)
            tempCount += 1;
    }
    if(filters.cityActive) {
        string tempCit = toLowerCase(cit);
        if(tempCit.find(filters.city) != string::npos)
            tempCount += 1;
    }
    if(filters.stateActive) {
        string tempStat = toLowerCase(stat);
        if(tempStat.find(filters.state) != string::npos)
            tempCount += 1;
    }
    if(filters.companyNameActive) {
        string tempComp = toLowerCase(comp);
        if(tempComp.find(filters.companyName) != string::npos)
            tempCount += 1;
    }
    if(filters.postDateActive) {
        string tempPos = toLowerCase(pos);
        if(tempPos.find(filters.postDate) != string::npos)
            tempCount += 1;
    }
    if(filters.salaryActive) {
        if(salar.find(filters.salary) != string::npos)
            tempCount += 1;
    }
    if(tempCount == filters.totalFilterCount){
        return true;
    }
    else {
        return false;
    }
}

void BFS(map<string, vector<pair<string, int>>>& graph, vector<Job>& alljobs, Filters& filters) {
    set<string> visited; // id's that have been visited
    queue<string> q; // id's still to be visited
    vector<pair<string, int>> neighbors;

    // insert source vertex
    for (auto v : alljobs) {
        if (v.checkFilters(filters)) {
            for (auto g : graph) {
                if (g.first == v.uniq) {
                    q.push(v.uniq);
                    visited.insert(v.uniq);
                    break;
                }
            }
        }
    }

    while (!q.empty()) {
        string id = q.front();
        for (auto v : alljobs) {
            if (v.uniq == id && v.checkFilters(filters)) {
                v.printJob(); // output details
                for (auto g : graph) {
                    if (g.first == v.uniq) {
                        neighbors = g.second;
                        break;
                    }
                }
            }
        }
        q.pop();

        for (auto x : neighbors) {
            if (visited.find(x.first) == visited.end()) {
                visited.insert(x.first);
                q.push(x.first);
            }
        }
    }
}

void DFS(map<string, vector<pair<string, int>>>& graph, vector<Job>& alljobs, Filters& filters) {
    set<string> visited; // id's that have been visited
    stack<string> s; // id's still to be visited
    vector<pair<string, int>> neighbors;

    // insert source vertex
    for (auto v : alljobs) {
        if (v.checkFilters(filters)) {
            for (auto g : graph) {
                if (g.first == v.uniq) {
                    s.push(v.uniq);
                    visited.insert(v.uniq);
                    break;
                }
            }
        }
    }

    while (!s.empty()) {
        string id = s.top();
        for (auto v : alljobs) {
            if (v.uniq == id && v.checkFilters(filters)) {
                v.printJob(); // output details
                for (auto g : graph) {
                    if (g.first == v.uniq) {
                        neighbors = g.second;
                        break;
                    }
                }
            }
        }
        s.pop();

        for (auto x : neighbors) {
            if (visited.find(x.first) == visited.end()) {
                visited.insert(x.first);
                s.push(x.first);
            }
        }
    }
}

int main() {


    string temp = "";
    //these 9 strings refer to the 9 constructor values
    map<string, int> lists = {{"uniq_id\":",        10},
                              {"city\":",           7},
                              {"state\":",          8},
                              {"post_date\":",      11},
                              {"salary_offered\":", 16},
                              {"job_title\":",      12},
                              {"company_name\":",   15}};

    int weight = 0;
    int x = 0;
    int index = 0;
    int end = 0;

    vector<Job> alljobs;
    map<string, vector<pair<string, int>>> graph;

    //NOTE: We did try using an actual JSON library for c++ instead of hard coding to find the data, but we ran into several errors with the library and there
    //were not any other good alternatives so we decided to do this instead
    ifstream jobs_file;
    jobs_file.open("joblisting.ldjson", ios::in);

    map<string, int>::iterator it = lists.begin();
    string temporary = "";
    Job hello;
    auto t1 = Clock::now();
    while (getline(jobs_file, temp)) {
        it = lists.begin();
        string one = "";
        string two = "";
        string three = "";
        //string four= "";
        string five = "";
        string six = "";
        //string seven= "";
        string eight = "";
        string nine = "";
        //cout<<index;
        //cout<<" ";
        //cout<<end;
        //cout<<endl;
        //cout<<temp;
        x = x + 1;
        //cout<<x;
        //cout<<endl;

        //if the line is a valid line, meaning it has a job listing in it with a unique id
        index = temp.find("uniq_id\":");
        if (index != string::npos) {
            //go through the map which has the text we're looking for and iterate through to get every single attribute of the job listing that we need
            while (it != lists.end()) {
                //cout<<it->first;
                //cout<<endl;
                index = temp.find(it->first) + it->second;
                end = temp.find("\",", index);

                //cout<<temp[0,10] << endl;
                if (it->first == "uniq_id\":") {
                    one = string(temp.begin() + index, temp.begin() + end);
                    //cout<<one;
                    //cout<<endl;
                } else if (it->first == "city\":") {
                    two = string(temp.begin() + index, temp.begin() + end);
                } else if (it->first == "state\":") {
                    three = string(temp.begin() + index, temp.begin() + end);
                } else if (it->first == "post_date\":") {
                    five = string(temp.begin() + index, temp.begin() + end);
                } else if (it->first == "salary_offered\":") {
                    six = string(temp.begin() + index, temp.begin() + end);
                } else if (it->first == "job_title\":") {
                    eight = string(temp.begin() + index, temp.begin() + end);
                } else if (it->first == "company_name\":") {
                    nine = string(temp.begin() + index, temp.begin() + end);
                }
                it++;
            }


            hello = Job(one, two, three, five, six, eight, nine);
            alljobs.push_back(hello);
            vector<pair<string, int>> newvector;
            graph.emplace(hello.uniq, newvector);
            //hello.printJob();
            //cout<<one;
            //cout<<endl;

        }


        for (Job a : alljobs) {
            weight = a.calculateWeight(hello);
            if (weight <= 5) {
                graph[a.uniq].push_back(pair<string, int>(hello.uniq, weight));
                graph[hello.uniq].push_back(pair<string, int>(a.uniq, weight));
            }

        }

    }
    auto t2 = Clock::now();
    cout << x;
    cout << " Job Listings Indexed";
    cout << endl;
    cout << "Time Needed to Create Graph: ";
    cout << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count() << " nanoseconds";
    cout << endl;
    //map<string,vector<pair<string,int>>>::iterator its = graph.begin();
    //while(its != graph.end())
    //{
    //  for (pair<string,int> b  : graph[its->first])
    //  {

    //       if (b.second == 2)
    //       {cout<<"yes";}

    //   }

    // }

    bool initiateSearch = false;
    bool programRun = true;
    string userSelectionStr;
    int userSelection;

    while(programRun) {
        Filters filters;
        cout << "       Job Search" << endl;
        cout << "------------------------" << endl;
        cout << "Select filters from the list below" << endl << "Enter 0 when ready to search" << endl;
        while (!initiateSearch) {
            cout << "------------------------" << endl;
            cout << "Select filters to apply:" << endl;
            cout << "1. Job Title" << endl;
            cout << "2. City" << endl;
            cout << "3. State" << endl;
            cout << "4. Company Name" << endl;
            cout << "5. Post Date" << endl;
            cout << "6. Offered Salary" << endl;
            cout << "0. Search" << endl;
            cout << "------------------------" << endl;


            getline(cin, userSelectionStr);
            userSelection = stoi(userSelectionStr);

            if (userSelection == 0) {
                initiateSearch = true;

                /***** Breadth First *****/
                auto t3 = Clock::now();
                BFS(graph, alljobs, filters);
                auto t4 = Clock::now();
                float bfsTime = chrono::duration_cast<chrono::nanoseconds>(t4 - t3).count();
                cout << endl;

                /***** Depth First *****/
                auto t5 = Clock::now();
                DFS(graph, alljobs, filters);
                auto t6 = Clock::now();
                float dfsTime = chrono::duration_cast<chrono::nanoseconds>(t6 - t5).count();
                cout << "Depth First Search Time: ";
                cout << dfsTime << " nanoseconds" << endl;
                cout << "Breadth First Search Time: ";
                cout << bfsTime << " nanoseconds" << endl;
                cout << endl;

            }
            if (userSelection == 1) {
                filters.jobTitleActive = true;
                filters.totalFilterCount += 1;
                cout << "Please enter job title (0 to go back)" << endl;
                getline(cin, filters.jobTitle);
                filters.jobTitle = toLowerCase(filters.jobTitle);
                if (filters.jobTitle == "0") {
                    filters.jobTitleActive = false;
                    filters.totalFilterCount -= 1;
                    cout << "Filter not applied" << endl;
                }
            }
            if (userSelection == 2) {
                filters.cityActive = true;
                filters.totalFilterCount += 1;
                cout << "Please enter city name (0 to go back)" << endl;
                getline(cin, filters.city);
                filters.city = toLowerCase(filters.city);
                if (filters.city == "0") {
                    filters.cityActive = false;
                    filters.totalFilterCount -= 1;
                    cout << "Filter not applied" << endl;
                }

            }
            if (userSelection == 3) {
                filters.stateActive = true;
                filters.totalFilterCount += 1;
                cout << "Please enter state name (0 to go back)" << endl;
                getline(cin, filters.state);
                filters.state = toLowerCase(filters.state);
                if (filters.state == "0") {
                    filters.stateActive = false;
                    cout << "Filter not applied" << endl;
                }
            }
            if (userSelection == 4) {
                filters.companyNameActive = true;
                filters.totalFilterCount += 1;
                cout << "Please enter company name (0 to go back)" << endl;
                getline(cin, filters.companyName);
                filters.companyName = toLowerCase(filters.companyName);
                if (filters.companyName == "0") {
                    filters.companyNameActive = false;
                    filters.totalFilterCount -= 1;
                    cout << "Filter not applied" << endl;
                }
            }
            if (userSelection == 5) {
                filters.postDateActive = true;
                filters.totalFilterCount += 1;
                cout << "Please enter post date (0 to go back)" << endl;
                getline(cin, filters.postDate);
                filters.postDate = toLowerCase(filters.postDate);
                if (filters.postDate == "0") {
                    filters.postDateActive = false;
                    filters.totalFilterCount -= 1;
                    cout << "Filter not applied" << endl;
                }
            }
            if (userSelection == 6) {
                filters.salaryActive = true;
                filters.totalFilterCount += 1;
                cout << "Please enter salary (0 to go back)" << endl;
                getline(cin, filters.salary);
                filters.salary = toLowerCase(filters.salary);
                if (filters.salary == "0") {
                    filters.salaryActive = false;
                    filters.totalFilterCount -= 1;
                    cout << "Filter not applied" << endl;
                }
            }
        }
        cout << "Would you like to perform a new search?" << endl;
        cout << "1. Yes" << endl << "2. No" << endl;
        getline(cin, userSelectionStr);
        if(userSelectionStr == "1") {
            initiateSearch = false;
        }
        else if(userSelectionStr == "2") {
            programRun = false;
        }
    }

    return 0;

}