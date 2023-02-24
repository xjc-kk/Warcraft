#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>

using namespace std;

const vector<string> warriorNames = {"dragon", "ninja", "iceman", "lion", "wolf"};
const vector<string> weaponNames = {"sword", "bomb", "arrow"};

class HeadQuarter {
    private:
        string name;
        int time;
        int totalLife;
        vector<int> warriorLifes;
        vector<int> produceOrder;
        int producePos;
        int warriorCnt;
        map<int, int> warriorMap;
        bool stopped;

    public:
        HeadQuarter(const string& name_, const int& tLife_, const vector<int>& wLifes, const vector<int>& pOrder_);
        string getName() const;
        int getTotalLife() const;
        bool isStopped() const;
        int canProduce();
        void updateStatistics(const int& warrior);
        void produce();
        void print(const bool& stopped, const int& warrior) const;
        void weaponPrint(const int& warrior) const;
        void timeTicks();
};

HeadQuarter::HeadQuarter(const string& name_, const int& tLife_, const vector<int>& wLifes_, const vector<int>& pOrder_) :
name(name_), totalLife(tLife_), warriorLifes(wLifes_), produceOrder(pOrder_) {
    time = 0;
    producePos = 0;
    warriorCnt = 0;
    stopped = false;
}

string HeadQuarter::getName() const {
    return name;
}

int HeadQuarter::getTotalLife() const {
    return totalLife;
}

bool HeadQuarter::isStopped() const {
    return stopped;
}

int HeadQuarter::canProduce() {
    int initPos = producePos;
    while(totalLife < warriorLifes[produceOrder[producePos]]) {
        producePos = (producePos + 1) % produceOrder.size();
        if(producePos == initPos) {
            stopped = true;
            return -1;
        }
    }
    int warrior = produceOrder[producePos];
    producePos = (producePos + 1) % produceOrder.size();
    return warrior;
}

void HeadQuarter::updateStatistics(const int& warrior) {
    totalLife -= warriorLifes[warrior];
    ++warriorCnt;
    warriorMap[warrior] += 1;
    return;
}

void HeadQuarter::produce() {
    if(isStopped())
        return;
    int warrior = canProduce();
    if(warrior != -1)
        updateStatistics(warrior);
    print(stopped, warrior);
    timeTicks();
    return;
}

void HeadQuarter::print(const bool& stopped, const int& warrior) const {
    if(stopped) {
        cout << setw(3) << setfill('0') << time << " " << name << " headquarter stops making warriors" << endl;
    } else {
        cout << setw(3) << setfill('0') << time << " " << name << " " << warriorNames[warrior] << " "
        << warriorCnt << " born with strength " << warriorLifes[warrior] << "," << warriorMap.at(warrior) << " "
        << warriorNames[warrior] << " in " << name << " headquarter" << endl;
        weaponPrint(warrior);
    }
    return;
}

void HeadQuarter::weaponPrint(const int& warrior) const {
    switch(warrior)
    {
    case 0:
        cout << fixed << setprecision(2);
        cout << "It has a " << weaponNames[warriorCnt % 3] << ",and it's morale is " << double(totalLife) / warriorLifes[warrior] << endl;
        break;
    case 1:
        cout << "It has a " << weaponNames[warriorCnt % 3] << " and a " << weaponNames[(warriorCnt + 1) % 3] << endl;
        break;
    case 2:
        cout << "It has a " << weaponNames[warriorCnt % 3] << endl;
        break;
    case 3:
        cout << "It's loyalty is " << totalLife << endl;
        break;
    default:
        break;
    }
    return;
}

void HeadQuarter::timeTicks() {
    ++time;
}


void startGame (const vector<int>& lifes) {
    const vector<int> warriorLifes(lifes.begin() + 1, lifes.end());
    const vector<int> redOrder = {2, 3, 4, 1, 0}, blueOrder = {3, 0, 1, 2, 4};
    HeadQuarter red("red", lifes[0], warriorLifes, redOrder), blue("blue", lifes[0], warriorLifes, blueOrder);
    while(!red.isStopped() || !blue.isStopped()) {
        red.produce();
        blue.produce();
    }
    return;
};

int main() {
    int curCase = 1, testCases;
    vector<int> lifes;
    cin >> testCases;
    while(testCases--) {
        int life;
        for(int i = 0; i < 6; ++i) {
            cin >> life;
            lifes.push_back(life);
        };
        cout << "Case:" << curCase << endl;
        startGame(lifes);
        curCase += 1;
        lifes.clear();
    };
    return 0;
}