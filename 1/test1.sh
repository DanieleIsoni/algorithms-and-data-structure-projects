#!/bin/bash
for i in $(seq 0 20); do
  cp dataset/input/input$i.txt input.txt
  time ./pokemon
  diff -q <(head -n 1 output.txt) <(head -n 1 dataset/output/output$i.txt)
done
