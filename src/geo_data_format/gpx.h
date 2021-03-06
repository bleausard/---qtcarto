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

#ifndef __QcGpx_H__
#define __QcGpx_H__

/**************************************************************************************************/

#include <QDateTime>
#include <QList>
#include <QString>
#include <QXmlStreamWriter>

#include "math/interval.h"
#include "route.h"
#include "waypoint.h"
#include "xml_reader.h"

/**************************************************************************************************/

// http://www.topografix.com/GPX/1/1

/*
 * <gpx
 * version="1.1 [1]"
 * creator="xsd:string [1]">
 * <metadata>
 *     <name> xsd:string </name> [0..1]
 *     <desc> xsd:string </desc> [0..1]
 *     <author>
 *         <name> xsd:string </name> [0..1]
 *         <email id="xsd:string [1]" domain="xsd:string [1]"/> [0..1]
 *         <link> linkType </link> [0..1]
 *     </author> [0..1]
 *     <copyright>
 *         author="xsd:string [1]">
 *         <year> xsd:gYear </year> [0..1]
 *         <license> xsd:anyURI </license> [0..1]
 *     </copyright> [0..1]
 *     <link href="xsd:anyURI [1]">
 *         <text> xsd:string </text> [0..1]
 *         <type> xsd:string </type> [0..1]
 *     </link> [0..*]
 *     <time> xsd:dateTime </time> [0..1]
 *     <keywords> xsd:string </keywords> [0..1]
 *     <bounds
 *         minlat="latitudeType [1]"
 *         minlon="longitudeType [1]"
 *         maxlat="latitudeType [1]"
 *         maxlon="longitudeType [1]"/> [0..1]
 *     <extensions> extensionsType </extensions> [0..1]
 * </metadata> [0..1]
 * <wpt> wptType </wpt> [0..*]
 * <rte> rteType </rte> [0..*]
 * <trk> trkType </trk> [0..*]
 * <extensions> extensionsType </extensions> [0..1]
 * </gpx>
 */

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

class QcGpx
{
public:
  QcGpx(); // QObject * parent = 0
  QcGpx(const QcGpx & other);
  ~QcGpx();

  QcGpx & operator=(const QcGpx & other);

  const QString & creator() const { return m_creator; }
  void set_creator(const QString & creator) { m_creator = creator; }

  const QString & version() const { return m_version; }
  void set_version(const QString & version) { m_version = version; }

  const QString & name() const { return m_name; }
  void set_name(const QString & name) { m_name = name; }

  const QString & description() const { return m_description; }
  void set_description(const QString & description) { m_description = description; }

  const QString & author() const { return m_author; }
  void set_author(const QString & author) { m_author = author; }

  const QString & link() const { return m_link; }
  void set_link(const QString & link) { m_link = link; }

  QDateTime time() const { return m_time; }
  void set_time(const QDateTime & time) { m_time = time; }

  const QString & keywords() const { return m_keywords; }
  void set_keywords(const QString & keywords) { m_keywords = keywords; }

  QcInterval2DDouble bounds() const { return m_bounds; }
  void set_bounds(const QcInterval2DDouble & bounds) { m_bounds = bounds; }

  const QcWayPointList & waypoints() const { return m_waypoints; }
  const QList<QcRoute> & routes() const { return m_routes; }
  const QList<QcTrack> & tracks() const { return m_tracks; }

  void add_waypoint(const QcWayPoint & waypoint);
  void add_route(const QcRoute & route);
  void add_track(const QcTrack & track);

private:
  QString m_creator;
  QString m_version;
  QString m_name;
  QString m_description;
  QString m_author;
  QString m_link;
  QDateTime m_time;
  QString m_keywords;
  QcInterval2DDouble m_bounds;
  QcWayPointList m_waypoints;
  QList<QcRoute> m_routes;
  QList<QcTrack> m_tracks;
};

/**************************************************************************************************/

class QcGpxReader
{
public:
  QcGpxReader();
  ~QcGpxReader();

  QcGpx read(const QString & gpx_path);

private:
  void read_metadata(QcGpx & gpx);
  void read_bounds(QcGpx & gpx);
  QcWayPoint read_waypoint(const QString & element);
  bool read_route_metadata(QcRouteMetaData & route, const QStringRef & ename);
  QcRoute read_route();
  QcTrack read_track();
  QcWayPointList read_track_segment();

private:
  QcXmlStreamReader m_reader;
};

/**************************************************************************************************/

class QcGpxWriter
{
public:
  QcGpxWriter();
  ~QcGpxWriter();

  void write(const QcGpx & gpx, const QString & gpx_path);

private:
  void write_metadata(const QcGpx & gpx);
  void write_waypoint(const QcWayPoint & waypoint);
  void write_route_metadata(const QcRouteMetaData & metadata);
  void write_route(const QcRoute & route);
  void write_track(const QcTrack & track);

private:
  QXmlStreamWriter m_writer;
};

/**************************************************************************************************/

// QC_END_NAMESPACE

#endif /* __QcGpx_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
