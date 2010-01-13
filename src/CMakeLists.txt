INCLUDE(${QT_USE_FILE})
INCLUDE_DIRECTORIES(
	${OpenCV_INCLUDE_DIRS} 
	${QT_INCLUDE_DIR}
	${PROJECT_SOURCE_DIR}/includes
	#${GTEST_INCLUDE_DIRS}
	)

IF(WIN32)
IF(CMAKE_C_FLAGS_RELEASE )
SET(SUBSYSTEM WIN32)
ELSEIF(CMAKE_C_FLAGS_DEBUG)
SET(WIN32_EXECUTABLE OFF )
ENDIF()
ENDIF(WIN32)

set(EagleEye_SRCS 
    main.cpp
	# core source
	core/cvframesource.cpp

	
	
	# gui source
	gui/mainwindow.cpp
	gui/movieviewer.cpp
	gui/tabdialog.cpp
	#gui/movieplayer.cpp
	#gui/cvmovielabel.cpp 
	
	#core/cvmovie.cpp
	
	# algorithm source
	algorithms/codebook.cpp
	algorithms/tracker.cpp
	algorithms/edge.cpp
	algorithms/mhi.cpp
	# test source 
	# test/sample1_unittest.cc
		
	)

set(EagleEye_MOCS
    # core header
	core/iframesource.h
	core/cvframesource.h
	#gui/movieplayer.h
	#core/cvmovie.h
    #gui/cvmovielabel.h
	# gui header
	
	gui/mainwindow.h
	gui/movieviewer.h
	gui/tabdialog.h
	
	# algorithm header
	algorithms/ialgorithmmodel.h
	algorithms/codebook.h
	algorithms/tracker.h
	algorithms/edge.h
	algorithms/mhi.h
	
	)
	
set(EagleEye_HEADERS
	# core header
	core/iframesource.h
	core/cvframesource.h
	#gui/movieplayer.h
	#core/cvmovie.h
    #gui/cvmovielabel.h
	# gui header
	
	gui/mainwindow.h
	gui/movieviewer.h
	gui/tabdialog.h
	
	# algorithm header
	algorithms/ialgorithmmodel.h
	algorithms/codebook.h
	algorithms/tracker.h
	algorithms/edge.h
	algorithms/mhi.h

	)
	
set(EagleEye_RCCS
	# resource
	resources/application.qrc
	)

# Declare the target (an executable)
ADD_DEFINITIONS(-DQT_DLL)
ADD_DEFINITIONS(-DQT_THREAD_SUPPORT)

QT4_ADD_RESOURCES(EagleEye_RCC_SRCS ${EagleEye_RCCS})
QT4_WRAP_CPP(EagleEye_MOC_SRCS ${EagleEye_MOCS})

ADD_EXECUTABLE(EagleEye ${EagleEye_SRCS} ${EagleEye_MOC_SRCS} ${EagleEye_RCC_SRCS} ${EagleEye_HEADERS}) 

TARGET_LINK_LIBRARIES(EagleEye 
	${QT_LIBRARIES} 
	${OpenCV_LIBRARIES} 
	${GTEST_BOTH_LIBRARIES}
	ecvblob 
	) 
	


set (QT_QTCORE_LIBRARY ${QT_LIBRARY_DIR}/../bin/QtCore4.dll)
set (QT_QTGUI_LIBRARY ${QT_LIBRARY_DIR}/../bin/QtGui4.dll)
if (MINGW)
find_file(MINGW_DLL mingwm10.dll)
INSTALL(FILES  ${MINGW_DLL} DESTINATION bin)
else (MINGW)
INCLUDE(InstallRequiredSystemLibraries)
endif (MINGW)

INSTALL(TARGETS EagleEye DESTINATION bin)
INSTALL(FILES  ${OpenCV_LIBRARIES} DESTINATION bin)
INSTALL(FILES  ${QT_QTCORE_LIBRARY} DESTINATION bin)
INSTALL(FILES  ${QT_QTGUI_LIBRARY} DESTINATION bin)

#GTEST_A DD_TESTS(${EXECUTABLE_OUTPUT_PATH}/EagleEye "" test/sample1_unittest.cc)
#ADD_TEST(AllTestsInEagleEye ${EXECUTABLE_OUTPUT_PATH}/EagleEye)
