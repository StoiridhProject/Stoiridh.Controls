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
#include "nullpointerexception.hpp"

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates {
//--------------------------------------------------------------------------------------------------


/*! \class NullPointerException nullpointerexception.hpp <StoiridhControlsTemplates/Core/Exception/NullPointerException>
    \since StoiridhControlsTemplates 1.0
    \ingroup core
    \ingroup exception

    \brief The NullPointerException class represents an exception to handle a null object.

    A NullPointerException exception is thrown when an application attempts to use a null pointer
    where an object is required.
*/


/*!
    Constructs a null pointer exception with the \a given message.
*/
NullPointerException::NullPointerException(const QString &name, const QString &type) noexcept
    : Exception{}
{
    if (!name.isEmpty())
    {
        auto message = QString::fromUtf8("%1 ").arg(name);

        if (!type.isEmpty())
        {
            message.append(QStringLiteral("of type '%1' ").arg(type));
        }

        message.append(QStringLiteral("is null"));

        setMessage(std::move(message));
    }
}

/*!
    Raises \a this instance of NullPointerException.
*/
void NullPointerException::raise() const
{
    throw (*this);
}

/*!
    Clones \a this instance of NullPointerException.
*/
NullPointerException *NullPointerException::clone() const
{
    return (new NullPointerException(*this));
}

/*!
    Returns an explanatory string.
*/
const char *NullPointerException::what() const noexcept
{
    return {"StoiridhControlsTemplates::NullPointerException"};
}

//--------------------------------------------------------------------------------------------------
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------
