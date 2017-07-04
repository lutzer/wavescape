# wavescape

a wave landscape synthesizer prototype

## Setup

- install ofxGuiExtended addon from https://github.com/frauzufall/ofxGuiExtended
- install jack from http://jackaudio.org/ to send soundstream from openframeworks to puredata
- start *qjackctl* and run openframeworks and puredata patches, then route the 2 channels from of to pd.

## Todo

* [x] Implement bilinear interpolation, see: https://en.wikipedia.org/wiki/Bilinear_interpolation#Unit_Square
* [x] Fix hypocloid function https://en.wikipedia.org/wiki/Hypocycloid
* [ ] Calculate lenth of hypocycloid: <http://www-math.mit.edu/~djk/18_01/chapter18/section02.html>


