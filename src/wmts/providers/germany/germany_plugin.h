// -*- mode: c++ -*-

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

#ifndef __GERMANY_PLUGIN_H__
#define __GERMANY_PLUGIN_H__

/**************************************************************************************************/

#include "wmts/wmts_plugin.h"
#include "wmts/wmts_network_tile_fetcher.h"

#include <QString>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

class QcGermanyPlugin;

/**************************************************************************************************/

class QcGermanyLayer : public QcWmtsPluginLayer
{
public:
  QcGermanyLayer(QcGermanyPlugin * plugin,
                 int map_id,
                 int position,
                 const QString & title,
                 const QString & name,
                 const QString & image_format);

  QUrl url(const QcTileSpec & tile_spec) const override;
};

/**************************************************************************************************/

class QcGermanyPlugin : public QcWmtsPlugin
{
  Q_OBJECT

public:
  static const QString PLUGIN_NAME;

public:
  QcGermanyPlugin();
  ~QcGermanyPlugin();
};

/**************************************************************************************************/

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __GERMANY_PLUGIN_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
