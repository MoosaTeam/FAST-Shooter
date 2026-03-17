cmake_minimum_required(VERSION 3.10)
project(FAST_Shooter VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enforce hardware acceleration and strict optimization
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native")

# Find the SFML library
find_package(SFML 2 COMPONENTS graphics window system audio REQUIRED)

# List your source files
add_executable(FAST_Shooter
    main.cpp
    Background.cpp
    Enemy.cpp
    EnemyDiagonal.cpp
    EnemyProjectile.cpp
    Game.cpp
    Menu.cpp
    Player.cpp
    Projectile.cpp
    Timer.cpp
)

# Link using the legacy names required by your specific package
target_link_libraries(FAST_Shooter sfml-graphics sfml-window sfml-system sfml-audio)

# --- ASSET COPYING AUTOMATION ---
# This guarantees your assets are always next to the executable
add_custom_command(TARGET FAST_Shooter POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Fonts $<TARGET_FILE_DIR:FAST_Shooter>/Fonts
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Sounds $<TARGET_FILE_DIR:FAST_Shooter>/Sounds
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Sprite $<TARGET_FILE_DIR:FAST_Shooter>/Sprite
)
