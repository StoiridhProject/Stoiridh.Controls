Padding
====================================================================================================

.. Copyright 2016 Stòiridh Project.
.. This file is under the FDL licence, see LICENCE.FDL for details.

.. sectionauthor:: William McKIE <mckie.william@hotmail.co.uk>
.. cpp:namespace:: StoiridhControlsTemplates

----------------------------------------------------------------------------------------------------

Introduction
------------

The Padding class represents the space around the :cpp:func:`~Control::content`. By default, a
padding has its values set to ``0``.

.. code-block:: cpp

   #include <StoiridhControlsTemplates/Padding>

Syntax
------

.. cpp:class:: Padding : public QObject

   The Padding class represents the space around the :cpp:func:`~Control::content`.

.. cpp:namespace-push:: Control

Constructors & Destructor
-------------------------

   .. cpp:function:: Padding(QObject *parent = nullptr)

      Construct a padding with the given ``parent``.

Properties
----------

   .. cpp:function:: qreal left() const

      Return the *left* padding.

   .. cpp:function:: void setLeft(qreal left)

      Set the *left* padding.

   .. cpp:function:: void resetLeft()

      Reset the *left* padding to its initial value.

   .. cpp:function:: qreal top() const

      Return the *top* padding.

   .. cpp:function:: void setTop(qreal top)

      Set the *top* padding.

   .. cpp:function:: void resetTop()

      Reset the *top* padding to its initial value.

   .. cpp:function:: qreal right() const

      Return the *right* padding.

   .. cpp:function:: void setRight(qreal right)

      Set the *right* padding.

   .. cpp:function:: void resetRight()

      Reset the *right* padding to its initial value.

   .. cpp:function:: qreal bottom() const

      Return the *bottom* padding.

   .. cpp:function:: void setBottom(qreal bottom)

      Set the *bottom* padding.

   .. cpp:function:: void resetBottom()

      Reset the *bottom* padding to its initial value.

Functions
---------

   .. cpp:function:: bool isNull() const

      A null padding corresponds to the left, top, right, and bottom values are *nought*.

   .. cpp:function:: void setPaddings(qreal paddings)

      Set a global padding.

   .. cpp:function:: void setPaddings(qreal left, qreal top, qreal right, qreal bottom)

      Set a padding with the given *left*, *top*, *right*, and *bottom* values.

   .. cpp:function:: void setPaddings(const QMarginsF &paddings)

      Set a padding with the given *paddings*.

   .. cpp:function:: void setPaddings(const QRectF &paddings)

      Set a padding with the given *paddings*.

Signals
-------

   .. cpp:function:: void leftChanged(qreal left)

      Emit when the left padding changes. The *left* parameter holds the new value for the left
      padding.

   .. cpp:function:: void topChanged(qreal top)

      Emit when the top padding changes. The *top* parameter holds the new value for the top
      padding.

   .. cpp:function:: void rightChanged(qreal right)

      Emit when the right padding changes. The *right* parameter holds the new value for the right
      padding.

   .. cpp:function:: void bottomChanged(qreal bottom)

      Emit when the bottom padding changes. The *bottom* parameter holds the new value for the
      bottom padding.

.. cpp:namespace-pop::
