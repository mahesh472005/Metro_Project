# 🚇 Mumbai Metro Online Ticketing System

A **C-based console application** that simulates the Mumbai Metro ticket booking process — complete with fare calculation, discounts, ticket printing, and persistent storage.  

This project demonstrates **file handling, structured programming, data validation, and user interaction** in C, making it an excellent example of **problem-solving and system design** for transportation ticketing.

---

## ✨ Features

- **Dynamic Station Loading**  
  Reads station names from a file (`stations.txt`) for easy updates.

- **Interactive Menu System**  
  User-friendly, color-coded terminal interface for ticket booking.

- **Fare Calculation**  
  - Base fare + rate per station  
  - 15% discount for return journeys  
  - 20% discount for student passengers

- **Passenger Details Management**  
  Capture and store multiple passenger details with student status.

- **Ticket Generation & Storage**  
  - Printable ticket in terminal  
  - Auto-saves ticket details to `tickets.txt` with date/time & unique ticket ID

---

## 🗂 Project Structure

```plaintext
├── main.c          # Source code for the ticketing system
├── stations.txt    # List of Mumbai Metro stations
├── tickets.txt     # Generated tickets log
```

---

## 📂 Example Files

### stations.txt
```
Versova
D N Nagar
Azad Nagar
Andheri
Western Express Highway
...
```

### tickets.txt
```
TicketID: 1754860340 | From: Versova | To: Ghatkopar | Type: Return | Passengers: 2 | Names: mahesh(S), pallavi | Fare: Rs 367.00 | Date: Sun Aug 10 20:48:09 2025
```

---

## 🚀 How to Run

1. **Clone the Repository**
   ```bash
   git clone https://github.com/yourusername/mumbai-metro-ticketing.git
   cd mumbai-metro-ticketing
   ```

2. **Compile the Program**
   ```bash
   gcc main.c -o metro
   ```

3. **Run the Application**
   ```bash
   ./metro
   ```

---

## 🎯 Skills Demonstrated

- **C Programming**
- **File Handling (Read/Write)**
- **Structs & Arrays**
- **String Manipulation**
- **User Input Validation**
- **Formatted Output**
- **Modular Code Organization**

---

## 📸 Screenshots

| Main Menu | Ticket Example |
|-----------|----------------|
| ![Menu Screenshot](assets/images/menu.png) | ![Ticket Screenshot](assets/images/ticket.png) |

---

## 📌 Future Enhancements

- Add online payment simulation  
- Implement seat reservation  
- Export tickets as PDF  
- Integrate with a real-time database

---

## 🏆 About This Project

This project was built to **simulate a real-world metro ticketing system** while strengthening **core C programming concepts**. It highlights attention to **user experience**, **reusability**, and **scalable code design**.

---

**💡 Pro Tip:** If you're a recruiter, check out `main.c` for clean and maintainable C code with practical real-world application logic.
