RED='\033[1;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

for i in $(seq 0 19); do
  printf "TEST $i\t"
  cp dataset/input/input$i.txt input.txt
  #time ./lich >/dev/null
  #TIME="$(bash -c "time ./lich > /dev/null" 2>&1)"
  start=`date +%s%N`
  ./lich >/dev/null
  end=`date +%s%N`
  TIME=`awk "BEGIN { print ($end - $start)/10000000/60 }" `
  if diff output.txt dataset/output/output$i.txt > /dev/null ; then
    echo "-->$TIME\t------> ${GREEN}OUTPUT CORRETTO${NC}"
  else
    echo "-->$TIME\t------> ${RED}OUTPUT SBAGLIATO${NC}"
fi
done
