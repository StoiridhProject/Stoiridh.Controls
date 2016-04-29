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
#ifndef STOIRIDHCONTROLSTEMPLATES_INTERNAL_STYLE_STYLEPROPERTYCHANGESPARSER_HPP
#define STOIRIDHCONTROLSTEMPLATES_INTERNAL_STYLE_STYLEPROPERTYCHANGESPARSER_HPP

////////////////////////////////////////////////////////////////////////////////////////////////////
//  --------------------------------------------------------------------------------------------  //
//  /!\                                     W A R N I N G                                    /!\  //
//  --------------------------------------------------------------------------------------------  //
//                                                                                                //
//  This internal header file is not part of StoiridhControlsTemplates API. It exists purely as   //
//  an internal use and must not be used in external project(s).                                  //
//                                                                                                //
//  The content of this file may change from version to version without notice, or even be        //
//  removed.                                                                                      //
//                                                                                                //
//  You are forewarned!                                                                           //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "api/internal/global.hpp"

#include <QtCore/QList>
#include <QtCore/QString>

#include <QtQml/private/qqmlcustomparser_p.h>

#include <type_traits>

QT_BEGIN_NAMESPACE
class QObject;
QT_END_NAMESPACE

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates {
//--------------------------------------------------------------------------------------------------

class SCT_INTERNAL_API StylePropertyChangesParser final : public QQmlCustomParser
{
    using Unit    = QV4::CompiledData::Unit;
    using Binding = QV4::CompiledData::Binding;
    using Object  = QV4::CompiledData::Object;

public:
    explicit StylePropertyChangesParser() = default;
    StylePropertyChangesParser(const StylePropertyChangesParser &rhs) = delete;
    StylePropertyChangesParser(StylePropertyChangesParser &&rhs) = delete;
    ~StylePropertyChangesParser() override = default;

    void verifyBindings(const Unit *unit, const QList<const Binding *> &bindings) override;
    void applyBindings(QObject *object, QQmlCompiledData *data,
                       const QList<const Binding *> &bindings) override;

    StylePropertyChangesParser &operator=(const StylePropertyChangesParser &rhs) = delete;
    StylePropertyChangesParser &operator=(StylePropertyChangesParser &&rhs) = delete;

protected:
    template<typename Class>
    void error(const Class *object, quint32 type);

private:
    static QString valueTypeError(Binding::ValueType type);

    void verifyGroupPropertyBindings(const Unit *unit, const Binding *binding);
};

//--------------------------------------------------------------------------------------------------

template<typename Class>
void StylePropertyChangesParser::error(const Class *object, quint32 type)
{
    static_assert(std::is_same<Class, Binding>::value || std::is_same<Class, Object>::value,
                  "T must be either a Binding type or an Object type");

    auto valueType = static_cast<Binding::ValueType>(type);
    QQmlCustomParser::error(object, valueTypeError(valueType));
}

//--------------------------------------------------------------------------------------------------
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------

#endif // STOIRIDHCONTROLSTEMPLATES_INTERNAL_STYLE_STYLEPROPERTYCHANGESPARSER_HPP
