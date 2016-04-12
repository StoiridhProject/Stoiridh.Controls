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

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates {
//--------------------------------------------------------------------------------------------------


/*! \class ExceptionHandler
    \since StoiridhControlsTemplates 1.0
    \ingroup core
    \ingroup exception

    \brief The ExceptionHandler class is a utility class to handle the exceptions.

    The class defines a set of static methods in order to handle an exception type. Generally, each
    methods come with a boolean condition and two others parameters. Those parameters are purely
    used to compose a pretty message when the exception is thrown.
*/


/*!
    Checks if \a pointer is null.

    \a name corresponds to the parameter or the variable name and \a type corresponds to the type of
    \a name.

    \tparam T a pointer type to check.

    Example:

    \code
    void apply(const Control *control)
    {
        using StoiridhControlsTemplates::ExceptionHandler;

        ExceptionHandler::checkNullPointer(control, QStringLiteral("control"),
                                                    QStringLiteral("const Control *"));

        // control is not null.
    }
    \endcode

    \throw NullPointerException if \a pointer is null.
*/
template<typename T>
void ExceptionHandler::checkNullPointer(T pointer, const QString &name, const QString &type)
{
    if (!pointer)
    {
        throw NullPointerException(name, type);
    }
}

//--------------------------------------------------------------------------------------------------
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------
