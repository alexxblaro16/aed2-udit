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


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET AEDProfeCM PROPERTY CXX_STANDARD 20)
endif()

#for Google Test:
enable_testing()

add_executable( ${ProjectTarget}_test 
				"${ProjectName}_test.cpp"
				"${LibTarget}.h" "${LibTarget}I.h" "${LibTarget}.cpp"
				)
target_link_libraries( ${ProjectTarget}_test	
	GTest::gtest_main
	)

include(GoogleTest)
gtest_discover_tests(${ProjectTarget}_test)