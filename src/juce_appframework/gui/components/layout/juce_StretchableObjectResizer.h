/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-7 by Raw Material Software ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the
   GNU General Public License, as published by the Free Software Foundation;
   either version 2 of the License, or (at your option) any later version.

   JUCE is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with JUCE; if not, visit www.gnu.org/licenses or write to the
   Free Software Foundation, Inc., 59 Temple Place, Suite 330, 
   Boston, MA 02111-1307 USA

  ------------------------------------------------------------------------------

   If you'd like to release a closed-source product which uses JUCE, commercial
   licenses are also available: visit www.rawmaterialsoftware.com/juce for
   more information.

  ==============================================================================
*/

#ifndef __JUCE_STRETCHABLEOBJECTRESIZER_JUCEHEADER__
#define __JUCE_STRETCHABLEOBJECTRESIZER_JUCEHEADER__

#include "../../../../juce_core/containers/juce_OwnedArray.h"


//==============================================================================
/**
    A utility class for fitting a set of objects whose sizes can vary between
    a minimum and maximum size, into a space.

    This is a trickier algorithm than it would first seem, so I've put it in this
    class to allow it to be shared by various bits of code.

    To use it, create one of these objects, call addItem() to add the list of items
    you need, then call resizeToFit(), which will change all their sizes. You can
    then retrieve the new sizes with getItemSize() and getNumItems().

    It's currently used by the TableHeaderComponent for stretching out the table
    headings to fill the table's width.
*/
class StretchableObjectResizer
{
public:
    //==============================================================================
    /** Creates an empty object resizer. */
    StretchableObjectResizer();

    /** Destructor. */
    ~StretchableObjectResizer();

    //==============================================================================
    /** Adds an item to the list.

        The order parameter lets you specify groups of items that are resized first when some
        space needs to be found. Those items with an order of 0 will be the first ones to be
        resized, and if that doesn't provide enough space to meet the requirements, the algorithm
        will then try resizing the items with an order of 1, then 2, and so on.
    */
    void addItem (const double currentSize,
                  const double minSize,
                  const double maxSize,
                  const int order = 0);

    /** Resizes all the items to fit this amount of space.

        This will attempt to fit them in without exceeding each item's miniumum and
        maximum sizes. In cases where none of the items can be expanded or enlarged any
        further, the final size may be greater or less than the size passed in.

        After calling this method, you can retrieve the new sizes with the getItemSize()
        method.
    */
    void resizeToFit (const double targetSize);

    /** Returns the number of items that have been added. */
    int getNumItems() const throw()                         { return items.size(); }

    /** Returns the size of one of the items. */
    double getItemSize (const int index) const throw();


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    struct Item
    {
        double size;
        double minSize;
        double maxSize;
        int order;
    };

    OwnedArray <Item> items;

    StretchableObjectResizer (const StretchableObjectResizer&);
    const StretchableObjectResizer& operator= (const StretchableObjectResizer&);
};


#endif   // __JUCE_STRETCHABLEOBJECTRESIZER_JUCEHEADER__
