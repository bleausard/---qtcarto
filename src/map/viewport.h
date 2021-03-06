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

#ifndef __VIEWPORT_H__
#define __VIEWPORT_H__

/**************************************************************************************************/

#include <QObject>
#include <QSize>

#include "qtcarto_global.h"
#include "coordinate/wgs84.h"
#include "geometry/polygon.h"
#include "math/interval.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

class QcMapScale
{
  Q_GADGET
  Q_PROPERTY(double length READ length CONSTANT)
  Q_PROPERTY(int length_px READ length_px CONSTANT)

public:
  QcMapScale() : m_length(0), m_length_px(0) {}
  QcMapScale(double length, int length_px) : m_length(length), m_length_px(length_px) {}

  double length() const { return m_length; }
  int length_px() const { return m_length_px; }

public:
  double m_length;
  int m_length_px;
};

// Q_DECLARE_METATYPE(QcMapScale)

/**************************************************************************************************/

/*!
 *
 * Map Resolution unit is [m/px]
 *
 */
class QC_EXPORT QcMapResolution
{
 public:
  QcMapResolution();
  QcMapResolution(double resolution);
  QcMapResolution(const QcMapResolution & other);
  ~QcMapResolution();

  QcMapResolution & operator=(const QcMapResolution & other);

  bool operator==(const QcMapResolution & other) const {
    return m_resolution == other.m_resolution;
  }

  bool operator!=(const QcMapResolution & other) const {
    return !operator==(other);
  }

  double resolution() const { return m_resolution; }
  void set_resolution(double resolution);

  double from_px(double distance_px) const {
    return distance_px * resolution();
  }

  double to_px(double distance) const {
    // Fxime: cache inverse ?
    return distance / resolution();
  }

 private:
  double m_resolution;
};

/**************************************************************************************************/

// Tool to compute a zoom factor from a pyramid
// Fixme: versus tile matrix ???
class QC_EXPORT QcTiledZoomLevel : public QcMapResolution
{
 public:
  QcTiledZoomLevel();
  QcTiledZoomLevel(double map_size, unsigned int tile_size, unsigned int zoom_level = 0); // Fixme: tile_size depends of the map 256, 512 !!!
  QcTiledZoomLevel(const QcTiledZoomLevel & other);
  ~QcTiledZoomLevel();

  QcTiledZoomLevel & operator=(const QcTiledZoomLevel & other);

  bool operator==(const QcTiledZoomLevel & other) const;

  bool operator!=(const QcTiledZoomLevel & other) const {
    return !operator==(other);
  }

  double map_size() const { return m_map_size; }

  unsigned int tile_size() const { return m_tile_size; }

  unsigned int zoom_level() const { return m_zoom_level; }
  void set_zoom_level(unsigned int zoom_level);

 private:
  unsigned int m_tile_size;
  unsigned int m_zoom_level;
  double m_map_size;
};

/**************************************************************************************************/

class QC_EXPORT QcViewportState
{
 public:
  bool is_valid_bearing(double bearing) {
    return -180. <= bearing && bearing <= 180.;
  }

 public:
  QcViewportState();
  // Fixme: QcTiledZoomLevel or QcMapResolution ???
  QcViewportState(const QcWgsCoordinate & coordinate, const QcTiledZoomLevel & tiled_zoom_level, double bearing);
  QcViewportState(const QcViewportState & other);
  ~QcViewportState();

  QcViewportState & operator=(const QcViewportState & other);

  bool operator==(const QcViewportState & other) const;
  bool operator!=(const QcViewportState & other) const {
    return !operator==(other);
  }

  QcWgsCoordinate coordinate() const { return m_coordinate; }
  void set_coordinate(const QcWgsCoordinate & coordinate) { m_coordinate = coordinate; }

  double bearing() const { return m_bearing; }
  void set_bearing(double bearing);

  const QcTiledZoomLevel & tiled_zoom_level() const { return m_tiled_zoom_level; }

  unsigned int zoom_level() const { return m_tiled_zoom_level.zoom_level(); }
  void set_zoom_level(unsigned int zoom_level) { m_tiled_zoom_level.set_zoom_level(zoom_level); }

 private:
  QcWgsCoordinate m_coordinate;
  QcTiledZoomLevel m_tiled_zoom_level;
  double m_bearing;
};

/**************************************************************************************************/

class QcViewport;

class QcViewportPart
{
public:
  QcViewportPart();
  QcViewportPart(const QcViewport * m_viewport,
                 int position,
                 const QcInterval2DDouble screen_interval,
                 // double offset,
                 const QcPolygon & polygon // Fixme: interval ?
                 );
  QcViewportPart(const QcViewportPart & other);
  ~QcViewportPart();

  QcViewportPart & operator=(const QcViewportPart & other);

  const QcViewport * viewport() const { return m_viewport; }

  int position() const { return m_position; }
  const QcInterval2DDouble & screen_interval() const  { return m_screen_interval; }
  const QcPolygon & polygon() const { return m_polygon; }
  const QcInterval2DDouble & interval() const  { return m_polygon.interval(); }

  operator bool() const { return m_position != -1; }

  void clear();

  bool contains(const QcVectorDouble & projected_coordinate) const;
  QcVectorDouble inf_position() const;
  QcVectorDouble map_vector(const QcVectorDouble & projected_coordinate) const;

private:
  const QcViewport * m_viewport;
  int m_position;
  QcInterval2DDouble m_screen_interval;
  QcPolygon m_polygon;
};

#ifndef QT_NO_DEBUG_STREAM
QC_EXPORT QDebug operator<<(QDebug debug, const QcViewportPart & viewport_part);
#endif

/**************************************************************************************************/

class QC_EXPORT QcViewport : public QObject
{
  Q_OBJECT

 public:
  static QcInterval2DDouble interval_from_center_and_size(const QcVectorDouble & center, const QcVectorDouble & size);

 public:
  QcViewport(const QcViewportState & viewport_state, const QSize & viewport_size); // Fixme : tiled_zoom_level has parameters

  const QcViewportState & viewport_state() const { return m_state; }

  const QcProjection * projection_ptr() const { return m_projection; }
  const QcProjection & projection() const { return *m_projection; } // Fixme: m_projection = nullptr
  void set_projection(const QcProjection * projection);

  // Fixme: add flag ready ?
  // int smallest_tile_size() const { return m_smallest_tile_size; }
  const QcIntervalInt & zoom_level_interval() const { return m_zoom_level_interval; }
  void set_zoom_level_interval(const QcIntervalInt & zoom_level_interval, int smallest_tile_size);

  QcWgsCoordinate center() const { return m_state.coordinate(); }
  QcVectorDouble projected_center_coordinate() const;
  void set_center(const QcWgsCoordinate & coordinate);

  double bearing() const { return m_state.bearing(); }
  void set_bearing(double bearing);

  unsigned int zoom_level() const { return tiled_zoom_level().zoom_level(); }
  void set_zoom_level(unsigned int zoom_level);

  double resolution() const { return tiled_zoom_level().resolution(); }
  // void set_resolution(double resolution);

  QcVectorDouble to_projected_coordinate(const QcWgsCoordinate & coordinate) const;
  QcWgsCoordinate from_projected_coordinate(const QcVectorDouble & coordinate) const;

  QcVectorDouble screen_to_projected_coordinate(const QcVectorDouble & screen_position, bool clip_to_viewport = false) const;
  QcWgsCoordinate screen_to_coordinate(const QcVectorDouble & position, bool clip_to_viewport = false) const;
  QcVectorDouble coordinate_to_screen(const QcVectorDouble & projected_coordinate, bool clip_to_viewport = false) const;
  QcVectorDouble coordinate_to_screen(const QcWgsCoordinate & coordinate, bool clip_to_viewport = false) const;

  double from_px(double distance_px) const { return tiled_zoom_level().from_px(distance_px); }
  double to_px(double distance) const { return tiled_zoom_level().to_px(distance); }
  QcVectorDouble from_px(const QcVectorDouble & distance_px) const { return distance_px * resolution(); }
  QcVectorDouble to_px(const QcVectorDouble & distance) const { return distance / resolution(); }

  QSize viewport_size() const { return m_viewport_size; }
  int width() const  { return m_viewport_size.width(); }
  int height() const  { return m_viewport_size.height(); }
  void set_viewport_size(const QSize & size, float device_pixel_ratio);

  QcVectorDouble area_size_m() const { return m_area_size_m; }

  void stable_zoom(const QcVectorDouble & position_px, unsigned int zoom_level);
  void zoom_at(const QcWgsCoordinate & coordinate, unsigned int zoom_level);
  void pan(const QcVectorDouble & translation);
  void pan(double x, double y) {
    pan(QcVectorDouble(x, y));
  }

  bool is_interval_defined() const;

  bool cross_boundaries() const { return m_cross_boundaries; }
  bool cross_west_line() const { return m_cross_west_line; }
  bool cross_east_line() const { return m_cross_east_line; }
  int number_of_full_maps() const { return m_number_of_full_maps; }

  const QcViewportPart & east_part() const { return m_east_part; }
  const QcViewportPart & central_part() const { return m_central_part; }
  const QList<QcViewportPart> & central_part_clones() const { return m_central_part_clones; }
  const QcViewportPart & west_part() const { return m_west_part; }

  QcMapScale make_scale(unsigned int max_length_px);

 signals:
  void viewport_changed();

 private:
  const QcTiledZoomLevel & tiled_zoom_level() const { return m_state.tiled_zoom_level(); }
  void update_zoom_level_interval();
  void update_area_size();
  QcVectorDouble inf_point() const;
  void update_area();
  const QcViewportPart * find_part(const QcVectorDouble & projected_coordinate) const;
  void begin_state_transaction();
  void end_state_transaction();
  QcPolygon compute_polygon() const;
  void adjust_center();

 private:
  QcViewportState m_state;
  QcViewportState m_previous_state;
  int m_state_transaction = 0;
  const QcProjection * m_projection = nullptr; // Fixme: const
  bool m_is_web_mercator = false;

  int m_smallest_tile_size = -1;
  QcIntervalInt m_map_zoom_level_interval;
  QcIntervalInt m_zoom_level_interval;

  QSize m_viewport_size; // px   Fixme: QcVectorInt ?
  float m_device_pixel_ratio;
  int m_smallest_zoom_level;
  QcVectorDouble m_area_size_m;
  QcVectorDouble m_half_diagonal_m;

  QcPolygon m_viewport_polygon;
  bool m_center_map_vertically; // map height < item height
  QcIntervalDouble m_y_screen_interval;

  QcViewportPart m_west_part;
  QcViewportPart m_central_part;
  QList<QcViewportPart> m_central_part_clones;
  QcViewportPart m_east_part;

  bool m_cross_boundaries;
  bool m_cross_west_line;
  bool m_cross_east_line;
  int m_number_of_full_maps;
};

/**************************************************************************************************/

#endif /* __VIEWPORT_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
