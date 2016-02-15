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
#include "control.hpp"

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates {
//--------------------------------------------------------------------------------------------------


/*! \class StoiridhControlsTemplates::Control
    \inherits QQuickItem
    \inmodule StoiridhControlsTemplates
    \ingroup stoiridh_controls_templates
    \since StoiridhControlsTemplates 1.0

    \brief The Control class provides a base class for UI controls.
*/


/*!
    Constructs a Control with an optional \a parent as parent.
*/
Control::Control(QQuickItem *parent)
    : QQuickItem{parent}
    , m_padding{new Padding{this}}
{

}

/*! \property StoiridhControlsTemplates::Control::availableWidth
    \readonly

    This property holds the available width for the content item.
*/
qreal Control::availableWidth() const
{
    return qMax(0.0, width() - m_padding->left() - m_padding->right());
}

/*! \property StoiridhControlsTemplates::Control::availableHeight
    \readonly

    This property holds the available height for the content item.
*/
qreal Control::availableHeight() const
{
    return qMax(0.0, height() - m_padding->top() - m_padding->bottom());
}

/*! \property StoiridhControlsTemplates::Control::paddings

    This property holds the global paddings of the control.

    \sa {Control::}{padding()}
*/
qreal Control::paddings() const
{
    return m_paddings;
}

void Control::setPaddings(qreal paddings)
{
    if (!qFuzzyCompare(m_paddings, paddings))
    {
        m_paddings = paddings;

        // adjust the padding of the grouped property
        m_padding->setPaddings(paddings);

        if (isComponentComplete())
            calculateContentGeometry();

        emit paddingsChanged(paddings);
    }
}

void Control::resetPaddings()
{
    setPaddings(0.0);
}

/*! \property StoiridhControlsTemplates::Control::padding
    \readonly

    This property holds the padding of the control.

    \sa {Control::}{paddings()}
*/
Padding *Control::padding() const
{
    return m_padding;
}

/*! \property StoiridhControlsTemplates::Control::background

    This property holds the background of the control.
*/
QQuickItem *Control::background() const
{
    return m_background;
}

void Control::setBackground(QQuickItem *background)
{
    if (m_background != background)
    {
        m_background = background;

        if (m_background)
        {
            m_background->setParentItem(this);
            m_background->setZ(-1.0);

            if (isComponentComplete())
                calculateBackgroundGeometry();
        }

        emit backgroundChanged(background);
    }
}

/*! \property StoiridhControlsTemplates::Control::content

    This property holds the content of the control.
*/
QQuickItem *Control::content() const
{
    return m_content;
}

void Control::setContent(QQuickItem *content)
{
    if (m_content != content)
    {
        m_content = content;

        if (m_content)
        {
            m_content->setParentItem(this);

            if (isComponentComplete())
                calculateContentGeometry();
        }

        emit contentChanged(content);
    }
}

/*!
    \reimp
*/
void Control::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
    calculateBackgroundGeometry();
    calculateContentGeometry();
}

void Control::calculateBackgroundGeometry()
{
    if (!m_background)
        return;

    m_background->setX(0.0);
    m_background->setY(0.0);

    if (widthValid())
    {
        m_background->setWidth(width());
    }
    else
    {
        const auto width = qMax(m_background->implicitWidth(), implicitWidth());
        m_background->setWidth(width);
        setImplicitWidth(width);
    }

    if (heightValid())
    {
        m_background->setHeight(height());
    }
    else
    {
        const auto height = qMax(m_background->implicitHeight(), this->implicitHeight());
        m_background->setHeight(height);
        setImplicitHeight(height);
    }
}

void Control::calculateContentGeometry()
{
    if (!m_content)
        return;

    m_content->setX(m_padding->left());
    m_content->setY(m_padding->top());

    const auto ciw = m_content->implicitWidth();

    if (widthValid() || qFuzzyIsNull(ciw))
    {
        m_content->setWidth((ciw > 0.0 && ciw < availableWidth()) ? ciw : availableWidth());
    }
    else
    {
        // adjust the width of the control so as to keep the implicit width of the content item.
        if (ciw >= availableWidth())
        {
            const auto width = ciw + m_padding->left() + m_padding->right();
            setWidth(width);
        }
    }

    // identical as width but for height.
    const auto cih = m_content->implicitHeight();

    if (heightValid() || qFuzzyIsNull(cih))
    {
        m_content->setHeight((cih > 0.0 && cih < availableHeight()) ? cih : availableHeight());
    }
    else
    {
        // adjust the height of the control so as to keep the implicit height of the content item.
        if (cih >= availableHeight())
        {
            const auto height = cih + m_padding->top() + m_padding->bottom();
            setHeight(height);
        }
    }
}

//--------------------------------------------------------------------------------------------------
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------
