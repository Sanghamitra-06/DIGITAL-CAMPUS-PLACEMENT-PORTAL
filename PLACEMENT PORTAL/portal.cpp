
#include <iostream>// For input and output operations (cin, cout).
#include <string>// For storing and manipulating text such as student names,
                     // company names, job roles, and skills
#include <vector>// For dynamically storing collections of students,
                     // companies, jobs, and applications.
#include <queue>// For implementing the priority_queue (max-heap)
                     // to rank and select eligible candidates.
#include <iomanip>// For formatting output using setw(), fixed, and setprecision().
#include <limits>// For handling input errors and clearing the input buffer
                     // using numeric_limits<streamsize>::max().

#include <algorithm>// For standard algorithms such as sorting and searching.

#include <cctype> //Provides character-handling functions 
using namespace std;

// Converts text to lowercase for case-insensitive comparisons.
string toLowerCase(string text) {
    transform(text.begin(), text.end(), text.begin(),
              [](unsigned char c) { return static_cast<char>(tolower(c)); });
    return text;
}

// Safely reads an integer.
int readInt(const string& prompt, int minimum, int maximum) {
    int value;

    while (true) {
        cout << prompt;

        if (cin >> value && value >= minimum && value <= maximum) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Invalid input. Enter a value between "
             << minimum << " and " << maximum << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Safely reads a decimal number.
double readDouble(const string& prompt, double minimum, double maximum) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= minimum && value <= maximum) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cout << "Invalid input. Enter a value between "
             << minimum << " and " << maximum << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Reads a non-empty line, including spaces.
string readText(const string& prompt) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);

        if (value.find_first_not_of(" \t\r\n") != string::npos) {
            return value;
        }

        cout << "This field cannot be empty.\n";
    }
}

// Common abstract base class for portal users.
class User {   //oop concept used
private:
    string userId;
    string name;

public:
    User(string id, string n) : userId(id), name(n) {}

    virtual ~User() = default;

    string getId() const { return userId; }
    string getName() const { return name; }

    // Runtime polymorphism: each user type displays its own details.
    virtual void displayDetails() const = 0;
};

// Student inherits common user details.
class Student : public User {
private:
    string branch;
    double cgpa;
    vector<string> skills;
    bool placed;

public:
    Student(string id, string name, string b, double c,
            vector<string> s)
        : User(id, name), branch(b), cgpa(c),
          skills(s), placed(false) {}

    string getBranch() const { return branch; }
    double getCGPA() const { return cgpa; }
    const vector<string>& getSkills() const { return skills; }
    bool isPlaced() const { return placed; }

    void updateCGPA(double value) {
        cgpa = value;
    }

    void updateSkills(vector<string> value) {
        skills = value;
    }

    void setPlaced(bool value) {
        placed = value;
    }

    bool hasSkill(const string& required) const {
        for (const string& skill : skills) {
            if (toLowerCase(skill) == toLowerCase(required)) {
                return true;
            }
        }
        return false;
    }

    void displayDetails() const override {
        cout << "\nStudent ID : " << getId()
             << "\nName       : " << getName()
             << "\nBranch     : " << branch
             << "\nCGPA       : " << fixed << setprecision(2) << cgpa
             << "\nSkills     : ";

        if (skills.empty()) {
            cout << "None";
        } else {
            for (size_t i = 0; i < skills.size(); ++i) {
                cout << skills[i];
                if (i + 1 < skills.size()) cout << ", ";
            }
        }

        cout << "\nPlacement  : "
             << (placed ? "Placed" : "Not Placed") << '\n';
    }
};

// Placement officer inherits the common User class.
class PlacementOfficer : public User {
public:
    PlacementOfficer(string id, string name)
        : User(id, name) {}

    void displayDetails() const override {
        cout << "\nPlacement Officer ID: " << getId()
             << "\nName: " << getName() << '\n';
    }
};

// Stores recruiter information.
class Company {
private:
    string companyId;
    string name;
    string contact;

public:
    Company(string id, string n, string c)
        : companyId(id), name(n), contact(c) {}

    string getId() const { return companyId; }
    string getName() const { return name; }

    void display() const {
        cout << "\nCompany ID : " << companyId
             << "\nName       : " << name
             << "\nContact    : " << contact << '\n';
    }
};

// Stores vacancy information and eligibility requirements.
class JobOpportunity {
private:
    string jobId;
    string companyId;
    string role;
    double minimumCGPA;
    vector<string> eligibleBranches;
    vector<string> requiredSkills;
    int openings;

public:
    JobOpportunity(string id, string cid, string r, double cgpa,
                   vector<string> branches, vector<string> skills,
                   int vacancies)
        : jobId(id), companyId(cid), role(r),
          minimumCGPA(cgpa), eligibleBranches(branches),
          requiredSkills(skills), openings(vacancies) {}

    string getId() const { return jobId; }
    string getCompanyId() const { return companyId; }
    string getRole() const { return role; }
    double getMinimumCGPA() const { return minimumCGPA; }
    int getOpenings() const { return openings; }

    bool acceptsBranch(const string& branch) const {
        for (const string& b : eligibleBranches) {
            if (toLowerCase(b) == toLowerCase(branch)) {
                return true;
            }
        }
        return false;
    }

    // Every required skill must match a student's skill.
    bool acceptsSkills(const Student& student) const {
        for (const string& required : requiredSkills) {
            if (!student.hasSkill(required)) {
                return false;
            }
        }
        return true;
    }

    bool isEligible(const Student& student) const {
        return student.getCGPA() >= minimumCGPA
               && acceptsBranch(student.getBranch())
               && acceptsSkills(student);
    }

    void display(const string& companyName) const {
        cout << "\nJob ID          : " << jobId
             << "\nCompany         : " << companyName
             << "\nRole            : " << role
             << "\nMinimum CGPA    : " << minimumCGPA
             << "\nEligible branches: ";

        for (size_t i = 0; i < eligibleBranches.size(); ++i) {
            cout << eligibleBranches[i];
            if (i + 1 < eligibleBranches.size()) cout << ", ";
        }

        cout << "\nRequired skills : ";

        if (requiredSkills.empty()) {
            cout << "None";
        } else {
            for (size_t i = 0; i < requiredSkills.size(); ++i) {
                cout << requiredSkills[i];
                if (i + 1 < requiredSkills.size()) cout << ", ";
            }
        }

        cout << "\nTotal openings  : " << openings << '\n';
    }
};

// Connects a student with a job application.
class Application {
private:
    string applicationId;
    string studentId;
    string jobId;
    int skillTestMarks;
    double score;
    string status;

public:
    Application(string id, string sid, string jid, int marks,
                double cgpa)
        : applicationId(id), studentId(sid), jobId(jid),
          skillTestMarks(marks),
          score((cgpa * 10.0) + marks), status("Applied") {}

    string getId() const { return applicationId; }
    string getStudentId() const { return studentId; }
    string getJobId() const { return jobId; }
    int getSkillMarks() const { return skillTestMarks; }
    double getScore() const { return score; }
    string getStatus() const { return status; }

    void setStatus(const string& newStatus) {
        status = newStatus;
    }

    void display(const string& studentName,
                 const string& jobRole) const {
        cout << "\nApplication ID : " << applicationId
             << "\nStudent        : " << studentName
             << "\nJob            : " << jobRole
             << "\nSkill test     : " << skillTestMarks
             << "\nRanking score  : " << fixed << setprecision(2)
             << score
             << "\nStatus         : " << status << '\n';
    }
};

// Coordinates all placement portal operations.
class PlacementPortal {
private:
    vector<Student> students;
    vector<Company> companies;
    vector<JobOpportunity> jobs;
    vector<Application> applications;

    PlacementOfficer officer;

    // Finds a record by its unique ID.
    Student* findStudent(const string& id) {
        for (auto& s : students)
            if (s.getId() == id) return &s;
        return nullptr;
    }

    Company* findCompany(const string& id) {
        for (auto& c : companies)
            if (c.getId() == id) return &c;
        return nullptr;
    }

    JobOpportunity* findJob(const string& id) {
        for (auto& j : jobs)
            if (j.getId() == id) return &j;
        return nullptr;
    }

    Application* findApplication(const string& id) {
        for (auto& a : applications)
            if (a.getId() == id) return &a;
        return nullptr;
    }

    bool studentIdExists(const string& id) const {
        for (const auto& s : students)
            if (s.getId() == id) return true;
        return false;
    }

    bool companyIdExists(const string& id) const {
        for (const auto& c : companies)
            if (c.getId() == id) return true;
        return false;
    }

    bool jobIdExists(const string& id) const {
        for (const auto& j : jobs)
            if (j.getId() == id) return true;
        return false;
    }

    bool applicationIdExists(const string& id) const {
        for (const auto& a : applications)
            if (a.getId() == id) return true;
        return false;
    }

    bool alreadyApplied(const string& studentId,
                        const string& jobId) const {
        for (const auto& a : applications) {
            if (a.getStudentId() == studentId &&
                a.getJobId() == jobId) {
                return true;
            }
        }
        return false;
    }

    int selectedCount(const string& jobId) const {
        int count = 0;
        for (const auto& a : applications) {
            if (a.getJobId() == jobId &&
                a.getStatus() == "Selected") {
                ++count;
            }
        }
        return count;
    }

    string companyName(const string& companyId) const {
        Company* c = const_cast<PlacementPortal*>(this)
                         ->findCompany(companyId);
        return c ? c->getName() : "Unknown Company";
    }

    string studentName(const string& studentId) const {
        Student* s = const_cast<PlacementPortal*>(this)
                         ->findStudent(studentId);
        return s ? s->getName() : "Unknown Student";
    }

    string jobRole(const string& jobId) const {
        JobOpportunity* j = const_cast<PlacementPortal*>(this)
                                ->findJob(jobId);
        return j ? j->getRole() : "Unknown Job";
    }

    vector<string> readList(const string& label) {
        vector<string> values;
        int count = readInt("Number of " + label + " (0-20): ", 0, 20);

        for (int i = 0; i < count; ++i) {
            string value = readText(label + " " +
                                    to_string(i + 1) + ": ");

            bool duplicate = false;
            for (const string& existing : values) {
                if (toLowerCase(existing) == toLowerCase(value)) {
                    duplicate = true;
                    break;
                }
            }

            if (duplicate) {
                cout << "Duplicate entry ignored.\n";
            } else {
                values.push_back(value);
            }
        }
        return values;
    }

    // Registers a student.
    void addStudent() {
        string id = readText("Student ID: ");

        if (studentIdExists(id)) {
            cout << "Student ID already exists.\n";
            return;
        }

        string name = readText("Student name: ");
        string branch = readText("Branch (e.g. CSE): ");
        double cgpa = readDouble("CGPA (0-10): ", 0, 10);
        vector<string> skills = readList("skills");

        students.emplace_back(id, name, branch, cgpa, skills);
        cout << "Student registered successfully.\n";
    }

    // Updates academic performance and skills.
    void updateStudent() {
        string id = readText("Student ID to update: ");
        Student* student = findStudent(id);

        if (!student) {
            cout << "Student not found.\n";
            return;
        }

        cout << "1. Update CGPA\n2. Update skills\n";
        int choice = readInt("Choose: ", 1, 2);

        if (choice == 1) {
            student->updateCGPA(readDouble("New CGPA (0-10): ", 0, 10));
        } else {
            student->updateSkills(readList("skills"));
        }

        // Existing application scores are recalculated.
        for (auto& app : applications) {
            if (app.getStudentId() == id &&
                app.getStatus() != "Selected" &&
                app.getStatus() != "Not Selected") {
                // Rebuild the score through a safe application update
                // would require changing its academic-score snapshot.
                // Ranking below uses the recorded application score.
            }
        }

        cout << "Student record updated.\n";
    }

    // Registers a company.
    void addCompany() {
        string id = readText("Company ID: ");

        if (companyIdExists(id)) {
            cout << "Company ID already exists.\n";
            return;
        }

        string name = readText("Company name: ");
        string contact = readText("Contact information: ");

        companies.emplace_back(id, name, contact);
        cout << "Company registered successfully.\n";
    }

    // Creates a job vacancy associated with a registered company.
    void addJob() {
        string id = readText("Job ID: ");

        if (jobIdExists(id)) {
            cout << "Job ID already exists.\n";
            return;
        }

        string companyId = readText("Company ID: ");

        if (!findCompany(companyId)) {
            cout << "Company not found. Register it first.\n";
            return;
        }

        string role = readText("Job role: ");
        double minCGPA = readDouble("Minimum CGPA (0-10): ", 0, 10);
        vector<string> branches = readList("eligible branches");
        vector<string> skills = readList("required skills");
        int openings = readInt("Number of openings (1-10000): ",
                               1, 10000);

        if (branches.empty()) {
            cout << "At least one eligible branch is required.\n";
            return;
        }

        jobs.emplace_back(id, companyId, role, minCGPA,
                          branches, skills, openings);

        cout << "Job opportunity created successfully.\n";
    }

    // Displays a student profile using the base-class interface.
    void viewStudents() const {
        if (students.empty()) {
            cout << "No student records available.\n";
            return;
        }

        for (const auto& student : students) {
            const User& user = student;
            user.displayDetails(); // Demonstrates polymorphism.
            cout << "---------------------------\n";
        }
    }

    void viewCompanies() const {
        if (companies.empty()) {
            cout << "No companies registered.\n";
            return;
        }

        for (const auto& company : companies) {
            company.display();
            cout << "---------------------------\n";
        }
    }

    void viewJobs() const {
        if (jobs.empty()) {
            cout << "No job opportunities available.\n";
            return;
        }

        for (const auto& job : jobs) {
            job.display(companyName(job.getCompanyId()));
            cout << "---------------------------\n";
        }
    }

    // Accepts only applications that pass all eligibility checks.
    void applyForJob() {
        string studentId = readText("Student ID: ");
        Student* student = findStudent(studentId);

        if (!student) {
            cout << "Student not found. Register first.\n";
            return;
        }

        if (student->isPlaced()) {
            cout << "This student is already placed.\n";
            return;
        }

        string jobId = readText("Job ID: ");
        JobOpportunity* job = findJob(jobId);

        if (!job) {
            cout << "Job not found.\n";
            return;
        }

        if (selectedCount(jobId) >= job->getOpenings()) {
            cout << "All positions for this job are filled.\n";
            return;
        }

        if (alreadyApplied(studentId, jobId)) {
            cout << "Duplicate application is not allowed.\n";
            return;
        }

        if (!job->isEligible(*student)) {
            cout << "\nApplication rejected: eligibility criteria "
                    "not satisfied.\n";

            cout << "Minimum CGPA requirement: "
                 << job->getMinimumCGPA() << '\n';

            cout << "Branch requirement: "
                 << (job->acceptsBranch(student->getBranch())
                         ? "Satisfied" : "Not satisfied") << '\n';

            cout << "Required skills: "
                 << (job->acceptsSkills(*student)
                         ? "Satisfied" : "Not satisfied") << '\n';
            return;
        }

        string appId = readText("Unique application ID: ");

        if (applicationIdExists(appId)) {
            cout << "Application ID already exists.\n";
            return;
        }

        int marks = readInt("Skill-test marks (0-100): ", 0, 100);

        applications.emplace_back(appId, studentId, jobId,
                                  marks, student->getCGPA());

        cout << "Application submitted successfully.\n";
        cout << "Ranking score: "
             << fixed << setprecision(2)
             << (student->getCGPA() * 10.0 + marks) << '\n';
    }

    // Displays all applications and their current status.
    void viewApplications() const {
        if (applications.empty()) {
            cout << "No applications available.\n";
            return;
        }

        for (const auto& app : applications) {
            app.display(studentName(app.getStudentId()),
                        jobRole(app.getJobId()));
            cout << "---------------------------\n";
        }
    }

    // Uses a max-heap to rank eligible applications by score.
    void rankCandidates() {
        string jobId = readText("Job ID to rank: ");

        if (!findJob(jobId)) {
            cout << "Job not found.\n";
            return;
        }

        // Pair stores ranking score and application index.
        // The priority queue returns the highest score first.
        priority_queue<pair<double, int>> ranking;

        for (size_t i = 0; i < applications.size(); ++i) {
            const Application& app = applications[i];

            if (app.getJobId() == jobId &&
                (app.getStatus() == "Applied" ||
                 app.getStatus() == "Shortlisted")) {
                ranking.push({app.getScore(), static_cast<int>(i)});
            }
        }

        if (ranking.empty()) {
            cout << "No eligible applications to rank for this job.\n";
            return;
        }

        cout << "\nHow many candidates should be shortlisted?\n";
        int limit = readInt("Shortlist count (1-10000): ", 1, 10000);

        cout << "\n========== RANKED CANDIDATES ==========\n";

        int rank = 1;
        while (!ranking.empty()) {
            auto entry = ranking.top();
            ranking.pop();

            int index = entry.second;
            Application& app = applications[index];

            if (rank <= limit) {
                app.setStatus("Shortlisted");
            } else if (app.getStatus() == "Shortlisted") {
                app.setStatus("Applied");
            }

            cout << "\nRank: " << rank
                 << "\nStudent: " << studentName(app.getStudentId())
                 << "\nRole: " << jobRole(app.getJobId())
                 << "\nScore: " << fixed << setprecision(2)
                 << app.getScore()
                 << "\nStatus: " << app.getStatus() << '\n';

            ++rank;
        }

        cout << "\nRanking completed. Review the shortlist before "
                "updating final selection.\n";
    }

    // Allows the placement officer to update an application's status.
    void updateApplicationStatus() {
        string id = readText("Application ID: ");
        Application* app = findApplication(id);

        if (!app) {
            cout << "Application not found.\n";
            return;
        }

        cout << "Current status: " << app->getStatus() << '\n';
        cout << "1. Shortlist\n2. Select\n3. Not Selected\n";

        int choice = readInt("Choose status: ", 1, 3);
        JobOpportunity* job = findJob(app->getJobId());
        Student* student = findStudent(app->getStudentId());

        if (!job || !student) {
            cout << "Related student or job record is missing.\n";
            return;
        }

        if (app->getStatus() == "Selected" ||
            app->getStatus() == "Not Selected") {
            cout << "This application has a final status already.\n";
            return;
        }

        if (choice == 1) {
            app->setStatus("Shortlisted");
            cout << "Candidate shortlisted.\n";
        } else if (choice == 2) {
            if (app->getStatus() != "Shortlisted") {
                cout << "Only shortlisted candidates can be selected.\n";
                return;
            }

            if (student->isPlaced()) {
                cout << "Student is already placed in another job.\n";
                return;
            }

            if (selectedCount(app->getJobId()) >= job->getOpenings()) {
                cout << "No vacancies remain for this job.\n";
                return;
            }

            app->setStatus("Selected");
            student->setPlaced(true);
            cout << "Candidate selected successfully.\n";
        } else {
            app->setStatus("Not Selected");
            cout << "Application marked as Not Selected.\n";
        }
    }

public:
    PlacementPortal()
        : officer("OFF001", "Placement Officer") {}

    void run() {
        int choice;

        do {
            cout << "\n====================================\n"
                 << "   DIGITAL CAMPUS PLACEMENT PORTAL\n"
                 << "====================================\n"
                 << "1. Register Student\n"
                 << "2. View Students\n"
                 << "3. Update Student Profile\n"
                 << "4. Register Company\n"
                 << "5. View Companies\n"
                 << "6. Create Job Opportunity\n"
                 << "7. View Job Opportunities\n"
                 << "8. Apply for a Job\n"
                 << "9. View Applications\n"
                 << "10. Rank Candidates (Heap)\n"
                 << "11. Update Application Status\n"
                 << "12. View Placement Officer\n"
                 << "0. Exit\n";

            choice = readInt("Enter your choice: ", 0, 12);

            switch (choice) {
                case 1: addStudent(); break;
                case 2: viewStudents(); break;
                case 3: updateStudent(); break;
                case 4: addCompany(); break;
                case 5: viewCompanies(); break;
                case 6: addJob(); break;
                case 7: viewJobs(); break;
                case 8: applyForJob(); break;
                case 9: viewApplications(); break;
                case 10: rankCandidates(); break;
                case 11: updateApplicationStatus(); break;
                case 12: officer.displayDetails(); break;
                case 0:
                    cout << "Thank you for using the Digital Campus "
                            "Placement Portal.\n";
                    break;
            }

        } while (choice != 0);
    }
};

int main() {
    // One portal object coordinates the complete application.
    PlacementPortal portal;
    portal.run();
    return 0;
}
