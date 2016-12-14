for i in $(seq 0 20); do
  cp dataset/input/input$i.txt input.txt
  time ./lich >/dev/null
  echo "testing file $i"
  diff -q output.txt dataset/output/output$i.txt
done
