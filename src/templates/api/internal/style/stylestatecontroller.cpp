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
#include "stylestatecontroller.hpp"

#include "control.hpp"
#include "core/exception/exceptionhandler.hpp"

#include "api/internal/style/style.hpp"

#include "api/private/control_p.hpp"

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates {
//--------------------------------------------------------------------------------------------------


/*! \class StyleStateController
    \since StoiridhControlsTemplates 1.0
    \ingroup style

    \brief The StyleStateController class handles the different style state operations of a
           style.

    \sa Style
*/


/*!
    Constructs a style state controller with the given \a style.

    \throw NullPointerException if \a style is null.
*/
StyleStateController::StyleStateController(Style *style)
    : m_style{style}
{
    ExceptionHandler::checkNullPointer(m_style, QStringLiteral("style"), QStringLiteral("Style *"));
}

/*!
    Returns true if the style state controller has not style state operations, otherwise,
    false.
*/
bool StyleStateController::isEmpty() const noexcept
{
    return m_operations.isEmpty();
}

/*!
    Returns the number of style state operations in the style state controller.
*/
StyleStateController::size_type StyleStateController::count() const noexcept
{
    return m_operations.count();
}

/*!
    Returns the style associated to the style state controller.
*/
Style *StyleStateController::style() const
{
    return m_style;
}

/*!
    Adds a new style state \a operation at the end of the style state controller.

    \sa findStateOperation(), defaultStateOperation()
*/
void
StyleStateController::addStateOperation(QSharedPointer<StyleStateOperation> &&operation) noexcept
{
    m_operations[operation->name()] = std::move(operation);
}

/*!
    Finds the \a name of a style state operation and returns a weak pointer on it.

    An empty \a name means that the default style state operation will be returned.

    \note If \a name was not found, a default-constructed weak pointer is returned to notice
    there is not operation with that \a name.

    \sa defaultStateOperation()
*/
QWeakPointer<StyleStateOperation>
StyleStateController::findStateOperation(const QString &name) const noexcept
{
    return m_operations.contains(name) ? (*m_operations.find(name)).toWeakRef()
                                       : QWeakPointer<StyleStateOperation>{};
}

/*!
    Returns the default style state operation.

    \sa findStateOperation()
*/
QWeakPointer<StyleStateOperation> StyleStateController::defaultStateOperation() const noexcept
{
    return findStateOperation({});
}

/*!
    Applies a style state operation to the given target \a control.

    \throw NullPointerException if \a control is null.
*/
void StyleStateController::apply(const Control *control)
{
    ExceptionHandler::checkNullPointer(control,
                                       QStringLiteral("control"),
                                       QStringLiteral("const Control *"));

    const auto *const d_control = ControlPrivate::get(control);
    const auto styleStateName = d_control->styleState();
    const auto key = m_operations.contains(styleStateName) ? styleStateName : QString{};

    // apply the default style's state before any other style's states.
    if (auto defaultState = m_operations.value({}))
    {
        defaultState->apply(control);
    }

    if (!key.isEmpty())
    {
        if (auto state = m_operations.value(key))
        {
            state->apply(control);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////   DOCUMENTATION    ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \typedef StyleStateController::size_type

    This type alias represents an integer type for StyleStateController.
*/

//--------------------------------------------------------------------------------------------------
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------
