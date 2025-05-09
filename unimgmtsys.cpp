#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <ctime>

class Person;
class Student;
class Professor;
class Course;
class Department;
class Classroom;

class EnrollmentException : public std::runtime_error {
public:
    EnrollmentException(const std::string& message) : std::runtime_error(message) {}
};

class GradeBookException : public std::runtime_error {
public:
    GradeBookException(const std::string& message) : std::runtime_error(message) {}
};

class PersonException : public std::runtime_error {
public:
    PersonException(const std::string& message) : std::runtime_error(message) {}
};

class Logger {
public:
    static void log(const std::string& message) {
        std::ofstream file("log.txt", std::ios::app);
        file << message << std::endl;
    }
};

class Person {
private:
    std::string name;
    int age;
    std::string ID;
    int contactInfo;

public:
    Person() : name(""), age(0), ID(""), contactInfo(0) {}
    
    Person(std::string name, int age, std::string ID, int contactInfo) {
        (age > 0 && age < 120) ? this->age = age : this->age = -1;
        (name.length() > 0) ? this->name = name : this->name = "invalid Name";
        
       
        if (ID.length() < 5) {
            throw PersonException("invalid ID");
        }
        this->ID = ID;
        
      
        if (contactInfo <= 0) {
            throw PersonException("Invalid contact information");
        }
        this->contactInfo = contactInfo;
    }
    
    virtual void display() const {
        std::cout << "Name: " << name << std::endl;
        std::cout << "Age: " << age << std::endl;
        std::cout << "ID: " << ID << std::endl;
        std::cout << "Contact Information: " << contactInfo << std::endl;
    }
    
    virtual float calculatePayment() const {
        try {
            return 0.0;
        } catch (...) {
            throw PersonException("Error");
        }
    }
    
    std::string getID() const { return ID; }
    std::string getName() const { return name; }
    
    virtual ~Person() {}
};


class Professor : public Person {
private:
    std::string dept;
    std::string specialization;
    std::string hireDate;
    int experience;
    
public:
    Professor() : Person(), dept(""), specialization(""), hireDate(""), experience(0) {}
    
    Professor(std::string name, int age, std::string ID, int contactInfo,
              std::string dept, std::string specialization, std::string hireDate)
        : Person(name, age, ID, contactInfo) {
        this->dept = dept;
        this->specialization = specialization;
        this->hireDate = hireDate;
        this->experience = 0;
    }
    
    void display() const override {
        Person::display();
        std::cout << "Department: " << dept << std::endl;
        std::cout << "Specialization: " << specialization << std::endl;
        std::cout << "Hire Date: " << hireDate << std::endl;
        std::cout << "Experience: " << experience << std::endl;
    }
    
    float calculatePayment() const override {
        try {
            float baseSalary = 5000.0;
            float serviceBonus = experience * 100.0; 
            return baseSalary + serviceBonus;
        } catch (...) {
            throw PersonException("Error");
        }
    }
    
    std::string getDept() const { return dept; }
    std::string getSpecialization() const { return specialization; }
    std::string getHireDate() const { return hireDate; }
    
    void setexperience(int years) {
        if (years < 0) {
            throw PersonException("Invalid experience");
        }
        experience = years;
    }
    
    int getexperience() const { return experience; }
    
    ~Professor() {}
};

class Student : public Person {
private:
    std::string enrollDate;
    float cgpa;
    std::string program;
    std::vector<class Course*> enrolledCourses; 
    
public:
    Student() : Person(), enrollDate(""), cgpa(0.0), program("") {}
    
    Student(std::string name, int age, std::string ID, int contactInfo,
            std::string enrollDate, float cgpa, std::string program)
        : Person(name, age, ID, contactInfo) {
        if (cgpa < 0.0 || cgpa > 10.0) {
            throw PersonException("Invalid cgpa");
        }
        this->cgpa = cgpa;
        this->enrollDate = enrollDate;
        this->program = program;
    }
    
    void display() const override {
        Person::display();
        std::cout << "Enrollment Date: " << enrollDate << std::endl;
        std::cout << "cgpa: " << cgpa << std::endl;
        std::cout << "Program: " << program << std::endl;
    }
    
    float calculatePayment() const override {
        try {
            return -1000.0; 
        } catch (...) {
            throw PersonException("Error");
        }
    }
    
    float getcgpa() const { return cgpa; }
    void setcgpa(float newcgpa) {
        if (newcgpa >= 0.0 && newcgpa <= 4.0)
            cgpa = newcgpa;
        else
            throw PersonException("Invalid cgpa");
    }
    
    std::string getProgram() const { return program; }
    std::string getEnrollDate() const { return enrollDate; }
    
    void enrollInCourse(class Course* course);
    void dropCourse(class Course* course);
    std::vector<class Course*> getec() const;
    
    ~Student() {}
};

class GraduateStudent : public Student {
private:
    std::string researchTopic;
    Professor* advisor; 
    std::string thesisTitle;
    bool hasTeachingAssistantship;
    bool hasResearchAssistantship;
    
public:
    GraduateStudent() : Student(), researchTopic(""), advisor(nullptr), thesisTitle(""), 
                        hasTeachingAssistantship(false), hasResearchAssistantship(false) {}
    
    GraduateStudent(std::string name, int age, std::string ID, int contactInfo,
                    std::string enrollDate, float cgpa, std::string program,
                    std::string researchTopic, std::string thesisTitle)
        : Student(name, age, ID, contactInfo, enrollDate, cgpa, program) {
        this->researchTopic = researchTopic;
        this->advisor = nullptr;
        this->thesisTitle = thesisTitle;
        this->hasTeachingAssistantship = false;
        this->hasResearchAssistantship = false;
    }
    
    void display() const override {
        Student::display();
        std::cout << "Research Topic: " << researchTopic << std::endl;
        if (advisor) {
            std::cout << "Advisor: " << advisor->getName() << std::endl;
        } else {
            std::cout << "Advisor: NA" << std::endl;
        }
        std::cout << "Thesis Title: " << thesisTitle << std::endl;
        std::cout << "Teaching Assistantship: " << (hasTeachingAssistantship ? "Yes" : "No") << std::endl;
        std::cout << "Research Assistantship: " << (hasResearchAssistantship ? "Yes" : "No") << std::endl;
    }
    
    float calculatePayment() const override {
        try {
            float tuition = -3000.0;
            float stipend = 0.0;
            
            if (hasTeachingAssistantship) stipend += 1000.0;
            if (hasResearchAssistantship) stipend += 1500.0;
            
            return tuition + stipend; 
        } catch (...) {
            throw PersonException("Error");
        }
    }
    
    void setAdvisor(Professor* prof) {
        advisor = prof;
    }
    
    Professor* getAdvisor() const {
        return advisor;
    }
    
    void assignTeachingAssistantship() {
        hasTeachingAssistantship = true;
    }
    
    void removeTeachingAssistantship() {
        hasTeachingAssistantship = false;
    }
    
    void assignResearchAssistantship() {
        hasResearchAssistantship = true;
    }
    
    void removeResearchAssistantship() {
        hasResearchAssistantship = false;
    }
    
    bool hasTA() const {
        return hasTeachingAssistantship;
    }
    
    bool hasRA() const {
        return hasResearchAssistantship;
    }
    
    ~GraduateStudent() {}
};

class UndergraduateStudent : public Student {
private:
    std::string major;
    std::string minor;
    std::string graddate;
    
public:
    UndergraduateStudent() : Student(), major(""), minor(""), graddate("") {}
    
    UndergraduateStudent(std::string name, int age, std::string ID, int contactInfo,
                         std::string enrollDate, float cgpa, std::string program,
                         std::string major, std::string minor, std::string graddate)
        : Student(name, age, ID, contactInfo, enrollDate, cgpa, program) {
        this->major = major;
        this->minor = minor;
        this->graddate = graddate;
    }
    
    void display() const override {
        Student::display();
        std::cout << "Major: " << major << std::endl;
        std::cout << "Minor: " << minor << std::endl;
        std::cout << "Graduation Date: " << graddate << std::endl;
    }
    
    float calculatePayment() const override {
        try {
            return -5000.0; 
        } catch (...) {
            throw PersonException("Error");
        }
    }
    
    ~UndergraduateStudent() {}
};

class AssistantProfessor : public Professor {
private:
    int TRVIEW;
    int requiredPublications;
    
public:
    AssistantProfessor() : Professor(), TRVIEW(0), requiredPublications(0) {}
    
    AssistantProfessor(std::string name, int age, std::string ID, int contactInfo,
                       std::string dept, std::string specialization, std::string hireDate,
                       int TRVIEW, int requiredPublications)
        : Professor(name, age, ID, contactInfo, dept, specialization, hireDate) {
        this->TRVIEW = TRVIEW;
        this->requiredPublications = requiredPublications;
    }
    
    void display() const override {
        Professor::display();
        std::cout << "Years until tenure review: " << TRVIEW << std::endl;
        std::cout << "Required Publications: " << requiredPublications << std::endl;
    }
    
    float calculatePayment() const override {
        try {
            float baseSalary = 6000.0;  
            float serviceBonus = getexperience() * 100.0; 
            float rankBonus = 1000.0;   
            
            return baseSalary + serviceBonus + rankBonus;
        } catch (...) {
            throw PersonException("Error");
        }
    }
    
    ~AssistantProfessor() {}
};

class AssociateProfessor : public Professor {
private:
    bool tenured;
    int lastpromotion;
    
public:
    AssociateProfessor() : Professor(), tenured(false), lastpromotion(0) {}
    
    AssociateProfessor(std::string name, int age, std::string ID, int contactInfo,
                       std::string dept, std::string specialization, std::string hireDate,
                       bool tenured, int lastpromotion)
        : Professor(name, age, ID, contactInfo, dept, specialization, hireDate) {
        this->tenured = tenured;
        this->lastpromotion = lastpromotion;
    }
    
    void display() const override {
        Professor::display();
        std::cout << "Tenured: " << (tenured ? "Yes" : "No") << std::endl;
        std::cout << "last promotion: " << lastpromotion << std::endl;
    }
    
    float calculatePayment() const override {
        try {
            float baseSalary = 8000.0;   
            float serviceBonus = getexperience() * 150.0;  
            float rankBonus = 2000.0;    
            float tenureBonus = tenured ? 1500.0 : 0.0;  
            
            return baseSalary + serviceBonus + rankBonus + tenureBonus;
        } catch (...) {
            throw PersonException("Error");
        }
    }
    
    ~AssociateProfessor() {}
};

class FullProfessor : public Professor {
private:
    int workingyears;
    bool departmentHead;
    int researchGrants;
    
public:
    FullProfessor() : Professor(), workingyears(0), departmentHead(false), researchGrants(0) {}
    
    FullProfessor(std::string name, int age, std::string ID, int contactInfo,
                  std::string dept, std::string specialization, std::string hireDate,
                  int workingyears, bool departmentHead, int researchGrants)
        : Professor(name, age, ID, contactInfo, dept, specialization, hireDate) {
        this->workingyears = workingyears;
        this->departmentHead = departmentHead;
        this->researchGrants = researchGrants;
    }
    
    void display() const override {
        Professor::display();
        std::cout << "Years as Full Professor: " << workingyears << std::endl;
        std::cout << "Department Head: " << (departmentHead ? "Yes" : "No") << std::endl;
        std::cout << "Research Grants: " << researchGrants << std::endl;
    }
    
    float calculatePayment() const override {
        try {
            float baseSalary = 10000.0; 
            float serviceBonus = getexperience() * 200.0;  
            float rankBonus = 3000.0;    
            float departmentHeadBonus = departmentHead ? 2500.0 : 0.0; 
            float grantBonus = researchGrants * 500.0;  
            
            return baseSalary + serviceBonus + rankBonus + departmentHeadBonus + grantBonus;
        } catch (...) {
            throw PersonException("Error");
        }
    }
    
    ~FullProfessor() {}
};

class Classroom {
private:
    std::string roomNumber;
    
public:
    Classroom() : roomNumber("") {}
    
    Classroom(std::string roomNumber) {
        this->roomNumber = roomNumber;
    }
    
    std::string getRoomNumber() const { return roomNumber; }
    
    ~Classroom() {}
};

class Course {
private:
    std::string code;
    std::string title;
    int credits;
    std::string description;
    Professor* instructor; 
    Classroom* classroom; 
    int maxEnrollment;
    std::vector<std::string> prerequisites;
    
public:
    Course() : code(""), title(""), credits(0), description(""), instructor(nullptr), classroom(nullptr), maxEnrollment(30) {}
    
    Course(std::string code, std::string title, int credits, std::string description, int maxEnrollment = 30) {
        if (credits <= 0) {
            throw std::invalid_argument("Credits must be positive");
        }
        this->credits = credits;
        this->code = code;
        this->title = title;
        this->description = description;
        this->instructor = nullptr;
        this->classroom = nullptr;
        this->maxEnrollment = maxEnrollment;
    }
    
    void display() const {
        std::cout << "Code: " << code << std::endl;
        std::cout << "Title: " << title << std::endl;
        std::cout << "Credits: " << credits << std::endl;
        std::cout << "Description: " << description << std::endl;
        if (instructor) {
            std::cout << "Instructor: " << instructor->getName() << std::endl;
        } else {
            std::cout << "Instructor: not assigned" << std::endl;
        }
        if (classroom) {
            std::cout << "Classroom: " << classroom->getRoomNumber() << std::endl;
        } else {
            std::cout << "Classroom: not assigned" << std::endl;
        }
        std::cout << "Maximum enrollment: " << maxEnrollment << std::endl;
    }
    
    std::string getCode() const { return code; }
    std::string getTitle() const { return title; }
    int getCredits() const { return credits; }
    int getMaxEnrollment() const { return maxEnrollment; }
    
    void addPrerequisite(const std::string& courseCode) {
        prerequisites.push_back(courseCode);
    }
    
    const std::vector<std::string>& getPrerequisites() const {
        return prerequisites;
    }
    
    void setInstructor(Professor* prof) {
        instructor = prof;
    }
    
    Professor* getInstructor() const {
        return instructor;
    }
    
    void setClassroom(Classroom* room) {
        classroom = room;
    }
    
    Classroom* getClassroom() const {
        return classroom;
    }
    
    ~Course() {}
};


void Student::enrollInCourse(Course* course) {
    enrolledCourses.push_back(course);
}

void Student::dropCourse(Course* course) {
    enrolledCourses.erase(
        std::remove(enrolledCourses.begin(), enrolledCourses.end(), course), 
        enrolledCourses.end()
    );
}

std::vector<Course*> Student::getec() const {
    return enrolledCourses;
}

class Department {
private:
    std::string name;
    std::string location;
    float budget;
    std::vector<Professor*> professors; 
    std::vector<Course*> courses; 
    
public:
    Department() : name(""), location(""), budget(0.0) {}
    
    Department(std::string name, std::string location, float budget) {
        (name.length() > 0) ? this->name = name : this->name = "Invalid Name";
        this->location = location;
        this->budget = budget;
    }
    
    void display() const {
        std::cout << "Name: " << name << std::endl;
        std::cout << "Location: " << location << std::endl;
        std::cout << "Budget: " << budget << std::endl;
        std::cout << "Number of Professors: " << professors.size() << std::endl;
        std::cout << "Number of Courses: " << courses.size() << std::endl;
    }
    
    void addProfessor(Professor* prof) {
        professors.push_back(prof);
    }
    
    void removeProfessor(Professor* prof) {
        professors.erase(std::remove(professors.begin(), professors.end(), prof), professors.end());
    }
    
    void addCourse(Course* course) {
        courses.push_back(course);
    }
    
    void removeCourse(Course* course) {
        courses.erase(std::remove(courses.begin(), courses.end(), course), courses.end());
    }
    
    std::vector<Professor*> getProfessors() const {
        return professors;
    }
    
    std::vector<Course*> getCourses() const {
        return courses;
    }
    
    std::string getName() const {
        return name;
    }
    
    ~Department() {}
};

class UniversitySystem {
    private:
        std::vector<Student*> students;
        std::vector<Professor*> professors;
        std::vector<Course*> courses;
        std::vector<Department*> departments;
    
    public:
        void addStudent(Student* s) {
            students.push_back(s);
            std::cout << "Student added: " << s->getName() << "\n";
        }
    
        void addProfessor(Professor* p) {
            professors.push_back(p);
            std::cout << "Professor added: " << p->getName() << "\n";
        }
    
        void addCourse(Course* c) {
            courses.push_back(c);
            std::cout << "Course added: " << c->getCode() << "\n";
        }
    
        void addDepartment(Department* d) {
            departments.push_back(d);
            std::cout << "Department added: " << d->getName() << "\n";
        }
    
        Student* findStudent(const std::string& id) {
            for (auto* s : students)
                if (s->getID() == id) return s;
            return nullptr;
        }
    
        Course* findCourse(const std::string& code) {
            for (auto* c : courses)
                if (c->getCode() == code) return c;
            return nullptr;
        }
    
        Department* findDepartment(const std::string& name) {
            for (auto* d : departments)
                if (d->getName() == name) return d;
            return nullptr;
        }
    
        void enroll(const std::string& studentID, const std::string& courseCode) {
            Student* s = findStudent(studentID);
            Course* c = findCourse(courseCode);
            if (s && c) {
                s->enrollInCourse(c);
                Logger::log("Enrolled " + studentID + " in " + courseCode);
                std::cout << "Enrolled successfully.\n";
            } else {
                std::cout << "Enrollment failed.\n";
            }
        }
    
        void drop(const std::string& studentID, const std::string& courseCode) {
            Student* s = findStudent(studentID);
            Course* c = findCourse(courseCode);
            if (s && c) {
                s->dropCourse(c);
                Logger::log("Dropped " + studentID + " from " + courseCode);
                std::cout << "Student dropped from course successfully.\n";
            } else {
                std::cout << "Drop operation failed.\n";
            }
        }
    
        void displayStudent(const std::string& studentID) {
            Student* s = findStudent(studentID);
            if (s) {
                s->display();
                
              
                std::cout << "\nEnrolled Courses:\n";
                std::vector<Course*> enrolledCourses = s->getec();
                if (enrolledCourses.empty()) {
                    std::cout << "  None\n";
                } else {
                    for (Course* c : enrolledCourses) {
                        std::cout << "  " << c->getCode() << " - " << c->getTitle() << "\n";
                    }
                }
            } else {
                std::cout << "Student not found.\n";
            }
        }
    
        void displayCourse(const std::string& courseCode) {
            Course* c = findCourse(courseCode);
            if (c) {
                c->display();
                
                // Count enrolled students
                int enrolledCount = 0;
                for (Student* s : students) {
                    std::vector<Course*> courses = s->getec();
                    if (std::find(courses.begin(), courses.end(), c) != courses.end()) {
                        enrolledCount++;
                    }
                }
                
                std::cout << "Enrolled Students: " << enrolledCount << "\n";
            } else {
                std::cout << "Course not found.\n";
            }
        }
    
        void displayDepartmentInfo() {
            if (departments.empty()) {
                std::cout << "No departments found.\n";
                return;
            }
            
            std::cout << "\nAvailable Departments:\n";
            for (int i = 0; i < departments.size(); i++) {
                std::cout << i + 1 << ". " << departments[i]->getName() << "\n";
            }
            
            int choice;
            std::cout << "Select a department (1-" << departments.size() << "): ";
            std::cin >> choice;
            
            // Clear the input buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            if (choice < 1 || choice > departments.size()) {
                std::cout << "Invalid selection.\n";
                return;
            }
            
            Department* dept = departments[choice - 1];
            dept->display();
            
            // Show professors in department
            std::cout << "\nProfessors in " << dept->getName() << " Department:\n";
            std::vector<Professor*> deptProfs = dept->getProfessors();
            if (deptProfs.empty()) {
                std::cout << "  None\n";
            } else {
                for (Professor* p : deptProfs) {
                    std::cout << "  " << p->getName() << " - " << p->getSpecialization() << "\n";
                }
            }
            
            // Show courses in department
            std::cout << "\nCourses in " << dept->getName() << " Department:\n";
            std::vector<Course*> deptCourses = dept->getCourses();
            if (deptCourses.empty()) {
                std::cout << "  None\n";
            } else {
                for (Course* c : deptCourses) {
                    std::cout << "  " << c->getCode() << " - " << c->getTitle() << "\n";
                }
            }
        }
    
        void displayAllProfessors() {
            if (professors.empty()) {
                std::cout << "No professors found.\n";
                return;
            }
            
            std::cout << "\n--- All Professors ---\n";
            for (Professor* p : professors) {
                std::cout << "Name: " << p->getName() << "\n";
                std::cout << "ID: " << p->getID() << "\n";
                std::cout << "Department: " << p->getDept() << "\n";
                std::cout << "Specialization: " << p->getSpecialization() << "\n";
                std::cout << "Years of Service: " << p->getexperience() << "\n";
                std::cout << "Salary: " << p->calculatePayment() << "\n";
                
                // Find courses taught by this professor
                std::cout << "Courses Teaching:\n";
                bool teachingCourses = false;
                for (Course* c : courses) {
                    if (c->getInstructor() == p) {
                        std::cout << "  " << c->getCode() << " - " << c->getTitle() << "\n";
                        teachingCourses = true;
                    }
                }
                if (!teachingCourses) {
                    std::cout << "  Not currently teaching any courses\n";
                }
                
                std::cout << "----------------------\n";
            }
        }
    };

class Semester {
private:
    std::string term;
    std::string year;
    std::string startDate;
    std::string endDate;
    std::vector<Course*> offeredCourses;

public:
    Semester() : term(""), year(""), startDate(""), endDate("") {}
    
    Semester(std::string term, std::string year, std::string startDate, std::string endDate)
        : term(term), year(year), startDate(startDate), endDate(endDate) {}
    
    void addCourse(Course* course) {
        offeredCourses.push_back(course);
    }
    
    std::vector<Course*> getOfferedCourses() const {
        return offeredCourses;
    }
    
    std::string getTerm() const { return term; }
    std::string getYear() const { return year; }
    std::string getStartDate() const { return startDate; }
    std::string getEndDate() const { return endDate; }
    
    void display() const {
        std::cout << "Semester: " << term << " " << year << std::endl;
        std::cout << "Start Date: " << startDate << std::endl;
        std::cout << "End Date: " << endDate << std::endl;
        std::cout << "Offered Courses: " << offeredCourses.size() << std::endl;
    }
    
    ~Semester() {}
};

class Report {
private:
    std::string title;
    std::string date;
    std::string content;
    
public:
    Report(std::string title, std::string date, std::string content)
        : title(title), date(date), content(content) {}
    
    void display() const {
        std::cout << "\n===== " << title << " =====" << std::endl;
        std::cout << "Date: " << date << std::endl;
        std::cout << "\n" << content << std::endl;
        std::cout << "=====================" << std::endl;
    }
    
    std::string getTitle() const { return title; }
    std::string getContent() const { return content; }
};

class Scheduler {
private:
    std::map<std::string, std::vector<Course*>> scheduledCourses;
    std::map<std::string, std::string> instructorSchedules;
    
public:
    Scheduler() {}
    
    void scheduleCourse(const std::string& day, Course* course) {
        scheduledCourses[day].push_back(course);
    }
    
    void assignInstructorToDay(const std::string& instructorID, const std::string& day) {
        instructorSchedules[instructorID] = day;
    }
    
    std::vector<Course*> getCoursesForDay(const std::string& day) {
        return scheduledCourses[day];
    }
    
    std::string getInstructorSchedule(const std::string& instructorID) {
        return instructorSchedules[instructorID];
    }
    
    ~Scheduler() {}
};

class GradeBook {
private:
    std::string courseCode;
    std::map<std::string, float> studentGrades;
    std::map<std::string, bool> completedRequirements;
    std::map<std::string, std::string> authorizedUsers; 
    bool gradesFinalized;
    
public:
    GradeBook(std::string courseCode) : courseCode(courseCode), gradesFinalized(false) {}
    
    void addAuthorizedUser(const std::string& userID, const std::string& role) {
        authorizedUsers[userID] = role;
    }
    
    bool isAuthorized(const std::string& userID) const {
        return authorizedUsers.find(userID) != authorizedUsers.end();
    }
    
    void addGrade(const std::string& studentID, float grade, const std::string& graderID) {
      
        if (!isAuthorized(graderID)) {
            throw GradeBookException("Unauthorized user: " + graderID);
        }
        
      
        if (grade < 0.0 || grade > 100.0) {
            throw GradeBookException("Invalid grade value: " + std::to_string(grade) + " for student " + studentID);
        }
        
       
        if (gradesFinalized) {
            throw GradeBookException("Cannot add grades");
        }
        
        studentGrades[studentID] = grade;
    }
    
    void updateGrade(const std::string& studentID, float newGrade, const std::string& graderID) {
        // Check if student exists
        if (studentGrades.find(studentID) == studentGrades.end()) {
            throw GradeBookException("Cannot update grade: " + studentID);
        }
        
        // Check authorization
        if (!isAuthorized(graderID)) {
            throw GradeBookException("Unauthorized user " + graderID);
        }
        
        // Validate grade
        if (newGrade < 0.0 || newGrade > 100.0) {
            throw GradeBookException("Invalid grade value: " + std::to_string(newGrade) + " for student " + studentID);
        }
        
        // Check if grades are finalized
        if (gradesFinalized) {
            throw GradeBookException("Cannot change grades");
        }
        
        studentGrades[studentID] = newGrade;
    }
    
    void markRequirementComplete(const std::string& studentID, bool completed) {
        completedRequirements[studentID] = completed;
    }
    
    void finalizeGrades(const std::string& graderID) {
        // Check authorization
        if (!isAuthorized(graderID)) {
            throw GradeBookException("Unauthorized user: " + graderID);
        }
        
        
        for (const auto& entry : studentGrades) {
            auto req = completedRequirements.find(entry.first);
            if (req == completedRequirements.end() || !req->second) {
                throw GradeBookException("Cannot finalize grades: Student " + entry.first + " has not completed all requirements");
            }
        }
        
        gradesFinalized = true;
    }
    
    float calculateAverageGrade() {
        if (studentGrades.empty()) return 0.0;
        
        float sum = 0.0;
        for (const auto& entry : studentGrades) {
            sum += entry.second;
        }
        return sum / studentGrades.size();
    }
    
    float getHighestGrade() {
        if (studentGrades.empty()) return 0.0;
        
        float highest = 0.0;
        for (const auto& entry : studentGrades) {
            if (entry.second > highest) {
                highest = entry.second;
            }
        }
        return highest;
    }
    
    std::vector<std::string> getFailingStudents() {
        std::vector<std::string> failingStudents;
        for (const auto& entry : studentGrades) {
            if (entry.second < 60.0) {
                failingStudents.push_back(entry.first);
            }
        }
        return failingStudents;
    }
    
    ~GradeBook() {}
};

class EnrollmentManager {
    private:
        std::map<std::string, std::vector<std::string>> courseEnrollments;
        std::map<std::string, int> courseCapacities;
        std::map<std::string, std::string> enrollmentDeadlines; 
        std::map<std::string, std::vector<std::string>> studentCompletedCourses; 
        
    public:
        EnrollmentManager() {}
        
        void setCourseCapacity(const std::string& courseCode, int capacity) {
            courseCapacities[courseCode] = capacity;
        }
        
        void setEnrollmentDeadline(const std::string& courseCode, const std::string& deadline) {
            enrollmentDeadlines[courseCode] = deadline;
        }
        
        void addCompletedCourse(const std::string& studentID, const std::string& courseCode) {
            studentCompletedCourses[studentID].push_back(courseCode);
        }
        
        bool hasCompletedPrerequisites(const std::string& studentID, const Course* course) {
            const auto& prerequisites = course->getPrerequisites();
            const auto& completedCourses = studentCompletedCourses[studentID];
            
            for (const auto& prereq : prerequisites) {
                if (std::find(completedCourses.begin(), completedCourses.end(), prereq) == completedCourses.end()) {
                    return false;
                }
            }
            return true;
        }
        
        bool isEnrollmentOpen(const std::string& courseCode, const std::string& currentDate) {
          
            auto it = enrollmentDeadlines.find(courseCode);
            if (it == enrollmentDeadlines.end()) {
                return true; 
            }
            
          
            return currentDate <= it->second;
        }
        
        void enrollStudent(const std::string& studentID, const std::string& courseCode, 
                           const Course* course, const std::string& currentDate) {
           
            auto enrollments = courseEnrollments[courseCode];
            auto capacityIt = courseCapacities.find(courseCode);
            int capacity = (capacityIt != courseCapacities.end()) ? capacityIt->second : course->getMaxEnrollment();
            
            if (enrollments.size() >= capacity) {
                throw EnrollmentException("Cannot enroll student " + studentID + 
                                          " in course " + courseCode + ": Course is full");
            }
            
          
            if (!hasCompletedPrerequisites(studentID, course)) {
                throw EnrollmentException("Cannot enroll student " + studentID + 
                                          " in course " + courseCode + ": Prerequisites not met");
            }
            
           
            if (!isEnrollmentOpen(courseCode, currentDate)) {
                throw EnrollmentException("Cannot enroll student " + studentID + 
                                          " in course " + courseCode + ": Enrollment deadline has passed");
            }
            
            
            courseEnrollments[courseCode].push_back(studentID);
        }
        
        void dropStudent(const std::string& studentID, const std::string& courseCode) {
            auto& enrollments = courseEnrollments[courseCode];
            enrollments.erase(std::remove(enrollments.begin(), enrollments.end(), studentID), 
                            enrollments.end());
        }
        
        std::vector<std::string> getEnrolledStudents(const std::string& courseCode) {
            return courseEnrollments[courseCode];
        }
        
        std::vector<std::string> getec(const std::string& studentID) {
            std::vector<std::string> courses;
            for (const auto& entry : courseEnrollments) {
                if (std::find(entry.second.begin(), entry.second.end(), studentID) != entry.second.end()) {
                    courses.push_back(entry.first);
                }
            }
            return courses;
        }
        
        ~EnrollmentManager() {}
    };

    void showMenu() {
        std::cout << "\n--- University Management System Menu ---\n";
        std::cout << "1. Enroll Student in Course\n";
        std::cout << "2. Drop Student from Course\n";
        std::cout << "3. Display Student Details\n";
        std::cout << "4. Display Course Details\n";
        std::cout << "5. Display Department Info\n";
        std::cout << "6. Display All Professors\n";
        std::cout << "7. Exit\n";
        std::cout << "Choose an option: ";
    }
    
int main() {
    Logger::log("University Management System");
    UniversitySystem system;
        
       
    Department* csDept = new Department("Computer Science", "CS Building", 500000.0);
    Department* mathDept = new Department("Mathematics", "Maths Building", 300000.0);
    system.addDepartment(csDept);
    system.addDepartment(mathDept);
        
   
    Course* focp = new Course("CSL100", "Fundamentals of computer programming", 3, "Basic programming concepts");
    Course* bme = new Course("MEP100", "Basics of Mechanical engineering", 4, "basic machinery");
    Course* calculus = new Course("MEL100", "Calculus I", 4, "Introduction to calculus");
    bme->addPrerequisite("CSL100");
        
    system.addCourse(focp);
    system.addCourse(bme);
    system.addCourse(calculus);
        
        
    csDept->addCourse(focp);
    csDept->addCourse(bme);
    mathDept->addCourse(calculus);
        
     
    Professor* csProf = new Professor("Richa Singh", 45, "prof1", 1234567890, "FOCP", "Programming Language", "2020-01-15");
    Professor* mathProf = new Professor("Raman Yadav", 28, "PROF2", 1234567891, "Mathematics", "Calculus", "2024-08-20");
        
       
    csProf->setexperience(5);
    mathProf->setexperience(1);
        
    system.addProfessor(csProf);
    system.addProfessor(mathProf);
        
      
    csDept->addProfessor(csProf);
    mathDept->addProfessor(mathProf);
        
      
    focp->setInstructor(csProf);
    bme->setInstructor(csProf);
    calculus->setInstructor(mathProf);
        
       
    Student* undergrad = new Student("Lohitaksh Rastogi", 20, "24CSU115", 1234567892, "2024-10-06", 9.5, "Computer Science");
    Student* gradStudent = new Student("igotsar hskatihol", 25, "24CSU116", 1234567893, "2024-09-06", 9.8, "Computer Science");
        
    system.addStudent(undergrad);
    system.addStudent(gradStudent);
        
       
    system.enroll("24CSU115", "CSL100");
    system.enroll("24CSU116", "MEP100");
        
      
    int choice = 0;
    std::string studentID, courseCode;
        
    while (choice != 7) {
        showMenu();
            

        if (!(std::cin >> choice)) {
         
            std::cin.clear();
             
               
            std::cout << "Enter a number.\n";
            continue;
        }
            

         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
        switch (choice) {
            case 1: 
                std::cout << "Enter student ID: ";
                std::getline(std::cin, studentID);
                std::cout << "Enter course code: ";
                std::getline(std::cin, courseCode);
                system.enroll(studentID, courseCode);
                break;
                    
            case 2: 
                std::cout << "Enter student ID: ";
                std::getline(std::cin, studentID);
                std::cout << "Enter course Code: ";
                std::getline(std::cin, courseCode);
                system.drop(studentID, courseCode);
                break;
                    
            case 3: 
                std::cout << "Enter Student ID: ";
                std::getline(std::cin, studentID);
                system.displayStudent(studentID);
                break;
                    
            case 4: 
                std::cout << "Enter Course Code: ";
                std::getline(std::cin, courseCode);
                system.displayCourse(courseCode);
                break;
                    
            case 5: 
                system.displayDepartmentInfo();
                break;
                    
            case 6: 
                system.displayAllProfessors();
                break;
                    
            case 7: 
                break;
                    
            default:
                std::cout << "Invalid option\n";
        }
    }
        
    return 0;
}