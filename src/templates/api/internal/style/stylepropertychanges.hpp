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
#ifndef STOIRIDHCONTROLSTEMPLATES_INTERNAL_STYLE_STYLEPROPERTYCHANGES_HPP
#define STOIRIDHCONTROLSTEMPLATES_INTERNAL_STYLE_STYLEPROPERTYCHANGES_HPP

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

#include <QtCore/QObject>
#include <QtQml/qqml.h>

QT_BEGIN_NAMESPACE
class QQuickItem;
QT_END_NAMESPACE

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates {
//--------------------------------------------------------------------------------------------------

class StylePropertyChangesPrivate;

class SCT_INTERNAL_API StylePropertyChanges : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem *target READ target WRITE setTarget NOTIFY targetChanged FINAL)

public:
    explicit StylePropertyChanges(QObject *parent = nullptr);
    ~StylePropertyChanges() override = default;

    QQuickItem *target() const;
    void setTarget(QQuickItem *target);

signals:
    void targetChanged();

protected:
    StylePropertyChanges(StylePropertyChangesPrivate &dd, QObject *parent);

private:
    Q_DISABLE_COPY(StylePropertyChanges)
    Q_DECLARE_PRIVATE(StylePropertyChanges)
};

//--------------------------------------------------------------------------------------------------
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------
QML_DECLARE_TYPE(StoiridhControlsTemplates::StylePropertyChanges)
//--------------------------------------------------------------------------------------------------

#endif // STOIRIDHCONTROLSTEMPLATES_INTERNAL_STYLE_STYLEPROPERTYCHANGES_HPP
