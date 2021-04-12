## Β' Ομάδα Ασκήσεων

Εκφώνηση: http://cgi.di.uoa.gr/~izambo/OOPassgn2_2021.pdf


### Προσωπικά στοιχεία

__Όνομα__: Ιωάννης Δραβίλας

__Α.Μ.__: sdi1900053


### Documentation

__Άσκηση 1:__

A school consists of three floors, a yard and a staircase. Every floor consists of six classrooms and a corridor. Every classroom contains a maximum of Cclass students and a teacher.
Every student is classified either as a junior or a senior one.
Every student and teacher has a fatigue meter (Lj for junior students, Ls for senior students, Lt for teachers).
For every hour a student attends a lesson or a teacher teaches a lesson, the fatigue meter is increased by Lj, Ls or Lt correspondingly.

In a `main()` function, a school and some students and teachers are created. Then the students the teachers enter at it in a random order and the school operates for N hours. Finally, the school life is printed.

Compile and link with `g++ -o assgn2 assgn2.cpp main.cpp`.
The executable `assgn2` is created, which can be executed with `./assgn2 Cclass Lj Ls Lt N`, where Cclass is the maximum number of students in each classroom, Lj, Ls and Lt are the fatigue meters according to which the fatigue of the junior and senior students and teachers are increased, and N are the hours for which the school operates.

E.g. `./assgn2 10 1 2 3 10`.
