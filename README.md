# Raspberry Pi 5 – Cross‑Compilation Using VS Code Dev Container

This repository provides a complete development environment for building **ARM32 (armhf)** applications for a **Raspberry Pi 5** — while compiling **entirely on your Windows PC inside a Docker Dev Container**.

It includes:
- A Docker‑based cross‑compilation toolchain (gcc/g++ for armhf)
- CMake + Ninja build system
- Deployment via `scp`
- Remote debugging using `gdbserver` + `gdb-multiarch`
- libgpiod (ARM32) support
- Git‑aware colored shell prompt

---

## 📦 1. Prerequisites

Before you start, install on Windows:

1. **Docker Desktop**
2. **Visual Studio Code**
3. **VS Code Extensions:**
   - *Dev Containers* (`ms-vscode-remote.remote-containers`)
   - C/C++ Tools
   - CMake Tools

4. Enable WSL2 backend in Docker Desktop (recommended)

---

## 🐳 2. Building the Dev Container

The devcontainer configuration lives in the `.devcontainer` directory.
VS Code will automatically build the Docker container.

### Steps:

1. Open VS Code
2. Open the folder containing this repository:
   
   **File → Open Folder → MyPiApp**

3. VS Code will detect `.devcontainer/devcontainer.json` and ask:

   **“Reopen in Container?”** → Click **Yes**

4. The Docker image builds automatically (this takes 1–3 minutes the first time).

After build completes, VS Code opens inside the container with:
- armhf toolchain installed
- CMake + Ninja
- gdb-multiarch
- libgpiod ARM32 headers
- git prompt and vim installed

---

## 🔐 SSH keys to the Raspberry Pi

After the dev container is up the first time, set up passwordless SSH from the container to your Raspberry Pi. This is required so CMake can deploy the binary via `scp` without prompting for a password.

Inside the **dev container terminal**:

```bash
ssh-keygen -t ed25519 -f ~/.ssh/id_ed25519
ssh-copy-id -i ~/.ssh/id_ed25519.pub erwinbuysse@192.168.0.127
```

- Accept the host key if asked.
- Enter the Raspberry Pi user password once.

After this, you should be able to run:

```bash
ssh erwinbuysse@192.168.0.127
```

without being prompted for a password. The **`rpi-debug-deploy`** preset relies on this key-based authentication.

---

The devcontainer configuration lives in the `.devcontainer` directory.
VS Code will automatically build the Docker container.

### Steps:

1. Open VS Code
2. Open the folder containing this repository:
   
   **File → Open Folder → MyPiApp**

3. VS Code will detect `.devcontainer/devcontainer.json` and ask:

   **“Reopen in Container?”** → Click **Yes**

4. The Docker image builds automatically (this takes 1–3 minutes the first time).

After build completes, VS Code opens inside the container with:
- armhf toolchain installed
- CMake + Ninja
- gdb-multiarch
- libgpiod ARM32 headers
- git prompt and vim installed

---

## 🛠 3. Project Structure

```
MyPiApp/
 ├── src/
 │   └── main.cpp
 ├── cmake/
 │   └── toolchain-rpi-armhf.cmake
 ├── build-rpi-debug/      <-- auto-generated (ignored)
 ├── CMakeLists.txt
 ├── CMakePresets.json
 └── .devcontainer/
     ├── devcontainer.json
     └── Dockerfile
```

---

## ⚙️ 4. Configuring the Build

The repository uses **CMake Presets**, so building is simple.

### Configure Debug build
```
cmake --preset rpi-debug
```

### Build only
```
cmake --build --preset rpi-debug-build
```

### Build & Deploy to the Pi
```
cmake --build --preset rpi-debug-deploy
```

The deployment copies the compiled binary to the Raspberry Pi using `scp`.
SSH keys are already installed inside the container so no password prompts appear.

---

## 🚀 5. Running on the Raspberry Pi

On the Raspberry Pi:

```
cd ~/software/cpp/mypiapp
./mypi
```

---

## 🐞 6. Remote Debugging

### On the Raspberry Pi:
Run your program under gdbserver:

```
gdbserver :1234 ./mypi
```

### In VS Code:
Press **F5** and choose **Remote GDB Debug (Raspberry Pi)**.

Your code will debug from inside the Dev Container.

---

## 🧹 7. Build Artifacts

Build directories such as `build-rpi-debug` are automatically ignored via `.gitignore`.
They should not appear in your Git commits.

---

## 📚 8. Common Commands (inside the container)

| Action | Command |
|--------|----------|
| Rebuild CMake | `rm -rf build-rpi-debug && cmake --preset rpi-debug` |
| Build | `cmake --build --preset rpi-debug-build` |
| Deploy | `cmake --build --preset rpi-debug-deploy` |
| Clean | `git clean -xfd` |
| SSH into Pi | `ssh erwinbuysse@192.168.0.127` |

---

## 🔑 9. GitHub Usage

If you cloned this repo normally, Git is ready.
If not, initialize and push:

```
git init
git remote add origin <YOUR_REPO_URL>
git add .
git commit -m "Initial commit"
git push -u origin main
```

---

## 🎉 Done!

You now have a full cross‑compilation, deployment, and debugging environment for the Raspberry Pi 5 — entirely running inside Docker on your Windows machine.

If you want improvements (unit tests, CI, packaging), just ask!

