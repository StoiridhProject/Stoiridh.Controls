Control
====================================================================================================

.. Copyright 2016 Stòiridh Project.
.. This file is under the FDL licence, see LICENCE.FDL for details.

.. sectionauthor:: William McKIE <mckie.william@hotmail.co.uk>
.. cpp:namespace:: StoiridhControlsTemplates

----------------------------------------------------------------------------------------------------

Introduction
------------

The Control class represents the base class for all UI controls. A control may have a
:cpp:func:`~Control::background` and :cpp:func:`~Control::content` in order to customise the
appearance of the control.

.. code-block:: cpp

   #include <StoiridhControlsTemplates/Control>

Syntax
------

.. cpp:class:: Control : public QQuickItem

   The Control class provides a base class for all UI controls.

.. cpp:namespace-push:: Control

Constructors & Destructor
-------------------------

   .. cpp:function:: Control(QQuickItem *parent = nullptr)

      Construct a control with the given ``parent``.

   .. cpp:function:: ~Control()

      Destroy *this* control.

Properties
----------

   .. cpp:function:: qreal availableWidth() const

      Return the available width for the content item.

   .. cpp:function:: qreal availableHeight() const

      Return the available height for the content item.

   .. cpp:function:: qreal paddings() const

      Return the global paddings of the control.

   .. cpp:function:: void setPaddings(qreal paddings)

      Set the global paddings for the control.

   .. cpp:function:: void resetPaddings()

      Reset the global paddings to *nought*.

   .. cpp:function:: Padding *padding() const

      Return the padding of the control.

   .. cpp:function:: QQuickItem *background() const

      Return the background item of the control.

   .. cpp:function:: void setBackground(QQuickItem *background)

      Set the background item of the control.

   .. cpp:function:: QQuickItem *content() const

      Return the content item of the control.

   .. cpp:function:: void setContent(QQuickItem *content)

      Set the content item of the control.

Signals
-------

   .. cpp:function:: void paddingsChanged()

      Emit when the :cpp:func:`~paddings` property changes.

   .. cpp:function:: void backgroundChanged()

      Emit when the :cpp:func:`~background` property changes.

   .. cpp:function:: void contentChanged()

      Emit when the :cpp:func:`~content` property changes.

.. cpp:namespace-pop::
