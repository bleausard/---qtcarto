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

#include "location_circle_material_shader.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

#include "shaders/location_circle_shader.h"

const char *
QcLocationCircleMaterialShader::vertexShader() const
{
  return vertex_shader_location_circle;
}

const char *
QcLocationCircleMaterialShader::fragmentShader() const
{
  return fragment_shader_location_circle;
}

QList<QByteArray>
QcLocationCircleMaterialShader::attributes() const
{
  return QList<QByteArray>()
    << "a_vertex"
    << "a_tex_coord"
    << "a_radius"
    << "a_angle";
}

void
QcLocationCircleMaterialShader::updateState(const QcLocationCircleMaterialShaderState * state,
                                            const QcLocationCircleMaterialShaderState *)
{
  program()->setUniformValue("cone_colour", state->cone_r, state->cone_g, state->cone_b, state->cone_a);
  program()->setUniformValue("accuracy_colour", state->accuracy_r, state->accuracy_g, state->accuracy_b, state->accuracy_a);
}

/**************************************************************************************************/

// QC_END_NAMESPACE

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
