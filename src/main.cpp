#include "bits/stdc++.h"
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

int main()
{
    string jsonFileName, PATH;

    // jsonFileName = "2.json";
    // jsonFileName = "7.json";
    // jsonFileName = "2627.json";
    // jsonFileName = "10780.json";
    // jsonFileName = "13116.json";
    // jsonFileName = "14842.json";
    // jsonFileName = "17172.json";
    // jsonFileName = "20566.json";
    // jsonFileName = "21632.json";
    // jsonFileName = "27366.json";
    // jsonFileName = "29127.json";
    // jsonFileName = "30024.json";
    // jsonFileName = "30332.json";
    // jsonFileName = "31870.json";
    // jsonFileName = "33550.json";
    // jsonFileName = "34407.json";
    // jsonFileName = "34429.json";
    // jsonFileName = "36495.json";
    jsonFileName = "37327.json";
    // jsonFileName = "38639.json";

    PATH = "../data/" + jsonFileName;
    
    ifstream jsonInput(PATH);//reading json file
    json jsonObj; //declaring a json object 
    //the 'json' keyword is defined in "json.hpp" header file

    jsonInput >> jsonObj; // assigning json data from input file to jsonObj

    map<int, string> dayIdToDate;
    for(auto i : jsonObj["calendar"]["dateToDayId"].items()){
        dayIdToDate[i.value()] = i.key();//mapping dayId with date 
    }

    map<int, int> userIDToMealCount;
    typedef vector<pair<int,int> > vii;
    vii userMeals;
    map<string, vii> dayToUserMeals;

    for(auto i : jsonObj["calendar"]["daysWithDetails"].items()){
        json temp1 = i;
        for(auto j : temp1[i.key()]["details"]["mealsWithDetails"].items()){
            json temp2 = j;
            int userId = temp2[j.key()]["meal"]["userId"];
            userIDToMealCount[userId]++;//counting meals per user at a specific date
        }
        for(auto k : userIDToMealCount){
            userMeals.push_back(make_pair(k.first, k.second));
        }
        int dayId = temp1[i.key()]["day"]["id"];
        dayToUserMeals[dayIdToDate[dayId]] = userMeals;
        
        userIDToMealCount.clear();
        userMeals.clear();
    }
    // for(auto i : dayToUserMeals){
    //     cout << i.first << " : " << endl;
    //     vii temp = i.second;
    //     for(auto j : temp){
    //         cout << "userID : " << j.first << "  mealCount : " << j.second << endl;
    //     }
    //     cout << endl;
    // }

    string status, startDate, endDate;
    cin >> status >> startDate >> endDate;//input
    /* sample input : 
        active 2016-09-01 2016-09-08

        superactive 2016-09-01 2016-09-08

        bored 2016-09-01 2016-09-08
    */

    //check "active"
    userIDToMealCount.clear();
    if(status=="active"){

        vector<int> activeUserIDs;
        //counting from start date to end date
        for(auto it : dayToUserMeals){
            string currentDate = it.first;
            if(startDate <= currentDate && currentDate <=endDate){
                if(currentDate > endDate) break;
                vii temp = it.second;
                for(auto i : temp){
                    userIDToMealCount[i.first] += i.second;
                }
            }
        }

        for(auto i : userIDToMealCount){
            if(i.second >= 5) activeUserIDs.push_back(i.first); 
        }
        //printing active userID
        for(int i = 0; i<activeUserIDs.size(); i++){
            if(i<activeUserIDs.size()-1) cout << activeUserIDs[i] << ", ";
            else cout << activeUserIDs[i] << endl;
        }
    }

    //check "superactive"
    else if(status=="superactive"){
        vector<int> superactiveUserIDs;
        //counting from start date to end date
        for(auto it : dayToUserMeals){
            string currentDate = it.first;
            if(startDate <= currentDate && currentDate <=endDate){
                if(currentDate > endDate) break;
                vii temp = it.second;
                for(auto i : temp){
                    userIDToMealCount[i.first] += i.second;
                }
            }
        }

        for(auto i : userIDToMealCount){
            if(i.second > 10) superactiveUserIDs.push_back(i.first); 
        }
        //printing superactive userID
        for(int i = 0; i<superactiveUserIDs.size(); i++){
            if(i<superactiveUserIDs.size()-1) cout << superactiveUserIDs[i] << ", ";
            else cout << superactiveUserIDs[i] << endl;
        }
    }
    //check "bored"
    if(status=="bored"){
        string earliestDate = jsonObj["earliestDate"];
        // cout << earliestDate << endl;
        vector<int> boredUserIDs;
        //counting from earliest date to start date
        for(auto it : dayToUserMeals){
            string currentDate = it.first;
            if(earliestDate <= currentDate && currentDate <=startDate){
                if(currentDate > startDate) break;
                vii temp = it.second;
                for(auto i : temp){
                    userIDToMealCount[i.first] += i.second;
                }
            }
        }

        map<int, int> isActiveBefore;
        for(auto i : userIDToMealCount){
            if(i.second >= 5) isActiveBefore[i.first] = 1; 
        }

        userIDToMealCount.clear();
        //counting from start date to end date
        for(auto it : dayToUserMeals){
            string currentDate = it.first;
            if(startDate <= currentDate && currentDate <=endDate){
                if(currentDate > endDate) break;
                vii temp = it.second;
                for(auto i : temp){
                    userIDToMealCount[i.first] += i.second;
                }
            }
        }
        for(auto i : userIDToMealCount){
            if(i.second < 5 && isActiveBefore[i.first]==1) boredUserIDs.push_back(i.first); 
        }
        //printing bored userID
        for(int i = 0; i<boredUserIDs.size(); i++){
            if(i<boredUserIDs.size()-1) cout << boredUserIDs[i] << ", ";
            else cout << boredUserIDs[i] << endl;
        }
    }
    system("pause"); 
}
