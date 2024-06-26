/*
Copyright (C) 2020 Phillip Lamp
This file is part of the SMPLComp project <https://github.com/p-hlp/SMPLComp>.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "MeterNeedle.h"
#include "../util/Constants.h"
#include <limits>

MeterNeedle::MeterNeedle()
{
    valueInDecibel = 0.0f;
    mode = 3;
    minValue = 0;
    maxValue = 0;
    sAngle = 0.0f;
    eAngle = 0.0f;
    statusOutline = juce::Colour(Constants::Colors::statusOutline);
}

void MeterNeedle::paint(juce::Graphics &g)
{
    const auto bounds = area.toFloat();
    const float centreX = bounds.getX() + bounds.getWidth() * 0.5f;
    const float centreY = bounds.getY() + bounds.getHeight();
    const float needleLength = juce::jmin(bounds.getWidth() * 0.75f, bounds.getHeight() * 0.75f);

    g.setColour(statusOutline);
    redrawNeedle(g, centreX, centreY, needleLength);
}

void MeterNeedle::resized()
{
    area = getLocalBounds().reduced(3);
    repaint();
}

void MeterNeedle::update(const float &val)
{
    if (std::abs(val - valueInDecibel) > std::numeric_limits<float>::epsilon())
    {
        valueInDecibel = val;
        repaint();
    }
}

void MeterNeedle::redrawNeedle(juce::Graphics &g, float centreX, float centreY, float length)
{
    float val = std::clamp(valueInDecibel, static_cast<float>(minValue), static_cast<float>(maxValue));
    float mapped = juce::jmap(val, static_cast<float>(minValue), static_cast<float>(maxValue), sAngle, eAngle);
    mapped -= mapped > 2 * juce::MathConstants<float>::pi ? juce::MathConstants<float>::twoPi : 0.0f;
    const float x2 = centreX + sin(mapped) * length;
    const float y2 = centreY - cos(mapped) * length;
    g.drawArrow({centreX, centreY, x2, y2}, 2.0f, 0, 0);
}

void MeterNeedle::prepare(const float &s, const float &e)
{
    sAngle = s;
    eAngle = e;
}

void MeterNeedle::setMode(int m)
{
    minValue = m == 3 ? -30 : -50;
    mode = m;
    repaint();
}
