cmake_minimum_required(VERSION 3.16)
project(MyPiApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- executable ----
add_executable(mypi
    src/main.cpp
)

# Link libstdc++ and libgcc statically so we dont depend on the PI's version
target_link_options(mypi PRIVATE
    -static-libstdc++
    -static-libgcc
)

# ---- libgpiod (GPIO) ----
# Requires libgpiod-dev:armhf in the container and libgpiod-dev on the Pi
target_link_libraries(mypi PRIVATE gpiod)

# ---- deployment settings ----
set(PI_USER "erwinbuysse" CACHE STRING "Raspberry Pi SSH username")
set(PI_HOST "192.168.0.127" CACHE STRING "Raspberry Pi hostname or IP")
set(PI_PATH "/home/erwinbuysse/software/cpp/mypiapp/mypi" CACHE STRING "Remote path on Raspberry Pi")

# ---- deploy target: build + copy binary to the Pi ----
add_custom_target(deploy
    DEPENDS mypi

    COMMAND ${CMAKE_COMMAND} -E echo
            "Deploying '$<TARGET_FILE:mypi>' to ${PI_USER}@${PI_HOST}:${PI_PATH}"

    COMMAND scp
            -o BatchMode=yes
            -o ConnectTimeout=5
            -o StrictHostKeyChecking=no
            -o UserKnownHostsFile=/dev/null
            -o ControlMaster=no
            -o ControlPath=none
            "$<TARGET_FILE:mypi>"
            ${PI_USER}@${PI_HOST}:${PI_PATH}

    COMMENT "Copying Raspberry Pi binary via safe non-interactive SCP"
    VERBATIM
)
