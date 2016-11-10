#!/bin/sh
for i in $(seq 0 20); do
  cp dataset/input/input$i.txt input.txt
  pokemon
  diff -q output.txt dataset/output/output$i.txt
done
