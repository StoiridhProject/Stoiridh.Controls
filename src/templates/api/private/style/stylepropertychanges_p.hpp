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
#ifndef STOIRIDHCONTROLSTEMPLATES_STYLE_STYLEPROPERTYCHANGES_P_HPP
#define STOIRIDHCONTROLSTEMPLATES_STYLE_STYLEPROPERTYCHANGES_P_HPP

////////////////////////////////////////////////////////////////////////////////////////////////////
//  --------------------------------------------------------------------------------------------  //
//  /!\                                     W A R N I N G                                    /!\  //
//  --------------------------------------------------------------------------------------------  //
//                                                                                                //
//  This private header file is not part of StoiridhControlsTemplates API. It exists purely as    //
//  an implementation detail for the internal class, StylePropertyChanges.                        //
//                                                                                                //
//  The content of this file may change from version to version without notice, or even be        //
//  removed.                                                                                      //
//                                                                                                //
//  You are forewarned!                                                                           //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "api/internal/style/stylepropertychanges.hpp"

#include <QtCore/QPointer>
#include <QtCore/QVector>
#include <QtQuick/QQuickItem>

#include <QtCore/private/qobject_p.h>
#include <QtQml/private/qv4compileddata_p.h>

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates {
//--------------------------------------------------------------------------------------------------

class StylePropertyChangesPrivate final : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(StylePropertyChanges)
    using Unit     = QV4::CompiledData::Unit;
    using Binding  = QV4::CompiledData::Binding;
    using Bindings = QList<const Binding *>;
    using Property = QPair<QString, QVariant>;

public:
    StylePropertyChangesPrivate() = default;
    ~StylePropertyChangesPrivate() override = default;

    static StylePropertyChangesPrivate *get(StylePropertyChanges *changes);
    static const StylePropertyChangesPrivate *get(const StylePropertyChanges *changes);

    void applyBindings(QQmlCompiledData *data, const Bindings &bindings);
    void decodeGroupPropertyBindings(const QString &prefix, const Unit *unit,
                                     const Binding *binding);
    void decode();

    // members
    QPointer<QQuickItem> target{};
    QVector<Property> properties{};
    QVector<Property> defaultProperties{};
    bool decoded{false};
};

//--------------------------------------------------------------------------------------------------

/*! \internal */
inline
StylePropertyChangesPrivate *StylePropertyChangesPrivate::get(StylePropertyChanges *changes)
{
    return changes->d_func();
}

/*! \internal */
inline const
StylePropertyChangesPrivate *StylePropertyChangesPrivate::get(const StylePropertyChanges *changes)
{
    return changes->d_func();
}

//--------------------------------------------------------------------------------------------------
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------

#endif // STOIRIDHCONTROLSTEMPLATES_STYLE_STYLEPROPERTYCHANGES_P_HPP
