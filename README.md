# 🎮 Hangman in C

A simple **console-based Hangman game** written in **C**.  
This project demonstrates file handling, structures, pointers, randomization, and modular code organization (`.h` / `.c`).  
Perfect as a small portfolio project for beginner C programmers.

---

## 🖼️ Gameplay Preview

=== HANGMAN ===
Guess the letters. You have 8 mistakes allowed.

Word: _ _ _ _ _ _ _
Mistakes: 0/8
Used letters: (none)

Enter a letter: a

Word: _ a _ _ a _
Mistakes: 1/8
Used letters: a
+---+
| |
O |
|
yaml
Skopiuj kod

---

## ⚙️ Features

- Random word selection from `words.txt`
- Mistake counter with ASCII hangman drawing
- Tracks already used letters
- Saves game results to `scores.txt` (date, result, word, number of mistakes)
- Clean modular code (`main.c`, `hangman.c`, `hangman.h`)

---

## 📂 Project Structure

hangman/
├── src/
│ ├── main.c # game loop & input handling
│ ├── hangman.c # game logic implementation
│ └── hangman.h # header file with declarations
├── words.txt # word list for the game
└── README.md

yaml
Skopiuj kod

---

## 🛠️ Requirements

- C compiler (e.g. `gcc` or `clang`)
- Works on Linux, macOS, and Windows (MinGW or WSL)

---

## ▶️ Compilation & Run

From the project root:

```bash
gcc -O2 -Wall -Wextra -std=c11 src/main.c src/hangman.c -o hangman
./hangman
📄 Example words.txt
vbnet
Skopiuj kod
programming
compiler
pointer
structure
file
algorithm
loop
array
📝 Example scores.txt
arduino
Skopiuj kod
2025-09-08 20:41:11;result=WIN;word=pointer;wrong=2
2025-09-08 20:45:33;result=LOSE;word=compiler;wrong=8
🚀 Possible Improvements
Difficulty levels (different word lists)

Hints system (one-time reveal)

Colorful ANSI terminal output

UTF-8 support (non-English letters)

Multiplayer mode (player enters the secret word)
