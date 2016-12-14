for i in $(seq 0 19); do
  echo "TEST $i"
  cp dataset/input/input$i.txt input.txt
  #time
   ./lich >/dev/null 

  if diff output.txt dataset/output/output$i.txt > /dev/null ; then
    echo "------------> OUTPUT $i CORRETTO"
  else
    echo "------------> OUTPUT $i SBAGLIATO"
fi
done
