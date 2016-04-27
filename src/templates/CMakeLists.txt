####################################################################################################
##                                                                                                ##
##            Copyright (C) 2015-2016 William McKIE                                               ##
##                                                                                                ##
##            This program is free software: you can redistribute it and/or modify                ##
##            it under the terms of the GNU General Public License as published by                ##
##            the Free Software Foundation, either version 3 of the License, or                   ##
##            (at your option) any later version.                                                 ##
##                                                                                                ##
##            This program is distributed in the hope that it will be useful,                     ##
##            but WITHOUT ANY WARRANTY; without even the implied warranty of                      ##
##            MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                       ##
##            GNU General Public License for more details.                                        ##
##                                                                                                ##
##            You should have received a copy of the GNU General Public License                   ##
##            along with this program.  If not, see <http://www.gnu.org/licenses/>.               ##
##                                                                                                ##
####################################################################################################
##                                 - Stòiridh.Controls.Templates -                                ##
####################################################################################################
set(STOIRIDH_PROJECT_NAME "StoiridhControlsTemplates")

####################################################################################################
##  Configuration                                                                                 ##
####################################################################################################
stoiridh_include("Stoiridh.Qt.Library")
stoiridh_include("Stoiridh.Install.LocalAPI")

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# project API sources directories
set(PRIVATE_API_SOURCE_DIR "${STOIRIDH_CONTROLS_TEMPLATES_SOURCE_DIR}/api/private")
set(PUBLIC_API_SOURCE_DIR  "${STOIRIDH_CONTROLS_TEMPLATES_SOURCE_DIR}/api/public")

add_definitions(
    -DSTOIRIDH_CONTROLS_TEMPLATES_LIB
    -DQT_NO_CAST_FROM_ASCII
    -DQT_NO_CAST_TO_ASCII
)
####################################################################################################
##  Packages                                                                                      ##
####################################################################################################
find_package(Qt5Core  5.6 CONFIG COMPONENTS Private REQUIRED)
find_package(Qt5Gui   5.6 CONFIG COMPONENTS Private REQUIRED)
find_package(Qt5Qml   5.6 CONFIG COMPONENTS Private REQUIRED)
find_package(Qt5Quick 5.6 CONFIG COMPONENTS Private REQUIRED)

####################################################################################################
##  Sources and Headers                                                                           ##
####################################################################################################
set(PUBLIC_SOURCES
    # templates
    "${STOIRIDH_CONTROLS_TEMPLATES_SOURCE_DIR}/control.cpp"
    "${STOIRIDH_CONTROLS_TEMPLATES_SOURCE_DIR}/control.hpp"
    "${STOIRIDH_CONTROLS_TEMPLATES_SOURCE_DIR}/global.hpp"
    "${STOIRIDH_CONTROLS_TEMPLATES_SOURCE_DIR}/padding.cpp"
    "${STOIRIDH_CONTROLS_TEMPLATES_SOURCE_DIR}/padding.hpp"
)
####################################################################################################
##  Public API                                                                                    ##
####################################################################################################
set(PUBLIC_HEADERS
    # templates
    "${PUBLIC_API_SOURCE_DIR}/Control"
    "${PUBLIC_API_SOURCE_DIR}/Padding"
    "${PUBLIC_API_SOURCE_DIR}/global.hpp"
)
####################################################################################################
##  Private API                                                                                   ##
####################################################################################################
set(PRIVATE_SOURCES
    # templates
    "${PRIVATE_API_SOURCE_DIR}/control_p.hpp"
)
####################################################################################################
##  Library                                                                                       ##
####################################################################################################
stoiridh_qt_add_library(${STOIRIDH_PROJECT_NAME}
                        ALIAS       StoiridhControls::Templates
                        SOURCES     ${PUBLIC_SOURCES} ${PRIVATE_SOURCES}
                        OTHER_FILES ${PUBLIC_HEADERS}
                        DEPENDS     Qt5::Core Qt5::Gui Qt5::Qml Qt5::Quick
                        USE_QT_PRIVATE_API)

####################################################################################################
##  Local Install                                                                                 ##
####################################################################################################
# create a local copy of the header files into the build directory, see STOIRIDH_INSTALL_ROOT.
stoiridh_install_local_api(HEADERS       ${PUBLIC_HEADERS}
                           DESTINATION   ${STOIRIDH_PROJECT_NAME}
                           VERSION       ${PROJECT_VERSION}
                           PUBLIC        ${PUBLIC_SOURCES}
                           PRIVATE       ${PRIVATE_SOURCES}
                           PATH_SUFFIXES "api/public;api/private")
