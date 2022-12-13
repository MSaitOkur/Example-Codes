#ifndef CAR_H
#define CAR_H

#include <random>
#include <iostream>
#include <memory>

class Car
{
public:
    virtual ~Car() = default;
    virtual Car *clone() = 0;
    virtual std::ostream &print(std::ostream &os) const = 0;
    virtual void start() = 0;
    virtual void run() = 0;
    virtual void stop() = 0;

private:
};

class Bmw : public Car
{
public:
    // virtual Car* clone()override
    // {
    //     return new Bmw{*this};
    // }

    virtual Bmw *clone() override
    {
        return new Bmw{*this};
    }

    std::ostream &print(std::ostream &os) const override
    {
        return os << "I am a Bmw\n";
    }

    void start() override
    {
        std::cout << "Bmw has started\n";
    }
    void run() override
    {
        std::cout << "Bmw is running\n";
    }
    void stop() override
    {
        std::cout << "Bmw has just stopped\n";
    }

private:
};

class Fiat : public Car
{
public:
    // virtual Car* clone()override
    // {
    //     return new Fiat{*this};
    // }
    virtual Fiat *clone() override
    {
        return new Fiat{*this};
    }

    std::ostream &print(std::ostream &os) const override
    {
        return os << "I am a Fiat\n";
    }

    void start() override
    {
        std::cout << "Fiat has started\n";
    }
    void run() override
    {
        std::cout << "Fiat is running\n";
    }
    void stop() override
    {
        std::cout << "Fiat has just stopped\n";
    }

private:
};

class Renault : public Car
{
public:
    // virtual Car* clone()override
    // {
    //     return new Renault{*this};
    // }

    virtual Renault *clone() override
    {
        return new Renault{*this};
    }

    std::ostream &print(std::ostream &os) const override
    {
        return os << "I am a Reanult\n";
    }

    virtual void start() override
    {
        std::cout << "Renault has started\n";
    }
    virtual void run() override
    {
        std::cout << "Renault is running\n";
    }
    virtual void stop() override
    {
        std::cout << "Renault has just stopped\n";
    }

private:
};

class Mercedes : public Car
{
public:
    virtual ~Mercedes() = default;

    // virtual Car* clone()override
    // {
    //     return new Mercedes{*this};
    // }

    virtual Mercedes *clone() override
    {
        return new Mercedes{*this};
    }

    std::ostream &print(std::ostream &os) const override
    {
        return os << "I am a Mercedes\n";
    }

    void open_sunroof()
    {
        std::cout << "Mercedes's sunroof has opened\n";
    }
    virtual void start() override
    {
        std::cout << "Mercedes has started\n";
    }
    virtual void run() override
    {
        std::cout << "Mercedes is running\n";
    }
    virtual void stop() override
    {
        std::cout << "Mercedes has just stopped\n";
    }

private:
};

class Mercedes_S500 : public Mercedes
{
public:
    // virtual Car* clone()override
    // {
    //     return new Mercedes_S500{*this};
    // }

    virtual Mercedes_S500 *clone() override
    {
        return new Mercedes_S500{*this};
    }

    std::ostream &print(std::ostream &os) const override
    {
        return os << "I am a Mercedes_S500\n";
    }

    virtual void start() override
    {
        std::cout << "Mercedes_S500 has started\n";
    }
    virtual void run() override
    {
        std::cout << "Mercedes_S500 is running\n";
    }
    virtual void stop() override
    {
        std::cout << "Mercedes_S500 has just stopped\n";
    }

private:
};

class Audi : public Car
{
public:
    // virtual Car* clone()override
    // {
    //     return new Audi{*this};
    // }

    virtual Audi *clone() override
    {
        return new Audi{*this};
    }

    std::ostream &print(std::ostream &os) const override
    {
        return os << "I am an Audi\n";
    }

    virtual void start() override
    {
        std::cout << "Audi has started\n";
    }
    virtual void run() override
    {
        std::cout << "Audi is running\n";
    }
    virtual void stop() override
    {
        std::cout << "Audi has just stopped\n";
    }

private:
};
class Volvo : public Car
{
public:
    virtual Car *clone() override
    {
        return new Volvo{*this};
    }

    std::ostream &print(std::ostream &os) const override
    {
        return os << "I am a Volvo\n";
    }

    virtual void start() override
    {
        std::cout << "Volvo has started\n";
    }
    virtual void run() override
    {
        std::cout << "Volvo is running\n";
    }
    virtual void stop() override
    {
        std::cout << "Volvo has just stopped\n";
    }

private:
};

inline Car* create_random_car()
{
    static std::mt19937 eng{std::random_device{}()};
    static std::uniform_int_distribution<> dist{0, 6};

    switch(dist(eng)){
        case 0: std::cout << "Mercedes case\n";      return new Mercedes;
        case 1: std::cout << "Mercedes_S500 case\n"; return new Mercedes_S500;
        case 2: std::cout << "Audi case\n";          return new Audi;
        case 3: std::cout << "Fiat case\n";          return new Fiat;
        case 4: std::cout << "Bmw case\n";           return new Bmw;
        case 5: std::cout << "Reanult case\n";       return new Renault;
        case 6: std::cout << "Volvo case\n";         return new Volvo;
        default: return nullptr;
    }

}

inline std::unique_ptr<Car> create_unique_random_car()
{
    static std::mt19937 eng{std::random_device{}()};
    static std::uniform_int_distribution<int> dist{0, 6};

    switch(dist(eng)){
        case 0: std::cout << "Mercedes case\n";      return std::make_unique<Mercedes>();
        case 1: std::cout << "Mercedes_S500 case\n"; return std::make_unique<Mercedes_S500>();
        case 2: std::cout << "Audi case\n";          return std::make_unique<Audi>();
        case 3: std::cout << "Fiat case\n";          return std::make_unique<Fiat>();
        case 4: std::cout << "Bmw case\n";           return std::make_unique<Bmw>();
        case 5: std::cout << "Reanult case\n";       return std::make_unique<Renault>();
        case 6: std::cout << "Volvo case\n";         return std::make_unique<Volvo>();
        default: return nullptr;
    }
}

#endif // CAR_H
