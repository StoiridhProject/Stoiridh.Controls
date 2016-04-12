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
#include "qmlextensionplugin_p.hpp"

#include "api/internal/style/style.hpp"
#include "api/internal/style/stylefactory.hpp"
#include "api/internal/style/stylepropertychanges.hpp"
#include "api/internal/style/stylepropertychangesparser.hpp"
#include "api/internal/style/stylestate.hpp"

#include <QtQml/QQmlEngine>
#include <QtQml/qqml.h>

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates { namespace Bootstrap {
//--------------------------------------------------------------------------------------------------


/*! \class QmlExtensionPlugin
    \since StoiridhControlsTemplates 1.0
    \ingroup bootstrap
    \ingroup plugin

    \brief The QmlExtensionPlugin class is an entry point to register QML types.

    The QmlExtensionPlugin class registers and exposes classes from the internal API to QML.
*/


/*!
    Initialises the QML extension plugin.
*/
void QmlExtensionPlugin::init(const QQmlEngine *engine)
{
    // destroys all style dispatchers from the style factory only when the QML engine is destroyed.
    QQmlEngine::connect(engine, &QQmlEngine::destroyed, []()
    {
        StyleFactory::destroy();
    });
}

/*!
    Registers and exposes classes from the internal API in order to be use in a QML application.
*/
void QmlExtensionPlugin::qmlRegisterInternalTypes(const char *uri)
{
    namespace SCT = StoiridhControlsTemplates;

    // style
    qmlRegisterType<SCT::Style>(uri, 1, 0, "Style");
    qmlRegisterType<SCT::StyleState>(uri, 1, 0, "StyleState");
    qmlRegisterCustomType<SCT::StylePropertyChanges>(uri, 1, 0, "StylePropertyChanges",
                                                     new SCT::StylePropertyChangesParser{});
}

//--------------------------------------------------------------------------------------------------
} // namespace Bootstrap
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------
