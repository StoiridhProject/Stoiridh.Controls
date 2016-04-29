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
## [QML Autotest]                       - Stòiridh.Controls -                      [QML Autotest] ##
####################################################################################################
set(STOIRIDH_PROJECT_NAME "tst_sc_qml_controls")

####################################################################################################
##  Configuration                                                                                 ##
####################################################################################################
stoiridh_include("Stoiridh.Qt.Qml.Autotest")

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

####################################################################################################
##  Packages                                                                                      ##
####################################################################################################
find_package(Qt5 5.6 CONFIG COMPONENTS QuickTest REQUIRED)

####################################################################################################
##  Sources and Headers                                                                           ##
####################################################################################################
set(SOURCES
    "tst_stoiridh_controls.cpp"
)
####################################################################################################
##  Executable                                                                                    ##
####################################################################################################
stoiridh_qt_qml_add_autotest(${STOIRIDH_PROJECT_NAME}
    TEST_NAME "Stoiridh.Controls"
    DATA_DIR  "data"
    SOURCES   ${SOURCES}
    DEPENDS   Qt5::QuickTest)
