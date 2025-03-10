#include <iostream>
#include <string>
#include <ctime>
#include <cassert>
using namespace std;

template <class T>
class SmartArray
{
private:
	T *A;
	int size;

public:
	//Constructors
	SmartArray(); 
	SmartArray(const SmartArray<T>&); //Copy constructor: Deep copy of the argument

	//Assignment operator
	SmartArray<T>& operator = (const SmartArray<T>&); //Assignment operator. Memory clean up and deep copy of the argument

	//Destructor
	~SmartArray(); //Destructor. Memory clean up

	//Getters, Setters, operators and other functions
	int getSize() const; //Return the size of the calling object
	T& operator[](const int&) const; //Assert index is valid and then return the element at the given index
	int find(const T&) const; //Return the index of the element that is == to the argument. Return -1 if not found.
	void append(const T&); //Append the argument to the calling object.
	bool remove(const int&); //If the index argument is a valid index, then remove the element at the index argument
							//from the calling object and return true. Otherwise return false. 
							//You don't need to assert the index argument.
	bool operator == (const SmartArray<T>&) const; //return true if sizes are equal and elements at same indexes are ==
	
	template <class TF>
	friend ostream& operator << (ostream&, const SmartArray<TF>&); //Implemented for you
};

//Constructors
template <class T>
SmartArray<T>::SmartArray()
{
    this->A = nullptr;
    this->size = 0;
}

template <class T>
SmartArray<T>::SmartArray(const SmartArray<T> &sArr)
{
    this->size = sArr.getSize();
    if(this->getSize() > 0)
    {
        this->A = new T[this->getSize()];
        for(int i(0); i < size; i++)
            this->A[i] = sArr[i];
    }
    
}

//Assignment Operator
template <class T>
SmartArray<T>& SmartArray<T>::operator = (const SmartArray<T> &sArr)
{
    //Check for self assingment. If so, do nothing.
    if (this == &sArr)
        return *this;
    //Delete the left hand side object's memory
    this->~SmartArray();
    //Now copy the right hand side to the left
    this->size = sArr.getSize();
    if (this->getSize() > 0)
    {
        this->A = new T[this->getSize()];
        for(int i(0); i < this->getSize(); i++)
            this->A[i] = sArr[i];
    }
    return *this;
}

//Destructor
template <class T>
SmartArray<T>::~SmartArray()
{
    if (this->getSize() > 0)
    {
        delete[] this->A;
        this->size = 0;
    }
}

//Getters, Setters, Operators and other functions
template <class T>
int SmartArray<T>::getSize() const
{
    return this->size;
}

template <class T>
T& SmartArray<T>::operator[](const int &index) const 
{
	assert(index > 0 || index < this->getSize());
    return this->A[index];
}

template <class T>
int SmartArray<T>::find(const T &e) const
{
    for (int i(0); i < this->getSize(); i++)
        if (this->A[i] == e)
            return i;   
    return -1; 
}

template <class T>
void SmartArray<T>::append(const T &e)
{
    T *temp = new T[this->getSize() + 1];
    
    for(int i(0); i < this->getSize(); i++)
        temp[i] = this->A[i];
    
    temp[this->getSize()] = e;
    
    if (this->getSize() > 0)
        delete[] this->A;
    
    this->A = temp;
    this->size += 1;
}

template <class T>
bool SmartArray<T>::remove(const int &index)
{
	if(index < 0 || index >= this->getSize())
        return false;
    else
    {
        T *temp = new T[this->getSize() - 1];
        
        for(int i(0); i < index; i++)
            temp[i] = this->A[i];
		for(int i(index+1); i < this->getSize(); i++)
			temp[i-1] = this->A[i];
        
        if(this->getSize() > 0)
            delete[] this->A;
        
        this->A = temp;
        this->size -= 1;
        return true;
    }
}

template <class T>
bool SmartArray<T>::operator == (const SmartArray<T> &sArr) const
{
    if(this->getSize() != sArr.getSize())
        return false;
    else
    {
        for(int i(0); i < this->getSize(); i++)
            if (A[i] != sArr[i])
                return  false;
    }
    return true;
}

template <class TF>
ostream& operator << (ostream& out, const SmartArray<TF>& L)
{
    if (L.getSize() == 0)
        out << "[Empty List]";
    else
    {
        for (int i = 0; i < L.getSize()-1; i++)
            out << L[i] << endl;
        out << L[L.getSize()-1] << endl;
    }
    return out;
}

////
template <class K, class V>
class Map
{
private:
	SmartArray<K> A1;	//The keys of the map
	SmartArray<V> A2;	//The values of the map
	
public:
	//Constructors
	Map();
	Map(const Map<K, V>&); //Copy constructor. Deep copy.

	//Assignment operator
	Map<K, V>& operator = (const Map<K, V>&); //Assignment operator. Memory clean up and deep copy.

	//Destructor
	~Map();

	//Getters, Setters, operators and other functions
	int getSize() const; //Return the common size of the map.
	int findKey(const K&) const; //Return the index of the first element of the Keys array == the argument. Return -1 if not found.
	int findValue(const V&) const; //Return the index of the first element of the Values array == the argument. Return -1 if not found.
	K getKey(const V&) const; //Assert the argument is found in the Values array and then return the key with the given value 
	V getValue(const K&) const; //Assert the argument is found in the Keys array and then return the value with the given key
	K getKeyAtIndex(const int&) const; //Assert the index argument and then return the key at the given index
	V getValueAtIndex(const int&) const; //Assert the index argument and then return the value at the given index
	void setKeyAtIndex(const int&, const K&); //Assert the index argument and then set the key at the given index
	void setValueAtIndex(const int&, const V&); //Assert the index argument and then set the value at the given index
	void append(const K&, const V&); //Append the key-value pair to the calling object
	bool remove(const int&); //If the index argument is a valid index, then remove the key-value pair at the index argument
							//from the calling object and return true. Otherwise return false. 
							

	template <class KF, class VF>
	friend ostream& operator << (ostream&, const Map<KF, VF>&);
};

//Constructors
template <class K, class V>
Map<K, V>::Map()
{
	//The member variables will automatically be initialized as default objects
}

template <class K, class V>
Map<K, V>::Map(const Map<K, V> &M)
{
	A1 = M.A1;
	A2 = M.A2;
}

//Assignment operator
template<class K, class V>
Map<K, V>& Map<K, V>::operator = (const Map<K, V> &M)
{
	this->~Map();
	A1 = M.A1;
	A2 = M.A2;
	return *this;
}

//Destructor
template<class K, class V>
Map<K, V>::~Map()
{
	if(this->A1.getSize() > 0)
	{
		A1.~SmartArray();
	}
	if(this->A2.getSize() > 0)
	{
		A1.~SmartArray();
	}
}

//Getters, Setters, Other functions
template<class K, class V>
int Map<K, V>::getSize() const 
{
	return A1.getSize();
}

template<class K, class V>
int Map<K, V>::findKey(const K &key) const
{
	return this->A1.find(key);
}

template<class K, class V>
int Map<K, V>::findValue(const V &value) const 
{
	return this->A2.find(value);
}

template<class K, class V>
K Map<K, V>::getKey(const V &value) const 
{
	assert(this->A2.find(value));
	return A1[this->A2.find(value)];
}

template<class K, class V>
V Map<K, V>::getValue(const K &key) const
{
	assert(this->A1.find(key));
	return A2[this->A1.find(key)];
}

template<class K, class V>
K Map<K, V>::getKeyAtIndex(const int &index) const
{												  
	assert(index < A1.getSize());
	return A1[index];
}

template<class K, class V>
V Map<K, V>::getValueAtIndex(const int &index) const  
{
	assert(index < A2.getSize());
	return A2[index];
}

template<class K, class V>
void Map<K, V>::setKeyAtIndex(const int &index, const K &key) 
{
	assert(index < A1.getSize());
	A1[index] = key;
}

template<class K, class V>
void Map<K, V>::setValueAtIndex(const int &index, const V &value) 
{
	assert(index < A2.getSize());
	A2[index] = value;
}

template<class K, class V>
void  Map<K, V>::append(const K &key, const V &value) 
{
	this->A1.append(key);
	this->A2.append(value);
}

template<class K, class V>
bool  Map<K, V>::remove(const int &index) 
{
	if(index < A2.getSize() && index >= 0)
	{
		this->A1.remove(index);
		this->A2.remove(index);
		return true;
	}
	else
		return false;
}						

//Operator
template <class KF, class VF>
ostream& operator << (ostream& out, const Map<KF, VF>& m)
{
	if (m.getSize() == 0)
		out << "[Empty Map]" << endl;
	else
	{
		for (int i = 0; i < m.getSize(); i++)
			out << m.A1[i] << ", " << m.A2[i] << endl;
	}
	return out;
}



///
class Course
{
private:
	string name;
	int creditHours;
public:
	Course();
	Course(const string&, const int&);
	string getCourseName() const;
	int getCreditHours() const;
	void setCourseName(const string&);
	void setCreditHours(const int&);
	bool operator == (const Course&) const; //Return true if course names are equal and credit hours are also equal.
	friend ostream& operator << (ostream&, const Course&);
};

//Constructors
Course::Course()
{
	name = "None";
	creditHours = 0;
}

Course::Course(const string &name, const int &hours)
{
	this->name = name;
	this->creditHours = hours;
}

//Getters
string Course::getCourseName() const
{
	return this->name;
}

int Course::getCreditHours() const
{
	return this->creditHours;
}

//Setters
void Course::setCourseName(const string &name)
{
	this->name = name;
}
void Course::setCreditHours(const int &hours)
{
	this->creditHours = hours;
}

//Operator and Friend functions
bool Course::operator == (const Course &c) const 
{
	if(c.getCourseName() == this->name && c.getCreditHours() == creditHours)
		return true;
	else
		return false;
}

ostream& operator << (ostream& out, const Course& c)
{
	out << "Course Name = " << c.name << ", Credit Hours = " << c.creditHours;
	return out;
}

///
struct Date
{
	int y, m, d;
};

///
class Student
{
private:
	string fn, ln; //first name and last name
	Date dob;
public:
	Student();
	Student(const string& firstName, const string& lastName, const Date&);
	string getFirstName() const;
	string getLastName() const;
	Date getDob() const;
	void setFirstName(const string&);
	void setLastName(const string&);
	void setDob(const Date&);
	bool operator == (const Student&) const; //Return true if all the first names, last names, and date of births are equal
	friend ostream& operator << (ostream&, const Student&);
};

//Constructors
Student::Student()
{
	fn = "None";
	ln = "None";
	dob.y = 0;
	dob.m = 0;
	dob.d = 0;
}

Student::Student(const string &firstName, const string &lastName, const Date &D) 
{
	this->fn = firstName;
	this->ln = lastName;
	this->dob = D;
}

//Getters
string Student::getFirstName() const
{
	return fn;
}

string Student::getLastName() const
{
	return ln;
}

Date Student::getDob() const
{
	return dob;
}

//Setters
void Student::setFirstName(const string &firstName)
{
	this-> fn = firstName;
}

void Student::setLastName(const string &lastName)
{
	this->ln = lastName;
}

void Student::setDob(const Date &date)
{
	this->dob = date;
}

//Operator and Friend functions
bool Student::operator == (const Student &s) const 
{
	if(this->fn == s.getFirstName() && this->ln == s.getLastName() && this->dob.d == s.getDob().d && this->dob.m == s.getDob().m && this->dob.y == s.getDob().y)
		return true;
	else
		return false;
}

ostream& operator << (ostream& out, const Student& s)
{
	out << "Full Name = " << s.fn << " " << s.ln << ": ";
	out << "DOB (d-m-y) = " << s.dob.d << "-" << s.dob.m << "-" << s.dob.y;
	return out;
}

///
typedef Map<int, char> StudentMap;

///

class SchoolManagementSystem
{
private:
	SmartArray<Student> studentList; //A SmartArray to store the students in the school
	SmartArray<Course> courseList; //A SmartArray to store the courses in the school
	SmartArray<StudentMap> studentMapList; //A SmartArray to store the students' maps

public:
	//Constructors
	SchoolManagementSystem();

	//Getters
	int getNumberOfRegisteredStudents() const;
	int getNumberOfCoursesOffered() const;
	int findStudent(const string &firstName, const string &lastName) const;
	Student getStudent(const int &studentIndex) const;
	StudentMap getStudentMap(const int &studentIndex) const;
	int findCourse(const string &courseName) const;
	Course getCourse(const int &courseIndex) const;
	double getStudentGPA(const int &studentIndex) const;
	int getTopStudentIndex() const;
	
	//Setters
	bool registerStudent(const Student &s);
	bool enrolStudent(const int &studentIndex, const int &courseIndex); 
	bool assignLetterGrade(const int &studentIndex, const int &courseIndex, const char &letterGrade);
	bool offerCourse(const Course &course);
	void removeStudent(const int &studentIndex);  
	bool withdrawStudent(const int &studentIndex, const int &courseIndex); 
	void removeCourse(const int &courseIndex); 

	//Static functions
	static Student generateRandomStudent();
	static char generateRandomLetterGrade();

	//Friend functions
	friend ostream& operator << (ostream &, const SchoolManagementSystem &);
};
//Constructors
SchoolManagementSystem::SchoolManagementSystem()
{}

//Getters
int SchoolManagementSystem::getNumberOfRegisteredStudents() const
{
	return studentList.getSize();
}

int SchoolManagementSystem::getNumberOfCoursesOffered() const
{
	return courseList.getSize();
}

int SchoolManagementSystem::findStudent(const string &firstName, const string &lastName) const
{
	for(int i(0); i < studentList.getSize(); i++)
		if(studentList[i].getFirstName() == firstName && studentList[i].getLastName() == lastName)
			return i;
	return -1;
}

Student SchoolManagementSystem::getStudent(const int &studentIndex) const
{
	assert(studentIndex < this->studentList.getSize() || studentIndex > 0);
	return this->studentList[studentIndex];
}

StudentMap SchoolManagementSystem::getStudentMap(const int &studentIndex) const
{
	assert(studentIndex < this->studentList.getSize() || studentIndex > 0);
	return this->studentMapList[studentIndex];
}

int SchoolManagementSystem::findCourse(const string &courseName) const
{
	for(int i(0); i < this->courseList.getSize(); i++)
		if(courseList[i].getCourseName() == courseName)
			return i;
	return -1;
}

Course SchoolManagementSystem::getCourse(const int &courseIndex) const
{
	assert(courseIndex < this->courseList.getSize() || courseIndex > 0);
	return courseList[courseIndex];
}

double SchoolManagementSystem::getStudentGPA(const int &studentIndex) const
{
	assert(studentIndex < this->studentList.getSize() || studentIndex > 0); 
	//Student doesnt have any courses
	if(studentMapList[studentIndex].getSize() == 0)
		return 0.0;
	
	double creditHours = 0;
	double creditPoints = 0;
	int nCourses = 0; 

	for(int i(0); i < studentMapList[studentIndex].getSize(); i++)
	{
		double temp;
		if(studentMapList[studentIndex].getValueAtIndex(i) == 'N')
		{
			nCourses++;
			continue;
		}
		else if(studentMapList[studentIndex].getValueAtIndex(i) == 'A')
		{
			temp = courseList[studentMapList[studentIndex].getKeyAtIndex(i)].getCreditHours();
			creditHours += temp;
			creditPoints += temp*4.0;
		}
		else if(studentMapList[studentIndex].getValueAtIndex(i) == 'B')
		{
			temp = courseList[studentMapList[studentIndex].getKeyAtIndex(i)].getCreditHours();
			creditHours += temp;
			creditPoints += temp*3.0;
		}
		else if(studentMapList[studentIndex].getValueAtIndex(i) == 'C')
		{
			temp = courseList[studentMapList[studentIndex].getKeyAtIndex(i)].getCreditHours();
			creditHours += temp;
			creditPoints += temp*2.0;
		}
		else if(studentMapList[studentIndex].getValueAtIndex(i) == 'D')
		{
			temp = courseList[studentMapList[studentIndex].getKeyAtIndex(i)].getCreditHours();
			creditHours += temp;
			creditPoints += temp*1.0;
		}
		else if(studentMapList[studentIndex].getValueAtIndex(i) == 'F')
		{
			temp = courseList[studentMapList[studentIndex].getKeyAtIndex(i)].getCreditHours();
			creditHours += temp;
			creditPoints += temp*0.0;
		}
	}
	if(nCourses == studentMapList[studentIndex].getSize() || creditHours == 0)
		return 0.0; 
	return (creditPoints/creditHours);

}

int SchoolManagementSystem::getTopStudentIndex() const
{
	assert(studentList.getSize() > 0);
	double max;
	int index = 0;
	max = (*this).getStudentGPA(0);

	for(int i(0); i < studentList.getSize(); i++)
	{
		if((*this).getStudentGPA(i) > max)
		{
			max = (*this).getStudentGPA(i);
			index = i;
		}
	}
	return index;
}

//Setters
bool SchoolManagementSystem::registerStudent(const Student &s)
{
	StudentMap temp;
	if(this->studentList.find(s) != -1)
		return false;
	else
	{
		studentList.append(s);
		studentMapList.append(temp);
		return true;
	}
}

bool SchoolManagementSystem::enrolStudent(const int &studentIndex, const int &courseIndex)
{
	assert(studentIndex < this->studentList.getSize() || studentIndex > 0);
	assert(courseIndex < this->courseList.getSize() || courseIndex > 0);

	if(this->studentMapList[studentIndex].findKey(courseIndex) != -1)
		return false;
	else
	{
		studentMapList[studentIndex].append(courseIndex, 'N');
		return true;
	}
}

bool SchoolManagementSystem::assignLetterGrade(const int &studentIndex, const int &courseIndex, const char &letterGrade)
{
	assert(studentIndex < this->studentList.getSize() || studentIndex > 0);
	assert(courseIndex < this->courseList.getSize() || courseIndex > 0);
	assert(letterGrade == 'A' || letterGrade == 'B' || letterGrade == 'C'  || letterGrade == 'D' || letterGrade == 'F');

	if(studentMapList[studentIndex].findKey(courseIndex) == -1)
		return false;
	else
	{
	studentMapList[studentIndex].setValueAtIndex(studentMapList[studentIndex].findKey(courseIndex), letterGrade);
		return true;
	}
	
}

bool SchoolManagementSystem::offerCourse(const Course &course)
{
	if(courseList.find(course) == -1)
	{
		courseList.append(course);
		return true;
	}
	else
		return false;
}

void SchoolManagementSystem::removeStudent(const int &studentIndex)
{
	assert(studentIndex < this->studentList.getSize() || studentIndex > 0);

	this->studentList.remove(studentIndex);
	this->studentMapList.remove(studentIndex);
}

bool SchoolManagementSystem::withdrawStudent(const int &studentIndex, const int &courseIndex)
{
	assert(studentIndex < this->studentList.getSize() || studentIndex > 0);
	assert(courseIndex < this->courseList.getSize() || courseIndex > 0);

	if (this->studentMapList[studentIndex].findKey(courseIndex) == -1)
		return false;
	else
	{
		this->studentMapList[studentIndex].remove(studentMapList[studentIndex].findKey(courseIndex));
		return true;
	}
}

void SchoolManagementSystem::removeCourse(const int &courseIndex)
{
	assert(courseIndex < this->courseList.getSize() || courseIndex > 0);
	//Withdraws every student from the course at the courseIndex argument
	for(int i(0); i < studentMapList.getSize(); i++)
	{
		for(int j(0); j < studentMapList[i].getSize(); j++)
		{
			if(studentMapList[i].getKeyAtIndex(j) == courseIndex)
				(*this).withdrawStudent(i, courseIndex);
		}
	}
	//Removes the element of the courseList SmartArray member variable at CourseIndex argument
	this->courseList.remove(courseIndex);

	//Decrement each key value greater than courseIndex argument from all students map
	int key;
	for(int i(0); i < studentMapList.getSize(); i++)
	{
		for(int j(0); j < studentMapList[i].getSize(); j++)
		{
			if(studentMapList[i].getKeyAtIndex(j) > courseIndex)
			{
				key = studentMapList[i].getKeyAtIndex(j);
				this->studentMapList[i].setKeyAtIndex(j, (key-1));
			}
		}
	}
}

//Friend Functions and Other Functions
ostream& operator << (ostream &out, const SchoolManagementSystem &sms)
{
	out << endl << "Students List" << endl;
	if (sms.studentList.getSize() == 0)
		out << "No student has been registered yet." << endl;
	for (int studentIndex = 0; studentIndex < sms.studentList.getSize(); studentIndex++)
		out << "Student at index " << studentIndex << ": " << sms.studentList[studentIndex] << endl;

	out << endl << "Courses List" << endl;
	if (sms.courseList.getSize() == 0)
		out << "No course has been offered yet." << endl;
	for (int courseIndex = 0; courseIndex < sms.courseList.getSize(); courseIndex++)
		out << "Course at index " << courseIndex << ": " << sms.courseList[courseIndex] << endl;

	cout << endl << "Students Map" << endl;
	if (sms.studentMapList.getSize() == 0)
		out << "No student is enrolled in any course yet." << endl;
	for (int studentIndex = 0; studentIndex < sms.studentMapList.getSize(); studentIndex++)
	{
		out << "Student at index " << studentIndex << endl;
		out << sms.studentMapList[studentIndex];
		out << "GPA = " << sms.getStudentGPA(studentIndex) << endl << endl;
	}
	return out;
}

Student SchoolManagementSystem::generateRandomStudent()
{
	string fn, ln;
	Date dob;

	fn = rand() % 26 + 65;
	for (int i = 0; i < 9; i++)
		fn += char(rand() % 26 + 97);

	ln = rand() % 26 + 65;
	for (int i = 0; i < 9; i++)
		ln += char(rand() % 26 + 97);

	dob.y = 1998 + rand() % 5;
	dob.m = 1 + rand() % 12;
	dob.d = 1 + rand() % 30;

	return Student(fn, ln, dob);
}

char SchoolManagementSystem::generateRandomLetterGrade()
{
	int g = rand() % 11;
	if (g == 0)
		return 'A';
	else if (g <= 2)
		return'B';
	else if (g <= 5)
		return'C';
	else if (g <= 7)
		return 'D';
	else
		return 'F';
}

///
int main()
{
	cout << "Welcome to Phantom College School Management System" << endl;
	cout << "===================================================" << endl;

	srand(1);
	const int STUDENT_SIZE = 10;
	const int COURSE_SIZE = 16;

	//Prepare the courses offered in the school
	Course course[] = {Course("CMPT120", 2), Course("CMPT130", 3), Course("CMPT135", 4),
		Course("MACM101", 2), Course("CALC151", 3), Course("CALC152", 4),
				  Course("MATH242", 4), Course("ECON101", 3), Course("ECON102", 4),
				  Course("ENGL100", 2), Course("HIST101", 3), Course("PHYS100", 2),
				  Course("PHYS101", 3), Course("PHYS102", 4), Course("CHEM101", 3),
				  Course("CHEM102", 4)};

	//Construct and print a school management system object
	SchoolManagementSystem sms;
	cout << sms << endl;

	//Add courses offered into the system
	for (int i = 0; i < COURSE_SIZE; i++)	//there are 16 courses initially
	{
		bool flag = sms.offerCourse(course[i]);
		if (flag)
			cout <<"Course offering successful." << endl;
		else
			cout << "Course offering failed. The same course already exists in the system." << endl;
	}
	cout << endl << "Some courses have been offered and added in to the system." << endl;
	cout << "The updated system information is..." << endl;
	cout << sms << endl;

	//See if CMPT135 course is offered in the school
	int courseIndex = sms.findCourse("CMPT225");
	if (courseIndex == -1)
		cout << "CMPT225 course is not offered in the school." << endl << endl;
	else
	{
		cout << "CMPT225 course is offered in the school. Details below..." << endl;
		cout << sms.getCourse(courseIndex) << endl;
	}

	//See if a randomly chosen course is offered in the school
	int randomCourseIndex = rand() % sms.getNumberOfCoursesOffered();
	Course c = sms.getCourse(randomCourseIndex);
	courseIndex = sms.findCourse(c.getCourseName());
	if (courseIndex == -1)
		cout << c.getCourseName() << " course is not offered in the school." << endl << endl;
	else
	{
		cout << c.getCourseName() << " course is offered in the school. Details below..." << endl;
		cout << sms.getCourse(courseIndex) << endl << endl;
	}

	//Register some new students into the system
	for (int i = 0; i < STUDENT_SIZE; i++)
	{
		bool flag = sms.registerStudent(Student(sms.generateRandomStudent()));
		if (flag)
			cout <<"Student registration successful." << endl;
		else
			cout << "Student registration failed. The same student already exists in the system." << endl;
	}
	cout << endl << "Some students have been registered in to the system." << endl;
	cout << "The updated system information is..." << endl;
	cout << sms << endl;
	
	//See if Robert Kazik is a student in the school
	int studentIndex = sms.findStudent("Robert", "Kazik");
	if (studentIndex == -1)
		cout << "Robert Kazik is not a student in the school." << endl << endl;
	else
	{
		cout << "Robert Kazik is a student in the school. Details below..." << endl;
		cout << sms.getStudent(studentIndex) << endl;
		cout << sms.getStudentMap(studentIndex) << endl;
		cout << "GPA = " << sms.getStudentGPA(studentIndex) << endl << endl;
	}

	//See if a randomly chosen student is a student in the school
	int randomStudentIndex = rand() % sms.getNumberOfRegisteredStudents();
	Student s = sms.getStudent(randomStudentIndex);
	studentIndex = sms.findStudent(s.getFirstName(), s.getLastName());
	if (studentIndex == -1)
		cout << s.getFirstName() << " " << s.getLastName() << " is not a student in the school." << endl << endl;
	else
	{
		cout << s.getFirstName() << " " << s.getLastName() << " is a student in the school. Details below..." << endl;
		cout << sms.getStudent(studentIndex) << endl;
		cout << sms.getStudentMap(studentIndex);
		cout << "GPA = " << sms.getStudentGPA(studentIndex) << endl << endl;
	}

	//Enroll students to some courses
	for (int studentIndex = 0; studentIndex < sms.getNumberOfRegisteredStudents(); studentIndex++)
	{
		int numberOfCourses = rand() % (sms.getNumberOfCoursesOffered()/2);
		for (int i = 0; i < numberOfCourses; i++)
		{
			int courseIndex = rand() % sms.getNumberOfCoursesOffered();
			sms.enrolStudent(studentIndex, courseIndex);
		}
	}
	cout << endl << "Some students have been enrolled in to some courses." << endl;
	cout << "The updated system information is..." << endl;
	cout << sms << endl;
	
	//Assign letter grades to the students
	for (int studentIndex = 0; studentIndex < sms.getNumberOfRegisteredStudents(); studentIndex++)
	{
		if (rand() % 4 == 0)
		{
			cout << "Skipping a student from letter grade assignments." << endl;
			continue;
		}
		int n = sms.getStudentMap(studentIndex).getSize(); //Assign letter grades to each course the student is enrolled in
		for (int j = 0; j < n; j++)
		{
			if (rand() % 5 == 0)
			{
				cout << "Skipping a course from letter grade assignment." << endl;
				continue;
			}
			int courseIndex = sms.getStudentMap(studentIndex).getKeyAtIndex(j);
			sms.assignLetterGrade(studentIndex, courseIndex, sms.generateRandomLetterGrade());
		}
	}
	cout << endl << "Students have been assigned letter grades." << endl;
	cout << "The updated system information is..." << endl;
	cout << sms << endl;
	
	
	
	for (int i = 0; i < STUDENT_SIZE/2; i++)
	{
		if (sms.getNumberOfRegisteredStudents() == 0)
			continue;	//There is no any student in the system so we don't need to do anything

		//Remove a randomly chosen student from the system
		randomStudentIndex = rand() % sms.getNumberOfRegisteredStudents();
		sms.removeStudent(randomStudentIndex);
		cout << endl << "The student at index " << randomStudentIndex << " has been removed from the system." << endl;
		cout << "The updated system information is..." << endl;
		cout << sms << endl;

		if (sms.getNumberOfRegisteredStudents() == 0 || sms.getNumberOfCoursesOffered() == 0)
			continue;	//There is no any student or any course in the system so we don't need to do anything
		
		//Withdraw a student from a course
		randomStudentIndex = rand() % sms.getNumberOfRegisteredStudents();
		s = sms.getStudent(randomStudentIndex);
		studentIndex = sms.findStudent(s.getFirstName(), s.getLastName());
		if (studentIndex == -1)
			cout << s.getFirstName() << " " << s.getLastName() << " is not a student in the school." << endl << endl;
		else
		{
			cout << s.getFirstName() << " " << s.getLastName() << " is a student in the school. Details below..." << endl;
			cout << sms.getStudent(studentIndex) << endl;
			cout << sms.getStudentMap(studentIndex) << endl;

			if (sms.getStudentMap(studentIndex).getSize() == 0)
				continue; //The specified student is not enrolled in any course so nothing to do
			
			int randomCourseMapIndex = rand() % sms.getStudentMap(studentIndex).getSize();
			int courseIndex = sms.getStudentMap(studentIndex).getKeyAtIndex(randomCourseMapIndex);
			bool flag = sms.withdrawStudent(studentIndex, courseIndex);
			if (!flag)
				cout << "Withdrawing the student at index " << studentIndex << " from the course at index " << courseIndex << " failed." << endl << endl;
			else
			{
				cout << "Student at index " << studentIndex << " withdrawn from the course at index " << courseIndex << endl;
				cout << "The updated information for the student is now..." << endl;
				cout << sms.getStudent(studentIndex) << endl;
				cout << sms.getStudentMap(studentIndex) << endl;
			}
			
		}
		
		//Remove a randomly chosen course from the system
		randomCourseIndex = rand() % sms.getNumberOfCoursesOffered();
		c = sms.getCourse(randomCourseIndex);
		sms.removeCourse(randomCourseIndex);
		cout << c.getCourseName() << " has been removed from the system." << endl;
		cout << "The system has been updated. Below is the updated system information..." << endl;
		cout << sms << endl;
		
		//Compute and print the top student
		int topStudentIndex = sms.getTopStudentIndex();
		cout << "The top student is..." << endl;
		cout << sms.getStudent(topStudentIndex) << endl;
		cout << "GPA = " << sms.getStudentGPA(topStudentIndex) << endl << endl;
	
	}
	

	//system("Pause");
	return 0;
}