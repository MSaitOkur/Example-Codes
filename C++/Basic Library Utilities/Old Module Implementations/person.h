#ifndef PERSON_H
#define PERSON_H 

class Person
{
public:
    Person() = default;
    Person(int id, const char *p);

    Person(const Person &other);
    Person(Person&&);
    
    ~Person();

    Person& operator=(const Person& other);
    Person& operator=(Person&& other);
    

    void print() const;
    int get_id() const { return m_id; }

private:
    Person& deep_copy(const Person& other);
    void release_resources();
    int m_id{};
    char *mpa{nullptr};
};

#endif //PERSON_H
