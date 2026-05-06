# CMakeList.txt: proyecto de CMake para AEDProfeCMake, incluya el origen y defina
# la lógica específica del proyecto aquí.
#


# Agregue un origen al ejecutable de este proyecto.
set(ProjectTarget AEDProfeCM)
set(ProjectName AEDProfeCM)
set(LibTarget AEDProfeLib) #AEDProfeCMakeLib
set(LibName AEDProfeLib)	
add_executable (${ProjectTarget} "${ProjectName}.cpp" "${ProjectName}.h" "${LibTarget}.h" "${LibTarget}I.h" "${LibTarget}.cpp")

add_executable (Nolineales "AEDNoLineales.h" "AEDNoLinealesImp.h" "${ProjectName}.cpp" "${ProjectName}.h" "${LibTarget}.h" "${LibTarget}I.h" "${LibTarget}.cpp")

# Parte 1: Hospital con punteros (reimplementacion de la practica 1)
add_executable (HospitalP2 "HospitalP2.h" "HospitalP2.cpp" "HospitalP2_main.cpp")


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET AEDProfeCM PROPERTY CXX_STANDARD 20)
  set_property(TARGET Nolineales PROPERTY CXX_STANDARD 20)
  set_property(TARGET HospitalP2 PROPERTY CXX_STANDARD 20)
endif()

#for Google Test:
enable_testing()

add_executable( ${ProjectTarget}_test
				"${ProjectName}_test.cpp"
				"${LibTarget}.h" "${LibTarget}I.h" "${LibTarget}.cpp"
				"AEDNoLineales.h" "AEDNoLinealesImp.h"
				)
target_link_libraries( ${ProjectTarget}_test
	GTest::gtest_main
	)
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${ProjectTarget}_test PROPERTY CXX_STANDARD 20)
endif()

include(GoogleTest)
gtest_discover_tests(${ProjectTarget}_test)