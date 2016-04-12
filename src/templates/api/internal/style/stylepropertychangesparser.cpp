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
#include "stylepropertychangesparser.hpp"

#include "api/private/style/stylepropertychanges_p.hpp"

#include <QtCore/QObject>

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates {
//--------------------------------------------------------------------------------------------------


/*! \class StylePropertyChangesParser
    \since StoiridhControlsTemplates 1.0
    \ingroup style

    \brief The StylePropertyChangesParser class is a QML custom parser for the StylePropertyChanges
           class.

    The class parses a StylePropertyChanges QML type.

    During parsing of a StylePropertyChanges QML type, the StylePropertyChangesParser class verifies
    the bindings (verifyBindings()) in order to check if the property values are well-defined.

    If the property values are well-defined, then a call to applyBindings() will apply the bindings
    on the StylePropertyChanges in order to modify its property values of \a target, otherwise, an
    error will be sent to notice the user. The StylePropertyChanges' status will be
    QQmlComponent::Status::Error.

    \sa StylePropertyChanges
*/


/*!
    Verifies the \a bindings of the property values.

    \note Only basic types (eg., boolean, number, and string) and group property types are allowed
          as a valid binding.
*/
void StylePropertyChangesParser::verifyBindings(const Unit *unit,
                                                const QList<const Binding *> &bindings)
{
    for (const auto *binding : bindings)
    {
        if (binding)
        {
            quint32 type{binding->type};

            switch (type)
            {
            case Binding::Type_Boolean:
            case Binding::Type_Number:
            case Binding::Type_String:
                break;
            case Binding::Type_Object:
                error(unit->objectAt(binding->value.objectIndex), type);
                break;
            case Binding::Type_Invalid:
            case Binding::Type_Translation:
            case Binding::Type_TranslationById:
            case Binding::Type_Script:
            case Binding::Type_AttachedProperty:
                error(binding, type);
                break;
            case Binding::Type_GroupProperty:
                verifyGroupPropertyBindings(unit, binding);
                break;
            default:
                error(binding, type);
            }
        }
    }
}

/*!
    Applies the \a bindings to the \a object.
*/
void StylePropertyChangesParser::applyBindings(QObject *object, QQmlCompiledData *data,
                                               const QList<const QV4::CompiledData::Binding *> &bindings)
{
    auto *const stylePropertyChanges = qobject_cast<StylePropertyChanges *>(object);

    if (stylePropertyChanges)
    {
        auto *const d = StylePropertyChangesPrivate::get(stylePropertyChanges);
        d->applyBindings(data, bindings);
    }
}

/*!
    Returns an appropriate error message according to the \a type of the error.
*/
QString StylePropertyChangesParser::valueTypeError(Binding::ValueType type)
{
    switch (type)
    {
    case Binding::Type_Invalid:
        return StylePropertyChanges::tr("StylePropertyChanges has an invalid binding.");
    case Binding::Type_Boolean:
        return StylePropertyChanges::tr("StylePropertyChanges does not support boolean binding.");
    case Binding::Type_Number:
        return StylePropertyChanges::tr("StylePropertyChanges does not support number binding.");
    case Binding::Type_String:
        return StylePropertyChanges::tr("StylePropertyChanges does not support string binding.");
    case Binding::Type_Translation:
        return StylePropertyChanges::tr("StylePropertyChanges does not support translation "
                                        "binding.");
    case Binding::Type_TranslationById:
        return StylePropertyChanges::tr("StylePropertyChanges does not support translation by id "
                                        "binding.");
    case Binding::Type_Script:
        return StylePropertyChanges::tr("StylePropertyChanges does not support script binding.");
    case Binding::Type_Object:
        return StylePropertyChanges::tr("StylePropertyChanges does not support object binding.");
    case Binding::Type_AttachedProperty:
        return StylePropertyChanges::tr("StylePropertyChanges does not support attached property "
                                        "binding.");
    case Binding::Type_GroupProperty:
        return StylePropertyChanges::tr("StylePropertyChanges does not support group property "
                                        "binding.");
    }

    return StylePropertyChanges::tr("StylePropertyChanges has an unknown binding.");
}

/*!
    Verifies a group property \a binding.

    \note Only basic types (eg., boolean, number, and string) and group property are allowed.
*/
void StylePropertyChangesParser::verifyGroupPropertyBindings(const Unit *unit,
                                                             const Binding *binding)
{
    quint32 type{binding->type};

    switch (type)
    {
    case Binding::Type_Boolean:
    case Binding::Type_Number:
    case Binding::Type_String:
        break;
    case Binding::Type_Invalid:
    case Binding::Type_Translation:
    case Binding::Type_TranslationById:
    case Binding::Type_Script:
    case Binding::Type_AttachedProperty:
        error(binding, type);
        break;
    case Binding::Type_Object:
        error(unit->objectAt(binding->value.objectIndex), type);
        break;
    }

    if (type == Binding::Type_GroupProperty)
    {
        const auto *const object = unit->objectAt(binding->value.objectIndex);
        const auto *subBinding = object->bindingTable();

        for (quint32 i = 0; i < object->nBindings; ++i)
        {
            verifyGroupPropertyBindings(unit, subBinding++);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////   DOCUMENTATION    ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \fn void StylePropertyChangesParser::error(const Class *object, quint32 type)

    Sends a binding \a type error to an \a object.

    \tparam Class must be either a \b QV4::CompiledData::Binding (QtQml private API) class or a
            \b QV4::CompiledData::Object (QtQml private API) object.
*/

//--------------------------------------------------------------------------------------------------
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------
