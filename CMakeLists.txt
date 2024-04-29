cmake_minimum_required(VERSION 3.27)
project(PharmacyC C)

set(CMAKE_C_STANDARD 11)

add_executable(PharmacyC main.c
        medicine.c
        repository.c
        controller.c
        ui.c
        tests.c)
