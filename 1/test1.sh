#!/bin/bash
for i in $(seq 0 20); do
  echo Test $i
  cp dataset/input/input$i.txt input.txt
  ./pokemon >/dev/null
  diff -q <(head -n 1 output.txt) <(head -n 1 dataset/output/output$i.txt)
done
