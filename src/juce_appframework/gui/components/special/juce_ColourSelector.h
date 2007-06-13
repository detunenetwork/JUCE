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

#ifndef __JUCE_COLOURSELECTOR_JUCEHEADER__
#define __JUCE_COLOURSELECTOR_JUCEHEADER__

#include "../controls/juce_Slider.h"
#include "../../../events/juce_ChangeBroadcaster.h"


//==============================================================================
/**
    A component that lets the user choose a colour.

    This shows RGB sliders and a colourspace that the user can pick colours from.

    This class is also a ChangeBroadcaster, so listeners can register to be told
    when the colour changes.
*/
class JUCE_API  ColourSelector  : public Component,
                                  public ChangeBroadcaster,
                                  protected SliderListener
{
public:
    //==============================================================================
    /** Options for the type of selector to show. These are passed into the constructor. */
    enum ColourSelectorOptions
    {
        showAlphaChannel    = 1 << 0,   /**< if set, the colour's alpha channel can be changed as well as its RGB. */

        showColourAtTop     = 1 << 1,   /**< if set, a swatch of the colour is shown at the top of the component. */
        showSliders         = 1 << 2,   /**< if set, RGB sliders are shown at the bottom of the component. */
        showColourspace     = 1 << 3    /**< if set, a big HSV selector is shown. */
    };

    //==============================================================================
    /** Creates a ColourSelector object.

        The flags are a combination of values from the ColourSelectorOptions enum, specifying
        which of the selector's features should be visible.

        The edgeGap value specifies the amount of space to leave around the edge.

        gapAroundColourSpaceComponent indicates how much of a gap to put around the
        colourspace and hue selector components.
    */
    ColourSelector (const int sectionsToShow = (showAlphaChannel | showColourAtTop | showSliders | showColourspace),
                    const int edgeGap = 4,
                    const int gapAroundColourSpaceComponent = 7);

    /** Destructor. */
    ~ColourSelector();

    //==============================================================================
    /** Returns the colour that the user has currently selected.

        The ColourSelector class is also a ChangeBroadcaster, so listeners can
        register to be told when the colour changes.

        @see setCurrentColour
    */
    const Colour getCurrentColour() const;

    /** Changes the colour that is currently being shown.
    */
    void setCurrentColour (const Colour& newColour);

    //==============================================================================
    /** Tells the selector how many preset colour swatches you want to have on the component.

        To enable swatches, you'll need to override getNumSwatches(), getSwatchColour(), and
        setSwatchColour(), to return the number of colours you want, and to set and retrieve
        their values.
    */
    virtual int getNumSwatches() const;

    /** Called by the selector to find out the colour of one of the swatches.

        Your subclass should return the colour of the swatch with the given index.

        To enable swatches, you'll need to override getNumSwatches(), getSwatchColour(), and
        setSwatchColour(), to return the number of colours you want, and to set and retrieve
        their values.
    */
    virtual const Colour getSwatchColour (const int index) const;

    /** Called by the selector when the user puts a new colour into one of the swatches.

        Your subclass should change the colour of the swatch with the given index.

        To enable swatches, you'll need to override getNumSwatches(), getSwatchColour(), and
        setSwatchColour(), to return the number of colours you want, and to set and retrieve
        their values.
    */
    virtual void setSwatchColour (const int index, const Colour& newColour) const;

    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    friend class ColourSpaceView;
    friend class HueSelectorComp;
    Colour colour;
    float h, s, v;
    Slider* sliders[4];
    Component* colourSpace;
    Component* hueSelector;
    VoidArray swatchComponents;
    const int flags;
    int topSpace, edgeGap;

    void setHue (float newH);
    void setSV (float newS, float newV);
    void updateHSV();
    void update();
    void sliderValueChanged (Slider*);
    void paint (Graphics& g);
    void resized();

    ColourSelector (const ColourSelector&);
    const ColourSelector& operator= (const ColourSelector&);

    // this constructor is here temporarily to prevent old code compiling, because the parameters
    // have changed - if you get an error here, update your code to use the new constructor instead..
    // (xxx - note to self: remember to remove this at some point in the future)
    ColourSelector (const bool);
};


#endif   // __JUCE_COLOURSELECTOR_JUCEHEADER__
