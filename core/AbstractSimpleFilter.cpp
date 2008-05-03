/***************************************************************************
    File                 : AbstractSimpleFilter.cpp
    Project              : SciDAVis
    --------------------------------------------------------------------
    Copyright            : (C) 2007,2008 by Knut Franke, Tilman Benkert
    Email (use @ for *)  : knut.franke*gmx.de, thzs*gmx.net
    Description          : Simplified filter interface for filters with
                           only one output port.

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *  This program is free software; you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation; either version 2 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the Free Software           *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor,                    *
 *   Boston, MA  02110-1301  USA                                           *
 *                                                                         *
 ***************************************************************************/

#include "AbstractSimpleFilter.h"

// TODO: should simple filters have a name argument?
AbstractSimpleFilter::AbstractSimpleFilter()
	: AbstractFilter("SimpleFilter"), d_output_column(new SimpleFilterColumn(this))
{
	addChild(d_output_column);
}

void AbstractSimpleFilter::clearMasks()
{
	emit d_output_column->maskingAboutToChange(d_output_column);
	d_masking.clear();
	emit d_output_column->maskingChanged(d_output_column);
}

void AbstractSimpleFilter::setMasked(Interval<int> i, bool mask)
{
	emit d_output_column->maskingAboutToChange(d_output_column);
	d_masking.setValue(i, mask);
	emit d_output_column->maskingChanged(d_output_column);
}

void AbstractSimpleFilter::inputPlotDesignationAboutToChange(const AbstractColumn*)
{
	emit d_output_column->plotDesignationAboutToChange(d_output_column);
}

void AbstractSimpleFilter::inputPlotDesignationChanged(const AbstractColumn*)
{
	emit d_output_column->plotDesignationChanged(d_output_column);
}

void AbstractSimpleFilter::inputModeAboutToChange(const AbstractColumn*)
{
	emit d_output_column->dataAboutToChange(d_output_column);
}

void AbstractSimpleFilter::inputModeChanged(const AbstractColumn*)
{
	emit d_output_column->dataChanged(d_output_column);
}

void AbstractSimpleFilter::inputDataAboutToChange(const AbstractColumn*)
{
	emit d_output_column->dataAboutToChange(d_output_column);
}

void AbstractSimpleFilter::inputDataChanged(const AbstractColumn*)
{
	emit d_output_column->dataChanged(d_output_column);
}

void AbstractSimpleFilter::inputRowsAboutToBeInserted(const AbstractColumn * source, int before, int count)
{
	Q_UNUSED(source);
	Q_UNUSED(count);
	foreach(Interval<int> output_range, dependentRows(Interval<int>(before, before)))
		emit d_output_column->rowsAboutToBeInserted(d_output_column, output_range.start(), output_range.size());
}

void AbstractSimpleFilter::inputRowsInserted(const AbstractColumn * source, int before, int count)
{
	Q_UNUSED(source);
	Q_UNUSED(count);
	foreach(Interval<int> output_range, dependentRows(Interval<int>(before, before)))
		emit d_output_column->rowsInserted(d_output_column, output_range.start(), output_range.size());
}

void AbstractSimpleFilter::inputRowsAboutToBeRemoved(const AbstractColumn * source, int first, int count)
{
	Q_UNUSED(source);
	foreach(Interval<int> output_range, dependentRows(Interval<int>(first, first+count-1)))
		emit d_output_column->rowsAboutToBeRemoved(d_output_column, output_range.start(), output_range.size());
}

void AbstractSimpleFilter::inputRowsRemoved(const AbstractColumn * source, int first, int count)
{
	Q_UNUSED(source);
	foreach(Interval<int> output_range, dependentRows(Interval<int>(first, first+count-1)))
		emit d_output_column->rowsRemoved(d_output_column, output_range.start(), output_range.size());
}

AbstractColumn *AbstractSimpleFilter::output(int port)
{
	return port == 0 ? static_cast<AbstractColumn*>(d_output_column) : 0;
}

const AbstractColumn *AbstractSimpleFilter::output(int port) const
{
	return port == 0 ? static_cast<const AbstractColumn*>(d_output_column) : 0;
}