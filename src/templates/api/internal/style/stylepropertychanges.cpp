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
#include "stylepropertychanges.hpp"

#include "api/private/style/stylepropertychanges_p.hpp"

#include <QtQml/QQmlInfo>
#include <QtQml/QQmlProperty>
#include <QtQuick/QQuickItem>

#include <QtQml/private/qqmlcompiler_p.h>
#include <QtQml/private/qqmlmetatype_p.h>

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates {
//--------------------------------------------------------------------------------------------------


/*! \class StylePropertyChanges
    \since StoiridhControlsTemplates 1.0
    \ingroup style

    \brief The StylePropertyChanges class allows to modify the properties from the target.

    The class is used to define the property values of a \a target in a StyleState.

    Examples:

    \code
    import QtQuick 2.6
    import Stoiridh.Controls.Private 1.0

    Button {
        id: button

        background: Rectangle {
            // ...
        }

        // ...

        style: Style {
            StyleState {
                name: "Hovered"

                StylePropertyChanges {
                    target: background
                    color: "#6994d4"
                }
            }
        }
    }
    \endcode

    In the example above, when the state of the button will be 'Hovered', the \e color property
    of the background will change to '#6994d4'.
*/


/*!
    Constructs a style property changes with the given \a parent.
*/
StylePropertyChanges::StylePropertyChanges(QObject *parent)
    : StylePropertyChanges{*(new StylePropertyChangesPrivate{}), parent}
{

}

/*! \internal */
StylePropertyChanges::StylePropertyChanges(StylePropertyChangesPrivate &dd, QObject *parent)
    : QObject{dd, parent}
{

}

/*! \property StylePropertyChanges::target

    This property holds the \a target item where its properties can be modified.

    \access

    <table>
      <tr>
        <td>QQuickItem *</td>
        <td><b>target() const</b></td>
      </tr>
      <tr>
        <td>void</td>
        <td><b>setTarget(QQuickItem *target)</b></td>
      </tr>
    </table>

    \notifier_signal

    <table>
      <tr>
        <td>void</td>
        <td>targetChanged()</td>
      </tr>
    </table>
*/
QQuickItem *StylePropertyChanges::target() const
{
    Q_D(const StylePropertyChanges);
    return d->target;
}

void StylePropertyChanges::setTarget(QQuickItem *target)
{
    Q_D(StylePropertyChanges);

    if (d->target != target)
    {
        d->target = target;

        if (target && !d->decoded)
        {
            d->decode();
        }

        emit targetChanged();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////   PRIVATE API    /////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \class StoiridhControlsTemplates::StylePropertyChangesPrivate
    \internal
*/

void StylePropertyChangesPrivate::applyBindings(QQmlCompiledData *data, const Bindings &bindings)
{
    for (const auto &binding : bindings)
    {
        const auto *const unit = data->compilationUnit->data;
        auto name = unit->stringAt(binding->propertyNameIndex);
        QVariant value{};

        switch (binding->type)
        {
        case Binding::Type_Boolean:
            value = binding->valueAsBoolean();
            break;
        case Binding::Type_Number:
            value = binding->valueAsNumber();
            break;
        case Binding::Type_String:
            value = binding->valueAsString(unit);
            break;
        case Binding::Type_GroupProperty:
            decodeGroupPropertyBindings(QString{}, unit, binding);
            break;
        // StylePropertyChanges supports only one-way to source - target - binding.
        case Binding::Type_Invalid:
        case Binding::Type_Translation:
        case Binding::Type_TranslationById:
        case Binding::Type_Script:
        case Binding::Type_AttachedProperty:
        case Binding::Type_Object:
            break;
        }

        if (value.isValid())
        {
            properties << qMakePair(name, value);
        }
    }
}

void StylePropertyChangesPrivate::decodeGroupPropertyBindings(const QString &prefix,
                                                              const Unit *unit,
                                                              const Binding *binding)
{
    quint32 type{binding->type};
    QString property{prefix};
    QVariant value{};

    switch (type)
    {
    case Binding::Type_Boolean:
        value = binding->valueAsBoolean();
        break;
    case Binding::Type_Number:
        value = binding->valueAsNumber();
        break;
    case Binding::Type_String:
        value = binding->valueAsString(unit);
        break;
    // StylePropertyChanges supports only one-way to source - target -  binding.
    case Binding::Type_Invalid:
    case Binding::Type_Translation:
    case Binding::Type_TranslationById:
    case Binding::Type_Script:
    case Binding::Type_AttachedProperty:
    case Binding::Type_Object:
        break;
    }

    auto propertyName = unit->stringAt(binding->propertyNameIndex);

    if (property.isEmpty())
    {
        property = propertyName;
    }
    else
    {
        property += QLatin1Char{'.'} + propertyName;
    }

    if (type == Binding::Type_GroupProperty)
    {
        const auto *const object = unit->objectAt(binding->value.objectIndex);
        const auto *subBinding = object->bindingTable();

        for (quint32 i = 0; i < object->nBindings; ++i)
        {
            decodeGroupPropertyBindings(property, unit, subBinding++);
        }
    }

    if (value.isValid())
    {
        properties << qMakePair(property, value);
    }
}

void StylePropertyChangesPrivate::decode()
{
    Q_Q(StylePropertyChanges);

    for (const auto &property : properties)
    {
        QQmlProperty p{target, property.first, QtQml::qmlContext(q)};

        if (p.isValid())
        {
            if (!p.isWritable())
            {
                QtQml::qmlInfo(q) << QObject::tr("Cannot assign to a read-only property: ")
                                  << p.name();
            }
            else
            {
                // p.name() doesn't take into account the fully qualified attached-property name
                // like 'border.width' instead it will return only 'width' as attached-property
                // name.
                defaultProperties << qMakePair(property.first, p.read());
            }
        }
        else
        {
            auto *const metaObject = target->metaObject();
            auto *const qmlType = QQmlMetaType::qmlType(metaObject);

            auto qmlTypeName = qmlType ? qmlType->elementName()
                                       : QString::fromUtf8(metaObject->className());

            QtQml::qmlInfo(q) << QObject::tr("The target item of type ") << qmlTypeName
                              << QObject::tr(" has no property named '") << property.first << "'";
        }
    }

    decoded = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////   DOCUMENTATION    ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \signal void StylePropertyChanges::targetChanged()

    This signal is emmitted when the target changes.
*/

//--------------------------------------------------------------------------------------------------
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------
