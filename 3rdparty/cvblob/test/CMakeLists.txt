# Copyright (C) 2007 by Cristóbal Carnero Liñán
# grendel.ccl@gmail.com
#
# This file is part of cvBlob.
#
# cvBlob is free software: you can redistribute it and/or modify
# it under the terms of the Lesser GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# cvBlob is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# Lesser GNU General Public License for more details.
#
# You should have received a copy of the Lesser GNU General Public License
# along with cvBlob.  If not, see <http://www.gnu.org/licenses/>.
#


include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${ecvblob_SOURCE_DIR}/cvBlob)

# TEST
set(TEST_SRC test.cpp)

add_executable(test ${TEST_SRC})

target_link_libraries(test ecvblob)
target_link_libraries(test ${OpenCV_LIBRARIES})


# TEST TRACKING
set(TEST_TRACKING_SRC test_tracking.cpp)

add_executable(test_tracking ${TEST_TRACKING_SRC})

target_link_libraries(test_tracking ecvblob)
target_link_libraries(test_tracking ${OpenCV_LIBRARIES})
