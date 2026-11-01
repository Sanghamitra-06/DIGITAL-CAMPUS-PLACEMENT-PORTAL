# 🎓 Digital Campus Placement Portal

<p align="center">
  <img src="https://img.shields.io/badge/Language-C++-blue?style=for-the-badge&logo=c%2B%2B" />
  <img src="https://img.shields.io/badge/Concepts-OOP-orange?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Data_Structure-Max--Heap-purple?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Status-Academic%20Project-success?style=for-the-badge" />
</p>

<p align="center">
  <b>🚀 Bridging Students and Opportunities Through Smart Placement Management</b>
</p>

---

## 📌 Table of Contents

- [🌟 About the Project](#-about-the-project)
- [🎯 Objectives](#-project-objectives)
- [🛠️ Tech Stack](#️-tech-stack)
- [🧠 OOP Concepts](#-oops-concepts-implemented)
- [🏗️ Architecture](#️-project-architecture)
- [🔄 Workflow](#-project-workflow)
- [🏆 Ranking Simulation](#-candidate-ranking-simulation)
- [🎮 How to Run](#-how-to-run-the-project)
- [🧭 Navigation](#-how-to-navigate-the-portal)
- [📂 Repository Structure](#-repository-structure)
- [🔮 Future Scope](#-future-enhancements)
- [👩‍💻 Author](#-project-author)

---

## 🌟 About the Project

**Digital Campus Placement Portal** is a menu-driven C++ application that simulates the campus placement process.

It brings students, placement officers, companies, and job opportunities together in one system. It manages student details, company information, job openings, applications, eligibility verification, candidate ranking, and placement status.

The project demonstrates the practical implementation of **Object-Oriented Programming and Data Structures using C++**.

## 🎯 Project Objectives

- 👨‍🎓 Manage student profiles and academic records.
- 🏢 Maintain company details and job opportunities.
- 📋 Allow students to apply for available jobs.
- ✅ Verify eligibility using CGPA, branch, and skills.
- 🏆 Rank eligible candidates using a Max-Heap.
- 📊 Track application and selection statuses.
- 💻 Apply OOP concepts to a real-world-inspired problem.

---

## 🛠️ Tech Stack

| Technology | Application |
|---|---|
| C++ | Core programming language |
| OOP | Modular program design |
| STL Vector | Dynamic data storage |
| Priority Queue | Max-Heap implementation |
| Console Interface | User interaction |

---

## 🧠 OOP Concepts Implemented

| Concept | Implementation |
|---|---|
| 🔒 Encapsulation | Combining data and functions inside classes |
| 🎭 Abstraction | Abstract `User` base class |
| 🌳 Inheritance | `Student` and `PlacementOfficer` derive from `User` |
| 🔄 Polymorphism | Virtual functions and derived-class behaviour |

### Class Structure

```text
                  User (Abstract Class)
                         |
              -----------------------
              |                     |
           Student           PlacementOfficer

       Company
       JobOpportunity
       Application
       PlacementPortal
