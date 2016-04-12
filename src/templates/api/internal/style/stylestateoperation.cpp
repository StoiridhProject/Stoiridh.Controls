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
#include "stylestateoperation.hpp"

#include "control.hpp"
#include "core/exception/exceptionhandler.hpp"

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates {
//--------------------------------------------------------------------------------------------------


/*! \class StyleStateOperation
    \since StoiridhControlsTemplates 1.0
    \ingroup style

    \brief The StyleStateOperation class applies an operation to a control.
*/


/*!
    Constructs a style state operation with the given \a name.
*/
StyleStateOperation::StyleStateOperation(const QString &name) noexcept
    : m_name{name}
{
}

/*!
    Constructs a style state operation by copying \a rhs to \a this StyleStateOperation instance.
*/
StyleStateOperation::StyleStateOperation(const StyleStateOperation &rhs)
    : m_name{rhs.m_name}
    , m_expressions(rhs.m_expressions)
{

}

/*!
    Constructs a style state operation by moving \a rhs to \a this StyleStateOperation instance.
*/
StyleStateOperation::StyleStateOperation(StyleStateOperation &&rhs) noexcept
    : m_name{std::move(rhs.m_name)}
    , m_expressions(std::move(rhs.m_expressions))
{
    rhs.m_name.clear();
    rhs.m_expressions.clear();
}

/*!
    Returns a STL iterator pointing to the first style property expression in the style state
    operation.

    \sa cbegin(), end()
*/
StyleStateOperation::iterator StyleStateOperation::begin()
{
    return m_expressions.begin();
}

/*!
    Returns a const STL iterator pointing to the first style property expression in the style state
    operation.

    \sa begin(), cend()
*/
StyleStateOperation::const_iterator StyleStateOperation::cbegin() const
{
    return m_expressions.cbegin();
}

/*!
    Returns a STL iterator pointing to a non-existant style property expression after the last style
    property expression in the style state operation.

    \sa begin(), cend()
*/
StyleStateOperation::iterator StyleStateOperation::end()
{
    return m_expressions.end();
}

/*!
    Returns a const STL iterator pointing to a non-existant style property expression after the last
    style property expression in the style state operation.

    \sa cbegin(), end()
*/
StyleStateOperation::const_iterator StyleStateOperation::cend() const
{
    return m_expressions.cend();
}

/*!
    Returns the name of the style state operation.

    \sa setName()
*/
QString StyleStateOperation::name() const
{
    return m_name;
}

/*!
    Sets a \a name for the style state operation.

    \sa name()
*/
void StyleStateOperation::setName(const QString &name)
{
    if (m_name != name)
    {
        m_name = name;
    }
}

/*!
    Inserts \a expression at the end of the style state operation.

    Example:

    \code
    StyleStateOperation operation{};

    auto expression = QSharedPointer<StylePropertyExpression>::create();
    operation.addExpression(std::move(expression));
    \endcode
*/
void
StyleStateOperation::addExpression(QSharedPointer<StylePropertyExpression> &&expression) noexcept
{
    m_expressions.push_back(std::move(expression));
}

/*!
    Inserts \a mapping for a StylePropertyExpression contained in the style state operation at
    index position \a index.

    \warning \a index must be a valid index position in the style state operation
             (i.e., 0 <= i < count()).
*/
void StyleStateOperation::insertExpressionMapping(int index, const Mapping &mapping)
{
    const auto &expression = m_expressions.at(index);

    if (expression && !expression->containsControl(mapping.first))
    {
        expression->addMapping(mapping.first, mapping.second);
    }
}

/*!
    Returns a weak pointer to a StylePropertyExpression at index position \a index in the style
    state operation.

    Example:

    \code
    StyleStateOperation operation{QStringLiteral("Operation")};

    // insert expressions...

    if (auto expression = operation.expressionAt(0).lock())
    {
        // do something with the style property expression.
    }
    \endcode

    \warning \a index must be a valid index position in the style state operation
             (i.e., 0 <= i < count()).
*/
QWeakPointer<StylePropertyExpression> StyleStateOperation::expressionAt(int index) const
{
    return m_expressions.at(index).toWeakRef();
}

/*!
    Applies the style state operation to \a control.

    \return true, if the style state operation is successfully applied to \a control, otherwise,
            false.

    \throw NullPointerException if \a control is null.
*/
void StyleStateOperation::apply(const Control *control)
{
    ExceptionHandler::checkNullPointer(control,
                                       QStringLiteral("control"),
                                       QStringLiteral("const Control *"));

    for (const auto &expression : m_expressions)
    {
        if (expression)
        {
            expression->apply(control);
        }
    }
}

/*!
    Copies \a rhs to \a this StyleStateOperation instance and returns a reference to \a this
    style state operation.
*/
StyleStateOperation &StyleStateOperation::operator=(const StyleStateOperation &rhs)
{
    if (this != &rhs)
    {
        m_name = rhs.m_name;
        m_expressions = rhs.m_expressions;
    }

    return (*this);
}

/*!
    Moves \a rhs to \a this StyleStateOperation instance and returns a reference to \a this
    style state operation.
*/
StyleStateOperation &StyleStateOperation::operator=(StyleStateOperation &&rhs) noexcept
{
    m_name = std::move(rhs.m_name);
    m_expressions = std::move(rhs.m_expressions);

    rhs.m_name.clear();
    rhs.m_expressions.clear();

    return (*this);
}

/*!
    Returns true if the style state operation is equal to \a rhs style state operation,
    otherwise, false.
*/
bool StyleStateOperation::operator==(const StyleStateOperation &rhs) noexcept
{
    return (m_name == rhs.m_name && m_expressions == rhs.m_expressions);
}

/*!
    Returns true if the style state operation is not equal to \a rhs style state operation,
    otherwise, false.
*/
bool StyleStateOperation::operator!=(const StyleStateOperation &rhs) noexcept
{
    return !(*this == rhs);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////   DOCUMENTATION    ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \typedef StyleStateOperation::iterator

    This type alias provides a STL non-const iterator for StyleStateOperation.

    \sa begin(), end()
*/

/*! \typedef StyleStateOperation::const_iterator

    This type alias provides a STL const iterator for StyleStateOperation.

    \sa cbegin(), cend()
*/

/*! \typedef StyleStateOperation::size_type

    This type alias represents an integer type for StyleStateOperation.
*/

/*! \fn bool StyleStateOperation::isDefault() const noexcept

    Returns true if this style state operation is the default style state operation.
*/

/*! \fn size_type StyleStateOperation::count() const noexcept

    Returns the number of style property expressions in the style state operation.
*/

//--------------------------------------------------------------------------------------------------
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------
