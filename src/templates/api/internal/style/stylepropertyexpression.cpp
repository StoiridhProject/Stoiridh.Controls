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
#include "stylepropertyexpression.hpp"

#include "control.hpp"
#include "core/exception/exceptionhandler.hpp"

#include <QtQml/QQmlProperty>
#include <QtQuick/QQuickItem>

#include <stdexcept>

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates {
//--------------------------------------------------------------------------------------------------

static const
QString &propertyEmptyMessage = QObject::tr("A property can't be an empty string.");


/*! \class StylePropertyExpression
    \since StoiridhControlsTemplates 1.0
    \ingroup style

    \brief The StylePropertyExpression class represents an expression for a StyleStateOperation.
*/


/*!
    Constructs a style property expression by copying \a rhs to \a this StylePropertyExpression
    instance.
*/
StylePropertyExpression::StylePropertyExpression(const StylePropertyExpression &rhs)
    : m_mappings(rhs.m_mappings)
    , m_properties(rhs.m_properties)
{

}

/*!
    Constructs a style property expression by moving \a rhs to \a this StylePropertyExpression
    instance.
*/
StylePropertyExpression::StylePropertyExpression(StylePropertyExpression &&rhs) noexcept
    : m_mappings(std::move(rhs.m_mappings))
    , m_properties(std::move(rhs.m_properties))
{
    rhs.m_mappings.clear();
    rhs.m_properties.clear();
}

/*!
    Returns the number of \e controls and \e properties in the style property expression.
*/
QPair<int, int> StylePropertyExpression::count() const noexcept
{
    return qMakePair(m_mappings.count(), m_properties.count());
}

/*!
    Returns true, if the style property expression contains an occurrence of \a control, otherwise,
    false.
*/
bool StylePropertyExpression::containsControl(const Control *control) const noexcept
{
    return m_mappings.contains(control);
}

/*!
    Returns true, if the style property expression contains an occurrence of
    (\a control, \a target)-pair, otherwise, false.
*/
bool StylePropertyExpression::containsTarget(const Control *control, const QQuickItem *target) const noexcept
{
    if (!(control && target))
        return false;

    return (*m_mappings.constFind(control)) == target;
}

/*!
    Inserts (\a control, \a target)-pair at the end of the style property expression.

    \throw NullPointerException if either \a control or \a target is null.
*/
void StylePropertyExpression::addMapping(const Control *control, QQuickItem *target)
{
    ExceptionHandler::checkNullPointer(control,
                                       QStringLiteral("control"),
                                       QStringLiteral("const Control *"));
    ExceptionHandler::checkNullPointer(target,
                                       QStringLiteral("target"),
                                       QStringLiteral("QQuickItem *"));

    m_mappings.insert(control, target);
}

/*!
    Removes \a control from the style property expression.

    \return true if \a control is removed from the style property expression, otherwise, false.
*/
bool StylePropertyExpression::removeMapping(const Control *control) noexcept
{
    if (!control)
        return false;

    return (m_mappings.remove(control) > 0);
}

/*!
    Returns true, if the style property expression contains an occurrence of \a name property,
    otherwise, false.
*/
bool StylePropertyExpression::containsProperty(const QString &name) const noexcept
{
    return m_properties.contains(name);
}

/*!
    Inserts a (\a name, \a value)-pair property at the end of the style property expression.

    \throw std::invalid_argument if \a name is an empty string.

    \sa addProperties()
*/
void StylePropertyExpression::addProperty(const QString &name, const QVariant &value)
{
    if (name.isEmpty())
    {
        throw std::invalid_argument{propertyEmptyMessage.toStdString()};
    }

    m_properties.insert(name, value);
}

/*! \overload

    \throw std::invalid_argument if \a property.first is an empty string.

    \sa addProperties()
*/
void StylePropertyExpression::addProperty(const QPair<QString, QVariant> &property)
{
    addProperty(property.first, property.second);
}

/*!
    Inserts a vector of (\a name, \a value)-pair property at the end of the style property
    expression.

    \throw std::invalid_argument if the first of <tt>properties[0..$].first</tt> is an empty string.

    \sa addProperty()
*/
void StylePropertyExpression::addProperties(const QVector<QPair<QString, QVariant>> &properties) noexcept
{
    for (const auto &property : properties)
    {
        if (!containsProperty(property.first))
        {
            addProperty(property);
        }
    }
}

/*!
    Removes a \a property from the style property expression.

    \return true if the control has successfully removed from the style property expression,
            otherwise, false.
*/
bool StylePropertyExpression::removeProperty(const QString &name) noexcept
{
    return (m_properties.remove(name) > 0);
}

/*!
    Applies the style property expression to \a control.

    \return true, if the style property expression is successfully applied to \a control, otherwise,
            false.

    \pre \a control must be in the style property expression.

    \throw NullPointerException if \a control is null.
*/
bool StylePropertyExpression::apply(const Control *control)
{
    ExceptionHandler::checkNullPointer(control,
                                       QStringLiteral("control"),
                                       QStringLiteral("const Control *"));

    auto citMappings = m_mappings.constFind(control);

    if (citMappings == m_mappings.end())
        return false;

    for (auto cit = m_properties.cbegin(); cit != m_properties.cend(); ++cit)
    {
        QQmlProperty property{citMappings.value(), cit.key(), QtQml::qmlContext(control)};

        if (property.isValid() && property.isWritable())
        {
            property.write(cit.value());
        }
        else
        {
            return false;
        }
    }

    return true;
}

/*!
    Copies \a rhs to \a this StylePropertyExpression instance and returns a reference to \a this
    style property expression.
*/
StylePropertyExpression &StylePropertyExpression::operator=(const StylePropertyExpression &rhs)
{
    if (this != &rhs)
    {
        m_mappings = rhs.m_mappings;
        m_properties = rhs.m_properties;
    }

    return (*this);
}

/*!
    Moves \a rhs to \a this StylePropertyExpression instance and returns a reference to \a this
    style property expression.
*/
StylePropertyExpression &StylePropertyExpression::operator=(StylePropertyExpression &&rhs) noexcept
{
    m_mappings = std::move(rhs.m_mappings);
    m_properties = std::move(rhs.m_properties);

    rhs.m_mappings.clear();
    rhs.m_properties.clear();

    return (*this);
}

/*!
    Returns true if the style property expression is equal to \a rhs style property expression,
    otherwise, false.
*/
bool StylePropertyExpression::operator==(const StylePropertyExpression &rhs) const
{
    return (m_mappings == rhs.m_mappings && m_properties == rhs.m_properties);
}

/*!
    Returns true if the style property expression is not equal to \a rhs style property expression,
    otherwise, false.
*/
bool StylePropertyExpression::operator!=(const StylePropertyExpression &rhs) const
{
    return !(*this == rhs);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////   DOCUMENTATION    ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \fn StylePropertyExpression::StylePropertyExpression()

    Constructs a style property expression.
*/

//--------------------------------------------------------------------------------------------------
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------
