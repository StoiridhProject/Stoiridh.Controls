.. StoiridhControls documentation master file, created by
   sphinx-quickstart on Tue Jun 28 15:06:44 2016.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

.. Copyright 2016 Stòiridh Project.
.. This file is under the FDL licence, see LICENCE.FDL for details.

|project-version| documentation
===============================

Welcome! This is the documentation for |project-version|, last updated |today|.

Introduction
------------

The |project| module provides a set of UI controls for creating user interfaces in your
QML application.

Getting Started
---------------

The QML types can be imported into your application using the following import statement in your
``.qml`` file.

.. code-block:: qml

   import Stoiridh.Controls 1.0

To use the Template classes from the C++ API, add the following ``#include`` directive into your C++
files.

.. code-block:: cpp

   #include <StoiridhControlsTemplates>

All Classes are declared under the ``StoiridhControlsTemplates`` namespace.

**Contents:**

.. toctree::
   :maxdepth: 1

   api

Indices and tables
==================

* :ref:`genindex`
* :ref:`search`
