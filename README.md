This is my solution to this project
submission/1output.txt - solution for soal1
submission/2output.txt - solution for soal2
submission/3output.txt - solution for soal3

To compile: `g++ -O2 -std=c++17 solution.cpp -o solution `
To use executable: `./solution ../maps/soal1.txt output.txt`

# Pathfinding Visualizer — Data Structures Final Project 2026

Final project for the Data Structures course (IUP). You write a C++ pathfinding
algorithm, run it against three maps, and watch your result animate in a local
visualizer.

**Watch the walkthrough video first:** https://youtu.be/nEu9wuTx4Jw

---

## Quick start

1. **Download** this repository (green `Code` button → `Download ZIP`), or clone it.
2. **Read** the slides / brief in this repo, and watch the video above.
3. **Write your algorithm** inside `submission/solution.cpp` — only in the `solve()` function.
4. **Compile & run:**
   ```bash
   cd submission
   g++ -O2 -std=c++17 solution.cpp -o solution
   ./solution ../maps/soal1.txt output.txt
   ```
5. **View the result:** open `engine/index.html` (double-click), pick the problem,
   drag your `output.txt` in, press Play.

---

## What's inside

```
engine/        the visualizer (one HTML file, open by double-click)
maps/          the three problem maps (soal1, soal2, soal3)
submission/    harness.h (DO NOT MODIFY) + solution.cpp (your work)
```

- **soal1** — no weights, no walls
- **soal2** — walls, no weights
- **soal3** — weights and walls

Symbols in maps: `S` = start · `G` = goal · `.` = open cell · `#` = wall · `1`–`9` = weighted cell.

---

## Rules

- Write your logic **only inside `solve()`**. Do not modify `harness.h`.
- Language: **C++ (C++17)**.
- Submit **one file**: `solution.cpp`, plus your report.
- Group of **3**. Every member must understand the solution — questions at the demo
  may go to any member.

---

## Timeline

| Date | What |
|------|------|
| **June 3** | Assistance 1 — show `solution.cpp` compiles and solves at least Problem 1 |
| **June 10** | Assistance 2 — all three problems run; draft report ready |
| **June 17** | Final demo + report submission (exchange students: via Zoom / TBA) |

---

## Your goal

Two levels:
1. **Make it work** — reach the goal on every map.
2. **Make it good** — explore fewer cells. Many algorithms reach the goal; the better
   ones check fewer cells to get there.

You are not graded on reaching the goal alone — you are graded on how well you
understand *why* your choice works. Be ready to explain your code at the demo.
