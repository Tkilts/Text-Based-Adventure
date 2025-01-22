#include <iostream>
#include <sstream>
#include <time.h>

using namespace std;

class Player {
    public:
    Player(int x, int y){
        health = MAX_HEALTH;
        hunger = MAX_HUNGER;
        thirst = MAX_THIRST;
        
        this->x = x;
        this->y = y;
        this->score = 0;
    }
    
    int getScore() const {
        return score;
    }
    
    void takeDamage(int val){
        this->health -= val;
        if(this->health < 0) this->health = 0;
    }
    
    void takeTurn(){
        this->thirst--;
        this->hunger--;
        
        if(this->thirst <= 0){
            this->health--;
            this->thirst = 0;
        }
        
        if(this->hunger <= 0){
            this->health--;
            this->hunger = 0;
        }
        
        this->score++;
    }
    
    string getStats() const {
        stringstream ss;
        ss  << "============\n"
            << "Health: " << this->health << "\n" 
            << "Hunger: " << this->hunger << "\n" 
            << "Thirst: " << this->thirst << "\n"
            << "============\n";
        return ss.str();
    }
    
    bool isAlive() const {
        return this->health > 0;
    }
    
    void increaseThirst(int val){
        //this->thirst = this->thirst + val;
        if(this->thirst > MAX_THIRST) this->thirst = MAX_THIRST;
    }
    
    void increaseHunger(int val){
        this->hunger += val;
        if(this->hunger > MAX_HUNGER) this->hunger = MAX_HUNGER;
    }
    
    int x, y;
    private:
    int health, hunger, thirst, score;
    const int MAX_HEALTH = 3;
    const int MAX_HUNGER = 5;
    const int MAX_THIRST = 3;
};

class Land {
    public:
    virtual string getDescription() = 0;
    virtual string visit(Player& player) = 0;
};

// TODO: Define at least 3 more types of derivded land types
// TODO: Add some unique effect to each new type

class Forest : public Land {
    public:
    string getDescription(){
        return "a densely wooded forest.";
    }
    
    string visit(Player& player){
        int randomNum = rand() % 100;
        
        if(randomNum > 74){
            player.takeDamage(1);
            return "You are attacked by a bear while foraging for berries.";
        } else {
            player.increaseHunger(1);
            return "You forage for berries in the woods and eat a few.";
        }
    }
};

class Lake : public Land {
    public:
    string getDescription(){
        return "a clear sparkling lake.";
    }
    
    string visit(Player& player){
        player.increaseThirst(2);
        return "You visit the lake and drink its clean water";
    }
};

class Plains : public Land {
    public:
    string getDescription(){
        return "a wide open, wind swept plain.";
    }
    
    string visit(Player& player){
        int randomNum = rand() % 100;
        
        if(randomNum > 60){
            player.increaseThirst(1);
            player.increaseHunger(1);
            return "The weather is clear and you take a moment to rest.";
        } 
        
        else {
            return "A storm is rolling in, you think it best to hurry on.";
        }
    }
};

class MountainPass : public Land {
    public:
    string getDescription(){
        return "a frigid pass through a snow capped mountain.";
    }
    
    string visit(Player& player){
        int randomNum = rand() % 100;
        
        if(randomNum > 74){
            player.takeDamage(1);
            return "The freezing wind rips through your light garments, leaving you frostbitten.";
        } 
        
        if(randomNum > 50||randomNum < 75){
            player.increaseHunger(1);
            return "You find a frozen pond and stop to ice fish.";
        }
        
        else {
            player.increaseThirst(1);
            return "You find a frozen pond, it looks clean enough so you fill your waterskin with ice.";
        }
    }
};

class Desert : public Land {
    public:
    string getDescription(){
        return "a barren desert miles long, no oasis in sight.";
    }
    
    string visit(Player& player){
        int randomNum = rand() % 100;
        
        if(randomNum > 85){
            player.increaseThirst(-1);
            return "You spend an extra day chasing an oasis that ends up a mirage.";
        } else {
            player.takeDamage(-1);
            return "You're found by a local who provides you with medicinal herbs for your travels.";
        }
    }
};

class Canyon : public Land {
    public:
    string getDescription(){
        return "a gradual down slope, leading into a deep, dark canyon.";
    }
    
    string visit(Player& player){
        int randomNum = rand() % 100;
        
        if(randomNum > 51){
            player.increaseHunger(-1);
            return "You decide to stick to the high ground, taking longer to navigate.";
        } else {
            player.takeDamage(-1);
            return "You venture down into the canyon, finding respite from the elements.";
        }
    }
};

class Town : public Land {
    public:
    string getDescription(){
        return "a small town with few houses and visible farms.";
    }
    
    string visit(Player& player){
        player.increaseHunger(1);
        player.increaseThirst(1);
        return "The townsfolk share some bread and water, but shortly send you on your way.";
    }
};

class ForestCave : public Land {
    public:
    string getDescription(){
        return "a large cave mouth peaking through the trees of a forest.";
    }
    
    string visit(Player& player){
        int randomNum = rand() % 100;
        
        if(randomNum > 70){
            player.takeDamage(1);
            return "As you approach, you startle a swarm of bats, you flee but not without being bitten.";
        } else {
            player.increaseHunger(1);
            return "You take shelter in the cave and rest.";
        }
    }
};

class Rainforest : public Land {
    public:
    string getDescription(){
        return "a lush rainforest bellowing with the sounds of animals.";
    }
    
    string visit(Player& player){
        int randomNum = rand() % 100;
        
        if(randomNum > 85){
            player.increaseThirst(1);
            return "You find a spring and refill your waterskin.";
        } 
        if (randomNum > 25|| randomNum < 85){
            player.increaseThirst(1);
            player.takeDamage(1);
            return "You manage to fill your waterskin at a spring, but are chased off by a leopard.";
        }
        else {
            player.takeDamage(2);
            return "You approach a spring, but a snake bites your leg before you make it there. Hopefully it wasn't venomous.";
        }
    }
};

class Barrens : public Land {
    public:
    string getDescription(){
        return "a desolate scorched field, nothing living remains.";
    }
    string visit(Player& player){
    return "As you pass through you feel as though you're being stalked, but you never find anything. You decide to hurry through.";
     }
};


const int MAP_SIZE = 10;
Land* map[MAP_SIZE][MAP_SIZE];

void populateMap(){
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            // TODO: Modify this code to add your new land types
            int randomNum = rand() % 10;
            switch(randomNum){
                case 0: // Forest
                    map[i][j] = new Forest;
                    break;
                case 1: // Lake
                    map[i][j] = new Lake;
                    break;
                    case 2: // Lake
                    map[i][j] = new Plains;
                    break;
                    case 3: // Lake
                    map[i][j] = new Desert;
                    break;
                    case 4: // Lake
                    map[i][j] = new Town;
                    break;
                    case 5: // Lake
                    map[i][j] = new Canyon;
                    break;
                    case 6: // Lake
                    map[i][j] = new MountainPass;
                    break;
                    case 7: // Lake
                    map[i][j] = new Barrens;
                    break;
                    case 8: // Lake
                    map[i][j] = new ForestCave;
                    break;
                    case 9: // Lake
                    map[i][j] = new Rainforest;
                    break;
                default:
                    cout << "Invalid land type selected" << endl;
                    break;
            }
        }
    }
}

int main(){
    srand(time(0));
    
    populateMap();
    
    Player player(MAP_SIZE/2, MAP_SIZE/2);
    
    cout << "You wake up and find yourself lost in the middle of a strange wilderness." << endl;
    
    // TODO: Handle boundary conditions (e.g., if index out of bounds north, you index the south-most location)
    
    while(player.isAlive()){
        cout << "To the north you see " << map[player.x][player.y - 1]->getDescription() << endl;
        cout << "To the east you see " << map[player.x + 1][player.y]->getDescription() << endl;
        cout << "To the south you see " << map[player.x][player.y + 1]->getDescription() << endl;
        cout << "To the west you see " << map[player.x - 1][player.y]->getDescription() << endl;
        
        cout << "Which way will you go? Enter N, E, S, or W:" << endl;
        char userInput;
        cin >> userInput;
        
        switch(userInput){
            case 'N':
                player.y = player.y - 1;
                break;
            case 'E':
                player.x = player.x + 1;
                break;
            case 'S':
                player.y = player.y + 1;
                break;
            case 'W':
                player.x = player.x - 1;
                break;
            default:
                break;
        }
        
        cout << map[player.x][player.y]->visit(player) << endl;
        
        cout << player.getStats() << endl;
        player.takeTurn();
    }
    
    cout << "You died." << endl;
    cout << player.getScore() << endl;
    
    return 0;
}