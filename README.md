# Main Road Post config for SideFX Houdini

## Contents

### Materials and Shading Models

This package consists of the following shading models and materials:

* MRP GGX Specular
* MRP GGX Metallic
* MRP GGX Glass
* MRP Berry Specular
* MRP Principled Shader Core
* MRP Principled Shader

The most important difference with Houdini's built-in shading models is our models returns correct albedo value for it's parameters, instead of just 1.0 multiplied by color. This feature reduces noise significantly in some cases and allows us to use `Conserve Energy` VOP node to ensure we are not violating energy conservation without making our shaders too dark.

![GGX Metallic](/examples/ggx_metallic.png?raw=true "GGX Metallic")

## Installation

Just add this repo to `HOUDINI_PATH` environment variable before starting of Houdini.
For example, you may do this writing the following to your `houdini.env` file:

`HOUDINI_PATH = YOUR_PATH\houdini_configs;&`

Depending on OS and Houdini version you are using, you may find `houdini.env` in the following places:

| OS | Location | Example |
| ------ | ------ | ------ |
| Linux | $HOME/houdini[ver#] | /home/mike/houdini16.5/houdini.env |
| Windows | C:\Users\[username]\Documents\houdini[ver#] |  C:\Users\mike\Documents\houdini16.5\houdini.env |
| MacOSX | /Users/[username]/Library/Preferences/houdini/[ver#] | /Users/mike/Library/Preferences/houdini/16.5/houdini.env |
