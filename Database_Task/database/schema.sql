-- STUDENT TABLE
CREATE TABLE Student (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT,
    dob TEXT,
    address TEXT
);

-- TEACHER TABLE
CREATE TABLE Teacher (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT,
    subject TEXT
);

-- COURSE TABLE
CREATE TABLE Course (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    title TEXT,
    id_teacher INTEGER,
    FOREIGN KEY(id_teacher) REFERENCES Teacher(id)
);

-- ASSIGNMENT TABLE
CREATE TABLE Assignment (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    title TEXT,
    id_course INTEGER,
    FOREIGN KEY(id_course) REFERENCES Course(id)
);

-- ENROLLMENT TABLE
CREATE TABLE Enrollment (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    id_student INTEGER,
    id_course INTEGER,
    FOREIGN KEY(id_student) REFERENCES Student(id),
    FOREIGN KEY(id_course) REFERENCES Course(id)
);

-- SUBMISSIONS TABLE
CREATE TABLE Submissions (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    id_assignment INTEGER,
    id_student INTEGER,
    time TEXT,
    FOREIGN KEY(id_assignment) REFERENCES Assignment(id),
    FOREIGN KEY(id_student) REFERENCES Student(id)
);

-- CREDITS TABLE
CREATE TABLE Credits (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    id_course INTEGER,
    id_student INTEGER,
    date TEXT,
    grade INTEGER,
    credits INTEGER,
    FOREIGN KEY(id_course) REFERENCES Course(id),
    FOREIGN KEY(id_student) REFERENCES Student(id)
);


-- STUDENTS
INSERT INTO Student (name, dob, address) VALUES
("Prashant Bhandari", "2005-11-25", "Gulmi, Nepal"),
("Sita Rana", "2004-04-13", "Kathmandu, Nepal"),
("Bikash Thapa", "2003-09-02", "Pokhara, Nepal");

-- TEACHERS
INSERT INTO Teacher (name, subject) VALUES
("Ramesh Adhikari", "Math"),
("Sunita Koirala", "Computer Science");

-- COURSES
INSERT INTO Course (title, id_teacher) VALUES
("Embedded Systems", 2),
("Discrete Mathematics", 1);

-- ENROLLMENTS (students join courses)
INSERT INTO Enrollment (id_student, id_course) VALUES
(1, 1),
(2, 1),
(3, 2);

-- ASSIGNMENTS
INSERT INTO Assignment (title, id_course) VALUES
("Traffic Light Project", 1),
("Logic Gates Homework", 2);

-- SUBMISSIONS
INSERT INTO Submissions (id_assignment, id_student, time) VALUES
(1, 1, "2025-12-11 10:00"),
(1, 2, "2025-12-11 11:00"),
(2, 3, "2025-12-11 09:30");

-- CREDITS
INSERT INTO Credits (id_course, id_student, date, grade, credits) VALUES
(1, 1, "2025-12-12", 85, 3),
(1, 2, "2025-12-12", 78, 3),
(2, 3, "2025-12-12", 90, 4);


SELECT * FROM Student;

SELECT Course.title AS course, Teacher.name AS teacher
FROM Course
JOIN Teacher ON Course.id_teacher = Teacher.id;

SELECT Student.name
FROM Enrollment
JOIN Student ON Enrollment.id_student = Student.id
WHERE Enrollment.id_course = 1;


SELECT Assignment.title, Student.name, Submissions.time
FROM Submissions
JOIN Assignment ON Submissions.id_assignment = Assignment.id
JOIN Student ON Submissions.id_student = Student.id;

SELECT Student.name, Course.title, Credits.grade, Credits.credits
FROM Credits
JOIN Student ON Credits.id_student = Student.id
JOIN Course ON Credits.id_course = Course.id;
