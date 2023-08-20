<!--
Simple Filter - very simple LP/HP/BP/BR filter.
 
 Copyright (C) 2023 Christoph Wellm <christoph.wellm@creaflect.de>

 This program is free software: you can redistribute it and/or modify it under the terms of the 
 GNU General Public License version 3 as published by the Free Software Foundation.
 
 This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without 
 even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
 General Public License for more details. 
 
 You should have received a copy of the GNU General Public License along with this program.  
 If not, see <http://www.gnu.org/licenses/>.
  
 SPDX-License-Identifier: GPL-3.0-only
-->

# Simple Filter

This project consists of a very simple filter.
It serves mainly as a study project, but aims at supplying some interesting, experimental features.
As a basis, the [JUCE Framework](https://github.com/juce-framework/JUCE) is used heavily. 

## Table of Contents

* [Features](#features)
* [Getting Started](#getting-started)
    * [System Requirements](#system-requirements)
    * [Dependencies](#dependencies)
    * [Installation](#installation)
* [License](#license)
* [Development](#development)
    * [Building](#building)
    * [Code Structure](#code-structure)
    * [Extending](#extending)
* [Known Issues](#known-issues)
* [Contact](#contact)

## Features

Four different modes:
* LP (low pass)
* HP (high pass)
* BP (bandpass)
* BR (band reject)

For BP and BR, you can adjust the center frequency and the frequency window. These two interact with
each other in the sense that the edge frequencies never go below 0 Hz and 20 kHz.

![Screenshot of the current version of the plugin.](/res/shotv_0_1.png)

## Getting Started

### System Requirements

This plugin has been tested to be working with the following setup:

#### Operating System

* Ubuntu-22.04
* Windows Server 2022
* Windows 10
* MAC OS 12

#### DAW

* Reaper 

Feel free to let me know about your experiences with your setup, so I can extend these lists :slightly_smiling_face:	

### Dependencies

- [JUCE Framework](https://github.com/juce-framework/JUCE)

### Installation

#### Current Version

Right click, "save link as..."

[Windows](artifacts/Simple_Filter_Windows.zip)

[Linux](artifacts/Simple_Filter_Linux.zip)

[MAC OS](artifacts/Simple_Filter_Macos.zip)

These are readily-built libraries, which you can simply download, unzip and put into your VST3 Plugin directory.

### Documentation

--- coming soon ---

## License

This software is licensed under the GPL-3.0. See the [license text](LICENSE) for more information. Appropriate copyright notices are
added to all source files which originate from the contributors of this repository. Copyright information of the dependencies in use
within this software is given in the according links under the [Dependencies](#dependencies) section.

Licenses used throughout this project can be found in the [LICENSES](LICENSES) folder. 

Some files do not explicitly contain a license header. In this case, these are covered by the matching license as specified
in the [dep5](.reuse/dep5) file (for instance, for binary files). See [here](https://reuse.software/faq/#bulk-license) for more information about this.

To get a bill of materials of the files this repository (without dependencies), you can use [reuse spdx](https://reuse.readthedocs.io/en/latest/readme.html#usage).

## Development

--- coming soon ---

### Building

--- coming soon ---

### Code Structure

--- coming soon ---

### Extending

--- coming soon ---

## Known Issues

--- none so far ---

## Contribution

--- coming soon ---

## Contact

--- coming soon ---
