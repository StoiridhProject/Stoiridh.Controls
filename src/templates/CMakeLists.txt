####################################################################################################
##                                                                                                ##
##            Copyright (C) 2016 William McKIE                                                    ##
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
set(INTERNAL_API_SOURCE_DIR "${STOIRIDH_CONTROLS_TEMPLATES_SOURCE_DIR}/api/internal")
set(PRIVATE_API_SOURCE_DIR  "${STOIRIDH_CONTROLS_TEMPLATES_SOURCE_DIR}/api/private")
set(PUBLIC_API_SOURCE_DIR   "${STOIRIDH_CONTROLS_TEMPLATES_SOURCE_DIR}/api/public")

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
    # core
    "${STOIRIDH_CONTROLS_TEMPLATES_SOURCE_DIR}/core/exception/exception.cpp"
    "${STOIRIDH_CONTROLS_TEMPLATES_SOURCE_DIR}/core/exception/exception.hpp"
    "${STOIRIDH_CONTROLS_TEMPLATES_SOURCE_DIR}/core/exception/exceptionhandler.hpp"
    "${STOIRIDH_CONTROLS_TEMPLATES_SOURCE_DIR}/core/exception/exceptionhandler.inl"
    "${STOIRIDH_CONTROLS_TEMPLATES_SOURCE_DIR}/core/exception/nullpointerexception.cpp"
    "${STOIRIDH_CONTROLS_TEMPLATES_SOURCE_DIR}/core/exception/nullpointerexception.hpp"

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
    # core
    "${PUBLIC_API_SOURCE_DIR}/Core/Exception/Exception"
    "${PUBLIC_API_SOURCE_DIR}/Core/Exception/ExceptionHandler"
    "${PUBLIC_API_SOURCE_DIR}/Core/Exception/NullPointerException"

    # templates
    "${PUBLIC_API_SOURCE_DIR}/Control"
    "${PUBLIC_API_SOURCE_DIR}/Padding"
    "${PUBLIC_API_SOURCE_DIR}/global.hpp"
)
####################################################################################################
##  Internal API                                                                                  ##
####################################################################################################
set(INTERNAL_SOURCES
    # style
    "${INTERNAL_API_SOURCE_DIR}/style/utility/stylefactoryhelper.cpp"
    "${INTERNAL_API_SOURCE_DIR}/style/utility/stylefactoryhelper.hpp"
    "${INTERNAL_API_SOURCE_DIR}/style/abstractstyledispatcher.cpp"
    "${INTERNAL_API_SOURCE_DIR}/style/abstractstyledispatcher.hpp"
    "${INTERNAL_API_SOURCE_DIR}/style/style.cpp"
    "${INTERNAL_API_SOURCE_DIR}/style/style.hpp"
    "${INTERNAL_API_SOURCE_DIR}/style/styledispatcher.cpp"
    "${INTERNAL_API_SOURCE_DIR}/style/styledispatcher.hpp"
    "${INTERNAL_API_SOURCE_DIR}/style/stylefactory.cpp"
    "${INTERNAL_API_SOURCE_DIR}/style/stylefactory.hpp"
    "${INTERNAL_API_SOURCE_DIR}/style/stylefactory.inl"
    "${INTERNAL_API_SOURCE_DIR}/style/stylepropertychanges.cpp"
    "${INTERNAL_API_SOURCE_DIR}/style/stylepropertychanges.hpp"
    "${INTERNAL_API_SOURCE_DIR}/style/stylepropertychangesparser.cpp"
    "${INTERNAL_API_SOURCE_DIR}/style/stylepropertychangesparser.hpp"
    "${INTERNAL_API_SOURCE_DIR}/style/stylepropertyexpression.cpp"
    "${INTERNAL_API_SOURCE_DIR}/style/stylepropertyexpression.hpp"
    "${INTERNAL_API_SOURCE_DIR}/style/stylestate.cpp"
    "${INTERNAL_API_SOURCE_DIR}/style/stylestate.hpp"
    "${INTERNAL_API_SOURCE_DIR}/style/stylestatecontroller.cpp"
    "${INTERNAL_API_SOURCE_DIR}/style/stylestatecontroller.hpp"
    "${INTERNAL_API_SOURCE_DIR}/style/stylestateoperation.cpp"
    "${INTERNAL_API_SOURCE_DIR}/style/stylestateoperation.hpp"

    # others
    "${INTERNAL_API_SOURCE_DIR}/abstractcontrol.hpp"
    "${INTERNAL_API_SOURCE_DIR}/global.hpp"
)
####################################################################################################
##  Private API                                                                                   ##
####################################################################################################
set(PRIVATE_SOURCES
    # bootstrap
    "${PRIVATE_API_SOURCE_DIR}/bootstrap/qmlextensionplugin.cpp"
    "${PRIVATE_API_SOURCE_DIR}/bootstrap/qmlextensionplugin_p.hpp"

    # style
    "${PRIVATE_API_SOURCE_DIR}/style/style_p.hpp"
    "${PRIVATE_API_SOURCE_DIR}/style/stylepropertychanges_p.hpp"
    "${PRIVATE_API_SOURCE_DIR}/style/stylestate_p.hpp"

    # templates
    "${PRIVATE_API_SOURCE_DIR}/control_p.hpp"
)
####################################################################################################
##  Library                                                                                       ##
####################################################################################################
stoiridh_qt_add_library(${STOIRIDH_PROJECT_NAME}
    ALIAS       StoiridhControls::Templates
    SOURCES     ${PUBLIC_SOURCES} ${INTERNAL_SOURCES} ${PRIVATE_SOURCES}
    OTHER_FILES ${PUBLIC_HEADERS}
    DEPENDS     Qt5::Core Qt5::Gui Qt5::Qml Qt5::Quick
    USE_QT_PRIVATE_API)

target_compile_definitions(${STOIRIDH_PROJECT_NAME}
    PRIVATE STOIRIDH_CONTROLS_TEMPLATES_LIB QT_NO_CAST_FROM_ASCII QT_NO_CAST_TO_ASCII)

if(STOIRIDH_PROJECT_TESTING_ENABLE_INTERNAL)
    target_compile_definitions(${STOIRIDH_PROJECT_NAME}
        PRIVATE SCT_BUILD_INTERNAL_API SCT_INTERNAL_LIB)
endif()

target_include_directories(${STOIRIDH_PROJECT_NAME}
    INTERFACE $<BUILD_INTERFACE:${STOIRIDH_CONTROLS_TEMPLATES_SOURCE_DIR}>)

####################################################################################################
##  Local Install                                                                                 ##
####################################################################################################
# create a local copy of the header files into the build directory, see STOIRIDH_INSTALL_ROOT.
stoiridh_install_local_api(HEADERS ${PUBLIC_HEADERS}
    DESTINATION   ${STOIRIDH_PROJECT_NAME}
    VERSION       ${PROJECT_VERSION}
    PUBLIC        ${PUBLIC_SOURCES}
    INTERNAL      ${INTERNAL_SOURCES}
    PRIVATE       ${PRIVATE_SOURCES}
    PATH_SUFFIXES "api/public;api/internal;api/private")
