// код -> прекомпиляция -> ассемблирование -> линковка
#include <iostream>
#include <vector>

class Citizen;

class City {
private: 
    std::vector<Citizen*> people;
    std::string title;

public:
    City(std::string title_ );

    std::string GetTitle();

    void print();

    void AddResident(Citizen* person);
};    

class Citizen {
private:

    bool is_alive;
    std::string name;
    City *home;
    int health;

public:

    Citizen(std::string name_) : 
            name(name_), health(100), 
            is_alive(true), home(nullptr)
    { // <- constructor. there are some complex information, but may help
// https://en.cppreference.com/w/cpp/language/constructor
// https://en.cppreference.com/w/cpp/language/default_constructor
// https://en.cppreference.com/w/cpp/language/copy_constructor
        std::cout << name_ << " was born\n";
    }
    
    void GetHit(int damage) {
        if (!is_alive) {
            std::cout << name << " is already dead\n";
            return;
        }
        std::cout << name << " is damaged\n";
        health -= damage;
        health = std::max(0, health);

        if (health <= 0) {
            is_alive = false;
            std::cout << name << " was killed\n";
        } 
    }

    int GetHealth() {
        return health;
    }

    void SetHealth(int health_) {
        health = health_;
        health = std::min(100, health);
    }

    void SetHome(City *home_) {
        home = home_;
    }

    void print() const {
        std::cout << "person " << name;
        if (home) std::cout << " who was born in " << home->GetTitle();
        if (is_alive) {
            std::cout << " with health = " << health;
        } else {
            std::cout << " is dead";
        }
        std::cout << '\n';
    }
    
    ~Citizen() { // <- деструктор https://en.cppreference.com/w/cpp/language/destructor
        if (is_alive) {
            std::cout << name << " died\n";
        }
    }
};

// Пример определения после объявления
City::City(std::string title_) : title(title_) {
}

std::string City::GetTitle() {
    return title;
}

void City::print() {
    for (const Citizen* person : people) {
        person->print(); // <=> (*person).print();
    }
}

void City::AddResident(Citizen *person) {
    people.push_back(person);
    person->SetHome(this); // <-- поговорим потом
}

int main() {
    Citizen Ray("Ray");
    Citizen Bob("Bob");
    City Downtown("Downtown");
    Downtown.AddResident(&Ray);
    Downtown.AddResident(&Bob);
    Downtown.print();
}
