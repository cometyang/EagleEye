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

set(EagleCvBlob_SRCS
		   cvblob.cpp
           cvlabel.cpp
		   cvaux.cpp
		   cvcontour.cpp
		   cvtrack.cpp
)

set(EagleCvBlob_HEADERS
		   cvblob.h
)

add_library(ecvblob STATIC ${EagleCvBlob_SRCS} ${EagleCvBlob_HEADERS})
