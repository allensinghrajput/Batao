# 🚀 BATAO - CLI Ping Tool

## 📌 How to Use

### ▶️ Run from Terminal

```bash
batao <hostname/IP> [count]
```

### 🔁 Continuous Mode

```bash
batao <hostname/IP> /t
batao <hostname/IP> --t
```

### ❓ Help Menu

```bash
batao ?
batao --help
```

### 🖱️ Double Click Mode

* Open `BATAO.exe`
* Enter host/IP
* Choose:

  * Normal (fixed packets)
  * Continuous (/t)
* Press any key to stop (in `/t` mode)

---

## 📖 Commands

| Command                | Description                       |
| ---------------------- | --------------------------------- |
| `batao <host>`         | Sends 4 packets to the host       |
| `batao <host> <count>` | Sends specified number of packets |
| `batao <host> /t`      | Continuous ping until key press   |
| `batao <host> --t`     | Same as `/t`                      |
| `batao ?`              | Shows help menu                   |
| `batao --help`         | Shows help menu                   |

---

## ⚙️ How It’s Made

* Language: **C**
* Platform: **Windows (MinGW / GCC)**
* Uses:

  * `system()` → executes native `ping`
  * `popen()` → reads output
  * `string.h` → parsing responses
  * `conio.h` → key detection (`/t` mode)
* Filters only **"Reply from"** lines
* Tracks:

  * Packets sent/received/lost
  * Min / Max / Average time

---

## ✨ Features

* CLI-based ping tool
* Continuous mode (`/t`)
* Clean output (only reply lines)
* Live packet tracking
* Final statistics summary
* Interactive mode (double-click support)
* Custom `.exe` icon support

---

## 👤 Credit

**Abhinav Kumar**
Creator & Developer of BATAO
