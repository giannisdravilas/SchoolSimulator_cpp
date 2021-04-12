// Ιωάννης Δραβίλας, sdi1900053

#include <string>
#include <vector>
using namespace std;

// Forward declaration of some classes
class Floor;
class Classroom;
class Yard;
class Stairs;
class Corridor;
class Student;
class Teacher;

// A base class which represents a person in the school
class Person{
    // A pointer to the floor to which this person belongs
    Floor* floor;
    protected:
        string name;
        // A pointer to the classroom to which this person belongs
        Classroom* classroom;
        // A counter for how much tired this person is
        int tired;
        // The tiring rate of the person
        int Lindex;
        bool is_in_classroom;
    public:
        // Constructor
        Person(string name_, Floor& floor_, Classroom& classroom_, int Lindex_);
        // Destructor
        virtual ~Person();
        // Returns the name of this person
        string get_name();
        void print();
        bool is_inside_school();
        // Set whether this person is in classroom or not
        void set_is_in_classroom(bool value);
        // Return the floor or the classroom to which this person belongs
        Floor& get_floor();
        Classroom& get_classroom();
};

// An abstract base class which represents a space
class Space{
    public:
        virtual ~Space();
        // Every derived class has its own enter() function, so it is a pure virtual function
        virtual void enter(Student& student_) = 0;
        // Every derived class has its own print() function, so it is a pure virtual function
        virtual void print() = 0;
};

// A class School derived from the abstract class Space
class School: public Space{
    // A pointer to the yard, the stairs and the floors of the School
    Yard* yard;
    Stairs* stairs;
    Floor* floors[3];
    public:
        // Constructor
        School(Yard& yard_, Stairs& stairs_, Floor** floors_);
        // Destructor
        ~School();
        // The only navigation functions used by the user // Overriding
        void enter(Student& student_);
        void place(Teacher& teacher_);
        // The amount of hours for which the School operates
        void operate(int);
        // A new print() function, using function overriding
        void print();
};

// A class Student derived from the base class Person
class Student: public Person{
    public:
        // Constructor
        Student(string name_, Floor& floor_, Classroom& classroom_, int Lindex_);
        // Destructor
        ~Student();
        // A Student attends classes for an amount of hours
        void attend(int);
};

// A class for Junior Students derived from the base class Student
class StudentJunior: public Student{
    public:
        // Constructor
        StudentJunior(string name_, Floor& floor_, Classroom& classroom_, int Lindex_);
        // Destructor
        ~StudentJunior();
};

// A class for Senior Students derived from the base class Student
class StudentSenior: public Student{
    public:
        // Constructor
        StudentSenior(string name_, Floor& floor_, Classroom& classroom_, int Lindex_);
        // Destructor
        ~StudentSenior();
};

// A class Teacher derived from the base class Person
class Teacher: public Person{
    public:
        // Constructor
        Teacher(string name_, Floor& floor_, Classroom& classroom_, int Lindex_);
        // Destructor
        ~Teacher();
        // A Teacher teaches for an amount of hours
        void teach(int);
};

// A class Classroom derived from the abstract class Space
class Classroom: public Space{
    // A pointer to the teacher of the classroom
    Teacher* teacher;
    // The id number of the classroom (no comparisons are performed using the id, so it may not be unique)
    int id;
    public:
        // Constructor
        Classroom(int id_);
        // Destructor
        ~Classroom();
        // Returns the id of the Classroom
        int get_id();
        // Sets a teacher for the Classroom
        void set_teacher(Teacher& teacher);
        // A vector containing the students of the Classroom
        vector<Student*> students;
        // Overriding functions used by the simulation for the navigation of the students and teachers through the School
        void enter(Student& student_);
        void place(Teacher& teacher_);
        // The amount of hours for which the Classroom operates
        void operate(int);
        // A new print() function, using function overriding
        void print();
};

// A class Floor derived from the abstract class Space
class Floor: public Space{
    // An array containing pointers to the classrooms of the Floor
    Classroom* classrooms[6];
    // A pointer to the corridor of the Floor
    Corridor* corridor;
    // The id number of the floor (no comparisons are performed using the id, so it may not be unique)
    int id;
    public:
        // Constructor
        Floor(int id_, Corridor& corridor_, Classroom** classrooms_);
        // Destructor
        ~Floor();
        // Overriding functions used by the simulation for the navigation of the students and teachers through the School
        void enter(Student& student_);
        void place(Teacher& teacher_);
        // The amount of hours for which the Floor operates
        void operate(int);
        // A new print() function, using function overriding
        void print();
        // Returns the corridor of the floor
        Corridor& get_corridor();
};

// A class Corridor derived from the abstract class Space
class Corridor: public Space{
    // A new print() function, using function overriding
    void print();
    public:
        // Constructor and Destructor
        Corridor();
        ~Corridor();
        // Overriding functions used by the simulation for the navigation of the students through the School
        void enter(Student& student_);
        Student& exit(Student& student_);
};

// A class Stairs derived from the abstract class Space
class Stairs: public Space{
    // A new print() function, using function overriding
    void print();
    public:
        // Constructor and Destructor
        Stairs();
        ~Stairs();
        // Overriding functions used by the simulation for the navigation of the students through the School
        void enter(Student& student_);
        Student& exit(Student& student_);
};

// A class Yard derived from the abstract class Space
class Yard: public Space{
    // A new print() function, using function overriding
    void print();
    public:
        // Constructor and Destructor
        Yard();
        ~Yard();
        // Overriding functions used by the simulation for the navigation of the students through the School
        void enter(Student& student_);
        Student& exit(Student& student_);
};