/***************************************************************************************************
**
** $QTCARTO_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
**
** This file is part of the QtCarto library.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
** $QTCARTO_END_LICENSE$
**
***************************************************************************************************/

/**************************************************************************************************/

#include "location_circle_data.h"

#include <QtDebug>

/**************************************************************************************************/

QcLocationCircleData::QcLocationCircleData(QObject * parent)
  : QObject(parent),
    m_bearing(),
    m_horizontal_precision()
{}

QcLocationCircleData::QcLocationCircleData(const QcLocationCircleData & other, QObject * parent)
  : QObject(parent),
    m_bearing(other.m_bearing),
    m_horizontal_precision(other.m_horizontal_precision)
{}

QcLocationCircleData::~QcLocationCircleData()
{}

QcLocationCircleData &
QcLocationCircleData::operator=(const QcLocationCircleData & other)
{
  if (this != &other) {
    m_bearing = other.m_bearing;
    m_horizontal_precision = other.m_horizontal_precision;
  }

  return *this;
}

void
QcLocationCircleData::set_bearing(double bearing)
{
  if (bearing != m_bearing) {
    m_bearing = bearing;
    emit bearingChanged();
  }
}

void
QcLocationCircleData::set_horizontal_precision(double horizontal_precision)
{
  qInfo() << horizontal_precision;
  if (horizontal_precision != m_horizontal_precision) {
    m_horizontal_precision = horizontal_precision;
    emit horizontal_precisionChanged();
  }
}

/**************************************************************************************************/

// QC_END_NAMESPACE

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/