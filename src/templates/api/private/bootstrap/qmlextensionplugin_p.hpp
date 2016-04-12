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
#ifndef STOIRIDHCONTROLSTEMPLATES_BOOTSTRAP_QMLEXTENSIONPLUGIN_P_HPP
#define STOIRIDHCONTROLSTEMPLATES_BOOTSTRAP_QMLEXTENSIONPLUGIN_P_HPP

////////////////////////////////////////////////////////////////////////////////////////////////////
//  --------------------------------------------------------------------------------------------  //
//  /!\                                     W A R N I N G                                    /!\  //
//  --------------------------------------------------------------------------------------------  //
//                                                                                                //
//  This private header file is not part of StoiridhControlsTemplates API. It exists purely as    //
//  an entry point to expose some classes from the StoiridhControlsTemplates internal API into    //
//  QML.                                                                                          //
//                                                                                                //
//  The content of this file may change from version to version without notice, or even be        //
//  removed.                                                                                      //
//                                                                                                //
//  You are forewarned!                                                                           //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <StoiridhControlsTemplates/Public/global.hpp>

QT_BEGIN_NAMESPACE
class QQmlEngine;
QT_END_NAMESPACE

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates { namespace Bootstrap {
//--------------------------------------------------------------------------------------------------

class STOIRIDH_CONTROLS_TEMPLATES_API QmlExtensionPlugin final
{
public:
    static void init(const QQmlEngine *engine);
    static void qmlRegisterInternalTypes(const char *uri);
};

//--------------------------------------------------------------------------------------------------
} // namespace Bootstrap
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------

#endif // STOIRIDHCONTROLSTEMPLATES_BOOTSTRAP_QMLEXTENSIONPLUGIN_P_HPP
