# Raspberry Pi 5 – Cross-Compilation Using VS Code Dev Container

This repository demonstrates a clean and modern development workflow for building and debugging C++ applications for a **Raspberry Pi 5**, using:

- **VS Code Dev Containers**
- **A Debian Bookworm–based Docker environment**
- **Cross-compiling for ARMhf**
- **Automatic deployment via SCP**
- **Remote debugging using gdbserver**
- **libgpiod (ARMhf) support**

This setup ensures that you develop entirely on your host machine while producing binaries that run correctly on your Raspberry Pi—without installing compilers or dependencies directly on the Pi.

---

## 🚀 Features

- ✔ Fully automated Docker Dev Container for cross-compiling  
- ✔ ARMhf cross-compiler (Raspberry Pi OS Bookworm glibc 2.36 compatible)  
- ✔ `libgpiod` ARMhf headers installed in the container  
- ✔ Automatic **build & deploy** using `CMakePresets.json`  
- ✔ Remote debugging via `gdbserver`  
- ✔ Colored Git prompt, Nano/Vim preinstalled  
- ✔ Clean `.gitignore`  
- ✔ No need to compile on the Pi  

---

## 📦 Requirements

- Windows / macOS / Linux  
- Docker Desktop  
- VS Code  
- Dev Containers extension  
- Raspberry Pi 5 running **Raspberry Pi OS Bookworm (32-bit)**  
- SSH enabled on the Raspberry Pi  

---

## 🧰 1. Building the Dev Container

Open the repository in VS Code and press:

> **Ctrl+Shift+P → Dev Containers: Rebuild and Reopen in Container**

VS Code will:

✔ Build the Docker image  
✔ Install ARMhf toolchains  
✔ Install GPIOD ARMhf headers  
✔ Configure Git prompt  
✔ Prepare your development environment  

---

## 🔑 2. Generate SSH Keys (inside the Dev Container)

```bash
ssh-keygen -t ed25519 -f ~/.ssh/id_ed25519 -N ""
```

---

## 📤 3. Copy Your SSH Key to the Raspberry Pi

```bash
ssh-copy-id -i ~/.ssh/id_ed25519.pub erwinbuysse@192.168.0.127
```

---

## 📝 4. Updating Raspberry Pi User/IP

If your Pi uses **another username or IP**, update:

### **CMakePresets.json**
```json
"PI_USER": "your_user",
"PI_HOST": "your_ip_address",
"PI_PATH": "/home/your_user/software/cpp/mypiapp"
```

### **.vscode/launch.json**
```json
"miDebuggerServerAddress": "your_ip_address:1234"
```

---

## 🛠 5. Build the Project

```bash
cmake --build --preset rpi-debug
```

Build & deploy:

```bash
cmake --build --preset rpi-debug-deploy
```

---

## 🐞 6. Remote Debugging

On the Raspberry Pi:

```bash
gdbserver :1234 ./mypi
```

In VS Code:

> Run → **Start Debugging**

---

## 📁 7. Repo Layout

```
MyPiApp/
 ├── src/
 ├── cmake/
 ├── .devcontainer/
 ├── .vscode/
 ├── CMakeLists.txt
 ├── CMakePresets.json
 ├── .gitignore
 └── README.md
```

---

## 🏁 Done!

You now have a full cross‑compilation workflow with automatic deployment and remote debugging.

