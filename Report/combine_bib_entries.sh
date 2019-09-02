#!/bin/bash

rm library.bib
for bibfile in ManualBibEntries/*.bib; do 
  (cat "${bibfile}"; echo) >> library.bib
done