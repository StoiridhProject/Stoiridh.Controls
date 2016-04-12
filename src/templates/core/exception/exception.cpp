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
#include "exception.hpp"

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates {
//--------------------------------------------------------------------------------------------------


/*! \class Exception exception.hpp <StoiridhControlsTemplates/Core/Exception/Exception>
    \since StoiridhControlsTemplates 1.0
    \ingroup core
    \ingroup exception

    \brief The Exception class is a base class for all exceptions.
*/


/*!
    Constructs an exception with the \a given message.
*/
Exception::Exception(const QString &message) noexcept
    : m_message{message}
{
}

/*!
    Raises \a this instance of Exception.
*/
void Exception::raise() const
{
    throw (*this);
}

/*!
    Clones \a this instance of Exception.
*/
Exception *Exception::clone() const
{
    return (new Exception(*this));
}

/*!
    Returns an explanatory string.
*/
const char *Exception::what() const noexcept
{
    return {"StoiridhControlsTemplates::Exception"};
}

/*!
    Returns a explanatory string describing the error of the Exception.
*/
const QString &Exception::message() const noexcept
{
    return m_message;
}

/*!
    Sets the message of the Exception.
*/
void Exception::setMessage(QString &&message)
{
    m_message = std::move(message);
}

//--------------------------------------------------------------------------------------------------
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------
