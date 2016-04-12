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
#ifndef STOIRIDHCONTROLSTEMPLATES_INTERNAL_STYLE_STYLE_HPP
#define STOIRIDHCONTROLSTEMPLATES_INTERNAL_STYLE_STYLE_HPP

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
#include <QtQml/QQmlListProperty>
#include <QtQml/qqml.h>

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates {
//--------------------------------------------------------------------------------------------------

class StylePrivate;
class StyleState;

class SCT_INTERNAL_API Style : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<StoiridhControlsTemplates::StyleState> states READ states FINAL)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_CLASSINFO("DefaultProperty", "states")

public:
    explicit Style(QObject *parent = nullptr);
    ~Style() override = default;

    QQmlListProperty<StoiridhControlsTemplates::StyleState> states();

    QString name() const;
    void setName(const QString &name);

signals:
    void nameChanged();

protected:
    Style(StylePrivate &dd, QObject *parent);

private:
    Q_DISABLE_COPY(Style)
    Q_DECLARE_PRIVATE(Style)
};

//--------------------------------------------------------------------------------------------------
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------
QML_DECLARE_TYPE(StoiridhControlsTemplates::Style)
//--------------------------------------------------------------------------------------------------

#endif // STOIRIDHCONTROLSTEMPLATES_INTERNAL_STYLE_STYLE_HPP
