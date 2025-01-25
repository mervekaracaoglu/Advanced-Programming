#include <iostream>
using namespace std;
#include <thread>
#include <mutex>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <random>
#include <vector>

mutex myMutex, coutMutex;
int target;
int winner_id = -1;


int random_range(const int & min, const int & max) {
    static mt19937 generator(time(0));
    uniform_int_distribution<int> distribution(min,max);
    return distribution(generator);
}

void player(int playerId, int low, int high, bool & round_on, bool & correct_guess)
{
    while(round_on)
    {
        time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
        auto *ptm = new struct tm;
        localtime_s(ptm, &tt);
        myMutex.lock();
        int guess = random_range(low, high);
        myMutex.unlock();

        if (!correct_guess && guess == target) {
            myMutex.lock();// Only enter if no correct guess has been made yet
            correct_guess = true;
            round_on = false;
            winner_id = playerId;
            myMutex.unlock();// Only enter if no correct guess has been made yet


            coutMutex.lock();
            cout << "Player with id " << playerId << " guessed " << guess << " correctly at: " << put_time(ptm, "%X") << endl;
            coutMutex.unlock();

        }
        else
        {
            myMutex.lock();// Only enter if no correct guess has been made yet
            round_on = true;
            correct_guess = false;
            myMutex.unlock();// Only enter if no correct guess has been made yet


            coutMutex.lock();
            cout << "Player with id " << playerId << " guessed " << guess << " incorrectly at: " << put_time(ptm, "%X") << endl;
            coutMutex.unlock();
        }

        this_thread::sleep_for(chrono::seconds(1));
    }
}


void host(int low, int high, int no_of_rounds, vector<int> &scores, bool & round_on, bool & correct_guess)
{
    for (int round = 0; round < no_of_rounds; round++)
    {
        myMutex.lock();
        time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
        auto *ptm1 = new struct tm;
        localtime_s(ptm1, &tt);
        target = random_range(low, high);

        myMutex.unlock();

        coutMutex.lock();
        cout << "--------------------------------------------------- " << endl;
        cout << "Round " << round + 1 << " started at: " << put_time(ptm1, "%X") << endl;
        cout << "Target is " << target << endl;
        coutMutex.unlock();

        myMutex.lock();

        scores[winner_id]++;
        correct_guess = true;
        round_on = false;

        myMutex.unlock();
    }
    coutMutex.lock();
    cout << "Game is over!" << endl;
    cout << "Leaderboard: " << endl;
    for (int score : scores) {
        cout << "Player " << score << " has won " << scores[score] << " times" << endl;
    }
    cout << endl;
    coutMutex.unlock();

}

int main()
{
    int player_num;
    cout << "Please enter number of players" << endl;
    cin >> player_num;

    while(player_num < 1 )
    {
        cout << "Please enter number of players" << endl;
        cin >> player_num;
    }

    int round_num;
    cout << "Please enter number of rounds" << endl;
    cin >> round_num;
    while(round_num < 1)
    {
        cout << "Please enter number of rounds" << endl;
        cin >> round_num;
    }

    int low, high;
    cout << "Please enter the randomization range" << endl;
    cin >> low >> high;
    while(high < low )
    {
        cout << "Please enter the randomization range" << endl;
        cin >> low >> high;
    }

    bool round_on = true;
    bool correct_guess = false;

    vector<int> scores(player_num, 0);

    time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
    auto *ptm2 = new struct tm;
    localtime_s(ptm2, &tt);
    cout << endl;
    cout << endl;
    cout << "--------------------------------------------------- " << endl;
    cout << "Game started at: "<< put_time(ptm2,"%X") << endl;
    cout << "Round 1 will start 3 seconds later" << endl;

    this_thread::sleep_for(chrono::seconds(3));

    thread host_thread(&host, low, high,round_num, ref(scores), ref(round_on), ref(correct_guess));


    vector<thread> player_threads;
    for (int i = 0; i < player_num; ++i)
    {
        player_threads.emplace_back(player, i, low, high, ref(round_on), ref(correct_guess));
    }

    for (int i = 0; i < player_num; ++i)
    {
        player_threads[i].join();
    }
    host_thread.join();



    cout << "Game is over!" << endl;
    cout << "Leaderboard: " << endl;
    for (int i = 0; i < player_num; ++i) {
        cout << "Player " << i << " has won " << scores[i] << " times" << endl;
    }

    return 0;


}
