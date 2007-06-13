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

#ifndef __JUCE_THREADWITHPROGRESSWINDOW_JUCEHEADER__
#define __JUCE_THREADWITHPROGRESSWINDOW_JUCEHEADER__

#include "../windows/juce_AlertWindow.h"
#include "../../../events/juce_Timer.h"
#include "../../../../juce_core/threads/juce_Thread.h"


//==============================================================================
/**
    A thread that automatically pops up a modal dialog box with a progress bar
    and cancel button while it's busy running.

    These are handy for performing some sort of task while giving the user feedback
    about how long there is to go, etc.

    E.g. @code
    class MyTask  : public ThreadWithProgressWindow
    {
    public:
        MyTask()    : ThreadWithProgressWindow (T("busy..."), true, true)
        {
        }

        ~MyTask()
        {
        }

        void run()
        {
            for (int i = 0; i < thingsToDo; ++i)
            {
                // must check this as often as possible, because this is
                // how we know if the user's pressed 'cancel'
                if (threadShouldExit())
                    break;

                // this will update the progress bar on the dialog box
                setProgress (i / (double) thingsToDo);


                //   ... do the business here...
            }
        }
    };

    void doTheTask()
    {
        MyTask m;

        if (m.runThread())
        {
            // thread finished normally..
        }
        else
        {
            // user pressed the cancel button..
        }
    }

    @endcode

    @see Thread, AlertWindow
*/
class JUCE_API  ThreadWithProgressWindow  : public Thread,
                                            private Timer
{
public:
    //==============================================================================
    /** Creates the thread.

        Initially, the dialog box won't be visible, it'll only appear when the
        runThread() method is called.

        @param windowTitle              the title to go at the top of the dialog box
        @param hasProgressBar           whether the dialog box should have a progress bar (see
                                        setProgress() )
        @param hasCancelButton          whether the dialog box should have a cancel button
        @param timeOutMsWhenCancelling  when 'cancel' is pressed, this is how long to wait for
                                        the thread to stop before killing it forcibly (see
                                        Thread::stopThread() )
    */
    ThreadWithProgressWindow (const String& windowTitle,
                              const bool hasProgressBar,
                              const bool hasCancelButton,
                              const int timeOutMsWhenCancelling = 10000);

    /** Destructor. */
    ~ThreadWithProgressWindow();

    //==============================================================================
    /** Starts the thread and waits for it to finish.

        This will start the thread, make the dialog box appear, and wait until either
        the thread finishes normally, or until the cancel button is pressed.

        Before returning, the dialog box will be hidden.

        @param threadPriority   the priority to use when starting the thread - see
                                Thread::startThread() for values
        @returns true if the thread finished normally; false if the user pressed cancel
    */
    bool runThread (const int threadPriority = 5);

    /** The thread should call this periodically to update the position of the progress bar.

        @param newProgress  the progress, from 0.0 to 1.0
        @see setStatusMessage
    */
    void setProgress (const double newProgress);

    /** The thread can call this to change the message that's displayed in the dialog box.
    */
    void setStatusMessage (const String& newStatusMessage);


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    void timerCallback();

    double progress;
    AlertWindow alertWindow;
    String message;
    const int timeOutMsWhenCancelling;

    ThreadWithProgressWindow (const ThreadWithProgressWindow&);
    const ThreadWithProgressWindow& operator= (const ThreadWithProgressWindow&);
};

#endif   // __JUCE_THREADWITHPROGRESSWINDOW_JUCEHEADER__
