// Ιωάννης Δραβίλας, sdi1900053

#include <iostream>
#include <string>
#include "header.h"
using namespace std;

//////////////////////////////////////////////////////////
////////////CONSTRUCTORS AND DESTRUCTORS//////////////////
/////////////////////////////////////////////////////////

// Constructor
Person::Person(string name_, Floor& floor_, Classroom& classroom_, int Lindex_){
    name = name_;
    floor = &floor_;
    classroom = &classroom_;
    Lindex = Lindex_;
    is_in_classroom = false;
    tired = 0;
}

// Empty destructors for the Base Classes
Person::~Person(){

}

Space::~Space(){

}

// Constructor
School::School(Yard& yard_, Stairs& stairs_, Floor** floors_){
    Yard* yard = &yard_;
    Stairs* stairs = &stairs_;
    // No need for dynamic memory allocation, just a static array with three cells pointing to a floor each
    floors[0] = floors_[0];
    floors[1] = floors_[1];
    floors[2] = floors_[2];
    cout << "A New School has been created!" << endl;
}

// Destructor
School::~School(){
    cout << "A School to be destroyed!" << endl;
}

// Constructor
Student::Student(string name_, Floor& floor_, Classroom& classroom_, int Lindex_):Person(name_, floor_, classroom_, Lindex_){
    cout << "A New Student has been created! " << name << ", Classroom id is " << classroom->get_id() << endl;
}

// Destructor
Student::~Student(){
    cout << "A Student to be destroyed! " << name << endl;
}

// Constructors and destructors for derived classes
StudentJunior::StudentJunior(string name_, Floor& floor_, Classroom& classroom_, int Lindex_):Student(name_, floor_, classroom_, Lindex_){
}

StudentJunior::~StudentJunior(){
}

StudentSenior::StudentSenior(string name_, Floor& floor_, Classroom& classroom_, int Lindex_):Student(name_, floor_, classroom_, Lindex_){
}

StudentSenior::~StudentSenior(){
}

// Constructor
Teacher::Teacher(string name_, Floor& floor_, Classroom& classroom_, int Lindex_):Person(name_, floor_, classroom_, Lindex_){
    // Also change the teacher of the classroom to which this teacher belongs
    classroom->set_teacher(*this);
    cout << "A New Teacher has been created! " << name << ", Classroom id is " << classroom->get_id() << endl;
}

// Destructor
Teacher::~Teacher(){
    cout << "A Teacher to be destroyed! " << name << endl;
}

// Constructor
Classroom::Classroom(int id_){
    id = id_;
    cout << "A New Classroom has been created!" << endl;
}

// Destructor
Classroom::~Classroom(){
    cout << "A Classroom to be destroyed!" << endl;
    // Delete the vector of students
    students.clear();
}

// Constructor
Floor::Floor(int id_, Corridor& corridor_, Classroom** classrooms_){
    id = id_;
    corridor = &corridor_;
    // No need for dynamic allocation, just a static array with six cells, each pointing to a classroom
    for(int i = 0; i < 6; i++){
        classrooms[i] = classrooms_[i];
    }
    cout << "A New Floor has been created!" << endl;
}

// Destructor
Floor::~Floor(){
    cout << "A Floor to be destroyed!" << endl;
}

// Constructor
Yard::Yard(){
    cout << "A New Yard has been created!" << endl;
}

// Destructor
Yard::~Yard(){
    cout << "A Yard to be destroyed!" << endl;
}

// Constructor
Stairs::Stairs(){
    cout << "A New Stairs has been created!" << endl;
}

// Destructor
Stairs::~Stairs(){
    cout << "A Stairs to be destroyed!" << endl;
}

// Constructor
Corridor::Corridor(){
    cout << "A New Corridor has been created!" << endl;
}

// Destructor
Corridor::~Corridor(){
    cout << "A Corridor to be destroyed!" << endl;
}

///////////////////////////////////////////////////////
//////////// CLASS MEMBER FUNCTIONS ///////////////////
///////////////////////////////////////////////////////

void Student::attend(int hours){
    tired += Lindex*hours;
}

void Teacher::teach(int hours){
    tired += Lindex*hours;
}

void School::enter(Student& student_){
    cout << student_.get_name() << " enters school!" << endl;
    // Do the rest for the navigation of the student through the school
    // Access enter() overriding member functions using the scope resolution operator
    yard->Yard::enter(student_);
    yard->exit(student_);
    stairs->Stairs::enter(student_);
    stairs->exit(student_);
    student_.get_floor().Floor::enter(student_);
    student_.get_floor().get_corridor().exit(student_);
    student_.get_classroom().Classroom::enter(student_);
}

void School::place(Teacher& teacher_){
    // Do the rest for the navigation of the teacher through the school
    teacher_.get_floor().place(teacher_);
}

void School::operate(int hours){
    // When a School operates for an amount of hours, its floors operate for the same time
    floors[0]->operate(hours);
    floors[1]->operate(hours);
    floors[2]->operate(hours);
}

void School::print(){
    cout << endl << "School life consists of: " << endl;
    // Print the floors of the School
    floors[0]->print();
    floors[1]->print();
    floors[2]->print();
    cout << endl;
}

void Floor::enter(Student& student_){
    cout << student_.get_name() << " enters floor!" << endl;
    this->corridor->Corridor::enter(student_);
}

void Floor::place(Teacher& teacher_){
    teacher_.get_classroom().place(teacher_);
}

void Floor::operate(int hours){
    // When a Floor operates for an amount of hours, its classrooms operate for the same time
    for(int i = 0; i < 6; i++){
        classrooms[i]->operate(hours);
    }
}

void Floor::print(){
    cout << endl << "=========================" << endl;
    cout << "Floor number " << id << " contains: " << endl;
    cout << "=========================" << endl;
    // Print the classrooms of the Floor
    for(int i = 0; i < 6; i++){
        classrooms[i]->print();
    }
}

Corridor& Floor::get_corridor(){
    return *(this->corridor);
}

void Classroom::enter(Student& student_){
    cout << student_.get_name() << " enters classroom!" << endl;
    // Add this student to the vector of students of this classroom
    this->students.push_back(&student_);
    student_.set_is_in_classroom(true);
}

void Classroom::place(Teacher& teacher_){
    teacher->set_is_in_classroom(true);
}

void Classroom::operate(int hours){
    // When a Classroom operates for an amount of hours, its students attend classes for the same time
    // Vector iteration
    for(vector<Student*>::iterator it = students.begin(); it != students.end(); ++it){
        it[0]->attend(hours);
    }
    // The teacher teaches for the same time
    teacher->teach(hours);
}

void Classroom::print(){
    cout << endl << "People in class " << id << " are: " << endl;
    // Vector iteration to print each student of it
    for(vector<Student*>::iterator it = students.begin(); it != students.end(); ++it){
        it[0]->print();
    }
    cout << "The teacher is: ";
    teacher->print();
}

void Classroom::set_teacher(Teacher& teacher_){
    teacher = &teacher_;
}

int Classroom::get_id(){
    return id;
}

string Person::get_name(){
    return name;
}

void Person::print(){
    cout << name << ", " << tired << endl;
}

bool Person::is_inside_school(){
    return is_in_classroom;
}

void Person::set_is_in_classroom(bool value){
    is_in_classroom = value;
}

Classroom& Person::get_classroom(){
    return *(this->classroom);
}

Floor& Person::get_floor(){
    return *(this->floor);
}

void Corridor::enter(Student& student_){
    cout << student_.get_name() << " enters corridor!" << endl;
}

Student& Corridor::exit(Student& student_){
    cout << student_.get_name() << " exits corridor!" << endl;
    return student_;
}

void Yard::enter(Student& student_){
    cout << student_.get_name() << " enters schoolyard!" << endl;
}

Student& Yard::exit(Student& student_){
    cout << student_.get_name() << " exits schoolyard!" << endl;
    return student_;
}

void Stairs::enter(Student& student_){
    cout << student_.get_name() << " enters stairs!" << endl;
}

Student& Stairs::exit(Student& student_){
    cout << student_.get_name() << " exits stairs!" << endl;
    return student_;
}

// Empty print() functions for the derived classes of the abstract class Space
// Print() at the abstract class is a pure virtual function
void Corridor::print(){
}

void Yard::print(){
}

void Stairs::print(){
}
