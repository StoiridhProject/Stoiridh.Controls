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

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates {
//--------------------------------------------------------------------------------------------------

template<typename T>
Style *StyleFactory::create(const Control *control)
{
    static_assert(std::is_base_of<AbstractStyleDispatcher, T>::value,
                  "T is not a base of AbstractStyleDispatcher");
    ExceptionHandler::checkNullPointer(control,
                                       QStringLiteral("control"),
                                       QStringLiteral("const Control *"));

    QScopedPointer<StyleFactoryHelper> helper{new StyleFactoryHelper{control}};
    AbstractStyleDispatcher *dispatcher{nullptr};

    const auto id = helper->controlId();

    // a style dispatcher is already registered for a control type.
    if (m_dispatchers.contains(id))
    {
        dispatcher = m_dispatchers.value(id);

        helper->setStyleDispatcher(dispatcher);

        if (!helper->mapping())
        {
            QString message = QString::fromUtf8("StyleFactory: %1\n%2\n    %3")
                    .arg(QObject::tr("An error has occurred during mapping styles."))
                    .arg(QObject::tr("Errors:"))
                    .arg(helper->mappingErrors());

            QtQml::qmlInfo(control) << message;
        }
    }
    else
    {
        helper->createStyleStatesOperations();

        dispatcher = new T{helper->style()};
        m_dispatchers[id] = dispatcher;
    }

    return dispatcher->style();
}

//--------------------------------------------------------------------------------------------------
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------
