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

#ifndef __JUCE_CHANGELISTENER_JUCEHEADER__
#define __JUCE_CHANGELISTENER_JUCEHEADER__


//==============================================================================
/**
    Receives callbacks about changes to some kind of object.

    Many objects use a ChangeListenerList to keep a set of listeners which they
    will inform when something changes. A subclass of ChangeListener
    is used to receive these callbacks.

    Note that the major difference between an ActionListener and a ChangeListener
    is that for a ChangeListener, multiple changes will be coalesced into fewer
    callbacks, but ActionListeners perform one callback for every event posted.

    @see ChangeListenerList, ChangeBroadcaster, ActionListener
*/
class JUCE_API  ChangeListener
{
public:
    /** Destructor. */
    virtual ~ChangeListener()  {}

    /** Overridden by your subclass to receive the callback.

        @param objectThatHasChanged the value that was passed to the
                                    ChangeListenerList::sendChangeMessage() method
    */
    virtual void changeListenerCallback (void* objectThatHasChanged) = 0;
};


#endif   // __JUCE_CHANGELISTENER_JUCEHEADER__
