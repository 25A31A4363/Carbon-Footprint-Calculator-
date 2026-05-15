# 🌿 Carbon Footprint Calculator
A Console-based C++ application that calculates your annual carbon dioxide (CO₂) emissions based on your lifestyle — covering transport, diet, and home energy usage. Designed as a 1st year B.Tech project aligned with **UN SDG Goal 12 — Responsible Consumption & Production**.

---

## ✨ Highlights
- **Clean, intuitive console interface** — ideal for learning and demonstrating C++ fundamentals.
- **Real emission factors** — values sourced from IPCC 2021 and India's CEA 2023 grid data for scientific accuracy.
- **Easy to extend** — simple to add new categories, graphical output, or a database backend.

---

## 🎯 Features
- **Transport Emissions:** Calculates CO₂ from personal car usage (petrol/diesel/electric), bus travel, and short/long flights.
- **Diet Analysis:** Estimates annual food-related emissions based on diet type — heavy meat, average, vegetarian, or vegan.
- **Home Energy:** Computes emissions from monthly electricity consumption (kWh) and LPG gas usage.
- **Footprint Comparison:** Compares your result against the Indian average (1,900 kg/yr) and global average (4,000 kg/yr).
- **Personalised Suggestions:** Provides targeted, data-driven tips to reduce your carbon footprint in each category.
- **Report Export:** Automatically saves a formatted summary report to `carbon_report.txt` for documentation.

---

## 🛠️ Technologies Used
- **Language:** C++ (ISO C++11)
- **Suggested Compilers / IDEs:** GCC (g++), Code::Blocks, VS Code
- **Libraries:** `<iostream>`, `<fstream>`, `<iomanip>`, `<string>`
- **Design Pattern:** Object-Oriented Programming (OOP) with modular class structure

---

## 📚 Concepts Demonstrated
- Classes, Objects & Constructors
- Encapsulation (member data + functions)
- `if-else` ladder & conditional logic
- `for` loops
- User-defined functions & return values
- File handling (`ofstream`)
- Formatted output (`setw`, `setprecision`, `fixed`)
- Constants (`const`) for emission factors
- Basic input/output with `cin` / `cout`

---

## 🚀 How to Run the Project

**Step 1: Open Terminal / Command Prompt**
- Windows: Command Prompt or PowerShell
- macOS / Linux: Terminal

**Step 2: Navigate to the Project Folder**
```bash
cd path/to/Carbon-Footprint-Calculator-CPP
```

**Step 3: Compile the Program**
```bash
g++ carbon_footprint_calculator.cpp -o carbon_footprint
```

**Step 4: Run the Program**
```bash
./carbon_footprint        # Linux / macOS
carbon_footprint.exe      # Windows
```

**Step 5: Follow the Prompts**
Enter your name, answer questions in each section (Transport → Diet → Home Energy), and choose whether to save your report.

---

## 📂 Files in the Project
- `carbon_footprint_calculator.cpp` — Main source code containing all logic and classes
- `Carbon_Footprint_Calculator.pdf` — Project documentation and viva reference
- `README.md` — Project overview and usage instructions
- `carbon_report.txt` — Auto-generated output file (created on first run)

---

## 📝 Notes
- This project is designed as a **first-year academic C++ project** for understanding OOP and file handling.
- The suggestion engine uses **rule-based logic** — comparing user emissions against defined thresholds to generate personalised feedback.
- Input validation is included to handle incorrect entries during interactive sessions.
- Aligned with **UN SDG Goal 12** — promoting responsible consumption and sustainable lifestyle choices.

---

## 🤝 Contributing
Contributions and suggestions are welcome — feel free to open issues or submit pull requests to add new emission categories, improve the UI, or extend the suggestion engine.

---

## 👥 Team Members
- S.V.S. MOHITH
- P. BALA CHANDRIKA
- Y.V. RAM CHARAN
- S. PUJITHA
- R. PRINCE JOEL
