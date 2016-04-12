////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                //
//            Copyright (C) 2016 William McKIE                                                    //
//                                                                                                //
//            This program is free software: you can redistribute it and/or modify                //
//            it under the terms of the GNU General Public License as published by                //
//            the Free Software Foundation, either version 3 of the License, or                   //
//            (at your option) any later version.                                                 //
//                                                                                                //
//            This program is distributed in the hope that it will be useful,                     //
//            but WITHOUT ANY WARRANTY; without even the implied warranty of                      //
//            MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                       //
//            GNU General Public License for more details.                                        //
//                                                                                                //
//            You should have received a copy of the GNU General Public License                   //
//            along with this program.  If not, see <http://www.gnu.org/licenses/>.               //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef STOIRIDHCONTROLSTEMPLATES_CORE_EXCEPTION_EXCEPTIONHANDLER_HPP
#define STOIRIDHCONTROLSTEMPLATES_CORE_EXCEPTION_EXCEPTIONHANDLER_HPP

#include <StoiridhControlsTemplates/Public/global.hpp>
#include <StoiridhControlsTemplates/Core/Exception/NullPointerException>

#include <QObject>

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates {
//--------------------------------------------------------------------------------------------------

class STOIRIDH_CONTROLS_TEMPLATES_API ExceptionHandler
{
public:
    template<typename T>
    static void checkNullPointer(T pointer, const QString &name = {}, const QString &type = {});
};

//--------------------------------------------------------------------------------------------------
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------
#include "exceptionhandler.inl"
//--------------------------------------------------------------------------------------------------

#endif // STOIRIDHCONTROLSTEMPLATES_CORE_EXCEPTION_EXCEPTIONHANDLER_HPP
