# DESYSummer2019
Scripts generated during the DESY Summer Student Programme 2019, for analysis of the semileptonic decay of a pair of W bosons.
include/ src/ and CMakelists required to build processor for analysis

## Report:
```LaTeX files used in the generation of the final report - report submitted 05/09/19```

## Presentation:
```LaTeX files used in the generation of the final presentation - presented 02/09/19```

## include:
```Contains .h files for processor```

## src:
```Contains .cc files for processor```

## CMakelists:
```cmake file for building Marlin Package```

## scripts:
```steering_files for running processor with Marlin```
```.py and .cc scripts used to analyse .root file output of processor```

### Tips and Tricks:
- 'nohup ariane' allows you to close your terminal window
- use nedit to edit the segrid.
  - preferences > wrap = none
  - preferences > Text Fonts > -misc-fixed-medium-r-normal--6-60-75-75-c-40-iso8859-1         i.e. font size 6
  - use scroll bars to navigate, don't use the scroll wheel or 2 finger drag because it is laggy
  - use 'ctrl+click' and drag to select horizontal or vertical regions and then the macro 'fill Sel. w/ char' to replace the
    selections with numbers. Much better than doing it by hand.
- add a surface lid to try prevent node dropping
