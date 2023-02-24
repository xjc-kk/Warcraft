#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <deque>

using namespace std;

const vector<string> warriorNames = {"dragon", "ninja", "iceman", "lion", "wolf"};
const vector<string> weaponNames = {"sword", "bomb", "arrow"};
const deque<int> redOrder = {2, 3, 4, 1, 0};
const deque<int> blueOrder = {3, 0, 1, 2, 4};


class Weapon {
private:
    string name;
public:
    Weapon(const string& name_);
};

Weapon::Weapon(const string& name_) : name(name_) {
}


class Sword : public Weapon {
private:
    int power;
public:
    Sword(const int& power_);
    const int& getPower() const;
    void losePower();
};

Sword::Sword(const int& power_) : Weapon("sword"), power(power_) {}

const int& Sword::getPower() const {
    return power;
}

void Sword::losePower() {
    power = power * 8 / 10;
    return;
}


class Bomb : public Weapon {
public:
    Bomb();
};

Bomb::Bomb() : Weapon("bomb") {}


class Arrow : public Weapon {
private:
    int count;
    int damage;
public:
    Arrow(const int& damage_);
    const int& getCount() const;
    void loseCount();
};

Arrow::Arrow(const int& damage_) : Weapon("arrow"), count(3), damage(damage_) {}

const int& Arrow::getCount() const {
    return count;
}

void Arrow::loseCount() {
    --count;
    return;
};


class Warrior {
private:
    string name;
    string color;
    int number;
    int life;
    int power;
    int steps;
    Sword* sword;
    Bomb* bomb;
    Arrow* arrow;
    int arrowDamage;
public:
    Warrior(const string& name_, const string& color_, const int& number_,
            const int& life_, const int& power_, const int& arrowDamage_);
    const string& getName() const;
    const string& getColor() const;
    const int& getNumber() const;
    const int& getLife() const;
    void increaseLife(const int& life_);
    void hurt(const int& life_);
    bool isAlive() const;
    const int& getPower() const;
    void increasePower(const int& power_);
    const int& getSteps() const;
    void moveSteps();
    Sword* getSword();
    void setSword(Sword* ptr);
    Bomb* getBomb();
    void setBomb(Bomb* ptr);
    Arrow* getArrow();
    void setArrow(Arrow* ptr);

    void shootArrow(Warrior* ptr, const int& time);
    int measureHarm(Warrior* ptr, const bool& first);
    void winLife(const int& time, const int& life_);
    void attack(Warrior* other, const int& time, const int& city);
    void reattack(Warrior* other, const int& time, const int& city);

    virtual void yell(const int& time, const int& city) {};
    virtual void increaseMorale(const double& morale_) {};
    virtual void adjustAfter2Steps() {};
    virtual int getLoyalty() const {return 0;};
    virtual void loseLoyalty() {};
    virtual void robWeapon(Warrior* other) {};
};

Warrior::Warrior(const string& name_, const string& color_, const int& number_,
const int& life_, const int& power_, const int& arrowDamage_) : 
name(name_), color(color_), number(number_), life(life_), power(power_), arrowDamage(arrowDamage_) {
    steps = 0;
    sword = nullptr;
    bomb = nullptr;
    arrow = nullptr;
}

const string& Warrior::getName() const {
    return name;
}

const string& Warrior::getColor() const {
    return color;
}

const int& Warrior::getNumber() const {
    return number;
}

const int& Warrior::getLife() const {
    return life;
}

void Warrior::increaseLife(const int& life_) {
    life += life_;
    return;
}

void Warrior::hurt(const int& life_) {
    life -= life_;
    return;
}

bool Warrior::isAlive() const {
    return (life > 0);
}

const int& Warrior::getPower() const {
    return power;
}

void Warrior::increasePower(const int& power_) {
    power += power_;
}

const int& Warrior::getSteps() const {
    return steps;
}

void Warrior::moveSteps() {
    ++steps;
    return;
}

Sword* Warrior::getSword() {
    return sword;
}

void Warrior::setSword(Sword* ptr) {
    sword = ptr;
}

Bomb* Warrior::getBomb() {
    return bomb;
}

void Warrior::setBomb(Bomb* ptr) {
    bomb = ptr;
}

Arrow* Warrior::getArrow() {
    return arrow;
}

void Warrior::setArrow(Arrow* ptr) {
    arrow = ptr;
}

void Warrior::shootArrow(Warrior* ptr, const int& time) {
    ptr->hurt(arrowDamage);
    arrow->loseCount();
    if(arrow->getCount() == 0) {
        delete arrow;
        arrow = nullptr;
    }

    cout << setw(3) << setfill('0') << (time / 60) << ":" << setw(2) << (time % 60)
        << " " << color << " " << name << " " << number << " shot";
    if(!ptr->isAlive())
        cout << " and killed " << ptr->getColor() << " " << ptr->getName() << " " << ptr->getNumber();
    cout << endl;

    return;
}

int Warrior::measureHarm(Warrior* ptr, const bool& first) {
    int harm = 0;
    if(first) {
        int harmToEnemy = power;
        if(sword)
            harmToEnemy += sword->getPower();
        if(ptr->getLife() > harmToEnemy && ptr->getName() != "ninja") {
            harm += ptr->getPower() * 5 / 10;
            if(ptr->getSword())
                harm += ptr->getSword()->getPower();
        }
    } else {
        harm += ptr->getPower();
        if(ptr->getSword())
            harm += ptr->getSword()->getPower();
    }
    return harm;
}

void Warrior::winLife(const int& time, const int& life_) {
    cout << setw(3) << setfill('0') << (time / 60) << ":" << setw(2) << (time % 60)
        << " " << getColor() << " " << getName() << " " << getNumber() << " earned "
        << life_ << " elements for his headquarter" << endl;
    return;
}

void Warrior::attack(Warrior* other, const int& time, const int& city) {
    int harm = power;
    if(sword) {
        harm += sword->getPower();
        sword->losePower();
        if(sword->getPower() == 0) {
            delete sword;
            sword = nullptr;
        }
    }
    other->hurt(harm);

    cout << setw(3) << setfill('0') << (time / 60) << ":" << setw(2) << (time % 60)
        << " " << color << " " << name << " " << number << " attacked " << other->getColor()
        << " " << other->getName() << " " << other->getNumber() << " in city " << city
        << " with " << life << " elements and force " << power << endl;
    
    if(!other->isAlive()) {
        cout << setw(3) << setfill('0') << (time / 60) << ":" << setw(2) << (time % 60)
            << " " << other->getColor() << " " << other->getName() << " " 
            << other->getNumber() << " was killed in city " << city << endl;
    }
    
    return;
}

void Warrior::reattack(Warrior* other, const int& time, const int& city) {
    if(life <= 0 || name == "ninja")
        return;

    int harm = power * 5 / 10;
    if(sword) {
        harm += sword->getPower();
        sword->losePower();
        if(sword->getPower() == 0) {
            delete sword;
            sword = nullptr;
        }
    }
    other->hurt(harm);

    cout << setw(3) << setfill('0') << (time / 60) << ":" << setw(2) << (time % 60)
        << " " << color << " " << name << " " << number << " fought back against " << other->getColor()
        << " " << other->getName() << " " << other->getNumber() << " in city " << city << endl;

    if(!other->isAlive()) {
        cout << setw(3) << setfill('0') << (time / 60) << ":" << setw(2) << (time % 60)
            << " " << other->getColor() << " " << other->getName() << " " 
            << other->getNumber() << " was killed in city " << city << endl;
    }

    return;
}



class Dragon : public Warrior {
private:
    double morale;
public:
    Dragon(const string& color_, const int& number_, const int& life_,
            const int& power_, const int& arrowDamage_, const double& morale_);
    
    virtual void yell(const int& time, const int& city);
    virtual void increaseMorale(const double& morale_);
};

Dragon::Dragon(const string& color_, const int& number_, const int& life_,
const int& power_, const int& arrowDamage_, const double& morale_) :
Warrior("dragon", color_, number_, life_, power_, arrowDamage_), morale(morale_) {
    int weaponNo = number_ % 3;
    if(weaponNo == 0) {
        int swordPower = power_ * 2 / 10;
        if(swordPower) {
            Sword* ptr = new Sword(swordPower);
            setSword(ptr);
            ptr = nullptr;
        }
    } else if(weaponNo == 1) {
        Bomb* ptr = new Bomb();
        setBomb(ptr);
        ptr = nullptr;
    } else {
        Arrow* ptr = new Arrow(arrowDamage_);
        setArrow(ptr);
        ptr = nullptr;
    }
}

void Dragon::yell(const int& time, const int& city) {
    if(morale > 0.8 && getLife() > 0)
        cout << setw(3) << setfill('0') << (time / 60) << ":" << setw(2) << (time % 60)
            << " " << getColor() << " dragon " << getNumber() << " yelled in city " << city << endl;
}

void Dragon::increaseMorale(const double& morale_) {
    morale += morale_;
    return;
}


class Ninja : public Warrior {
public:
    Ninja(const string& color_, const int& number_, const int& life_,
            const int& power_, const int& arrowDamage_);
};

Ninja::Ninja(const string& color_, const int& number_, const int& life_,
const int& power_, const int& arrowDamage_) : 
Warrior("ninja", color_, number_, life_, power_, arrowDamage_) {
    int weaponNo = number_ % 3;
    int swordPower = power_ * 2 / 10;
    if(weaponNo == 0) {
        if(swordPower) {
            Sword* swordPtr = new Sword(swordPower);
            setSword(swordPtr);
            swordPtr = nullptr;
        }

        Bomb* bombPtr = new Bomb();
        setBomb(bombPtr);
        bombPtr = nullptr;
    } else if(weaponNo == 1) {
        Bomb* bombPtr = new Bomb();
        setBomb(bombPtr);
        bombPtr = nullptr;

        Arrow* arrowPtr = new Arrow(arrowDamage_);
        setArrow(arrowPtr);
        arrowPtr = nullptr;
    } else {
        Arrow* arrowPtr = new Arrow(arrowDamage_);
        setArrow(arrowPtr);
        arrowPtr = nullptr;

        if(swordPower) {
            Sword* swordPtr = new Sword(swordPower);
            setSword(swordPtr);
            swordPtr = nullptr;
        }
    }
}


class Iceman : public Warrior {
public:
    Iceman(const string& color_, const int& number_, const int& life_,
            const int& power_, const int& arrowDamage_);
    virtual void adjustAfter2Steps();
};

Iceman::Iceman(const string& color_, const int& number_, const int& life_,
const int& power_, const int& arrowDamage_) :
Warrior("iceman", color_, number_, life_, power_, arrowDamage_) {
    int weaponNo = number_ % 3;
    if(weaponNo == 0) {
        int swordPower = power_ * 2 / 10;
        if(swordPower) {
            Sword* ptr = new Sword(swordPower);
            setSword(ptr);
            ptr = nullptr;
        }
    } else if(weaponNo == 1) {
        Bomb* ptr = new Bomb();
        setBomb(ptr);
        ptr = nullptr;
    } else {
        Arrow* ptr = new Arrow(arrowDamage_);
        setArrow(ptr);
        ptr = nullptr;
    }
}

void Iceman::adjustAfter2Steps() {
    int steps = getSteps();
    if(steps % 2 == 0) {
        increasePower(20);
        int curLife = getLife();
        if(curLife > 9)
            increaseLife(-9);
        else
            increaseLife(1 - curLife);
    }
    return;
}


class Lion : public Warrior {
private:
    int loyalty;
    int deltaLoyalty;
public:
    Lion(const string& color_, const int& number_, const int& life_,
            const int& power_, const int& arrowDamage_, const int& loyalty_,
            const int& deltaLoyalty_);
    virtual int getLoyalty() const;
    virtual void loseLoyalty();
};

Lion::Lion(const string& color_, const int& number_, const int& life_,
const int& power_, const int& arrowDamage_, const int& loyalty_, const int& deltaLoyalty_) :
Warrior("lion", color_, number_, life_, power_, arrowDamage_), 
loyalty(loyalty_), deltaLoyalty(deltaLoyalty_) {}

int Lion::getLoyalty() const {
    return loyalty;
}

void Lion::loseLoyalty() {
    loyalty -= deltaLoyalty;
    return;
}


class Wolf : public Warrior {
public:
    Wolf(const string& color_, const int& number_, const int& life_,
            const int& power_, const int& arrowDamage_);
    virtual void robWeapon(Warrior* other);
};

Wolf::Wolf(const string& color_, const int& number_, const int& life_,
const int& power_, const int& arrowDamage_) :
Warrior("wolf", color_, number_, life_, power_, arrowDamage_) {}

void Wolf::robWeapon(Warrior* other) {
    if(getSword() == nullptr && other->getSword()) {
        setSword(other->getSword());
        other->setSword(nullptr);
    }
    if(getBomb() == nullptr && other->getBomb()) {
        setBomb(other->getBomb());
        other->setBomb(nullptr);
    }
    if(getArrow() == nullptr && other->getArrow()) {
        setArrow(other->getArrow());
        other->setArrow(nullptr);
    }
}


class Headquarter;

class City {
private:
    int number;
    int life;
    string flag;
    string lastWinner;
    bool lastBattle;
    Warrior* red;
    Warrior* blue;
public:
    City(const int& number_, const int& life_);
    const int& getNumber() const;
    const int& getLife() const;
    void increaseLife(const int& life_);
    const string& getFlag() const;
    void setFlag(const string& flag_);
    const string& getLastWinner() const;
    bool getLastBattle() const;
    Warrior* getWarrior(const string& name_) const;
    void setWarrior(const string& name_, Warrior* ptr);
    void cleanDeadWarrior();
    void raiseFlag(const int& time, const string& flag_);

    void produceLife();
    void takeLife(Headquarter* redHeadquarter, Headquarter* blueHeadquarter, const int& time);
    int judgeThrowBomb();
    void throwBomb(const int& time);
    void battle(const int& time, Headquarter* redHeadquarter, Headquarter* blueHeadquarter);
    void reportWeapons(const int& time, Warrior* ptr) const;

    virtual void escape(const int& time);
    virtual void printMarch(const int& time) const;
};

City::City(const int& number_, const int& life_) : number(number_), life(life_) {
    flag = "";
    lastWinner = "none";
    lastBattle = false;
    red = nullptr;
    blue = nullptr;
}

const int& City::getNumber() const {
    return number;
}

const int& City::getLife() const {
    return life;
}

void City::increaseLife(const int& life_) {
    life += life_;
    return;
}

const string& City::getFlag() const {
    return flag;
}

void City::setFlag(const string& flag_) {
    flag = flag_;
    return;
}

const string& City::getLastWinner() const {
    return lastWinner;
}

bool City::getLastBattle() const {
    return lastBattle;
}

Warrior* City::getWarrior(const string& name_) const {
    if(name_ == "red")
        return red;
    else
        return blue;
}

void City::setWarrior(const string& name_, Warrior* ptr) {
    if(name_ == "red")
        red = ptr;
    else
        blue = ptr;
    ptr = nullptr;
    return;
}

void City::cleanDeadWarrior() {
    if(red && !red->isAlive()) {
        delete red;
        red = nullptr;
    }
    if(blue && !blue->isAlive()) {
        delete blue;
        blue = nullptr;
    }
    return;
}

void City::raiseFlag(const int& time, const string& flag_) {
    if(lastWinner == flag_ && flag != flag_) {
        flag = flag_;
        cout << setw(3) << setfill('0') << (time / 60) << ":" << setw(2) << (time % 60)
            << " " << flag_ << " flag raised in city " << number << endl;
    }
    lastWinner = flag_;
}

void City::produceLife() {
    life += 10;
    return;
}

int City::judgeThrowBomb() {
    if(red && blue && red->isAlive() && blue->isAlive()) {
        bool redFirst = ((flag == "red") || (flag == "" && number % 2 == 1));
        if(red->getBomb()) {
            int harm = red->measureHarm(blue, redFirst);
            if(harm >= red->getLife())
                return 1;
        }
        if(blue->getBomb()) {
            int harm = blue->measureHarm(red, !redFirst);
            if(harm >= blue->getLife())
                return 2;
        }
    }
    return 0;
}

void City::throwBomb(const int& time) {
    int judge = judgeThrowBomb();
    if(judge == 0)
        return;
    else if(judge == 1) {
        // red throws
        cout << setw(3) << setfill('0') << (time / 60) << ":" << setw(2) << (time % 60)
            << " red " << red->getName() << " " << red->getNumber() << " used a bomb and killed blue "
            << blue->getName() << " " << blue->getNumber() << endl;
    } else {
        // blue throws
        cout << setw(3) << setfill('0') << (time / 60) << ":" << setw(2) << (time % 60)
            << " blue " << blue->getName() << " " << blue->getNumber() << " used a bomb and killed red "
            << red->getName() << " " << red->getNumber() << endl;
    }

    red->hurt(red->getLife());
    blue->hurt(blue->getLife());
    return;
}

void City::reportWeapons(const int& time, Warrior* ptr) const {
    if(ptr == nullptr)
        return;
    cout << setw(3) << setfill('0') << (time / 60) << ":" << setw(2) << (time % 60)
        << " " << ptr->getColor() << " " << ptr->getName() << " " << ptr->getNumber() << " has ";
    bool hasWeapon = false;
    if(ptr->getArrow()) {
        cout << "arrow(" << ptr->getArrow()->getCount() << ")";
        hasWeapon = true;
    }
    if(ptr->getBomb()) {
        if(hasWeapon)
            cout << ",";
        cout << "bomb";
        hasWeapon = true;
    }
    if(ptr->getSword()) {
        if(hasWeapon)
            cout << ",";
        cout << "sword(" << ptr->getSword()->getPower() << ")";
        hasWeapon = true;
    }
    if(!hasWeapon)
        cout << "no weapon";
    cout << endl;
    return;
}

void City::escape(const int& time) {
    if(red && red->getName() == "lion" && red->getLoyalty() <= 0) {
        cout << setw(3) << setfill('0') << (time / 60) << ":" << setw(2) << (time % 60)
            << " red lion " << red->getNumber() << " ran away" << endl;
        delete red;
        red = nullptr;
    }
    if(blue && blue->getName() == "lion" && blue->getLoyalty() <= 0) {
        cout << setw(3) << setfill('0') << (time / 60) << ":" << setw(2) << (time % 60)
            << " blue lion " << blue->getNumber() << " ran away" << endl;
        delete blue;
        blue = nullptr;
    }
}

void City::printMarch(const int& time) const {
    if(red) {
        cout << setw(3) << setfill('0') << (time / 60) << ":" << setw(2) << (time % 60)
            << " red " << red->getName() << " " << red->getNumber() << " marched to city " << number
            << " with " << red->getLife() << " elements and force " << red->getPower() << endl;
    }
    if(blue) {
        cout << setw(3) << setfill('0') << (time / 60) << ":" << setw(2) << (time % 60)
            << " blue " << blue->getName() << " " << blue->getNumber() << " marched to city " << number
            << " with " << blue->getLife() << " elements and force " << blue->getPower() << endl;
    }
    return;
}


class Headquarter : public City {
private:
    string name;
    deque<int> produceOrder;
    int enemies;
    int warriorNumber;
    int accumulate;
public:
    Headquarter(const int& number_, const int& life_, const string& name_,
                const deque<int>& produceOrder_);
    const string& getName() const;
    const int& getEnemies() const;
    void increaseEnemies();
    const int& getWarriorNumber();
    bool isDefeated() const;
    void increaseAccumulate(int accumulate_);
    void accumulateVictory();

    void produce(const int& time, const int& arrowPower, const int& loyaltyLose,
        const vector<int>& warriorLifes, const vector<int>& warriorAttacks);
    void producePrint(const int& time, const string& warriorName, 
        const int& loyalty, const double& morale) const;
    void reportLifes(const int& time) const;
    
    virtual void escape(const int& time);
    virtual void printMarch(const int& time, Warrior* prevWarrior) const;
};

Headquarter::Headquarter(const int& number_, const int& life_, const string& name_,
const deque<int>& produceOrder_) :
City(number_, life_), name(name_), produceOrder(produceOrder_) {
    enemies = 0;
    warriorNumber = 1;
    accumulate = 0;
}

const string& Headquarter::getName() const {
    return name;
}

const int& Headquarter::getEnemies() const {
    return enemies;
}

void Headquarter::increaseEnemies() {
    ++enemies;
}

const int& Headquarter::getWarriorNumber() {
    return warriorNumber;
}

bool Headquarter::isDefeated() const {
    return (enemies >= 2);
}

void Headquarter::increaseAccumulate(int accumulate_) {
    accumulate += accumulate_;
    return;
}

void Headquarter::accumulateVictory() {
    increaseLife(accumulate);
    accumulate = 0;
    return;
}

void Headquarter::produce(const int& time, const int& arrowPower, const int& loyaltyLose,
const vector<int>& warriorLifes, const vector<int>& warriorAttacks) {
    int warriorToProduce = produceOrder[0];
    int headquarterLife = getLife();
    if(headquarterLife < warriorLifes[warriorToProduce])
        return;
    
    increaseLife(-warriorLifes[warriorToProduce]);
    string warriorName = warriorNames[warriorToProduce];
    int warriorLife = warriorLifes[warriorToProduce];
    int warriorPower = warriorAttacks[warriorToProduce];
    double morale = (double)getLife() / warriorLife;
    int loyalty = getLife();
    Warrior* warriorPtr;

    switch (warriorToProduce)
    {
    case 0:
        warriorPtr = new Dragon(name, warriorNumber, warriorLife, warriorPower, arrowPower, morale);
        break;

    case 1:
        warriorPtr = new Ninja(name, warriorNumber, warriorLife, warriorPower, arrowPower);
        break;

    case 2:
        warriorPtr = new Iceman(name, warriorNumber, warriorLife, warriorPower, arrowPower);
        break;

    case 3:
        warriorPtr = new Lion(name, warriorNumber, warriorLife, warriorPower, arrowPower, 
                        loyalty, loyaltyLose);
        break;

    default:
        warriorPtr = new Wolf(name, warriorNumber, warriorLife, warriorPower, arrowPower);
        break;
    }
    if(name == "red")
        setWarrior("red", warriorPtr);
    else
        setWarrior("blue", warriorPtr);

    producePrint(time, warriorName, loyalty, morale);

    ++warriorNumber;
    produceOrder.pop_front();
    produceOrder.push_back(warriorToProduce);
    return;
}

void Headquarter::producePrint(const int& time, const string& warriorName,
const int& loyalty, const double& morale) const {
    cout << setw(3) << setfill('0') << (time / 60) << ":" << setw(2) << (time % 60)
        << " " << name << " " << warriorName << " " << warriorNumber << " born" << endl;
    if(warriorName == "dragon")
        cout << fixed << setprecision(2) << "Its morale is " << morale << endl;
    if(warriorName == "lion")
        cout << "Its loyalty is " << loyalty << endl;
    return;
}

void Headquarter::reportLifes(const int& time) const {
    int life = getLife();
    cout << setw(3) << setfill('0') << (time / 60) << ":" << setw(2) << (time % 60)
         << " " << life << " elements in " << name << " headquarter" << endl;
    return;
}

void Headquarter::escape(const int& time) {
    if(name == "red") {
        // only red lion can run
        Warrior* redWarrior = getWarrior("red");
        if(redWarrior && redWarrior->getName() == "lion" && redWarrior->getLoyalty() <= 0) {
            cout << setw(3) << setfill('0') << (time / 60) << ":" << setw(2) << (time % 60)
                << " red lion " << redWarrior->getNumber() << " ran away" << endl;
            delete redWarrior;
            setWarrior("red", nullptr);
        }
    } else {
        // only blue lion can run
        Warrior* blueWarrior = getWarrior("blue");
        if(blueWarrior && blueWarrior->getName() == "lion" && blueWarrior->getLoyalty() <= 0) {
            cout << setw(3) << setfill('0') << (time / 60) << ":" << setw(2) << (time % 60)
                << " blue lion " << blueWarrior->getNumber() << " ran away" << endl;
            delete blueWarrior;
            setWarrior("blue", nullptr);
        }
    }
    return;
}

void Headquarter::printMarch(const int& time, Warrior* prevWarrior) const {
    Warrior* redWarrior = getWarrior("red");
    Warrior* blueWarrior = getWarrior("blue");
    if(name == "red" && blueWarrior && blueWarrior != prevWarrior) {
        cout << setw(3) << setfill('0') << (time / 60) << ":" << setw(2) << (time % 60)
            << " blue " << blueWarrior->getName() << " "
            << blueWarrior->getNumber() << " reached red headquarter with "
            << blueWarrior->getLife() << " elements and force "
            << blueWarrior->getPower() << endl;
        if(isDefeated())
            cout << setw(3) << setfill('0') << (time / 60) << ":" << setw(2) << (time % 60)
                << " red headquarter was taken" << endl;
    }
    if(name == "blue" && redWarrior && redWarrior != prevWarrior) {
        cout << setw(3) << setfill('0') << (time / 60) << ":" << setw(2) << (time % 60)
            << " red " << redWarrior->getName() << " "
            << redWarrior->getNumber() << " reached blue headquarter with "
            << redWarrior->getLife() << " elements and force "
            << redWarrior->getPower() << endl;
        if(isDefeated())
            cout << setw(3) << setfill('0') << (time / 60) << ":" << setw(2) << (time % 60)
                << " blue headquarter was taken" << endl;
    }
    return;
}

void City::takeLife(Headquarter* redHeadquarter, Headquarter* blueHeadquarter, const int& time) {
    if(red && blue == nullptr) {
        redHeadquarter->increaseLife(life);
        cout << setw(3) << setfill('0') << (time / 60) << ":" << setw(2) << (time % 60)
            << " red " << red->getName() << " " << red->getNumber() << " earned "
            << life << " elements for his headquarter" << endl;
        life = 0;
    } else if(blue && red == nullptr) {
        blueHeadquarter->increaseLife(life);
        cout << setw(3) << setfill('0') << (time / 60) << ":" << setw(2) << (time % 60)
            << " blue " << blue->getName() << " " << blue->getNumber() << " earned "
            << life << " elements for his headquarter" << endl;
        life = 0;
    }
    return;
}

void City::battle(const int& time, Headquarter* redHeadquarter, Headquarter* blueHeadquarter) {
    if(red && blue) {
        lastBattle = true;
        bool redAlive = red->isAlive(), blueAlive = blue->isAlive();
        bool redFirst = ((flag == "red") || (flag == "" && number % 2 == 1));
        int redLife = red->getLife(), blueLife = blue->getLife();
        if(!redAlive && !blueAlive) {
            // both dead before the battle
            lastBattle = false;
        } else if(redAlive && !blueAlive) {
            red->increaseMorale(0.2);
            if(redFirst)
                red->yell(time, number);
            
            if(red->getName() == "wolf")
                red->robWeapon(blue);

            redHeadquarter->increaseAccumulate(life);
            red->winLife(time, life);
            life = 0;

            raiseFlag(time, "red");
        } else if(!redAlive && blueAlive) {
            blue->increaseMorale(0.2);
            if(!redFirst)
                blue->yell(time, number);
            
            if(blue->getName() == "wolf")
                blue->robWeapon(red);

            blueHeadquarter->increaseAccumulate(life);
            blue->winLife(time, life);
            life = 0;

            raiseFlag(time, "blue");
        } else {
            // battle
            if(redFirst) {
                red->attack(blue, time, number);
                blue->reattack(red, time, number);
            } else{
                blue->attack(red, time, number);
                red->reattack(blue, time, number);
            }

            red->increaseMorale(-0.2);
            blue->increaseMorale(-0.2);
            if(redFirst)
                red->yell(time, number);
            else
                blue->yell(time, number);
            
            red->loseLoyalty();
            blue->loseLoyalty();

            if(red->isAlive() && blue->isAlive())
                lastWinner = "none";
            else if(red->isAlive()) {
                if(red->getName() == "wolf")
                    red->robWeapon(blue);
                if(blue->getName() == "lion")
                    red->increaseLife(blueLife);

                redHeadquarter->increaseAccumulate(life);
                red->winLife(time, life);
                life = 0;

                raiseFlag(time, "red");
            } else {
                if(blue->getName() == "wolf")
                    blue->robWeapon(red);
                if(red->getName() == "lion")
                    blue->increaseLife(redLife);

                blueHeadquarter->increaseAccumulate(life);
                blue->winLife(time, life);
                life = 0;

                raiseFlag(time, "blue");
            }
        }
    } else {
        lastBattle = false;
    }
    cleanDeadWarrior();
    return;
}



void produce(const int& time, Headquarter* redHeadquarter, Headquarter* blueHeadquarter,
const int& arrowPower, const int& loyaltyLose, const vector<int>& warriorLifes, 
const vector<int>& warriorAttacks) {
    redHeadquarter->produce(time, arrowPower, loyaltyLose, warriorLifes, warriorAttacks);
    blueHeadquarter->produce(time, arrowPower, loyaltyLose, warriorLifes, warriorAttacks);
    return;
}

void escape(const int& time, Headquarter* redHeadquarter, Headquarter* blueHeadquarter,
vector<City*>& cities, const int& numCity) {
    redHeadquarter->escape(time);
    for(int i = 0; i < numCity; ++i)
        cities[i]->escape(time);
    blueHeadquarter->escape(time);
    return;
}

void march(const int& time, Headquarter* redHeadquarter, Headquarter* blueHeadquarter,
vector<City*>& cities, const int& numCity) {
    deque<Warrior*> redWarriors, blueWarriors;
    Warrior* redEnemy = redHeadquarter->getWarrior("blue");
    Warrior* blueEnemy = blueHeadquarter->getWarrior("red");
    
    if(redHeadquarter->getWarrior("red")) {
        redHeadquarter->getWarrior("red")->moveSteps();
        redHeadquarter->getWarrior("red")->adjustAfter2Steps();
    }
    redWarriors.push_back(redHeadquarter->getWarrior("red"));
    for(int i = 0; i < numCity; ++i) {
        if(cities[i]->getWarrior("red")) {
            cities[i]->getWarrior("red")->moveSteps();
            cities[i]->getWarrior("red")->adjustAfter2Steps();
        }
        if(cities[i]->getWarrior("blue")) {
            cities[i]->getWarrior("blue")->moveSteps();
            cities[i]->getWarrior("blue")->adjustAfter2Steps();
        }
        redWarriors.push_back(cities[i]->getWarrior("red"));
        blueWarriors.push_back(cities[i]->getWarrior("blue"));
    }
    if(blueHeadquarter->getWarrior("blue")) {
        blueHeadquarter->getWarrior("blue")->moveSteps();
        blueHeadquarter->getWarrior("blue")->adjustAfter2Steps();
    }
    blueWarriors.push_back(blueHeadquarter->getWarrior("blue"));

    redHeadquarter->setWarrior("blue", blueWarriors.front());
    blueWarriors.pop_front();  
    for(int i = 0; i < numCity; ++i) {
        cities[i]->setWarrior("blue", blueWarriors.front());
        blueWarriors.pop_front();
    }
    blueHeadquarter->setWarrior("blue", nullptr);

    blueHeadquarter->setWarrior("red", redWarriors.back());
    redWarriors.pop_back();
    for(int i = numCity - 1; i >= 0; --i) {
        cities[i]->setWarrior("red", redWarriors.back());
        redWarriors.pop_back();
    }
    redHeadquarter->setWarrior("red", nullptr);

    if(redHeadquarter->getWarrior("blue") && redHeadquarter->getWarrior("blue") != redEnemy) {
        redHeadquarter->increaseEnemies();
        redHeadquarter->printMarch(time, redEnemy);
    }

    for(int i = 0; i < numCity; ++i)
        cities[i]->printMarch(time);
    
    if(blueHeadquarter->getWarrior("red") && blueHeadquarter->getWarrior("red") != blueEnemy) {
        blueHeadquarter->increaseEnemies();
        blueHeadquarter->printMarch(time, blueEnemy);
    }

    if(redHeadquarter->getWarrior("blue") == nullptr && redEnemy)   
        redHeadquarter->setWarrior("blue", redEnemy);
    if(blueHeadquarter->getWarrior("red") == nullptr && blueEnemy)
        blueHeadquarter->setWarrior("red", blueEnemy);
    return;
}

void produceLife(vector<City*> cities, const int& numCity) {
    for(int i = 0; i < numCity; ++i)
        cities[i]->produceLife();
    return;
}

void takeLife(const int& time, Headquarter* redHeadquarter, Headquarter* blueHeadquarter,
vector<City*>& cities, const int& numCity) {
    for(int i = 0; i < numCity; ++i)
        cities[i]->takeLife(redHeadquarter, blueHeadquarter, time);
    return;
}

void shootArrow(const int& time, Headquarter* redHeadquarter, Headquarter* blueHeadquarter,
vector<City*>& cities, const int& numCity) {
    if(redHeadquarter->getWarrior("red") && redHeadquarter->getWarrior("red")->getArrow()
        && cities[0]->getWarrior("blue"))
        redHeadquarter->getWarrior("red")->shootArrow(cities[0]->getWarrior("blue"), time);

    for(int i = 0; i < numCity; ++i) {
        if(cities[i]->getWarrior("red") && cities[i]->getWarrior("red")->getArrow()) {
            if(i == numCity - 1) {
                if(blueHeadquarter->getWarrior("blue"))
                    cities[i]->getWarrior("red")->shootArrow(blueHeadquarter->getWarrior("blue"), time);
            } else if(cities[i + 1]->getWarrior("blue"))
                cities[i]->getWarrior("red")->shootArrow(cities[i + 1]->getWarrior("blue"), time);
        }
        if(cities[i]->getWarrior("blue") && cities[i]->getWarrior("blue")->getArrow()) {
            if(i == 0) {
                if(redHeadquarter->getWarrior("red"))
                    cities[i]->getWarrior("blue")->shootArrow(redHeadquarter->getWarrior("red"), time);
            }
            else if(cities[i - 1]->getWarrior("red"))
                cities[i]->getWarrior("blue")->shootArrow(cities[i - 1]->getWarrior("red"), time);
        }
    }

    if(blueHeadquarter->getWarrior("blue") && blueHeadquarter->getWarrior("blue")->getArrow()
        && cities[numCity - 1]->getWarrior("red"))
        blueHeadquarter->getWarrior("blue")->shootArrow(cities[numCity - 1]->getWarrior("red"), time);
    return;
}

void throwBomb(const int& time, vector<City*>& cities, const int& numCity) {
    for(int i = 0; i < numCity; ++i)
        cities[i]->throwBomb(time);
    return;
}

void battle(const int& time, Headquarter* redHeadquarter, Headquarter* blueHeadquarter,
vector<City*>& cities, const int& numCity) {
    for(int i = 0; i < numCity; ++i)
        cities[i]->battle(time, redHeadquarter, blueHeadquarter);

    for(int i = 0; i < numCity; ++i) {
        if(cities[i]->getLastBattle() && cities[i]->getLastWinner() == "blue" 
            && blueHeadquarter->getLife() >= 8) { 
            blueHeadquarter->increaseLife(-8);
            cities[i]->getWarrior("blue")->increaseLife(8);
        }
    }

    for(int i = numCity - 1; i >= 0; --i) {
        if(cities[i]->getLastBattle() && cities[i]->getLastWinner() == "red" 
            && redHeadquarter->getLife() >= 8) {
            redHeadquarter->increaseLife(-8);
            cities[i]->getWarrior("red")->increaseLife(8);
        }
    }

    redHeadquarter->accumulateVictory();
    blueHeadquarter->accumulateVictory();
}


void reportLifes(const int& time, Headquarter* redHeadquarter, Headquarter* blueHeadquarter) {
    redHeadquarter->reportLifes(time);
    blueHeadquarter->reportLifes(time);
}


void reportWeapons(const int& time, Headquarter* redHeadquarter, Headquarter* blueHeadquarter,
vector<City*>& cities, const int& numCity) {
    redHeadquarter->reportWeapons(time, redHeadquarter->getWarrior("red"));
    for(int i = 0; i < numCity; ++i)
        cities[i]->reportWeapons(time, cities[i]->getWarrior("red"));
    blueHeadquarter->reportWeapons(time, blueHeadquarter->getWarrior("red"));

    redHeadquarter->reportWeapons(time, redHeadquarter->getWarrior("blue"));
    for(int i = 0; i < numCity; ++i)
        cities[i]->reportWeapons(time, cities[i]->getWarrior("blue"));
    blueHeadquarter->reportWeapons(time, blueHeadquarter->getWarrior("blue"));

    return;
}


void timeTicks(int& time, int t) {
    time += t;
    return;
}

void startGame (const int& numLife, const int& numCity, const int& arrowPower, const int& loyaltyLose,
                const int& numTime, const vector<int>& warriorLifes, const vector<int>& warriorAttacks) {
    Headquarter* redHeadquarter = new Headquarter(0, numLife, "red", redOrder);
    Headquarter* blueHeadquarter = new Headquarter(numCity + 1, numLife, "blue", blueOrder);

    vector<City*> cities;
    for(int i = 1; i <= numCity; ++i) {
        City* city = new City(i, 0);
        cities.push_back(city);
    }

    int time = 0;
    while(time <= numTime) {
        produce(time, redHeadquarter, blueHeadquarter, arrowPower, 
            loyaltyLose, warriorLifes, warriorAttacks);

        timeTicks(time, 5);
        if(time > numTime)
            break;
        escape(time, redHeadquarter, blueHeadquarter, cities, numCity);

        timeTicks(time, 5);
        if(time > numTime)
            break;
        march(time, redHeadquarter, blueHeadquarter, cities, numCity);
        if(redHeadquarter->isDefeated() || blueHeadquarter->isDefeated())
            break;

        timeTicks(time, 10);
        if(time > numTime)
            break;
        produceLife(cities, numCity);

        timeTicks(time, 10);
        if(time > numTime)
            break;
        takeLife(time, redHeadquarter, blueHeadquarter, cities, numCity);

        timeTicks(time, 5);
        if(time > numTime)
            break;
        shootArrow(time, redHeadquarter, blueHeadquarter, cities, numCity);

        timeTicks(time, 3);
        if(time > numTime)
            break;
        throwBomb(time, cities, numCity);

        timeTicks(time, 2);
        if(time > numTime)
            break;
        battle(time, redHeadquarter, blueHeadquarter, cities, numCity);

        timeTicks(time, 10);
        if(time > numTime)
            break;
        reportLifes(time, redHeadquarter, blueHeadquarter);

        timeTicks(time, 5);
        if(time > numTime)
            break;
        reportWeapons(time, redHeadquarter, blueHeadquarter, cities, numCity);

        timeTicks(time, 5);
    }
    return;
};

int main() {
    int curCase = 1, testCases;
    cin >> testCases;
    while(testCases--) {
        int numLife, numCity, arrowPower, loyaltyLose, numTime;
        vector<int> warriorLifes, warriorAttacks;
        cin >> numLife >> numCity >> arrowPower >> loyaltyLose >> numTime;
        int life, attack;
        for(int i = 0; i < 5; ++i) {
            cin >> life;
            warriorLifes.push_back(life);
        };
        for(int i = 0; i < 5; ++i) {
            cin >> attack;
            warriorAttacks.push_back(attack);
        };
        cout << "Case " << curCase << ":" << endl;
        startGame(numLife, numCity, arrowPower, loyaltyLose, numTime, warriorLifes, warriorAttacks);
        curCase += 1;
    };
    return 0;
}