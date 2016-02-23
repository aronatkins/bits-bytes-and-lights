#!/usr/bin/python
#
# A python program which builds a table showing the transformations performed
# by the Wheel function that is part of the strandtest example included within
# the NeoPixel library.
#
# References:
#   https://github.com/adafruit/Adafruit_NeoPixel/blob/be0d7706e196dd8479e4573038785bad0b1e6726/examples/strandtest/strandtest.ino
#   https://github.com/adafruit/Adafruit_NeoPixel/tree/be0d7706e196dd8479e4573038785bad0b1e6726/examples/strandtest
#   https://github.com/adafruit/Adafruit_NeoPixel

def wheel(position) :
    """
    reimplementation of Wheel in python. returns a rgb triple instead of
    converting to a 32-bit value.
    """
    position = 255 - position
    if position < 85:
        return (255 - position * 3, 0, position * 3)
    if position < 170:
        position = position - 85
        return (0, position * 3, 255 - position * 3)
    position = position - 170
    return (position * 3, 255 - position * 3, 0)

def color32(rgb) :
    """
    reimplementation of Adafruit_NeoPixel::Color, taking an rgb triple and
    returning a 32-bit number (the top eight bits are unused here).
    """
    (r,g,b) = rgb
    return (r << 16) | (g << 8) | b


def make_table(positions) :
    reds = []
    greens = []
    blues = []
    colors = []

    for position in positions:
        rgb = wheel(position)
        c = color32(rgb)

        reds.append(rgb[0])
        greens.append(rgb[1])
        blues.append(rgb[2])
        colors.append(c)

    print "<tbody>"
    print "<tr><th>position</th>" + "".join([ "<th>%d</th>" % position for position in positions ]) + "</tr>"
    print "<tr><th>Red</th>" + "".join([ "<td>%d</td>" % red for red in reds ]) + "</tr>"
    print "<tr><th>Green</th>" + "".join([ "<td>%d</td>" % green for green in greens ]) + "</tr>"
    print "<tr><th>Blue</th>" + "".join([ "<td>%d</td>" % blue for blue in blues ]) + "</tr>"
    print "<tr><th>HTML color code</th>" + "".join([ "<td><tt>#%06x<tt></td>" % color for color in colors ]) + "</tr>"
    print "<tr><th>HTML color</th>" + "".join([ "<td style='background-color:#%06x;'></td>" % color for color in colors ]) + "</tr>"
    print "</tbody>"


print "<table>"
step = 8
for i in range(0,256,step) :
    make_table(range(i,i+step))
print "</table>"
