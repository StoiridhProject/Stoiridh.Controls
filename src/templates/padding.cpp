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
#include "padding.hpp"

#include <QMarginsF>
#include <QRectF>

#ifndef QT_NO_DEBUG_STREAM
#include <QtDebug>
#endif

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates {
//--------------------------------------------------------------------------------------------------


/*! \class StoiridhControlsTemplates::Padding
    \inherits QtObject
    \inmodule StoiridhControlsTemplates
    \ingroup controls
    \ingroup templates
    \since StoiridhControlsTemplates 1.0

    \brief The Padding class represents the space around content.
*/


/*!
    Constructs a padding with the given \a parent.
 */
Padding::Padding(QObject *parent)
    : QObject{parent}
{

}

/*!
    Returns \c true if the padding is null, otherwise returns \c false.

    A null padding corresponds to the left, top, right, and bottom values are set to 0.
*/
bool Padding::isNull() const
{
    return qFuzzyIsNull(m_left) && qFuzzyIsNull(m_top)
            && qFuzzyIsNull(m_right) && qFuzzyIsNull(m_bottom);
}

/*! \property StoiridhControlsTemplates::Padding::left

    This property holds the left padding.
*/
qreal Padding::left() const
{
    return m_left;
}

void Padding::setLeft(qreal left)
{
    if (!qFuzzyCompare(m_left, left))
    {
        m_left = left;
        emit leftChanged(left);
    }
}

void Padding::resetLeft()
{
    setLeft(0.0);
}

/*! \property StoiridhControlsTemplates::Padding::top

    This property holds the top padding.
*/
qreal Padding::top() const
{
    return m_top;
}

void Padding::setTop(qreal top)
{
    if (!qFuzzyCompare(m_top, top))
    {
        m_top = top;
        emit topChanged(top);
    }
}

void Padding::resetTop()
{
    setTop(0.0);
}

/*! \property StoiridhControlsTemplates::Padding::right

    This property holds the right padding.
*/
qreal Padding::right() const
{
    return m_right;
}

void Padding::setRight(qreal right)
{
    if (!qFuzzyCompare(m_right, right))
    {
        m_right = right;
        emit rightChanged(right);
    }
}

void Padding::resetRight()
{
    setRight(0.0);
}

/*! \property StoiridhControlsTemplates::Padding::bottom

    This property holds the bottom padding.
*/
qreal Padding::bottom() const
{
    return m_bottom;
}

void Padding::setBottom(qreal bottom)
{
    if (!qFuzzyCompare(m_bottom, bottom))
    {
        m_bottom = bottom;
        emit bottomChanged(bottom);
    }
}

void Padding::resetBottom()
{
    setBottom(0.0);
}

/*!
    Sets the global \a paddings.

    \sa {Padding::}{left}, {Padding::}{top}, {Padding::}{right}, {Padding::}{bottom}
*/
void Padding::setPaddings(qreal paddings)
{
    setPaddings(paddings, paddings, paddings, paddings);
}

/*!
    Sets the \a left, \a top, \a right, and \a bottom padding.

    \sa {Padding::}{left}, {Padding::}{top}, {Padding::}{right}, {Padding::}{bottom}
*/
void Padding::setPaddings(qreal left, qreal top, qreal right, qreal bottom)
{
    setLeft(left);
    setTop(top);
    setRight(right);
    setBottom(bottom);
}

/*!
    Sets the padding.

    \sa {Padding::}{left}, {Padding::}{top}, {Padding::}{right}, {Padding::}{bottom}
*/
void Padding::setPaddings(const QMarginsF &paddings)
{
    setPaddings(paddings.left(), paddings.top(), paddings.right(), paddings.bottom());
}

/*!
    Sets the padding.

    \sa {Padding::}{left}, {Padding::}{top}, {Padding::}{right}, {Padding::}{bottom}
*/
void Padding::setPaddings(const QRectF &paddings)
{
    setPaddings(paddings.x(), paddings.y(), paddings.width(), paddings.height());
}

#ifndef QT_NO_DEBUG_STREAM

QDebug operator<<(QDebug debug, const Padding &padding)
{
    QDebugStateSaver saver{debug};
    debug.nospace() << "Padding("
                    << padding.left()   << ", "
                    << padding.top()    << ", "
                    << padding.right()  << ", "
                    << padding.bottom() << ")";

    return debug;
}

QDebug operator<<(QDebug debug, const Padding *padding)
{
    QDebugStateSaver saver{debug};
    debug.nospace() << "Padding(";

    if (padding)
    {
        debug << padding->left()  << ", "
              << padding->top()   << ", "
              << padding->right() << ", "
              << padding->bottom();
    }

    debug << ")";

    return debug;
}

#endif

//--------------------------------------------------------------------------------------------------
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------
