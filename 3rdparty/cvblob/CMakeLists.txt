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

# XXX It's possible that this can work with a previous version of CMake.
# TODO Check it.
project(ecvblob)
set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_BUILD_TYPE Debug)

#if(!WIN32)
#  set(CMAKE_EXE_LINKER_FLAGS -Bstatic)
#endif(!WIN32)

add_subdirectory(cvBlob lib)
#add_subdirectory(pyCvBlob pyCvBlob)
add_subdirectory(test test)

#install(DIRECTORY dll DESTINATION dll)

